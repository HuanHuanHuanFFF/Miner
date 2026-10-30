from pathlib import Path
import datetime
import hashlib
import json
import math
import random

HERE = Path(__file__).resolve().parent
B, M = 1 << 64, 1 << 32


def uint32_of_float(x):
    if math.isnan(x) or x <= 0:
        return 0
    if x >= M-1:
        return M-1
    return int(x)


def proposal_path(a,d,inv):
    if d >= M:
        return divmod(a,d), 'wide'
    q = uint32_of_float(float(a)*inv)
    for x,label in ((q,'first'),((q+1)%(M),'plus_one'),((q-1)%M,'minus_one')):
        p=x*d
        assert p < B
        if p<=a and a-p<d:
            return (x,a-p),label
    return (divmod(a,d) if d else (0,a)),'fallback'


def main():
    rng=random.Random(27102947)
    counts={x:0 for x in ('first','plus_one','minus_one','fallback','wide')}
    for _ in range(50000):
        d=rng.randrange(1,M)
        q=rng.randrange(M)
        a=q*d+rng.randrange(d)
        got,branch=proposal_path(a,d,1.0/float(d))
        assert got==divmod(a,d)
        counts[branch]+=1
    arbitrary=0
    cache_records=[]
    invs=[0.0,1.0,-1.0,math.inf,-math.inf,math.nan,1e-300,1e300]
    for a in [0,1,M-1,M,M+1,1<<63,B-1]:
        for d in [0,1,2,3,1<<23,M-1,M,1<<63,B-1]:
            oracle=divmod(a,d) if d else (0,a)
            for inv in invs:
                got,branch=proposal_path(a,d,inv)
                assert got==oracle
                arbitrary+=1
            if 0<d<M:
                right=proposal_path(a,d,1.0/float(d))[1]
                wrong=proposal_path(a,d,0.0)[1]
                cache_records.append(dict(a=a,d=d,correct_reciprocal_branch=right,
                                          zero_reciprocal_branch=wrong,outputs_equal=True))
    p=HERE/'CheckedFloatDivision.lean'
    record=dict(at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                classification='FINITE_LITERAL_UINT32_PROPOSAL_CERTIFICATE_MODEL_NOT_LEAN_OR_NATIVE',
                random_seed=27102947,small_quotient_cases=50000,branches=counts,
                arbitrary_float_directed_cases=arbitrary,wrong_cache_controls=cache_records,
                source_hashes={q.name:hashlib.sha256(q.read_bytes()).hexdigest() for q in [Path(__file__),p]},
                boundary='Neighbors wrap asUInt32; denominatorwide skipsbeforetruncation; binary64proposalclampsasFloat.toUInt32. Arbitraryreciprocal changesbranchcost only, neveracceptedquotientvalidity.',
                missing=['PinnedLeanacceptance','NativeFPconversion/constructorcost','Actualrowcachehit/fallbackinstrumentation','Full12gate/currentchampionmeasurement'])
    (HERE/'checked-division-u32-model.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(dict(branches=counts,arbitrary_float_directed_cases=arbitrary),indent=2))


if __name__=='__main__':
    main()
