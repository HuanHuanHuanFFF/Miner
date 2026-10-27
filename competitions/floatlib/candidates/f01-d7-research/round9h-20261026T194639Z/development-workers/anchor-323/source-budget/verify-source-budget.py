"""Independently replay deletion ledger; no writes to source/candidates."""
import base64
from bisect import bisect_right
from collections import Counter
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('jam17_comment_budget', HERE / 'analyze-comment-budget.py')
a = importlib.util.module_from_spec(spec)
spec.loader.exec_module(a)
read = lambda p: json.loads(Path(p).read_bytes())


def main():
    original = a.SOURCE.read_bytes()
    draft = (HERE / 'Jam17-comments-emptylines-draft.lean.txt').read_bytes()
    ledger = read(HERE / 'inverse-deletions.json')
    receipt = read(HERE / 'budget-receipt.json')
    a.require(a.sha(original) == a.SOURCE_SHA == ledger['source_sha256'], 'Wrong source SHA')
    a.require(a.sha(draft) == ledger['draft_sha256'] == receipt['policies']['preserve_each_distinct_notice']['draft_sha256'], 'Wrong draft SHA')
    # Forward replay from original offsets, independent of writer's keep mask.
    chunks, previous, output_offset = [], 0, 0
    for edit in ledger['edits']:
        start, end = edit['original_start_byte'], edit['original_end_byte']
        removed = base64.b64decode(edit['removed_bytes_base64'], validate=True)
        a.require(previous <= start < end <= len(original), 'Invalid/non-monotone deletion range')
        a.require(original[start:end] == removed and len(removed) == end-start, 'Deletion payload mismatch')
        chunk = original[previous:start]; chunks.append(chunk); output_offset += len(chunk)
        a.require(output_offset == edit['draft_offset_byte'], 'Wrong inverse draft offset')
        previous = end
    chunks.append(original[previous:])
    a.require(b''.join(chunks) == draft, 'Draft performs more than exact recorded deletions')
    # Inverse replay uses only draft and ledger, not original source content.
    restored, previous = bytearray(), 0
    for edit in ledger['edits']:
        offset = edit['draft_offset_byte']
        restored.extend(draft[previous:offset]); previous = offset
        restored.extend(base64.b64decode(edit['removed_bytes_base64'], validate=True))
    restored.extend(draft[previous:])
    a.require(bytes(restored) == original, 'Reverse reconstruction differs from original bytes')
    before, comments = a.scan(original.decode())
    after, after_comments = a.scan(draft.decode())
    a.require([(k, v) for k, v, _, _ in before] == [(k, v) for k, v, _, _ in after], 'Token partition differs')
    def columns(raw, tokens):
        text = raw.decode(); starts = [0] + [i+1 for i, c in enumerate(text) if c == '\n']
        return [start-starts[bisect_right(starts, start)-1] for _, _, start, _ in tokens]
    a.require(columns(original, before) == columns(draft, after), 'A token moved horizontally')
    key = {'def', 'theorem', 'abbrev', 'opaque', 'axiom', 'namespace', 'end', 'import', 'set_option', 'open'}
    old_counts = Counter(value for kind, value, _, _ in before if kind == 'word' and value in key)
    new_counts = Counter(value for kind, value, _, _ in after if kind == 'word' and value in key)
    a.require(old_counts == new_counts, 'Declaration/namespace/options/header keyword count differs')
    a.require(draft.startswith(b'import ContractTensor\n'), 'Intake import header changed')
    notice = next(original.decode()[c['start']:c['end']].encode() for c in comments if 'MIT License' in original.decode()[c['start']:c['end']])
    a.require(original.count(notice) == 2 and draft.count(notice) == 1, 'Each distinct notice is not preserved byte-for-byte')
    a.require(len(after_comments) == 1 and draft.decode()[after_comments[0]['start']:after_comments[0]['end']].encode() == notice, 'A removable non-notice comment remains')
    position, remaining_unprotected_blank = 0, 0
    for line in draft.decode().splitlines(keepends=True):
        if not line.strip() and not any(c['start'] <= position < c['end'] for c in after_comments):
            remaining_unprotected_blank += 1
        position += len(line)
    a.require(remaining_unprotected_blank == 0, 'A removable unprotected blank line remains')
    # A zero-change negative control is not enough: detect token and indent edits.
    tampered = draft.replace(b'namespace R7W04', b'namespace R7W05', 1)
    a.require([(k, v) for k, v, _, _ in a.scan(tampered.decode())[0]] != [(k, v) for k, v, _, _ in before], 'Token-edit negative control missed')
    shifted = draft.replace(b'  cases x with', b' cases x with', 1)
    shifted_tokens = a.scan(shifted.decode())[0]
    a.require(columns(shifted, shifted_tokens) != columns(original, before), 'Indent-edit negative control missed')
    result = {'status': 'PASS_LOCAL_ONLY', 'at_utc': datetime.now(timezone.utc).isoformat(),
        'source_sha256': a.sha(original), 'draft_sha256': a.sha(draft), 'source_bytes': len(original), 'draft_bytes': len(draft),
        'saved_bytes': len(original)-len(draft), 'exact_forward_deletion_replay': True, 'exact_reverse_byte_reconstruction': True,
        'token_count': len(before), 'token_partition_equal': True, 'all_token_start_columns_equal': True,
        'nonempty_token_line_indentation_and_prefix_equal': True, 'declaration_keyword_counts': dict(sorted(old_counts.items())),
        'intake_import_line_exact': True, 'each_distinct_notice_preserved_exact': True,
        'remaining_non_notice_comments': 0, 'remaining_unprotected_blank_lines': 0,
        'negative_controls': ['changed_namespace_token_detected', 'changed_indentation_detected'],
        'source_unchanged_after_verification': a.sha(a.SOURCE.read_bytes()) == a.SOURCE_SHA,
        'lean_frontend_build_gate': 'NOT_RUN', 'scope': 'Only local byte/lexer/layout checks; draft is NOT a candidate or an acceptance result.'}
    (HERE / 'verification-receipt.json').write_bytes(a.encode(result))
    print(json.dumps(result, ensure_ascii=False))


if __name__ == '__main__':
    main()
