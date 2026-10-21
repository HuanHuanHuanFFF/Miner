"""Two independent structural probes on the frozen fast3 parser, no local binaries."""
from pathlib import Path
import argparse
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'candidates/r3-432-fast3'
PARENT = {'parse.rs': 'bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef',
          'Parse.lean': 'e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04'}

HELPERS = '''/// R12: share the input word between head hashing and the eventual probe.
#[inline(always)]
pub fn r12_ahead<const H: usize>(s: &[u8], head: &[u32; H], i: usize, km: u32) -> (usize, usize, u64, u64) {
    let pw = be8(s, i);
    let a = if s.len() >= 8 && i <= s.len() - 8 {
        let k = ((pw >> 32) as u32 & km) as u64;
        (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (64 - HB)) as usize % H
    } else {
        slot_of_m::<H>(s, i, km)
    };
    let c = head[a] as usize;
    (a, c, be8(s, c), pw)
}

#[inline(always)]
pub fn r12_ahead_if<const H: usize>(s: &[u8], head: &[u32; H], i: usize, lim: usize, a: usize, c: usize, w: u64, pw: u64, km: u32) -> (usize, usize, u64, u64) {
    if i < lim {
        r12_ahead::<H>(s, head, i, km)
    } else {
        (a, c, w, pw)
    }
}

#[inline(always)]
pub fn r12_ahead_fix<const H: usize>(s: &[u8], head: &[u32; H], i: usize, lim: usize, e: usize, a: usize, c: usize, w: u64, pw: u64, a0: usize, c0: usize, w0: u64, pw0: u64, km: u32) -> (usize, usize, u64, u64) {
    if i == e && i < lim && a < H && head[a] as usize == c {
        (a, c, w, pw)
    } else {
        r12_ahead_if::<H>(s, head, i, lim, a0, c0, w0, pw0, km)
    }
}

#[inline(always)]
pub fn r12_probe(s: &[u8], c: usize, cw: u64, p: usize, pw: u64, km: u32) -> (usize, usize) {
    let d = p.wrapping_sub(c);
    let x = cw ^ pw;
    if d.wrapping_sub(1) < 32768 && ((x >> 32) & (km as u64)) == 0 {
        (xlen16(s, c, p, x), d)
    } else {
        (0, 0)
    }
}

'''

def sha(b):
    return hashlib.sha256(b).hexdigest()


def generate(kind):
    raw = {f: (BASE/f).read_bytes() for f in PARENT}
    assert {f: sha(b) for f,b in raw.items()} == PARENT
    original = raw['parse.rs'].decode()
    if kind == 'wordhead':
        start = original.rfind('#[inline(always)]', 0, original.index('pub fn run1<const H: usize>'))
        end = original.index('/// The class itself when', start)
        body = original[start:end]
        replacements = [
            ('let a0 = ahead_m::<H>(input, &head, 0, km);', 'let a0 = r12_ahead::<H>(input, &head, 0, km);'),
            ('let mut pre_w = a0.2;', 'let mut pre_w = a0.2;\n        let mut pre_pw = a0.3;'),
            ('let cw = pre_w;', 'let cw = pre_w;\n            let pw = pre_pw;'),
            ('ahead_if_m::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, km)', 'r12_ahead_if::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, pre_pw, km)'),
            ('ahead_if_m::<H>(input, &head, q + 1, lim, pre_slot, pre_c, pre_w, km)', 'r12_ahead_if::<H>(input, &head, q + 1, lim, pre_slot, pre_c, pre_w, pre_pw, km)'),
            ('ahead_if_m::<H>(input, &head, e, lim, pre_slot, pre_c, pre_w, km)', 'r12_ahead_if::<H>(input, &head, e, lim, pre_slot, pre_c, pre_w, pre_pw, km)'),
            ('ahead_if_m::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w, km)', 'r12_ahead_if::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w, pre_pw, km)'),
            ('ahead_fix_m::<H>(input, &head, p, lim, e, ae.0, ae.1, ae.2, pre_slot, pre_c, pre_w, km)', 'r12_ahead_fix::<H>(input, &head, p, lim, e, ae.0, ae.1, ae.2, ae.3, pre_slot, pre_c, pre_w, pre_pw, km)'),
            ('probe_m(input, c, cw, p, km)', 'r12_probe(input, c, cw, p, pw, km)'),
        ]
        for i in range(1,5):
            replacements.append((f'pre_w = a{i}.2;', f'pre_w = a{i}.2;\n' + (' ' * (12 if i in (1,3) else 20)) + f'pre_pw = a{i}.3;'))
        changed = body
        for before,after in replacements:
            assert changed.count(before) == 1, before
            changed = changed.replace(before, after, 1)
        reverse = changed
        for before,after in reversed(replacements):
            assert reverse.count(after) == 1
            reverse = reverse.replace(after, before, 1)
        assert reverse == body
        source = original[:start] + HELPERS + changed + original[end:]
        assert source.replace(HELPERS + changed, body, 1) == original
        mechanism = 'Carry the current input word in read-ahead state; use its high four bytes for the original head hash and consume it at probe time. Preserve insert/skip/lazy/end-cache schedules.'
        difference = 'Changes the value reused across loop iterations. R11 skipahead changes the target position; R4 slotonly suppresses match-path loads. Neither carried the current input word from hashing to probing.'
        proof = 'Four new helper specs, an additional current-word invariant in run1/lazy state and its real extracted tuple plumbing. Original helpers and other engines unchanged. Parent Lean UNADAPTED.'
    else:
        assert kind == 'strideword'
        before = '''        let mut l = 3usize;
        while l < cap && s[c + l] == s[p + l] {
            l += 1;
        }
        (l, p - c)'''
        after = '''        let l = common_from(s, c, p, cap, 3);
        (l, p - c)'''
        start = original.index('pub fn st_find(')
        end = original.index('/// Record position', start)
        section = original[start:end]
        assert section.count(before) == 1
        changed = section.replace(before, after, 1)
        source = original[:start] + changed + original[end:]
        assert source[:start] + changed.replace(after, before, 1) + source[start + len(changed):] == original
        mechanism = 'Keep the stride engine distance and three-byte key gates, but extend its valid match with the existing bounded eight-byte common_from instead of one-byte comparisons.'
        difference = 'R4 stai changed inlining, not extension. This modifies the actual stride match extension work; no routing, hash, insertion or search budget changes.'
        proof = 'Replace st_find byte-loop proof by common_from_spec at seed length3; move dependent stride specs after common_from_spec if necessary. Parent Lean UNADAPTED.'
    name = 'r12-fast-' + kind
    files = {'parse.rs': source.encode(), 'Parse.lean': raw['Parse.lean']}
    manifest = {'candidate': name, 'parent': 'candidates/r3-432-fast3', 'parent_hashes': PARENT,
        'hashes': {f: sha(b) for f,b in files.items()},
        'attribution': {'source': 'Public #432 via fast3', 'reference': 'references/round3-public-432/PROVENANCE.md',
                        'author_hotkey': '5EAM7rJK571o7asrBBk6oozUZCRubR1tMiDKBNWmWhw66PRy', 'ownership': 'Derivative of public miner code'},
        'mechanism': mechanism, 'difference_from_old_work': difference, 'proof_cost': proof,
        'proof_status': 'UNADAPTED_PARENT_ONLY; official gate UNKNOWN',
        'expected_equivalent_to': 'r3-432-fast3', 'equivalence_status': 'INFERRED for valid parser calls; native/public checks pending',
        'performance_status': 'UNKNOWN; total parser plus encoder timing required',
        'source_reversal': 'Asserted exact original bytes after reversing the isolated source edits',
        'stop_condition': 'Token/decode mismatch rejects premise. No useful independently repeated total-time gain closes this fixed version. Do not infer formal admission or reward from public projection.',
        'formal_submission_sent': False}
    files['manifest.json'] = (json.dumps(manifest, ensure_ascii=False, indent=2) + '\n').encode()
    return name, files


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    for kind in ('wordhead','strideword'):
        name,files = generate(kind)
        dest = ROOT/'candidates'/name
        if args.check:
            assert all((dest/f).read_bytes() == b for f,b in files.items())
        else:
            if dest.exists():
                assert all((dest/f).read_bytes() == b for f,b in files.items())
            else:
                dest.mkdir(parents=True)
                for f,b in files.items():
                    (dest/f).write_bytes(b)
        print(json.dumps({'candidate': name, 'hashes': {f: sha(b) for f,b in files.items()}}))


if __name__ == '__main__':
    main()
