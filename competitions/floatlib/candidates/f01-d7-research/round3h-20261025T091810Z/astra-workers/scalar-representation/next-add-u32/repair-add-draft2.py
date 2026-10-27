"""Exact proof-only correction of four ambiguous type annotations plus approved four-leaf trim.
Original2f998 and all prior probe/c972 files remain untouched. No Lean/CI/Git.
"""
from pathlib import Path
from datetime import datetime,timezone
from types import SimpleNamespace
import ast,hashlib,json,re,difflib
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
ROUND=HERE.parents[2]
PLAN=ROUND/'astra-workers/source-budget/add-specific/budget.json'
assert PLAN.is_file(),PLAN
sha=lambda b:hashlib.sha256(b).hexdigest()
planbytes=PLAN.read_bytes();assert sha(planbytes)=='ce0fab64ac6734214186b76c4710b2af9735bad3917853fa3f062874b59d52cf'
plan=json.loads(planbytes)
oldpath=HERE/'Kernel-add-native-high-draft1.lean';oldbytes=oldpath.read_bytes();old=oldbytes.decode('utf-8')
assert sha(oldbytes)==plan['source_sha256']=='2f998811caa348ad7c0e66026b0d049c6ce0720549dd12622345777d24a1e13e'
assert len(oldbytes)==plan['source_bytes']==255913
removed=[]
for p in plan['selected']:
    s=old[p['start']:p['end']];b=s.encode('utf-8')
    assert sha(b)==p['sha256'] and len(b)==p['bytes']
    assert s.startswith('theorem '+p['name'])
    assert '@[' not in s and '/-' not in s and '--' not in s
    assert not re.search(r'^\s*(?:def|abbrev|instance|structure|inductive|class|opaque)\b',s,re.M)
    assert len(re.findall(r'\b'+re.escape(p['name'])+r'\b',old))==1
    removed.append({'name':p['name'],'bytes':len(b),'sha256':sha(b)})
trimmed=old
for p in sorted(plan['selected'],key=lambda x:x['start'],reverse=True):
    trimmed=trimmed[:p['start']]+trimmed[p['end']:]
assert len(trimmed.encode())==253771 and sha(trimmed.encode())==plan['resulting_sha256']
for p in plan['selected']:assert not re.search(r'\b'+re.escape(p['name'])+r'(?:\b|\.)',trimmed)
a=trimmed.index('namespace Submission.A16I\n');b=trimmed.index('end Submission.A16I',a)
block=trimmed[a:b]
assert block.count(': Dyadic')==4
assert not re.search(r'^\s*(?:def|abbrev|instance|structure|inductive|class|opaque)\b',block,re.M)
fixedblock=block.replace(': Dyadic',': FloatLib.Numerics.Dyadic')
new=trimmed[:a]+fixedblock+trimmed[b:]
assert ': Dyadic' not in fixedblock
assert len(new.encode())<=256000
out=HERE/'Kernel-add-native-high-draft2.lean';assert not out.exists(), 'Never overwrite a repair source'
out.write_bytes(new.encode('utf-8'))
(HERE/'add-draft1-to-draft2.diff').write_text(''.join(difflib.unified_diff(old.splitlines(True),new.splitlines(True),
    fromfile=oldpath.name,tofile=out.name)),encoding='utf-8')
gate=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate.read_bytes())=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
tree=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,
 'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ['OPTIONS','ATTRIBUTES','BANNED']:
    n=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==name for t in n.targets))
    env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in ['intake','policy','options']]
exec(compile(ast.Module(body=nodes,type_ignores=[]),str(gate),'exec'),env)
policy={k:env[k](out,SimpleNamespace(slot='full')) for k in ['intake','policy']}
assert all(v is None for v in policy.values()),policy
assert sha(oldpath.read_bytes())==plan['source_sha256']
report={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'PROOF_ONLY_REPAIR_AND_ORIGINAL_TEXT_POLICY_PASS_LEAN_NOT_RUN',
 'parent':{'path':oldpath.name,'sha256':sha(oldbytes),'bytes':len(oldbytes)},
 'candidate':{'path':out.name,'sha256':sha(new.encode()),'bytes':len(new.encode()),'remaining_bytes':256000-len(new.encode())},
 'plan':{'path':str(PLAN.relative_to(ROOT)),'sha256':sha(planbytes),'coordinate_unit':'Unicode code points'},
 'removed':removed,'trim_only_sha256':sha(trimmed.encode()),'qualification_edits':4,
 'old_annotation':': Dyadic','new_annotation':': FloatLib.Numerics.Dyadic','qualification_scope':'Submission.A16I theorem declarations and proof type ascriptions only',
 'runtime_source_delta':'NONE: only four ordinary unreferenced theorem slices removed and four proof type annotations qualified; no def/abbrev/instance/structure/attribute/license edits',
 'original_policy':policy,'gate_sha256':sha(gate.read_bytes()),'policy_includes_comments':True,
 'original2f998_unchanged':True,'original41241_c972_edited':False,
 'causal_feedback':'40186471996 interface2 four shared bare Dyadic type ambiguities. LowNormalization errors are unrelated and not included in this high-N source.',
 'Lean':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN','tokens':'UNKNOWN','ci_occupancy_seconds':0}
(HERE/'public-add-draft2-repair.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report,indent=2))
