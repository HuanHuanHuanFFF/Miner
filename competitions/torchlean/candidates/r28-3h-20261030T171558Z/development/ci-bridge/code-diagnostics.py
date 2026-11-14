"""Derived generated-C counters only; no upstream C body is published."""
import hashlib
import re


def inspect(raw, tokens):
    text = raw.decode('utf-8')
    pattern = re.compile(r'(?m)^(?P<header>[A-Za-z_][^\n;{}]*\b(?P<symbol>(?:l_|lp_competition_)Submission_[A-Za-z0-9_]+)\([^\n;{}]*\))\s*\{')
    rows = []
    for match in pattern.finditer(text):
        if not any(token in match['symbol'] for token in tokens):
            continue
        start = match.end() - 1
        position, depth = start + 1, 1
        while depth and position < len(text):
            depth += (text[position] == '{') - (text[position] == '}')
            position += 1
        assert depth == 0
        body = text[start:position]
        rows.append({
            'symbol': match['symbol'],
            'body_bytes': len(body.encode()),
            'body_sha256': hashlib.sha256(body.encode()).hexdigest(),
            'if_count': len(re.findall(r'\bif\s*\(', body)),
            'lexical_star_count': body.count('*'),
            'encoded_zero_literal_occurrences': body.count('144115188075855872'),
            'zero_literal_hex_occurrences': body.lower().count('0x200000000000000'),
            'uint64_multiply_calls': body.count('lean_uint64_mul'),
            'constructor_alloc_calls': body.count('lean_alloc_ctor'),
            'uint64_box_calls': body.count('lean_box_uint64'),
            'reference_increment_substring_count': body.count('lean_inc'),
            'reference_decrement_substring_count': body.count('lean_dec'),
        })
    missing = [token for token in tokens if not any(token in row['symbol'] for row in rows)]
    return {
        'state': 'INCOMPLETE_MISSING_SYMBOLS' if missing else 'COMPLETE_DERIVED_C_COUNTERS',
        'missing_symbol_tokens': missing,
        'generated_C_sha256': hashlib.sha256(raw).hexdigest(),
        'requested_symbol_tokens': tokens,
        'functions': rows,
        'scope': 'GENERATED_C_MECHANISM_DIAGNOSTIC_ONLY; counts are not optimized assembly, native timing, or proof',
        'publication': 'Only function names, hashes, and derived counts; no generated C bodies',
    }
