# B finite producer: minimal diagnostics for existing R26 runner

Priority is unfiltered goals, not an extra runner. If the native runner already builds pinned `ContractExact`, add these direct candidate-only checks in that same public job before long measurements. Do not alter the original gate; these are diagnostic source checks, not official acceptance.

1. Original failing R25 `research/widen/finite-bridge/Kernel.lean` — SHA256 `e5613ee190d4185d665b0cd52482e37dc0770ac468c19ee676cac7a6ba964ab6`. Copy to an owned `work/R26FiniteDiag.lean`, invoke pinned `lake env lean work/R26FiniteDiag.lean`, and preserve the complete stdout and exit code. Original retained verdict has seven headline-only failures; no complete goals survive in existing artifacts.
2. R26 `research/finite-producer/prepare-v1/PrepareCoreContractOnly.lean` — SHA256 `14034d10beed18b520bc6160140ae7bb15dd8640f1e656b14e90cb4971d7b9f4`, 4432 B. This closes or diagnoses the mandatory original mutable producer identity; no finite numeric theorem dependency.
3. If cheap, R26 `research/finite-producer/tail-v1/TailContractOnly.lean` — SHA256 `1156d745db74fd3fd21d11051937ef9464d1328a8db8271a87a0f7ee5a3ccd18`, 1618 B. It checks exact original Tail-to-SUM3 order.

Original finite direct check previously took about 17 seconds in the statement gate, but the new direct command has not been measured. A 60-second per-source cap is a proposed diagnostic budget, not a known enforcement or success guarantee. Core and Tail have passed original policy AST preflight only. Complete hash/roots in `prepare-v1/receipt.json`; full getter and peak sources are follow-on drafts, not part of this first request.
