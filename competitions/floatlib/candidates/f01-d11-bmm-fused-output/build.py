from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

HERE = Path(__file__).resolve().parent
PARENT = HERE.parent / 'f01-d10-bmm-direct-rows' / 'Kernel.lean'
PARENT_SHA = 'a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78'
parent_bytes = PARENT.read_bytes()
assert sha256(parent_bytes).hexdigest() == PARENT_SHA
source = parent_bytes.decode('utf-8')
begin = source.index('namespace Submission.RowStream\n')
end = source.index('end Submission.RowStream', begin) + len('end Submission.RowStream')
block = (HERE / 'fused-output-block.lean').read_text(encoding='utf-8').strip()
candidate_bytes = (source[:begin] + block + source[end:]).encode('utf-8')
assert len(candidate_bytes) <= 256000
assert candidate_bytes.count(b'import ContractTensor') == 1
assert b'sorry' not in candidate_bytes
assert b'axiom ' not in candidate_bytes
assert b'unsafe ' not in candidate_bytes
assert b'extern ' not in candidate_bytes
(HERE / 'Kernel.lean').write_bytes(candidate_bytes)
manifest = {
    'candidate': HERE.name,
    'candidate_file': 'Kernel.lean',
    'candidate_sha256': sha256(candidate_bytes).hexdigest(),
    'candidate_bytes': len(candidate_bytes),
    'created_at_utc': datetime.now(timezone.utc).isoformat(),
    'parent': PARENT.parent.name,
    'parent_sha256': PARENT_SHA,
    'baseline': 'f01-r8-combined-result-guard',
    'baseline_sha256': '41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7',
    'mechanism': 'Replace Packed RowStream row-index Vector.flatMap / rowTiles Vector / RowOutput.row Vector with nested Fin.foldl over rows and F10 column groups carrying one output Array. Compute each F10 once, finish valid lanes and push immediately. Preallocate total output capacity with Array.mkEmpty. Keep nativeA map and full packedB unchanged.',
    'proof': 'Generic Fin.foldl indexed invariant; Prefix size and every written element; emit_prefix; group_prefix through Packed10Index.runDot_eq and Packed10.finish_dot10_lane with exact original-word NaN replay; row/output prefix through min tail counts; row-major decode bridge; equality to referenceBmm and Packed10.core. All new proof text is NOT_RUN.',
    'scope': 'Only Packed RowStream changes. Parent DirectRows, DirectSmall, add, mul, sum, NaN replay and native MAC inner loop unchanged.',
    'edge_cases': 'Definition and proof quantify all Nat dimensions, including empty groups/rows, n=0, incomplete F10 tails and huge Nat. Existing bmmPackedBase empty-output/n=0 reference fallback and Packed10Index.runDot machine-bound fallback remain in dispatcher.',
    'validation_mode': 'statement-only first, full original public gate if accepted',
    'proof_status': 'NOT_RUN',
    'kernel_replay': 'NOT_RUN',
    'axiom_audit': 'NOT_RUN',
    'checksum': 'NOT_RUN',
    'performance': 'UNKNOWN',
    'formal_submission': 'NOT_SUBMITTED',
    'attribution': 'All parent author/provenance comments preserved byte-for-byte outside replaced RowStream block. New fused-output writer/proof is session-authored; no external implementation copied.',
}
(HERE / 'manifest.json').write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
print(json.dumps({k: manifest[k] for k in ('candidate', 'candidate_sha256', 'candidate_bytes', 'proof_status')}, ensure_ascii=False))
