"""Last R11 fast probe: recover a repeated distance across an actual literal gap.

The pending-literal design already keeps the last emitted match in out[nt-1],
so the fallback needs no new table or main-loop state. No tools are run here.
"""
from pathlib import Path
import argparse
import hashlib
import json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r3-432-fast3'
NAME='r11-fast-gaprepeat'

HELPER=r'''/// R11: the pending literal gap leaves the last match token in out[nt-1].
/// Only if the original head fails, and at least one gap byte was passed, try
/// that distance once. The normal match probe verifies all candidate bytes.
/// No attempt is made at the immediate end where a short match just mismatched.
#[inline(always)]
pub fn r11_gap_probe(s: &[u8], out: &[u32], nt: usize, ls: usize, c: usize, cw: u64, p: usize, km: u32) -> (usize, usize) {
    let f = probe_m(s, c, cw, p, km);
    if f.0 >= 3 || ls >= p || nt == 0 || nt > out.len() {
        return f;
    }
    let t = out[nt - 1];
    if t >= 16777216 && t < 25165824 {
        let d = ((t - 16777216) / 256 + 1) as usize;
        if d <= p && p <= s.len().saturating_sub(8) {
            let rc = p - d;
            let rw = be8(s, rc);
            let g = probe_m(s, rc, rw, p, km);
            if g.0 >= 3 {
                return g;
            }
        }
    }
    f
}

'''


def sha(b):return hashlib.sha256(b).hexdigest()


def generate():
    raw={n:(BASE/n).read_bytes() for n in ('parse.rs','Parse.lean')}
    assert sha(raw['parse.rs'])=='bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef'
    assert sha(raw['Parse.lean'])=='e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04'
    text=raw['parse.rs'].decode();a=text.rfind('#[inline(always)]',0,text.index('pub fn run1<const H: usize>'));b=text.index('/// The class itself when',a)
    original=text[a:b]
    old='            let f = probe_m(input, c, cw, p, km);'
    new='            let f = r11_gap_probe(input, out, nt, ls, c, cw, p, km);'
    assert original.count(old)==1
    changed=original.replace(old,new,1);source=text[:a]+HELPER+changed+text[b:]
    assert source.replace(HELPER+changed,original,1)==text
    files={'parse.rs':source.encode(),'Parse.lean':raw['Parse.lean']}
    manifest={
        'candidate':NAME,'parent':'candidates/r3-432-fast3','parent_hashes':{n:sha(v)for n,v in raw.items()},'hashes':{n:sha(v)for n,v in files.items()},
        'attribution':{'source':'Official public #432 then fast3; references/round3-public-432/PROVENANCE.md','public_miner_hotkey':'5EAM7rJK571o7asrBBk6oozUZCRubR1tMiDKBNWmWhw66PRy','named_author':'UNKNOWN','ownership':'Derivative of external public miner source, not an independently authored parser'},
        'mechanism':'At existing run1 search positions, keep the original head match whenever valid. Only after at least one pending literal and an original failed probe, read the previous output match token as an implicit repeat-distance cache and probe it once. No extra table, main-loop state, or eager scan on valid matches.',
        'difference_from_previous':'Closed continuation searched only exact 258-byte match boundaries; a short-match immediate continuation is impossible because the next byte mismatched. This probe instead crosses actual literal gaps. Unlike R3 tiny-rep1, it runs in existing run1, retains every valid original candidate, does not favor repeats on ties, and does not carry an added rep variable or run the tiny planner.',
        'cost_hypothesis':'May trade one cheap failed-probe fallback for fewer literal tokens and less encoder work; extra fallback work can outweigh both. Encoder occupied most historical fast3 component time. No time or size benefit is asserted.',
        'proof_status':'UNADAPTED_PARENT_ONLY; native checks, fresh extraction and complete original gate UNKNOWN',
        'proof_cost':'One wrapper spec using original probe_m_spec twice, be8_spec for the fallback and guarded token read/position arithmetic. Return FoundAt and original length/distance bounds. No new loops or main-state tuple changes.',
        'equivalence_status':'Final tokens may change. Original valid probe is preserved at the current state, but later search states/encoder blocks may change; no size monotonicity claim.',
        'audit':'One run1 call replacement and one helper. Reversing both restores exact parent bytes. All constants, routing, record logic and encoder unchanged.',
        'stop_condition':'Any native decode failure stops. If measured two-axis projection has no frontier opportunity, stop this version without threshold/depth variants. No combination with closed pendingfold/continuation candidates.',
        'formal_submission_sent':False,
    }
    files['manifest.json']=(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode()
    return files


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();dest=ROOT/'candidates'/NAME
    if args.check:assert all((dest/n).read_bytes()==b for n,b in files.items())
    else:
        dest.mkdir(parents=True,exist_ok=True)
        for n,b in files.items():(dest/n).write_bytes(b)
    print(json.dumps({'candidate':NAME,'hashes':{n:sha(b)for n,b in files.items()}},indent=2))


if __name__=='__main__':main()
