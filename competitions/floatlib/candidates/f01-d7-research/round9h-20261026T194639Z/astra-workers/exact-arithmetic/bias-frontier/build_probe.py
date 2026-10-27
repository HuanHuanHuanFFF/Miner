from pathlib import Path
from hashlib import sha256
from datetime import datetime,timezone,timedelta
import json,re,ast
from types import SimpleNamespace
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
b=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean';assert sha256(b.read_bytes()).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
paths=[b,D/'Retained-BranchlessRNE-seed.lean.inc',D/'PostBias.lean.inc',D/'Runtime-direct-bias.lean.inc']
embedded=[p.read_bytes().replace(b'\r\n',b'\n') for p in paths]
assert embedded[0]==b.read_bytes()
source=b'\n\n'.join(embedded);out=D/'Probe-direct-bias-v1.lean';out.write_bytes(source)
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec','BranchlessRNESeed.nat_bias','BranchlessRNESeed.nat_grouped_bias','BranchlessRNESeed.word_grouped','BranchlessRNESeed.grouped_eq_existing_rse','R19PostBias.biased_quotient','R19PostBias.biased_bounds','R19PostBias.normalized_quotient','Submission.R19DirectBias.normalCore','Submission.R19DirectBias.guardedMul','Submission.R19DirectBias.diagnosticEntry']
(D/'HelperAudit-direct-bias.lean.inc').write_text('\n'.join('#print axioms '+r for r in roots)+'\n',encoding='utf8',newline='\n')
g=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py';t=ast.parse(g.read_text(encoding='utf8'));e={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
assert sha256(g.read_bytes()).hexdigest()=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
for name in ['OPTIONS','ATTRIBUTES','BANNED']:
 n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets));e[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']];exec(compile(ast.Module(body=fs,type_ignores=[]),str(g),'exec'),e)
checks=[e['intake'](out,SimpleNamespace(slot='full')),e['policy'](out,SimpleNamespace(slot='full')),e['options'](source.decode('utf8'))];assert all(c is None for c in checks)
assert b'\r' not in source and not source.startswith(b'\xef\xbb\xbf')
now=datetime.now(timezone.utc)
stage_start=datetime.fromisoformat('2026-10-26T21:55:27+00:00')
m={'created_utc':now.isoformat(),'state':'MINIMUM_KEY_PROOF_AND_COMPLETE_CALLER_NOT_RUN','file':out.name,'bytes':len(source),'sha256':sha256(source).hexdigest(),'parts':[{'path':str(p.relative_to(R)).replace('\\','/'),'bytes':p.stat().st_size,'sha256':sha256(p.read_bytes()).hexdigest(),'embedded_sha256':sha256(content).hexdigest(),'newline_only_normalized':p.read_bytes()!=content} for p,content in zip(paths,embedded)],'roots':roots,'roots_count':len(roots),'original_static_gate':'PASS','public_runtime':'Allfour publicoperations stillB2; directbias is separate completeguarded diagnosticEntry, notpublicspec orperformance.','caller':'Submission.R19DirectBias.diagnosticEntry','stage_budget_minutes':30,'stage_start_utc':stage_start.isoformat(),'stage_deadline_utc':(stage_start+timedelta(minutes=30)).isoformat(),'statement':'NOT_RUN','kernel_replay':'NOT_RUN','helper_axioms':'NOT_RUN','C_ASM':'NOT_RUN','performance':'NOT_RUN','root_next_action':'D maycompileexactsourceandreplaywholemodule/14roots,theninspectselecteddiagnosticcaller. Main b271 actualfeedback preempts; no changes to frozenJam or heldoutinputs.'}
(D/'probe-manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf8')
print(json.dumps({k:v for k,v in m.items() if k not in ('parts','roots')},indent=2))
