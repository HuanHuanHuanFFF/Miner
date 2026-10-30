# Latest current-board response review — mixer

Droot saved a newer mixer champion response at 21:29:59 UTC. Its receipt is HTTP 200 and body SHA-256 `368a289c1909df47d98ac934490ffbbb87427701e7e45a47da4378e45334cd09`. The body reports promotion 27 / submission 36 as current, with source unavailable, and retired promotion 25 / submission 27 as non-current with `source_available=true`.

That response's publication hash `a8167e48…f312f21` does not match the only saved `boards.raw` publication hash `a1032722…c8f94c1`. I therefore kept the earlier mixer response bound to that boards snapshot as history and marked the latest mixer identity `UNKNOWN_LATEST_RESPONSE_PUBLICATION_MISMATCH`. The strict multiplier now refuses a current-champion conversion for mixer until a matching boards snapshot is saved. No new board request was made here.

The accompanying retired #27 source request failed with HTTP 403. The exact 7,145-byte response body is retained at `competition-state/source27-failure-2130.raw`, SHA-256 `b360ce791b33e3bcbafa47ffececdff4b3e5086dbf3cd1c67528cf00eab8eb4f`; the saved request record identifies a Cloudflare 1010 browser-signature block. This is a source-fetch block, not an algorithm result, and it does not turn the `source_available=true` metadata into source bytes. No source body was recovered or used.

The current-champion report chain still has zero failures for the six previously bound board snapshots. The newer unbound response is listed separately in `official-report-chain.json` and `champion-only-record.json`; the old mixer source/report hashes and response receipt remain available as historical evidence.
