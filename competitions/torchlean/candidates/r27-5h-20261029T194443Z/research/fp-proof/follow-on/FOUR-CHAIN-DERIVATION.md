# Four independent native64 chains with the existing radius

Status: PAPER_DERIVATION; no implementation, Lean acceptance or native speed claim.

Let each exact binary32 product be a finite binary64 term with magnitude less than M=2^k, -250<=k<=256. Let total count n<=2^L, 3<=L<=30. Split the terms into four lanes, each of length at most2^(L-2), and evaluate each lane with the existing native64 sum loop. Merge as (s0+s1)+(s2+s3).

SUM3 gives each lane error at most G=2^(k+2(L-2)-53), and native magnitude at most laneCount*M. The exact grid lemma for j*M, j<=2^30, remains applicable at every merge. Therefore all three merge results are finite and retain the count*M magnitude bound.

For a merge, the exact native input magnitude is at most2^(k+L). Use the strictly larger power2^(k+L+1) in SUM3's existing local error theorem. Its rounding error is at most J=2^(k+L-52). This avoids introducing a new closed-bound rounding theorem.

The full error is at most4G+3J. Since L>=3, J<=4G, so4G+3J<=16G=2^(k+2L-53). Substituting k=H-250 gives exactly the existing radius2^(H+2L-303). No radius constant or midpoint checker change is needed. n<=4 can retain the current sequential path; this is a runtime branch, not a restriction on the final kernel's input domain.

A four-lane runtime still needs its own exact partition/term-order connection. Interleaving indices0,4,8,... etc provides equal exact real total after proving the partition. It does not promise equal native sums. The existing strict checker/error argument would certify the proposed output, and the separately proved fallback handles all misses.

This is relevant only after the cheaper lazy-word-preparation complete-call experiment. Four chains may remove an add-latency dependency, but preparation, FloatArray getters, branches and output work can dominate. Native whole-call cost, source-specific full12 proof and a reconciled current-champion comparison remain necessary.
