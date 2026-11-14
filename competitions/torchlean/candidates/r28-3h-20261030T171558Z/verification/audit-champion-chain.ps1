$ErrorActionPreference = 'Stop'
$repo = (Get-Location).Path
$round = 'competitions/torchlean/candidates/r28-3h-20261030T171558Z'
$state = Join-Path $repo "$round/competition-state"
$live = Get-Content -LiteralPath (Join-Path $state 'live-refresh.json') -Raw | ConvertFrom-Json
$old = Get-Content -LiteralPath (Join-Path $repo '.runtime/champion-status-20261030T170112Z/derived-gap.json') -Raw | ConvertFrom-Json
$boardSnap = Get-Content -LiteralPath (Join-Path $state 'boards.raw') -Raw | ConvertFrom-Json
$boardHash = (Get-FileHash -Algorithm SHA256 -LiteralPath (Join-Path $state 'boards.raw')).Hash.ToLowerInvariant()
$boardReceipt = $live.receipts | Where-Object { $_.url -match '/boards$' }
$results = @()
$allChecks = $true
foreach ($expected in $old.rows) {
    $name = [string]$expected.board
    $path = Join-Path $state "champions-$name.raw"
    $bytes = [System.IO.File]::ReadAllBytes($path)
    $sha = [Convert]::ToHexString([System.Security.Cryptography.SHA256]::HashData($bytes)).ToLowerInvariant()
    $receipt = $live.receipts | Where-Object { $_.url -match ("champions\?board=" + [regex]::Escape($name) + '$') }
    $response = [System.Text.Encoding]::UTF8.GetString($bytes) | ConvertFrom-Json
    $boardDef = $boardSnap.boards | Where-Object { $_.id -eq $name }
    $currentRows = @($response.champions | Where-Object { $_.current -eq $true })
    $currentIndex = [Array]::FindIndex([object[]]$response.champions, [Predicate[object]]{ param($x) $x.current -eq $true })
    $anchorIndex = [Array]::FindIndex([object[]]$response.champions, [Predicate[object]]{ param($x) $x.submission -eq $expected.candidate_anchor })
    $binding = ($sha -eq $receipt.sha256) -and ($bytes.Length -eq $receipt.bytes) -and ($receipt.status -eq 200) -and ($response.publication_hash -eq $boardSnap.publication_hash) -and ($boardDef.current_promotion_id -eq $currentRows[0].promotion_id) -and ($currentRows.Count -eq 1) -and ($currentRows[0].submission -eq $expected.champion)
    if ($currentIndex -lt 0 -or $anchorIndex -le $currentIndex) { throw "Missing promotion path for $name" }
    $edges = @($response.champions[$currentIndex..($anchorIndex - 1)])
    $currentEdgeRatio = [double]$response.champions[$currentIndex].ratio
    $nearestPublicPredecessor = $response.champions[$currentIndex + 1]
    $product = 1.0
    foreach ($edge in $edges) { $product *= [double]$edge.ratio }
    $recomputed = [double]$expected.local_anchor_ratio / $product
    $matches = [Math]::Abs($recomputed - [double]$expected.candidate_current_champion) -lt 1e-10
    $allChecks = $allChecks -and $binding -and $matches
    $chainRows = @($edges | ForEach-Object { [ordered]@{submission=[int]$_.submission; promotion_id=[int]$_.promotion_id; ratio=[double]$_.ratio; source_available=[bool]$_.source_available} })
    $results += [ordered]@{
        board=$name; current_submission=[int]$currentRows[0].submission; current_promotion_id=[int]$currentRows[0].promotion_id
        current_source_available=[bool]$currentRows[0].source_available; anchor_submission=[int]$expected.candidate_anchor
        nearest_public_predecessor_submission=[int]$nearestPublicPredecessor.submission
        current_over_nearest_predecessor=[double]$currentEdgeRatio
        nearest_predecessor_over_current=(1.0/$currentEdgeRatio)
        nearest_predecessor_reduction_to_0_97_fraction=(1.0 - 0.97*$currentEdgeRatio)
        response_sha256=$sha; response_bytes=$bytes.Length; receipt_status=[int]$receipt.status
        publication_match=($response.publication_hash -eq $boardSnap.publication_hash)
        board_promotion_match=($boardDef.current_promotion_id -eq $currentRows[0].promotion_id)
        current_row_count=$currentRows.Count; bound=$binding; chain_links=$chainRows
        promotion_product=$product; local_anchor_ratio=[double]$expected.local_anchor_ratio
        recomputed_candidate_over_current=$recomputed; saved_candidate_over_current=[double]$expected.candidate_current_champion
        recomputation_match=$matches; reduction_to_match_fraction=(1.0 - 1.0/$recomputed)
        reduction_to_0_97_fraction=(1.0 - 0.97/$recomputed)
        classification='INFERRED_FROM_R27_LOCAL_ANCHOR_AND_OFFICIAL_PROMOTION_CHAIN; not current candidate result or official direct pair'
    }
}
$sourceReceipts = @($live.receipts | Where-Object { $_.url -match '/submissions/\d+/source$' })
$sourceChecks = @()
foreach ($r in $sourceReceipts) {
    $full = [System.IO.Path]::GetFullPath((Join-Path $repo $r.path))
    $allowed = $full.StartsWith([System.IO.Path]::GetFullPath((Join-Path $state 'source-private')),[StringComparison]::OrdinalIgnoreCase)
    if (-not $allowed) { throw 'Source receipt path escaped the R28 private source folder' }
    $present = Test-Path -LiteralPath $full
    $hash = if ($present) { (Get-FileHash -Algorithm SHA256 -LiteralPath $full).Hash.ToLowerInvariant() } else { $null }
    $sourceChecks += [ordered]@{submission=[int]$r.submission; status=[int]$r.status; bytes=[int]$r.bytes; receipt_sha256=$r.sha256; saved_file_present=$present; saved_hash_matches=($present -and $hash -eq $r.sha256)}
}
$sourceAll = (@($sourceChecks | Where-Object { -not $_.saved_hash_matches }).Count -eq 0)
$allChecks = $allChecks -and ($boardHash -eq $boardReceipt.sha256) -and ($boardReceipt.status -eq 200) -and $sourceAll
$out = [ordered]@{
    round='R28'; state='INDEPENDENT_READ_ONLY_BINDING_AND_CHAIN_RECALCULATION'; captured_at_utc=[DateTime]::UtcNow.ToString('yyyy-MM-ddTHH:mm:ssZ')
    board_publication_hash=$boardSnap.publication_hash; boards_sha256=$boardHash; boards_receipt_sha256=$boardReceipt.sha256
    boards_bytes=(Get-Item (Join-Path $state 'boards.raw')).Length; boards_status=[int]$boardReceipt.status
    results=$results; source_receipt_count=$sourceChecks.Count; source_receipts=$sourceChecks
    checks_passed=$allChecks; notes=@('Only response metadata, hashes, promotion ratios and local anchor values retained; source bodies were not emitted.','Local anchor ratios are R27 fixed-scorer results or unit reference anchors; they are cross-environment/seed route estimates.','The current champion source_available flag is kept separate from predecessor source fetch receipts.')
}
$out | ConvertTo-Json -Depth 10 | Set-Content -LiteralPath (Join-Path $repo "$round/verification/audit-champion-chain.json") -Encoding utf8
$out | ConvertTo-Json -Depth 6
