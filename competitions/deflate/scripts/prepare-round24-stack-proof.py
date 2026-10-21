"""Migrate positive compositions using the actual AL interfaces and accepted components."""
from pathlib import Path
import hashlib, importlib, json, re
ROOT=Path(__file__).resolve().parents[1]; E=ROOT/'evidence/round24'
w=importlib.import_module('build-round18-start'); tree=importlib.import_module('prepare-round24-tree-proof')

def section(text,first,last):
    a=text.index('@[local step]\ntheorem '+first);b=text.index('@[local step]\ntheorem '+last,a)
    return a,b,text[a:b]

def main():
    base=ROOT/'candidates/r24-609-root-prune-proof1'
    cert=json.loads((base/'VERIFICATION.json').read_bytes()); assert cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
    l=(base/'Parse.lean').read_text()
    helper='''@[step]
theorem r24_Afirstword_spec (s:I) (p q k:R) (word:Std.U64)
 (hp:p.val ≤ 2 ^ 30) (hq:q.val ≤ 2 ^ 30) (hk:k.val ≤ 258) :
 slot.Afirstword s p q k word ⦃ fun r => r.1.val ≤ 258 ⦄ := by
 rw [slot.Afirstword]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

'''
    a,_,_=tree.decl(l,'u104');a=l.rfind('@[step]',0,a);l=l[:a]+helper+l[a:]
    for uid,num in [('u104','162'),('u485','189')]:
        a,b,d=tree.decl(l,uid)
        assert d.count('(pos depth oldest:R)')==1 and d.count('s kid pos depth mb')==1
        d=d.replace('(pos depth oldest:R)','(pos:R) (word:Std.U64) (depth oldest:R)').replace('s kid pos depth mb','s kid pos word depth mb')
        l=l[:a]+d+l[b:]
        a,b,_=tree.decl(l,'r24_Aroot'+num+'_loop_spec');a=l.rfind('@[step]',0,a)
        l=l[:a]+tree.alias(l,uid,'Z'+num+'_loop','Aroot'+num+'_loop')+l[b:]
    np=(ROOT/'candidates/r24-609-price-groups/Parse.lean').read_text()
    a=np.index('@[local step]\ntheorem SFprice_bend_loop_spec');b=np.index('@[local step]',np.index('theorem SFprice_bend_spec',a))
    marker='@[local step]\ntheorem SFsolve_loop'
    at=l.index(marker);l=l[:at]+np[a:b]+l[at:]
    for parent in ['r24-609-root-word-price','r24-609-root-word-price-buffer']:
        p=ROOT/'candidates'/parent;r=(p/'parse.rs').read_text();proof=l
        fp=E/'38097534969/proof-al-extract/diagnostics/research5'/parent/'Funs.lean';f=fp.read_text()
        report=json.loads((fp.parent.parent/'research.json').read_bytes());assert report['extractions'][parent]['extraction_accepted'] and report['extractions'][parent]['source_sha256']==hashlib.sha256(r.encode()).hexdigest()
        for num in ['162','189']:
            for suffix in ['_loop.body','_loop']:
                def block(n):
                    a=f.index('def '+n+'\n');b=f.index('\n/--',a);return f[a:b]
                assert re.sub(r'\s+',' ',block('Z'+num+suffix))==re.sub(r'\s+',' ',block('Aroot'+num+suffix).replace('Aroot'+num,'Z'+num))
        if parent.endswith('-buffer'):
            t=(ROOT/'candidates/r24-609-buffer-split-proof1/Parse.lean').read_text()
            a,b,_=section(proof,'SFfastadd_loop_spec','SFshortlookup_spec');_,_,rep=section(t,'SFfastkeep_loop_spec','SFshortlookup_spec');proof=proof[:a]+rep+proof[b:]
            a,b,_=tree.decl(proof,'SFmorematches_loop0_loop0_spec');_,_,rep=tree.decl(t,'SFmorematches_loop0_loop0_spec');proof=proof[:a]+rep+proof[b:]
        assert len(proof.encode())<=524288
        name=parent+'-proof1';e=w.write_candidate(name,parent,r,proof,'Migrate exact combined interfaces from AL, using the accepted root-state proof, explicit cached-word loop parameter, equal-price helper and optional accepted buffer policy proof.','Proof-only copy of the measured composition. Full original re-extraction, obligation and roundtrip are mandatory; component gates do not certify the combination.',{'extraction':fp.relative_to(ROOT).as_posix(),'Funs_sha256':hashlib.sha256(fp.read_bytes()).hexdigest(),'proof':'DRAFT until fresh original complete gate.'})
        label='gate-'+parent.removeprefix('r24-609-')+'-proof1'
        for stem,data in [(label,{'r24_mode':'gate','candidate':name,'path':e['path'],'files':e['hashes'],'expected_public_output_bytes':4864115 if parent.endswith('-buffer') else 4864126}),('preflight-'+label,{'gap':'Positive components are measured, but the two actual compositions have only native parity and extraction. Their exact combined proof is unverified.','change':'Proof-only migration against actual emitted AL Funs, preserving original obligation and900s Lean limit.','minimum':'Fresh original full gate on each exact Rust/Lean pair.','decision':'Bind only accepted exact pairs; retain specific failures and repair without changing original verifier. Confirmation follows on frozen pair.','cost_cap_runner_minutes':50,'evidence':f'evidence/round24/<run>/{label}/exact-gate'})]:
            dest=E/(stem+'.json');assert not dest.exists();dest.write_bytes((json.dumps(data,indent=2)+'\n').encode())
        print(name,e['hashes'],len(proof.encode()))

if __name__=='__main__':main()
