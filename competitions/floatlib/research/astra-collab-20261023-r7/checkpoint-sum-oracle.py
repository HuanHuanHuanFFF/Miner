"""Finite semantics/boundary diagnosis for block checkpoints; not timing or Lean proof."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,itertools,json,random
HERE=Path(__file__).resolve().parent
sp=importlib.util.spec_from_file_location('word_oracle',HERE/'nonfinite-oracle.py');O=importlib.util.module_from_spec(sp);sp.loader.exec_module(O)

def repair_suffix(xs,start,acc,c):
    for k in range(start,len(xs)):
        value=xs[k];v=O.native_model(O.add,acc,value);c['repair_native_steps']+=1
        if not O.nan(v):acc=v;continue
        q=O.add(acc,value);c['exact_events']+=1
        assert O.nan(q) and not O.snan(q)
        for x in xs[k+1:]:
            c['raw_suffix_words']+=1
            if O.snan(x):q=x|0x400000
        return q
    return acc

def checkpoint(xs,K,c):
    assert K>0
    start=0;acc=0
    while start<len(xs):
        assert not O.nan(acc)
        stop=min(len(xs),start+K);assert start<stop
        value=acc
        for x in xs[start:stop]:value=O.native_model(O.add,value,x);c['block_native_steps']+=1
        c['block_checks']+=1
        if not O.nan(value):start=stop;acc=value;continue
        c['fallback_blocks']+=1
        result=repair_suffix(xs,start,acc,c)
        # This source-derived model check is independent of the optimized suffix algorithm.
        exact=acc
        for x in xs[start:]:exact=O.add(exact,x)
        assert result==exact
        return result
    return acc

def main():
    edge=[0,0x80000000,1,0x80000001,0x7fffff,0x800000,0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc12345,0xffc23456,0x7f800001,0xff800002]
    seq=[list(x) for n in range(4) for x in itertools.product(edge,repeat=n)]
    # Every first-event location around representative block boundaries, with later sNaN replacement.
    for n in [0,1,2,3,7,8,9,31,32,33,63,64,65,127,128,129]:
        seq.append([0x3f800000]*n)
        for pos in range(n):
            for word in [0x7fc12345,0xff800002]:
                xs=[0x3f800000]*n;xs[pos]=word
                if pos+1<n:xs[-1]=0x7f800022
                seq.append(xs)
    seq.extend([[0x7f800000]*n+[0xff800000,0xff800011,0x7fc00123,0x7f800022] for n in [0,1,31,32,33,63,64]])
    r=random.Random(2026102304)
    seq.extend([[r.choice(edge) if r.randrange(3)==0 else r.getrandbits(32) for _ in range(n)] for n in [4,16,32,64,128] for _ in range(100)])
    expected=[O.summation(xs) for xs in seq];records=[];trace=hashlib.sha256()
    for K in [1,2,3,8,32,64]:
        c={k:0 for k in ['block_native_steps','block_checks','fallback_blocks','repair_native_steps','exact_events','raw_suffix_words']}
        for xs,e in zip(seq,expected):
            a=checkpoint(xs,K,c);assert a==e,(K,xs,a,e)
            trace.update(K.to_bytes(4,'little')+len(xs).to_bytes(4,'little')+e.to_bytes(4,'little'))
        records.append({'K':K,'cases':len(seq),'counts':c})
    out={'status':'PASS_FINITE_CHECKPOINT_BOUNDARIES','completed_at_utc':datetime.now(timezone.utc).isoformat(),'seed':2026102304,'unique_sequences':len(seq),'checked_sequence_K_pairs':sum(x['cases'] for x in records),'trace_sha256':trace.hexdigest(),'oracle_sha256':hashlib.sha256((HERE/'nonfinite-oracle.py').read_bytes()).hexdigest(),'records':records,'scope':'Correctness/boundary checks across K only, not a performance parameter search. Own exact integer source transcription and canonical native model; no actual Lean/hardware/fullgate claim. Runtime proposed representativeK remains32, with complete real cost UNKNOWN.'}
    (HERE/'checkpoint-sum-oracle.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps({k:v for k,v in out.items() if k!='records'},indent=2))

if __name__=='__main__':main()
