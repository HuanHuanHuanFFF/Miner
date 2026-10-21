"""Bind the repaired L proof to its observed original extraction interface."""
from pathlib import Path
import importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';w=importlib.import_module('build-round18-start')
def main():
    p=ROOT/'candidates/r24-609-buffer-split';r=(p/'parse.rs').read_text();l=(p/'Parse.lean').read_text()
    a=l.index('@[local step]\ntheorem SFfastadd_loop_spec');b=l.index('@[local step]\ntheorem SFfastkeep_loop_spec',a);c=l.index('@[local step]\ntheorem SFshortlookup_spec',b)
    add=l[a:b];keep=l[b:c]
    add=add.replace('(t : Std.U32)', '(t : Std.U32) (ct : Array Std.U32 1024#usize)')
    add=add.replace('count t dc j ⦃','count t ct dc j ⦃').replace('count t ⦃','count t ct ⦃')
    helper='''@[local step]
theorem SFroom_loop_spec (best : Array Std.U32 4#usize) (codes : Array Std.Usize 4#usize) (ct : Array Std.U32 1024#usize) (nc : Std.U32) (nl : Std.Usize) (i : Std.Usize) :
 slot.SFroom_loop best codes ct nc nl i ⦃ fun _ => True ⦄ := by
 rw [slot.SFroom_loop]
 apply Std.loop.spec_decr_nat (measure := fun q => 4 - q.val) (inv := fun _ => True)
 · rintro i1 _
   simp only [slot.SFroom_loop.body]
   step*
   repeat' (split <;> step*)
   all_goals scalar_tac
 · trivial

@[local step]
theorem SFroom_spec (best : Array Std.U32 4#usize) (codes : Array Std.Usize 4#usize) (t : Std.U32) (ct : Array Std.U32 1024#usize) :
 slot.SFroom best codes t ct ⦃ fun _ => True ⦄ := by
 rw [slot.SFroom]
 step*

'''
    l=l[:a]+keep+helper+add+l[c:]
    a=l.index('theorem SFmorematches_loop0_loop0_spec');b=l.index('\n@[local step]',a);part=l[a:b]
    part=part.replace('(prev : Slice Std.U32)', '(prev : Slice Std.U32) (ct : Array Std.U32 1024#usize)')
    part=part.replace('input prev e depth p best codes ot count q k ⦃','input prev ct e depth p best codes ot count q k ⦃')
    l=l[:a]+part+l[b:]
    e=w.write_candidate('r24-609-buffer-split-proof1',p.name,r,l,'Proof migration only: actual extracted SFroom loop, ct propagation through fastadd and the matcher, and dependency order for fastkeep.','Same Rust as native-equal split repair; not a distinct optimization candidate.',{'extraction':'evidence/round24/38089577310/repair-t-extract/diagnostics/research5/r24-609-buffer-split/Funs.lean','native':'evidence/round24/feedback-t-native.json','proof':'DRAFT until fresh original complete gate.'})
    for name,d in [('gate-buffer-split1',{'r24_mode':'gate','candidate':e['name'],'path':e['path'],'files':e['hashes'],'expected_public_output_bytes':4864115}),('preflight-gate-buffer-split1',{'gap':'L has positive discovery projections, but original structure could not extract. The split repair extracts and preserves all28publictokens/output; exact proof is now migrated against emitted Funs.','change':'Only Lean proof migration on frozen split Rust.','minimum':'Fresh original complete public verifier,900s Lean obligation/axioms and roundtrip.','decision':'Fix specific retained errors if needed; a passed gate applies only to this exact pair. Original L timing is not automatically independent performance evidence for new Rust.','cost_cap_runner_minutes':50,'evidence':'evidence/round24/<run>/gate-buffer-split1/diagnostics/exact-gate'})]:
        out=E/(name+'.json');assert not out.exists();out.write_bytes((json.dumps(d,indent=2)+'\n').encode())
    print(e['hashes'])
if __name__=='__main__':main()
