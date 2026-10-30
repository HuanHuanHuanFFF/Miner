from pathlib import Path
import re,json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd();P=ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/evidence/40852769757/download-988ea0459868494bb525e3d8f8795129/fp-word-conv6/Submission.c';raw=P.read_bytes();assert hashlib.sha256(raw).hexdigest()=='103523f22ef030bfa5d3631312b2049665175a08ddb7957a20ed0dbd0846f847';s=raw.decode('utf-8')
rows=[]
for key in ['R24PortableF64_prepare_spec__0','R24ExactDotCost_prepareOperand_spec__0']:
 starts=[m for m in re.finditer(r'(?m)^LEAN_EXPORT[^\n;]+\{',s)if key+'('in m.group()];assert len(starts)==1,key;m=starts[0];pos=m.end()-1;depth=0;quoted=False;escaped=False;end=None
 for j in range(pos,len(s)):
  c=s[j]
  if quoted:
   if escaped:escaped=False
   elif c=='\\':escaped=True
   elif c=='"':quoted=False
  else:
   if c=='"':quoted=True
   elif c=='{':depth+=1
   elif c=='}':
    depth-=1
    if depth==0:end=j+1;break
 assert end is not None;body=s[m.start():end];calls={name:len(re.findall(r'\b'+name+r'\s*\(',body))for name in ['lean_alloc_ctor','lean_is_exclusive','lean_box_float','lean_box_uint64','lean_box_uint32','lean_array_push','lean_float_array_push']}
 rows.append(dict(name=key,signature=m.group()[:-1],start_line=s.count('\n',0,m.start())+1,end_line=s.count('\n',0,end)+1,bytes=len(body.encode()),sha256=hashlib.sha256(body.encode()).hexdigest(),direct_call_sites=calls,tail_goto_start='goto _start;'in body))
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),source_path=P.relative_to(ROOT).as_posix(),source_sha256=hashlib.sha256(raw).hexdigest(),candidate_sha256='ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540',functions=rows,verified_source_type='R24ExactDotCost.Operand.data is Array UInt32, notArray UInt64; line936-941 in historicalKernel.lean',interpretation=['FPfinite preparation normalpath hasconditional constructorreuse, not unconditional perwordstateallocation. The nonfinite branch andfailedexclusivity branches have allocation sites. Dynamic exclusivity frequencies unmeasured.','No direct lean_box_float or lean_box_uint64 call in eitherworker; do not attribute lazygain to removalof UInt64elementboxes. lean_box_uint32 site counts alone are not heapallocation counts.','Eagerduplicate work does include encodedUInt32cache writes, metadata/flags scans andstate/reference management. Actual fractions of completecall time remainUNKNOWN.'],next_if_native_profile_supports='Only after ThinFP cost/profile: inspect its actualRange-based prepare C; if state packing remainsdominant, test direct tail-recursive preparation withseparate UInt32/Bool args. Do not assume ithelps or inherit oldproducerproof without equality.',no_new_native_run=True)
(H/'PREPARATION-C-AUDIT.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');print(json.dumps(r,indent=2))
