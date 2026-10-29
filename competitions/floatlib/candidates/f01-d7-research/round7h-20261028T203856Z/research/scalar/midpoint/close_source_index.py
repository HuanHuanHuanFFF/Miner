"""Refresh B's current source index without changing frozen source or evidence."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
SCALAR = HERE.parent
ROOT = Path(__file__).resolve().parents[8]
ROUND = HERE.parents[2]
CANDIDATES = ROOT / 'competitions/floatlib/candidates'

def digest(b):
    return hashlib.sha256(b).hexdigest()

def entry(p):
    b = p.read_bytes()
    return {'path': str(p.relative_to(ROOT)).replace('\\', '/'), 'bytes': len(b), 'sha256': digest(b)}

def main():
    now = datetime.now(timezone.utc)
    stamp = now.strftime('%Y%m%dT%H%M%SZ')
    public = []
    api = [
        ('SignedSemantics-Core.lean.raw', 'ada0d4c6c8041c245bee146ca921a31f1869edb2',
         'lean-dojo/FloatLib', '0d91825727839f597fd06b22fdd038ea21480f0c',
         'FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/SignedSemantics/Core.lean', 'MIT; FloatLib Team'),
        ('Lean-Nat-Mod.lean.raw', '463a9cd95eee65cc8fa315bc157ad0b197b8f115',
         'leanprover/lean4', 'v4.34.0', 'src/Init/Data/Nat/Mod.lean', 'Apache 2.0; Lean FRO, LLC; Kim Morrison')
    ]
    for name, blob, repo, ref, remote, license in api:
        p = HERE / 'sources' / name
        b = p.read_bytes()
        def git_blob(v):
            return hashlib.sha1(b'blob ' + str(len(v)).encode() + b'\0' + v).hexdigest()
        if git_blob(b) != blob:
            assert b.endswith(b'\n') and git_blob(b[:-1]) == blob
            b = b[:-1]
            p.write_bytes(b)
        assert git_blob(b) == blob
        public.append({**entry(p), 'git_blob_sha1': blob, 'git_blob_verified': True,
                       'url': f'https://github.com/{repo}/blob/{ref}/{remote}', 'license': license})
    (HERE / 'raw-midpoint-public-sources.json').write_text(json.dumps(public, indent=2) + '\n', encoding='utf-8')

    core_path = CANDIDATES / 'f01-r24-dev-core-certificate1/Kernel.lean'
    core = core_path.read_bytes()
    assert digest(core) == '049b01fae1ff44a2479b2e3c0c1566329e580e7da2c5826045e1980835890934'
    quotient = CANDIDATES / 'f01-r24-research-scalar-quotient2/Quotient.lean.inc'
    qb = quotient.read_bytes()
    assert digest(qb) == '5733f2e317b9ce71e3b213ad4283148ff8870276e4dd7d327874096a090fd541'
    assert qb in core
    math3_path = ROUND / 'development-math3-results.json'
    math3 = json.loads(math3_path.read_text(encoding='utf-8'))
    assert math3['core']['statement_pass'] and math3['core']['kernel_replay'] and math3['core']['helper_axioms_accepted']
    audit = ROUND / math3['core']['audit_path']
    assert digest(audit.read_bytes()) == math3['core']['audit_sha256']
    accepted_component = {
        'run': 40793795026, 'carrier': entry(core_path), 'component': entry(quotient),
        'byte_exact_component_containment': True, 'audit': entry(audit),
        'collector_result': entry(math3_path),
        'roots': ['Submission.R24QuotientCertificate.checker_sound', 'Submission.R24QuotientCertificate.rounded_toNat'],
        'acceptance': 'STATEMENT_MODULE_REPLAY_AXIOMS_PASS_IN_EXACT_CORE13',
        'not_inherited': 'No acceptance for quotient2 full B2 Kernel, parent islands, performance, full25, or new target.'
    }
    sources = sorted(SCALAR.rglob('*.lean.inc')) + sorted(SCALAR.rglob('*.py'))
    for candidate in ['f01-r24-research-scalar-quotient1', 'f01-r24-research-scalar-quotient2']:
        sources += sorted((CANDIDATES / candidate).glob('*.lean'))
        sources += sorted((CANDIDATES / candidate).glob('*.lean.inc'))
        sources += sorted((CANDIDATES / candidate).glob('*.py'))
    indexed = []
    for p in sources:
        item = entry(p)
        if p == quotient:
            item['status'] = 'ACCEPTED_ONLY_WITH_EXACT_CORE13_CARRIER'
        elif 'f01-r24-research-scalar-quotient1' in p.parts and p.name.endswith(('.lean', '.lean.inc')):
            item['status'] = 'FROZEN_REAL_CI_FAILURE_40779515020'
        elif 'quotient2' in '/'.join(p.parts) and p.name == 'Kernel.lean':
            item['status'] = 'FULL_B2_KERNEL_NOT_VALIDATED_BY_COMPONENT_PASS'
        elif p.name == 'PowerCell-v3.lean.inc':
            item['status'] = 'FROZEN_ISLAND5_RECURSION_FAILURE_TWO_LOCATIONS'
        elif p.name == 'PowerCell-v4.lean.inc':
            item['status'] = 'NO_POWER_ERRORS_IN_FAILED_ISLAND6_NOT_WHOLE_ARTIFACT_ACCEPTANCE'
        elif p.name == 'NormalCell.lean.inc':
            item['status'] = 'ROOT_STATIC_REVIEW_READY_PUBLIC_TYPING_NOT_OBSERVED'
        elif p.parent.name == 'transport' or p.name == 'Runtime-signed-add.lean.inc':
            item['status'] = 'FROZEN_SUBLINE_NOT_RUN'
        elif p.name.endswith('.lean.inc'):
            item['status'] = 'SOURCE_DRAFT_PUBLIC_TYPING_NOT_OBSERVED'
        else:
            item['status'] = 'LIGHTWEIGHT_LOCAL_SCRIPT_NOT_A_LEAN_ACCEPTANCE_ARTIFACT'
        indexed.append(item)
    out = {
        'observed_at_utc': now.isoformat(), 'first_actual_tool_utc': '2026-10-28T20:43:26Z',
        'round_start_utc': '2026-10-28T20:38:56Z', 'round_deadline_utc': '2026-10-29T03:38:56Z',
        'current_entry': 'midpoint/HANDOFF.md', 'sources': indexed,
        'verified_component_acceptance': accepted_component,
        'newest_components_receipt': entry(HERE / 'raw-midpoint-source-receipt.json'),
        'public_source_receipt': entry(HERE / 'raw-midpoint-public-sources.json'),
        'actual_power_latest_collector': entry(ROUND / 'development-math4-results.json'),
        'tokens': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN',
        'continuous_activity': 'UNKNOWN_NOT_INFERRED_FROM_FIRST_LAST_SPAN',
        'CI_Git_owner': 'D only', 'local_Lean_or_native_compilation': 'NONE',
        'next': 'Actual typed feedback first; then final source handoff. No new long task after03:15.'
    }
    (SCALAR / 'SOURCE-INDEX.json').write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
    status = SCALAR / 'notes/status.json'
    if status.exists():
        (SCALAR / 'notes' / f'status-history-{stamp}.json').write_bytes(status.read_bytes())
    status.write_text(json.dumps({
        'state': 'RAW_MIDPOINT_SIGN_AND_FIELD_SOURCE_READY_PENDING_PUBLIC_TYPING',
        'first_actual_tool_utc': out['first_actual_tool_utc'], 'last_actual_tool_utc': now.isoformat(),
        'round_start_utc': out['round_start_utc'], 'common_deadline_utc': out['round_deadline_utc'],
        'current_entry': 'midpoint/HANDOFF.md', 'source_index': 'SOURCE-INDEX.json',
        'tokens': 'UNKNOWN', 'cached_input_tokens': 'UNKNOWN', 'continuous_activity': out['continuous_activity'],
        'actual_accepted_scope': 'Exact core13 carrier containing quotient2 fragment; no parent inheritance.',
        'new_track_code': 'NONE', 'new_track_ci': 'NONE', 'git_operator': 'D'
    }, indent=2) + '\n', encoding='utf-8')
    handoff = HERE / 'HANDOFF.md'
    (HERE / f'HANDOFF-history-{stamp}.md').write_bytes(handoff.read_bytes())
    handoff.write_text(f'''# B scalar / midpoint current handoff

Last actual update {now.isoformat()}. Common R24 window20:38:56–03:38:56 UTC unchanged; no new long task after03:15. First B tool20:43:26; continuous activity, tokens/cache UNKNOWN. D alone owns Git/CI; no local Lean/native build or new target runtime.

**Newest source:** `NativeSignOr.lean.inc` 2740B / `0ea8f879…` establishes actual sign-OR raw64 model equality before finite native real negation. `RawMidpoint.lean.inc` 8937B / `85a54ce3…` proves masked raw32 fields→UInt64 fields, exact minimum-normal predicate, runtime OR-base = retained add-center, native negative endpoint swap, and a thin rational-rounder composition. Suggested two roots: `Submission.R24RawMidpoint.signed_endpoint_reals` / `roundRatScaled_of_endpoint_bounds`. Full hashes, dependency/runtime mapping: `raw-midpoint-source-receipt.json`; public pinned MIT/Apache source receipts: `raw-midpoint-public-sources.json`. All new public Lean/replay/AX **NOT_RUN**.

24 fixed normal raw32 words /48 endpoint equalities matched an independent exact-neighbor model, including both signs, power/minnormal/maxfinite. Ten excluded words were used only for field-adapter checks. No old broad model sweep or performance test was rerun. Remaining caller work is orderKey boolean→real strict comparison and radius/exact-sum enclosure composition, not native sign-word or field extraction (now complete proof-source drafts, untyped).

**Retained chain:** MidpointReal3879B /`96050a50…`; NormalCell10125B /`43958f8b…` (root static review READY); DyadicAgreement6876B /`ef4efc52…` plus DyadicCell1388B /`27dc56cb…`. These source snapshots remain byte-frozen and have no observed full public acceptance. New dependencies use WidenNormal4/`abe56775…`; historical MidpointReal receipt still binds its original Widen3 snapshot.

**Verified acceptance boundary:** exact core13 Kernel `049b01fa…`, run40793795026, statement/module replay/AX PASS; quotient2 fragment `5733f2e3…` is byte-exactly contained and both of its roots are audited. This does not accept quotient2's full B2 Kernel or any parent/new source. `../SOURCE-INDEX.json` binds the carrier, raw audit SHA and every current B source. Power-v4 `322eb784…` had no Power errors in failed island6; no whole-artifact PASS is inferred. Norm transport and old scalar runtime remain frozen sublines.

Next: real typed feedback before further changes, root's single critical review of new source, then D's minimum carrier decision. No new Kernel or CI queue was created by B. All originals, failures, source/model receipts and prior index snapshots are preserved.
''', encoding='utf-8')
    print(json.dumps({'source_count': len(indexed), 'core_component_bytes_exact': True,
                      'raw_audit_sha256': entry(audit)['sha256'], 'last_actual_utc': now.isoformat()}))

if __name__ == '__main__':
    main()
