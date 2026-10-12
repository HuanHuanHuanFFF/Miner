"""Finite bit30 field isolation, epoch retention and projected offset checks."""
from pathlib import Path
import hashlib
import json
import random

ROOT=Path(__file__).resolve().parents[1]
TAG=1<<30


def slot(x):
    if x<4:return x
    k=x.bit_length()-1
    return 2*k+((x>>(k-1))&1)


def record(length,distance,fixed=False):
    x=distance-1
    return x|((length-3)<<15)|(slot(x)<<23)|((1<<31) if fixed else 0)


def main():
    bitcases=0
    for distance in range(1,32769):
        for length in (3,258):
            old=record(length,distance)
            assert old&TAG==0 and record(length,distance,True)&TAG==0
            new=old|TAG
            assert ((new>>23)%32)==slot(distance-1)
            assert (((new>>15)&255)+3)==length and (new&32767)+1==distance
            assert new<1<<31 and (new&~TAG)==old
            bitcases+=1
    rng=random.Random(2615)
    epochs=[0]*32;lengths=[0]*32;distances=[0]*32;epochcases=0
    for position in range(10000):
        touched=[];expected={}
        for _ in range(rng.randrange(20)):
            d=rng.randrange(1,32769);l=rng.randrange(3,259);code=slot(d-1)
            if epochs[code]!=position+1:
                epochs[code]=position+1;lengths[code]=l;distances[code]=d;touched.append(code)
            elif l>lengths[code] or (l==lengths[code] and d<distances[code]):
                lengths[code]=l;distances[code]=d
            pair=expected.get(code)
            if pair is None or l>pair[0] or (l==pair[0] and d<pair[1]):expected[code]=(l,d)
        assert len(touched)==len(set(touched))<=30
        assert {code:(lengths[code],distances[code]) for code in touched}==expected
        epochcases+=1
    positions=[];oldflat=[];newflat=[];oldmp=[0];newmp=[0]
    for _ in range(10000):
        rs=[];l=2
        for _ in range(rng.randrange(1,8)):
            l=min(258,l+rng.randrange(1,20));rs.append(record(l,rng.randrange(1,32769)))
            if l==258:break
        extras=[record(rng.randrange(3,l+1),rng.randrange(1,32769))|TAG for _ in range(rng.randrange(5))]
        positions.append((rs,extras));oldflat.extend(rs);newflat.extend(rs+extras);oldmp.append(len(oldflat));newmp.append(len(newflat))
    for i,(rs,extras) in enumerate(positions):
        start,top=newmp[i],newmp[i+1];end=top
        while end>start and newflat[end-1]&TAG:end-=1
        assert newflat[start:end]==oldflat[oldmp[i]:oldmp[i+1]]==rs
        assert newflat[end:top]==extras
    result={'status':'VERIFIED_FINITE_TAG_FIELDS_EPOCH_AND_PROJECTED_GRAPH_MODEL',
        'bitfield_cases':bitcases,'epoch_cases':epochcases,'offset_projection_positions':len(positions),
        'source_boundary':'OriginalCD read precedes tagged append; originalDP excludes tagged suffix before lo/prev/pd/XL/XD. Nativeactualgraph check still required.',
        'limits':['Finite bitfield/retention/offset model, not nativeparent graph equivalence or originalobligation/gate.',
                  'Productiontagged source only uses ordinary already-probed length<=best prefixes; no taggedfixed record or emittedtoken.'],
        'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (ROOT/'evidence/round26/route-b/tagged-record-model.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps(result))


if __name__=='__main__':main()
