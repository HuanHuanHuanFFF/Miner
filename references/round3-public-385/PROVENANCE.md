# Public reference 385

Retrieved by HTTP GET from the official source endpoint: https://conjectures.io/v1/competitions/deflate/submissions/385/source

- Retrieval: HTTP 200 at 2026-10-06T15:21:27.038Z; the response contained parse_rs and proof_lean, both saved below.
- Scoring snapshot: 23753, computed 2026-10-06T15:15:37.582609+00:00; kind=miner, gate_status=passed, on_frontier=False, admission=passed.
- Official metrics: balanced_time_ratio=0.45050524299274386; mean_file_compression_pct=36.52795642963188; total_compression_seconds=0.6222165600000003.
- Snapshot attribution: miner hotkey 5EP7qGWUrwnATj7Jfvi3AckHVKGsr4poBE326LsxQ4eCNAUr; it differs from #261's hotkey 5GvKW731MCtqWCqtYLcDaBMjmirKuuhBbmJpHnjPJrgtkaT1. The source/snapshot exposes no named author or project affiliation, so project ownership is UNKNOWN.
- SHA-256 parse.rs: 56b92f95a93fd8662c20dd26934fed065f812a685610d09f58d01148cfdb367f
- SHA-256 Parse.lean: db97b9e2c525995a63e31f6b720ff0f234b4acd2a5822663f026848dd0864d62

Active source entry: parse.rs:315-319. `parse` dispatches exact lengths 28,000 and 12,000 to `r109_row17/18`; other inputs enter `bulk_parse`, whose `route` function hard-codes many more lengths to `r109_row0..22` and uses `format_id` for selected sizes. This exact-length dispatch, rather than the file header lineage, is the active entry behavior. It is not recommended as a general structural optimization reference.

Parse.lean contains `bulk_parse_spec` and the final `parse_spec` for `slot.parse`. Presence of the proof source is verified; compilation, obligation acceptance, axiom audit, round trip, gate, benchmark, and stage2 behavior were not checked.