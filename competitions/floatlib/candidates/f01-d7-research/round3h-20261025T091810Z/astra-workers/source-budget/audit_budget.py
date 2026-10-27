"""Read only exact R16 sources; report source capacity without producing a candidate."""
from pathlib import Path
from hashlib import sha256
from collections import Counter
from datetime import datetime, timezone
from time import monotonic
import json, re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[6]
ROUND = HERE.parents[1]
SOURCES = {
    'b2': (ROOT / 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean', '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'),
    'a4b2': (ROUND / 'astra-workers/matrix-architecture/Kernel-a4b2.lean', '5f53a9300f6554a80a68fcee5fda84dc4af063706c0b928be8ec9d7f1b81213c'),
    'repack': (ROUND / 'astra-workers/scalar-representation/Kernel-native-repack.lean', 'c972fd72694d4d7db4660d2dbcd640d766d013d58bd9c9a27a6c68d47010b7ac'),
}
ATTRIBUTION = re.compile(r'copyright|license|authors?\s*[:：]|SPDX|https?://|来源|作者|许可', re.I)
CMD = re.compile(r'(?m)^(?:@\[[^\n]*\]\s*)?(?:(?:private|protected|noncomputable|unsafe|partial)\s+)*(?:theorem|lemma|def|abbrev|opaque|instance|structure|inductive|class|namespace|section|end|open|variable|variables|attribute|set_option|local|scoped|notation|syntax|macro|elab|initialize|export|include|omit|import)\b')
DECL = re.compile(r"(?m)^(?P<attr>@\[[^\n]*\]\s*)?(?P<modifier>(?:(?:private|protected|noncomputable|unsafe|partial)\s+)*)(?P<kind>theorem|lemma|def|abbrev|opaque|instance|structure|inductive|class)\s+(?P<name>[A-Za-z_][A-Za-z0-9_'.]*)")
IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_']*(?:\.[A-Za-z_][A-Za-z0-9_']*)*")
PROTECTED = {'add', 'mul', 'sum', 'bmm', 'add_spec', 'mul_spec', 'sum_spec', 'bmm_spec'}

def digest(b): return sha256(b).hexdigest()

def declaration_rows(text, masked):
    suffix_counts = Counter()
    for token in IDENT.findall(masked):
        parts = token.split('.')
        for j in range(len(parts)): suffix_counts['.'.join(parts[j:])] += 1
    boundaries = [m.start() for m in CMD.finditer(masked)] + [len(text)]
    dead = []
    for d in DECL.finditer(masked):
        if d['kind'] not in ('theorem', 'lemma') or d['attr']: continue
        name = d['name']; leaf = name.rsplit('.', 1)[-1]
        if leaf in PROTECTED or suffix_counts[leaf] != 1: continue
        hi = next(x for x in boundaries if x > d.start())
        piece = text[d.start():hi]
        if ATTRIBUTION.search(piece): continue
        dead.append(dict(name=name, kind=d['kind'], modifier=d['modifier'].strip(),
                         line=text.count('\n', 0, d.start())+1,
                         end_line=text.count('\n', 0, hi)+1,
                         start=d.start(), end=hi, bytes=len(piece.encode()),
                         sha256=digest(piece.encode()), explicit_leaf_occurrences=1,
                         review='STATIC_ONLY; plain theorem, no explicit reference; inspect exact slice before deletion'))
    return dead

def remove_ranges(text, rows):
    pieces = []; at = 0
    for r in rows:
        pieces.append(text[at:r['start']]); at = r['end']
    pieces.append(text[at:]); return ''.join(pieces)

def lex(text):
    masked = list(text); spans = []; literals = []; i = 0
    while i < len(text):
        start = i
        if text.startswith('--', i):
            end = text.find('\n', i); i = len(text) if end < 0 else end
            spans.append((start, i, 'line'))
        elif text.startswith('/-', i):
            depth = 1; i += 2
            while depth:
                assert i < len(text), 'unclosed comment'
                if text.startswith('/-', i): depth += 1; i += 2
                elif text.startswith('-/', i): depth -= 1; i += 2
                else: i += 1
            spans.append((start, i, 'block'))
        elif text[i] == '"':
            i += 1
            while i < len(text):
                if text[i] == '\\': i += 2
                elif text[i] == '"': i += 1; break
                else: i += 1
            else: raise AssertionError('unclosed string')
            literals.append((start, i, 'string'))
        elif text[i] == '«':
            end = text.find('»', i + 1); assert end >= 0
            i = end + 1; literals.append((start, i, 'quoted_identifier'))
        else:
            i += 1; continue
        for k in range(start, i):
            if text[k] not in '\r\n': masked[k] = ' '
    return ''.join(masked), spans, literals

def inspect(key, path, expected):
    raw = path.read_bytes(); assert digest(raw) == expected, (key, digest(raw))
    text = raw.decode('utf-8'); masked, comments, literals = lex(text)
    assert not re.search(r'\br#+"', masked), 'raw strings require separate review'
    # Literals are preserved; this source-specific analysis never rewrites Lean layout.
    removable = []; kept = []
    for lo, hi, kind in comments:
        begin = text.rfind('\n', 0, lo) + 1
        end = text.find('\n', hi); end = len(text) if end < 0 else end
        own = not text[begin:lo].strip() and not text[hi:end].strip()
        row = dict(start=lo, end=hi, line=text.count('\n', 0, lo)+1,
                   end_line=text.count('\n', 0, hi)+1, kind=kind,
                   bytes=len(text[lo:hi].encode()), sha256=digest(text[lo:hi].encode()),
                   recoverable_bytes=len(text[lo:hi].encode()) - text[lo:hi].count('\n'))
        (removable if own and not ATTRIBUTION.search(text[lo:hi]) else kept).append(row)
    at = 0; pieces = []
    for r in removable:
        pieces += [text[at:r['start']], '\n' * text[r['start']:r['end']].count('\n')]
        at = r['end']
    pieces.append(text[at:]); comment_compact = ''.join(pieces)
    assert text.count('\n') == comment_compact.count('\n')
    protected_lines = set()
    for lo, hi, _ in literals + comments:
        protected_lines.update(range(text.count('\n', 0, lo)+1, text.count('\n', 0, hi)+2))
    empty_bytes = 0; trailing_bytes = 0; crlf_bytes = 0
    for n, line in enumerate(text.splitlines(keepends=True), 1):
        if n in protected_lines: continue
        if not line.strip(): empty_bytes += len(line.encode())
        else:
            body = line.rstrip('\r\n'); trailing_bytes += len(body) - len(body.rstrip(' \t'))
            if line.endswith('\r\n'): crlf_bytes += 1
    dead = declaration_rows(text, masked)
    # Explicit attribute application, environment-search tactics and reflection remain exclusions.
    search = re.findall(r'(?<!\w)(?:exact\?|apply\?|simp\?|rw\?|library_search\b|aesop\b|solve_by_elim\b|grind\b|run_tac\b|run_elab\b|mkConst\b|decl_name\b)', masked)
    special = re.findall(r'(?m)^(?:attribute|export|notation|local\s+(?:notation|instance)|macro|syntax|elab|initialize)\b[^\n]*', masked)
    rounds = []; current = text
    for round_n in range(1, 5):
        clean, _, _ = lex(current); rows = declaration_rows(current, clean)
        if not rows: break
        updated = remove_ranges(current, rows)
        rounds.append(dict(round=round_n, parent_sha256=digest(current.encode()),
                           result_sha256=digest(updated.encode()), rows=rows,
                           recovery=len(current.encode())-len(updated.encode())))
        current = updated
    _, current_comments, current_literals = lex(current)
    assert not current_literals, 'whitespace plan reviewed only for sources without literals'
    ranges = []
    for lo, hi, kind in current_comments:
        begin = current.rfind('\n', 0, lo)+1
        end = current.find('\n', hi); end = len(current) if end < 0 else end
        if not current[begin:lo].strip() and not current[hi:end].strip() and not ATTRIBUTION.search(current[lo:hi]):
            ranges.append(dict(start=lo, end=hi))
    # Keep attribution comments byte-for-byte and every nonblank code line's indentation.
    temporary = current
    for r in reversed(ranges):
        piece = temporary[r['start']:r['end']]
        temporary = temporary[:r['start']] + '\n'*piece.count('\n') + temporary[r['end']:]
    _, retained_comments, _ = lex(temporary)
    protected = set()
    for lo, hi, _ in retained_comments:
        protected.update(range(temporary.count('\n',0,lo)+1, temporary.count('\n',0,hi)+2))
    fully_compact = ''.join(line for n,line in enumerate(temporary.splitlines(keepends=True),1)
                            if n in protected or line.strip())
    return dict(path=path.relative_to(ROOT).as_posix(), bytes=len(raw), sha256=digest(raw),
                line_count=text.count('\n'), comment_count=len(comments), literals=literals,
                standalone_comments_recoverable=sum(r['recoverable_bytes'] for r in removable),
                standalone_comment_compact_sha256=digest(comment_compact.encode()),
                removable_comments=removable, kept_comments=kept,
                empty_lines_recoverable_outside_comments_literals=empty_bytes,
                trailing_spaces_recoverable_outside_comments_literals=trailing_bytes,
                crlf_to_lf_recoverable_outside_comments_literals=crlf_bytes,
                plain_unreferenced_theorems=dead,
                plain_unreferenced_theorem_bytes=sum(r['bytes'] for r in dead),
                environment_search_tactics=search, special_commands=special,
                bounded_four_round_pruning=rounds,
                bounded_four_round_theorem_recovery=len(raw)-len(current.encode()),
                bounded_four_round_plus_comment_blank_recovery=len(raw)-len(fully_compact.encode()),
                bounded_four_round_plus_comment_blank_bytes=len(fully_compact.encode()),
                bounded_four_round_plus_comment_blank_sha256=digest(fully_compact.encode()),
                protected_public_names=sorted(PROTECTED),
                exact_compacted_source_emitted=False)

def main():
    start = monotonic(); out = {k: inspect(k, p, h) for k, (p, h) in SOURCES.items()}
    # Minimum common deletion plan: re-evaluate each exact source after the SAME
    # preceding slices are removed. This avoids adding incompatible per-source capacities.
    current = {k:p.read_bytes().decode('utf-8') for k,(p,_) in SOURCES.items()}
    common_rounds = []; common_recovery = 0
    for round_n in range(1,5):
        available = {k:declaration_rows(s, lex(s)[0]) for k,s in current.items()}
        shared = set.intersection(*({r['sha256'] for r in rows} for rows in available.values()))
        if not shared: break
        per_source = {}; recovery = None
        for k, text in current.items():
            rows = [r for r in available[k] if r['sha256'] in shared]
            updated = remove_ranges(text, rows)
            n = len(text.encode())-len(updated.encode())
            assert recovery is None or recovery == n
            recovery = n
            per_source[k] = dict(parent_sha256=digest(text.encode()),result_sha256=digest(updated.encode()),rows=rows)
            current[k] = updated
        common_recovery += recovery
        common_rounds.append(dict(round=round_n, recovery=recovery, cumulative_recovery=common_recovery, sources=per_source))
        if common_recovery >= 10571: break
    result = dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),
                  window_start_utc='2026-10-25T09:54:36Z', task_deadline_utc='2026-10-25T10:05:00Z',
                  scope='Read-only size analysis. No output Kernel, queued source mutation, Lean, CI, or confirmation input/result read.',
                  accounting=dict(tokens='UNKNOWN', cached_input='UNKNOWN', CI_seconds=0),
                  max_kernel_bytes=256000, integration_linear_estimate=266571,
                  required_recovery=10571, sources=out,
                  validation=dict(byte_capacity='VERIFIED_BY_EXACT_SLICE_REPLAY',
                                  combined_size='INFERRED_FROM_LINEAR_ESTIMATE_NOT_CONSTRUCTED',
                                  Lean='NOT_RUN', full_gate='NOT_RUN', actual_combined_bytes='UNKNOWN'),
                  common_plan=dict(state='STATIC_COMMON_PLAIN_THEOREM_DELETION_ONLY_NOT_LEAN_VALIDATED',
                                   recovery=common_recovery, enough_arithmetically=common_recovery>=10571,
                                   linear_estimated_combination_bytes_after=266571-common_recovery,
                                   linear_estimated_headroom=256000-(266571-common_recovery),
                                   rounds=common_rounds,
                                   scope='Identical slice SHA in all three exact sources; every round re-counts all explicit leaf references after only common prior deletions. Preserve public APIs, definitions, attributes, layout, attribution and comments. No merged source constructed.'),
                  elapsed_seconds=monotonic()-start)
    assert result['elapsed_seconds'] < 4.5
    (HERE/'budget.json').write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    print(json.dumps({k:{x:v[x] for x in ('bytes','comment_count','standalone_comments_recoverable','empty_lines_recoverable_outside_comments_literals','plain_unreferenced_theorem_bytes','bounded_four_round_theorem_recovery','bounded_four_round_plus_comment_blank_recovery','environment_search_tactics','special_commands')} for k,v in out.items()}, ensure_ascii=False, indent=2))
    print('plain theorem candidates B2:', [(x['name'],x['bytes'],x['line'],x['end_line']) for x in out['b2']['plain_unreferenced_theorems']])
    print('common plan:', {k:v for k,v in result['common_plan'].items() if k!='rounds'})
    print('common rounds:', [(r['round'],r['recovery'],len(r['sources']['b2']['rows'])) for r in common_rounds])

if __name__ == '__main__': main()
