"""Isolate modular predecessor semantics in newly public539, retaining U32 arrays."""
from pathlib import Path
from datetime import datetime, timezone
import importlib.util
import json

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'


def main():
    sp = importlib.util.spec_from_file_location('builder', ROOT / 'scripts/build-round18-start.py')
    builder = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(builder)
    source = ROOT / 'references/round18-public-539'
    original_rust = (source / 'parse.rs').read_text()
    original_lean = (source / 'Parse.lean').read_text()
    entries = []
    for suffix, condition in [('key3', 'km == 4294967040'), ('all', 'true')]:
        rust, lean = original_rust, original_lean
        marker = '#[inline(always)]\npub fn pc_f_deepen('
        assert rust.count(marker) == 1
        helper = '''// R18: preserve full-width storage; isolate the semantics of wrapped hints.
// The existing byte matcher validates a hint before accepting a match.
#[inline(always)]
pub fn r18_prev_hint(c: usize, raw: u32, km: u32) -> usize {
    if CONDITION {
        let delta = c.wrapping_sub(raw as usize) & 32767;
        c.wrapping_sub(delta)
    } else {
        raw as usize
    }
}
'''.replace('CONDITION', condition)
        rust = rust.replace(marker, helper + marker)
        old = 'd: usize, dp: usize, minl: usize) -> (usize, usize) {'
        assert rust.count(old) == 1
        rust = rust.replace(old, 'd: usize, dp: usize, minl: usize, km: u32) -> (usize, usize) {')
        changes = [
            ('let c3 = prev[c2 % 32768] as usize;', 'let c3 = r18_prev_hint(c2, prev[c2 % 32768], km);', 1),
            ('let cl = prev[c % 32768] as usize;', 'let cl = r18_prev_hint(c, prev[c % 32768], km);', 2),
            ('pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl)',
             'pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl, km)', 2),
        ]
        for old, new, count in changes:
            assert rust.count(old) == count, (old, rust.count(old))
            rust = rust.replace(old, new)
        marker = '@[local step]\ntheorem f_deepen_spec '
        assert lean.count(marker) == 1
        proof = '''/-- This helper supplies a hint, not a validity claim. The original f_try checks it. -/
@[local step]
theorem r18_prev_hint_spec (c : Std.Usize) (raw km : Std.U32) :
    slot.r18_prev_hint c raw km ⦃ fun _ => True ⦄ := by
  rw [slot.r18_prev_hint]
  step*
  repeat' (split <;> step*)
  all_goals first | trivial | scalar_tac

'''
        lean = lean.replace(marker, proof + marker)
        old = '(c c2 p l d dp minl : Std.Usize) (hc : c.val ≤ p.val)'
        assert lean.count(old) == 1
        lean = lean.replace(old, '(c c2 p l d dp minl : Std.Usize) (km : Std.U32) (hc : c.val ≤ p.val)')
        old = 'slot.pc_f_deepen s prev c c2 p l d dp minl ⦃'
        assert lean.count(old) == 1
        lean = lean.replace(old, 'slot.pc_f_deepen s prev c c2 p l d dp minl km ⦃')
        marker = '@[local step]\nabbrev f_deepen_spec := @_root_.Submission.PC.f_deepen_spec'
        assert lean.count(marker) == 2
        lean = lean.replace(marker, '@[local step]\nabbrev r18_prev_hint_spec := @_root_.Submission.PC.r18_prev_hint_spec\n' + marker)
        name = 'r18-539-chain-hint-' + suffix
        entry = builder.write_candidate(name, 'public539', rust, lean,
            'Interpret U32 predecessor hints modulo32768 for ' + ('three-byte masked keys only' if suffix == 'key3' else 'all PC/PIM chain keys') + '. Keep the original array representation, hash, insertion, search depth, byte validation, route and emitter.',
            'Separates a search-state effect of R13 modular predecessors from their cache footprint. This is a transfer to newly public539, not a new matcher invention. No equality claim: stale or overwritten slots can produce different tested positions.',
            {'source': 'references/round18-public-539/source-receipt.json',
             'mechanism_source': 'candidates/r17-dna-nofold-proof1/parse.rs:r13_prev_unwrap',
             'audit': 'evidence/round18/539-vs582-PC-source-audit.json',
             'ownership': 'Original539 authors and R13 mechanism attribution retained.'})
        entry.update(anchor='public539', comparison_baseline='public539', native_decode_reference='public539')
        entries.append(entry)
    spec = json.loads((E / 'public539-bd-native.json').read_bytes())
    for field in ('r18_function_profile', 'r15_profile_entry', 'r15_profile_functions'):
        spec.pop(field)
    spec['entries'] += entries
    spec['screen_orders'] = [[e['name'] for e in spec['entries']], [e['name'] for e in reversed(spec['entries'])]]
    spec['snapshot_pages'] = 'evidence/round18/official-extension-start/pareto-pages.json'
    spec['description'] = 'BG controlled predecessor semantics on539: preserve U32 storage, compare key3-only and all-chain low15-bit reconstruction. Full28 original encoder/decode versus539 and582, synthetic validity. No official total-time or proof conclusion. Useful quality changes earn paired timing; fixed outputs distinguish no-op from representation opportunity. Cap15 minutes.'
    (E / 'chain-bg-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    preflight = {
        'declared_at_utc': datetime.now(timezone.utc).isoformat(),
        'gap': '539 is better on lean/bundle/prose but worse by25588B on CSV versus582. Hash width was ruled out; absolute versus modular predecessor semantics remain a causal candidate.',
        'material_change': 'Only hint reconstruction at both predecessor reads, key3-only versus all keys. Original U32 storage and search budgets retained.',
        'minimum_operation': 'Two exact derivatives, original28-file encoder/decode and same-source references; no expensive gate before output evidence.',
        'decision_boundary': 'Preserved text gains plus CSV recovery earns standard timing and scoring; identical output identifies a no-op on public corpus; broad quality loss stops this transfer version.',
        'proof_preflight': 'One total hint helper with True postcondition; existing byte validator owns MatchAt. Updated f_deepen signature and both imported spec aliases. Lean draft has not compiled and full original gate remains mandatory.',
        'cost_cap_runner_minutes': 15,
        'deadline_utc': '2026-10-10T04:32:51+00:00',
        'rejected_hash_assumption': 'pc_HB is15 in582, not16. Prior builder asserted before mutation and was disabled; no candidates or CI from it.',
        'evidence_directory': 'evidence/round18/<run>/chain-bg-native/diagnostics',
    }
    (E / 'chain-bg-preflight.json').write_bytes((json.dumps(preflight, indent=2) + '\n').encode())
    print(json.dumps(entries))


if __name__ == '__main__':
    main()
