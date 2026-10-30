from pathlib import Path
import json,hashlib,re,ast,types,sys
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd();E=ROOT/'competitions/torchlean/candidates/r27-5h-20261029T194443Z/evidence/40948208583/download-12f49c520f4a40649df4b418915e9e2b'
d=json.loads((E/'summary.json').read_bytes());entry=next(x for x in d['helper_diagnostics'] if x['name']=='real_strict_v1');assert entry['exit_code']==0
p=H/'sources-v1/RealStrictContractOnly.lean';assert hashlib.sha256(p.read_bytes()).hexdigest()==entry['source_sha256']
log=(E/'real_strict_v1-helper.log').read_bytes();s=log.decode();assert ': error:'not in s
roots=re.findall(r"'([^']+)' depends on axioms: \[([^\]]*)\]",s);expected=['raw_value','magnitudeReal_strictMono','orderKey_lt_real','native_ofBits','orderKey_native_endpoints'];assert [x[0]for x in roots]==['Submission.R25OrderKey.'+n for n in expected];assert all(set(v.strip()for v in ax.split(','))<={'propext','Classical.choice','Quot.sound'}for _,ax in roots)
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),run_id=d['run_id'],source_commit=d['source_commit'],finished_at_utc=d['finished_at_utc'],source_path=p.relative_to(ROOT).as_posix(),source_sha256=entry['source_sha256'],log_path=(E/'real_strict_v1-helper.log').relative_to(ROOT).as_posix(),log_sha256=hashlib.sha256(log).hexdigest(),log_bytes=len(log),exit_code=0,roots=roots,allowed_only=True,scope='EXACT_STANDALONE_HELPER_ELABORATION_AND_ALLOWED_AXIOMS',full_original_gate=False,independent_kernel_replay=False)
(H/'batch2-proof-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
P=ROOT/'competitions/torchlean/candidates/r25-90m-20261029T064916Z/development/contract-port/policy-source';dup={};exec(compile((P/'duplicates.py').read_text(encoding='utf-8'),'pinned_duplicates','exec'),dup)
t=ast.parse((P/'sandbox.py').read_text(encoding='utf-8'));names={'_MAX_BYTES','OPTIONS','ATTRIBUTES','BANNED','GLOBAL'};funcs={'intake','policy','global_declarations','options'};sel=[n for n in t.body if(isinstance(n,ast.Assign)and any(isinstance(x,ast.Name)and x.id in names for x in n.targets))or(isinstance(n,ast.FunctionDef)and n.name in funcs)];ns={'Path':Path,'Verdict':object,'re':re,'normalized':dup['normalized']};exec(compile(ast.Module(body=sel,type_ignores=[]),'pinned_policy','exec'),ns)
class BytesSource:
 def __init__(self,b):self.b=b
 def is_file(self):return True
 def stat(self):return types.SimpleNamespace(st_size=len(self.b))
 def read_bytes(self):return self.b
 def read_text(self):return self.b.decode('utf-8')
sys.dont_write_bytecode=True;sys.path.insert(0,str(H/'census'));from patch_lazy_prepare import transform
raw=(ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/development/native/fp-word-conv6-local/Kernel.lean').read_bytes();base=transform(raw);withproof=base+b'\n'+(H/'census/LazyScalarEquivalence.lean.inc').read_text(encoding='utf-8-sig').encode('utf-8')
checks=[]
for name,b in [('runtime_only',base),('relative_scalar_proof',withproof)]:
 v=BytesSource(b);a=ns['intake'](v,None);c=ns['policy'](v,None);assert a is None and c is None;checks.append(dict(name=name,sha256=hashlib.sha256(b).hexdigest(),bytes=len(b),intake=a,policy=c,scope='Original static functions on exact reconstructed bytes in memory; no physicalKernel written, no Lean/native'))
(H/'census/lazy-static-policy.json').write_text(json.dumps(dict(at_utc=datetime.now(timezone.utc).isoformat(),checks=checks),indent=2)+'\n',encoding='utf-8')
p=H/'CI-REQUEST.json';q=json.loads(p.read_bytes());q.update(updated_at_utc=datetime.now(timezone.utc).isoformat(),state='READY_ACTUAL_CHECKER_REAL_PREFIX_ACCEPTED',batch2_result='RealStrict e004d3d7 exit0,5roots allowed-only; do not repeat unchangedReal standalone',priority='Actual guarded checker36.6KB + repairedPrepareCore/Peak next; numerical6blocks independent; optional lazy completecall native discriminator now supported by108exactoldcohort outputhashes.');p.write_text(json.dumps(q,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
p=H/'status.json';q=json.loads(p.read_bytes());q.update(updated_at_utc=datetime.now(timezone.utc).isoformat(),state='ACTIVE_CORE_AND_REAL_ACCEPTED',verification='key4e1ed0b4 fourroots + RealStrict e004d3d7 fiveroots standaloneelaboration/allowedAX PASS; actualchecker/producer/rounder/all12 NOT_RUN',active_work='Next actualchecker and prepare fixes; oldcohort FPacceptance99.7773percent supports lazywordprepare costexperiment; nativegainUNKNOWN.');p.write_text(json.dumps(q,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
p=H/'HANDOFF.md';s=p.read_text(encoding='utf-8').replace('20:36 UTC；','20:40 UTC；').replace('- **新实质归约**：','- **Real已接受**：batch2 40948208583 /bfee4263，e004d3d7五根elaboration＋allowedAX PASS；回执`batch2-proof-receipt.json`，实际checker和producer仍未接受。\n- **新实质归约**：').replace('仅key四根获本轮Lean/allowedAX接受','key四根＋Real五根获本轮Lean/allowedAX接受');p.write_text(s,encoding='utf-8')
print(json.dumps({'real_proof':r,'lazy_static':checks},indent=2))
