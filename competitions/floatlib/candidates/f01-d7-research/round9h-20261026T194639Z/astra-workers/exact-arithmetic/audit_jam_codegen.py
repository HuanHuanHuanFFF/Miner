from pathlib import Path
from hashlib import sha256
from datetime import datetime,timezone
import re,json,collections
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40404258098'
idx=json.loads((run/'original-artifact-hashes.json').read_bytes());base=run/idx['directory']
diag=base/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-jam17-public1'
expected='b2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff'
def bind(p):
 rel=str(p.relative_to(base)).replace('\\','/');m=idx['files'][rel];b=p.read_bytes()
 assert len(b)==m['bytes'] and sha256(b).hexdigest()==m['sha256']
 return {'path':str(p.relative_to(R)).replace('\\','/'),'bytes':len(b),'sha256':m['sha256']}
cp=diag/'candidate-generated-1.c';ap=diag/'native-loop-8.asm.txt';ip=diag/'native-assembly-index.json'
bindings=[bind(p) for p in [cp,ap,ip]]
c=cp.read_text(encoding='utf8');a=ap.read_text(encoding='utf8');asmidx=json.loads(ip.read_bytes())
row=next(r for r in asmidx if r.get('file')==ap.name)
assert row['kernel_sha256']==expected and row['symbol']=='lp_competition_main___lam__3' and row['exit_code']==0
assert '.m_data = "BENCH_PLAN"' in c
assert '.m_fun = (void*)lp_competition_main___lam__3___boxed' in c
assert 'v___f_3393_ = ((lean_object*)(lp_competition_main___closed__5));' in c
assert 'lp_competition_Bench_Suite_run(v___f_3392_, v___f_3393_,' in c
assert 'v_res_3376_ = lp_competition_main___lam__3(' in c
instructions=[]
for line in a.splitlines():
 m=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)',line)
 if m:instructions.append({'offset':int(m[1],16),'op':m[2],'args':m[3],'raw':line})
segments=[(0,0x2d),(0x74,0x86),(0x266,0x272),(0x45b,0x4cf),(0xb59,0xb65)]
path=[x for lo,hi in segments for x in instructions if lo<=x['offset']<=hi]
arm=[x for x in instructions if 0x45b<=x['offset']<=0x4cf]
assert next(x for x in instructions if x['offset']==0x272)['args'].startswith('45b ')
assert next(x for x in arm if x['offset']==0x4cf)['args'].startswith('b59 ')
counts=collections.Counter(x['op'] for x in arm)
assert counts['imul']==1 and counts['cvtsi2ss']==1 and counts['cvttss2si']==1
assert counts['subss']==0 and counts['sar']==0 and counts['call']==0
assert not any('rsp' in x['args'] or 'rbp+' in x['args'] for x in arm)
assert counts['setne']==1 and counts['test']==1 and counts['cmova']==1 and counts['ucomiss']==1
O=D/'codegen-404042';O.mkdir(exist_ok=True)
(O/'accepted-public-path.asm.txt').write_text('\n'.join(x['raw'] for x in path)+'\n',encoding='utf8')
clines=c.splitlines();ranges=[(63,80),(5875,5932),(10584,10612)]
(O/'selected-C-excerpts.txt').write_text('\n'.join(f'{i+1}:{clines[i]}' for lo,hi in ranges for i in range(lo-1,hi))+'\n',encoding='utf8')
out={'created_utc':datetime.now(timezone.utc).isoformat(),'status':'VERIFIED_ACTUAL_PUBLIC_CALLER_DIAGNOSTIC_ASM','run':40404258098,'kernel_sha256':expected,'bindings':bindings,'selected_call_chain':'BENCH_PLAN present: closed__5 -> main___lam__3___boxed -> main___lam__3','selected_C_lines':ranges,'actual_object_sha256_reported':row['object_sha256'],'raw_object_available_for_rehash':False,'path_segments_inclusive':[[hex(l),hex(h)] for l,h in segments],'arithmetic_arm_instruction_positions':len(arm),'arithmetic_arm_counts':dict(counts),'whole_accepted_path_instruction_positions':len(path),'shared_prologue':{'callee_saved_pushes':sum(x['op']=='push' for x in path),'callee_saved_pops':sum(x['op']=='pop' for x in path),'frame_bytes':16},'verified_changes_vs_R18_unsigned_diagnostic':'One signed32 forwardcvtsi2ss; one reversecvttss2si. R18secondreverse/subss/sar/ANDmerge absent. Sticky Cif loweredto test/setne/OR. No fastarmcall orstackspill.','remaining_cost':'Upperlimit movss/ucomiss/UINT32MAX/cmova selection; normal/exsum guards;5push/pop and16B sharedframe.','constant_limit_value':'2^32 INFERRED fromfixedUInt32 primitive; RIPconstantpoolbytes notincluded.','cost_comparison_boundary':'OldR18was diagnosticEntry of876; newb271 is actual selectedpublicMainFull but still a statement/bench-build diagnostic object, not the cleanedtimedgateobject. No cycle/fullspeed gain claimed.','next':'Complete original uninstrumentedfullgate/25roundD on exactb271; keep sourcefrozen. No extra signmask variant: forward already uses signed32 conversion.'}
(O/'audit.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps({k:v for k,v in out.items() if k not in ['bindings','arithmetic_arm_counts']},indent=2))
