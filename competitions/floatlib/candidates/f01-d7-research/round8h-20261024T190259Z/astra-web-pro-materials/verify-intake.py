"""Verify intake identities and source claims; never invoke Lean or benchmarks."""
import hashlib
import json
import re
import time
from datetime import datetime, timezone
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent
ROOT = ROUND.parents[4]


def uncomment(text):
    out, i, depth = [], 0, 0
    while i < len(text):
        if text[i:i + 2] == '/-':
            depth += 1
            out.extend('  ')
            i += 2
        elif depth and text[i:i + 2] == '-/':
            depth -= 1
            out.extend('  ')
            i += 2
        elif not depth and text[i:i + 2] == '--':
            end = text.find('\n', i)
            end = len(text) if end < 0 else end
            out.extend(' ' * (end - i))
            i = end
        else:
            out.append(text[i] if not depth or text[i] == '\n' else ' ')
            i += 1
    assert depth == 0
    return ''.join(out)


def declarations(text):
    code = uncomment(text)
    frames, prefix, offset, found = [], '', 0, {}
    for line in code.splitlines(keepends=True):
        ns = re.match(r'^namespace\s+([A-Za-z0-9_.]+)', line)
        if ns:
            frames.append(('namespace', prefix))
            prefix = '.'.join(x for x in (prefix, ns.group(1)) if x)
        elif re.match(r'^section(?:\s|$)', line):
            frames.append(('section', prefix))
        elif re.match(r'^end(?:\s|$)', line):
            assert frames, line
            _, prefix = frames.pop()
        decl = re.match(r'^(private\s+)?theorem\s+([A-Za-z0-9_\x27.]+)', line)
        if decl:
            end = re.search(r':=\s*by\b', code[offset:])
            assert end is not None
            full = '.'.join(x for x in (prefix, decl.group(2)) if x)
            found[full] = {
                'statement': ' '.join(code[offset:offset + end.start()].split()),
                'private': bool(decl.group(1)),
                'line': text[:offset].count('\n') + 1,
            }
        offset += len(line)
    assert not frames
    return found, code


def first_definition(text, name):
    start = re.search(r'(?m)^def ' + name + r'\b', text).start()
    return text[start:text.index('\n\n', start)]


def main():
    started = time.perf_counter()
    raw_rows = []
    for topic in ['common-rounding', 'integer-mul']:
        intake = json.loads((HERE / topic / 'intake.json').read_text(encoding='utf-8-sig'))
        for item in intake['files']:
            e_path, branch_path = Path(item['e_path']), Path(item['branch_path'])
            e, branch = e_path.read_bytes(), branch_path.read_bytes()
            assert e == branch and hashlib.sha256(branch).hexdigest() == item['sha256']
            raw_rows.append({'name': item['name'], 'bytes': len(branch), 'sha256': item['sha256'], 'E_equals_branch': True})
    original_algebra = (ROUND / 'astra-exponent-shift-algebra-draft.lean').read_text()
    packing = original_algebra[:original_algebra.index('\ntheorem translated_nat ')]
    original = packing + '\nend Submission.R14ExponentAlgebra\n' + (
        ROUND / 'astra-raw-exponent-shift-general.lean').read_text() + '\n' + (
        ROUND / 'astra-general-integer-round-shape-draft.lean').read_text()
    repaired_path = HERE / 'common-rounding/originals/R14_common_rounding_repaired.lean'
    repaired = repaired_path.read_text()
    old, _ = declarations(original)
    new, code = declarations(repaired)
    assert len(old) == 13
    mismatches = [k for k in old if k not in new or old[k]['statement'] != new[k]['statement']]
    assert not mismatches, mismatches
    definition_matches = {}
    shape = (ROUND / 'astra-general-integer-round-shape-draft.lean').read_text()
    for name in ['roundedMantissa', 'carry', 'normalized']:
        definition_matches[name] = first_definition(shape, name) == first_definition(repaired, name)
        assert definition_matches[name]
    forbidden = re.findall(r'\b(?:sorry|admit|axiom|unsafe|extern|implemented_by|native_decide|run_elab)\b|#eval', code)
    assert not forbidden
    section_variables = re.findall(r'(?m)^variable\b.*', code)
    assert not section_variables
    header = b'import ContractTensor' + bytes([10])
    rb = repaired_path.read_bytes()
    assert rb.startswith(header)
    parent_path = ROOT / 'competitions/floatlib/candidates/f01-r14-dev-compact-base/Kernel.lean'
    parent = parent_path.read_bytes()
    assert hashlib.sha256(parent).hexdigest() == '3c6af73f9d679e9831ac8c4abb9f0e6d41b61718301dd045bedd2402e980632a'
    one_lf, two_lf = parent + b'\n' + rb[len(header):], parent + b'\n\n' + rb[len(header):]
    assert len(one_lf) == 247640 and len(two_lf) == 247641
    assert len(re.findall(r'(?m)^import\b', uncomment(two_lf.decode()))) == 1
    assert time.perf_counter() - started < 2.0
    result = {
        'at_utc': datetime.now(timezone.utc).isoformat(), 'raw_files': raw_rows,
        'all_13_original_public_statements_textually_equal': True,
        'original_shape_definitions_exact': definition_matches,
        'new_declarations': [k for k in new if k not in old],
        'lexical_forbidden_hits': forbidden, 'section_variable_declarations': section_variables,
        'import_line_bytes_removed': len(header),
        'in_memory_composition_previews': [
            {'separator': 'one extra LF', 'bytes': len(one_lf), 'sha256': hashlib.sha256(one_lf).hexdigest()},
            {'separator': 'two extra LF matching Pro byte count', 'bytes': len(two_lf), 'sha256': hashlib.sha256(two_lf).hexdigest()},
        ],
        'candidate_created_or_Lean_run': False,
        'limits': 'Text/byte checks are not Lean elaboration, kernel replay, axiom audit, runtime integration or performance. New machine Int64 alignment and primitive bridge remain separate obligations.',
        'elapsed_seconds': time.perf_counter() - started,
        'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    }
    (HERE / 'intake-verification.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(result))


if __name__ == '__main__':
    main()
