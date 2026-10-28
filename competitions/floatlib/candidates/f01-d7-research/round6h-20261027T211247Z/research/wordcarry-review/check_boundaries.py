"""Independent integer endpoint check; not Lean or Float32 validation."""
from pathlib import Path
import hashlib, json
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE.parents[3]
ROUND = HERE.parents[1]
B = 1 << 23
H = 1 << 47
M32 = (1 << 32) - 1

def evaluate(a, b, s, sign):
    p = a * b
    h = p >> 47
    t = p + ((1 << (22+h)) - 1) + ((p >> (23+h)) & 1)
    hp = t >> 47
    q = t >> (23+h)
    qp = t >> (23+hp)
    old = sign | (((s-127+hp) << 23) | (qp-B))
    new = sign | (((s-128+h) << 23) + q)
    assert B*B <= p <= (2*B-1)**2
    assert t < (1 << 48) and hp in (0, 1)
    assert B <= q <= 2*B and B <= qp < 2*B
    assert h == 0 or q <= 2*B-2
    assert old == new and 0 <= new <= M32
    assert (new & 0x7fffffff) < 0x80000000
    return dict(a=a,b=b,S=s,sign=sign,P=p,h=h,T=t,h_post=hp,Q=q,q_post=qp,old=hex(old),new=hex(new))

pairs = {(B,B),(B+1,2*B-2),(2*B-1,2*B-1),(B+1,B+B//2),(B+2,B+B//4)}
for a in [B, B+1, B+2, B+B//4, B+B//2, 2*B-3, 2*B-2, 2*B-1]:
    for b in [B,B+1,2*B-2,2*B-1,H//a-1,H//a,H//a+1]:
        if B <= b < 2*B:
            pairs.add((a,b))
cases = 0
for a,b in sorted(pairs):
    for s in range(128,381):
        for sign in [0,1<<31]:
            evaluate(a,b,s,sign)
            cases += 1
examples = [evaluate(a,b,s,sign) for a,b,s,sign in [
    (B,B,128,0), (B+1,2*B-2,128,0),
    (B+1,B+B//2,128,0), (B+2,B+B//4,128,0),
    (2*B-1,2*B-1,380,0), (2*B-1,2*B-1,380,1<<31)]]
cross = examples[1]
wrong_mask = (((cross['S']-128+cross['h'])<<23) + (cross['Q'] & (B-1)))
assert wrong_mask != int(cross['new'],16)
def receipt(path):
    data = path.read_bytes()
    return dict(path=str(path),bytes=len(data),sha256=hashlib.sha256(data).hexdigest())
report = dict(created_at_utc=datetime.now(timezone.utc).isoformat(),
    status='PAPER_IDENTITY_AND_FINITE_INTEGER_BOUNDARIES_ONLY',
    formal='NOT_RUN', native_cost='UNKNOWN', pairs=len(pairs), sums=253, signs=2,
    cases=cases, examples=examples,
    mutation=dict(kind='mask_Q_to_23_bits_before_add',actual=hex(wrong_mask),expected=cross['new']),
    sources=[receipt(ROUND/'development-wordcarry/Runtime.lean.inc'),
             receipt(CANDIDATES/'f01-r19-dev-direct-bias-public1/Kernel.lean'),
             receipt(HERE/'PAPER-PROOF.md')])
(HERE/'boundary-receipt.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:report[k] for k in ['status','pairs','cases','formal','native_cost']},ensure_ascii=False))
