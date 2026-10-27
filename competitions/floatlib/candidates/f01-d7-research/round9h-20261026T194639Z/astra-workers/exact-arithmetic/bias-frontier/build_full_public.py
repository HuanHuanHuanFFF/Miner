from pathlib import Path
import re,json,hashlib,difflib,ast,importlib.util
from types import SimpleNamespace
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
H=lambda b:hashlib.sha256(b).hexdigest()
base=(R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert H(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
seed=(D/'Retained-BranchlessRNE-seed.lean.inc').read_text(encoding='utf8')
seed=seed[:seed.index('@[inline] def grouped')].rstrip()+'\n\nend BranchlessRNESeed\n'
(D/'Seed-Nat-closure.lean.inc').write_text(seed,encoding='utf8',newline='\n')
names=['Seed-Nat-closure.lean.inc','PostBias.lean.inc','WordBias.lean.inc',
 'FastMulBoundary.lean.inc','Runtime-direct-bias.lean.inc','TypedOutlet.lean.inc','PublicOutlet.lean.inc']
parts=[(D/n).read_text(encoding='utf8') for n in names]
wrapper='''
namespace Submission
open FloatLib.Floats Competition
@[inline] def add := R19BiasBase.add
theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := R19BiasBase.add_spec
@[inline] def mul (x y : Binary32) : Binary32 := R19BiasBase.R19DirectBias.guardedMul R19BiasBase.mul x y
theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  R19BiasBase.R19DirectBias.guardedMul_spec R19BiasBase.mul R19BiasBase.mul_spec x y
@[inline] def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R19BiasBase.sum x
theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := R19BiasBase.sum_spec
@[inline] def bmm := R19BiasBase.bmm
theorem bmm_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := R19BiasBase.bmm_spec
end Submission
'''
whole='\n\n'.join([base.decode()]+parts).replace('Submission','R19BiasBase')+wrapper
(D/'Kernel-direct-bias-public-unpruned.lean').write_text(whole,encoding='utf8',newline='\n')
# Keep all new theorem roots; only remove unreferenced B2 ordinary theorem leaves.
keep={m.group(1) for p in parts for m in re.finditer(r'^theorem (\w+)\b',p,re.M)}
pruned=whole;removed=[]
base_end=pruned.index('namespace BranchlessRNESeed')
while len(pruned.encode())>255500:
 candidates=[]
 for m in re.finditer(r'^theorem ([A-Za-z_][A-Za-z0-9_\x27?]*)\b',pruned[:base_end],re.M):
  n=m.group(1)
  if n in keep or n.endswith('_spec'):continue
  if len(re.findall(r'(?<![A-Za-z0-9_\x27?])'+re.escape(n)+r'(?![A-Za-z0-9_\x27?])',pruned))!=1:continue
  if pruned[:m.start()].rstrip().split('\n')[-1].lstrip().startswith('@['):continue
  e=re.search(r'^((?:@\[[^\n]*\]\s*)?(?:theorem|def|end|namespace|abbrev|instance|structure)\b|/[-*])',pruned[m.end():],re.M)
  if not e:continue
  end=m.end()+e.start();txt=pruned[m.start():end]
  candidates.append((len(txt.encode()),n,m.start(),end,txt))
 assert candidates,'no safe B2 proof leaves remain'
 sz,n,st,en,txt=max(candidates)
 removed.append({'name':n,'bytes':sz,'text':txt})
 pruned=pruned[:st]+pruned[en:]
 base_end=pruned.index('namespace BranchlessRNESeed')
out=D/'Kernel-direct-bias-public-v1.lean'
out.write_text(pruned,encoding='utf8',newline='\n')
patch=''.join(difflib.unified_diff(whole.splitlines(True),pruned.splitlines(True),fromfile='unpruned',tofile='public-v1'))
(D/'public-source-budget.patch').write_text(patch,encoding='utf8',newline='\n')
replay=whole
for x in removed:assert replay.count(x['text'])==1;replay=replay.replace(x['text'],'',1)
assert replay==pruned
lexer=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py'
spec=importlib.util.spec_from_file_location('source_lexer',lexer)
lex=importlib.util.module_from_spec(spec);spec.loader.exec_module(lex)
def decls(s):
 c=lex.lex(s)[0];bounds=[m.start() for m in lex.CMD.finditer(c)]+[len(c)]
 return [(m['kind'],m['name'],c[m.start():next(i for i in bounds if i>m.start())].strip()) for m in lex.DECL.finditer(c)]
br=[x for x in decls(whole) if x[0] not in ['theorem','lemma']]
ar=[x for x in decls(pruned) if x[0] not in ['theorem','lemma']]
assert br==ar,'non-proof declaration changed'
runtime=(D/'Runtime-direct-bias.lean.inc').read_bytes()
assert H(runtime)=='f3e868424175ddeedf37711d6370afbc3702995e3aa0f3df111d8a0ce86cb2c4'
assert runtime.decode().replace('\r\n','\n').replace('Submission','R19BiasBase') in pruned
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec']
for s in parts:
 stack=[]
 for line in s.splitlines():
  if line.startswith('namespace '):stack.append(line[10:])
  elif line.startswith('end ') and stack:stack.pop()
  else:
   m=re.match(r'theorem (\w+)\b',line)
   if m:roots.append('.'.join(stack+[m.group(1)]).replace('Submission','R19BiasBase'))
roots=list(dict.fromkeys(roots))
(D/'HelperAudit-public-direct-bias.lean.inc').write_text('\n'.join('#print axioms '+r for r in roots)+'\n',encoding='utf8',newline='\n')
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert H(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t=ast.parse(gate.read_text(encoding='utf8'));env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS','ATTRIBUTES','BANNED']:
 n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
 env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
checks={'intake':env['intake'](out,SimpleNamespace(slot='full')),'policy':env['policy'](out,SimpleNamespace(slot='full')),'options':env['options'](pruned)}
assert all(v is None for v in checks.values()),checks
b=out.read_bytes();assert b'\r' not in b and not b.startswith(b'\xef\xbb\xbf')
manifest={'state':'COMPLETE_PUBLIC_PROOF_ATTEMPT_NOT_RUN_HOLD_SEED_PREFIX',
 'file':out.name,'bytes':len(b),'sha256':H(b),'unpruned_bytes':len(whole.encode()),
 'parts':[{'path':n,'bytes':len((D/n).read_bytes()),'sha256':H((D/n).read_bytes())} for n in names],
 'seed_removed':'Only unused grouped/word_grouped/grouped_eq_existing_rse; original quotient_bias/nat_bias/nat_grouped_bias unchanged',
 'removed_B2_ordinary_theorem_leaves':[{'name':x['name'],'bytes':x['bytes']} for x in removed],
 'pruning_runtime_declarations_identical':True,'nonproof_declarations':len(br),'inverse_patch':True,
 'frozen_runtime_unchanged_except_namespace':True,'static_gate':'PASS','roots_count':len(roots),'roots':roots,
 'public_MUL':'Exact frozen guardedDirectBias with original B2 fallback; other public ops B2',
 'statement':'NOT_RUN','kernel_replay':'NOT_RUN','axioms':'NOT_RUN','fullgate':'NOT_RUN','performance':'NOT_RUN',
 'hold':'Original generic quotient proof resource unresolved; ImportOnly->QuotientOnly causal result first. 7b03 not incorporated.'}
(D/'public-v1-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({k:manifest[k] for k in ['state','file','bytes','sha256','unpruned_bytes','roots_count','static_gate','nonproof_declarations']},indent=2))
