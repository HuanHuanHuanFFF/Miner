from pathlib import Path
from types import SimpleNamespace
import ast,re,hashlib,json,importlib.util
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
lexer=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/source-budget/audit_budget.py'
assert hashlib.sha256(gate.read_bytes()).hexdigest()=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t=ast.parse(gate.read_text(encoding='utf8'))
env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS','ATTRIBUTES','BANNED']:
    n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
    env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
spec=importlib.util.spec_from_file_location('source_lexer',lexer)
lex=importlib.util.module_from_spec(spec);spec.loader.exec_module(lex)
def declarations(text):
    clean=lex.lex(text)[0]
    bounds=[m.start() for m in lex.CMD.finditer(clean)]+[len(clean)]
    return [(m['kind'],m['name'],clean[m.start():next(i for i in bounds if i>m.start())].strip()) for m in lex.DECL.finditer(clean)]
before=(D/'Kernel-jam17-unpruned.draft.lean').read_text(encoding='utf8')
after=(D/'Kernel-jam17-public-v1.draft.lean').read_text(encoding='utf8')
bd=declarations(before);ad=declarations(after)
br=[x for x in bd if x[0] not in ['theorem','lemma']];ar=[x for x in ad if x[0] not in ['theorem','lemma']]
assert br==ar,'Runtime or other declarations changed during pruning'
rows=[]
for name in ['Probe-jam17-v1.lean','Kernel-jam17-public-v1.draft.lean']:
    p=D/name;b=p.read_bytes();s=b.decode('utf8')
    checks={'intake':env['intake'](p,SimpleNamespace(slot='full')),'policy':env['policy'](p,SimpleNamespace(slot='full')),'options':env['options'](s)}
    assert all(v is None for v in checks.values()),checks
    assert b'\r' not in b and not b.startswith(b'\xef\xbb\xbf')
    rows.append({'file':name,'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest(),'original_static_gate':'PASS','canonical_UTF8_LF':True})
out={'rows':rows,'pruning_runtime_declarations_identical':True,'runtime_declarations_count':len(br),'removed_proof_count':len(bd)-len(ad),'Lean':'NOT_RUN','fullgate':'NOT_RUN','performance':'NOT_RUN'}
(D/'source-preflight.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps(out,indent=2))
