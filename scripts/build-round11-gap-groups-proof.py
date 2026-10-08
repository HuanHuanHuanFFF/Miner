"""First bounded UNCOMPILED groups bridge against the actual d00bd Funs."""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import re

ROOT=Path(__file__).resolve().parents[1]
PARENT=ROOT/'candidates/r10-finder-pipeline-proof'
BASE=ROOT/'candidates/r11-gap-groups'
DEST=ROOT/'candidates/r11-gap-groups-proof'
EXTRACT=ROOT/'evidence/round11/37727588709/groups-d/extraction/r11-gap-groups'
RUST_SHA='6ef07be874052d23fbe3cdca8de7e311e82a306338a93f70389fe35006e99992'
LEAN_PARENT_SHA='e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db'
FUNS_SHA='d00bd9e6bec3571e140db0484d71eaf02625d4a72eddf1d278cc2d249c954c45'
sp=importlib.util.spec_from_file_location('meta_bridge',ROOT/'scripts/build-round11-gap-meta-proof.py')
meta=importlib.util.module_from_spec(sp); assert sp.loader;sp.loader.exec_module(meta)

WORD = r'''
@[local step]
theorem d_gap_word_loop0_loop0_spec (lc «end» price l flat) :
    slot.d_gap_word_loop0_loop0 lc «end» price l flat ⦃ fun _ => True ⦄ := by
  rw [slot.d_gap_word_loop0_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 512 - x.1.val) (inv := fun _ => True)
  · rintro ⟨l', flat'⟩ _
    unfold slot.d_gap_word_loop0_loop0.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok trivial)
    refine d2_lt (fun h2 => ?_) (fun _ => d2_ok trivial)
    refine d2_idx h2 fun i => ?_
    refine d2_tot d2_itev fun flat1 => ?_
    refine d2_inck 512 (Nat.le_of_lt h2) (by decide) fun l1 hl1 => ?_
    exact d2_ok ⟨trivial, d2_msub h2 hl1⟩
  · trivial

@[local step]
theorem d_gap_word_loop0_spec (lc mask g) :
    slot.d_gap_word_loop0 lc mask g ⦃ fun _ => True ⦄ := by
  rw [slot.d_gap_word_loop0]
  apply Std.loop.spec_decr_nat (measure := fun x => 20 - x.2.val) (inv := fun _ => True)
  · rintro ⟨mask', g'⟩ _
    unfold slot.d_gap_word_loop0.body
    refine d2_lt (fun hg => ?_) (fun _ => d2_ok trivial)
    refine d2_idx hg fun start => ?_
    refine d2_idx hg fun «end» => ?_
    refine d2_rem (by decide) fun i hi => ?_
    refine d2_idx hi fun price => ?_
    refine d2_lift <| d2_tot (d_gap_word_loop0_loop0_spec _ _ _ _ _) fun flat => ?_
    refine d2_tot (Q := fun _ => True) ?_ fun mask1 => ?_
    · exact d2_ite
        (fun _ => d1_shl (by omega) fun i1 => d2_ok trivial)
        (fun _ => d2_ok trivial)
    refine d2_inck 20 (Nat.le_of_lt hg) (by decide) fun g1 hg1 => ?_
    exact d2_ok ⟨trivial, d2_msub hg hg1⟩
  · trivial

@[local step]
theorem d_gap_word_spec (litc lc) :
    slot.d_gap_word litc lc ⦃ fun _ => True ⦄ := by
  rw [slot.d_gap_word]
  refine d2_tot (d_gap_positive_max_spec _) fun maximum => ?_
  refine d2_ite (fun _ => d2_ok trivial) (fun _ => ?_)
  refine d2_ite (fun _ => d2_ok trivial) (fun _ => ?_)
  refine d2_tot (d_gap_word_loop0_spec _ _ _) fun mask => ?_
  refine d2_ite (fun _ => d2_ok trivial) (fun _ => ?_)
  refine d2_tot (WP.spec_mono (U32.ShiftLeft_IScalar_spec mask 12#i32 (by decide) (by decide))
    (fun _ _ => trivial)) fun i => d2_ok trivial

@[local step]
theorem d_load_groups_spec (tabs tb litc lc dcc) :
    slot.d_load_groups tabs tb litc lc dcc ⦃ fun _ => True ⦄ := by
  rw [slot.d_load_groups]
  refine d2_tot (d_load_spec _ _ _ _ _) ?_
  rintro ⟨litc1, lc1, dcc1⟩
  refine d2_tot (d_gap_word_spec _ _) fun word => ?_
  exact d2_upd (by decide) fun lc2 => d2_ok trivial

@[local step]
theorem d_gap_group_spec (rem) :
    slot.d_gap_group rem ⦃ fun _ => True ⦄ := by
  rw [slot.d_gap_group]
  -- The actual short-circuit extraction duplicates branches, but each leaf is
  -- only wrapping arithmetic, a constant nonzero divisor and optional d_min.
  repeat' first
    | refine d2_ite (fun _ => ?_) (fun _ => ?_)
    | refine d2_lift ?_
    | refine d2_div (by decide) fun _ => ?_
    | refine d2_tot (d_min_spec _ _) fun _ => ?_
    | exact d2_ok trivial

@[local step]
theorem d_gap_group_fill_loop_spec (ring out hi ri endpoint high chd p) :
    slot.d_gap_group_fill_loop ring out hi ri endpoint high chd p
      ⦃ fun r => r.2.length = out.length ⦄ := by
  rw [slot.d_gap_group_fill_loop]
  apply Std.loop.spec_decr_nat (measure := fun x => hi.val - x.2.2.2.val)
    (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', ri', p'⟩ hinv
    unfold slot.d_gap_group_fill_loop.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok hinv)
    refine d2_lt (fun h2 => ?_) (fun _ => d2_ok hinv)
    refine d2_lt (fun h3 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h4 => ?_) (fun _ => d2_ok hinv)
    refine d2_sub h4 fun rem _ => ?_
    refine d2_lift <| d2_lift <| d2_lift ?_
    have hri : ri'.val < (1024#usize).val := by simpa [slot.D_RING] using h3
    refine d2_upd hri fun a => ?_
    refine d2_lift <| d2_supd h2 fun out1 hout1 => ?_
    refine d2_inc h1 fun p1 hp1 => ?_
    refine d2_inck 1024 (Nat.le_of_lt hri) (by decide) fun ri1 _ => ?_
    exact d2_ok ⟨hout1.trans hinv, d2_msub h1 hp1⟩
  · rfl

@[local step]
theorem d_gap_group_fill_spec (ring out lo hi ri endpoint high chd) :
    slot.d_gap_group_fill ring out lo hi ri endpoint high chd
      ⦃ fun r => r.2.length = out.length ⦄ := by
  rw [slot.d_gap_group_fill]
  exact d_gap_group_fill_loop_spec _ _ _ _ _ _ _ _

'''

GAP = r'''
@[local step]
theorem d_gap_groups_loop2_spec (s litc lc ring out stop «end» chd dlit word maximum q nxt kc) :
    slot.d_gap_groups_loop2 s litc lc ring out stop «end» chd dlit word maximum q nxt kc
      ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.d_gap_groups_loop2]
  apply Std.loop.spec_decr_nat (measure := fun x => x.2.2.1.val)
    (inv := fun x => x.2.1.length = out.length)
  · rintro ⟨ring', out', q', nxt'⟩ hinv
    unfold slot.d_gap_groups_loop2.body
    refine d2_lt (fun h1 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h2 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h3 => ?_) (fun _ => d2_ok hinv)
    refine d2_le (fun h4 => ?_) (fun _ => d2_ok hinv)
    refine d2_dec h1 fun q1 hq1 => ?_
    refine d2_sub (Nat.le_of_lt (d2_le_pred hq1 h4)) fun rem _ => ?_
    refine d2_rem (by decide) fun i2 hi2 => ?_
    refine d2_idx hi2 fun length_price => ?_
    refine d2_tot (d2_shr32 _) fun i3 => ?_
    refine d2_sidx (d2_le_pred hq1 h2) fun i4 => ?_
    refine d2_lift <| d2_idx (d2_u8 i4) fun i6 => ?_
    refine d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i9 => ?_
    refine d2_lift <| d2_lift <| d2_lift <| d2_tot (d2_shl32 _) fun i12 => ?_
    refine d2_lift <| d2_lift <| d2_lift <| d2_tot d2_itev fun v => ?_
    refine d2_remR fun i15 hi15 => ?_
    refine d11_amut hi15 fun _ back0 => ?_
    refine d11_smut (d2_le_pred hq1 h3) fun _ back1 hback1 => ?_
    refine d2_lift ?_
    have hout1 := (hback1 (UScalar.cast .U32 v)).trans hinv
    refine d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_tot (d2_shr32 _) fun i17 => ?_
    refine d2_lift <| d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_tot (d_gap_group_spec _) ?_
    rintro ⟨group, group_end⟩
    refine d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_lift <| d2_rem (by decide) fun i20 hi20 => ?_
    refine d1_shr hi20 fun i21 => ?_
    refine d2_lift <| d2_ite (fun _ => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_lift <| d2_lift <| d2_lift <| d2_tot (d_min_spec _ _) fun count => ?_
    refine d2_lt (fun hc0 => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_le (fun hcq => ?_) (fun _ => d2_ok ⟨hout1, d2_pred hq1⟩)
    refine d2_sub hcq fun lower hlower => ?_
    have hlow : lower.val < q1.val := by omega
    refine d2_lift <| d2_remR fun ri hri => ?_
    refine d2_sub (by simpa [slot.D_RING] using Nat.le_of_lt hri) fun room _ => ?_
    refine d2_lift <| d2_tot (d_min_spec _ _) fun middle => ?_
    refine d2_bind (d_gap_group_fill_spec _ _ _ _ _ _ _ _) ?_
    rintro ⟨ring2, out2⟩ hout2
    refine d2_bind (Q := fun r => r.2.length = out2.length) ?_ ?_
    · exact d2_ite (fun _ => d_gap_group_fill_spec _ _ _ _ _ _ _ _) (fun _ => d2_ok rfl)
    rintro ⟨ring3, out3⟩ hout3
    refine d2_lift <| d2_lift <| d2_lift <| d2_lift ?_
    exact d2_ok ⟨hout3.trans (hout2.trans hout1), Nat.lt_trans hlow (d2_pred hq1)⟩
  · rfl

@[local step]
theorem d_gap_groups_spec (s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit) :
    slot.d_gap_groups s litc lc ring out hi stop «end» kcd chd lo nxt0 dlit
      ⦃ fun r => r.2.2.length = out.length ⦄ := by
  rw [slot.d_gap_groups]
  refine d2_idx (by decide) fun word => ?_
  refine d2_lift <| d2_lift <| d2_ite (fun _ => d_gap_spec _ _ _ _ _ _ _ _ _ _ _ _ _) (fun _ => ?_)
  refine d2_ite (fun _ => d_gap_spec _ _ _ _ _ _ _ _ _ _ _ _ _) (fun _ => ?_)
  refine d2_ite (fun _ => d_gap_spec _ _ _ _ _ _ _ _ _ _ _ _ _) (fun _ => ?_)
  refine d2_lift <| d2_tot (d_clip_spec _ _ _) fun mid => ?_
  refine d2_bind (d_gap_groups_loop0_spec s litc ring out lo dlit hi nxt0 mid) ?_
  rintro ⟨ring1, out1, q, nxt⟩ h0
  refine d2_tot (d_cell_spec _ _) fun i2 => ?_
  refine d2_tot (d2_shr32 _) fun i3 => ?_
  refine d2_lift <| d2_tot (d_clip_spec _ _ _) fun s1 => ?_
  refine d2_bind (d_gap_groups_loop1_spec s litc lc ring1 out1 «end» chd dlit q nxt _ s1) ?_
  rintro ⟨ring2, out2, q1, nxt1⟩ h1
  exact WP.spec_mono (d_gap_groups_loop2_spec s litc lc ring2 out2 stop «end» chd dlit word _ q1 nxt1 _)
    (fun r h2 => h2.trans (h1.trans h0))

'''


def sha(data):return hashlib.sha256(data).hexdigest()


def generate():
    rust=(BASE/'parse.rs').read_bytes(); parent=(PARENT/'Parse.lean').read_bytes();funs=(EXTRACT/'Funs.lean').read_bytes()
    assert sha(rust)==RUST_SHA and sha(parent)==LEAN_PARENT_SHA and sha(funs)==FUNS_SHA
    original=parent.decode();proof=original
    pre=meta.PRELUDE.split('@[local step]\ntheorem d_load_meta_spec')[0]
    block=meta.theorem(original,'d_block_spec').replace('d_block_spec','d_block_groups_spec').replace('slot.d_block','slot.d_block_groups').replace('d_load_spec','d_load_groups_spec')
    clones=''.join(meta.theorem(original,f'd_gap_loop{i}_spec').replace(f'd_gap_loop{i}',f'd_gap_groups_loop{i}') for i in (0,1))
    additions=pre+WORD+block+clones+GAP
    assert not re.search(r'\b(sorry|admit|axiom)\b',additions)
    anchor='@[local step]\ntheorem d_top_spec ';assert proof.count(anchor)==1
    proof=proof.replace(anchor,additions+anchor,1)
    start=proof.index('@[local step]\ntheorem d_dp_loop0_loop0_spec ');end=proof.index('@[local step]\ntheorem d_extract_loop_spec ',start)
    before=proof[start:end];after=before;binding_changes={}
    for a,b,n in [('d_load_spec','d_load_groups_spec',1),('d_block_spec','d_block_groups_spec',2),('d_gap_spec','d_gap_groups_spec',1)]:
        assert after.count(a)==n;after=after.replace(a,b);binding_changes[a]=n
    proof=proof[:start]+after+proof[end:]
    restored=proof.replace(additions,'',1)
    start=restored.index('@[local step]\ntheorem d_dp_loop0_loop0_spec ');end=restored.index('@[local step]\ntheorem d_extract_loop_spec ',start);r=restored[start:end]
    for a,b in [('d_load_groups_spec','d_load_spec'),('d_block_groups_spec','d_block_spec'),('d_gap_groups_spec','d_gap_spec')]:r=r.replace(a,b)
    restored=restored[:start]+r+restored[end:];assert restored.encode()==parent
    files={'parse.rs':rust,'Parse.lean':proof.encode()}
    manifest=json.loads((BASE/'manifest.json').read_text());manifest.update(
        candidate='r11-gap-groups-proof',parent='candidates/r11-gap-groups',parent_hashes={'parse.rs':RUST_SHA,'Parse.lean':LEAN_PARENT_SHA},
        hashes={f:sha(v) for f,v in files.items()},bytes={f:len(v) for f,v in files.items()},
        proof_status='UNCOMPILED_ACTUAL_D00BD_FIRST_DRAFT; root must run exact pair original obligation/axioms/roundtrip',
        proof_scope='Planner totality/out.length only; zero new metadata-origin premises, unchanged original checked-emitter/root suffix; not all-input token equivalence',
        equivalence_status='VERIFIED_FINITE groups-e444/public same tokens/output, v2 loader14/dp2156 and9 cross-ring cases; no arbitrary fake-metadata equivalence',
        performance_status='First runner two blocks+0.33337%/-2.71782%, mean-1.1922258%; independent h/i confirmation PENDING; no frontier/admission claim')
    audit={'status':'UNCOMPILED_FIRST_DRAFT_SOURCE_REVERSAL_CHECKED','rust_sha256':RUST_SHA,'lean_sha256':sha(files['Parse.lean']),'parent_lean_sha256':LEAN_PARENT_SHA,'funs_sha256':FUNS_SHA,'binding_changes':binding_changes,'new_helper_specs':14,'new_mutable_borrow_bridges':2,'inserted_bytes':len(additions.encode()),'original_root_and_checked_emitter_suffix':'byte-identical','new_sorry_admit_axiom':False,'compile_status':'NOT_RUN'}
    status={'status':'UNCOMPILED_FIRST_DRAFT','candidate':'r11-gap-groups-proof','files':manifest['hashes'],'extraction_funs_sha256':FUNS_SHA,'gate_status':'NOT_RUN','independent_performance_confirmation':'PENDING','unverified':['All new specs and four caller bindings must compile against the pin','mut-back API and out.length combination','pure group62-branch tactic reduction','word/fill loop scalar increment and rank elaboration','original obligation/axiom/full roundtrip acceptance'],'allocation':'One bounded25-minute first draft while h/i retest runs; root may stop proof if no repeatable signal'}
    for f,v in [('manifest.json',manifest),('proof-port-audit.json',audit),('UNCOMPILED_STATUS.json',status)]:files[f]=(json.dumps(v,indent=2,ensure_ascii=False)+'\n').encode()
    assert all(0<len(files[f])<=524288 for f in ['parse.rs','Parse.lean'])
    return files


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();DEST.mkdir(parents=True,exist_ok=True)
    for f,v in files.items():
        p=DEST/f
        if args.check:assert p.read_bytes()==v
        elif p.exists():assert p.read_bytes()==v,'Refusing frozen proof mutation'
        else:p.write_bytes(v)
    print(json.dumps({'candidate':'r11-gap-groups-proof','status':'UNCOMPILED','hashes':{f:sha(v) for f,v in files.items()},'builder_sha256':sha(Path(__file__).read_bytes())}))


if __name__=='__main__':main()
