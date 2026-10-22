/-
Append this diagnostic file to ConversionCandidate.lean in a temporary file.
These commands are separate from the candidate and must not be submitted.
Status of this delivery: NOT_RUN.
-/

#check R2W03b.uint32_unpack_exact24
#check R2W03b.mul_normal_scale_target
#check R2W03b.mul_normal_scale_exact
#check R2W03b.raw_unpack_normal
#check R2W03b.scale_unpack_normal
#check R2W03b.signedScaleTable_lookup
#check R2W03b.fromBitsTable_eq_ofBits
#check R2W03b.fromBitsTable_all
#check R2W03b.fromBitsTable_eq

#print axioms R2W03b.round_at_target
#print axioms R2W03b.ofNat_eq_round
#print axioms R2W03b.uint32_unpack_exact24
#print axioms R2W03b.mul_normal_scale_exact
#print axioms R2W03b.raw_unpack_normal
#print axioms R2W03b.scale_unpack_normal
#print axioms R2W03b.signedScaleTable_lookup
#print axioms R2W03b.fromBitsTable_all
#print axioms R2W03b.fromBitsTable_eq

example : ∀ u : UInt32,
    R2W03b.fromBitsTable u = Float32.ofBits u :=
  R2W03b.fromBitsTable_all

example (u : UInt32) :
    (R2W03b.fromBitsTable u).toBits = (Float32.ofBits u).toBits :=
  congrArg Float32.toBits (R2W03b.fromBitsTable_eq_ofBits u)

example {α : Type} (context : Float32 → α) (u : UInt32) :
    context (R2W03b.fromBitsTable u) = context (Float32.ofBits u) :=
  congrArg context (R2W03b.fromBitsTable_eq_ofBits u)
