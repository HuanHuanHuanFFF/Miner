"""C3: stop O_A immediate-accept discovery at 64; trusted emitter finishes once."""
from pathlib import Path
import hashlib, importlib, json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round26-public-658'
OUT=ROOT/'evidence/round26/extension1h/route-c'
NAME='r26-c-658-deferred-extension'
RUST='1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad'
LEAN='354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494'
HELP=importlib.import_module('r26-a-rep-shadow')

EMITTER=r'''
// C3: keep byte verification in emission, but finish an immediate-accept long
// match there instead of fully extending it once in discovery and once again here.
// Only O_A greedy consumes this helper; symbol-replay and N70 stay unchanged.
#[inline(always)]
pub fn c3_emit_step(input:&[u8],out:&mut[u32],pos:usize,d:usize,l:usize,lits:usize,ntok:usize)->(usize,usize){
    let n=input.len();
    if l==64 && n>=8 && pos<=n-8 && d>=1 && d<=32768 && d<=pos {
        let rem=n-pos-8;
        let cap=if rem<258{rem}else{258};
        if cap>=64 {
            let full=o_a_match_len(input,pos-d,pos,cap);
            if full>=64 {
                out[ntok]=16777216u32+((d-1)as u32)*256+((full-3)as u32);
                return(ntok+1,pos+full);
            } else {
                return o_a_emit_lits(input,out,pos,lits,ntok);
            }
        }
    }
    o_a_emit_step(input,out,pos,d,l,lits,ntok)
}
'''

def sha(b):return hashlib.sha256(b).hexdigest()
def dump(p,x):p.write_bytes((json.dumps(x,indent=2,ensure_ascii=False)+'\n').encode())
def source():
    raw=(BASE/'parse.rs').read_bytes(); assert sha(raw)==RUST
    def eval_edit(s):
        old='o_a_fast_len(input, c.wrapping_sub(1), p, cap)'
        return HELP.once(s,old,'o_a_fast_len(input, c.wrapping_sub(1), p, if cap > 64 { 64 } else { cap })')
    text=HELP.edit_fn(raw.decode(),'o_a_eval(',eval_edit)
    text=HELP.edit_fn(text,'o_a_run_greedy<',lambda s:HELP.once(s,'o_a_emit_step(input, out, pos, d, l, 1, ntok)','c3_emit_step(input, out, pos, d, l, 1, ntok)'))
    return(text+EMITTER).encode()

def main():
    p=ROOT/'candidates'/NAME; assert not p.exists();p.mkdir()
    raw=source(); lean=(BASE/'Parse.lean').read_bytes();assert sha(lean)==LEAN
    (p/'parse.rs').write_bytes(raw);(p/'Parse.lean').write_bytes(lean)
    hashes={'parse.rs':sha(raw),'Parse.lean':sha(lean)}
    dump(p/'manifest.json',{'candidate':NAME,'parent':'references/round26-public-658','hashes':hashes,
       'attribution':{'source_receipt':'references/round26-public-658/source-receipt.json','author_hotkey':'5G3YLL7PuDhRBoVoDBYKhAfTxFM4EouSDiYuFXeeWciNRzyK'},
       'mechanism':'Only O_A base eval caps discovery at64, the largest active O_A lazy threshold. Immediate-accept matches are finished by the original trusted o_a_match_len during emission, whose verified length is then emitted directly. Short/lazy suggestions use original emitter; N70, replay and all other emitters unchanged.',
       'actual_scope':'O_A greedy paths (docs/prose and any existing sparse restart). All routing/classifiers unchanged. No file identity, search budget or table modification.',
       'safety':'New emitter validates source/window/range, caps to min258,n-pos-8 and uses original proven match_len; emits only full>=64, otherwise original literal fallback. It never emits unverified hinted bytes.',
       'equivalence':'INFERRED for active O_A thresholds<=64 and BEXT=0. Near-tail source cap remains n-pos-8. Real native output may change and must be measured; no all-input equality claim.',
       'proof_status':'DRAFT_PARENT_SCAFFOLD. New c3_emit_step_spec must use EO.EA.match_len_spec and emit_match, with original emit_step_spec fallback; greedy loop switches the local step lemma. Exact extraction/fullgate NOT_RUN. No need to prove the untrusted search yields valid matches.',
       'performance':'UNKNOWN. Save discovery reads beyond64 for accepted longmatches; extra conditional/entry overhead and trusted fullscan remain.',
       'formal_submission_sent':False})
    e={'name':NAME,'path':p.relative_to(ROOT).as_posix(),'control':False,'anchor':'public658','comparison_baseline':'public658','native_decode_reference':'public658','hashes':hashes}
    dump(OUT/'c3-entry.json',e); print(json.dumps(e,indent=2))

if __name__=='__main__':main()
