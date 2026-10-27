from pathlib import Path
from types import SimpleNamespace
import re,json,hashlib,difflib,ast,importlib.util
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
I=D/'public-proof-review1';O=D/'public-resource1-conditional';O.mkdir(exist_ok=True)
H=lambda b:hashlib.sha256(b).hexdigest()
old7=(D/'Probe-direct-bias-resource1.lean').read_text(encoding='utf8')
assert H((D/'Probe-direct-bias-resource1.lean').read_bytes())=='7b0371161a56940568a15a1af3c8db8d11dec4a429ea83c84bc7a31f4ef3d558'
new=old7[old7.index('private theorem remainder_bias'):old7.index('theorem nat_bias',old7.index('private theorem remainder_bias'))]
assert new==(D/'Restricted-quotient-bias.lean.inc').read_text(encoding='utf8').rstrip()+'\n\n'
lexer=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py'
sp=importlib.util.spec_from_file_location('source_lexer',lexer);lex=importlib.util.module_from_spec(sp);sp.loader.exec_module(lex)
def decls(s):
 c=lex.lex(s)[0];bounds=[m.start() for m in lex.CMD.finditer(c)]+[len(c)];out=[]
 for m in lex.DECL.finditer(c):
  e=next(x for x in bounds if x>m.start());p=c[m.start():e].strip()
  out.append((m['kind'],m['name'],m['modifier'],p,p.split(':=',1)[0]))
 return out
rows=[]
for n in ['Kernel-direct-bias-public-v1.lean','MathOutlet-interface-v1.lean']:
 s=(I/n).read_text(encoding='utf8');st=s.index('private theorem quotient_bias');en=s.index('theorem nat_bias',st);old=s[st:en]
 t=s[:st]+new+s[en:];assert t.replace(new,old,1)==s
 a,b=decls(s),decls(t)
 assert [(k,n,p) for k,n,m,p,h in a if k not in ['theorem','lemma']]==[(k,n,p) for k,n,m,p,h in b if k not in ['theorem','lemma']]
 assert [(k,n,h) for k,n,m,p,h in a if 'private' not in m]==[(k,n,h) for k,n,m,p,h in b if 'private' not in m]
 p=O/n;p.write_text(t,encoding='utf8',newline='\n')
 (O/(n+'.patch')).write_text(''.join(difflib.unified_diff(s.splitlines(True),t.splitlines(True),fromfile='review1/'+n,tofile='conditional-resource1/'+n)),encoding='utf8',newline='\n')
 rows.append({'file':n,'base_sha256':H((I/n).read_bytes()),'bytes':len(p.read_bytes()),'sha256':H(p.read_bytes()),'delta_bytes':len(t.encode())-len(s.encode())})
for n in ['HelperAudit-public-direct-bias.lean.inc','HelperAudit-math-outlet.lean.inc']:(O/n).write_bytes((I/n).read_bytes())
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert H(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
g=ast.parse(gate.read_text(encoding='utf8'));env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS','ATTRIBUTES','BANNED']:
 v=next(x for x in g.body if isinstance(x,ast.Assign) and any(isinstance(y,ast.Name) and y.id==name for y in x.targets));env[name]=re.compile(ast.literal_eval(v.value.args[0])) if name=='BANNED' else ast.literal_eval(v.value)
fs=[x for x in g.body if isinstance(x,ast.FunctionDef) and x.name in ['intake','policy','options']];exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
p=O/rows[0]['file'];checks=[env['intake'](p,SimpleNamespace(slot='full')),env['policy'](p,SimpleNamespace(slot='full')),env['options'](p.read_text(encoding='utf8'))];assert all(x is None for x in checks),checks
manifest={'state':'CONDITIONAL_HOLD_NOT_RUN','activation_condition':'ImportOnly exits0 and exact original QuotientOnly has verified target-scope OOM; R/D decides activation, not merely batchfailure or exit-15.',
 'rows':rows,'proof_provenance':'Exact private remainder_bias/quotient_bias block from 7b03, no further rewrite',
 'runtime_declarations_identical':True,'public_headers_identical':True,'guards_and_public_assumptions_unchanged':True,
 'audit_roots_count':48,'audit_files_identical':True,'inverse_patch_exact':True,'original_static_gate':'PASS',
 'statement':'NOT_RUN','axioms':'NOT_RUN','replay':'NOT_RUN','performance':'NOT_RUN','old7b03':'Still HOLD, not claimed fixed',
 'mathematical_scope':'Only private half parameter restricted to2^22/2^23; original nat_bias literal23/24 branch calls retain by decide certificates, no public input assumption added'}
(O/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8',newline='\n')
(O/'HANDOFF.md').write_text(f'''# Conditional resource1：精确私有证明迁移，HOLD

完整源 {rows[0]['bytes']} B / {rows[0]['sha256']}；B2-import数学模块 {rows[1]['bytes']} B / {rows[1]['sha256']}。文件名见manifest；均只比review1增加11 B。

仅将原7b03的private remainder_bias/quotient_bias块逐字迁移。private half限制2^22/2^23，现有nat_bias的23/24分支仍以by decide给出真实条件；全部非private声明头、运行定义、guards、公开假设、48根不变，逆patch精确。完整源原intake/policy/options PASS且≤256000；没有用改算法压字节。

**放行条件**：ImportOnly独立进程退出0，原QuotientOnly有目标scope的OOM证据，再由R/D放行。不能以batch failure、-15或历史空日志代替；若import失败或quotient普通证明错误，先处理该实际反馈。当前编译/重放/公理/性能全NOT_RUN，不排队，不改原7b03 HOLD状态。review1/fa6529及原v1保留。
''',encoding='utf8',newline='\n')
print(json.dumps(manifest,indent=2))
