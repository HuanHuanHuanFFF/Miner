"""Finite dense D-domain/ring/forward-and-backward-prefix bounds, no native outcome."""
from pathlib import Path
import ast
import hashlib
import itertools
import json
import random
import re

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'references/round24-public-552/parse.rs'


def main():
    raw=SOURCE.read_bytes()
    assert hashlib.sha256(raw).hexdigest()=='5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
    source=raw.decode();bases=ast.literal_eval(re.search(r'pub const LBASE:.*?=\s*(\[.*?\]);',source,re.S)[1])
    lsym=[0]*512;code=0
    for l in range(259):
        if code<28 and l>=bases[code+1]:code+=1
        lsym[l]=code
    dense_next=[l+1 for l in range(512)]
    assert all(l<dense_next[l]<=512 for l in range(512))
    domains=0
    for flen in (8,16):
        old=[]
        for l in range(512):
            e=l+1
            if not(l<flen or l>=257):
                while e<258 and lsym[e+1]==lsym[l+1]:e+=1
            old.append(e)
        for lo in range(3,259):
            for hi in range(3,259):
                sampled=[];l=lo
                while l<hi:sampled.append(l);l=old[l%512]
                if hi>=lo:sampled.append(hi)
                full=list(range(lo,hi+1))
                assert set(sampled)<=set(full)
                assert all(3<=l<=hi<=258 for l in full)
                domains+=1
    rng=random.Random(2616);ringcases=5000
    for _ in range(ringcases):
        lo,hi=sorted((rng.randrange(3,259),rng.randrange(3,259)))
        start=rng.choice([0,4095,4096,8190,8191,8192,16383,rng.randrange(1<<31)])
        targets=[(start+l)%8192 for l in range(lo,hi+1)]
        assert len(targets)==len(set(targets)) and all(0<=q<8192 for q in targets)
        assert all(start+lo<=start+l<=start+hi for l in range(lo,hi+1))
    backward=0
    for length in range(3,259):
        for t in range(1,min(64,258-length)+1):
            full=list(range(t+3,t+length))
            assert all(3<=l<=length+t<=258 for l in full)
            i=8191;j=i-t
            assert all(i+3<=j+l<=i+length-1 for l in full)
            backward+=1
    byteprefix=0
    for n in range(3,10):
        for symbols in itertools.product(b'ab',repeat=n):
            s=bytes(symbols)
            for p in range(1,n-2):
                for d in range(1,p+1):
                    cap=n-p;hi=0
                    while hi<cap and s[p+hi]==s[p-d+hi]:hi+=1
                    for l in range(3,hi+1):
                        assert s[p:p+l]==s[p-d:p-d+l];byteprefix+=1
    for n in (301,513):
        s=(b'abba'*((n+3)//4))[:n]
        for p in (70,n-258):
            for d in (4,8,32):
                if d<=p:
                    for l in range(3,min(258,n-p)+1):
                        assert s[p:p+l]==s[p-d:p-d+l];byteprefix+=1
    result={'status':'VERIFIED_FINITE_DENSE_DOMAIN_PROGRESS_AND_RING_PREFIX_BOUNDS',
        'all_lo_hi_flen_cases':domains,'dense_table_entries':512,'ring_boundary_cases':ringcases,
        'backward_truncated_domain_cases':backward,'byte_valid_prefix_cases':byteprefix,
        'source_sha256':hashlib.sha256(raw).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'scope':'Fullnew length set contains originalsampled set for lo/hi3..258 andflen8/16. All arrivals remain within originalmatched or backwardextendedprefix/ring window; emptydomains remainempty.',
        'limits':['Finite arithmetic/prefix model, not nativeparser/record equivalence or originalobligation acceptance.',
                  'Candidate expandsgraph; changes to prices/refinement/blockpaths may improve or worsen originalencoder size. No quality/time monotonicity.',
                  'Original directskip/continuation/backwardendpoint logic remains; full only refers to existingrelax_run domains.']}
    path=ROOT/'evidence/round26/route-b/dense-forward-model.json';path.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result))


if __name__=='__main__':main()
