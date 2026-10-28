# Exact conditional RC premise

This is a final source-level refinement for the unchanged 680ca1b3 probe, not a new runtime, proof of emitted behavior or CI request. Pinned ExplicitRC.lean is bound by borrowed-rc-source.json and borrowed-rc-verification.json.

The condition can now be stated precisely. Suppose the two original arrays reach ExplicitRC as borrowed parameters, the eight USize and eight Float32 arguments remain scalars, and a cross-edge has the direct LCNF form `let r := callee args; return r` with an owned result. The RC pass has no rule here requiring an array decrement after that cross-call:

1. visitParam (102–105) puts borrowed reference parameters into borrowedValues. setRetLiveVars (390–396) retains those borrows at the return boundary.
2. addDecAfterFullApp (521–541) inserts a post-call decrement only when the argument is a possible reference, is borrowed by the callee, is not live and is **not already borrowed in the caller**. The final condition is false for both original arrays. The remaining direct arguments are scalar.
3. The return case (662–669) only adds a reference increment for a borrowed returned object; the owned cross-call result in the stated condition does not trigger it. addDecForDeadParams (557–561) likewise uses addDecIfNeeded, whose predicate excludes borrowed parameters.

This closes the narrow claim that forwarding those two borrowed arrays must inherently force post-call RC. It does not prove that the actual elaborated probe satisfies the whole condition. Argument reduction, generic array-element temporaries, result boxing, helper calls and selected wrappers still need their actual C. ExplicitRC can also choose borrowed array-read primitives (586–591), but that is its existing internal optimization; the candidate must not call unsafe borrowed primitives directly.

The scalar side of that conditional is supported by the pinned type classifier, not only by source spelling: borrowed-interface-source/Types.lean:452–477 classifies Float32/USize as scalars and reserves isPossibleRef for object/tobject. codec-LCNF-EmitC.lean:31–41 maps those direct native types to float/size_t. This still does not license using a boxed closure wrapper as evidence for the selected direct function.

The next decision remains a single codegen check of the existing probe. Inspect the direct native functions and both cross-edges, including equivalent transformed/fused bodies. If the condition holds but ordinary call/return stack growth remains, the remaining failure is outside this array-RC premise; do not respond by changing bounds or building a public BMM proof. If post-call RC remains, identify the exact object and ownership source before any new runtime version. Machine jump behavior and benefit remain UNKNOWN.
