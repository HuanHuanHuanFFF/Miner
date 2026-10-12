"""Exact tree-prefix first total-time pair, current snapshot and same-source controls."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
NAME = 'r26-b-552-tree-prefix'
CAPTURE = 'evidence/round26/extension4h/official-start/pareto-pages.json'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def entry(name, path, control=True, formal=None):
    folder = ROOT/path
    e = {'name': name, 'path': path, 'control': control, 'anchor': 'public552',
         'hashes': {f: sha((folder/f).read_bytes()) for f in ('parse.rs', 'Parse.lean')}}
    if formal:
        e['formal_id'] = str(formal)
    if not control:
        e.update(comparison_baseline='public552', native_decode_reference='public552', expected_equivalent_to='public552')
    return e


def main():
    folder = ROOT/'evidence/round26/route-b'
    out = folder/'b23-tree-prefix-screen.json'
    assert not out.exists()
    native = ROOT/'evidence/round26/38216961738/quality-b21-native/diagnostics/r13-encoder/encoder.json'
    data = json.loads(native.read_bytes())
    rows = {r['candidate']: {} for r in data['rows']}
    for r in data['rows']:
        rows[r['candidate']][r['file']] = r
    assert len(rows[NAME]) == len(rows['public552']) == 28
    keys = ['input_sha256', 'tokens_sha256', 'output_sha256', 'output_bytes']
    assert all(all(r[k] == rows['public552'][file][k] for k in keys) for file, r in rows[NAME].items())
    entries = [entry('probe3', 'candidates/probe3', formal=427), entry('r3-432-fast3', 'candidates/r3-432-fast3', formal=453),
               entry('public432', 'references/round3-public-432', formal=432),
               entry('public552', 'references/round24-public-552', formal=552),
               entry('public552-shadow', 'references/round24-public-552'),
               entry(NAME, 'candidates/'+NAME, False),
               entry(NAME+'-shadow', 'candidates/'+NAME)]
    assert data['source_hashes'][NAME] == entries[-2]['hashes']
    names = [e['name'] for e in entries]
    spec = {'entries': entries, 'snapshot_pages': CAPTURE, 'screen_blocks': 2, 'refine_blocks': 0, 'shortlist': 0,
            'gate_candidates': [], 'gate_limit': 0, 'extract_candidates': [NAME], 'retain_extracted_lean': True,
            'synthetic_validation': False, 'synthetic_reference_candidates': [], 'research_synthetic_candidates': [],
            'cpu_diagnostics': False, 'native_only': False, 'native_encoder': False, 'native_encoder_references': [],
            'r18_role': 'discovery', 'r26_mode': 'standard', 'r26_expected_candidates': 1,
            'screen_orders': [names, names[::-1]],
            'description': 'B23 exact U16 tree-prefix consumer first original11rep total-encoder pair, two reversed blocks; original552 primary/shadow plus candidate same-source control. Exact extraction before timing and existing finite equivalence/decode, no fullproof. New128KiB and every read/write included. Latest29870, discovery not stable share.',
            'r26_required_files': {}}
    deps = ['scripts/r26-b-tree-pair-plan.py', 'scripts/r26-b-preflight-draft.py', CAPTURE,
            'evidence/round26/route-b/b23-tree-pair-predeclared.md', native.relative_to(ROOT).as_posix()]
    spec['r26_required_files'] = {p: sha((ROOT/p).read_bytes()) for p in deps}
    out.write_text(json.dumps(spec, indent=2)+'\n')
    print(json.dumps({'draft': out.relative_to(ROOT).as_posix(), 'hashes': entries[-2]['hashes'], 'entries': len(entries), 'blocks': 2}))


if __name__ == '__main__':
    main()
