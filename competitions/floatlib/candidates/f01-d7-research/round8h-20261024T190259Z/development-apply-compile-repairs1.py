"""Apply exact first compiler feedback to three new source versions."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib
import json

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
pairs=[
 ('astra-biased-rne2.lean','astra-biased-rne3.lean','fd3df0d744f52f15ba697b1f742f56d77c0ee58ea082b3f5872afbaa970f8326'),
 ('astra-small-shift-bias2.lean','astra-small-shift-bias3.lean','ec6a8e65cb608d094049682549e3e9213ac81e13125ca57d2a89943b2c2c2a94'),
 ('astra-word-add-alignment2.lean','astra-word-add-alignment4.lean','c8bd8475394f3161f412309476226edb724e961852e08ebce5d866aff8f69e50'),
 ('astra-word-add-rounding1.lean','astra-word-add-rounding2.lean','b358c5a11e524af35fc476a5d373c84714b3e570de543a0b9a5dd4dcfb6a846b'),
 ('development-word-add-runtime3.lean','development-word-add-runtime4.lean','ed74b92765065fc814c3e392b2f4dee4b72730ddd4e6d433ffed931b430f20fe'),
 ('development-word-add-fields2.lean','development-word-add-fields3.lean','eac38006c15aa6bfca52471da3aab14905714c0557ac138e7dc52c70ba39adb2'),
 ('development-word-add-spec2.lean','development-word-add-spec3.lean','234dfa98f80295e6d12501efbb819531f8755629c5a04ee165d229859c082999'),
]
for _,new_name,expected in pairs:assert sha((OUT/new_name).read_bytes())==expected
new_model=OUT/'astra-integer-core-model2.lean'
model_raw=new_model.read_bytes()
assert sha(model_raw)=='c201150eb693447adbec8c58a7e877f6f21ea336d00508582ac717680d2bd3bf'
model=model_raw[model_raw.index(b'theorem core_model '):model_raw.index(b'\nend Submission.R14ExponentShift')].rstrip()+b'\n\n'
results=[]
for parent_name,expected,name in (
 ('f01-r14-dev-integer-exponent3','5556cd0abefe97c136f9ef857b80637fe2ea4b43594b724728aef9a24bcfa703','f01-r14-dev-integer-exponent4'),
 ('f01-r14-dev-word-add-entry1','a2342948257d2e2e2011f0fe941bd2b692e70604b915734f4538b5efd1e69372','f01-r14-dev-word-add-entry2'),
 ('f01-r14-dev-allword-combined1','393473afe5cbcd5a360a30eff7e6729f6f591a7a427aedd101ad6ef9c8bf9c7c','f01-r14-dev-allword-combined2'),
):
    parent=C/parent_name;original=(parent/'Kernel.lean').read_bytes();assert sha(original)==expected
    result=original;changes=[];added=[]
    for old_name,new_name,_ in pairs:
        old=(OUT/old_name).read_bytes();new=(OUT/new_name).read_bytes()
        count=result.count(old)
        assert count<=1,(parent_name,old_name,count)
        if not count:continue
        result=result.replace(old,new)
        changes.append(dict(parent=old_name,parent_sha256=sha(old),path=new_name,sha256=sha(new),bytes=len(new)))
        added.append(new_name)
    if 'word-add' not in parent_name:
        start=result.index(b'theorem core_model (u v : UInt32)\n    (hu0 :')
        finish=result.index(b'theorem core_spec (x y : Binary32)\n    (hx0 :',start)
        old=result[start:finish]
        result=result[:start]+model+result[finish:]
        changes.append(dict(parent_theorem_sha256=sha(old),path=new_model.name,source_sha256=sha(model_raw),
                            selected_theorem_sha256=sha(model),selected_bytes=len(model)))
        added.append(new_model.name)
    # Both B-cache versions have the same proof-script error, independent of
    # which existing fallback name follows their namespace.
    old=b'    simp only [dif_pos hk]\n    dsimp only\n    rw [Packed10.nativeA_getD]'
    new=b'    simp only [dif_pos hk]\n    rw [Packed10.nativeA_getD]'
    if b'namespace Submission.R14ThinBCache' in result:
        assert result.count(old)==1
        result=result.replace(old,new)
        changes.append(dict(kind='THIN_LOOP_CONFIRMED_REDUNDANT_DSIMP_REMOVAL',runtime_changed=False))
    stripped=[]
    if len(result)>256000:
        assert parent_name=='f01-r14-dev-word-add-entry1'
        runtime=(OUT/'development-word-add-runtime4.lean').read_bytes()
        header=runtime[:runtime.index(b'namespace Submission.R14WordAdd')]
        assert result.count(header)==1 and b'copyright' not in header.lower() and b'license' not in header.lower()
        result=result.replace(header,b'')
        stripped.append(dict(kind='OWN_NON_ATTRIBUTION_COMPONENT_HEADER',bytes=len(header),sha256=sha(header)))
    assert len(result)<=256000,(name,len(result))
    assert result.count(b'import ContractTensor')==1
    folder=C/name;assert not folder.exists();folder.mkdir();(folder/'Kernel.lean').write_bytes(result)
    record=json.loads((parent/'manifest.json').read_bytes())
    record.update(candidate=name,candidate_sha256=sha(result),candidate_bytes=len(result),bytes_remaining=256000-len(result),
                  parent=parent_name,parent_sha256=expected,created_at_utc=datetime.now(timezone.utc).isoformat(),
                  proof_status='FIRST_ACTUAL_COMPILER_FEEDBACK_REPAIRS_NOT_COMPILED',performance='NOT_RUN',
                  exact_compiler_run=40149766137,repairs=changes,header_removals=stripped,
                  inherited_preparation_fields_refer_to_parent_manifest=True,
                  limits='First real error repairs only; complete exact-source compilation/replay/axiom gate and performance still required. No runtime algorithm or operand-order change; annotated UInt32 literals make intended original arithmetic well-typed.')
    components=record.get('components',[])
    mapping={old:new for old,new,_ in pairs}
    for item in components:
        previous=Path(item['path']).name
        if previous in mapping:
            path=OUT/mapping[previous];data=path.read_bytes()
            item.update(path=path.relative_to(ROOT).as_posix(),sha256=sha(data),bytes=len(data))
    known={x['path'] for x in components}
    for new_name in added:
        path=OUT/new_name;relative=path.relative_to(ROOT).as_posix();data=path.read_bytes()
        if relative not in known:
            components.append(dict(path=relative,sha256=sha(data),bytes=len(data)));known.add(relative)
    record['components']=components
    (folder/'manifest.json').write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode())
    results.append({k:record[k] for k in ('candidate','candidate_sha256','candidate_bytes','bytes_remaining','proof_status')})
(OUT/'development-first-real-compile-repair-build.json').write_bytes((json.dumps(dict(at_utc=datetime.now(timezone.utc).isoformat(),run=40149766137,results=results),indent=2)+'\n').encode())
print(json.dumps(results))
