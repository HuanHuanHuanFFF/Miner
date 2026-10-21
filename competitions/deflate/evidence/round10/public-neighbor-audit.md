# Public-neighbor source audit

I searched local `references`, the historical round reports, and current round10 evidence before making source requests. There are no local source packages for #375, #418, #422, #443, or #489; the only source package among these paths is the existing [#361 reference](../../references/round7-public-361/PROVENANCE.json). Round 09 mentions #418 and #443 as geometry thresholds, but contains no bodies or source hashes for them.

The official complete snapshot in [official-mid-payability](official-mid-payability/pareto-pages.json) is snapshot **27460**, computed at **2026-10-08 04:57:46 +08:00**, with API freshness marked `unknown`. It places all five target submissions on the Pareto frontier. Their official `/source` endpoints returned HTTP 403 with `reason_code=SOURCE_WITHHELD` and this response:

```json
{"type":"about:blank","title":"Not permitted","status":403,"detail":"Source is withheld while this submission is on the Pareto frontier; it is published once another submission beats it","reason_code":"SOURCE_WITHHELD"}
```

The 219-byte response body has SHA-256 `0915db7bc772960652f5dd86fe2b423f1b07431278fc55ee835d34e1ca59e512`. The request and response times for #375, #422, #443, and #489 are recorded in the JSON audit; the #418 diagnostic response time was not retained. No source JSON or code files were downloaded, so no `references/round10-public-*` directories were created. The public snapshot exposes hotkeys and metrics, not source hashes or named authors.

The public coordinates show one especially relevant point: #375 `(1.134506, 34.207568%)` strictly dominates #361 `(1.160869, 34.209958%)`, by about **2.271% lower time** and **0.002390 pp smaller size**. Its source is also withheld while it remains on the frontier. If it becomes public later, it should be the first source-level comparison for a possible re-anchor. Until then, the available #361 source remains the reproducible baseline.

The other points trade speed for size against #361: #418 is 14.860% slower and 0.029487 pp smaller; #422 is 16.890% slower and 0.032715 pp smaller; #443 is 4.535% slower and 0.014872 pp smaller; #489 is 8.448% slower and 0.019058 pp smaller. #489 is newest among these, but its metrics alone do not justify moving the base. Since the source endpoints withhold all five bodies, this audit cannot tell whether their changes are parameter adjustments, structural advances, or mechanisms already covered by round10. It makes no source-level novelty claim.
