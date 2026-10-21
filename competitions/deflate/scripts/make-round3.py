"""Generate a predeclared two-sided parameter screen; no correctness claim."""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]


def generate(check=False):
    base = ROOT / 'candidates/probe3'
    assert hashlib.sha256((base / 'parse.rs').read_bytes()).hexdigest() == 'e20ea5a7d2e77821008592faef393855077b9b8ceee244f390a85ac0257e047d'
    assert hashlib.sha256((base / 'Parse.lean').read_bytes()).hexdigest() == '3906aeb259d83d315811629a54d796b514fc3953742063081451c47997b824b7'
    variants = {
        'r3-depth4': {'T_DEPTH': 4, 'P_DEPTH': 4, 'S_DEPTH': 4},
        'r3-depth8': {'T_DEPTH': 8, 'P_DEPTH': 8, 'S_DEPTH': 8},
        'r3-depth16': {'T_DEPTH': 16, 'P_DEPTH': 16, 'S_DEPTH': 16},
        'r3-depth32': {'T_DEPTH': 32, 'P_DEPTH': 32, 'S_DEPTH': 32},
        'r3-lazy8': {'T_DEPTH': 8, 'P_DEPTH': 8, 'S_DEPTH': 8, 'T_LAZY': 32, 'P_LAZY': 32, 'LDEPTH': 4, 'S_LDEPTH': 4, 'NICE': 128},
        'r3-dense16': {'T_DEPTH': 16, 'P_DEPTH': 16, 'S_DEPTH': 16, 'T_LAZY': 32, 'P_LAZY': 32, 'LDEPTH': 4, 'S_LDEPTH': 4, 'INS_MAX': 8, 'TAIL': 2, 'STRIDE': 4, 'NICE': 128},
        'r3-insert8': {'T_DEPTH': 8, 'P_DEPTH': 8, 'S_DEPTH': 8, 'INS_MAX': 8, 'TAIL': 2},
        'r3-fast1': {'T_DEPTH': 1, 'P_DEPTH': 1, 'S_DEPTH': 1, 'H_DEPTH': 1, 'B_DEPTH': 2, 'S_LAZY': 0, 'B_LAZY': 0, 'NICE': 16},
        'r3-fast2': {'T_DEPTH': 2, 'P_DEPTH': 2, 'S_DEPTH': 2, 'S_LAZY': 0, 'B_LAZY': 0, 'INS_MAX': 0, 'BACKTOK': 8},
        'r3-smalltable': {'HB': 14, 'HN': 16384, 'T_DEPTH': 2, 'P_DEPTH': 2, 'S_DEPTH': 2},
        'r3-smalltable1': {'HB': 13, 'HN': 8192, 'T_DEPTH': 1, 'P_DEPTH': 1, 'S_DEPTH': 1},
        'r3-tiny4': {'TF_TDEPTH': 4, 'TF_SDEPTH': 4},
        'r3-tiny8': {'TF_TDEPTH': 8, 'TF_SDEPTH': 8, 'TF_TLAZY': 32, 'TF_SLAZY': 32},
        'r3-tinykeep': {'TF_KL': 1, 'TF_KD': 1, 'TF_BKL': 1, 'TF_BKD': 1},
        'r3-tinyfast': {'TF_INS': 0, 'TF_TAIL': 0, 'TF_BACK': 0, 'TF_FOLD': 0},
        'r3-tinyregular': {'TF_N': 0},
    }
    entries = []
    for name, changes in variants.items():
        text = (base / 'parse.rs').read_text(encoding='utf-8')
        for key, value in changes.items():
            text, n = re.subn(rf'(pub const {key}: (?:usize|u32|i32) = )\d+;', rf'\g<1>{value};', text)
            assert n == 1, key
        dest = ROOT / 'candidates' / name
        files = {'parse.rs': text.encode('utf-8'), 'Parse.lean': (base / 'Parse.lean').read_bytes()}
        if check:
            assert all((dest / n).read_bytes() == data for n, data in files.items())
        else:
            dest.mkdir(exist_ok=True)
            for n, data in files.items():
                (dest / n).write_bytes(data)
        entries.append({'name': name, 'path': str(dest.relative_to(ROOT)).replace('\\', '/'), 'constants': changes,
                        'hashes': {n: hashlib.sha256(data).hexdigest() for n, data in sorted(files.items())}})
    for name in ('round3-speed-bucket16k', 'round3-speed-bucket8k'):
        dest = ROOT / 'candidates' / name
        entries.append({'name': name, 'path': dest.relative_to(ROOT).as_posix(),
                        'hashes': {n: hashlib.sha256((dest / n).read_bytes()).hexdigest() for n in ('parse.rs', 'Parse.lean')}})
    out = ROOT / 'evidence/round3'
    out.mkdir(exist_ok=True)
    config = {'scope': 'public parameter screening before fresh Lean gate; no official submission',
              'base': 'probe3, derived from public submission 261; attribution retained',
              'controls': ['probe3', 'probe2', 'bucket2'], 'candidates': entries,
              'screen_blocks': 2, 'refine_blocks': 2, 'shortlist': 4, 'gate_limit': 0}
    if check:
        assert json.loads((out / 'batch-a.json').read_text()) == config
    else:
        (out / 'batch-a.json').write_text(json.dumps(config, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'generated': len(entries), 'batch': 'evidence/round3/batch-a.json'}))


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    generate(ap.parse_args().check)
