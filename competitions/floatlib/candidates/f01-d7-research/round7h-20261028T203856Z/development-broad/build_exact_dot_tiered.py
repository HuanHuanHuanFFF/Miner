"""New signed64/128 diagnostic; frozen baseline, fixtures and Main stay intact."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-r24-dev-broad-exactdot-cost1'
CAND = ROOT / 'competitions/floatlib/candidates/f01-r24-dev-broad-exactdot-tiered1'
PART = HERE / 'ExactDotTiered.lean.inc'
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def main():
    assert sha(OLD / 'Kernel.lean') == '9a8e4f01b333616567f96440a4c348e99481769a1e3dad734eef0b8031ed11d9'
    assert sha(HERE / 'ExactDotCost.lean.inc') == 'cb0eaf4cf11181c2ee006b906f3008ec4d92ddcc5a317c1ceb47b23f70e7bd53'
    assert sha(HERE / 'ExactDotFixtureMain.lean') == 'be5128f24f01bb695b20a04da53c4a9e4bfb435b3e261c4388093d8a84a6e35f'
    assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b', PART.read_bytes())
    raw = (OLD / 'Kernel.lean').read_bytes() + b'\n' + PART.read_bytes()
    assert len(raw) < 256000
    model = json.loads((HERE / 'exact-dot-tiered-model-results.json').read_text(encoding='utf-8'))
    assert model['tiered_lean_sha256'] == sha(PART)
    own = [f for f in model['cases'] if f['group'] == 'own']
    old_main = (HERE / 'ExactDotFixtureMain.lean').read_text(encoding='utf-8')
    flags = 'def expected64Flags : Array Bool := #[' + ','.join('true' if f['tier'] == 'word64' else 'false' for f in own) + ']\n'
    new_main = old_main.replace('open Submission.R24ExactDotCost\n',
                                'open Submission.R24ExactDotCost\nopen Submission.R24ExactDotTiered\n')
    new_main = new_main.replace('def main : IO UInt32 := do\n', flags + 'def main : IO UInt32 := do\n')
    new_main = new_main.replace('  let mut failed := false\n', '  let mut failed := false\n  let mut fixtureIndex := 0\n')
    new_main = new_main.replace('    let c := pair left right\n',
                                '    let c := pair left right\n    let expected64 := expected64Flags[fixtureIndex]!\n    fixtureIndex := fixtureIndex + 1\n    let tierCold := fullv2 a b\n    let tierWarm := prepared2v2 left right\n')
    new_main = new_main.replace('    let good := cold == f.expected',
                                '    let good := tierCold == f.expected && tierWarm == f.expected && eligible64 c == expected64 && cold == f.expected')
    new_main = new_main.replace('    IO.println s!"DOT|',
                                '    IO.println s!"TIER|{f.name}|{f.expected.toNat}|{tierCold.toNat}|{tierWarm.toNat}|{eligible64 c}|{expected64}|{good}"\n    IO.println s!"DOT|')
    main_path = HERE / 'ExactDotTieredFixtureMain.lean'
    main_path.write_text(new_main, encoding='utf-8', newline='\n')
    CAND.mkdir(exist_ok=True)
    (CAND / 'Kernel.lean').write_bytes(raw)
    manifest = json.loads((OLD / 'manifest.json').read_text(encoding='utf-8'))
    source = sha(CAND / 'Kernel.lean')
    manifest.update(candidate=CAND.name, candidate_sha256=source, candidate_bytes=len(raw),
                    helper_audit_source_sha256=source,
                    proof_status='SIGNED64_128_EQUIVALENCE_NOT_PROVED_RESEARCH_COST_ONLY')
    files = [HERE / 'ExactDotCost.lean.inc', PART, HERE / 'exact-dot-cost-fixtures.json',
             main_path, HERE / 'exact_dot_tiered_model.py', HERE / 'exact-dot-tiered-model-results.json']
    manifest['components'] = [{'path': p.relative_to(ROOT).as_posix(), 'sha256': sha(p), 'bytes': p.stat().st_size} for p in files]
    manifest['scope'] = 'Research-only generic exact-dot cost control: one signed62-bit UInt64 chain, then frozen UInt128/native RNE, then finite exact replay. Separately reusable operand caches and timed zero-sign handling retained. Original official public four callbacks unchanged. Equivalence remains unproved; no official score/new-target Kernel/performance claim.'
    manifest['frozen_baseline'] = {'candidate': OLD.name, 'sha256': sha(OLD / 'Kernel.lean')}
    (CAND / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'candidate': CAND.name, 'sha256': source, 'bytes': len(raw),
                      'manifest_sha256': sha(CAND / 'manifest.json'), 'fragment_sha256': sha(PART),
                      'fragment_bytes': PART.stat().st_size, 'fixture_main_sha256': sha(main_path),
                      'crosschecked': model['summary']}, indent=2))


if __name__ == '__main__':
    main()
