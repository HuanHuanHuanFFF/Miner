from pathlib import Path
import re,json,hashlib,difflib
D=Path(__file__).resolve().parent
F=D.parents[4]
old=F/'candidates/f01-d7-research/round11h-20261025T173831Z/astra-workers/structural-frontier/integer-normal-mul/public-entry-repair1/Kernel.lean'
s=old.read_text(encoding='utf8')
fieldsrc=s[s.index('namespace R18.R17UInt64Fields'):s.index('end R18PublicMULBridgeProbe')]
def decl(src,name):
    m=list(re.finditer(r'^(?:(?:@\[[^\n]*\]|private)\s+)*(?:theorem|def) '+re.escape(name)+r'\b',src,re.M))
    assert len(m)==1,(name,len(m))
    st=m[0].start();end=m[0].end()
    e=re.search(r'^((?:@\[[^\n]*\]\s*)?(?:theorem|def|end|namespace)\b|/[-*])',src[end:],re.M)
    assert e,(name,'noend')
    return src[st:end+e.start()].rstrip()+'\n\n'
ns='namespace Submission.R19Jam17\nopen FloatLib.Floats Competition\nopen FloatLib.Floats.Formats.BinaryInterchange\n\n'
bridge=ns+''.join(decl(fieldsrc,n) for n in ['fractionWord_nat','exponentWord_nat','output_fields','low_mask_eq_self','mkW_eq_unmasked','packed_fields','normalCore_eq_fields'])
bridge=bridge.replace('highWord_toUInt32_nat','highWord_nat').replace('R17NumericMulInteger.normalCore','normalCore')
specsrc=(old.parent.parent/'Public-numeric-mul-bridge-v1.lean.inc').read_text(encoding='utf8')
bridge+=''.join(decl(specsrc,n) for n in ['sign_word_eq','core','core_word','core_model','core_spec','guardedMul_spec'])
bridge=bridge.replace('R17UInt64Fields.normalCore_eq_fields','normalCore_eq_fields').replace('R17NumericMulInteger.normalCore','normalCore').replace('R17NumericMulInteger.guardedMul','guardedMul')
bridge+='end Submission.R19Jam17\n'
(D/'Jam-public-bridge.lean.inc').write_text(bridge,encoding='utf8',newline='\n')
base=(F/'candidates/f01-r17-dev-u32-roundtrip-repair2/Kernel.lean').read_text(encoding='utf8')
parts=[base,(D/'Jam17.lean.inc').read_text(encoding='utf8'),(D/'Verified-model-support.lean.inc').read_text(encoding='utf8'),(D/'JamFields.lean.inc').read_text(encoding='utf8'),bridge]
whole='\n\n'.join(parts).replace('Submission','R19Base')
wrapper='''
namespace Submission
open FloatLib.Floats Competition
@[inline] def add := R19Base.add
theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := R19Base.add_spec
@[inline] def mul (x y : Binary32) : Binary32 := R19Base.R19Jam17.guardedMul R19Base.mul x y
theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y :=
  R19Base.R19Jam17.guardedMul_spec R19Base.mul R19Base.mul_spec x y
@[inline] def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R19Base.sum x
theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := R19Base.sum_spec
@[inline] def bmm := R19Base.bmm
theorem bmm_spec : ∀ (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := R19Base.bmm_spec
end Submission
'''
whole+=wrapper
(D/'Kernel-jam17-unpruned.draft.lean').write_text(whole,encoding='utf8',newline='\n')
# Safe source budget selection: unreferenced ordinary theorem leaves, never runtime or specs.
# Removal list is deterministic and each exact declaration text has only one short-name occurrence.
pruned=whole;removed=[]
while len(pruned.encode())>255500:
    found=[]
    for m in re.finditer(r'^theorem ([A-Za-z_][A-Za-z0-9_\x27?]*)\b',pruned,re.M):
        name=m.group(1)
        if name.endswith('_spec') or name in ['or_one','jamNat_eq','rne_jam','jam_bounds','leading_cases','jamWord_nat','jam_roundtrip']:continue
        if len(re.findall(r'(?<![A-Za-z0-9_\x27?])'+re.escape(name)+r'(?![A-Za-z0-9_\x27?])',pruned))!=1:continue
        before=pruned[:m.start()].rstrip().split('\n')[-1]
        if before.lstrip().startswith('@['):continue
        e=re.search(r'^((?:@\[[^\n]*\]\s*)?(?:theorem|def|end|namespace|abbrev|instance|structure)\b|/[-*])',pruned[m.end():],re.M)
        if not e:continue
        end=m.end()+e.start()
        txt=pruned[m.start():end]
        found.append((len(txt.encode()),name,m.start(),end,txt))
    assert found,'Insufficient ordinary theorem leaves'
    size,name,st,en,txt=max(found)
    removed.append({'name':name,'bytes':size,'text':txt})
    pruned=pruned[:st]+pruned[en:]
out=D/'Kernel-jam17-public-v1.draft.lean'
out.write_text(pruned,encoding='utf8',newline='\n')
patch=''.join(difflib.unified_diff(whole.splitlines(keepends=True),pruned.splitlines(keepends=True),fromfile='unpruned',tofile='public-v1'))
(D/'source-budget-pruning.patch').write_text(patch,encoding='utf8',newline='\n')
# Check proof-only removal by stripping only listed exact blocks from original.
replay=whole
for r in removed:assert replay.count(r['text'])==1;replay=replay.replace(r['text'],'',1)
assert replay==pruned
assert not re.search(r'\b(sorry|admit|axiom|unsafe|implemented_by)\b',pruned)
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec']
for frag in parts[1:]:
    # Audit all new-module named theorem roots including retained support; namespace-aware scan.
    stack=[]
    for line in frag.splitlines():
        if line.startswith('namespace '):stack.append(line[len('namespace '):])
        elif line.startswith('end '):
            if stack:stack.pop()
        else:
            m=re.match(r'theorem (\w+)\b',line)
            if m:
                root='.'.join(stack+[m.group(1)]).replace('Submission','R19Base')
                if m.group(1) not in [r['name'] for r in removed]:roots.append(root)
roots=list(dict.fromkeys(roots))
(D/'HelperAudit-public-jam17.lean.inc').write_text('\n'.join('#print axioms '+r for r in roots)+'\n',encoding='utf8')
manifest={'state':'COMPLETE_PUBLIC_PROOF_ATTEMPT_NOT_RUN','unpruned_bytes':len(whole.encode()),'public_bytes':len(pruned.encode()),'public_sha256':hashlib.sha256(pruned.encode()).hexdigest(),'public_path':str(out),'within256000':len(pruned.encode())<=256000,'removed_ordinary_leaves':[{'name':r['name'],'bytes':r['bytes']} for r in removed],'source_budget_replay':True,'new_runtime':'Same frozenJam17 interface runtime; publicMUL now invokes guardedJam17 withB2 fallback;add/sum/bmm aliasB2','roots_count':len(roots),'roots':roots,'gate':'NOT_RUN','statement':'NOT_RUN','axioms':'NOT_RUN','kernel_replay':'NOT_RUN','performance':'NOT_RUN'}
(D/'public-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8')
print(json.dumps({k:v for k,v in manifest.items() if k!='roots'},indent=2))
