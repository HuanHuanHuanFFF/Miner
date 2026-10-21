"""Minimal UNCOMPILED LensBound bridge against the actual lensconst extraction."""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
PARENT = ROOT / 'candidates/r3-432-fast3'
BASE = ROOT / 'candidates/r11-fast-lensconst'
DEST = ROOT / 'candidates/r11-fast-lensconst-proof'
EXTRACT = ROOT / 'evidence/round11/37737625602/fast-l/extraction/r11-fast-lensconst'
RUST_SHA = '86e44e1cd2bbb50810f971edb1f0e4fbc71a89c43142850c0eb4097cb03704d5'
PARENT_LEAN_SHA = 'e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04'
FUNS_SHA = '89ee43599f62996045f375a42a9f7761ad46927084f1f9d761b5e50bd00c46e6'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def generate():
    rust = (BASE / 'parse.rs').read_bytes()
    parent = (PARENT / 'Parse.lean').read_bytes()
    funs_bytes = (EXTRACT / 'Funs.lean').read_bytes()
    assert sha(rust) == RUST_SHA
    assert sha(parent) == PARENT_LEAN_SHA
    assert (BASE / 'Parse.lean').read_bytes() == parent
    assert sha(funs_bytes) == FUNS_SHA
    funs = funs_bytes.decode()
    start = funs.index('def r11_e_lens (m : Std.U32)')
    end = funs.index('/-- [slot::e_piece]', start)
    helper = funs[start:end]
    assert 'Result (Array Std.U16 260#usize)' in helper
    assert 'else let lens := Array.repeat 260#usize 0#u16\n       e_lens lens m' in helper
    match = re.search(r'\(Array\.make 260#usize \[(.*?)\]\)', helper, re.S)
    assert match
    array = 'Array.make 260#usize [' + match.group(1) + ']'
    values = list(map(int, re.findall(r'(\d+)#u16', match.group(1))))
    assert len(values) == 260 and max(values) == 258
    assert values[:3] == [0, 0, 0] and values[259] == 0
    proof = '''/-- The fixed literal and unchanged arbitrary-mask fallback preserve the original length bound. -/
@[local step]
theorem r11_e_lens_spec (m : Std.U32) :
    slot.r11_e_lens m ⦃ fun r => LensBound r ⦄ := by
  rw [slot.r11_e_lens]
  split
  · simp only [WP.spec_ok]
    let tab : Array Std.U16 260#usize := ARRAY
    change LensBound tab
    have hall : ∀ v ∈ tab.val, v.val ≤ 258 := by
      dsimp only [tab, Array.make]
      decide
    intro j hj
    rw [getElem!_pos tab.val j hj]
    exact hall _ (List.getElem_mem _)
  · exact e_lens_spec (Std.Array.repeat 260#usize 0#u16) m LensBound.init

'''.replace('ARRAY', array)
    assert not re.search(r'\b(sorry|admit|axiom|native_decide)\b', proof)
    original = parent.decode()
    marker = '/-- `e_piece`: 0, or a piece of at least 3 and at most `rem` bytes, at most 258. -/'
    assert original.count(marker) == 1
    lean = original.replace(marker, proof + marker, 1)
    old_init = '  have hL0 : LensBound (Std.Array.repeat 260#usize 0#u16) := LensBound.init\n'
    assert lean.count(old_init) == 2
    lean = lean.replace(old_init, '')
    # Reverse only the two caller edits and the new helper to recover the exact accepted parent.
    reverse = lean.replace(proof, '', 1)
    for caller in ('run1t_spec', 'run_z_spec'):
        position = reverse.index('theorem ' + caller + ' ')
        init_position = reverse.index('  have hdec0 :', position)
        reverse = reverse[:init_position] + old_init + reverse[init_position:]
    assert reverse == original
    files = {'parse.rs': rust, 'Parse.lean': lean.encode()}
    hashes = {name: sha(data) for name, data in files.items()}
    manifest = json.loads((BASE / 'manifest.json').read_text())
    manifest.update(candidate='r11-fast-lensconst-proof', parent='candidates/r11-fast-lensconst',
                    hashes=hashes, proof_parent='candidates/r3-432-fast3',
                    proof_status='UNCOMPILED_ACTUAL_INTERFACE_MINIMAL_LENSBOUND_BRIDGE',
                    equivalence_status='SOURCE_MODEL_260_VALUES; real native/public receipt must be read before claiming execution',
                    performance_status='PENDING fast-l receipt; no improvement claimed',
                    formal_submission_sent=False)
    audit = {
        'status': 'VERIFIED_SOURCE_INTERFACE_ONLY_LEAN_UNCOMPILED',
        'rust_sha256': RUST_SHA, 'parent_lean_sha256': PARENT_LEAN_SHA,
        'extraction_path': str(EXTRACT.relative_to(ROOT)), 'Funs_sha256': FUNS_SHA,
        'helper': {'name': 'slot.r11_e_lens', 'arguments': ['m : U32'],
                   'return': 'Result (Array U16 260#usize)', 'loop_count': 0,
                   'fixed_branch': 'ok(Array.make 260 literal U16 values)',
                   'fallback': 'Array.repeat 260 zero; unchanged e_lens lens m'},
        'callers': {'run1t': 'let lens <- r11_e_lens lm; existing loops consume lens',
                    'run_z': 'let lens <- r11_e_lens TZ_LM; existing loop consumes lens'},
        'changes': ['one new r11_e_lens_spec', 'remove redundant initial zero-table hL0 in run1t_spec and run_z_spec'],
        'array_check': {'entries': len(values), 'max': max(values), 'zero_indices': [0, 1, 2, 259]},
        'proof_method': 'ordinary decide on finite List membership, getElem!_pos, List.getElem_mem; original e_lens_spec fallback',
        'source_reversal': 'VERIFIED: removing helper and restoring two caller hL0 statements recovers exact e2c parent',
        'statement_axioms_checked_emitter': 'original text preserved by reversible insertion/removals',
        'not_proved': ['all-input token equivalence to old source', 'Lean elaboration', 'original obligation gate', 'allowed axioms receipt', 'round trip'],
    }
    status = {'status': 'UNCOMPILED', 'hashes': hashes,
              'actual_interface': 'SOURCE_AUDITED', 'lean_run': 'NOT_RUN', 'full_gate': 'NOT_RUN',
              'native_public_equivalence': 'PENDING_RAW_RECEIPT', 'performance': 'PENDING',
              'new_preconditions': [], 'new_axioms': [], 'sorry_admit_native_decide': False,
              'pending': ['WP.spec_ok normalization', 'finite membership decide and Array.make reduction',
                          'two caller step bindings', 'original obligation and axiom whitelist and round trip']}
    for name, value in [('manifest.json', manifest), ('interface-audit.json', audit), ('UNCOMPILED_STATUS.json', status)]:
        files[name] = (json.dumps(value, ensure_ascii=False, indent=2) + '\n').encode()
    return files


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    files = generate()
    DEST.mkdir(parents=True, exist_ok=True)
    for name, data in files.items():
        path = DEST / name
        if args.check:
            assert path.read_bytes() == data
        elif path.exists():
            assert path.read_bytes() == data, 'Refusing to change existing frozen draft'
        else:
            path.write_bytes(data)
    print(json.dumps({'candidate': DEST.name, 'status': 'UNCOMPILED',
                      'hashes': {name: sha(data) for name, data in files.items()},
                      'builder_sha256': sha(Path(__file__).read_bytes())}))


if __name__ == '__main__':
    main()
