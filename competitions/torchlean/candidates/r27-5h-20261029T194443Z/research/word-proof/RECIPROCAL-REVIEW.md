# Independent reciprocal review,20:20 UTC

Read Dimpl `ReciprocalUInt64ContractOnly-v2.lean` exact SHA
9555634b7ef92dfb7312eaf9b5103ff0034c0dcc81359f62bcb99129797799de,
`CI-REQUEST-07.json`, and the two actual norm equality snippets.

The mathematical route is valid: R=floor((B-1)/d), a<B and d>0 imply
q=floor(aR/B) satisfies qd≤a<(q+2)d. Thus r=a-qd is an exact nonnegative
word, not merely a modular remainder, and one compare/subtract corrects the
pair. The d=0 branch preserves the original word operations. D's word bridge
establishes the needed product-fit and remainder-subtraction premises; the
corrected quotient fit follows from equality with the original quotient.

D's mulHigh uses four32-bit products and a three-term middle carry. Its
unbounded high_parts_identity is valid even without ll/lh/hl bounds; word
middle additions use each64-bit word's upper/lower32 limits. The final sum is
bounded via a*b<2^128. No mathematical counterexample found by this review.
Lean acceptance remains UNKNOWN; `nlinarith` automation in the generic-base
Nat bounds is an execution uncertainty, not an arithmetic flaw.

Our independently written `ReciprocalNatCore.lean` uses explicit multiplied
inequalities and positivity cancellation, avoiding that nonlinear automation.
It is a fallback small root if D's Nat prefix fails. `MulHighContractOnly.lean`
is a distinct carry-chain implementation with two cross additions instead of
D's explicit middle split; it is not yet a preferred speed variant. Both are
NOT_COMPILED. Do not queue both full helpers just for consensus. Prioritize D07
as the actual integrated route; use ours only for a diagnosed failure or a
later native comparison supported by an identified mulHigh bottleneck.

The actual row integration remains a separate obligation: `r27Ya7G_eq`
rewrites the three quotient/remainder pairs; `r27MYbc_eq` uses the prepared
reciprocal array at the exact row index and preserves the fallback. D's exact
assembled source must compile and pass the original12 gate; the standalone
primitive cannot certify a reconstructed body or cached denominator by itself.

No performance claim is made. A four-partial-product mulHigh may cost more
than one native variable divide on some CPUs; the proposed advantage is reuse
across3pairs and n columns, with one setup division per row. Actual generated
code must show division/remainder sharing and complete-call preparation cost.
