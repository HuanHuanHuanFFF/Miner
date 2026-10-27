"""Three proof-only explicit-ofNat normalization repairs from exact public23ad."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime,timezone
import ast,difflib,hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
parent=R/'competitions/floatlib/candidates/f01-r17-dev-u64-public1/Kernel.lean'
raw=parent.read_bytes();assert sha(parent)=='23adf0984bef02e611143cfc7e40d64d65c99caa0f4d11a0648812b2fb6f1e73'
e=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40302810209/download-01cea0d70e9c4c2d8a5721ed1721668a/diagnostics/f01-d7-public-suite/public-suite'
arch=e/'inputs/f01-r17-dev-u64-public1/Kernel.lean';assert arch.read_bytes()==raw
verdict=e/'f01-r17-dev-u64-public1-verdict.json';v=json.loads(verdict.read_text())
assert not v['passed'] and v['stage']=='statement'
for line in (6849,6873,6907):assert f'Submission.lean:{line}:' in v['reason']
edits=[
 ('mantissaWord_nat',6849,'  rw [FastMul.toUInt32_eq,UInt32.toNat_ofNat,hq]',
  "  simp only [FastMul.toUInt32_eq,UInt32.toNat_ofNat',hq]"),
 ('highWord_toUInt32_nat',6873,'  rw [FastMul.toUInt32_eq,UInt32.toNat_ofNat,highWord_nat a b ha0 ha hb0 hb]',
  "  simp only [FastMul.toUInt32_eq,UInt32.toNat_ofNat',highWord_nat a b ha0 ha hb0 hb]"),
 ('low_mask_eq_self',6907,'  rw [UInt32.toNat_and,UInt32.toNat_ofNat]',
  "  simp only [UInt32.toNat_and,UInt32.toNat_ofNat']")]
source=raw.decode();changed=source
for name,line,old,new in edits:
 assert source.splitlines()[line-1]==old
 assert changed.count(old)==1,(name,changed.count(old))
 changed=changed.replace(old,new)
inverse=changed
for name,line,old,new in reversed(edits):inverse=inverse.replace(new,old)
assert inverse==source
data=changed.encode();out=H/'Kernel.lean';out.write_bytes(data)
assert len(data)<=256000 and b'\r' not in data and out.read_text().encode()==data
patch=''.join(difflib.unified_diff(source.splitlines(True),changed.splitlines(True),fromfile='parent-23ad/Kernel.lean',tofile='repaired/Kernel.lean',n=3))
(H/'proof-only.patch').write_bytes(patch.encode())
lem=R/'competitions/floatlib/research/materials/20261022/R2-W01c/FloatLib_R2-W01c/public_sources/lean4/src/Init/Data/UInt/Lemmas.lean'
assert sha(lem)=='197db99e55771dbf24ef299a091e9266fb23758643c24ea31a24a8908239dc5c'
lt=lem.read_text();assert "theorem toNat_ofNat' {n : Nat} : (ofNat n).toNat = n % 2 ^ $bits" in lt
assert 'declare_uint_theorems UInt32 32' in lt
gate=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
assert sha(gate)=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
t=ast.parse(gate.read_text());env={'re':re,'Path':Path,'Verdict':SimpleNamespace,'_MAX_BYTES':256000,'SLOTS':{'full':SimpleNamespace(contract='ContractTensor')}}
for name in ('OPTIONS','ATTRIBUTES','BANNED'):
 n=next(n for n in t.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id==name for x in n.targets))
 env[name]=re.compile(ast.literal_eval(n.value.args[0])) if name=='BANNED' else ast.literal_eval(n.value)
fs=[n for n in t.body if isinstance(n,ast.FunctionDef) and n.name in ('intake','policy','options')]
exec(compile(ast.Module(body=fs,type_ignores=[]),str(gate),'exec'),env)
checks={k:env[k](out,SimpleNamespace(slot='full')) for k in ('intake','policy')};checks['options']=env['options'](changed)
assert all(x is None for x in checks.values()),checks
pm=json.loads(parent.with_name('manifest.json').read_text());roots=pm['explicit_helper_audit'];assert len(roots)==67
(H/'HelperAudit.lean.inc').write_bytes((''.join('#print axioms '+x+'\n' for x in roots)).encode())
ident=lambda p:dict(path=str(p.relative_to(R)),bytes=p.stat().st_size,sha256=sha(p))
j=dict(created_utc=datetime.now(timezone.utc).isoformat(),state='THREE_OBSERVED_REWRITE_POINTS_REPAIRED_NOT_COMPILED',
 parent=ident(parent),archived_input=ident(arch),candidate=dict(path='Kernel.lean',bytes=len(data),sha256=sha(out),margin=256000-len(data)),
 failure_bindings=[ident(verdict),ident(e/'f01-r17-dev-u64-public1-gate.log')],actual_failure_reason=v['reason'],full_goal_available=False,
 changes=[dict(theorem='R18.R17UInt64Fields.'+name,line=line,old=old,new=new) for name,line,old,new in edits],
 fixed_interface=dict(pin='293d5d0c0c3f3dded4688b3ccd6a33939ac5102b',file=ident(lem),
  explicit_constructor_lemma="UInt32.toNat_ofNat' : (UInt32.ofNat n).toNat = n % 2^32",
  literal_lemma='UInt32.toNat_ofNat matches toNat(no_index(OfNat.ofNat n)); distinct declaration',lines=[44,47,250]),
 rationale='Use the explicit-ofNat theorem and bounded simp-only normalization, which does not require a second rewrite occurrence after the first rewrite/projection reduction. No claim that the absent full goal proves one unique normalization cause.',
 preserved=['All theorem statements, hypotheses and subsequent Nat.mod bounds','All runtime definitions/public wrapper/fallback graph','Original try dsimp change','All67 roots and original frozen sources'],
 exact_inverse_rebuild=True,original_policy_checks=checks,canonical_LF=True,
 helper_roots=roots,patch=dict(path='proof-only.patch',sha256=sha(H/'proof-only.patch')),
 next='D compile exact new source. If another error occurs, preserve full statement stdout/goal before another proof edit; verdict/gate.log alone has no full goal.',
 not_run=['Lean','Kernel/helper audit for this source','Full gate','Performance'],CI=False,Git=False,local_Lean=False)
(H/'manifest.json').write_bytes((json.dumps(j,indent=2)+'\n').encode())
print(json.dumps(dict(candidate=j['candidate'],changes=len(edits),roots=len(roots),checks=checks,inverse=True)))
