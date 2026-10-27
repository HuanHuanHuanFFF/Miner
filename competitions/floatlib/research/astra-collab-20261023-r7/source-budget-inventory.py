from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re
H=Path(__file__).resolve().parent;R=H.parents[3];C=R/'competitions/floatlib/candidates'
names=['f01-r7-nonnan-runtime','f01-r7-nonfinite-combined-proof2','f01-r7-sum-singlepass-fused-proof1','f01-r7-low-normal-sum-decode','f01-d7-canonical-dot-scan','f01-d7-singleton-native-normalize','f01-d7-scalar-exceptional-word']
rows=[]
for name in names:
 p=C/name/'Kernel.lean';b=p.read_bytes();rows.append({'candidate':name,'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()})
size={x['candidate']:x['bytes'] for x in rows};mincanon=(H/'canonical-image-minimal-block.lean').read_bytes()
scan=(C/'f01-d7-canonical-dot-scan/Kernel.lean').read_bytes();assert mincanon in scan
single_delta=size['f01-r7-sum-singlepass-fused-proof1']-size['f01-r7-nonfinite-combined-proof2']
low_delta=size['f01-r7-low-normal-sum-decode']-size['f01-r7-nonnan-runtime']
projection=size['f01-d7-canonical-dot-scan']+single_delta-len(mincanon)+low_delta
def strip_comments(s):
 out=[];i=0;depth=0
 while i<len(s):
  if s.startswith('/-',i):depth+=1;i+=2
  elif depth and s.startswith('-/',i):depth-=1;i+=2
  elif depth:i+=1
  elif s.startswith('--',i):
   j=s.find('\n',i);i=len(s) if j<0 else j
  else:out.append(s[i]);i+=1
 assert depth==0
 return ''.join(out)
decls=[]
for job,filename,ns in [('R7-W13','R7W13Increment.lean','R7W13'),('R7-W13b','R7W13bIncrement.lean','R7W13b')]:
 p=H/'web'/job/'original-extracted'/job/filename;s=p.read_text();hits=list(re.finditer(r'(?m)^(?:@\[[^\n]+\]\s+)?(?:private\s+)?(theorem|def|abbrev)\s+([A-Za-z_][A-Za-z0-9_\']*)',s))
 for i,m in enumerate(hits):
  body=s[m.start():hits[i+1].start() if i+1<len(hits) else len(s)]
  clean=strip_comments(body);decls.append({'name':ns+'.'+m[2],'short':m[2],'kind':m[1],'source':str(p.relative_to(H)),'approx_span_bytes':len(body.encode()),'tokens':set(re.findall(r'[A-Za-z_][A-Za-z0-9_\']*',clean)),'simp':bool(re.search(r'@\[[^\]]*\bsimp\b',clean))})
byname={x['name']:x for x in decls};shorts={}
for x in decls:shorts.setdefault(x['short'],set()).add(x['name'])
roots={'R7W13b.wrapper_eq_ofBits'}|{x['name'] for x in decls if x['simp']}
keep=set();todo=list(roots)
while todo:
 name=todo.pop()
 if name in keep:continue
 keep.add(name)
 for tok in byname[name]['tokens']:
  for dep in shorts.get(tok,set()):
   if dep not in keep:todo.append(dep)
optional=[{k:x[k] for k in ['name','kind','source','approx_span_bytes']} for x in decls if x['name'] not in keep]
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sizes_exact':rows,'singlepass_additive_delta':single_delta,'lowdecode_additive_delta':low_delta,'D_scan_contains_exact_61d_block_bytes':len(mincanon),'illustrative_scan_single_low_projection_bytes':projection,'illustrative_over_256000':max(0,projection-256000),'projection_status':'INFERRED_PLANNING_ONLY: addexactfiledeltas,removeonecanonicalblock thatsinglepasssupplies. No actualcombinedsource constructed, no claimfunctional/compilable/byte-minimal; furtherseed/scalarcomponents andtheirsharedproofs notaccounted.','low_math_root':'R7W13b.wrapper_eq_ofBits','low_math_declaration_count':len(decls),'lexical_keep_count':len(keep),'potentially_unused_declarations':optional,'approx_optional_span_bytes':sum(x['approx_span_bytes'] for x in optional),'dependency_status':'CONSERVATIVE_SOURCE_SCREEN_NOT_PROOF_TERM_CLOSURE: matchingalllocalshortnames andretainingnew simp declarations; spansmayincludeadjacentcomments/directives. No sourcepruned, no compileracceptance orconcretesavings claimed.','integration_warning':'353d rewires NativeDecodeSum.decode;3d9 exported sum uses explicit R7SinglePassSum.loop/natLoop branches and bypassesNativeDecodeSum. Simply concatenating35decode hook with3d9 wouldnotapplylowdecoder tothenewexportedsum. Anyfuturemerge requiresactualnewloop wiring/proof andfullgate,ownedbyD.'}
(H/'source-budget-inventory.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps({k:v for k,v in out.items() if k not in ['potentially_unused_declarations','candidate_sizes_exact']},indent=2))
