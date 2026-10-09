"""Skip unused next-candidate word loads after a rejected lazy lookahead."""
from pathlib import Path
import copy,hashlib,json

ROOT=Path(__file__).resolve().parents[1]
HELPER='''/// A rejected lazy probe needs only the next insertion slot, not its candidate word.
#[inline(always)]
pub fn r16_pc_ahead_lazy_m<const H: usize>(s: &[u8], head: &[u32; H], i: usize, lim: usize, a: usize, c: usize, w: u64, km: u32, take: bool) -> (usize, usize, u64) {
    if !take && i < lim {
        (pc_slot_of_m::<H>(s, i, km), c, w)
    } else {
        pc_ahead_if_m::<H>(s, head, i, lim, a, c, w, km)
    }
}

'''
LEMMA='''@[local step]
theorem r16_pc_ahead_lazy_m_spec {H : Std.Usize} (s : Slice Std.U8) (head : Array Std.U32 H)
    (i lim a c : Std.Usize) (w : Std.U64) (km : Std.U32) (take : Bool)
    (B : Nat) (hB : HeadBound head B) (hBi : B < i.val + 1)
    (hlim : lim.val + 8 = s.length) (ha : a.val < H.val)
    (hc : c.val < B + 1) (hw : w.val = word8 s c.val) (hH : 0 < H.val) :
    slot.r16_pc_ahead_lazy_m s head i lim a c w km take ⦃ fun r =>
      r.1.val < H.val ∧ r.2.1.val ≤ B ∧ r.2.2.val = word8 s r.2.1.val ⦄ := by
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  rw [slot.r16_pc_ahead_lazy_m]
  step*
  repeat' (split <;> step*)
  all_goals first | assumption | exact ⟨by assumption, by scalar_tac, by assumption⟩ | scalar_tac

'''

def main():
    parent='r16-514-lazy8-depth2';name='r16-514-demand';p=ROOT/'candidates'/parent
    original=(p/'parse.rs').read_text();start=original.index('pub fn pc_run1c<const H: usize>');end=original.index('/// Structured binaries (class 3)',start);old=original[start:end]
    before='''                    let a2 = pc_ahead_if_m::<H>(input, &head, q + 1, lim, pre_slot, pre_c, pre_w, km);
                    pre_slot = a2.0;
                    pre_c = a2.1;
                    pre_w = a2.2;
                    let g = pc_probe_lazy(input, c2, w2, q, l);
                    if g.0 >= 4 && pc_gain(g.0, g.1) > pc_gain(l, d) {'''
    after='''                    let g = pc_probe_lazy(input, c2, w2, q, l);
                    let take = g.0 >= 4 && pc_gain(g.0, g.1) > pc_gain(l, d);
                    let a2 = r16_pc_ahead_lazy_m::<H>(input, &head, q + 1, lim, pre_slot, pre_c, pre_w, km, take);
                    pre_slot = a2.0;
                    pre_c = a2.1;
                    pre_w = a2.2;
                    if take {'''
    assert old.count(before)==1;body=old.replace(before,after);rust=original[:start]+body+original[end:]
    marker='/// `pc_run1` with chain links and `pc_f_deepen` at every match of at least `minl` bytes.';assert rust.count(marker)==1;rust=rust.replace(marker,HELPER+marker)
    assert rust.replace(HELPER,'').replace(body,old)==original
    proof=(p/'Parse.lean').read_text();marker='@[local step]\ntheorem ahead_fix_m_spec'
    a=proof.index('namespace PC');b=proof.index('end PC',a);section=proof[a:b]
    assert section.count(marker)==1
    proof=proof[:a]+section.replace(marker,LEMMA+marker)+proof[b:]
    d=ROOT/'candidates'/name;d.mkdir(exist_ok=True);data={'parse.rs':rust.encode(),'Parse.lean':proof.encode()}
    for f,b in data.items():
        assert len(b)<=524288 and (not(d/f).exists() or (d/f).read_bytes()==b)
        (d/f).write_bytes(b)
    hashes={f:hashlib.sha256(b).hexdigest()for f,b in data.items()}
    m={'candidate':name,'parent':parent,'comparison_baseline':parent,'formal_anchor_id':'514','hashes':hashes,'attribution':json.loads((p/'manifest.json').read_bytes())['attribution'],'mechanism':'After lazy probe rejection, compute next insertion hash only and retain coherent oldcandidate/word. Acceptance preservesoriginalahead. Originalgain, acceptedmatches andinsertionorder intendedunchanged.','difference_from_old_work':'R13 match-ahead movedmainprobe andhurt lazy0. Here mainprobeandinitialahead stayunchanged; only active lazy rejection uses savedwork, with predicate alreadyneeded foracceptance.','evidence_basis':'R16 B increased parseraxis onchangedfiles accountsformostlazy8cost. Test actualtoken equivalence, thenpairedtotaltime; no instructioncount promotion.','proof_status':'DRAFT_CACHE_LEMMA_UNCOMPILED; ORIGINAL_OBLIGATION_REQUIRED','equivalence_status':'INFERRED; finite/public check pending','performance_status':'UNKNOWN','formal_submission_sent':False}
    (d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
    s=json.loads((ROOT/'evidence/round16/quality-f-native.json').read_bytes());s['entries']=[e for e in s['entries']if e['control']]+[{'name':name,'path':'candidates/'+name,'control':False,'anchor':'public514','comparison_baseline':parent,'expected_equivalent_to':parent,'hashes':hashes}]
    s.update(native_encoder=False,native_encoder_references=[],screen_orders=[[e['name']for e in s['entries']],[e['name']for e in reversed(s['entries'])]],description='R16 G finite/public equivalence beforecostallocation: do not loadunusednextcandidateafterlazysteprejected. Currentmeasuredlazy8costis+1.5766percentvsabs15. Newcodechangesactive lazy path, unlike failedR13lazy0mainprobe reorder. Anytoken/decode mismatchstops this exactversion.')
    (ROOT/'evidence/round16/demand-g-native.json').write_text(json.dumps(s,indent=2)+'\n')
    print(json.dumps({'candidate':name,'hashes':hashes}))

if __name__=='__main__':main()
