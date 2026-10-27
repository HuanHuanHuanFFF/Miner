from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,importlib.util,random
H=Path(__file__).resolve().parent
sp=importlib.util.spec_from_file_location('o',H/'nonfinite-oracle.py');O=importlib.util.module_from_spec(sp);sp.loader.exec_module(O)
r=random.Random(2026102348);trace=hashlib.sha256();count=0
for e in range(1,24):
 for sign in [0,0x80000000]:
  for f in [0,1,2,3,0x3fffff,0x7ffffe,0x7fffff]+[r.randrange(1<<23) for _ in range(512)]:
   u=sign|(e<<23)|f;shifted=u+0x10000000
   assert shifted<1<<32 and shifted>>31==u>>31 and O.frac(shifted)==f and O.exp(shifted)==e+32
   a=shifted&0x7fffffff;assert 0x0bffffff<=((a-1)&0xffffffff) and a<0x7f800000
   got=O.mul(shifted,0x2f800000);assert got==u
   assert 0<O.exp(got)<255 and 0<O.exp(shifted)<255
   trace.update(u.to_bytes(4,'little')+got.to_bytes(4,'little'));count+=1
counter=[{'u':hex(u),'formula_word':hex(O.mul((u+0x10000000)&0xffffffff,0x2f800000)),'original':hex(u)} for u in [0,0x80000000,1,0x007fffff]]
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'finite_cases':count,'trace_sha256':trace.hexdigest(),'excluded_e0_counterexamples':counter,'scope':'Exactintegerbinary32source-model only. R2 publictable equality for shiftednormalband is priorproofdependency, notexecutedLean/hardwarehere. No performanceorflag/trapclaim. Strongallworddomainproof pendingW13; e0 explicitly excluded.'}
(H/'low-normal-rescale-oracle.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
