# Final frontier refresh review

Independent read-only review of `official-final-retry1`, captured at snapshot **27887** (`2026-10-08 00:29:15.316831 UTC`; retrieval `00:29:33.024881–00:29:41.744266 UTC`). The capture freshness is reported as `unknown`.

All **13/13** raw response files match the receipt's byte counts and SHA-256 values; all HTTP statuses are 200. The four derived files also match their receipt digests, and each decoded raw Pareto/leaderboard page and weights response equals its derived JSON value. The Pareto pages are pinned to snapshot 27887 and contain **501 unique rows across six pages** (`100, 100, 100, 100, 100, 1`); every request cursor matches the prior response and the final cursor is null. The leaderboard contains **476 rows across five complete pages** (`100, 100, 100, 100, 76`) on the same snapshot. The raw competition policy, receipt policy, and derived policy agree.

The captured policy is `local-global-improvement-space-log`, with 10.0/40.0 bounds and Pareto/improvement shares of 1.0/0.0. The local scorer replay checked 491 scored rows; the other 10 rows are pending without metrics. Its maximum Pareto-weight difference is `2.78e-17`. The saved weights/current context also records snapshot 27887, and the receipt says the snapshot IDs match. The API response reports `chain_accepted=false`; that is an API field, not finalized-chain proof. Actual chain acceptance remains **UNKNOWN**.

The refreshed row changes the #453 conclusion. Submission **#453** is now off the frontier with Pareto and payable weights both zero, while `payment_eligible=true`. New submission **#501** is on the frontier at `(0.43541753, 36.79888211)` and strictly dominates #453 at `(0.43787346, 36.99972856)`. No same-hotkey frontier submission survives in this snapshot.

Replaying the hypothetical point `(1.25, 34.18)` against snapshot 27887 gives **2.22413193%** geometric share and the same conditional same-hotkey share, because #453 no longer survives on the frontier. This remains a hypothetical allocation conditional on eligibility and admission; it is not an actual payment or chain result.

The best pipeline same-family projection, `(1.40378031, 34.18551719)`, remains dominated by each of #360, #418, and #422. Its current geometric and conditional shares are zero. This describes the projected point's position in the captured public geometry; it does not assert a realized reward or validate live deployment identity.
