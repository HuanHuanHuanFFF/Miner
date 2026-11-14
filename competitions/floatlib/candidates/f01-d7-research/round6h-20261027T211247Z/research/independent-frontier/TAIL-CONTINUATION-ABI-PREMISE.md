# Fixed compiler: direct native ABI is plausible; mutual tail jumping is not guaranteed

Source-only15minute inquiry began01:48:58 UTC on fixed Lean293d5d0c. No runtime prototype, Kernel, compiler execution, CI or new confirmation material. Exact primary files/Git blobs are archived in tail-compiler-source-index.json; all conclusions below distinguish logical construction from native code generation.

The logical well-founded mutual construction packs varying arguments into a unary function (`WF/PackMutual.lean`). **That does not establish runtime PSum/state allocation.** `WF/Main.lean:81–83` first installs the proved unary definitions, then calls addAndCompilePartialRec on the original predefinitions. `PreDefinition/Basic.lean:280–295` retains their original types/bodies and redirects recursive names for compilation. The compiler's internal generated names are normal implementation machinery for safe proved definitions, not authorization to add unsafe/implemented_by/axioms to a candidate.

The inspected pipeline handles SCCs as arrays of declarations. `LCNF/SplitSCC.lean` computes call-graph components and partitions declarations; it does not turn a mutual SCC into one runtime state dispatcher. `LCNF/Main.lean:194–212` passes those declaration groups through the remaining lowering passes. This supplies no automatic unified native while-loop guarantee.

Two fixed source checks make the tail boundary explicit. `LCNF/InferBorrow.lean:408–415` only protects self-call tail recursion and explicitly records mutual TCO as future work. The native C emitter's `isTailCall` at527–530 requires the callee to equal the current function; its self-tail emitter at725–747 rewrites parameter assignments followed by goto_start. Cross-function final calls use ordinary call/return emission. Consequently **source mutual tail position is not Lean-guaranteed machine tail jumping**; Clang may make a sibling tail call if ABI and cleanup permit, but no such new result is measured here.

The smallest future ABI discriminator is two first-order functions with **identical direct parameter lists**, matching the observed indexed8 state:

- eight separate USize parameters: count,a0,a1,a2,a3,stride,k,cursor;
- two borrowed array references: raw A and the existing B cache;
- eight separate Float32 accumulator parameters q00,q10,q20,q30,q01,q11,q21,q31;
- the existing Acc pointer result; proof parameters erased, no additional phase/state record or continuation closure.

The already seen indexed8 caller demonstrates eight native Float32 parameters in XMM0..7, with the extra integer/array arguments on the ordinary stack argument area. Matching Hot/Cold signatures is a necessary compatibility target, not proof of tail transfer. Do not pass four extra preloaded raw words only to Cold: that changes its stack-argument requirement. Cold may reread its four raw inputs; that cost must be counted. A logical lexicographic termination measure can use remaining count plus a constant Hot/Cold phase without introducing a runtime phase parameter; actual erasure still needs checking.

The intended protocol is Hot's qualified ordinary step looping to Hot with unchanged operation trees; a failed qualifier returns Cold on the full current state. Cold performs exactly one old ordered step then returns Hot with k+1/cursor+stride. Original+0 and final finish/raw repair are retained. This is an ABI sketch only, **not supplied source or a proven operation**. Array ownership inference must not leave dec/inc or other work after either cross-call; the fixed InferBorrow limitation makes this a real risk. A higher-order continuation can instead introduce captures/closures, so it is not presumed equivalent in cost.

First rejectable requirements, before a large proof or cost run: both generated definitions retain native Float32 arguments and direct static calls; no PSum/tuple/state allocation or dynamic apply appears on transitions; both actual cross-transfers are tail jumps with no post-call RC/stack work and no stack growth on repeated Cold steps; ordinary Hot backedges have no non-tail decoder call and q no longer travels through per-k stack slots. Any failure closes this proposal as a register-residency mechanism. Even satisfying these checks would not prove a speedup.

Decision: HOLD_ABI_UNMEASURED. The language/source does not force the feared unary state allocation, but the pinned compiler does **not** provide the requested mutual-TCO guarantee. A future actual ABI check could distinguish a viable normal safe definition from a failed layout. No new compiler pass, external intrinsic, flag change or candidate-side implementation override is proposed.
