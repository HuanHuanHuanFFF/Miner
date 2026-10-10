"""Three bounded SF cost/quality mechanisms, all derived from official #603."""
from pathlib import Path
import importlib.util
import json
import re

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round19'


def main():
    sp = importlib.util.spec_from_file_location('writer', ROOT / 'scripts/build-round18-start.py')
    writer = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(writer)
    parent = ROOT / 'candidates/r18-rf-sf-content-proof1'
    rust, lean = [(parent / f).read_text() for f in ('parse.rs', 'Parse.lean')]
    variants = []
    old = 'let lo=(k/16384).wrapping_mul(16384);let hi=q9_umin(lo.wrapping_add(16384),ts.len());'
    new = 'let lo=k.saturating_sub(512);let hi=q9_umin(k.wrapping_add(512),ts.len());'
    assert rust.count(old) == 1
    variants.append(('r19-sf-local1024', rust.replace(old, new), lean,
        'Limit seam replanning to the 1024-token neighborhood around each crossed 64KiB seam, rather than the entire 16384-token block.',
        'Tests whether boundary-local quality can be retained with substantially less DP work; whole-stream SFcost still rejects a worse plan. This changes scope, not just search depth.'))
    nosearch = rust.replace('let prev=SFprev(input);', 'let prev=Vec::new();')
    nosearch, n = re.subn(r'pub fn SFdepth\(input:&\[u8\]\)->usize\{[^\n]+',
                         'pub fn SFdepth(_input:&[u8])->usize{0}', nosearch)
    assert n == 1 and nosearch != rust
    variants.append(('r19-sf-existing', nosearch, lean,
        'Replan only from existing original matches: skip the full-input predecessor index and additional match-chain search.',
        'Separates the value of retokenizing known matches from discovering new alternatives. Eliminates an entire search stage; quality may be lost.'))
    old = 'if cls >= 4 && cls <= 12 {'
    assert rust.count(old) == 1
    selective = rust.replace(old, 'if cls >= 4 && cls <= 12 && cls != 5 && cls != 7 && cls != 9 {')
    variants.append(('r19-sf-selective', selective, lean,
        'Skip SF for existing content classes 5, 7, 9 (markup and numeric structured text); retain the base parser there.',
        'R18 per-file marginal evidence suggests low quality return for substantial SF cost in these classes. This is a generic content-class test, not a filename route.'))
    entries = []
    for name, source, proof, mechanism, difference in variants:
        entry = writer.write_candidate(name, parent.name, source, proof, mechanism, difference,
            {'parent': 'candidates/r18-rf-sf-content-proof1/manifest.json',
             'formal_reference': 'evidence/round18/formal-a/result-summary.json',
             'ownership': 'Original 586 and 591 authors retained; R18/R19 changes recorded separately.'})
        entry.update(anchor='base603', comparison_baseline='base603', native_decode_reference='base603')
        entries.append(entry)
    oldspec = json.loads((ROOT / 'evidence/round18/confirm-bq.json').read_bytes())
    controls = [e for e in oldspec['entries'] if e['name'] in ('probe3', 'r3-432-fast3', 'public432', 'public514')]
    controls.append(writer.control('base603', 'candidates/r18-rf-sf-content-proof1', '603'))
    shadow = {**controls[-1], 'name': 'base603-shadow'}
    shadow.pop('formal_id')
    controls.append(shadow)
    spec = {'entries': controls + entries, 'snapshot_pages': 'evidence/round19/official-start/pareto-pages.json',
        'screen_blocks': 2, 'refine_blocks': 0, 'shortlist': 0, 'gate_candidates': [], 'gate_limit': 0,
        'extract_candidates': [], 'retain_extracted_lean': True, 'synthetic_validation': True,
        'synthetic_reference_candidates': [], 'research_synthetic_candidates': [], 'cpu_diagnostics': False,
        'native_only': True, 'native_encoder': True, 'native_encoder_references': ['base603'],
        'r19_mode': 'native', 'r18_role': 'discovery', 'r19_role': 'discovery',
        'description': 'R19 minimum actual encoder/decode experiment: local seam scope, known-match-only replan, selective content allocation. One runner, 20-minute cap. Size loss and timing diagnostic determine standard paired testing; native timing is not official performance. Exact Lean pairs remain uncompiled drafts.'}
    names = [e['name'] for e in spec['entries']]
    spec['screen_orders'] = [names, list(reversed(names))]
    (E / 'probe-a-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    (E / 'preflight-a.json').write_bytes((json.dumps({
        'gap': 'Official603 has 5.7% historical share; need substantially better time-quality position. SF adds about 1.8 public time-axis units for 1233 bytes.',
        'changes': [{'candidate': n, 'mechanism': m, 'difference': d} for n, _, _, m, d in variants],
        'minimum_operation': 'Exact original encoder on28 public files, decode and per-file output deltas for3 distinct mechanism changes. Reuse existing toolchain path.',
        'decision': 'Keep useful quality/speed tradeoffs for original paired tests; near-zero useful quality stops a route. Frozen file pairs and new independent runs required before promotion.',
        'cost_cap_runner_minutes': 20, 'confirmation_reserve_minutes': 25,
        'evidence': 'evidence/round19/<run>/probe-a-native/diagnostics',
        'proof_risk': 'SF helpers have totality-only contracts; checked emitter still establishes original obligation. Reused proof is a draft until exact original gate.'
    }, indent=2) + '\n').encode())
    print(json.dumps({'candidates': [e['name'] for e in entries], 'spec': 'probe-a-native'}))


if __name__ == '__main__':
    main()
