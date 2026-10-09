"""Avoid next-candidate word reads that lazy0 matched paths do not consume."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-514';NAME='r13-514-match-ahead'

HELPER='''/// Matched lazy0 paths need the next insertion key, but not its candidate word.
#[inline(always)]
pub fn r13_pc_ahead_after_m<const H: usize>(s: &[u8], head: &[u32; H], i: usize, lim: usize, a: usize, c: usize, w: u64, km: u32, lazy: usize, found: usize) -> (usize, usize, u64) {
    if lazy == 0 && found >= 3 && i < lim {
        (pc_slot_of_m::<H>(s,i,km),c,w)
    } else {
        pc_ahead_if_m::<H>(s,head,i,lim,a,c,w,km)
    }
}

'''

LEMMA='''/-- Preserve the original cache bound and actual cached word while skipping unused next-word work. -/
@[local step]
theorem r13_pc_ahead_after_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim a c : Std.Usize) (w : Std.U64) (km : Std.U32) (lazy found : Std.Usize)
    (B : Nat) (hB : HeadBound head B) (hBi : B < i.val + 1)
    (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)
    (hc : c.val < B + 1) (hw : w.val = word8 s c.val) (hH : 0 < H.val) :
    slot.r13_pc_ahead_after_m s head i lim a c w km lazy found ⦃ fun r =>
      r.1.val < H.val ∧ r.2.1.val ≤ B ∧ r.2.2.val = word8 s r.2.1.val ⦄ := by
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  rw [slot.r13_pc_ahead_after_m]
  step*
  repeat' (split <;> step*)
  all_goals first | assumption | exact ⟨by assumption, by scalar_tac, by assumption⟩ | scalar_tac

'''

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};origin=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(b)for f,b in raw.items()}==origin['files']
    original=raw['parse.rs'].decode();a=original.index('pub fn pc_run1c<const H: usize>');b=original.index('/// Structured binaries (class 3)',a);old=original[a:b];body=old
    probe='            let f = pc_probe_m(input, c, cw, p, km);\n';link='            pc_f_link::<H>(&mut head, &mut prev, pre_slot, p);\n'
    assert body.count(probe)==1 and body.count(link)==1;body=body.replace(probe,'',1).replace(link,probe+link,1)
    before='let a1 = pc_ahead_if_m::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, km);'
    after='let a1 = r13_pc_ahead_after_m::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, km, lazy, f.0);'
    assert body.count(before)==1;body=body.replace(before,after,1)
    rust=original[:a]+body+original[b:];marker='/// `pc_run1` with chain links and `pc_f_deepen` at every match of at least `minl` bytes.';assert rust.count(marker)==1;rust=rust.replace(marker,HELPER+marker,1)
    assert rust.replace(HELPER,'',1).replace(body,old,1).encode()==raw['parse.rs']
    lean=raw['Parse.lean'].decode();a=lean.index('namespace PC');b=lean.index('end PC',a);section=lean[a:b];marker='@[local step]\ntheorem ahead_fix_m_spec';assert section.count(marker)==1;section=section.replace(marker,LEMMA+marker,1);proof=(lean[:a]+section+lean[b:]).encode()
    assert proof.decode().replace(LEMMA,'',1).encode()==raw['Parse.lean']
    files={'parse.rs':rust.encode(),'Parse.lean':proof};assert all(len(x)<=524288 for x in files.values())
    manifest={'candidate':NAME,'parent':'public514','formal_anchor_id':'514','comparison_baseline':'public514','native_relation':'token_equality','hashes':{f:sha(x)for f,x in files.items()},'parent_original_hashes':origin['files'],
        'mechanism':'Compute the pure current probe before next-position ahead. On matched lazy0 paths, calculate only the insertion key and reuse current coherent candidate/word; elsewhere call original full ahead. Original chains, insertion order, search depths and all routes unchanged.',
        'evidence_basis':'Public PC observer counted1014141 matched/deepen requests; unlike rare1633 cap exits, matched lazy0 paths frequently do not consume next-candidate words. Both original PC row0/1 use lazy0.',
        'difference_from_previous':'Different from earlier D-family preloading/pipeline tests. Eliminates unused matched-path head/word work rather than moving required loads or changing table shape; miss paths still pay full ahead and may lose overlap.',
        'attribution':{'source':'Official public514; original headers retained','author_hotkey':origin['author_hotkey'],'reference':'references/round13-public-514/PROVENANCE.md'},
        'source_reversal':'Remove one helper, restore one ahead call and original pure-probe order to recover exact parent bytes; Lean differs by one cache-spec draft.',
        'equality_status':'INFERRED unused-word argument. Next slot equals original for first record insertion; lazy0 loop cannot consume cached next candidate; final ahead refreshes for live next positions. Actual finite/public equality required, not universal certificate.',
        'proof_status':'DRAFT_UNCOMPILED; new cache lemma keeps original bound/word postcondition, original main proof and obligation retained',
        'performance_status':'UNKNOWN; one-million opportunity count is not saved time; branch/overlap costs may cancel it','formal_submission_sent':False,
        'stop_condition':'Any finite/public token/decode mismatch stops this source; no worthwhile repeated paired total-time improvement closes it. Full original gate remains mandatory.'}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();p=ROOT/'candidates'/NAME
    if args.check:assert all((p/f).read_bytes()==x for f,x in files.items())
    else:
        assert not p.exists();p.mkdir()
        for f,x in files.items():(p/f).write_bytes(x)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(x)for f,x in files.items()},'status':'DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
