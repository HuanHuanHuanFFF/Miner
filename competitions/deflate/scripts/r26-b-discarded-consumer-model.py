"""Finite novel-source domain, same-code dedup and sparse backward cursor checks."""
from pathlib import Path
import bisect
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]


def main():
    rng = random.Random(2614)
    domains = lengths = cursors = 0
    for _ in range(10000):
        frontier = []
        last = 2
        for _ in range(rng.randrange(1,15)):
            last = min(258,last+rng.randrange(1,25))
            frontier.append((last,rng.randrange(30)))
            if last == 258:
                break
        maxcode = [2]*30
        for length,code in frontier:
            maxcode[code] = max(maxcode[code],length)
        extras = {rng.randrange(30):rng.randrange(3,last+1) for _ in range(rng.randrange(1,20))}
        extras = {code:length for code,length in extras.items() if length>maxcode[code]}
        inherited = (rng.randrange(30),rng.randrange(3,259))
        maxcode[inherited[0]] = max(maxcode[inherited[0]],inherited[1])
        oldprices = [rng.randrange(2049) for _ in range(30)]
        observed = set()
        prev = 2
        for stop,owner in frontier:
            for code,length in extras.items():
                lo = max(prev+1,maxcode[code]+1)
                hi = min(stop,length)
                if oldprices[code] < oldprices[owner]:
                    observed.update((code,x) for x in range(lo,hi+1))
            prev = max(prev,stop)
        expected = set()
        for code,length in extras.items():
            for x in range(3,length+1):
                if x <= maxcode[code]:
                    continue
                owner = next(owner for stop,owner in frontier if stop>=x)
                if oldprices[code] < oldprices[owner]:
                    expected.add((code,x))
        assert observed == expected
        domains += 1
        lengths += len(observed)
    for _ in range(10000):
        n = rng.randrange(1,400)
        positions = sorted(rng.randrange(n) for _ in range(rng.randrange(200)))
        p0 = rng.randrange(n)
        pe = rng.randrange(p0+1,n+1)
        e = bisect.bisect_left(positions,pe)
        groups = {}
        for i in range(pe-1,p0-1,-1):
            b = e
            while b>0 and positions[b-1]==i:
                b -= 1
            groups[i] = positions[b:e]
            e = b
        assert [x for i in range(p0,pe) for x in groups[i]] == [x for x in positions if p0<=x<pe]
        cursors += 1
    result = {'status':'VERIFIED_FINITE_NOVEL_LENGTH_DOMAIN_AND_SPARSE_CURSOR_MODEL',
              'random_frontier_domain_cases':domains, 'novel_cheap_terms_checked':lengths,
              'sparse_cursor_segment_cases':cursors,
              'scope':'Ordinary increasing-length records; original full-prefix samecode availability and inherited samecode availability both removed before strictprice checks. Sparse grouped positions consumed only inside p0..pe.',
              'limits':['Finite source-domain/cursor checks only, no byte-validity, native equivalence, original obligation or encoder outcome.',
                        'This stronger source dedup intentionally excludes short offers reproducible from an original samecode longer prefix even if old DP did not offer that prefix.'],
              'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    path = ROOT/'evidence/round26/route-b/discarded-consumer-model.json'
    path.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps(result))


if __name__=='__main__':
    main()
