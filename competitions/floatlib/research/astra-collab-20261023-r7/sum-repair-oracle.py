"""Finite independent integer-word checks of sum repair/last-sNaN; never a Lean proof."""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,itertools,random,hashlib,json
HERE=Path(__file__).resolve().parent
sp=importlib.util.spec_from_file_location('oracle',HERE/'nonfinite-oracle.py');O=importlib.util.module_from_spec(sp);sp.loader.exec_module(O)

def repair(xs,counts):
    acc=0
    for k,x in enumerate(xs):
        native=O.native_model(O.add,acc,x);counts['native_prefix_steps']+=1
        if not O.nan(native):acc=native;continue
        q=O.add(acc,x);counts['exact_repair_steps']+=1
        if O.nan(q) and not O.snan(q):
            for y in xs[k+1:]:
                counts['raw_suffix_words']+=1
                if O.snan(y):q=y | 0x400000
            return q
        for y in xs[k+1:]:q=O.add(q,y);counts['cold_exact_suffix_steps']+=1
        return q
    return acc

def main():
    edge=[0,0x80000000,1,0x80000001,0x7fffff,0x800000,0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc12345,0xffc23456,0x7f800001,0xff800002]
    counts=dict(native_prefix_steps=0,exact_repair_steps=0,raw_suffix_words=0,cold_exact_suffix_steps=0,full_exact_steps=0,cases=0,reverse_snan_hits=0)
    seq=[list(x) for n in range(4) for x in itertools.product(edge,repeat=n)]
    r=random.Random(2026102303)
    seq += [[r.choice(edge) if r.randrange(3)==0 else r.getrandbits(32) for _ in range(n)] for n in [4,16,64,256] for _ in range(500)]
    h=hashlib.sha256()
    for xs in seq:
        expected=O.summation(xs);actual=repair(xs,counts);assert actual==expected
        native=O.summation(xs,lambda a,b:O.native_model(O.add,a,b))
        assert (actual if O.nan(native) else native)==expected
        hit=next((x | 0x400000 for x in reversed(xs) if O.snan(x)),None)
        if hit is not None:assert hit==expected;counts['reverse_snan_hits']+=1
        counts['cases']+=1;counts['full_exact_steps']+=len(xs)
        h.update(len(xs).to_bytes(4,'little')+b''.join(x.to_bytes(4,'little') for x in xs)+expected.to_bytes(4,'little'))
    out=dict(status='PASS_FINITE_SOURCE_DERIVED_WORD_MODEL',completed_at_utc=datetime.now(timezone.utc).isoformat(),seed=2026102303,counts=counts,trace_sha256=h.hexdigest(),oracle_sha256=hashlib.sha256((HERE/'nonfinite-oracle.py').read_bytes()).hexdigest(),scope='Finite exact-integer/source transcription only; native modeled by canonicalized exact operations, not hardware/Lean runtime. Does not replace theorem compilation/replay/fullgate and is not a performance or public-prevalence estimate. Cold exact suffix retained even when these cases never use it.')
    (HERE/'sum-repair-oracle.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))

if __name__=='__main__':main()
