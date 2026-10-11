"""Test whether the matched-suffix key can replace the existing crossing tail key."""
from pathlib import Path
import hashlib, json

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT/'candidates/r22-595-chain-halfhead'
OUT = ROOT/'candidates/r25-root-tail4'


def main():
    raw = (PARENT/'parse.rs').read_bytes()
    assert hashlib.sha256(raw).hexdigest() == '57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275'
    source = raw.decode()
    start = source.index('pub fn pc_f_record3<const H: usize>')
    end = source.index('/// `pc_run1` with chain', start)
    original = source[start:end]
    before = '            ins = end - 1;'
    after = '''            // Reuse the one existing tail insertion for a complete matched key.
            // If the suffix is already covered by the head inserts, keep the old tail.
            if end >= 4 && ins <= end - 4 {
                ins = end - 4;
            } else {
                ins = end - 1;
            }'''
    assert original.count(before) == 1
    changed = original.replace(before, after)
    updated = source[:start]+changed+source[end:]
    assert updated.replace(changed, original).encode() == raw
    assert not OUT.exists()
    OUT.mkdir()
    (OUT/'parse.rs').write_bytes(updated.encode())
    (OUT/'Parse.lean').write_bytes((PARENT/'Parse.lean').read_bytes())
    manifest = {'candidate':OUT.name, 'parent':PARENT.name,
        'hashes':{f:hashlib.sha256((OUT/f).read_bytes()).hexdigest() for f in ('parse.rs','Parse.lean')},
        'mechanism':'Replace the original end-1 insertion with end-4 only when the complete matched suffix is beyond all inserted head positions. Keep the original tail for short/covered cases; no extra hash-table update.',
        'difference_from_old_work':'R25 end4 empirically improved15 public files but added an insertion. This isolates suffix-key position versus additional table-write/search coverage cost; it is not an insertion-density parameter sweep.',
        'attribution':{'original_source':'references/round21-public-595/source-receipt.json','parent':'candidates/r22-595-chain-halfhead/manifest.json','trigger':'evidence/round25/feedback-a-native.json'},
        'proof_status':'DRAFT_PARENT_PROOF_NOT_VERIFIED_FOR_CHANGED_RUST',
        'performance_status':'NOT_RUN', 'formal_submission_sent':False}
    (OUT/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
    print(json.dumps(manifest,indent=2))


if __name__ == '__main__': main()
