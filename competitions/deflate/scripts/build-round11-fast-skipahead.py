"""Predict the original miss destination before probe, for the non-lazy run1 path.

No search parameter changes. Proof is a source-level draft until real extraction.
"""
from pathlib import Path
import argparse, hashlib, json, random

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r3-432-fast3'
NAME='r11-fast-skipahead'

HELPERS=r'''/// R11: exact original miss destination; lazy paths still pre-read p+1.
#[inline(always)]
pub fn r11_next(p: usize, miss: usize, skip: usize, skcap: usize, lim: usize, lazy: usize) -> usize {
    if p < lim {
        let q = p + 1;
        if lazy == 0 {
            let step = skip_len(miss.wrapping_add(1), skip, skcap);
            skip_to(q, step, lim)
        } else { q }
    } else { lim }
}

/// R11: forecast may target beyond ins. Recording must still use ins's own key.
/// Backward fold changes the output start, but does not change this insertion cursor.
#[inline(always)]
pub fn r11_record_slot<const H: usize>(s: &[u8], ins: usize, lim: usize, forecast: usize, slot: usize, lazy: usize, km: u32) -> usize {
    if lazy == 0 && forecast != ins && ins < lim {
        slot_of_m::<H>(s, ins, km)
    } else { slot }
}

'''

PROOF=r'''/-! R11 source-level proof bridge draft. Actual new extraction and Lean gate
have NOT been run. The rule concerns bounds, not forecast/search equivalence. -/

@[local step]
theorem r11_next_spec (p miss skip skcap lim lazy : Std.Usize)
    (hp : p.val < lim.val) (hskip : skip.val < 32) :
    slot.r11_next p miss skip skcap lim lazy ⦃ fun r => p.val < r.val ∧ r.val ≤ lim.val ⦄ := by
  rw [slot.r11_next]
  step*
  all_goals first
    | exact ⟨by scalar_tac, by scalar_tac⟩
    | scalar_tac

@[local step]
theorem r11_record_slot_spec (H : Std.Usize) (s : Slice Std.U8)
    (ins lim forecast a lazy : Std.Usize) (km : Std.U32)
    (hlim : lim.val + 8 = s.length) (ha : a.val < H.val) (hH : 0 < H.val) :
    slot.r11_record_slot H s ins lim forecast a lazy km ⦃ fun r => r.val < H.val ⦄ := by
  rw [slot.r11_record_slot]
  have hmax : s.length ≤ Std.Usize.max := Std.Slice.length_ineq s
  step*

'''


def sha(b):return hashlib.sha256(b).hexdigest()


def generate():
    raw={n:(BASE/n).read_bytes()for n in ('parse.rs','Parse.lean')}
    assert sha(raw['parse.rs'])=='bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef'
    assert sha(raw['Parse.lean'])=='e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04'
    text=raw['parse.rs'].decode();a=text.rfind('#[inline(always)]',0,text.index('pub fn run1<const H: usize>'));b=text.index('/// The class itself when',a);old=text[a:b];new=old
    edits=[
        ('            let a1 = ahead_if_m::<H>(input, &head, p + 1, lim, pre_slot, pre_c, pre_w, km);','            let forecast = r11_next(p, miss, skip, skcap, lim, lazy);\n            let a1 = ahead_if_m::<H>(input, &head, forecast, lim, pre_slot, pre_c, pre_w, km);'),
        ('                record3_m::<H>(input, &mut head, ins, pre_slot, end, lim, km);','                let record_slot = r11_record_slot::<H>(input, ins, lim, forecast, pre_slot, lazy, km);\n                record3_m::<H>(input, &mut head, ins, record_slot, end, lim, km);'),
    ]
    old_miss='''                p += 1;
                miss += 1;
                let step = skip_len(miss, skip, skcap);
                if step > 0 {
                    p = skip_to(p, step, lim);
                    let a4 = ahead_if_m::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w, km);
                    pre_slot = a4.0;
                    pre_c = a4.1;
                    pre_w = a4.2;
                }'''
    new_miss='''                p += 1;
                miss += 1;
                if lazy == 0 {
                    p = forecast;
                } else {
                    let step = skip_len(miss, skip, skcap);
                    if step > 0 {
                        p = skip_to(p, step, lim);
                        let a4 = ahead_if_m::<H>(input, &head, p, lim, pre_slot, pre_c, pre_w, km);
                        pre_slot = a4.0;
                        pre_c = a4.1;
                        pre_w = a4.2;
                    }
                }'''
    edits.append((old_miss,new_miss))
    for x,y in edits:assert new.count(x)==1;new=new.replace(x,y,1)
    back=new
    for x,y in reversed(edits):back=back.replace(y,x,1)
    assert back==old
    rust=(text[:a]+HELPERS+new+text[b:]).encode()
    assert rust.decode().replace(HELPERS+new,old,1)==text
    proof=raw['Parse.lean'].decode();marker='/-- `ahead` with keys under `km`. -/'
    assert proof.count(marker)==1
    lean=proof.replace(marker,PROOF+marker,1);assert lean.replace(PROOF,'',1)==proof
    files={'parse.rs':rust,'Parse.lean':lean.encode()}
    manifest={'candidate':NAME,'parent':'candidates/r3-432-fast3','parent_hashes':{n:sha(v)for n,v in raw.items()},'hashes':{n:sha(v)for n,v in files.items()},'attribution':{'source':'Public #432 via fast3','reference':'references/round3-public-432/PROVENANCE.md','author_hotkey':'5EAM7rJK571o7asrBBk6oozUZCRubR1tMiDKBNWmWhw66PRy','ownership':'Derivative of external public miner code'},'mechanism':'For lazy=0 run1, pre-read the exact destination of a hypothetical current miss, after recording current p but before probe. A real miss reuses it instead of discarding p+1 and issuing another head/candidate-word load. A real match repairs the first insertion slot to ins; original lazy path is retained.','difference':'R4 slotonly gated successful non-lazy matches after probe; R4 endreload moved only match-end loads. This keeps early overlap and changes only the skip-miss lookahead destination. No skip/depth/NICE/lazy/layout constants changed.','equivalence_status':'INFERRED valid parser state; native444/public equality REQUIRED','proof_status':'SOURCE_INTERFACE_DRAFT_UNCOMPILED; new helper names/types and unchanged main-loop shape require real extraction and original gate','invariants':['head_set(current p) precedes forecast read; same-slot collisions therefore see p exactly as original late miss reload','No table writes occur between original p+1 read and miss reload','When forecast!=ins, compute slot_of_m(ins) for record3, even if backward fold changes match start; ins and end retain original meanings','If lazy>0 forecast=p+1, record_slot retains old pre_slot, miss reload remains old code','Forecast reaching lim may retain a different unused cache tuple; loop exits before consuming it'],'expected_counters':['run1 loop iterations','lazy0 forecast>p+1','actual skipped miss reuses','match branch first-slot repairs','lazy>0 untouched path'],'cost_risks':['Forecast arithmetic is paid before knowing match/miss','A match after a predicted skip recomputes insertion slot','Extra live forecast register may spill or alter scheduling','Parser component was15.8% of current diagnostic sum; total-axis gain is not implied'],'asm_evidence':'R4 raw baseline assembly at11000..1106b performs miss shift/cap then new hash/head/candidate-word reload; source also issues p+1 read before probe. No new assembly or hardware profile yet.','stops':['Any native/public token or decode mismatch','No removable skip-miss events or repair work dominates','No paired total compression improvement beyond control movement'],'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode()
    return files


def model():
    rng=random.Random(115511);tests=0;collisions=0;past=0;repairs=0
    for _ in range(4000):
        H=rng.choice([16,32]);s=bytes(rng.randrange(8)for _ in range(512));p=rng.randrange(0,480);lim=504;miss=rng.randrange(0,p+1);skip=rng.choice([3,4,5]);cap=rng.choice([8,1000000]);km=rng.choice([0xffffffff,0xffffff00])
        def slot(i):
            k=int.from_bytes(s[i:i+4],'big')&km
            return (((k*0x9e3779b97f4a7c15)&((1<<64)-1))>>49)%H
        def word(i):return int.from_bytes(s[i:i+8],'big')
        h=[rng.randrange(p+1)for _ in range(H)];h[slot(p)]=p;oldcache=(slot(p),p,word(p))
        def ahead(i,fallback):return (slot(i),h[slot(i)],word(h[slot(i)]))if i<lim else fallback
        first=ahead(p+1,oldcache);step=min((miss+1)>>skip,cap);target=min(lim,p+1+step);oldnext=ahead(target,first)if step else first;newnext=ahead(target,oldcache)
        if target<lim:assert oldnext==newnext
        else:past+=1
        collisions+=target<lim and slot(target)==slot(p)
        length=rng.randrange(3,min(258,512-p)+1);end=p+length;ins=p+1
        oldslot=first[0];newslot=slot(ins)if target!=ins and ins<lim else newnext[0]
        if ins<min(end,ins+2,lim):assert oldslot==newslot
        repairs+=target!=ins and ins<lim;tests+=1
    return {'status':'FINITE_SOURCE_STATE_MODEL_ONLY','cases':tests,'seed':115511,'same_slot_forecasts':collisions,'forecast_reaches_limit':past,'match_first_slot_repairs':repairs,'limits':'No Rust execution. Covers valid-state miss cache identity and actual insertion slot; native whole-parser equality remains required.'}


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');ap.add_argument('--model',action='store_true');args=ap.parse_args();files=generate();dest=ROOT/'candidates'/NAME
    if args.check:assert all((dest/n).read_bytes()==v for n,v in files.items())
    else:
        dest.mkdir(parents=True,exist_ok=True)
        for n,v in files.items():(dest/n).write_bytes(v)
    print(json.dumps({'candidate':NAME,'hashes':{n:sha(v)for n,v in files.items()}},indent=2))
    if args.model:
        m=model();print(json.dumps(m))
        if not args.check:(dest/'model.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf-8')


if __name__=='__main__':main()
