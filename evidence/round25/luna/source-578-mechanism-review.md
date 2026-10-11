# Round 25 public source check: submission #578

## Capture

The ordinary public endpoint `https://conjectures.io/v1/competitions/deflate/submissions/578/source` returned HTTP 200 during the current published snapshot **29673**. The untouched response is `evidence/round25/luna/source-578/578.response.json` (783,705 bytes, SHA-256 `8954eea734dc4465505e9cff5907593117773e783129e508834ef162a20991e`). The official source fields are preserved in `references/round25-public-578/`: `parse.rs` is 360,986 bytes, SHA-256 `e1f72d323e66a6787cb1310b2f07cb1d4045ceb247a78f2fb3547d2cd03d951e`; `Parse.lean` is 405,152 bytes, SHA-256 `4090a61ae9f3702cc36d57b36d6c103b05d0640a352a2cfedd0000340289b2c4`. The response receipt records author hotkey `5EbuBvUpc3tPmQnfYdeeUUxmeCnzJcG1HQ4stFLbknVf4kNW` and request time `2026-10-11T08:18:59.746954Z`–`08:19:02.271594Z`.

Snapshot 29673 reports #578 as gate `passed`, admission `passed`, but not on the Pareto frontier and with zero payable share. Source availability does not change that result. No new local gate or performance run was performed.

## Comparison with #595

The comparison used the retained public #595 bytes in `references/round21-public-595/` (source response SHA-256 `df6d774a026fb4f025005b615d7780fb8353d0a18e54ef87a491591f57cd28a7`; its source receipt records HTTP 200 on 2026-10-10). Both files describe the same `mA` content-adaptive LZ77 parser family: byte-histogram classification selects a parser route; hash-chain matching, lazy search, and per-class parameter choices drive the parser. #595's source header records lineage from public #514 with selected search rows from #590/#583/#542.

Against #583's already retained public source, #578 has the same 360,986-byte Rust file and differs in 9 localized hunks (15 changed lines on each side). The differences are in class-to-row dispatch and row-to-kernel parameter assignments; the shared classifier and matching kernels remain line-identical. Against #595, the line diff has 19 localized hunks (41 changed lines in #578, 35 in #595); it is again routing, parameter selection, and provenance/header text around the same parser family. This is evidence of a retuning/reassignment within the existing family, not a distinct matching mechanism. The line comparison is a source-diff screen, not a semantic proof or a gate result.

## Current coordinate proximity

| Submission | Balanced time ratio | Mean compression % | Relative to #612 |
|---|---:|---:|---|
| #612 | 0.4304598592 | 36.5273012167 | Current rank 1 |
| #595 | 0.4318296105 | 36.5781427955 | +0.0013697512 time; +0.0508415788 pp size |
| #578 | 0.4337752813 | 36.5503326918 | +0.0033154221 time; +0.0230314751 pp size |

#578 is farther from #612 on time but closer on compression than #595, so there is no axis-independent scalar meaning of “closer” without a stated normalization. Both coordinates are strictly dominated by #612; #626 is also better than each on both axes. #578 does not supply evidence for a new mechanism nearer to #612 than #595.

**Decision use:** preserve #578 as a legally retrieved, author-attributed source reference only. It may inform parameter/routing comparisons if that exact family is selected; it does not justify a distinct-mechanism experiment by itself.
