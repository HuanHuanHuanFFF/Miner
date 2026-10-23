"""Repair the two exact proof-glue failures observed in R11 seed910."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[5]
parent = ROOT/'competitions/floatlib/candidates/f01-d11-bmm-batch-local-output'
raw = (parent/'Kernel.lean').read_bytes()
assert hashlib.sha256(raw).hexdigest() == '7e7776d95fd74d3fc2fa68ab629750228d800cac54825b41606b20ee538fdc9b'
source = raw.decode('utf-8')
old_bound = '''    have h := Nat.mul_le_mul_right m b.isLt
    rw [Nat.add_mul] at h
    omega⟩'''
new_bound = '''    have h := Nat.mul_le_mul_right m b.isLt
    rw [Nat.succ_mul] at h
    have hi := i.isLt
    omega⟩'''
old_base = '  rw [hbb, packBatch_eq]\n'
new_base = old_base+'  rw [hb]\n'
assert source.count(old_bound) == source.count(old_base) == 1
source = source.replace(old_bound, new_bound, 1).replace(old_base, new_base, 1)
assert source.replace(new_bound, old_bound, 1).replace(new_base, old_base, 1).encode('utf-8') == raw
payload = source.encode('utf-8')
assert len(payload) <= 256000
out = ROOT/'competitions/floatlib/candidates/f01-d11-bmm-batch-local-output-proof2'
out.mkdir(exist_ok=False)
(out/'Kernel.lean').write_bytes(payload)
manifest = json.loads((parent/'manifest.json').read_bytes())
manifest.update(candidate=out.name, candidate_sha256=hashlib.sha256(payload).hexdigest(),
    candidate_bytes=len(payload), parent=parent.name, parent_sha256=hashlib.sha256(raw).hexdigest(),
    created_at_utc=datetime.now(timezone.utc).isoformat(), proof_status='NOT_RUN_PROOF_GLUE_REPAIR',
    change='Only proof terms: rewrite the actual Nat.succ_mul bound and explicitly use i.isLt; rewrite hb for the remaining raw B Nat base after the Fin index rewrite. All computational value expressions, scan/packing/arithmetic/output and resource options unchanged.',
    previous_failure={'run':40025423585,'seed':910,'stage':'statement',
        'verdict_sha256':'552b06aacdd76eb92824b6ff1e6dfba585fe2d022cd8600967966048e9c6c3c0',
        'errors':['6624:8 add_mul pattern absent on Nat.succ bound',
                  '6656:86 Nat r/m B base remains after Fin equality rewrite']})
(out/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
(out/'repair-evidence.json').write_text(json.dumps({'old_sha256':hashlib.sha256(raw).hexdigest(),
    'new_sha256':hashlib.sha256(payload).hexdigest(),'inverse_restores_parent_bytes':True,
    'rowIndex_value_expression_unchanged':'b.val*m+i.val',
    'other_runtime_expressions_unchanged':True,'official_environment_options_changed':False},indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':out.name,'sha256':manifest['candidate_sha256'],'bytes':len(payload)}))
