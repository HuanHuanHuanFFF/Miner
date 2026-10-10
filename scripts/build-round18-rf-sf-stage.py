"""Transfer591 seam replanning onto verified586 selectiveRF output."""
from pathlib import Path
from datetime import datetime, timezone
import importlib.util
import json
import re

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def module(name, path):
    sp = importlib.util.spec_from_file_location(name, path)
    out = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(out)
    return out


def declarations(text):
    starts = list(re.finditer(r'^theorem\s+(\w+)\b', text, re.M))
    result = []
    for match in starts:
        after = re.search(r'^(?:@\[|theorem\s|namespace\s|end\s|attribute\s|set_option\s|local notation\s|def\s|abbrev\s)', text[match.end():], re.M)
        end = match.end() + after.start() if after else len(text)
        result.append((match[1], text[match.start():end].rstrip()))
    return result


def main():
    helper = module('sfmap', ROOT / 'scripts/audit-round18-sf-helper-map.py')
    builder = module('writer', ROOT / 'scripts/build-round18-start.py')
    source = ROOT / 'references/round18-public-591'
    parent = ROOT / 'candidates/r18-586-selective-rf'
    sr, sl = (source / 'parse.rs').read_text(), (source / 'Parse.lean').read_text()
    rust, lean = (parent / 'parse.rs').read_text(), (parent / 'Parse.lean').read_text()
    sf = helper.items(sr)
    mapping = json.loads((E / 'sf-helper-map.json').read_bytes())
    reused = {k: v[0] for k, v in mapping['mapped'].items() if k != 'SFDEPTH'}
    reused.update(Z168='q9_get', Z304='q9_set', Z379='rf_byte')
    wanted = set(mapping['unmapped']) | {'SFDEPTH'}

    def rename(text):
        return re.sub(r'\b(?:' + '|'.join(sorted(reused, key=len, reverse=True)) + r')\b',
                      lambda m: reused[m[0]], text)

    code = '\n\n'.join(rename(value) for name, value in sf.items() if name in wanted)
    assert code.count('pub fn SFshape(') == 1
    old = 'pub fn parse(input: &[u8], out: &mut [u32]) -> usize {'
    assert rust.count(old) == 1
    rust = rust.replace(old, old.replace('parse(', 'r18_base('))
    rust += '\n// R18 transfers the public591 SFshape stage; original authors retained in manifest.\n' + code
    rust += '''
pub fn parse(input: &[u8], out: &mut [u32]) -> usize {
    let nt = r18_base(input, out);
    if input.len() >= 65536 && input.len() < 16777216 {
        let plan = SFshape(input, out, nt);
        emit_pos(input, &plan, out)
    } else {
        nt
    }
}
'''
    at = lean.rindex('theorem parse_spec (')
    lean = lean[:at] + lean[at:].replace('theorem parse_spec (', '@[local step]\ntheorem r18_base_spec (', 1)
    lean = lean.replace('slot.parse input out', 'slot.r18_base input out').replace('rw [slot.parse]', 'rw [slot.r18_base]')
    assert lean.rstrip().endswith('end Submission')
    lean = lean.rstrip()[:-len('end Submission')]
    # Select only totality proofs for the newly copied functions and their Aeneas loops.
    selected = []
    for name, declaration in declarations(sl):
        first = re.search(r'slot\.(\w+)', declaration)
        if not first:
            continue
        root = first[1].split('_loop')[0]
        if root in wanted and root != 'SFDEPTH':
            selected.append((name, rename(declaration)))
    assert len({name for name, _ in selected}) == len(selected)
    covered = {re.search(r'slot\.(\w+)', d)[1].split('_loop')[0] for _, d in selected}
    assert wanted - {'SFDEPTH'} <= covered, wanted - covered
    # Import the existing target helper specs into the new, separately named namespace.
    stack, theorem_name, imported = [], None, {}
    targets = set(reused.values())
    for line in (parent / 'Parse.lean').read_text().splitlines():
        nm = re.match(r'namespace\s+(\w+)', line)
        em = re.match(r'end\s+(\w+)', line)
        tm = re.search(r'\btheorem\s+(\w+)', line)
        if nm:
            stack.append(nm[1])
        if em and stack and stack[-1] == em[1]:
            stack.pop()
        if tm:
            theorem_name = '.'.join(stack + [tm[1]])
        for target in targets:
            if re.search(r'slot\.' + re.escape(target) + r'\s', line) and theorem_name:
                imported.setdefault(target, theorem_name)
    needed_functions = set(reused.values()) & set(helper.items((parent / 'parse.rs').read_text()))
    # Constants do not need step lemmas.
    needed_functions = {n for n in needed_functions if helper.items((parent / 'parse.rs').read_text())[n].startswith('pub fn')}
    assert needed_functions <= set(imported), needed_functions - set(imported)
    prefix = '''
namespace R18SF
open Aeneas Aeneas.Std Result ControlFlow
open LZ77 (toks bytes bytes_length bytes_getElem! Matches emit_lit emit_match ite_ok)
set_option maxRecDepth 8192
set_option maxHeartbeats 4000000
local notation "U" => Slice Std.U32
local notation "I" => Slice Std.U8
local notation "R" => Std.Usize
local notation "W" => Std.U32
local notation "C" => Std.Array Std.U32
local notation "G" => Std.Array Std.U8
local notation "Y112P0!" => (fun _ => True)
set_option hygiene false in
local notation "T14!" q0__:max => (by
  rw [q0__]
  try simp only [ite_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)
set_option hygiene false in
local notation "T15!" q0__:max => (by
  rw [q0__]
  simp only [lift, ite_ok, alloc.vec.Vec.deref_mut, bind_tc_ok]
  step*
  all_goals (repeat (split <;> step*))
  all_goals scalar_tac)
'''
    t16_start = sl.index('set_option hygiene false in\nlocal notation "T16!"')
    t16_end = sl.index('@[local step]', t16_start)
    prefix += sl[t16_start:t16_end] + '\n'
    prefix += 'attribute [local step] ' + ' '.join(sorted(set(imported.values()))) + '\n\n'
    ported = '\n\n'.join('@[local step]\n' + d for _, d in selected)
    lean += prefix + ported + '''

end R18SF
attribute [local step] R18SF.SFshape_spec
theorem parse_spec (input : Slice Std.U8) (out : Slice Std.U32)
    (hlen : input.length ≤ out.length) :
    slot.parse input out ⦃ fun r => r.1.val ≤ input.length ∧
      r.2.length = out.length ∧ LZ77.Valid (bytes input) (toks r.2 r.1.val) ⦄ := by
  rw [slot.parse]
  step*
  all_goals (first | assumption |
    (refine ⟨by assumption, by assumption, ?_⟩; unfold LZ77.Valid; assumption))
end Submission
'''
    assert len(rust.encode()) < 524288 and len(lean.encode()) < 524288, (len(rust.encode()), len(lean.encode()))
    entry = builder.write_candidate('r18-rf-sf-stage', 'r18-586-selective-rf', rust, lean,
        'Apply591 seam-local token replanning to the frozen586 selectiveRF output and re-emit through the existing checked positional emitter. Only inputs65536..16777215 are eligible; no filename routing is used.',
        'TheBF free-mixture matrix indicated complementary quality, but is not executable. This tests actual composition of the two mechanisms with25KB dependency closure, reused token-identical helpers and about40KB proof migration rather than duplicating entire parsers. Performance and private quality are unknown.',
        {'parent': 'candidates/r18-586-selective-rf/manifest.json', 'stage': 'references/round18-public-591/source-receipt.json',
         'reuse_audit': 'evidence/round18/sf-helper-map.json', 'ownership': 'Both original authors and R18 selectiveRF attribution retained.'})
    entry.update(anchor='public586', comparison_baseline='r18-586-selective-rf', native_decode_reference='public586')
    spec = json.loads((E / 'baseline-bf.json').read_bytes())
    spec['entries'] = [e for e in spec['entries'] if not e['name'].endswith('-shadow') and e['name'] != 'base591'] + [entry]
    spec.update(r18_mode='native', native_only=True, native_encoder=True, native_encoder_references=['public586', 'public591', 'r18-586-selective-rf'], synthetic_validation=True, r18_role='discovery')
    spec['screen_orders'] = [[e['name'] for e in spec['entries']], [e['name'] for e in reversed(spec['entries'])]]
    spec['snapshot_pages'] = 'evidence/round18/official-extension-30m/pareto-pages.json'
    spec['description'] = 'BK actualRF-to-SF stage composition. Minimum28-file originalencoder/decode and per-file incremental bytes; full reused proof is only a new draft. No free-routing model score promoted. Cap20minutes. Useful size improvements determine one content-based selective followup and original paired total timing. Preserve original RF/SF receipts and authors.'
    (E / 'stage-bk-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    (E / 'stage-bk-preflight.json').write_bytes((json.dumps({
        'declared_at_utc': datetime.now(timezone.utc).isoformat(),
        'gap': 'BF free mixtures reach17.33percent under586 but3.33under591 calibration; the components are not a real composed parser and their calibration disagrees.',
        'material_change': 'Actual seam replanning ofselectiveRF token output using591stage, then originalchecked emission; no duplicatedbaseengine.',
        'minimum_operation': 'One exact actual composition,28file originalencoder/decode; identify changedfiles before timing orfullgate investment.',
        'decision_boundary': 'Material incremental bytes across content classes earns bounded selective implementation and original timing; zeroquality stops composition. Transfer predictions stay conditional and bothfamily assumptions remain visible.',
        'proof_preflight': {'copied_theorems': len(selected), 'rust_bytes': len(rust.encode()), 'lean_bytes': len(lean.encode()), 'uncompiled': True},
        'cost_cap_runner_minutes': 20, 'deadline_utc': '2026-10-10T04:32:51+00:00',
    }, indent=2) + '\n').encode())
    print(json.dumps({'entry': entry, 'proof_bytes': len(lean.encode()), 'new_theorems': len(selected)}))


if __name__ == '__main__':
    main()
