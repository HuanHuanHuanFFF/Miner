"""Assemble one complete-call diagnostic with exact B2 prefix. No Lean/CI."""
from pathlib import Path
import ast,datetime,hashlib,json,re
from types import SimpleNamespace
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
OLD=ROOT/'competitions/floatlib/candidates/f01-d7-research/round45m-20261027T074758Z'
H=lambda b:hashlib.sha256(b).hexdigest()

def main():
 out=HERE/'v1';out.mkdir(exist_ok=True)
 basep=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
 gp=OLD/'research/row-broadcast/postfreeze/WideRowRefinement.lean.inc'
 sp=HERE/'StreamingPair.lean.inc';parts=[basep.read_bytes(),gp.read_bytes(),sp.read_bytes()]
 assert H(parts[0])=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
 whole=b'\n\n'.join(parts)
 kernel=out/'Kernel.lean';kernel.write_bytes(whole)
 roots=['Submission.'+op+'_spec' for op in ['add','mul','sum','bmm']]
 for part in parts[1:]:
  stack=[]
  for line in part.decode().splitlines():
   if line.startswith('namespace '):stack.append(line[10:])
   elif line.startswith('end '):stack.pop()
   else:
    m=re.match(r'theorem ([A-Za-z_][A-Za-z0-9_?]*)\b',line)
    if m:roots.append('.'.join(stack+[m[1]]))
  assert not stack
 assert len(roots)==len(set(roots))
 helper=out/'HelperAudit.lean.inc';helper.write_text('\n'.join('#print axioms '+r for r in roots)+'\n',encoding='utf-8',newline='\n')
 gate=ROOT/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/runtime-representation/static-dispatch-frontier/primary/gate-4b7.py'
 assert H(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
 t=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
 for name in ['OPTIONS','ATTRIBUTES','BANNED']:
  n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
  env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
 fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']]
 exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
 checks={'intake':env['intake'](kernel,SimpleNamespace(slot='full')),'policy':env['policy'](kernel,SimpleNamespace(slot='full')),'options':env['options'](whole.decode())}
 assert all(v is None for v in checks.values()),checks
 data={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'COMPLETE_TWO_ROW_CALL_AND_PROOF_ATTEMPT_NOT_RUN',
  'candidate_sha256':H(whole),'kernel_sha256':H(whole),'kernel_bytes':len(whole),'kernel_file':str(kernel),
  'parts':[{'path':str(p),'bytes':len(b),'sha256':H(b)} for p,b in zip([basep,gp,sp],parts)],
  'helper_audit_source':str(helper),'helper_audit_source_sha256':H(helper.read_bytes()),'explicit_helper_audit':True,
  'helper_audit_expected_count':len(roots),'helper_audit_required_endpoints':roots,'helper_audit_module':'Submission',
  'diagnostic_evaluations':[],'static_policy_checks':checks,'statement':'NOT_RUN','kernel_replay':'NOT_RUN','axioms':'NOT_RUN','codegen':'NOT_RUN','performance':'UNKNOWN',
  'public_dispatch':'Exact originalB2, no inheritedofficial336 result for this newsource.',
  'cost_callers':['Submission.R21StreamingPair.controlPair','Submission.R21StreamingPair.streamedPair','Submission.R21StreamingPair.controlRows','Submission.R21StreamingPair.streamedRows'],
  'hot_bodies':['Submission.R21StreamingPair.loop','Submission.R21StreamingPair.advance','Submission.R21StreamingPair.updateCell'],
  'caller_scope':'Complete2rows/arbitraryp, includes output allocation, replicate state, allk, two finish/replay passes, state lifetime; no complete publicBMM route integration.',
  'runtime_choice':'One safeArray.mapIdx whole-state sweep. Callback uses passedcell and capturesa0/a1/Braw/rowB; no oldstate runtimecapture. GenericstorageLoop appears only in proof; dedicatedruntime loop.',
  'prior_modify_draft':'Preserved in preliminary/, never dispatched; not an additionalcandidate or thresholdgrid.',
  'limitations':['Replicateinitial shareszeroCell; firstsweepallocation remains','Constructor reuse/closure0/COWfree are NOT_ESTABLISHED','No actualtimedcaller or allbatch/oddrow publictransport yet'],
  'direct_CI':False,'local_Lean':False}
 (out/'manifest.json').write_text(json.dumps(data,indent=2)+'\n',encoding='utf-8',newline='\n')
 print(json.dumps({k:data[k] for k in ['candidate_sha256','kernel_bytes','helper_audit_expected_count','helper_audit_source_sha256','static_policy_checks']},indent=2))

if __name__=='__main__':main()
