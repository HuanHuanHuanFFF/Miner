"""Bind complete narrow word-add source to the actual public add entry."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
C=ROOT/'competitions/floatlib/candidates'
sha=lambda data:hashlib.sha256(data).hexdigest()
read=lambda name:(OUT/name).read_bytes()
def create(name,data):
    path=OUT/name
    assert not path.exists(),name
    path.write_bytes(data)
    return path

parent_manifest=json.loads((C/'f01-r14-dev-word-add-fields1/manifest.json').read_bytes())
base_path=ROOT/parent_manifest['slim_parent']['path']
base=base_path.read_bytes()
assert sha(base)==parent_manifest['slim_parent']['sha256']
fields=read('development-word-add-fields1.lean')
assert sha(fields)==parent_manifest['components'][-1]['sha256']
old_order=b'    R2W01c.wordExp (low u v) \xe2\x89\xa4 R2W01c.wordExp (high u v) \xe2\x88\xa7\n'
assert fields.count(old_order)==1
fields2=fields.replace(old_order,b'')
before=b'  refine \xe2\x9f\xa8hehi, helo, ?_, hc.2.2.1, ?_\xe2\x9f\xa9\n  \xc2\xb7 rw [hs.1, hs.2]\n    omega\n'
after=b'  refine \xe2\x9f\xa8hehi, helo, hc.2.2.1, ?_\xe2\x9f\xa9\n'
assert fields2.count(before)==1
fields2=fields2.replace(before,after)
fields2=fields2.replace(b'hs.2.2.2.1',b'hs.2.2.1').replace(b'hs.2.2.2.2',b'hs.2.2.2')
fields2_path=create('development-word-add-fields2.lean',fields2)

raw_model=read('astra-word-add-raw-model1.lean')
assert sha(raw_model)=='d507f17d5b4a363fdfaf1a329be036a33df1122d4ef87b9959a1861013bf7323'
start=raw_model.index(b'theorem raw_add_sorted_conditions ')
finish=raw_model.index(b'theorem raw_add_model ',start)
removed=raw_model[start:finish]
integrated=raw_model[:start]+raw_model[finish:]
integrated=integrated.replace(b'raw_add_sorted_conditions',b'sorted_domain').replace(b'raw_add_gap_nat',b'gap_pair')
raw_path=create('development-word-add-raw-model-integration1.lean',integrated)

spec=read('development-word-add-spec1.lean')
old_bridge=b'R2W01c.rawModel_eq_ofUInt32'
assert spec.count(old_bridge)==1
spec2=spec.replace(old_bridge,b'R2W01c.rawModel_eq_native32')
spec_path=create('development-word-add-spec2.lean',spec2)

support=json.loads((C/'f01-r14-dev-word-add-support1/manifest.json').read_bytes())
pieces=[];components=[]
for item in support['components']:
    data=(ROOT/item['path']).read_bytes()
    assert sha(data)==item['sha256'] and len(data)==item['bytes']
    pieces.append(data);components.append(item)
for path in (fields2_path,raw_path,spec_path):
    data=path.read_bytes();pieces.append(data)
    components.append(dict(path=path.relative_to(ROOT).as_posix(),sha256=sha(data),bytes=len(data)))

text=base.decode()
first=text.index('@[inline] def add (x y : Binary32) : Binary32 :=\n  let result :=')
last=text.index('@[inline] def nativeMul ',first)
old=text[first:last]
assert old.count('theorem add_spec :')==1
fallback=old.replace('def add (','def addBeforeWord (').replace('theorem add_spec :','theorem addBeforeWord_spec :')
fallback=fallback.replace(', add x y = ExecFloat.Spec.add x y',', addBeforeWord x y = ExecFloat.Spec.add x y')
fallback=fallback.replace('  unfold add\n','  unfold addBeforeWord\n')
assert 'addBeforeWord x y = ExecFloat.Spec.add x y' in fallback
assert 'theorem add_spec :' not in fallback and '  unfold add\n' not in fallback
wrapper='''
namespace Submission
open FloatLib.Floats Competition

@[inline] def add (x y : Binary32) : Binary32 :=
  R14WordAdd.guardedAdd addBeforeWord x y

theorem add_spec : \u2200 x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  exact R14WordAdd.guardedAdd_spec addBeforeWord addBeforeWord_spec x y

'''
result=(text[:first]+fallback+'\nend Submission\n').encode()+b'\n'.join(pieces)+wrapper.encode()+text[last:].encode()
assert result.count(b'import ContractTensor')==1
assert result.index(b'theorem guardedAdd_spec ')<result.index(b'R14WordAdd.guardedAdd addBeforeWord x y')<result.index(b'theorem add_eq :')
assert b'R14ExponentShift.guardedMul' not in result
record=dict(created_at_utc=datetime.now(timezone.utc).isoformat(),candidate_file='Kernel.lean',
            candidate_sha256=sha(result),candidate_bytes=len(result),bytes_remaining=256000-len(result),
            parent='f01-r14-dev-word-add-fields1',parent_sha256=parent_manifest['candidate_sha256'],
            slim_parent=parent_manifest['slim_parent'],components=components,
            raw_model_derivation=dict(source='astra-word-add-raw-model1.lean',source_sha256=sha(raw_model),
                                      removed_duplicate_proof_bytes=len(removed),removed_duplicate_sha256=sha(removed),
                                      replacements={'raw_add_sorted_conditions':'sorted_domain','raw_add_gap_nat':'gap_pair'}),
            fields_derivation='Drop the unused order conjunct so sorted_domain matches the existing exact tuple required by the raw bridge; adapt its proof/projections only.',
            spec_derivation='Use the parent exact rawModel_eq_native32 theorem to match the NativeBinary32 codec directly. Prior generic-ofUInt32 expression remains in spec1; no actual compiler error is alleged.',
            validation_mode='full-gate',proof_status='COMPLETE_PUBLIC_ADD_SOURCE_ATTEMPT_NOT_COMPILED',performance='NOT_RUN',
            runtime='Actual public add uses pure UInt32 alignment/leading-bit and UInt64 biased RNE when both inputs normal, gap<=7 and same signs or gap>=2, and full result exponent1..254. All other inputs call the original ordered add fallback. No Float32 conversion/arithmetic in the fast arm.',
            unchanged='Original DF mul/spec restored; original SUM runtime remains. The inherited thin-cache and p<=8 direct BMM is a separate new mechanism and retains its full proof attempt.',
            limits='No Lean compilation, replay, axiom audit or timing has run on this exact source. All source-sized transformations preserve their frozen parents; no performance or full-input acceptance follows from finite host models.')
receipt=OUT/'development-word-add-entry-build1.json'
assert not receipt.exists()
receipt.write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode())
assert len(result)<=256000,record
folder=C/'f01-r14-dev-word-add-entry1'
assert not folder.exists()
folder.mkdir();(folder/'Kernel.lean').write_bytes(result)
record['candidate']=folder.name
(folder/'manifest.json').write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps({k:record[k] for k in ('candidate','candidate_sha256','candidate_bytes','bytes_remaining','proof_status')}))
