"""Migrate a selected tree experiment from its actual extracted interfaces."""
from pathlib import Path
import argparse,hashlib,importlib,json,re
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
def decl(t,name):
    ms=list(re.finditer(r'(?m)^theorem '+re.escape(name)+r'\b',t));assert len(ms)==1,name;a=ms[0].start()
    m=re.search(r'(?m)^(?:@\[|set_option |theorem |end |namespace )',t[ms[0].end():]);assert m;b=ms[0].end()+m.start();return a,b,t[a:b]
def alias(t,uid,old,new):
    _,_,d=decl(t,uid);header=re.split(r'\s*:=\s*by\b',d,maxsplit=1)[0]
    binders=re.split(r':\s*\n\s*slot\.',header,maxsplit=1)[0];args=[]
    for group in re.findall(r'\(([^()]*)\)',binders):args+=group.split(':',1)[0].split()
    header=header.replace('theorem '+uid+' ','theorem r24_'+new+'_spec ',1).replace('slot.'+old,'slot.'+new)
    return '@[step]\n'+header+' := by\n  simpa only [slot.'+new+', slot.'+new+'.body, slot.'+old+', slot.'+old+'.body] using ('+uid+' '+' '.join(args)+')\n\n'
CHILD='''@[step]
theorem r24_Achild_spec (kid : Std.Array Std.U16 65536#usize) (node side : R) :
 slot.Achild kid node side ⦃ fun _ => True ⦄ := by
 rw [slot.Achild]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac
@[step]
theorem r24_Asetchild_spec (kid : Std.Array Std.U16 65536#usize) (at_ now : R) (child : W) :
 slot.Asetchild kid at_ now child ⦃ fun _ => True ⦄ := by
 rw [slot.Asetchild]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

'''
def root_proofs(finder,tree,prefix):
    return f'''@[step]
theorem r24_Aroot{tree}_spec (s:I) (head kid h3) (pos:R) (pre depth mb)
 (hpos:pos.val + 266 ≤ s.length) (hn26:s.length < 67108864) :
 slot.Aroot{tree} s head kid h3 pos pre depth mb ⦃ Y112P0! ⦄ := by
 obtain ⟨q,t,h,c3,cr,cur⟩ := pre
 rw [slot.Aroot{tree}]
 apply WP.spec_bind (Pₘ := fun (_:R) => True)
 · split
   all_goals step*
 rintro oldest -
 step*
 apply WP.spec_bind (Pₘ := fun (x:alloc.vec.Vec W × R) => 2 ≤ x.2.val)
 · repeat' (split <;> step*)
   all_goals scalar_tac
 rintro ⟨mb1,best⟩ hb
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

set_option maxHeartbeats 4000000 in
@[step]
theorem r24_Aroot{finder}_loop_spec (i:W) (s:I) (mp:alloc.vec.Vec W) (mb depth) (n:R)
 (head kid h3) (i1:R) (nq nt nh n3 nc)
 (hn:n.val = s.length) (hn26:s.length < 67108864) (hi:i.val < 32)
 (hmp:mp.length ≤ i1.val + 1) :
 slot.Aroot{finder}_loop i s mp mb depth n head kid h3 i1 nq nt nh n3 nc ⦃ Y112P0! ⦄ := by
 rw [slot.Aroot{finder}_loop]
 apply Std.loop.spec_decr_nat
   (measure := fun (_,_,_,_,_,i_,_,_,_,_,_) => n.val - i_.val)
   (inv := fun ((mp_:alloc.vec.Vec W),_,_,_,_,(i_:R),_,_,_,_,_) => mp_.length ≤ i_.val + 1)
 · rintro ⟨mp_,mb_,head_,kid_,h3_,i_,nq_,nt_,nh_,n3_,nc_⟩ hmp_
   simp only [slot.Aroot{finder}_loop.body, {prefix}u37, {prefix}u40]
   step*
   repeat' (split <;> step*)
   all_goals (try cases_type* Prod)
   all_goals step*
   repeat' (split <;> step*)
   all_goals (try cases_type* Prod)
   all_goals step*
   all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
   all_goals scalar_tac
 · exact hmp

@[step]
theorem r24_Aroot{finder}_spec (s:I) (mp:alloc.vec.Vec W) (mb depth)
 (hn26:s.length < 67108864) (hmp:mp.length = 0) :
 slot.Aroot{finder} s mp mb depth ⦃ Y112P0! ⦄ := by
 have hhb := {prefix}u35
 rw [slot.Aroot{finder}]
 step*
 all_goals try simp only [alloc.vec.Vec.length, *, List.length_append, List.length_singleton]
 all_goals scalar_tac

@[step]
theorem r24_Z{finder}_spec (s:I) (mp:alloc.vec.Vec W) (mb depth) (skip:R)
 (hn26:s.length < 67108864) (hskip:3 ≤ skip.val) (hmp:mp.length = 0) :
 slot.Z{finder} s mp mb depth skip ⦃ Y112P0! ⦄ := by
 rw [slot.Z{finder}]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

'''
def make(parent):
    p=ROOT/'candidates'/parent;r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text();rec=E/'38094699832/proof-ah-extract/diagnostics/research5';report=json.loads((rec/'research.json').read_bytes());assert report['extractions'][parent]['extraction_accepted'] and report['extractions'][parent]['source_sha256']==hashlib.sha256(r.encode()).hexdigest()
    funs=(rec/parent/'Funs.lean').read_text();compact='pub fn Achild('in r;special='pub fn Aroot145('in r;counts={}
    if compact:
        for uid in ['u104','u106','u485','u487']:
            a,b,part=decl(l,uid)
            part,n=re.subn(r'(Std.Array W 65536#usize\s+×\s+)Std.Array W 65536#usize(\s+×\s+Std.Array W 32768#usize)',r'\1Std.Array Std.U16 65536#usize\2',part)
            if uid in ['u104','u485']:part,k=re.subn(r'Std.Array W 65536#usize(\s+×\s+R)',r'Std.Array Std.U16 65536#usize\1',part);n+=k
            assert n>0,uid;counts[uid]=n;l=l[:a]+part+l[b:]
        a,_,_=decl(l,'u104');at=l.rfind('@[',0,a);assert l[at:a].strip()=='@[step]';l=l[:at]+CHILD+l[at:]
    if special:
        for finder in ['145','186']:l=l.replace('slot.Z'+finder,'slot.Z'+finder+'full')
        def fblock(n):
            a=funs.index('def '+n+'\n');b=funs.find('\n/--',a);return funs[a:b if b>=0 else None]
        for finder,tree,loop_uid,wrapper_uid,prefix in [('145','162','u104','u107',''),('186','189','u485','u488','EA.EA.')]:
            for suffix in ['_loop.body','_loop']:
                aa=fblock('Z'+tree+suffix);bb=fblock('Aroot'+tree+suffix).replace('Aroot'+tree,'Z'+tree);assert re.sub(r'\s+',' ',aa)==re.sub(r'\s+',' ',bb)
            extra=alias(l,loop_uid,'Z'+tree+'_loop','Aroot'+tree+'_loop')+root_proofs(finder,tree,prefix)
            _,at,_=decl(l,wrapper_uid);l=l[:at]+'\n'+extra+l[at:]
    assert len(l.encode())<=524288
    return r,l,{'compact':compact,'specialized':special,'type_changes':counts,'Funs_sha256':hashlib.sha256(funs.encode()).hexdigest()}
def main():
    ap=argparse.ArgumentParser();ap.add_argument('parent',choices=['r24-609-child16','r24-609-root-prune','r24-609-root-child16']);ap.add_argument('--check',action='store_true');a=ap.parse_args();r,l,audit=make(a.parent)
    if a.check:print(json.dumps({'status':'DRAFT_SOURCE_INTERFACE_CHECK_ONLY','parent':a.parent,'proof_bytes':len(l.encode()),'audit':audit}));return
    name=a.parent+'-proof1';e=w.write_candidate(name,a.parent,r,l,'Proof-only migration against actual AH extraction; helper totality, exact child array types, renamed fallback and new fast-loop invariants.','Same Rust as the measured parent. Loop proof reuse is a kernel-checked definitional-equality attempt, not an inherited full gate or another optimization candidate.',{'extraction':'evidence/round24/38094699832/proof-ah-extract/diagnostics/research5/'+a.parent+'/Funs.lean','interface_audit':audit,'proof':'DRAFT until original complete gate.'})
    label='gate-'+a.parent.removeprefix('r24-609-')+'-proof1';spec={'r24_mode':'gate','candidate':name,'path':e['path'],'files':e['hashes'],'expected_public_output_bytes':4864126}
    p=E/(label+'.json');assert not p.exists();p.write_bytes((json.dumps(spec,indent=2)+'\n').encode());print(label,e['hashes'])
if __name__=='__main__':main()
