from pathlib import Path
import datetime, hashlib, json, sys

HERE=Path(__file__).resolve().parent
sys.path.insert(0,str(HERE))
import replay_words as r
import model_span_probe as m
import band_pair_probe as band

def shift_pair(pair,delta):
    lo,hi=pair
    outlo=(lo<<delta)&r.MASK if delta<64 else 0
    if delta==0: outhi=hi
    elif delta<64: outhi=((hi<<delta)|(lo>>(64-delta)))&r.MASK
    elif delta<128: outhi=(lo<<(delta-64))&r.MASK
    else: outhi=0
    return outlo,outhi

def add_pair(a,b):
    lo=(a[0]+b[0])&r.MASK
    return lo,(a[1]+b[1]+int(lo<a[0]))&r.MASK

seed=42;rr=m.lcg(8,seed^0x5bd1e995)
n=(32+rr[0]%67)*8;outputs=(8+rr[1]%25)*8
x=m.gen('wide',n,seed+999);y=m.weights('wide',seed,0,n,n*outputs)[:n]
bias=m.biases(seed,1,outputs)[0]
base,bands=band.prepare_bands(x,4)
baseB,preparedB=r.align(y)
arr=[];indices=[];starts=[];lengths=[];shifts=[]
for group in bands:
    starts.append(len(arr));lengths.append(len(group['items']));shifts.append(group['base']-base)
    for index,factor in group['items']:
        assert -(1<<31)<=factor<1<<31
        arr.append(factor&0xffffffff);indices.append(index)
assert sorted(indices)==list(range(n))
lo=hi=0;records=[]
for start,length,delta in zip(starts,lengths,shifts):
    a=arr[start:start+length];b=[preparedB[j] for j in indices[start:start+length]]
    assert max(map(r.magn32,a))*max(map(r.magn32,b))<1<<57
    pair=r.blocked(a,b,64)
    exact=sum(r.sx(u,32)*r.sx(v,32) for u,v in zip(a,b))
    assert r.signed128(pair)==exact
    shifted=shift_pair(pair,delta)
    assert shifted[0]+shifted[1]*r.B==(exact<<delta)&r.MASK128
    lo,hi=add_pair((lo,hi),shifted)
    records.append({'length':length,'shift':delta,'nonempty_merges':(length+63)//64,
                    'local_total':str(exact),'pair':list(pair),'shifted':list(shifted)})
body=r.signed128((lo,hi))
sg,mb,ib=m.decode(bias);biasShift=ib+149-base-baseB
assert biasShift>=0
total=body+sg*(mb<<biasShift)
got=m.round_rat(m.Fraction(total)*m.Fraction(2)**(base+baseB-298))
expected=m.round_rat(sum(m.rational(a)*m.rational(b) for a,b in zip(x,y))+m.rational(bias))
assert got==expected
shift_tests=[]
for pair in ((0,0),(r.MASK,r.MASK),(1,0),(r.MASK,1),(0,1<<63)):
    for delta in (0,1,31,63,64,65,127,128,129):
        output=shift_pair(pair,delta)
        want=((pair[0]+pair[1]*r.B)<<delta)&r.MASK128
        assert output[0]+output[1]*r.B==want
        shift_tests.append({'input':list(pair),'delta':delta,'output':list(output)})
source=(HERE/'WordBlockRuntime.lean').read_text(encoding='utf-8')+'\n'+(HERE/'WideBandRuntime.lean.inc').read_text(encoding='utf-8')
(HERE/'WideBandRuntime.lean').write_text(source,encoding='utf-8',newline='\n')
record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'status':'ONE_FIXED_PUBLIC_WIDE_CASE_ACTUAL_INDEXED_WORD_MODEL_NOT_LEAN_OR_TIMING',
        'profile':'typical','seed':42,'output_index':0,'n':n,'width':4,
        'word':got,'reference':expected,'bands':records,
        'total_nonempty_block_merges':sum(v['nonempty_merges'] for v in records),
        'global_shift_adds':len(records),'index_reads':len(indices),
        'actual_storage':'Array UInt32 for factors,indices,starts,lengths,shifts; per-entry physical slot still pointer-sized',
        'shift_boundary_tests':shift_tests,
        'sources':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (Path(__file__),HERE/'WideBandRuntime.lean',HERE/'WideBandRuntime.lean.inc',HERE/'WordBlockRuntime.lean')},
        'missing':['Lean compile','band partition/getter proof','shift128 modular theorem','global128-bound guard','native grouping/gather cost','whole model']} 
(HERE/'wide-fixed-case.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:record[k] for k in ('word','reference','total_nonempty_block_merges','global_shift_adds','index_reads')},indent=2))
