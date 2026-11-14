"""Freeze one research cost baseline and its independent fixture executable."""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
BASE = ROOT / 'competitions/floatlib/references/official-incumbent/Kernel.lean'
FRAGMENT = HERE / 'ExactDotCost.lean.inc'
FIXTURES = HERE / 'exact-dot-cost-fixtures.json'
CAND = ROOT / 'competitions/floatlib/candidates/f01-r24-dev-broad-exactdot-cost1'
HELPER = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
q = lambda s: json.dumps(s, ensure_ascii=True)
boolean = lambda b: 'true' if b else 'false'


def main():
    assert sha(BASE) == '5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
    assert sha(HELPER) == '5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975'
    fragment = FRAGMENT.read_bytes()
    assert not re.search(rb'\b(?:sorry|admit|native_decide|axiom|unsafe)\b', fragment)
    assert not re.search(rb'^\s*import\b', fragment, re.M)
    raw = BASE.read_bytes() + b'\n' + fragment
    assert len(raw) < 256000 and b'ContractExact' not in raw
    fixtures = json.loads(FIXTURES.read_text(encoding='utf-8'))
    assert fixtures['lean_source_sha256'] == sha(FRAGMENT)
    CAND.mkdir(exist_ok=True)
    (CAND / 'Kernel.lean').write_bytes(raw)
    fixture_source = '''import Submission
open Submission.R24ExactDotCost
structure DotFixture where
  name : String
  a : String
  b : String
  expected : UInt32
  fast : Bool
  finite : Bool
  matched : Bool
structure RoundFixture where
  name : String
  negative : Bool
  lo : UInt64
  hi : UInt64
  base : Int
  expected : UInt32
def dotFixtures : Array DotFixture := #[
'''
    rows = []
    for f in fixtures['dot_cases']:
        rows.append('  { name := ' + q(f['id']) + ', a := ' + q(','.join(map(str, f['a']))) +
                    ', b := ' + q(','.join(map(str, f['b']))) + ', expected := ' + str(f['expected']) +
                    ', fast := ' + boolean(f['expected_fast']) + ', finite := ' + boolean(f['expected_finite']) +
                    ', matched := ' + boolean(f['expected_matched']) + ' }')
    fixture_source += ',\n'.join(rows) + '\n]\ndef roundFixtures : Array RoundFixture := #[\n'
    rows = []
    for f in fixtures['round_cases']:
        rows.append('  { name := ' + q(f['id']) + ', negative := ' + boolean(f['negative']) +
                    ', lo := ' + str(f['lo']) + ', hi := ' + str(f['hi']) + ', base := ' + str(f['base']) +
                    ', expected := ' + str(f['expected']) + ' }')
    fixture_source += ',\n'.join(rows) + '\n]\n'
    fixture_source += '''
def parseWords (s : String) : Array UInt32 :=
  if s.isEmpty then #[] else
    (s.splitOn ",").toArray.map (fun x => UInt32.ofNat ((x.toNat?).getD 0))
def main : IO UInt32 := do
  let mut failed := false
  for f in dotFixtures do
    let a := parseWords f.a
    let b := parseWords f.b
    let left := prepareOperand a
    let right := prepareOperand b
    let c := pair left right
    let cold := full a b
    let warm := prepared2 left right
    let replay := referencePrepared c
    let good := cold == f.expected && warm == f.expected && replay == f.expected &&
      fastEligible c == f.fast && c.finite == f.finite && c.matched == f.matched
    failed := failed || !good
    IO.println s!"DOT|{f.name}|{f.expected.toNat}|{cold.toNat}|{warm.toNat}|{replay.toNat}|{fastEligible c}|{c.finite}|{c.matched}|{good}"
  for f in roundFixtures do
    let actual := round128 f.negative f.lo f.hi f.base
    let good := actual == f.expected
    failed := failed || !good
    IO.println s!"ROUND|{f.name}|{f.expected.toNat}|{actual.toNat}|{good}"
  IO.println s!"SUMMARY|{dotFixtures.size}|{roundFixtures.size}|{!failed}"
  return if failed then 1 else 0
'''
    main_path = HERE / 'ExactDotFixtureMain.lean'
    main_path.write_text(fixture_source, encoding='utf-8', newline='\n')
    source = sha(CAND / 'Kernel.lean')
    names = ['Submission.' + n + '_spec' for n in ('add', 'mul', 'sum', 'bmm')]
    names += ['Submission.FastMul.fastLog2_eq']
    manifest = {
        'candidate': CAND.name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': source,
        'candidate_bytes': len(raw), 'validation_mode': 'statement-only', 'diagnostic_only': True,
        'diagnostic_timeout_seconds': 600, 'proof_status': 'NATIVE_BASELINE_EQUIVALENCE_NOT_PROVED_RESEARCH_COST_ONLY',
        'performance': 'NOT_RUN_NO_SPEED_OR_ACCEPTANCE_CLAIM', 'formal_submission': 'NOT_SUBMITTED',
        'official_submission_inherited': False, 'helper_audit_module': HELPER.name,
        'helper_audit_module_path': HELPER.relative_to(ROOT / 'competitions/floatlib/candidates').as_posix(),
        'helper_audit_module_sha256': sha(HELPER), 'explicit_helper_audit': names,
        'helper_audit_required_endpoints': names, 'helper_audit_expected_count': len(names),
        'helper_audit_source_sha256': source, 'diagnostic_evaluations': [],
        'runtime_prefix': {'path': BASE.relative_to(ROOT).as_posix(), 'sha256': sha(BASE),
                           'bytes': BASE.stat().st_size, 'byte_identical': True},
        'components': [{'path': p.relative_to(ROOT).as_posix(), 'sha256': sha(p),
                        'bytes': p.stat().st_size} for p in (FRAGMENT, FIXTURES, main_path, HERE / 'exact_dot_baseline_model.py')],
        'scope': 'Old ContractTensor only; original public four callbacks unchanged. Research exact-dot baseline has independently reusable packed normal-or-zero operand caches, conservative separable summaries, four UInt64 positive/negative accumulators and word RNE. Guard misses replay finite exact Nat/Int; nonfinite/mismatch are explicit unsupported canonicalNaN policy. Native equivalence is an unproved proposition. Fraction fixtures and actual selected C/ASM/cost required; not an official exact-contract Kernel.',
    }
    (CAND / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'candidate': CAND.name, 'sha256': source, 'bytes': len(raw),
                      'manifest_sha256': sha(CAND / 'manifest.json'), 'fixture_main_sha256': sha(main_path),
                      'fixture_main_bytes': main_path.stat().st_size, 'fixture_summary': fixtures['summary']}, indent=2))


if __name__ == '__main__':
    main()
