"""Prepare a proof-only adapter for the frozen recovery composition."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r13-514-abs15-rescue'
NAME='r13-514-abs15-rescue-proof1'
EXPECTED={'parse.rs':'30277a30ba30d7cf523bcad9d9785d6c1fa33ad1d624e405a84b59df4cabe5da',
          'Parse.lean':'38d157d9b023874b0b54f2b0e2283352d2fb786b22f193212b9e9a6c23c2b925'}
ADAPTER='''/-- Recovery candidates remain hints; both accepted paths use the original byte validator. -/
@[local step]
theorem r13_pc_find_rescue_spec (s : Slice Std.U8) (prev : Array Std.U16 32768#usize)
    (c : Std.Usize) (cw : Std.U64) (p : Std.Usize) (km : Std.U32) (dp minl : Std.Usize)
    (hc : c.val ≤ p.val) (hcw : cw.val = word8 s c.val) (hp : p.val + 8 ≤ s.length) :
    slot.r13_pc_find_rescue s prev c cw p km dp minl
      ⦃ fun r => FoundAt s p.val r.1.val r.2.val ⦄ := by
  rw [slot.r13_pc_find_rescue]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*
  all_goals try (exact FoundAt.real (by assumption) (by scalar_tac))
  repeat' (split <;> step*)
  all_goals first
    | exact FoundAt.real (by assumption) (by scalar_tac)
    | exact Or.inr (by assumption)
    | exact FoundAt.none s p.val
    | assumption
    | scalar_tac

'''

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    raw={f:(BASE/f).read_bytes() for f in EXPECTED}
    assert {f:sha(v) for f,v in raw.items()}==EXPECTED
    lean=raw['Parse.lean'].decode();marker='@[local step]\ntheorem f_record3_loop0_spec'
    assert lean.count(marker)==1 and 'theorem r13_pc_find_rescue_spec' not in lean
    lean=lean.replace(marker,ADAPTER+marker,1)
    assert lean.replace(ADAPTER,'',1).encode()==raw['Parse.lean']
    files={'parse.rs':raw['parse.rs'],'Parse.lean':lean.encode()}
    origin=json.loads((BASE/'manifest.json').read_bytes())
    manifest={**origin,'candidate':NAME,'parent':'r13-514-abs15-rescue','comparison_baseline':'r13-514-abs15',
        'hashes':{f:sha(v) for f,v in files.items()},'parent_variant_hashes':EXPECTED,
        'proof_status':'DRAFT_ONLY_NOT_COMPILED; original re-extraction/obligation/axiom whitelist/roundtrip required',
        'performance_status':'Same exact Rust as discovery and independent confirmation; no new algorithm variant',
        'proof_change':'Adds local-step helper contract FoundAt; original probe/deepen/byte checks and surrounding loop invariant preserved. No new axioms or admission claims.',
        'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    files=generate();dest=ROOT/'candidates'/NAME
    if args.check:assert all((dest/f).read_bytes()==v for f,v in files.items())
    else:
        assert not dest.exists();dest.mkdir()
        for f,v in files.items():(dest/f).write_bytes(v)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(v) for f,v in files.items()},'status':'PROOF_DRAFT_ONLY_NOT_COMPILED'}))

if __name__=='__main__':main()
