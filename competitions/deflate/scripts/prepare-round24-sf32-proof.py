"""Draft the guarded32bit solver proof from AL interfaces; no inherited acceptance."""
from pathlib import Path
import argparse,hashlib,importlib,json,re
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')

def make():
    p=ROOT/'candidates/r24-609-sf32';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    fp=E/'38097534969/proof-al-extract/diagnostics/research5/r24-609-sf32/Funs.lean';f=fp.read_text();report=json.loads((fp.parent.parent/'research.json').read_bytes());assert report['extractions'][p.name]['extraction_accepted'] and report['extractions'][p.name]['source_sha256']==hashlib.sha256(r.encode()).hexdigest()
    # Only the original three solver declarations are renamed. Other call sites
    # must see the new wrapper theorem after both implementations are established.
    a=l.index('@[local step]\ntheorem SFsolve_loop0_loop0_spec');b=l.index('@[local step]',l.index('theorem SFsolve_spec',a))
    old=l[a:b];renamed=old.replace('SFsolve','SFsolve64');proofs=[]
    loops={
        'S32eligible_loop':('1024 - q.val','j1'),
        'S32short_loop':('11 - q.2.val','⟨best1,x1⟩'),
        'S32long_loop':('32 - q.2.2.val','⟨best1,x1,it1⟩'),
        'SFsolve32_loop0_loop0':('«end».val - q.2.2.val','⟨bc1,bt1,k1⟩'),
        'SFsolve32_loop0':('q.2.1.val','⟨ch1,i1,rm1⟩'),
    }
    names=['S32min','S32add','S32relative','S32linear','S32range','S32put','S32short_loop','S32short','S32long_loop','S32long','S32eligible_loop','S32eligible','SFsolve32_loop0_loop0','SFsolve32_loop0','SFsolve32','SFsolve']
    for n in names:
        match=re.search(r'(?m)^def '+n+r'(?:\s|\()',f);assert match,n
        head=f[match.start():f.index(':=',match.start())]
        signature=re.split(r'\s*:\s*Result\b',head,maxsplit=1)[0].replace('def '+n,'theorem r24_'+n+'_spec',1).rstrip()
        args=[]
        for g in re.findall(r'\(([^()]*)\)',signature):args+=g.split(':',1)[0].split()
        theorem='@[local step]\n'+signature+' :\n slot.'+n+' '+' '.join(args)+' ⦃ fun _ => True ⦄ := by\n rw [slot.'+n+']\n'
        if n in loops:
            measure,pat=loops[n];theorem+=' apply Std.loop.spec_decr_nat (measure := fun q => '+measure+') (inv := fun _ => True)\n · rintro '+pat+' _\n   simp only [slot.'+n+'.body, lift, alloc.vec.Vec.deref_mut, bind_tc_ok]\n   step*\n   repeat\' (split <;> step*)\n   all_goals scalar_tac\n · trivial\n\n'
        else:theorem+=' step*\n repeat\' (split <;> step*)\n all_goals scalar_tac\n\n'
        proofs.append(theorem)
    l=l[:a]+renamed+''.join(proofs)+l[b:];assert len(l.encode())<=524288
    return r,l,fp

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--freeze',action='store_true');a=ap.parse_args();r,l,fp=make()
    if not a.freeze:print(json.dumps({'status':'DRAFT_NOT_LEAN_CHECKED','proof_bytes':len(l.encode()),'Funs_sha256':hashlib.sha256(fp.read_bytes()).hexdigest()}));return
    e=w.write_candidate('r24-609-sf32-proof1','r24-609-sf32',r,l,'Proof-only migration against actualAL32bit solver and fallback interfaces. Explicit bounded loop measures, unchanged original obligation and checker.','Same measuredRust, no inheritedgate or newoptimizationcandidate.',{'extraction':fp.relative_to(ROOT).as_posix(),'Funs_sha256':hashlib.sha256(fp.read_bytes()).hexdigest(),'proof':'DRAFT until fresh original fullgate.'})
    for name,d in [('gate-sf32-proof1',{'r24_mode':'gate','candidate':e['name'],'path':e['path'],'files':e['hashes'],'expected_public_output_bytes':4864126}),('preflight-gate-sf32-proof1',{'gap':'Exact32bit solver had nativeparity andactualextraction, but no all-stage acceptance.','change':'Only proof migration for actual emitted interfaces; old64bit fallback proof retained under its realnewname.','minimum':'Original full verifier with original900sLean limit and publicroundtrip.','decision':'Only accepted exactpair earns certificate; fix retainedactualerrors if required. Performance and independent confirmation remain separate.','cost_cap_runner_minutes':50,'evidence':'evidence/round24/<run>/gate-sf32-proof1/exact-gate'})]:
        dest=E/(name+'.json');assert not dest.exists();dest.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['hashes'])
if __name__=='__main__':main()
