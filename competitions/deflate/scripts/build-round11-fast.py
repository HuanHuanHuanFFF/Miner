"""Two bounded fast3 structural probes; no compilation or external actions.

pendingfold moves cancellation of pending literals before their stores.
continuation rescues a failed head candidate only after a full 258-byte match.
"""
from pathlib import Path
import argparse
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "candidates/r3-432-fast3"
PARENT_RS = "bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef"
PARENT_LEAN = "e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04"

PENDING = r'''/// R11: consume the pending literal suffix before writing tokens that fold would discard.
/// The original BACKTOK budget includes these literal bytes. Only after all pending
/// literals were consumed may the remaining budget reach previously emitted tokens.
#[inline(always)]
pub fn r11_pending_fold(input: &[u8], out: &mut [u32], nt0: usize, ls: usize, p0: usize, l0: usize, d: usize) -> (usize, usize, usize) {
    if ls < p0 && p0 <= input.len() && l0 <= 258 {
        let mut p = p0;
        let mut l = l0;
        let mut back = 0usize;
        let mut go = 1u32;
        while go == 1 && p > ls && back < BACKTOK && l < 258 && d < p {
            if input[p - 1] == input[p - 1 - d] {
                p -= 1;
                l += 1;
                back += 1;
            } else {
                go = 0;
            }
        }
        let nt = flush4(input, out, nt0, ls, p);
        if p == ls && back < BACKTOK {
            fold_bt(input, out, nt, p, l, d, BACKTOK - back)
        } else {
            (nt, p, l)
        }
    } else {
        let nt = flush4(input, out, nt0, ls, p0);
        fold_w(input, out, nt, p0, l0, d)
    }
}

'''

CONTINUATION = r'''/// R11: at a full-match boundary only, rescue a head whose candidate cannot
/// pass the existing prefix/distance test. Keep the original hash slot and all
/// insertions; the original next-loop probe performs the one length extension.
#[inline(always)]
pub fn r11_continuation(s: &[u8], p: usize, lim: usize, span: usize, d: usize, a: usize, c: usize, cw: u64, km: u32) -> (usize, usize, u64) {
    if span == 258 && p < lim && p <= s.len().saturating_sub(8) {
        let pw = be8(s, p);
        let old_d = p.wrapping_sub(c);
        if !(old_d.wrapping_sub(1) < 32768 && (((cw ^ pw) >> 32) & (km as u64)) == 0) {
            if d >= 1 && d <= 32768 && d <= p {
                let rc = p - d;
                let rw = be8(s, rc);
                if (((rw ^ pw) >> 32) & (km as u64)) == 0 {
                    return (a, rc, rw);
                }
            }
        }
    }
    (a, c, cw)
}

'''


def sha(b):
    return hashlib.sha256(b).hexdigest()


def generate(kind):
    raw = {n: (BASE / n).read_bytes() for n in ("parse.rs", "Parse.lean")}
    assert sha(raw["parse.rs"]) == PARENT_RS
    assert sha(raw["Parse.lean"]) == PARENT_LEAN
    text = raw["parse.rs"].decode()
    start = text.rfind("#[inline(always)]", 0, text.index("pub fn run1<const H: usize>"))
    end = text.index("/// The class itself when", start)
    original = text[start:end]
    if kind == "pendingfold":
        helper = PENDING
        old = "                nt = flush4(input, out, nt, ls, p);\n                let b = fold_w(input, out, nt, p, l, d);"
        new = "                let b = r11_pending_fold(input, out, nt, ls, p, l, d);"
        mechanism = "Consume a match's backward extension through still-pending literals before flush4; preserve the shared 64-token fold budget and use existing fold_bt for already-emitted tokens. Search/insert schedule is unchanged."
        equivalence = "INFERRED identical counted token prefix; fewer speculative/out-of-prefix stores. Native full-parser finite equality is still UNKNOWN."
        proof_cost = "New pending-literal extension invariant plus Dec/MatchAt composition; new helper spec before main1_loop_spec. Reuse fold_bt/flush4 and original match proof. Parent Lean is UNADAPTED."
        difference = "Not R4 flushzero or foldplain/inline: changes when pending bytes are materialized as tokens, removing writes later cancelled by backward fold. No constants changed."
    else:
        assert kind == "continuation"
        helper = CONTINUATION
        old = "                let a3 = ahead_fix_m::<H>(input, &head, p, lim, e, ae.0, ae.1, ae.2, pre_slot, pre_c, pre_w, km);"
        new = old + "\n                let a3 = r11_continuation(input, p, lim, b.2, d, a3.0, a3.1, a3.2, km);"
        mechanism = "Only after an emitted 258-byte run1 match, replace the next cached head candidate if its existing key/distance test fails and the same-distance continuation key matches. Original next-loop probe extends it; no second common-prefix search or new table."
        equivalence = "Tokens intentionally may change; old valid head candidates remain selected, but later parse schedule can change. Decode and both score axes are required; no size monotonicity claim."
        proof_cost = "New helper preserves pre_slot bound, pre_c<=p and pre_w=word8(input,pre_c). Existing MainInv1 permits arbitrary such candidates; original probe supplies MatchAt. No extra loop state. Parent Lean is UNADAPTED."
        difference = "Not NICE/depth/skip/lazy sweep. Not old round3-tiny-rep1: this changes large run1 at the exact DEFLATE max-length truncation boundary, only when the original candidate would fail, with no eager full match scan or tie preference."
    assert original.count(old) == 1
    changed = original.replace(old, new, 1)
    source = text[:start] + helper + changed + text[end:]
    assert source.replace(helper + changed, original, 1) == text
    name = "r11-fast-" + kind
    files = {"parse.rs": source.encode(), "Parse.lean": raw["Parse.lean"]}
    attribution = {
        "source": "Official public submission 432, then r3-432-fast3",
        "reference": "references/round3-public-432/PROVENANCE.md",
        "public_miner_hotkey": "5EAM7rJK571o7asrBBk6oozUZCRubR1tMiDKBNWmWhw66PRy",
        "named_author": "UNKNOWN; no name in official source response",
        "ownership": "Derivative of external public miner code; not an independent parser algorithm",
    }
    manifest = {
        "candidate": name, "parent": "candidates/r3-432-fast3",
        "parent_hashes": {"parse.rs": PARENT_RS, "Parse.lean": PARENT_LEAN},
        "hashes": {n: sha(b) for n,b in files.items()},
        "attribution": attribution, "mechanism": mechanism,
        "difference_from_old_work": difference, "equivalence_status": equivalence,
        "proof_status": "UNADAPTED_PARENT_ONLY; official extraction/original obligation/axiom gate UNKNOWN",
        "proof_cost": proof_cost,
        "audit": "One isolated run1 call-site replacement and one helper; reverse replacement restores exact parent bytes. All constants and routing unchanged.",
        "performance_status": "UNKNOWN; parser was only 16.39% of diagnostic component time in R3. Instruction/store reduction is not a total-time claim.",
        "stop_condition": "Decode failure stops immediately. Pendingfold token difference rejects its equivalence premise. No improvement of current two-axis frontier projection or total-time regression closes the candidate; no parameter sweep.",
        "formal_submission_sent": False,
    }
    files["manifest.json"] = (json.dumps(manifest,ensure_ascii=False,indent=2)+"\n").encode()
    return name,files


def model():
    """Finite reference check of scheduling, including budget and match-token boundaries."""
    rng=random.Random(110810)
    base=16777216
    def word(s,p):
        return int.from_bytes(s[p:p+8],"big") if p+8<=len(s) else 0
    def fold(s,out,nt,p,l,d,bt):
        back=0
        while back<bt and nt>0 and nt<=len(out) and l<258 and d<p:
            t=out[nt-1]
            if t<256 and s[p-1]==s[p-1-d]:
                p-=1;nt-=1;l+=1;back+=1
            elif t>=base:
                w=(t-base)%256+3
                if l+w<=258 and w<=p and d<=p-w and s[p-w-d:p-d]==s[p-w:p]:
                    p-=w;nt-=1;l+=w;back+=1
                else: break
            else: break
        return nt,p,l
    def foldw(s,out,nt,p,l,d):
        m=1
        if 0<nt<=len(out) and out[nt-1]>=base:m=min(8,(out[nt-1]-base)%256+3)
        x=1
        if d<p and p-d>=8 and p<=len(s):x=(word(s,p-8)^word(s,p-8-d))&((1<<(8*m))-1)
        if x!=0 and d<p and p-d>=8:return nt,p,l
        return fold(s,out,nt,p,l,d,64)
    counts={"cases":0,"pending_consumed":0,"budget_exhausted":0,"length_cap":0,"crossed_into_old_tokens":0}
    for case in range(30000):
        n=512;r=rng.randrange(1,40);pat=bytes(rng.randrange(8) for _ in range(r));s=(pat*((n+r-1)//r))[:n]
        if case%3==0:s=bytes(rng.randrange(8) for _ in range(n))
        ls=rng.randrange(0,256);pending=rng.choice([0,1,2,3,4,63,64,65,127,rng.randrange(128)]);p0=ls+pending
        d=rng.choice([0,1,r,max(0,p0-1),p0,p0+1]);l0=rng.choice([3,4,8,193,194,257,258,rng.randrange(3,259)])
        old=[];pos=0
        while pos<ls:
            room=ls-pos
            if room>=3 and rng.randrange(4)==0:
                w=rng.randrange(3,min(258,room)+1);old.append(base+w-3);pos+=w
            else:old.append(s[pos]);pos+=1
        refout=old+list(s[ls:p0]);ref=foldw(s,refout,len(refout),p0,l0,d)
        p=p0;l=l0;back=0
        if ls<p0 and p0<=n and l0<=258:
            while p>ls and back<64 and l<258 and d<p:
                if s[p-1]!=s[p-1-d]:break
                p-=1;l+=1;back+=1
            newout=old+list(s[ls:p]);nt=len(newout)
            if p==ls and back<64:res=fold(s,newout,nt,p,l,d,64-back)
            else:res=(nt,p,l)
        else:
            newout=old+list(s[ls:p0]);res=foldw(s,newout,len(newout),p0,l0,d)
        assert ref==res,(case,ls,pending,d,l0,ref,res)
        assert refout[:ref[0]]==newout[:res[0]]
        counts['cases']+=1;counts['pending_consumed']+=back
        counts['budget_exhausted']+=back==64;counts['length_cap']+=l==258
        counts['crossed_into_old_tokens']+=res[1]<ls
    return {"status":"VERIFIED_FINITE_HELPER_SCHEDULING_MODEL","seed":110810,**counts,"limits":"Reference model, not native Rust, full parser equivalence, proof, or performance evidence. Synthetic prefix tokens need not decode; the check targets fold scheduling for arbitrary token-tag patterns."}


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check',action='store_true')
    ap.add_argument('--model',action='store_true')
    args=ap.parse_args()
    for kind in ('pendingfold','continuation'):
        name,files=generate(kind);dest=ROOT/'candidates'/name
        if args.check:
            assert all((dest/n).read_bytes()==b for n,b in files.items())
        else:
            dest.mkdir(parents=True,exist_ok=True)
            for n,b in files.items():(dest/n).write_bytes(b)
        print(json.dumps({'candidate':name,'hashes':{n:sha(b) for n,b in files.items()}},ensure_ascii=False))
    if args.model:
        result=model();print(json.dumps(result,ensure_ascii=False))
        if not args.check:(ROOT/'candidates/r11-fast-pendingfold/model.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')


if __name__=='__main__':main()
