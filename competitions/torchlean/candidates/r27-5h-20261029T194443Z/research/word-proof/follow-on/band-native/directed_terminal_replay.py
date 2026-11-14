"""Finite dyadic terminal checks at new fast-path subnormal/overflow edges."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
OWN = HERE.parents[1]
C = OWN.parent/'board-frontier'


def load(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


f = load(C/'norm_frontier.py', 'r27_band_terminal_formula')
m = load(OWN/'word_model_coverage.py', 'r27_band_terminal_meta')


def main():
    cases = [
        ('positive_nonzero_underflow', 1, 1, 0, 0),
        ('negative_nonzero_underflow', 0x80000001, 1, 0, 0x80000000),
        ('positive_overflow', 0x7f7fffff, 0x7f7fffff, 0, 0x7f800000),
        ('negative_overflow', 0xff7fffff, 0x7f7fffff, 0, 0xff800000),
        ('minimum_subnormal_exact', 1, 0x3f800000, 0, 1),
        ('negative_minimum_subnormal_exact', 0x80000001, 0x3f800000, 0, 0x80000001),
        ('power_of_two_metadata_padding', 0x3f800000, 0x3f800000, 0x3a800000, 0x3f802000)
    ]
    rows = []
    for name, x, w, b, expected in cases:
        ax, aw = m.metadata([x]), m.metadata([w])
        sx, mx, ix = f.fields(x)
        sw, mw, iw = f.fields(w)
        sb, mb, ib = f.fields(b)
        body_base = ax['base'] + aw['base']
        base = min(body_base, ib+126) if mb else body_base
        high = max(ax['upper']+aw['upper'], ib+126) if mb else ax['upper']+aw['upper']
        assert ax['finite'] and aw['finite'] and not ax['reversed'] and not aw['reversed']
        assert aw['span'] <= 6 and high-base <= 58
        body = sx*sw*mx*mw*(1 << (ix+iw-base))
        total = body + sb*mb*(1 << max(0, ib+149-base))
        assert total != 0 and -(1 << 127) <= total < 1 << 127
        observed = f.round_ratio(total, 1, base-298)
        assert observed == expected
        rows.append({'case': name, 'x': x, 'w': w, 'bias': b,
                     'body_base': body_base, 'terminal_base': base,
                     'range': high-base, 'total_is_nonzero': True,
                     'observed_word': observed, 'expected_word': expected,
                     'original_zero_fallback_needed': False})
    result = {'at_utc': datetime.now(timezone.utc).isoformat(),
              'state': 'FINITE_FORMULA_TERMINAL_EDGE_REPLAY_NO_LEAN_NATIVE',
              'cases': rows,
              'scope': 'New band arithmetic permits finite subnormal coefficients that old QPa may reject. Nonzero underflow must keep its sign; it is distinct from exact-zero callback fallback.',
              'limits': 'Original Ybo/YL/YD is reused by the candidate, but this script evaluates the dyadic formula. It does not execute or prove their new connection.',
              'source_hashes': {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in
                               (Path(__file__), HERE/'BandNative.lean.inc', OWN/'word_model_coverage.py', C/'norm_frontier.py')}}
    (HERE/'directed-terminal-replay.json').write_text(json.dumps(result, indent=2), encoding='utf8')
    print(json.dumps({'cases': len(rows), 'word_hex': [f"{r['observed_word']:08x}" for r in rows]}))


if __name__ == '__main__':
    main()
