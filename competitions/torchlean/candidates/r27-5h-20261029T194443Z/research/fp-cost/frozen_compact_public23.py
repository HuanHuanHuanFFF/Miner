"""Owned alias-compaction recipe for exact public23; keeps every declaration.

Uses only aliases already established by the original prelude, outside strings,
comments and directives. Complete kernels/correct remain. Fresh gate required.
Whole reconstructed third-party source is local/private only.
"""
from __future__ import annotations
from datetime import datetime, timezone
import argparse, hashlib, json, re
from pathlib import Path

PIN = '1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
TYPE_ALIASES = {'UInt64': 'ػ', 'UInt32': 'ؼ', 'Nat': 'ٳ', 'Int': 'ٴ',
                'Array': 'ؽ', 'Word': 'δ', 'Bool': 'ف'}
DECL = re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected)\s+)*(?:def|lemma|theorem|structure|abbrev)\s+([\w.'?!]+)")
STOP = re.compile(r"(?m)^(?:(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected|unsafe)\s+)*(?:def|theorem|lemma|structure|abbrev)\b|section\b|end\b|open\b|set_option\b|attribute\b|namespace\b)")
PROOF = re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:(?:private|protected)\s+)*(?:theorem|lemma)\s+[\w.'?!]+")
RUNTIME = re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected|unsafe)\s+)*(?:def|structure|abbrev)\s+([\w.'?!]+)")

def ranges(source, pattern):
    bounds = [m.start() for m in STOP.finditer(source)]
    return [(m, next((v for v in bounds if v > m.start()), len(source))) for m in pattern.finditer(source)]

def runtime_inventory(source):
    return {m.group(1): hashlib.sha256(source[m.start():end].rstrip().encode()).hexdigest()
            for m, end in ranges(source, RUNTIME)}

def masked(source):
    out = list(source)
    i, depth = 0, 0
    while i < len(source):
        if depth:
            if source.startswith('/-', i):
                out[i:i+2] = '  '; depth += 1; i += 2
            elif source.startswith('-/', i):
                out[i:i+2] = '  '; depth -= 1; i += 2
            else:
                if source[i] != '\n': out[i] = ' '
                i += 1
        elif source.startswith('/-', i):
            out[i:i+2] = '  '; depth = 1; i += 2
        elif source.startswith('--', i):
            stop = source.find('\n', i)
            if stop < 0: stop = len(source)
            out[i:stop] = ' ' * (stop-i); i = stop
        elif source[i] == '"':
            out[i] = ' '; i += 1
            while i < len(source):
                if source[i] == '\\':
                    out[i] = ' '; i += 1
                    if i < len(source): out[i] = ' '; i += 1
                elif source[i] == '"':
                    out[i] = ' '; i += 1; break
                else:
                    if source[i] != '\n': out[i] = ' '
                    i += 1
        else:
            i += 1
    assert len(out) == len(source)
    return ''.join(out)

def aliases(prelude):
    groups = re.finditer(r'\bopen\s+([\w.]+)\s+renaming\s+(.+?)(?=\s+open\s+|\s+local\s+notation|\s+local\s+postfix|$)', prelude)
    pairs = {}
    for g in groups:
        for src, dst in re.findall(r"([\w.'?!]+)->([\w'?!]+)", g.group(2)):
            name = g.group(1)+'.'+src
            if name not in pairs or len(dst.encode()) < len(pairs[name].encode()): pairs[name] = dst
    for src, dst in TYPE_ALIASES.items():
        # Type notations must already be declared in the exact original prelude.
        if src == 'Word':
            assert 'Word->δ' in prelude
        else:
            assert f'"{dst}"=>{src}' in prelude
        pairs[src] = dst
    return pairs

def possible_binders(code):
    found = set(DECL.findall(code))
    for pattern in [r"\bgeneralize\s+[^\n]*?=\s*([\w']+)",
                    r"\bcase\s+[\w']+\s+([^\n=]+)=>",
                    r"\b(?:let|have)\s+([\w']+)\s*(?::|:=|←)",
                    r"[({\[]\s*((?:[\w']+\s+)*[\w']+)\s*:",
                    r"\b(?:fun|intro|intros|rename_i)\s+([\w'\s]+)(?==>|;|\n)",
                    r"⟨([\w',\s]+)⟩\s*(?::|:=)"]:
        for m in re.finditer(pattern, code):
            found.update(re.findall(r"[\w']+", m.group(1)))
    return found

def transform(raw, mode='proof'):
    assert hashlib.sha256(raw).hexdigest() == PIN
    source = raw.decode('utf-8'); assert '\r' not in source
    start = source.index('structure Acc')
    code = masked(source)
    bindings = possible_binders(code[start:])
    mapping = aliases(source[:start])
    skipped = {name: alias for name, alias in mapping.items() if alias in bindings}
    mapping = {name: alias for name, alias in mapping.items() if alias not in bindings
               and (mode != 'unicode' or not alias.isascii()) and len(name.encode()) > len(alias.encode())}
    expression = re.compile(r"(?<![\w.'?!])("
                            + '|'.join(re.escape(k) for k in sorted(mapping, key=len, reverse=True))
                            + r")(?![\w.'?!])")
    substitutions = []
    proof_ranges = [(m.start(), end) for m, end in ranges(source, PROOF)]
    for m in expression.finditer(code, start):
        if mode == 'proof' and not any(begin <= m.start() < end for begin, end in proof_ranges): continue
        line_start = code.rfind('\n', 0, m.start())+1
        prefix = code[line_start:m.start()].lstrip()
        if prefix.startswith(('open ', 'namespace ', 'end ', 'local ', 'attribute ', 'set_option ')): continue
        substitutions.append((m.start(), m.end(), m.group(), mapping[m.group()]))
    chunks = []; pos = 0; new_pos = 0; receipt = []
    for begin, end, old, new in substitutions:
        chunks.append(source[pos:begin]); new_pos += begin-pos
        chunks.append(new)
        receipt.append({'old': old, 'new': new, 'old_start': begin,
                        'new_start': new_pos, 'new_end': new_pos+len(new),
                        'saved_bytes': len(old.encode())-len(new.encode())})
        new_pos += len(new); pos = end
    chunks.append(source[pos:]); compact = ''.join(chunks)
    inverse = compact
    for r in reversed(receipt):
        assert inverse[r['new_start']:r['new_end']] == r['new']
        inverse = inverse[:r['new_start']] + r['old'] + inverse[r['new_end']:]
    assert inverse == source
    assert DECL.findall(compact) == DECL.findall(source)
    assert compact.count('theorem correct:Obligation kernels:=') == 1
    assert compact[:start] == source[:start]
    if mode == 'proof': assert runtime_inventory(compact) == runtime_inventory(source)
    return compact.encode(), receipt, skipped

def recipe(raw, submission=23, variant='proof-alias'):
    assert submission == 23 and variant in ['proof-alias', 'all-alias']
    return transform(raw, 'proof' if variant == 'proof-alias' else 'all')[0]

def main():
    p = argparse.ArgumentParser()
    p.add_argument('--source', type=Path, required=True); p.add_argument('--output', type=Path, required=True)
    p.add_argument('--receipt', type=Path, required=True); p.add_argument('--mode', choices=['proof','all','unicode'], default='proof')
    a = p.parse_args(); raw = a.source.read_bytes(); result, changes, skipped = transform(raw, a.mode)
    a.output.parent.mkdir(parents=True, exist_ok=True); a.output.write_bytes(result)
    counts = {}
    for r in changes:
        row = counts.setdefault(r['old'], {'alias': r['new'], 'count': 0, 'saved_bytes': 0})
        row['count'] += 1; row['saved_bytes'] += r['saved_bytes']
    out = {'at_utc': datetime.now(timezone.utc).isoformat(), 'state': 'FULL_CORRECT_PRESERVED_ALIAS_COMPACTION_UNCOMPILED',
      'source_sha256': PIN, 'source_bytes': len(raw), 'candidate_sha256': hashlib.sha256(result).hexdigest(),
      'candidate_bytes': len(result), 'saved_bytes': len(raw)-len(result), 'free_bytes': 256000-len(result),
      'recipe_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(), 'mode': a.mode,
      'declarations_deleted': 0, 'declaration_order_and_names_preserved': True, 'exact_token_inverse_pass': True,
      'runtime_declaration_bytes_equal': runtime_inventory(raw.decode()) == runtime_inventory(result.decode()),
      'possible_shadow_aliases_skipped': skipped, 'replacement_counts': counts,
      'boundaries': ['No proof/definition removed', 'Original prelude and directives unchanged',
         'Only existing aliases used outside comments/strings', 'Binder scan is conservative, not a Lean parser proof',
         'New exact source requires full original12 gate; alias resolution must be confirmed'],
      'publication': 'Owned recipe/receipt only; whole source private'}
    a.receipt.write_text(json.dumps(out, indent=2, ensure_ascii=False), encoding='utf-8')
    print(json.dumps({k:out[k] for k in ['state','candidate_sha256','candidate_bytes','saved_bytes','free_bytes','recipe_sha256']}))

if __name__ == '__main__': main()
