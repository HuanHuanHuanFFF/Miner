"""Freeze a small fast3 comparison with independent candidate sources."""
from pathlib import Path
import argparse, hashlib, json, os, re

ROOT = Path(__file__).resolve().parents[1]

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('batch')
    ap.add_argument('candidates', nargs='+')
    ap.add_argument('--extract', action='store_true')
    ap.add_argument('--gate', action='store_true')
    ap.add_argument('--blocks', type=int, choices=[1,2,3,4], default=2)
    args = ap.parse_args()
    assert re.fullmatch(r'[a-z0-9-]{1,48}', args.batch)
    assert 1 <= len(args.candidates) <= 3 and len(args.candidates) == len(set(args.candidates))
    assert all(re.fullmatch(r'r12-fast-[a-z0-9-]+', n) for n in args.candidates)
    parent = json.loads((ROOT/'evidence/round11/fast-l.json').read_bytes())
    entries = [e.copy() for e in parent['entries'] if e['name'] in ('probe3','r3-432-fast3','public432','fast-shadow')]
    assert len(entries) == 4
    manifests = {name: json.loads((ROOT/'candidates'/name/'manifest.json').read_bytes()) for name in args.candidates}
    if any(m.get('formal_anchor_id')=='507' for m in manifests.values()):
        ref = ROOT/'references/round12-public-507'
        entries.append({'name':'public507','path':ref.relative_to(ROOT).as_posix(),'control':True,
            'anchor':'public507','formal_id':'507','hashes':{f:hashlib.sha256((ref/f).read_bytes()).hexdigest()for f in ('parse.rs','Parse.lean')}})
        shadow = entries[-1].copy();shadow.update(name='pc507-shadow');shadow.pop('formal_id')
        entries.append(shadow)
    for name,manifest in manifests.items():
        baseline = manifest.get('comparison_baseline')
        if baseline and baseline.startswith('r12-') and not any(e['name']==baseline for e in entries):
            path=ROOT/'candidates'/baseline
            entries.append({'name':baseline,'path':path.relative_to(ROOT).as_posix(),'control':True,
                'anchor':'public507','hashes':{f:hashlib.sha256((path/f).read_bytes()).hexdigest()for f in('parse.rs','Parse.lean')}})
    for name in args.candidates:
        path = ROOT/'candidates'/name
        anchor = 'public507' if manifests[name].get('formal_anchor_id')=='507' else 'r3-432-fast3'
        baseline = manifests[name].get('comparison_baseline',anchor)
        entry = {'name': name, 'path': path.relative_to(ROOT).as_posix(), 'control': False,
            'anchor': anchor, 'anchor_scope': 'Declared parent structural derivative; transfer hypothesis only',
            'comparison_baseline': baseline,
            'hashes': {f: hashlib.sha256((path/f).read_bytes()).hexdigest() for f in ('parse.rs','Parse.lean')}}
        if manifests[name].get('native_relation')=='decode_only':
            entry['native_decode_reference'] = anchor
        else:
            entry['expected_equivalent_to'] = baseline
        entries.append(entry)
    spec = {'entries': entries, 'snapshot_pages': 'evidence/round12/official-start-2/pareto-pages.json',
        'screen_blocks': args.blocks, 'refine_blocks': 0, 'shortlist': len(args.candidates),
        'gate_candidates': args.candidates if args.gate else [], 'gate_limit': len(args.candidates) if args.gate else 0,
        'extract_candidates': args.candidates if args.extract else [], 'retain_extracted_lean': True,
        'synthetic_validation': True, 'synthetic_reference_candidates': [], 'research_synthetic_candidates': args.candidates,
        'cpu_diagnostics': args.extract, 'cpu_diagnostic_candidates': args.candidates + ['r3-432-fast3'],
        'description': 'R12 bounded structural experiments; paired total-compression axes and same-source shadow.',
        'selection_policy': 'Initial screening is discovery only. Frozen sources require a fresh runner confirmation before promotion. Family projections do not establish private admission or actual payment.'}
    target = ROOT/'evidence/round12'/f'{args.batch}.json'
    assert not target.exists()
    target.write_text(json.dumps(spec, indent=2)+'\n', encoding='utf-8')
    os.environ['ROUND4_SPEC_DIR'] = 'evidence/round12'
    from round4 import validate
    validate(args.batch)
    print(json.dumps({'batch':args.batch,'entries':len(entries),'candidate_hashes':{e['name']:e['hashes']for e in entries if not e['control']}}))

if __name__ == '__main__':
    main()
