"""One ablation of the DNA prototype's added backward-fold work."""
from pathlib import Path
import json,hashlib,copy
ROOT=Path(__file__).resolve().parents[1]
def main():
    p=ROOT/'candidates/r14-514-dna-direct';rust=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text()
    a=rust.index('pub fn pc_run1<const H: usize>');b=rust.index('/// The class itself when',a);body=rust[a:b]
    old='let b = pc_fold_w(input, out, nt, p, l, d);';assert body.count(old)==1
    body=body.replace(old,'let b = r14_fold_optional(input, out, nt, p, l, d, km);')
    rust=rust[:a]+body+rust[b:]
    rust+='''\n#[inline(always)]
pub fn r14_fold_optional(input: &[u8], out: &[u32], nt: usize, p: usize, l: usize, d: usize, km: u32) -> (usize, usize, usize) {
    if km == 0 { (nt, p, l) } else { pc_fold_w(input, out, nt, p, l, d) }
}
'''
    a=proof.index('theorem fold_w_spec',proof.index('namespace PC'));b=proof.index('\ndef LazyInv',a)
    lemma=proof[a:b].replace('theorem fold_w_spec','theorem r14_fold_optional_spec').replace('(nt p l d : Std.Usize)','(nt p l d : Std.Usize) (km : Std.U32)').replace('slot.pc_fold_w input out nt p l d','slot.r14_fold_optional input out nt p l d km').replace('C12569! slot.pc_fold_w','by\n  rw [slot.r14_fold_optional]\n  step*\n  exact ⟨hdec, hm, rfl, Nat.le_refl _⟩')
    proof=proof[:b]+'\n@[local step]\n'+lemma+proof[b:]
    name='r14-514-dna-nofold';dest=ROOT/'candidates'/name;dest.mkdir(exist_ok=True)
    data={'parse.rs':rust.encode(),'Parse.lean':proof.encode()}
    for f,v in data.items():assert not (dest/f).exists()or(dest/f).read_bytes()==v;(dest/f).write_bytes(v)
    hashes={f:hashlib.sha256(v).hexdigest()for f,v in data.items()}
    manifest={'candidate':name,'parent':'r14-514-dna-direct','comparison_baseline':'r14-514-dna-direct','formal_anchor_id':'514','hashes':hashes,
        'attribution':json.loads((p/'manifest.json').read_bytes())['attribution'],
        'mechanism':'Ablate only backward folding on the new DNA mode; ordinary PC modes keep the original fold.',
        'difference_from_old_work':'DNA-D parser itself slowed4.36/4.55percent, so its aggregate apparent gain is not support for the intended mechanism. N70 had no fold; this ablation tests the additional work introduced by direct PC transfer.',
        'proof_status':'DRAFT_UNCOMPILED helper contract; DNA hash totality still needs validation','performance_status':'UNKNOWN','formal_submission_sent':False}
    (dest/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
    E=ROOT/'evidence/round14';s=json.loads((E/'dna-c-native.json').read_bytes());old=copy.deepcopy(s['entries'][-1]);old['control']=True;old.pop('native_decode_reference',None)
    s['entries']=[e for e in s['entries']if e['control']]+[old,{'name':name,'path':f'candidates/{name}','control':False,'anchor':'public514','comparison_baseline':old['name'],'native_decode_reference':old['name'],'hashes':hashes}]
    s['native_encoder_references']=['r13-514-abs15',old['name']];s['screen_orders']=[[e['name']for e in s['entries']],[e['name']for e in reversed(s['entries'])]]
    s['description']='One DNA mechanism ablation after the intended path itself regressed: no backwards folding in the newmode. Native size first, keep original and direct controls; not a claim that aggregate discovery was a true gain.'
    (E/'dna-h-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());print(json.dumps({'candidate':name,'hashes':hashes}))
if __name__=='__main__':main()
