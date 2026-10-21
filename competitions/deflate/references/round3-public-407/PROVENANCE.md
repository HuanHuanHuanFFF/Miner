# Public reference 407

Retrieved by HTTP GET from the official source endpoint: https://conjectures.io/v1/competitions/deflate/submissions/407/source

- Retrieval: HTTP 200 at 2026-10-06T15:21:20.348Z; the response contained parse_rs and proof_lean, both saved below.
- Scoring snapshot: 23753, computed 2026-10-06T15:15:37.582609+00:00; kind=miner, gate_status=passed, on_frontier=False, admission=passed.
- Official metrics: balanced_time_ratio=0.4499838311061295; mean_file_compression_pct=36.499576583188635; total_compression_seconds=0.6151808350000001.
- Snapshot attribution: miner hotkey 5G4QE3WeVrjCo2VQaBYttFWrHexzuPFAibGjGDgi6mR8eX8F; it differs from #261's hotkey 5GvKW731MCtqWCqtYLcDaBMjmirKuuhBbmJpHnjPJrgtkaT1. The source/snapshot exposes no named author or project affiliation, so project ownership is UNKNOWN.
- SHA-256 parse.rs: 64945bab5fa675ed724748b3097bf02477ba3677afc9fa4478a394ccc0996a40
- SHA-256 Parse.lean: ed37de55387d9a984afa841b83aac1edd4ea4517cfb5831967884b6783fa98a8

Active source entry: parse.rs:3661-3690. The exported dispatch runs a quick sampled RLE check for sufficiently large input, samples byte statistics and selects an initial `fl_part` path, then routes remaining input by sampled entropy/mode to high-entropy or main lanes. `main_parse` further selects high-entropy, zero-rich/3-byte and standard lanes. This description follows the exported `parse`, not the file header.

Parse.lean contains the final `Submission.parse_spec` for `slot.parse`. Presence of the proof source is verified; compilation, obligation acceptance, axiom audit, round trip, gate, benchmark, and stage2 behavior were not checked.