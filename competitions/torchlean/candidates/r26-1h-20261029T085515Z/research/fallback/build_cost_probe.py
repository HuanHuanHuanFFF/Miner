from pathlib import Path
import datetime, hashlib, json, sys

HERE=Path(__file__).resolve().parent
OLD=HERE.parents[2]/'r25-90m-20261029T064916Z'/'research'/'integer'
sys.path.insert(0,str(OLD))
import model_span_probe as m

source=(HERE/'WordBlockRuntime.lean').read_text(encoding='utf-8')+'\n'+(HERE/'CostDriver.lean.inc').read_text(encoding='utf-8')
out=HERE/'WordBlockCostMain.lean'
out.write_text(source,encoding='utf-8',newline='\n')
seed=42;r=m.lcg(8,seed^0x5bd1e995)
n=(32+r[0]%67)*8;count=(8+r[1]%25)*8
fixtures=[]
for kind in ('normal','sparse'):
    x=m.gen(kind,n,seed+999);w=m.weights(kind,seed,0,n,n*count);bias=m.biases(seed,1,count)
    expected=[]
    for j in range(count):
        z=m.round_rat(sum(m.rational(a)*m.rational(b) for a,b in zip(x,w[j*n:(j+1)*n]))+m.rational(bias[j]))
        expected.append(0 if z&0x80000000 else z)
    path=HERE/f'word-fixture-{kind}.txt'
    text='\n'.join((str(n),str(count),','.join(map(str,x)),','.join(map(str,w)),','.join(map(str,bias)),','.join(map(str,expected))))+'\n'
    path.write_text(text,encoding='utf-8',newline='\n')
    fixtures.append({'file':path.name,'sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'bytes':path.stat().st_size})
record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'status':'LEAN_NATIVE_DIAGNOSTIC_SOURCE_READY_NOT_COMPILED_OR_RUN',
        'main':out.name,'sha256':hashlib.sha256(out.read_bytes()).hexdigest(),'bytes':out.stat().st_size,
        'fixtures':fixtures,'shape':[n,count],'seed':seed,'public_profile':'typical',
        'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (Path(__file__),HERE/'WordBlockRuntime.lean',HERE/'CostDriver.lean.inc',OLD/'model_span_probe.py',m.SUITE,m.CONTRACT)},
        'boundary':{'prepared':'UInt32 factors + cached maxima/bases ready; body, Int terminal, bias, finishWord, ReLU and output array are timed',
                    'full':'raw UInt32 arrays ready; per-call finite/span scan, UInt32 factor preparation and all prepared work are timed',
                    'outside_timer':'file parsing; output checks/checksum; no source preparation or model output loading'},
        'samples':'11 alternating trials x3 calls per variant; no minimum elapsed-time calibration',
        'limits':['Not official benchmark or full model','No shipped kernel timing in this probe','Fixture domains are seen public seed42 only','No full all-input proof','Array output cleanup may occur after stopping timer; do not call this complete lifecycle cost'],
        'request':'Only run if D main queue has capacity; retain complete compiler output and generated C.'}
(HERE/'cost-probe-receipt.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,indent=2))
