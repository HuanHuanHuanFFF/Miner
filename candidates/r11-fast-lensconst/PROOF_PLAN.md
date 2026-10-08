# Unadapted proof checkpoint

Rust source is ready; parent Lean is byte-identical and UNADAPTED. No compiled proof is claimed.

The actual old e_lens_spec preserves LensBound (all260 entries<=258), not merely totality. After real extraction, add r11_e_lens_spec after e_lens_spec: fixed-mask branch proves LensBound of the concrete260-entry returned array; other-mask branch composes LensBound.init with e_lens_spec. run1t_spec/run_z_spec must consume the new helper result rather than the original repeat+e_lens pair. Inspect actual array-by-value return and tuple shape first. Keep original obligation, emitter and axiom whitelist. Do not add a new metadata assumption.

No lookup, skip, depth, routing, encoder or threshold changes. New array initialization may become memcpy, but this needs actual codegen and paired total-time measurement; source equality alone does not establish a gain.
