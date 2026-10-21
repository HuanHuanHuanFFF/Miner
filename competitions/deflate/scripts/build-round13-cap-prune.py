"""Remove PC chain work when a validated match already reaches DEFLATE's cap."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round13-public-514'
NAME='r13-514-cap-prune'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')}
    origin=json.loads((BASE/'receipt.json').read_bytes())
    assert {f:sha(b)for f,b in raw.items()}==origin['files']
    rust=raw['parse.rs'].decode();a=rust.index('pub fn pc_f_deepen(');b=rust.index('/// `pc_record3_m`',a)
    old=rust[a:b];before='if dp >= 2 && c2 < c {';after='if dp >= 2 && c2 < c && g.0 < 258 {'
    assert old.count(before)==1;new=old.replace(before,after,1);rust=rust[:a]+new+rust[b:]
    before='''                let cl = prev[c % 32768] as usize;
                let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);'''
    after='''                let g = r13_pc_hint_deepen(input, &prev, c, p, f.0, f.1, dp, minl);'''
    assert rust.count(before)==1;rust=rust.replace(before,after,1)
    helper='''/// A validated length258 match cannot be improved by another capped match.
#[inline(always)]
pub fn r13_pc_hint_deepen(s: &[u8], prev: &[u32; 32768], c: usize, p: usize, l: usize, d: usize, dp: usize, minl: usize) -> (usize, usize) {
    if l >= 258 {
        (l, d)
    } else {
        let cl = prev[c % 32768] as usize;
        pc_f_deepen(s, prev, c, cl, p, l, d, dp, minl)
    }
}

'''
    marker='/// `pc_run1` with chain links and `pc_f_deepen` at every match of at least `minl` bytes.'
    assert rust.count(marker)==1;rust=rust.replace(marker,helper+marker,1)
    restored=rust.replace(helper,'',1).replace(after,before,1).replace(new,old,1)
    assert restored.encode()==raw['parse.rs']
    lean=raw['Parse.lean'].decode();marker='@[local step]\ntheorem f_record3_loop0_spec'
    lemma='''/-- Keep an already validated capped match; otherwise use the original PC validator. -/
@[local step]
theorem r13_pc_hint_deepen_spec (s : Slice Std.U8) (prev : Array Std.U32 32768#usize)
    (c p l d dp minl : Std.Usize) (hc : c.val ≤ p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.r13_pc_hint_deepen s prev c p l d dp minl ⦃ fun r => MatchAt s p.val r.1.val r.2.val ⦄ := by
  rw [slot.r13_pc_hint_deepen]
  step*
  all_goals first | exact hm | scalar_tac

'''
    assert lean.count(marker)==1;lean=lean.replace(marker,lemma+marker,1)
    # The old proof's branch automation covers the additional early exit from
    # the second link; actual extraction/gate must check this draft.
    files={'parse.rs':rust.encode(),'Parse.lean':lean.encode()}
    assert all(len(b)<=524288 for b in files.values())
    manifest={'candidate':NAME,'parent':'public514','formal_anchor_id':'514','comparison_baseline':'public514',
        'native_relation':'token_equality','hashes':{f:sha(b)for f,b in files.items()},'parent_original_hashes':origin['files'],
        'mechanism':'Skip all PC predecessor reads at an initial258 match and skip second-link reads if first-link validation reaches258. Search order, ties and byte validator unchanged.',
        'logical_basis':'pc_common_from is capped at258 and pc_f_try accepts only strictly longer matches. This removes dominated work rather than changing a tuning threshold.',
        'all_input_equivalence':'INFERRED under existing validated parser invariants; finite actual token/output comparison and original gate still required.',
        'proof_status':'DRAFT_UNCOMPILED; wrapper MatchAt bridge added, original obligation unchanged',
        'performance_status':'UNKNOWN; count reached-cap cases before allocating a timing comparison',
        'attribution':{'source':'Official public514; original headers retained','author_hotkey':origin['author_hotkey'],'reference':'references/round13-public-514/PROVENANCE.md'},
        'source_reversal':'Original parent bytes recovered by reversing exactly two call/condition edits and removing one helper.',
        'stop_condition':'Zero relevant cap opportunities, any token/decode failure, or no repeatable total-time improvement closes this frozen version.',
        'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();p=ROOT/'candidates'/NAME
    if args.check:assert all((p/f).read_bytes()==b for f,b in files.items())
    else:
        assert not p.exists();p.mkdir()
        for f,b in files.items():(p/f).write_bytes(b)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(b)for f,b in files.items()},'status':'DRAFT_NOT_TIMED_OR_PROVED'}))

if __name__=='__main__':main()
