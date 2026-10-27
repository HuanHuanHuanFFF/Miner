"""Pinned Jam17 comment/empty-line budget; no Lean execution or candidate writes."""
import base64
from bisect import bisect_right
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import sys
import unicodedata

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
SOURCE = ROOT / 'competitions/floatlib/candidates/f01-r19-dev-jam17-public1/Kernel.lean'
PATCH = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/astra-workers/exact-arithmetic/source-budget-pruning.patch'
SOURCE_SHA = 'b2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff'
sha = lambda b: hashlib.sha256(b).hexdigest()
encode = lambda x: (json.dumps(x, ensure_ascii=False, indent=2) + '\n').encode()


def require(ok, text):
    if not ok:
        raise ValueError(text)


def word(c):
    return c.isalnum() or c in "_'?!" or unicodedata.category(c).startswith('M')


def scan(text):
    """Conservative partition; opaque strings/raw strings/quoted identifiers.

    Interpolated-string syntax is rejected rather than parsed heuristically.
    This is not a replacement for Lean's frontend. Exact code bytes, literal
    bytes, token boundaries and token-column invariants are also checked.
    """
    tokens, comments = [], []
    i, n = 0, len(text)
    while i < n:
        if text[i].isspace():
            i += 1; continue
        start = i
        if text.startswith('--', i):
            end = text.find('\n', i)
            i = n if end < 0 else end
            comments.append({'start': start, 'end': i, 'kind': 'line', 'nested_depth': 1})
            continue
        if text.startswith('/-', i):
            i += 2; depth = maximum = 1
            while i < n and depth:
                if text.startswith('/-', i):
                    depth += 1; maximum = max(maximum, depth); i += 2
                elif text.startswith('-/', i):
                    depth -= 1; i += 2
                else:
                    i += 1
            require(depth == 0, 'Unterminated block comment')
            comments.append({'start': start, 'end': i, 'kind': 'block', 'nested_depth': maximum})
            continue
        if any(text.startswith(prefix, i) for prefix in ('s!"', 'm!"', 'f!"')):
            raise ValueError('Interpolated strings deliberately unsupported')
        if text[i] == '«':
            end = text.find('»', i + 1)
            require(end >= 0, 'Unterminated quoted identifier')
            i = end + 1; tokens.append(('quoted_identifier', text[start:i], start, i)); continue
        if text[i] == 'r' and (i == 0 or not word(text[i-1])):
            j = i + 1
            while j < n and text[j] == '#': j += 1
            if j < n and text[j] == '"':
                ending = '"' + '#' * (j-i-1)
                end = text.find(ending, j+1)
                require(end >= 0, 'Unterminated raw string')
                i = end + len(ending); tokens.append(('raw_string', text[start:i], start, i)); continue
        if text[i] == '"':
            i += 1
            while i < n:
                if text[i] == '\\':
                    require(i+1 < n, 'Unterminated string escape'); i += 2
                elif text[i] == '"':
                    i += 1; break
                else:
                    i += 1
            else:
                raise ValueError('Unterminated string')
            tokens.append(('string', text[start:i], start, i)); continue
        if text[i] == "'" and (i == 0 or not word(text[i-1])):
            j = i + 1
            if j < n and text[j] == '\\':
                j += 2
                if j < n and text[j] == "'":
                    i = j+1; tokens.append(('char', text[start:i], start, i)); continue
            elif j+1 < n and text[j+1] == "'" and text[j] != '\n':
                i = j+2; tokens.append(('char', text[start:i], start, i)); continue
        if word(text[i]):
            i += 1
            while i < n and word(text[i]): i += 1
            tokens.append(('word', text[start:i], start, i)); continue
        i += 1
        while i < n and not text[i].isspace() and not word(text[i]) and text[i] not in '"«' and not text.startswith(('--', '/-'), i):
            i += 1
        tokens.append(('symbol', text[start:i], start, i))
    return tokens, comments


def token_layout(text, tokens):
    starts = [0] + [i+1 for i, c in enumerate(text) if c == '\n']
    rows = []
    seen = set()
    for _, _, begin, _ in tokens:
        line = bisect_right(starts, begin)-1
        if line not in seen:
            seen.add(line)
            rows.append({'line': line+1, 'column_codepoints': begin-starts[line],
                         'prefix_utf8_hex': text[starts[line]:begin].encode().hex()})
    return rows


def deletion_plan(text, tokens, comments, protected):
    keep = [True] * len(text)
    retained_comments = []
    for idx, comment in enumerate(comments):
        a, b = comment['start'], comment['end']
        after = text[b:text.find('\n', b) if text.find('\n', b) >= 0 else len(text)]
        # Keep a comment preceding code on its closing physical line: deleting
        # it could move that token's absolute/relative indentation to the left.
        shares_suffix_code = bool(after.strip()) and not after.lstrip().startswith('--')
        boundary_fusion = a > 0 and b < len(text) and not text[a-1].isspace() and not text[b].isspace()
        if idx in protected or shares_suffix_code or boundary_fusion:
            retained_comments.append({'index': idx, 'protected': idx in protected, 'layout_or_fusion': shares_suffix_code or boundary_fusion})
        else:
            keep[a:b] = [False] * (b-a)
    # Preserve the exact intake import line. It is part of the original header.
    header_end = text.find('\n') + 1
    require(text[:header_end] == 'import ContractTensor\n', 'Unexpected intake header')
    protected_chars = set(range(header_end))
    for idx in protected:
        c = comments[idx]; protected_chars.update(range(c['start'], c['end']))
    for kind, _, a, b in tokens:
        if kind in ('string', 'raw_string', 'quoted_identifier', 'char'):
            protected_chars.update(range(a, b))
    indices = [i for i, yes in enumerate(keep) if yes]
    survivors = ''.join(text[i] for i in indices)
    offset = 0
    for line in survivors.splitlines(keepends=True):
        original_indices = indices[offset:offset+len(line)]
        if not line.strip() and not any(i in protected_chars for i in original_indices):
            for i in original_indices: keep[i] = False
        offset += len(line)
    return keep, retained_comments


def materialize(text, keep):
    original = text.encode()
    char_bytes = [0]
    for c in text: char_bytes.append(char_bytes[-1] + len(c.encode()))
    draft = ''.join(c for c, yes in zip(text, keep) if yes).encode()
    removed, offset, i = [], 0, 0
    while i < len(text):
        yes, end = keep[i], i+1
        while end < len(text) and keep[end] == yes: end += 1
        a, b = char_bytes[i], char_bytes[end]
        if yes:
            offset += b-a
        else:
            removed.append({'original_start_byte': a, 'original_end_byte': b, 'draft_offset_byte': offset,
                            'removed_bytes_base64': base64.b64encode(original[a:b]).decode()})
        i = end
    # Reconstruct original bytes using only the draft and exact deletion ledger.
    rebuilt, at = bytearray(), 0
    for edit in removed:
        rebuilt.extend(draft[at:edit['draft_offset_byte']]); at = edit['draft_offset_byte']
        rebuilt.extend(base64.b64decode(edit['removed_bytes_base64']))
    rebuilt.extend(draft[at:])
    require(bytes(rebuilt) == original, 'Exact reverse mapping failed')
    return draft, removed


def analyze(text, protected):
    before, comments = scan(text)
    keep, retained_comments = deletion_plan(text, before, comments, protected)
    draft, removed = materialize(text, keep)
    after, _ = scan(draft.decode())
    require([(k, v) for k, v, _, _ in before] == [(k, v) for k, v, _, _ in after], 'Conservative token partition changed')
    old_layout, new_layout = token_layout(text, before), token_layout(draft.decode(), after)
    require([(x['column_codepoints'], x['prefix_utf8_hex']) for x in old_layout] == [(x['column_codepoints'], x['prefix_utf8_hex']) for x in new_layout], 'A nonempty token line changed relative indentation/prefix')
    for idx in protected:
        c = comments[idx]
        require(all(keep[c['start']:c['end']]), 'Protected intake/notice bytes removed')
    return draft, removed, {'bytes': len(draft), 'saved_bytes': len(text.encode())-len(draft),
        'source_sha256': sha(text.encode()), 'draft_sha256': sha(draft), 'token_count': len(before),
        'token_sequence_sha256': sha(encode([(k, v) for k, v, _, _ in before])),
        'token_sequence_equal': True, 'nonempty_token_line_count': len(old_layout),
        'relative_indentation_and_prefix_equal': True, 'retained_comments': retained_comments,
        'line_map': [{'original_line': a['line'], 'draft_line': b['line'], 'column_codepoints': a['column_codepoints']} for a, b in zip(old_layout, new_layout)],
        'exact_reverse_mapping': True, 'lean_frontend_compile_gate': 'NOT_RUN'}


def self_check():
    fixture = 'import ContractTensor\n\n/- outside /- nested -/ tail -/\ndef x := "literal /- -- \\\" quoted" -- trailing\ndef «name/-literal-/» := r#"raw -- /- \""#\ndef y := x\'\n'
    tokens, comments = scan(fixture)
    require(len(comments) == 2 and comments[0]['nested_depth'] == 2, 'Nested/string fixture misclassified')
    analyze(fixture, set())
    # Preserve prefix-comment indentation and token separation without insertion.
    inline = 'import ContractTensor\n  /-prefix-/ def a := foo/-sep-/bar\n\n'
    _, _, result = analyze(inline, set())
    require(len(result['retained_comments']) == 2, 'Conservative inline guard failed')
    try: scan('s!"interpolation {x}"')
    except ValueError: pass
    else: raise ValueError('Unsupported interpolation was not rejected')
    return {'nested_block_comment': True, 'escaped_and_raw_strings': True, 'quoted_identifier': True,
            'identifier_apostrophe': True, 'inline_indent_and_fusion_guard': True,
            'unsupported_interpolation_rejected': True, 'exact_reverse_mapping': True}


def main():
    source = SOURCE.read_bytes()
    require(sha(source) == SOURCE_SHA and len(source) == 254877, 'Jam17 frozen source changed')
    patch = PATCH.read_bytes()
    text = source.decode('utf-8')
    tokens, comments = scan(text)
    notices = [i for i, c in enumerate(comments) if any(marker in text[c['start']:c['end']] for marker in ('MIT License', 'Copyright', 'Third-party notices', 'REUSE.toml'))]
    distinct, seen = set(), set()
    for i in notices:
        c = comments[i]; h = sha(text[c['start']:c['end']].encode())
        if h not in seen: distinct.add(i); seen.add(h)
    results = {}
    drafts = {}
    for name, protected in (('preserve_all_notices', set(notices)), ('preserve_each_distinct_notice', distinct), ('unprotected_mechanical_upper_bound', set())):
        draft, edits, result = analyze(text, protected)
        result['protected_comment_indices'] = sorted(protected)
        result['target_saved_12000_met'] = result['saved_bytes'] >= 12000
        result['with_11068_added_bytes'] = len(draft)+11068
        result['with_11068_under_256000'] = len(draft)+11068 <= 256000
        if name != 'preserve_each_distinct_notice':
            result.pop('line_map')  # Only the actual draft needs a full line map.
        results[name] = result
        drafts[name] = (draft, edits)
    safe_draft, edits = drafts['preserve_each_distinct_notice']
    draft_path = HERE / 'Jam17-comments-emptylines-draft.lean.txt'
    draft_path.write_bytes(safe_draft)
    (HERE / 'inverse-deletions.json').write_bytes(encode({'status': 'NOT_RUN', 'source_sha256': SOURCE_SHA,
        'draft_sha256': sha(safe_draft), 'policy': 'preserve_each_distinct_notice', 'edits': edits,
        'scope': 'Only deletion; restore exact original bytes from draft plus ledger. No candidate or Lean acceptance.'}))
    receipt = {'status': 'PASS_LOCAL_LEXICAL_CHECKS_ONLY', 'at_utc': datetime.now(timezone.utc).isoformat(),
        'source': SOURCE.relative_to(ROOT).as_posix(), 'source_sha256': SOURCE_SHA, 'source_bytes': len(source),
        'existing_pruning_patch': PATCH.relative_to(ROOT).as_posix(), 'existing_pruning_patch_sha256': sha(patch),
        'existing_patch_deletes_declarations': True, 'existing_patch_applied': False,
        'existing_patch_removed_declaration_names': re.findall(r'^-(?:private\s+)?(?:theorem|def|abbrev|opaque)\s+([^\s(:{]+)', patch.decode(), re.M),
        'comment_count': len(comments), 'comment_bytes': sum(len(text[c['start']:c['end']].encode()) for c in comments),
        'comment_inventory': [{'index': i, 'kind': c['kind'], 'start_line': text[:c['start']].count('\n')+1,
            'end_line': text[:c['end']].count('\n')+1, 'bytes': len(text[c['start']:c['end']].encode()),
            'sha256': sha(text[c['start']:c['end']].encode()), 'notice': i in notices} for i, c in enumerate(comments)],
        'notice_comment_indices': notices, 'distinct_notice_count': len(distinct),
        'literal_token_counts': {kind: sum(t[0] == kind for t in tokens) for kind in ('string', 'raw_string', 'quoted_identifier', 'char')},
        'self_checks': self_check(), 'policies': results, 'draft': draft_path.name,
        'draft_status': 'NOT_RUN_NOT_A_CANDIDATE', 'selection_performance_input_read': False,
        'source_and_patch_bytes_unchanged': sha(SOURCE.read_bytes()) == SOURCE_SHA and PATCH.read_bytes() == patch,
        'scope': 'Conservative local lexer and exact deletion/reverse mapping only. No definitions/theorems/token text/namespace/options/import changed. No Lean, gate, Git, CI, candidate generation or submission.'}
    (HERE / 'budget-receipt.json').write_bytes(encode(receipt))
    print(json.dumps({'source_sha256': SOURCE_SHA, 'comment_count': len(comments), 'comment_bytes': receipt['comment_bytes'], 'notice_count': len(notices), 'distinct_notices': len(distinct), 'policies': {k: {j: v[j] for j in ('bytes', 'saved_bytes', 'target_saved_12000_met', 'with_11068_added_bytes', 'with_11068_under_256000')} for k, v in results.items()}, 'self_checks': receipt['self_checks']}, ensure_ascii=False))


if __name__ == '__main__':
    main()
