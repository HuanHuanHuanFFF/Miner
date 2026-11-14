"""Inspect saved runner C only; never build or execute a benchmark locally."""
from pathlib import Path
import argparse
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
MARKERS = (
    'R24PortableF64_sumRemaining', 'R24PortableF64_attemptPrepared',
    'R24ExactDotCost_nativeLoop', 'R24ExactDotTiered_native64Loop',
    'R26WordFallback_dotPrepared', 'R26WordFallback_exact',
    'R26RawWord_native64', 'R26RawWord_native128', 'R26RawWord_dotPrepared',
    'R26RawWord_attempt', 'R26WordModel_linear', 'R26WordModel_gemm',
    'R26SharedConv_conv2d', 'R26SharedConv_depthwise',
)

def sha(raw):
    return hashlib.sha256(raw).hexdigest()

def extract(text):
    # Generated Lean C has one-line headers. Require a body, never a prototype.
    regex = re.compile(r'(?m)^(?P<header>[^\n;{}]*\b(?P<symbol>[A-Za-z_][A-Za-z0-9_]*Submission_[A-Za-z0-9_]+)\([^\n;{}]*\))\s*\{')
    found = []
    for match in regex.finditer(text):
        symbol = match['symbol']
        if not any(marker in symbol for marker in MARKERS):
            continue
        at = match.end() - 1
        depth, end = 0, at
        for end in range(at, len(text)):
            if text[end] == '{':
                depth += 1
            elif text[end] == '}':
                depth -= 1
                if depth == 0:
                    end += 1
                    break
        body = text[match.start():end]
        found.append((match['header'], symbol, text.count('\n', 0, match.start()) + 1, body))
    return found

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('c_path', type=Path)
    parser.add_argument('--label', required=True)
    args = parser.parse_args()
    assert re.fullmatch(r'[A-Za-z0-9_-]+', args.label)
    data = args.c_path.read_bytes()
    text = data.decode('utf-8')
    target = HERE / 'c-review' / args.label
    target.mkdir(parents=True, exist_ok=True)
    records = []
    for header, symbol, line, body in extract(text):
        snippet = target / (symbol + '.c.txt')
        snippet.write_text(body + '\n', encoding='utf-8')
        calls = sorted(set(re.findall(r'\b((?:lean_|l_|lp_)[A-Za-z0-9_]+)\s*\(', body)))
        records.append({'symbol': symbol, 'header': header, 'definition_line': line,
                        'definition_sha256': sha(body.encode()),
                        'snippet': snippet.relative_to(HERE).as_posix(),
                        'interface_boxed_wrapper': symbol.endswith('___boxed'),
                        'double_accumulator_in_header': bool(re.search(r'\bdouble\s', header)),
                        'uint64_arguments': len(re.findall(r'\buint64_t\s', header)),
                        'suspicious_calls': [c for c in calls if any(t in c for t in (
                            'box_float', 'box_uint64', 'alloc_ctor', 'alloc_small', 'lean_apply',
                            'nat_mul', 'nat_shift', 'float_of', 'float_to'))],
                        'direct_calls': calls})
    report = {'C_path': str(args.c_path.resolve()), 'C_sha256': sha(data), 'C_bytes': len(data),
              'definitions': records,
              'scope': 'Saved generated C structure only. Selected caller and ASM still require review. '
                       'A whole-file boxed wrapper is not evidence that the actual MAC invokes it.',
              'runtime_speed': 'NOT_INFERRED_FROM_C', 'all_input_proof': 'NOT_PROVED'}
    (target / 'report.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'path': str(target / 'report.json'), 'definitions': len(records)}, indent=2))

if __name__ == '__main__':
    main()
