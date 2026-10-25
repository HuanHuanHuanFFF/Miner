"""Import two key-boundary-reviewed pure source entries for one compiler probe."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
baseline=(C/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha(baseline)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
jobs=[dict(candidate='f01-r16-dev-native-repack1',worker='scalar-representation',kernel='Kernel-native-repack.lean',
    expected='c972fd72694d4d7db4660d2dbcd640d766d013d58bd9c9a27a6c68d47010b7ac',
    pieces=['native-repack-complete-fragment.lean'],mechanism='Guarded normal MUL: native mantissa multiply and field repack, removing scale-table loads and scale multiplies; original B2 fallback and other public operations retained.'),
    dict(candidate='f01-r16-dev-a4b2-entry1',worker='matrix-architecture',kernel='Kernel-a4b2.lean',
    expected='5f53a9300f6554a80a68fcee5fda84dc4af063706c0b928be8ec9d7f1b81213c',
    pieces=['A4B2-core.lean','A4B2-entry.lean'],mechanism='Per-batch four-row panel prepared once outside all B2 column groups; eight USize accumulators, complete ordered four-row writer and original B2 tail/fallback. All costs charged.')]
records=[]
for job in jobs:
    worker=HERE/'astra-workers'/job['worker'];raw=(worker/job['kernel']).read_bytes()
    assert sha(raw)==job['expected'] and len(raw)<=256000
    assert re.findall(rb'^import\s+([^\r\n]+)',raw,re.M)==[b'ContractTensor']
    assert not re.search(rb'(?m)^\s*(?:axiom|unsafe|partial)\s|@\[\s*extern|\bimplemented_by\b|\bnative_decide\b',raw)
    components=[]
    for name in job['pieces']:
        original=(worker/name).read_bytes();data=original.replace(b'\r\n',b'\n')
        assert raw.count(data)==1,(job['candidate'],name)
        path=HERE/('development-'+job['worker']+'-'+name)
        assert not path.exists();path.write_bytes(data)
        components.append(dict(path=path.relative_to(ROOT).as_posix(),sha256=sha(data),bytes=len(data),producer_original_sha256=sha(original)))
    folder=C/job['candidate'];assert not folder.exists();folder.mkdir()
    (folder/'Kernel.lean').write_bytes(raw)
    manifest=dict(candidate=job['candidate'],candidate_file='Kernel.lean',candidate_sha256=sha(raw),candidate_bytes=len(raw),
        created_at_utc=datetime.now(timezone.utc).isoformat(),parent='f01-r15-dev-packed-b2-1',parent_sha256=sha(baseline),
        components=components,mechanism=job['mechanism'],proof_status='NOT_COMPILED',performance='NOT_RUN',full_gate='NOT_RUN',
        key_review='R source-level guard/tail/fallback review: shared20261025T094800Z-r16-research-first-decision.md; not a Lean or performance acceptance.',
        scope='Only pure candidate/proof source imported. Full research notes, prompts and old190 held export are excluded.')
    (folder/'manifest.json').write_bytes((json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode())
    records.append({k:manifest[k] for k in ('candidate','candidate_sha256','candidate_bytes')})
(HERE/'development-first-entry-import.json').write_bytes((json.dumps(records,indent=2)+'\n').encode())
print(json.dumps(records))
