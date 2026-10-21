**Refusals**

- 403 `ROLE_NEEDS_BROWSER`: called with a CLI bearer token
- 403 `ROLE_REQUIRED`: the account lacks the ADMIN role
- 503 `OPERATOR_ADAPTER_UNAVAILABLE`: **always, on the current schema** (the adapter refuses any database with `submissions.verification_attempt`, which the public routes require)
- 404 `NOT_FOUND`

## FloatLib

`{board}` is a FloatLib board: `floatlib`, the paid full entry (slot `full`), or one of its practice boards: `floatlib-add`, `-mul`, `-fma`, `-div`, `-sqrt`, `-sum`, `-bmm`. All of them read FloatLib's own database (`COMPETITION_FLOATLIB_DATABASE_URL`, as the `platform_api` role of `conjectures-optimisation-float-kernels`) and nothing else. The shapes are FloatLib's own API's (`validator/service/schemas.py` there), plus `kernels`, `promoted_at`, `/champions` and the rules on `/health`. Times are `YYYY-MM-DDTHH:MM:SSZ`, ids integers. Full-entry submissions are accepted here when enabled; practice boards are read-only. Every route answers **404 `NOT_FOUND`** when FloatLib is not served here, and **503 `COMPETITION_SCHEMA_UNAVAILABLE`** when its database is older than its migration 0016 or `platform_api` cannot read `promotions`.

### GET `/v1/competitions/{board}`

The board in the [Competition](#competition) shape, so `/v1/competitions` lists FloatLib (once, as `floatlib`) beside DEFLATE: `files` is `Kernel.lean`, the one metric is `ratio` (lower is better), `policy` is the latest published scoring's, and `submissions_open` reflects `FLOATLIB_SUBMISSIONS_ENABLED` and the global pause flag (practice boards are always closed).

### GET `/v1/competitions/{board}/health`

| Field | Type | Meaning |
| --- | --- | --- |
| `ok` | boolean | FloatLib's database answered |
| `queued` | integer | Queued plus verifying, across every board |
| `promotion_bar` | number | The ratio a submission must reach to be promoted; `0.97` until the first publication |
| `competition_share` | number or null | The competition's share of the validator's emission, as last published |
| `admission` | object or null | `{draws, quantile}`: the bootstrap behind promotion, as last published |
| `rank_shares` | number array or null | Published fractions of the slot winner share, newest champion first (currently `[0.6, 0.3, 0.1]`); null for older snapshots |

### GET `/health`

FloatLib's `/health`, at the root where FloatLib's own API serves it, in the same shape as `/v1/competitions/{board}/health` above. It never fails because of FloatLib's database, as FloatLib's own does not: while that database is unreachable or FloatLib is not served here it still answers 200 with `"ok": true`, `queued`, `competition_share`, `admission` and `rank_shares` null, and `promotion_bar` at its default `0.97`. It is not the platform's liveness probe, which is `/healthz`.

### GET `/v1/competitions/{board}/leaderboard`

The board: the champion first, then every other hotkey's best accepted ratio against it, fastest first.

Optional query parameter `champion_id` selects a champion's submission ID from `/champions`.
Without it, the response is unchanged. For example,
`GET /v1/competitions/floatlib/leaderboard?champion_id=42` returns champion #42 first,
then each hotkey's best accepted submission measured against its promoted code hash.
Unknown IDs, submissions never promoted, and champions from another board return 404;
non-positive or malformed IDs return 422. There is no page pagination.

On a historical board, `leader` identifies the selected reference, not today's champion.
Actual promoted challengers carry their promotion date and `admission: "qualifies"`,
including a successor from the reference champion's own hotkey. Other admission outcomes
are null unless the retained scoring publication belongs to the selected champion;
statistics are not recomputed. The `promotion_bar` and `qualifies` threshold flag retain
their existing meaning using the latest published policy, not a reconstructed historical
policy. Ratios are saved measurements against the selected code; they are not converted
into ratios against today's champion. Use `/champions`'s `current` field to distinguish them.


| Field | Type | Meaning |
| --- | --- | --- |
| `slot` | string | `full` or the practice board's kernel |
| `incumbent_sha256` | string or null | The latest recorded incumbent, provenance |
| `champion_sha256` | string or null | The Kernel.lean every ratio here is measured against |
| `verifier_fingerprint` | string or null | The verifier of the newest verdict |
| `promotion_bar` | number | As on `/health` |
| `leader` | integer or null | The champion's submission; null while the shipped champion holds |
| `pays` | boolean | Whether the champion's author is paid: the full entry only |
| `ranking[]` | array | `rank`, `submission`, `hotkey`, `ratio`, `qualifies` (at or below the bar), `admission`, `submitted_at`, `kernels`, `promoted_at` |

`admission` is `leader` on the champion's row on every board; on the others it is the latest published scoring's outcome (`qualifies`, `not-significant`, `above-bar`, `no-evidence`), which scores only the full entry, so practice-board rows carry `null`. `kernels` is ns per operation for each kernel, summed over its timed input types: `{add, mul, sum, bmm}` on the full entry, the board's own kernel on a practice board. `promoted_at` is when the champion took over, on its row only by default. Historical boards also include the promotion dates of promoted challengers.

### GET `/v1/competitions/{board}/champions`

Every submission the board promoted, newest first, without pagination: `[{submission, hotkey, ratio, speedup_vs_shipped, promoted_at, demoted_at, current, rank, rank_share}]`. `ratio` is against the champion it took over from: its total time over that champion's, so lower is faster.

`speedup_vs_shipped` is the shipped kernels' time over this champion's, so higher is faster: 1 divided by the product of the ratios along the chain of code each champion was timed against, ending at the shipped code the first promotion was timed against. The chain follows hashes, not promotion order, because after a demotion the next challenger is timed against the older champion the board fell back to. It is null when the chain is broken (a missing ratio, or a reference that is neither shipped nor an earlier promotion). Each link is its own bench run, so it is an estimate whose noise grows with the chain; clients should read it rather than multiply ratios themselves. A newer promotion supersedes a champion without demoting it, and `demoted_at` records an explicit operator demotion, which hands the board back to the newest earlier champion not demoted -- so `current` says who holds the board.

`rank` is the reward rank (1 is the current champion), and `rank_share` is that rank's fraction of the slot winner share. These use the latest published `policy.rank_shares` and the current non-demoted promotion history. Missing ranks are not redistributed; a hotkey can hold multiple ranks. Both fields are null for older champions, unpaid practice boards, and publications without a valid rank policy. They describe the reward rule, not proof that an on-chain payout has occurred; pause withholding and the competition's emission share apply separately.

### GET `/v1/competitions/{board}/submissions/{submission_id}`

One submission of that board (another board's id is a 404): `id`, `hotkey`, `slot`, `digest`, `submitted_at`, `state`, `exit_code`, `stage`, `reason`, `ratio`, `classes` (per input type: `incumbent_ns`, `submission_ns`, `ratio`, `spread_inc`, `spread_sub`), `seed`, `incumbent_sha256`, `champion_sha256`, `verifier_fingerprint`, and `verification_current` (an accepted verdict from the newest verdict's verifier; null otherwise).

### GET `/v1/competitions/{board}/submissions/{submission_id}/report`

`{report}`: the gate's verdict JSON in full, as a string.

## Signing a submission

`POST /v1/competitions/{slug}/submissions` authenticates by an sr25519 signature from the subnet hotkey over these five lines, joined by `\n` with no trailing newline:

```
conjectures-competition-submit-v1
competition: <slug>
digest: <digest>
hotkey: <hotkey ss58>
timestamp: <unix seconds>
```

- `digest` is lowercase hex of sha256 over the `parse.rs` bytes immediately followed by the `Parse.lean` bytes.
- `timestamp` is the same integer sent in `X-Conjectures-Timestamp`; it must be within 300 s of server time.
- `X-Conjectures-Signature` is the signature as hex, with or without `0x`.
- The server rebuilds the message from the slug in the path and the bytes it received, so any mismatch is `SIGNATURE_INVALID`.
- Reference client: `python miner/submit.py submit <dir> --hotkey <hotkey file> --url https://<api>` in the conjectures-optimisation-deflate repository.

## Schemas

Every response model referenced above, field by field. "Required" means always present in the JSON; a type ending in `null` may be null.

<a id="schema-index"></a>

### Index

| Field | Type | Required | Notes |
| --- | --- | --- | --- |
| `items` | array of [Competition](#schema-competition) | yes |  |
| `total` | integer | yes | Competitions configured here, whatever `limit` returned |
| `limit` | integer \| null | yes | The page size asked for, or null for every competition |
| `offset` | integer | yes |  |

<a id="schema-competition"></a>

### Competition

| Field | Type | Required | Notes |
| --- | --- | --- | --- |
| `slug` | string | yes |  |
| `name` | string | yes |  |
| `submissions_open` | boolean | yes |  |
| `queue_depth` | integer | yes |  |
| `current_snapshot_id` | string \| null | yes | Scoring snapshot the reads use by default |
| `description` | string | yes |  |
| `files` | array of object | yes | Each `{name: string, max_bytes: integer}`: `parse.rs` and `Parse.lean`, 524288 bytes each |
| `metric_definitions` | array of object | yes | Each `{key, label, unit, better}` (all strings): `balanced_time_ratio` (ratio) and `mean_file_compression_pct` (percent), both `better: "lower"` |
| `policy` | object \| null | yes | The snapshot's scoring policy: `method`, `version`, `speed_floor`, `max_balanced_time_ratio`, `max_mean_file_compression_pct`, `max_ratio_pct`, `pareto_share`, `improvement_share`, `improvement_window`, `improvement_threshold`, `improvement_decay`, `competition_share`, `alpha_total_submission_bounty`, `required_corpora` (array of string), `bootstrap_draws`, `confidence_level`, `admission_policy_version`. Null before the first snapshot |
| `policy_status` | string | yes | `"ready"` once a snapshot has published a policy |
| `execution_limits` | object | yes | `{benchmark_timeout_seconds, gate_timeout_seconds}`, both integer or null (null today) |
| `context` | [Context](#schema-context) | yes |  |

<a id="schema-accepted"></a>

### Accepted

| Field | Type | Required | Notes |
| --- | --- | --- | --- |
| `competition` | string | yes |  |
| `submission` | string | yes | Submission id |
| `state` | string | yes | `"queued"` for a new submission; the current state for a repeat |
| `digest` | string | yes | sha256 hex of `parse.rs` bytes followed by `Parse.lean` bytes |
| `created` | boolean | yes | False when the same files were already queued by this hotkey |
| `slots_remaining` | integer | yes | Unspent registrations left for more submissions |
| `status_url` | string | yes | Path of the submission's detail endpoint |

<a id="schema-submissionpage"></a>

### SubmissionPage

| Field | Type | Required | Notes |
| --- | --- | --- | --- |
| `context` | [Context](#schema-context) | yes |  |
| `items` | array of [Submission](#schema-submission) | yes |  |
| `next_cursor` | string \| null | no |  |
| `total` | integer | yes | Submissions matching the filters, when the page was read |

<a id="schema-detail"></a>

### Detail

| Field | Type | Required | Notes |
| --- | --- | --- | --- |
| `submission` | [Submission](#schema-submission) | yes |  |
| `digest` | string | yes |  |
| `source_sha256` | string \| null | yes |  |
| `pipeline_observed_at` | string | yes | When the pipeline state was read |
| `pipeline` | map of string → [Stage](#schema-stage) | yes | Keys `static`, `lean`, `benchmark`, `aggregation` |
| `current_evidence` | map of string → string \| null | yes | Keys `aggregation_id`, `admission_check_id` |
| `bounds` | [Bounds](#schema-bounds) \| null | yes |  |
| `context` | [Context](#schema-context) | yes |  |
| `links` | map of string → string | yes | Keys `report`, `source`, `admission`: paths of those endpoints |

<a id="schema-admissionresponse"></a>

### AdmissionResponse

| Field | Type | Required | Notes |
| --- | --- | --- | --- |
| `context` | [Context](#schema-context) \| null | yes |  |
| `admission` | [Admission](#schema-admission) | yes |  |
| `decision` | [AdmissionDecision](#schema-admissiondecision) \| null | yes |  |

<a id="schema-paretopage"></a>

### ParetoPage

| Field | Type | Required | Notes |
| --- | --- | --- | --- |
| `context` | [Context](#schema-context) | yes |  |
| `axes` | map of string → string | yes |  |
| `bounds` | [Bounds](#schema-bounds) | yes |  |
| `items` | array of [ParetoPoint](#schema-paretopoint) | yes |  |
| `next_cursor` | string \| null | no |  |
| `total` | integer | yes | Points in the pinned snapshot |

<a id="schema-leaderboard"></a>

### Leaderboard

| Field | Type | Required | Notes |
| --- | --- | --- | --- |
| `context` | [Context](#schema-context) | yes |  |
| `bounty_limit_alpha` | number \| null | no | The most alpha any one (hotkey, submission) pair is paid over its lifetime; null before the competition recorded bounties |
| `ranking` | array of [Ranking](#schema-ranking) | yes |  |
| `next_cursor` | string \| null | no |  |
| `total` | integer | yes | Ranked hotkeys in the pinned snapshot |

<a id="schema-weights"></a>

### Weights

| Field | Type | Required | Notes |
| --- | --- | --- | --- |
| `competition` | string | yes |  |
| `context` | [Context](#schema-context) | yes |  |
