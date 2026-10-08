"""Freeze a small R11 public comparison with declared family and parent baselines."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re

ROOT = Path(__file__).resolve().parents[1]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('batch')
    ap.add_argument('candidates', nargs='*')
    ap.add_argument('--extract', nargs='*', default=[])
    ap.add_argument('--gate', nargs='*', default=[])
    ap.add_argument('--equivalent', nargs='*', default=[])
    ap.add_argument('--synthetic', nargs='*', default=[])
    ap.add_argument('--gap-diagnostics', action='store_true')
    ap.add_argument('--gap-candidate-checks', action='store_true')
    ap.add_argument('--fast-diagnostics', action='store_true')
    ap.add_argument('--blocks', type=int, choices=[1,2,3,4], default=2)
    args = ap.parse_args()
    assert re.fullmatch(r'[a-z0-9-]{1,48}', args.batch)
    assert len(args.candidates) == len(set(args.candidates))
    assert all(re.fullmatch(r'r11-[a-z0-9-]+', n) for n in args.candidates)
    assert set(args.extract + args.gate + args.synthetic) <= set(args.candidates)
    assert len(args.extract) <= 3 and len(args.synthetic) <= 3
    r10 = json.loads((ROOT/'evidence/round10/confirm-j.json').read_bytes())
    entries = [e.copy() for e in r10['entries'] if e['name'] in
               ('probe3','r3-432-fast3','public432','public361','r10-finder-pipeline-proof')]
    for e in entries:
        e['control'] = True
        e.pop('expected_equivalent_to', None)
    # A source-identical fast control helps diagnose small CPU effects at the
    # currently tight speed-side frontier threshold.
    shadow = next(e for e in entries if e['name']=='r3-432-fast3').copy()
    shadow.update(name='fast-shadow', anchor='r3-432-fast3')
    shadow.pop('formal_id', None)
    entries.append(shadow)
    for name in args.candidates:
        path=ROOT/'candidates'/name
        fast=name.startswith('r11-fast-')
        entries.append({'name':name,'path':path.relative_to(ROOT).as_posix(),
            'control':False,'anchor':'r3-432-fast3' if fast else 'public361',
            'anchor_scope':'fast3 run1 structural derivative' if fast else 'pipeline D-planner derivative; other families need an explicit anchor review',
            'comparison_baseline':'r3-432-fast3' if fast else 'r10-finder-pipeline-proof',
            'hashes':{f:hashlib.sha256((path/f).read_bytes()).hexdigest() for f in ('parse.rs','Parse.lean')}})
    by={e['name']:e for e in entries}
    for pair in args.equivalent:
        n,ref=pair.split('=',1)
        assert n in args.candidates and ref in by and n!=ref
        by[n]['expected_equivalent_to']=ref
    spec={'entries':entries,'snapshot_pages':'evidence/round11/official-start/pareto-pages.json',
        'screen_blocks':args.blocks,'refine_blocks':0,'shortlist':len(args.candidates),
        'gate_candidates':args.gate,'gate_limit':len(args.gate),
        'extract_candidates':args.extract,'retain_extracted_lean':True,
        'synthetic_validation':True,
        'synthetic_reference_candidates':(['r10-finder-pipeline-proof'] if any(not n.startswith('r11-fast-') for n in args.candidates) else []),
        'research_synthetic_candidates':args.synthetic,
        'gap_diagnostics':args.gap_diagnostics,'gap_candidate_checks':args.gap_candidate_checks,
        'fast_diagnostics':args.fast_diagnostics,
        'description':'R11 two-hour frontier research; all source/proof bytes frozen before dispatch.',
        'selection_policy':'Declared same-family formal anchor and same-run parent comparisons; geometric share is conditional, not admission or reward.'}
    target=ROOT/'evidence/round11'/(args.batch+'.json')
    assert not target.exists(), 'Keep frozen specifications immutable'
    target.write_bytes((json.dumps(spec,indent=2)+'\n').encode())
    os.environ['ROUND4_SPEC_DIR']='evidence/round11'
    from round4 import validate
    validate(args.batch)
    print(json.dumps({'batch':args.batch,'entries':len(entries),'candidates':args.candidates,
                      'extract':args.extract,'gate':args.gate,'blocks':args.blocks}))


if __name__=='__main__':
    main()
