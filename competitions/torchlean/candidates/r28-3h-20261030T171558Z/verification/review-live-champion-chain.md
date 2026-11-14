# Fresh champion and promotion-chain review

Captured 2026-10-30 17:22:37 UTC from the seven saved official bodies under `competition-state/`. Boards HTTP 200 SHA-256 is `bb1493f41c6134cb51dc571268261273c32029f9b92b476d575dcf66c13d090e`; publication is `0e82e0a21aad77b3e177b0943bc90ba4a9b8bbc5f66ecb5c74af20a533774c6f`. All six champion responses are HTTP 200, their raw-body hashes and lengths match `live-refresh.json`, each binds to that publication, and the single current promotion matches its board row. Current IDs are overall 59, MLP 33, Mixer 56, ResNet 56, MobileNet 57, normalized MLP 51. Each current row still says `source_available=false`.

All eight separately saved retired/predecessor sources (#54, #8, #7, #36, #11, #53, #45, #43) exist under `source-private/`; byte counts and SHA-256 match the fetch receipts. The audit records hashes only; it does not expose source bodies. These predecessor fetches do not make the current champion source available.

## Nearest public predecessor route gaps

For a current row ratio `r = current time / immediately preceding submission time`, the source is `1/r` times current time; the additional reduction from that source to the `.97` promotion bar is `1 - .97*r`. These are official promotion-chain edges and route-planning facts, not R28 candidate scores or direct measurements against private current sources.

| Board | Current | Public predecessor | predecessor/current | Further reduction to `.97` |
|---|---:|---:|---:|---:|
| ResNet | 56 | 11 | 1.03267× | 6.07% |
| MobileNet | 57 | 53 | 1.04592× | 7.26% |
| Mixer | 56 | 36 | 1.16619× | 16.82% |
| normalized MLP | 51 | 43 | 1.32171× | 26.61% |
| overall | 59 | 54 | 1.33122× | 27.13% |
| MLP | 33 | 13 | 1.59145× | 39.05% |

The earlier cumulative R27 anchor conversions also recalculate exactly from the current chain and saved `derived-gap.json` (audit in [audit-champion-chain.json](audit-champion-chain.json)). They use R27 local anchors: Mixer `0.9980966844` from quick B1 NativeResearch and normalized MLP `0.9894216905` from B8 NativeOnly; the other three `1.0` entries are unit source anchors. Keep those cumulative figures as INFERRED route estimates, not observed candidate-vs-current results. The near-predecessor gaps above are the better current basis for route selection.

## Processing of request 172118

At 17:22 UTC I read `requests/172118-new-public-near-champion-bases.md` and independently confirmed the request's ResNet/MobileNet/Mixer/normalized-MLP arithmetic. The hashes and chain binding pass. Preserve the request's near-champion focus; do not infer that a public predecessor already beats the present champion.
