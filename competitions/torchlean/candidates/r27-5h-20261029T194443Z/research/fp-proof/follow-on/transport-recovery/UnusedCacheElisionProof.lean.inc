/- Graft-only proof preflight for exactpublic23 SHA1010c0744f050697...,
   inside namespaceSubmission after its existingQPa/QPac4/Yuc4 declarations.
   NOT_COMPILED; not a standalonekernel or a modifiedfrozen source.
   ROUTE RETRACTED: retainedYaV line869 alreadyelides thesecaches.
   This is a redundantinterface draft, not newruntimework elimination.
   The guard is Nat addition after toNat, so no UInt64 wrap premise is needed. -/
namespace R27UnusedAlignedCache

theorem qpa_eq_fallback_of_wide
    (X W b : Array UInt32) (P : Array Nat) (I : Array UInt32)
    (n i j : Nat) (bx bv : UInt32) (hwide : 15 < (QYF bx).toNat) :
    QPa X P I W b n i j bx bv = YaU X W b n i j bx bv := by
  dsimp only [QPa]
  split
  · rename_i h
    obtain ⟨_, _, _, _, _, _, _, _, _, _, _, hs, _, _, _⟩ := h
    omega
  · rfl

theorem qpa_drop_cache_of_wide
    (X W b : Array UInt32) (P : Array Nat) (I : Array UInt32)
    (n i j : Nat) (bx bv : UInt32) (hwide : 15 < (QYF bx).toNat) :
    QPa X P I W b n i j bx bv = QPa X #[] #[] W b n i j bx bv := by
  rw [qpa_eq_fallback_of_wide X W b P I n i j bx bv hwide,
      qpa_eq_fallback_of_wide X W b #[] #[] n i j bx bv hwide]

theorem qpac4_eq_fallback_of_wide
    (X W b : Array UInt32) (P : Array Nat) (I : Array UInt32)
    (n i j : Nat) (bx bv1 bv2 bv3 bv4 : UInt32)
    (hwide : 15 < (QYF bx).toNat) :
    QPac4 X P I W b n i j bx bv1 bv2 bv3 bv4 =
      ((YaU X W b n i j bx bv1, YaU X W b n i (j+1) bx bv2),
       (YaU X W b n i (j+2) bx bv3, YaU X W b n i (j+2+1) bx bv4)) := by
  dsimp only [QPac4]
  split
  · exact Yuc4 X W b n i j bx bv1 bv2 bv3 bv4
  · rw [qpa_eq_fallback_of_wide X W b P I n i j bx bv1 hwide,
        qpa_eq_fallback_of_wide X W b P I n i (j+1) bx bv2 hwide,
        qpa_eq_fallback_of_wide X W b P I n i (j+2) bx bv3 hwide,
        qpa_eq_fallback_of_wide X W b P I n i (j+2+1) bx bv4 hwide]

theorem qpac4_drop_cache_of_wide
    (X W b : Array UInt32) (P : Array Nat) (I : Array UInt32)
    (n i j : Nat) (bx bv1 bv2 bv3 bv4 : UInt32)
    (hwide : 15 < (QYF bx).toNat) :
    QPac4 X P I W b n i j bx bv1 bv2 bv3 bv4 =
      QPac4 X #[] #[] W b n i j bx bv1 bv2 bv3 bv4 := by
  rw [qpac4_eq_fallback_of_wide X W b P I n i j bx bv1 bv2 bv3 bv4 hwide,
      qpac4_eq_fallback_of_wide X W b #[] #[] n i j bx bv1 bv2 bv3 bv4 hwide]

end R27UnusedAlignedCache

