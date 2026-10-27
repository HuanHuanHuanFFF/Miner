"""Exact CI404929 proof repair only; frozenv1 and all runtime bodies preserved."""
from pathlib import Path
import ast,datetime,difflib,hashlib,importlib.util,json,re
from types import SimpleNamespace
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=HERE.parent.parent
H=lambda b:hashlib.sha256(b).hexdigest()

def main():
 oldp=HERE/'v1/Kernel.lean';old=oldp.read_text();assert H(oldp.read_bytes())=='5bbff7025deb78192cfcef646707f809487991db3453a1313394b873b6c7b7df'
 diag=ROUND/'ci-runs/40492989029/download-875016b13ca94ebe8cf7635dfb672303/diagnostics/f01-r21-dev-streaming-pair-probe1'
 logp=diag/'full-build-output.txt';log=logp.read_text();errors=[l for l in log.splitlines() if l.startswith('error: work/Submission.lean:')]
 assert len(errors)==1 and ':6777:2:' in errors[0] and 'Tactic `apply` failed' in errors[0]
 before='''  apply RowStream.foldl_inv p (fun acc j => acc.push (read j))
    (fun k acc => acc.size = out.size + k)
  · intro j acc h
    simp only [Array.size_push, h]
    omega
  · omega'''
 after='''  unfold RowStream.emit
  exact RowStream.foldl_inv (β := Array Binary32) p
    (fun (acc : Array Binary32) (j : Fin p) => acc.push (read j))
    (fun k (acc : Array Binary32) => acc.size = out.size + k)
    (by
      intro j acc h
      simp only [Array.size_push, h]
      omega)
    out (by omega)'''
 assert old.count(before)==1
 new=old.replace(before,after,1);assert new.replace(after,before,1)==old
 out=HERE/'v2';out.mkdir(exist_ok=True);kernel=out/'Kernel.lean';kernel.write_text(new,encoding='utf-8',newline='\n')
 frag=(HERE/'StreamingPair.lean.inc').read_text();assert frag.count(before)==1
 (out/'StreamingPair.lean.inc').write_text(frag.replace(before,after,1),encoding='utf-8',newline='\n')
 audit=(HERE/'v1/HelperAudit.lean.inc').read_bytes();(out/'HelperAudit.lean.inc').write_bytes(audit)
 roots=re.findall(r'^#print axioms (\S+)$',audit.decode(),re.M);assert len(roots)==19
 (out/'forward.patch').write_text(''.join(difflib.unified_diff(old.splitlines(True),new.splitlines(True),fromfile='v1/Kernel.lean',tofile='v2/Kernel.lean')),encoding='utf-8',newline='\n')
 (out/'inverse.patch').write_text(''.join(difflib.unified_diff(new.splitlines(True),old.splitlines(True),fromfile='v2/Kernel.lean',tofile='v1/Kernel.lean')),encoding='utf-8',newline='\n')
 lexer=ROOT/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py'
 spec=importlib.util.spec_from_file_location('lexer',lexer);lex=importlib.util.module_from_spec(spec);spec.loader.exec_module(lex)
 def nonproof(s):
  c=lex.lex(s)[0];bounds=[m.start() for m in lex.CMD.finditer(c)]+[len(c)]
  return [(m['kind'],m['name'],c[m.start():next(i for i in bounds if i>m.start())].strip()) for m in lex.DECL.finditer(c) if m['kind'] not in ('theorem','lemma')]
 assert nonproof(old)==nonproof(new)
 gate=ROOT/'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/runtime-representation/static-dispatch-frontier/primary/gate-4b7.py'
 t=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
 for name in ['OPTIONS','ATTRIBUTES','BANNED']:
  n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
  env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
 fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']]
 exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
 checks={'intake':env['intake'](kernel,SimpleNamespace(slot='full')),'policy':env['policy'](kernel,SimpleNamespace(slot='full')),'options':env['options'](new)}
 assert all(x is None for x in checks.values())
 freeze=json.loads((ROUND/'development-streaming-freeze.json').read_text())
 record={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'PROOF_ONLY_REPAIR_FROZEN_NOT_RUN','candidate_file':'Kernel.lean','candidate_sha256':H(kernel.read_bytes()),'kernel_bytes':kernel.stat().st_size,
  'source_producer_path':str(kernel),'parent_sha256':H(oldp.read_bytes()),'proof_changed':'Submission.R21StreamingPair.emit_size body only; explicitunfold,ArrayBinary32 predicate and initialout argument',
  'error_run':40492989029,'error_head':'a9a4053f','error':errors[0],'original_log':str(logp),'original_log_sha256':H(logp.read_bytes()),'inverse_exact':True,'nonproof_declarations_identical':True,'nonproof_declaration_count':len(nonproof(new)),
  'explicit_helper_audit':roots,'helper_audit_expected_count':19,'helper_audit_required_endpoints':roots,'helper_audit_source_sha256':H(kernel.read_bytes()),
  'helper_audit_text_file_sha256':H(audit),'helper_audit_module':freeze['helper_audit_module'],'helper_audit_module_sha256':freeze['helper_audit_module_sha256'],'diagnostic_evaluations':[],
  'static_policy_checks':checks,'statement':'NOT_RUN','kernel_replay':'NOT_RUN','axioms':'NOT_RUN','codegen':'NOT_RUN','performance':'UNKNOWN','runtime_changed':False,'public_algorithms_unchanged':True,'local_Lean':False,'CI_dispatched':False}
 (out/'manifest.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8',newline='\n')
 print(json.dumps({k:record[k] for k in ['candidate_sha256','kernel_bytes','helper_audit_expected_count','helper_audit_text_file_sha256','nonproof_declaration_count','original_log_sha256']},indent=2))

if __name__=='__main__':main()
