"""Versioned repair for confirmed local-let rewrite misuse; runtime unchanged."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
C = ROOT / 'competitions/floatlib/candidates'
old = (OUT / 'astra-biased-rne1.lean').read_bytes()
new = (OUT / 'astra-biased-rne2.lean').read_bytes()
assert hashlib.sha256(old).hexdigest() == '3515b1819897ad3d230f53d12375b85987fcf8678779e7428f4a78e693b65b0c'
assert hashlib.sha256(new).hexdigest() == 'e9abe15eaebf5dab13f717558292f49871f8fdde07b3075145915a493bb5db0a'
wrong = b'    rw [parity, UInt64.toNat_and, hshift]'
fixed = b'    dsimp only [parity]\n    rw [UInt64.toNat_and, hshift]'
assert old.count(wrong) == 1 and old.replace(wrong, fixed) == new
foundation1 = OUT / 'development-word-add-foundation.lean'
foundation2 = OUT / 'development-word-add-foundation2.lean'
assert not foundation2.exists()
data = foundation1.read_bytes()
assert data.count(old) == 1
foundation2.write_bytes(data.replace(old, new))
parents = [
    ('f01-r14-dev-integer-exponent2', 'b8a11a6a1c647df5031505b7effa5c3d21e653631db0638815a3062c7d20b6c2', 'f01-r14-dev-integer-exponent3'),
    ('f01-r14-dev-combined-slim2', 'b691c009afb1b484d23f25b154f7ea5b71fec521d7f55bf6660806316589aada', 'f01-r14-dev-combined-slim3'),
    ('f01-r14-dev-combined-headroom2', '29dc87c2280cb4274faf832bff84442a1dd8b1625a0fb8e754a7820fd330e8dd', 'f01-r14-dev-combined-headroom3'),
    ('f01-r14-dev-word-add-probe1', '24eea9a8d5f53eacdb7a3173bc7577445fe7effc1654c8af5af7a10b446bccf2', 'f01-r14-dev-word-add-probe2'),
]
rows = []
for parent_name, expected, name in parents:
    parent = C / parent_name
    original = (parent / 'Kernel.lean').read_bytes()
    assert hashlib.sha256(original).hexdigest() == expected and original.count(old) == 1
    result = original.replace(old, new)
    assert len(result) <= 256000 and wrong not in result
    folder = C / name
    assert not folder.exists()
    folder.mkdir()
    (folder / 'Kernel.lean').write_bytes(result)
    record = json.loads((parent / 'manifest.json').read_bytes())
    record.update(candidate=name, candidate_sha256=hashlib.sha256(result).hexdigest(), candidate_bytes=len(result),
                  created_at_utc=datetime.now(timezone.utc).isoformat(), parent=parent_name, parent_sha256=expected,
                  proof_status='CONFIRMED_LOCAL_LET_UNFOLD_REPAIR_NOT_COMPILED', performance='NOT_RUN',
                  bytes_remaining=256000 - len(result),
                  repair={'description':'Replace rw[local parity:UInt64] by dsimp only[parity], then rewrite actual equalities.',
                          'runtime_definition_source_changed':False, 'old_fragment_sha256':hashlib.sha256(old).hexdigest(),
                          'new_fragment_sha256':hashlib.sha256(new).hexdigest(), 'source_proof_only':True,
                          'inherited_preparation_fields_refer_to_parent_manifest':True})
    for component in record.get('components', []):
        if component['path'].endswith('/astra-biased-rne1.lean'):
            component.update(path=(OUT / 'astra-biased-rne2.lean').relative_to(ROOT).as_posix(), bytes=len(new), sha256=hashlib.sha256(new).hexdigest())
        if component['path'] == foundation1.relative_to(ROOT).as_posix():
            component.update(path=foundation2.relative_to(ROOT).as_posix(), bytes=foundation2.stat().st_size, sha256=hashlib.sha256(foundation2.read_bytes()).hexdigest())
    if 'source_budget' in record:
        record['source_budget'] = {**record['source_budget'], 'candidate_bytes':len(result)}
    (folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
    rows.append({key: record[key] for key in ('candidate','candidate_sha256','candidate_bytes','bytes_remaining','parent','proof_status')})
base = (C / 'f01-r14-dev-compact-base/Kernel.lean').read_bytes()
assert hashlib.sha256(base).hexdigest() == '3c6af73f9d679e9831ac8c4abb9f0e6d41b61718301dd045bedd2402e980632a'
folder = C / 'f01-r14-dev-bias-repair-probe2'
assert not folder.exists()
folder.mkdir()
result = base + b'\n' + new
(folder / 'Kernel.lean').write_bytes(result)
record = dict(candidate=folder.name, candidate_file='Kernel.lean', candidate_sha256=hashlib.sha256(result).hexdigest(),
              candidate_bytes=len(result), created_at_utc=datetime.now(timezone.utc).isoformat(), validation_mode='statement-only',
              proof_status='CONFIRMED_LOCAL_LET_REPAIR_NOT_COMPILED', public_runtime_changed=False,
              fragment=(OUT / 'astra-biased-rne2.lean').relative_to(ROOT).as_posix(), fragment_sha256=hashlib.sha256(new).hexdigest(),
              parent='f01-r14-dev-compact-base', parent_sha256=hashlib.sha256(base).hexdigest(), performance='NOT_RUN')
(folder / 'manifest.json').write_bytes((json.dumps(record, ensure_ascii=False, indent=2) + '\n').encode())
rows.append({key: record[key] for key in ('candidate','candidate_sha256','candidate_bytes','parent','proof_status')})
receipt = dict(at_utc=datetime.now(timezone.utc).isoformat(), old_sources_kept_unchanged=True, new_sources=rows,
               scope='Confirmed proof-script correction only; all new compiler/axiom/replay/performance checks remain NOT_RUN.')
(OUT / 'development-bias-local-let-repair3.json').write_bytes((json.dumps(receipt, indent=2) + '\n').encode())
print(json.dumps(receipt))
