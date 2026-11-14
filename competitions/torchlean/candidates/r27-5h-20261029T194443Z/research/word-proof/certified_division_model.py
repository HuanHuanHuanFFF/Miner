from pathlib import Path
import datetime
import hashlib
import json
import random

HERE = Path(__file__).resolve().parent
B = 1 << 64
M = 1 << 32
MASK = B - 1


def accept(a, d, q):
    p = (q*d) & MASK
    r = (a-p) & MASK
    return d != 0 and d < M and q < M and p <= a and r < d


def from_proposal(a, d, q):
    for candidate in (q, (q+1)&MASK, (q-1)&MASK):
        if accept(a,d,candidate):
            return (candidate, a-candidate*d), candidate-q
    return (divmod(a,d) if d else (0,a)), None


def main():
    rng = random.Random(27102943)
    counts = dict(cases=0, first=0, plus_one=0, minus_one=0, fallback=0)
    cases = []
    for d in [1,2,3,7,8,255,256,(1<<23)-1,1<<23,(1<<31)-1,1<<31,M-2,M-1]:
        for q in [0,1,2,255,256,(1<<24)-1,1<<24,(1<<31)-1,M-2,M-1]:
            for r in sorted({0,1,d//2,max(0,d-1)}):
                if r < d and q*d+r < B:
                    cases.append((q*d+r,d))
    for _ in range(50000):
        d = rng.randrange(1,M)
        q = rng.randrange(M)
        r = rng.randrange(d)
        cases.append((q*d+r,d))
    for a,d in cases:
        reciprocal = 1.0 / float(d)
        proposal = min(MASK,max(0,int(float(a)*reciprocal)))
        got, branch = from_proposal(a,d,proposal)
        assert got == divmod(a,d)
        counts['cases'] += 1
        counts['first' if branch == 0 else 'plus_one' if branch == 1 else
               'minus_one' if branch == -1 else 'fallback'] += 1
    # Arbitrary bad proposals must never affect exactness.
    for _ in range(10000):
        a,d,q = (rng.randrange(B) for _ in range(3))
        got,_ = from_proposal(a,d,q)
        assert got == (divmod(a,d) if d else (0,a))
    negatives=[]
    for a,d,q in [(0,1<<31,1<<33),(0,1<<63,2)]:
        p=(q*d)&MASK
        naive = d!=0 and p<=a and ((a-p)&MASK)<d
        assert naive and q != a//d and not accept(a,d,q)
        negatives.append(dict(a=a,d=d,q=q,wrapped_product=p,
                              unchecked_certificate_accepts=naive,checked_rejects=True))
    report=dict(at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                status='FINITE_BINARY64_PROPOSAL_AND_EXACT_INTEGER_CERTIFICATE_MODEL_ONLY',
                source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
                seed=27102943,counts=counts,arbitrary_proposal_cases=10000,
                wrap_negative_controls=negatives,
                mechanism='Perrow binary64reciprocal, one mul/conversion proposal, exact32x32-product certificate; try neighboringq, otherwise originalworddivrem.',
                soundness_boundary='No assumption about floatingproposal is needed if actualcertificate is proved. Both q<2^32 and0<d<2^32 are essential to this simple no-wrap proof.',
                missing=['PinnedLeancompile','actualkernelintegration','actualnative hit/fallback andcompletecallcost','all12gate','currentchampionperformance'])
    (HERE/'certified-division-model.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(dict(counts=counts,arbitrary_proposal_cases=10000),indent=2))


if __name__ == '__main__':
    main()
