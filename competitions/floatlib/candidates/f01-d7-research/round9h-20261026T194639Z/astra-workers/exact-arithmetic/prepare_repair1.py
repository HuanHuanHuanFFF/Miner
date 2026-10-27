from pathlib import Path
from datetime import datetime,timezone
import json,hashlib,re,difflib,importlib.util,ast
from types import SimpleNamespace
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
O=D/'repair1';O.mkdir(exist_ok=True)
log=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40395429076/download-01d3ee43e7ff4ae088ca57488a71a0b2/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-jam17-probe1/full-build-output.txt'
src=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40395429076/download-01d3ee43e7ff4ae088ca57488a71a0b2/diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r19-dev-jam17-probe1/Kernel.lean'
assert hashlib.sha256(src.read_bytes()).hexdigest()=='f78490eb6a2c2aa7a8b68ebdf54c43d68a39c8bd3bea43e9ee462bcc3cd68679'
errors=[l for l in log.read_text(encoding='utf8').splitlines() if l.startswith('error: work/Submission.lean:')]
assert len(errors)==5 and sum(':6886:' in e for e in errors)==4 and sum(':6945:' in e for e in errors)==1
lexer=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py'
sp=importlib.util.spec_from_file_location('jam_repair_lex',lexer);lex=importlib.util.module_from_spec(sp);sp.loader.exec_module(lex)
def decls(text):
 clean=lex.lex(text)[0];bs=[m.start() for m in lex.CMD.finditer(clean)]+[len(text)]
 out=[]
 for m in lex.DECL.finditer(clean):
  en=next(b for b in bs if b>m.start());piece=text[m.start():en]
  out.append((m['kind'],m['name'],piece,piece.split(':=',1)[0]))
 return out
changes=[('    dsimp only <;>\n    split_ifs <;> omega','    dsimp only <;>\n    simp only [beq_iff_eq] <;>\n    split_ifs <;> omega','Normalize both exact-tie Bool parity conditions before arithmetic splitting.'),('      apply UInt64.toNat.inj\n      simpa only [hm] using h','      apply UInt64.toNat.inj\n      change (p &&& 131071).toNat = 0\n      exact hm.trans h','Normalize the actual UInt64.toNat0 target toNat0; compose the existing exact low-mask equation.')]
rows=[]
for oldname,newname in [('Probe-jam17-v1.lean','Probe-jam17-repair1.lean'),('Kernel-jam17-public-v1.draft.lean','Kernel-jam17-public-repair1.lean'),('Jam17.lean.inc','Jam17-repair1.lean.inc')]:
 old=(D/oldname).read_text(encoding='utf8');new=old
 for a,b,_ in changes:assert new.count(a)==1,(oldname,a);new=new.replace(a,b,1)
 inverse=new
 for a,b,_ in reversed(changes):assert inverse.count(b)==1;inverse=inverse.replace(b,a,1)
 assert inverse==old
 od=decls(old);nd=decls(new)
 assert [(k,n,h) for k,n,p,h in od]==[(k,n,h) for k,n,p,h in nd]
 assert [(k,n,p) for k,n,p,h in od if k not in ('theorem','lemma')]==[(k,n,p) for k,n,p,h in nd if k not in ('theorem','lemma')]
 (O/newname).write_text(new,encoding='utf8',newline='\n')
 patch=''.join(difflib.unified_diff(old.splitlines(keepends=True),new.splitlines(keepends=True),fromfile=oldname,tofile=newname))
 (O/(newname+'.patch')).write_text(patch,encoding='utf8',newline='\n')
 rows.append({'old':oldname,'old_sha256':hashlib.sha256(old.encode()).hexdigest(),'new':newname,'bytes':len(new.encode()),'sha256':hashlib.sha256(new.encode()).hexdigest(),'inverse_exact':True,'all_statement_headers_identical':True,'all_runtime_declarations_identical':True})
for name in ['HelperAudit-jam17.lean.inc','HelperAudit-public-jam17.lean.inc']:(O/name).write_bytes((D/name).read_bytes())
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert hashlib.sha256(gate.read_bytes()).hexdigest()=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t=ast.parse(gate.read_text(encoding='utf8'));env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS','ATTRIBUTES','BANNED']:
 n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
 env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
for row in rows[:2]:
 p=O/row['new'];s=p.read_text(encoding='utf8')
 checks=[env['intake'](p,SimpleNamespace(slot='full')),env['policy'](p,SimpleNamespace(slot='full')),env['options'](s)]
 assert all(c is None for c in checks);row['original_static_gate']='PASS'
manifest={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'FIVE_ACTUAL_ERRORS_PROOF_ONLY_REPAIR_READY_NOT_RUN','run':40395429076,'log':str(log),'log_sha256':hashlib.sha256(log.read_bytes()).hexdigest(),'errors':errors,'changes':[{'old':a,'new':b,'reason':r} for a,b,r in changes],'files':rows,'probe_roots':7,'public_roots':40,'root_lists_byte_identical':True,'runtime_guard_premise_changes':False,'statement':'NOT_RUN','helper_audit':'NOT_RUN','kernel_replay':'NOT_RUN','fullgate':'NOT_RUN','performance':'NOT_RUN'}
(O/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps({'state':manifest['state'],'files':rows,'log_sha256':manifest['log_sha256']},indent=2))
