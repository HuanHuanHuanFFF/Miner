from pathlib import Path
from hashlib import sha256
from datetime import datetime,timezone
from types import SimpleNamespace
import re,json,ast,difflib,importlib.util
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40410895344';idx=json.loads((run/'original-artifact-hashes.json').read_bytes());base=run/idx['directory']
pre=base/'diagnostics/f01-d7-public-suite/public-suite'
inp=pre/'inputs/f01-r19-dev-direct-bias-probe1/Kernel.lean';log=pre/'diagnostics/f01-r19-dev-direct-bias-probe1/full-build-output.txt';replay=log.parent/'replay.log'
assert sha256(inp.read_bytes()).hexdigest()=='1180c82c69ded5619978a2673f47ce9ed6d94a80930099429fc0b7cd5b0044bd'
assert inp.read_bytes()==(D/'Probe-direct-bias-v1.lean').read_bytes()
assert log.read_bytes()==b'\n' and 'exit=-15 in 31.3s' in replay.read_text()
for p in [inp,log,replay,pre/'f01-r19-dev-direct-bias-probe1-verdict.json']:
 rel=p.relative_to(base).as_posix();m=idx['files'][rel];assert p.stat().st_size==m['bytes'] and sha256(p.read_bytes()).hexdigest()==m['sha256']
old=inp.read_text(encoding='utf8');start=old.index('private theorem quotient_bias');end=old.index('theorem nat_bias',start)
before=old[start:end];after=(D/'Restricted-quotient-bias.lean.inc').read_text(encoding='utf8').rstrip()+'\n\n'
new=old[:start]+after+old[end:];assert new.replace(after,before,1)==old
sp=importlib.util.spec_from_file_location('lexresource',R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py');lex=importlib.util.module_from_spec(sp);sp.loader.exec_module(lex)
def decls(s):
 clean=lex.lex(s)[0];bounds=[m.start() for m in lex.CMD.finditer(clean)]+[len(s)];rows=[]
 for m in lex.DECL.finditer(clean):
  e=next(b for b in bounds if b>m.start());piece=s[m.start():e];rows.append((m['kind'],m['name'],m['modifier'],piece,piece.split(':=',1)[0]))
 return rows
od,nd=decls(old),decls(new)
assert [(k,n,p) for k,n,m,p,h in od if k not in ('theorem','lemma')]==[(k,n,p) for k,n,m,p,h in nd if k not in ('theorem','lemma')]
assert [(k,n,h) for k,n,m,p,h in od if 'private' not in m]==[(k,n,h) for k,n,m,p,h in nd if 'private' not in m]
out=D/'Probe-direct-bias-resource1.lean';out.write_text(new,encoding='utf8',newline='\n')
(D/'proof-resource1.patch').write_text(''.join(difflib.unified_diff(old.splitlines(keepends=True),new.splitlines(keepends=True),fromfile='1180',tofile=out.name)),encoding='utf8',newline='\n')
g=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py';t=ast.parse(g.read_text(encoding='utf8'));env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
assert sha256(g.read_bytes()).hexdigest()=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
for name in ['OPTIONS','ATTRIBUTES','BANNED']:
 n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets));env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']];exec(compile(ast.Module(body=fs,type_ignores=[]),str(g),'exec'),env)
assert all(x is None for x in [env['intake'](out,SimpleNamespace(slot='full')),env['policy'](out,SimpleNamespace(slot='full')),env['options'](new)])
manifest={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'PROOF_RESOURCE_DISCRIMINATOR_NOT_VERIFIED_FIX','file':out.name,'bytes':len(new.encode()),'sha256':sha256(new.encode()).hexdigest(),'base_sha256':sha256(inp.read_bytes()).hexdigest(),'failed_run':40410895344,'failed_input_bound':True,'observed_failure':'VerifyFullSIGTERM-15/31.3s;1byteLF;noLeanerror','old_failure_cause':'UNKNOWN','changes':'Replace onlyprivate genericquotient proof by literalhalf domain with separateq/r remainder lemma; no originalp/division inthat arithmetic subproof. Calls at2^22/2^23 proveconditions bydecide.','public_declaration_headers_identical':True,'runtime_definitions_identical':True,'inverse_exact':True,'roots':'Same14 HelperAudit-direct-bias.lean.inc unchanged','original_static_gate':'PASS','proof_compilation':'NOT_RUN','replay':'NOT_RUN','ASM':'NOT_RUN','performance':'NOT_RUN','limitations':'Not a confirmed bugfix or mathematical counterexample. Proofperformance hypothesis only. Keep original caps/gate/compilerflags; if repeatedtermination collect targetscopeRSS/events/progress before furtherrewrites.'}
(D/'resource1-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps(manifest,indent=2))
