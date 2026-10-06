"""Reproduce round2 candidates from the frozen probe2 control, without toolchains.

This generates candidate files only; it does not certify them or submit anything.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]


def generate():
    source = (ROOT / 'candidates/probe2/parse.rs').read_text(encoding='utf-8')
    proof = (ROOT / 'candidates/probe2/Parse.lean').read_text(encoding='utf-8')
    variants = {
        'probe3': {'T_DEPTH': 3, 'P_DEPTH': 3, 'S_DEPTH': 3},
        'probe2-nice16': {'NICE': 16},
        'probe2-nice64': {'NICE': 64},
    }
    for name, constants in variants.items():
        text = source
        for key, value in constants.items():
            text, count = re.subn(rf'(pub const {key}: usize = )\d+;', rf'\g<1>{value};', text)
            assert count == 1
        target = ROOT / 'candidates' / name
        target.mkdir(exist_ok=True)
        (target / 'parse.rs').write_text(text, encoding='utf-8', newline='\n')
        (target / 'Parse.lean').write_text(proof, encoding='utf-8', newline='\n')

    # Keep the original engine for small inputs and every binary class. Only
    # the three large-text dispatches use buckets (H = W = 32768).
    start = source.index('#[inline(always)]\npub fn run<')
    end = source.index('/// Every input except larger text and prose:', start)
    bucket_run = source[start:end].replace('pub fn run<', 'pub fn bucket_run<')
    bucket_run = re.sub(r'\binsert\(', 'bucket_insert(', bucket_run)
    bucket_run = re.sub(r'\bfind\(', 'bucket_find(', bucket_run)
    helpers = '''/// Insert into two recent-position slots; snapshot both before rotation.
/// The second table is keyed by hash, rather than by input position.
#[inline(always)]
pub fn bucket_insert<const H: usize, const W: usize>(s: &[u8], head: &mut [u32; H], prev: &mut [u32; W], i: usize, mask: u32) -> (usize, usize) {
    let k = (be4(s, i) & mask) as u64;
    let a = (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - HB)) as usize % H;
    let old = head[a];
    let older = prev[a % W];
    prev[a % W] = old;
    head[a] = i as u32;
    (old as usize, older as usize)
}

/// A one-entry virtual chain links the first captured candidate to the second.
/// After that, nx == c stops the original verified walk. The array is scalar
/// after inlining; no position-indexed chain access is required.
#[inline(always)]
pub fn bucket_find<const W: usize>(s: &[u8], _prev: &[u32; W], p: usize, st: (usize, usize), have: usize, minl: usize, depth: usize, gm: usize) -> (usize, usize) {
    let link = [st.1 as u32; 1];
    find(s, &link, p, st.0, have, minl, depth, gm)
}

'''
    text = source[:start] + helpers + bucket_run + source[start:]
    parse_start = text.index('pub fn parse(')
    parse_end = text.index('// ─', parse_start)
    dispatch = text[parse_start:parse_end].replace('run::<HN, WN>', 'bucket_run::<HN, WN>')
    text = text[:parse_start] + dispatch + text[parse_end:]

    # Reuse all byte comparison and decode lemmas. Duplicate only the engine
    # loop proofs under a namespace, for the newly extracted loop names.
    insert_start = proof.index('@[local step]\ntheorem insert_spec')
    insert_end = proof.index('/-! ## 6.', insert_start)
    insert_spec = proof[insert_start:insert_end].replace('slot.insert', 'slot.bucket_insert')
    insert_spec = insert_spec.replace('r.1.val ≤ B', 'r.1.1.val ≤ B')
    find_spec = '''@[local step]
theorem find_spec (s : Slice Std.U8) {W : Std.Usize} (prev : Array Std.U32 W)
    (p : Std.Usize) (st : Std.Usize × Std.Usize) («have» minl depth gm : Std.Usize)
    (hp : p.val ≤ s.length) (hst : st.1.val ≤ p.val) (hhave : p.val + «have».val ≤ s.length)
    (hhave258 : «have».val ≤ 258) (hminl : 1 ≤ minl.val) (hminl' : p.val + minl.val ≤ s.length + 1)
    (hW : 0 < W.val) :
    slot.bucket_find s prev p st «have» minl depth gm ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := by
  rw [slot.bucket_find]
  step*

'''
    loops_start = proof.index('theorem back_loop_inv')
    loops_end = proof.index('/-! ## 13.', loops_start)
    loops = proof[loops_start:loops_end].replace('slot.run', 'slot.bucket_run')
    run_start = proof.index('@[local step]\ntheorem run_spec')
    run_end = proof.index('theorem run_rest_spec', run_start)
    run_spec = proof[run_start:run_end].replace('slot.run', 'slot.bucket_run')
    extra = '\nnamespace Bucket2\n\n' + insert_spec + find_spec + loops + run_spec + 'end Bucket2\n\n'
    obligation = proof.index('/-! ## 15.')
    new_proof = proof[:obligation] + extra + proof[obligation:]
    # Make each large-text branch use whichever verified engine appears after
    # extraction, while run_rest retains its original theorem.
    final = new_proof.index('theorem parse_spec')
    tail = new_proof[final:]
    tail = tail.replace('| exact run_spec _ _ input out _ hlen (by simp) (by simp)',
                        '| exact Bucket2.run_spec _ _ input out _ hlen (by simp) (by simp)\n'
                        '      | exact run_spec _ _ input out _ hlen (by simp) (by simp)')
    new_proof = new_proof[:final] + tail
    target = ROOT / 'candidates/bucket2'
    target.mkdir(exist_ok=True)
    (target / 'parse.rs').write_text(text, encoding='utf-8', newline='\n')
    (target / 'Parse.lean').write_text(new_proof, encoding='utf-8', newline='\n')


if __name__ == '__main__':
    generate()
