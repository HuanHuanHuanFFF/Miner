"""One extra predecessor and one measured gain-filter composition after depth2 feedback."""
from pathlib import Path
import hashlib,json,copy
ROOT=Path(__file__).resolve().parents[1]
HELPER='''
#[inline(always)]
pub fn r15_deepen3(s: &[u8], prev: &[u16; 32768], c: usize, c2: usize, p: usize, l: usize, d: usize, dp: usize, minl: usize) -> (usize, usize) {
    let g = pc_f_deepen(s, prev, c, c2, p, l, d, dp, minl);
    if dp >= 3 && c2 < c {
        let c3 = r13_prev_unwrap(c2, prev[c2 % 32768]);
        if c3 < c2 {
            let c4 = r13_prev_unwrap(c3, prev[c3 % 32768]);
            pc_f_try(s, c3, c4, p, g.0, g.1, minl)
        } else { g }
    } else { g }
}
'''
LEMMA='''@[local step]
theorem r15_deepen3_spec (s : Slice Std.U8) (prev : Array Std.U16 32768#usize)
    (c c2 p l d dp minl : Std.Usize) (hc : c.val ≤ p.val) (hm : MatchAt s p.val l.val d.val) :
    slot.r15_deepen3 s prev c c2 p l d dp minl ⦃ fun r => MatchAt s p.val r.1.val r.2.val ⦄ := by
  rw [slot.r15_deepen3]
  step*
  all_goals try (obtain ⟨g1, g2⟩ := g; dsimp only at *; step*)

'''
def main():
    p=ROOT/'candidates/r15-hash32-chain-depth2';rust=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text();variants=[]
    a=rust.index('pub fn pc_f_try(');b=rust.index('pub fn pc_f_deepen(',a);part=rust[a:b];needle='if m > l && m >= minl {';assert part.count(needle)==1
    gain=rust[:a]+part.replace(needle,'if m > l && m >= minl && pc_gain(m, d2) > pc_gain(l, d) {')+rust[b:]
    variants.append(('r15-hash32-depth2-gain',gain,proof,'Combine measured depth2 quality with measured gain filtering; actual combined output and time are required.'))
    call='let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);';assert rust.count(call)==1
    deeper=rust.replace(call,call.replace('pc_f_deepen','r15_deepen3'))+HELPER
    needle='pub fn p125_row1(input:&[u8],out:&mut[u32])->usize{pc_run1c::<32768>(input,out,4,0,1000000,4294967295,2,4)}';assert deeper.count(needle)==1;deeper=deeper.replace(needle,needle.replace('4294967295,2,4','4294967295,3,4'))
    needle='@[local step]\ntheorem f_record3_loop0_spec';assert proof.count(needle)==1;deeper_proof=proof.replace(needle,LEMMA+needle)
    variants.append(('r15-hash32-chain-depth3',deeper,deeper_proof,'One genuinely additional predecessor after depth2 saved21999B but modeled only0.3265percent share; target further useful compression, not a timing delay.'))
    E=ROOT/'evidence/round15';s=json.loads((E/'tradeoff-b-native.json').read_bytes());entries=[copy.deepcopy(e)for e in s['entries']if e['control']];parent_entry=copy.deepcopy(next(e for e in s['entries']if e['name']=='r15-hash32-chain-depth2'));parent_entry['control']=True;parent_entry.pop('native_decode_reference',None);entries.append(parent_entry)
    for name,code,lean,mechanism in variants:
        dest=ROOT/'candidates'/name;dest.mkdir(exist_ok=True);data={'parse.rs':code.encode(),'Parse.lean':lean.encode()}
        for f,b in data.items():assert not(dest/f).exists()or(dest/f).read_bytes()==b;(dest/f).write_bytes(b)
        hashes={f:hashlib.sha256(b).hexdigest()for f,b in data.items()};manifest={'candidate':name,'parent':'r15-hash32-chain-depth2','formal_anchor_id':'514','comparison_baseline':'r15-hash32-chain-depth2','hashes':hashes,'mechanism':mechanism,'attribution':json.loads((p/'manifest.json').read_bytes())['attribution'],'proof_status':'DRAFT_UNCOMPILED_FOR_NEW_RUST','performance_status':'UNKNOWN','formal_submission_sent':False};(dest/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode());entries.append({'name':name,'path':f'candidates/{name}','control':False,'anchor':'public514','comparison_baseline':'r15-hash32-chain-depth2','native_decode_reference':'r15-hash32-chain-depth2','hashes':hashes})
    s.update(entries=entries,native_encoder_references=['r14-514-hash32','r15-hash32-chain-depth2'],screen_orders=[[e['name']for e in entries],[e['name']for e in reversed(entries)]],description='R15 G: depth2 actual quality gain was0.09382pp with0.5883percent time cost and0.3265percent conditional share. Test one extra predecessor and one gain composition for enough additional compression. Both need actual byte and paired timing validation; no additive assumptions.')
    (E/'deeper-g-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps({'candidates':[v[0]for v in variants]}))
if __name__=='__main__':main()
