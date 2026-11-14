"""Original affine-positive dot representation: exact word-level finite model.

Each row has a power-of-two offset and a cached sum. Hot products are unsigned,
with no offset decode, per-product signed extension, or per-product scale shift.
Corrections and a single scale shift occur after the complete accumulation.
"""
from pathlib import Path
import collections
from datetime import datetime, timezone
import importlib.util
import json
import random
import hashlib
import sys
sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location("mixer_model", HERE / "mixer_path_model.py")
model = importlib.util.module_from_spec(spec)
spec.loader.exec_module(model)
m = model.m
MASK = (1 << 64) - 1
MASK128 = (1 << 128) - 1


def pair_add(h, l, a, b):
    low = (l + b) & MASK
    return (h + a + (low < l)) & MASK, low


def pair_sub(h, l, a, b):
    return (h - a - (l < b)) & MASK, (l - b) & MASK


def pair_of_shift(value, shift):
    assert 0 <= shift < 64
    return ((value >> (64-shift)) if shift else 0), (value << shift) & MASK


def pair_shift(h, l, shift):
    assert 0 <= shift < 64
    if shift == 0:
        return h, l
    return ((h << shift) | (l >> (64-shift))) & MASK, (l << shift) & MASK


def positive_dot(a, b, qa, qb):
    assert len(a) == len(b)
    ua, ub = [x + qa for x in a], [y + qb for y in b]
    assert all(0 <= x < 2*qa for x in ua)
    assert all(0 <= y < 2*qb for y in ub)
    assert qa.bit_count() == qb.bit_count() == 1
    ea, eb = qa.bit_length()-1, qb.bit_length()-1
    assert ea + eb <= 61
    h = l = 0
    for x, y in zip(ua, ub):
        product = x*y
        assert 0 <= product < 1 << 63
        h, l = pair_add(h, l, 0, product)
    sa, sb = sum(ua), sum(ub)
    assert sa <= MASK and sb <= MASK
    h, l = pair_sub(h, l, *pair_of_shift(sa, eb))
    h, l = pair_sub(h, l, *pair_of_shift(sb, ea))
    h, l = pair_add(h, l, *pair_of_shift(len(a), ea + eb))
    expected = sum(x*y for x, y in zip(a, b))
    assert ((h << 64) | l) == expected & MASK128
    return h, l


def fixtures():
    rng = random.Random(2800336)
    count = 0
    for ea, eb in [(0,0), (1,1), (24,24), (30,31), (39,22), (61,0)]:
        for n in [0,1,2,3,16,31,64,128]:
            if ea == 61 and n > 2:
                continue  # Outside cached UInt64 row-sum premise.
            for _ in range(8):
                a = [rng.randrange(-(1 << ea)+1, 1 << ea) for _ in range(n)]
                b = [rng.randrange(-(1 << eb)+1, 1 << eb) for _ in range(n)]
                positive_dot(a,b,1 << ea,1 << eb)
                count += 1
    for h in [0,1,(1<<63)-1,1<<63,MASK]:
        for l in [0,1,(1<<63)-1,1<<63,MASK]:
            for d in range(64):
                hh,ll=pair_shift(h,l,d)
                assert ((hh<<64)|ll)==(((h<<64)|l)<<d)&MASK128
                count += 1
    # Demonstrates why the positive accumulated body still needs a carry word.
    qa = qb = 1 << 30
    a = b = [qa-1]*8
    raw = sum((x+qa)*(y+qb) for x,y in zip(a,b))
    assert raw >= 1 << 64
    broken = ((raw & MASK) - qb*sum(x+qa for x in a) - qa*sum(y+qb for y in b) + len(a)*qa*qb)
    assert broken != sum(x*y for x,y in zip(a,b))
    # Zero-shift is a distinct branch: shifting by 64 masks to zero in UInt64.
    assert pair_shift(3,5,0)==(3,5)
    # A combined product-width bound alone does not bound a cached row sum.
    assert 128 * (1 << 61) > MASK
    return {"checks": count, "negative_controls": {"drop_positive_carry": True,
             "zero_shift_must_not_use_masked64_formula": True,
             "product_width_alone_does_not_bound_row_sum": {"offset_bits": [61,0], "n": 128, "sum_u": 128*(1<<61)}},
             "repair": "Real preparation additionally requires each offset exponent<=39 and n<2^20, so each cached sum<2^60. Wide synthetic offsets use only safe small n."}


def main():
    stats = collections.Counter()
    stages = []
    original = model.trace_dot
    decisions = []

    def replacement(x,w,bias,meta_x,meta_w):
        old_kind, old_output = original(x,w,bias,meta_x,meta_w)
        if old_output is None:
            stats["old_fallback_macs"] += len(x)
            decisions.append(False)
            return old_kind, old_output
        mx,hx,ex=meta_x;mw,hw,ew=meta_w
        # All-zero metadata has min=510,max=0; choose offset1 for that row.
        ea=24+hx-mx if hx>=mx else 0
        eb=24+hw-mw if hw>=mw else 0
        sb,mb,ib=m.fields(bias)
        lo=min(mx+mw,126+ib) if mb else mx+mw
        d=mx+mw-lo
        if ea+eb>61 or d>=64:
            stats["center_guard_rejected_macs"] += len(x)
            decisions.append(False)
            return old_kind, old_output
        a=[model.prepared_value(v,mx) for v in x]
        b=[model.prepared_value(v,mw) for v in w]
        h,l=positive_dot(a,b,1<<ea,1<<eb)
        h,l=pair_shift(h,l,d)
        signed=(h<<64)|l
        if h>>63:signed-=1<<128
        total=signed+(sb*mb<<(149+ib-lo) if mb else 0)
        output=m.round_ratio(total,1,lo-298)
        assert output==old_output
        stats["center_accepted_dots"] += 1
        decisions.append(True)
        stats["center_accepted_macs"] += len(x)
        stats[f"offset_bit_sum_{ea+eb}_macs"] += len(x)
        return old_kind, old_output

    model.trace_dot = replacement
    original_linear = model.Census.linear

    def capture_linear(self,x,rows,k,out,w,b,relu,stage):
        start=len(decisions)
        result=original_linear(self,x,rows,k,out,w,b,relu,stage)
        local=decisions[start:]
        assert len(local)==rows*out
        if rows>=2 and 0<k<1048576:
            stats['native_extra_prepare_items']+=(rows+out)*k
            for i in range(0,rows-1,2):
                for j in range(out):
                    if local[i*out+j] and local[(i+1)*out+j]:
                        stats['native_pair_accepted_macs']+=2*k
                        stats['native_pair_accepted_calls']+=1
        return result

    model.Census.linear=capture_linear
    original_matrix=model.Census.matrix

    def capture_matrix(self,left,right,relu,stage):
        start=len(decisions)
        result=original_matrix(self,left,right,relu,stage)
        local=decisions[start:]
        n=len(left[0])
        assert len(local)==len(left)*len(right)
        if len(left)>=2 and len(right)>=2 and 0<n<1048576:
            stats['native_gemm_accepted_macs']+=sum(local)*n
            stats['native_gemm_accepted_calls']+=sum(local)
            stats['native_extra_prepare_items']+=(len(left)+len(right))*n
        return result

    model.Census.matrix=capture_matrix
    evidence = fixtures()
    req=json.loads((model.r.E/'fp-word-conv6-26102901-request.json').read_bytes())
    measured=json.loads((model.r.E/'fp-word-conv6-26102901-measurement.json').read_bytes())["result"]
    for workload in req['workloads']:
        for kind in ['normal','wide','sparse']:
            c=model.Census()
            before=stats.copy()
            output=model.r.run_cell('mixer',workload['seed'],workload['profile'],kind,c)
            cell=f"{workload['id']}|mixer:b1:{kind}"
            expected=measured['rounds'][0]['cells'][cell]['candidate_checksum']
            actual=model.r.fnv(output)
            assert actual==expected
            stages.append({'cell':cell,'checksum':actual,'old_native_checksum':expected,'counts':stats-before})
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'EXACT_INTEGER_WORD_FINITE_MODEL_NOT_LEAN_OR_NATIVE',
            'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'fixtures':evidence,'counts':stats,'cells':stages,
            'mechanism':'u=x+Qx,v=w+Qw; dot=sum(u*v)-Qw*sum(u)-Qx*sum(v)+n*Qx*Qw. Nonnegative products permit unsigned128 carry-only loop, followed by three constant shifts and two subtract/add pairs, then one body-scale shift and original exact bias/finish.',
            'limits':['18 old seen batch1 Mixer cells only','Native extra preparation/cache/drop cost UNKNOWN','center_accepted counts include scalar dots; native_pair_accepted counts require both rows in the actual two-row channel-linear consumer','Original exactzero/NaN/infinity/smallK paths must remain fallback','Actual all12 proof absent']}
    (HERE/'centered-dot-model.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'fixtures':evidence,'counts':stats,'cells':len(stages)},indent=2))


if __name__=='__main__':
    main()
