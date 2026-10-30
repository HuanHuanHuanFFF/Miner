from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[1]
now=datetime.now(timezone.utc).isoformat()
parent_path=BASE/'CI-RESULTS-BATCH6.json';parent=json.loads(parent_path.read_text(encoding='utf-8'))
native=next(r for r in parent['results'] if r['candidate']=='public23-row-reciprocal-native-cost-v1')
helper=next(r for r in parent['helper_results'] if r['name']=='reciprocal_u64_v4')
assert helper['exit_code']==0 and helper['all_printed_axioms_allowed']
receipt={'at_utc':now,'run':40967910604,'source_commit':parent['source_commit'],
 'canonical_parent_receipt':'../../CI-RESULTS-BATCH6.json','canonical_parent_sha256':hashlib.sha256(parent_path.read_bytes()).hexdigest(),
 'native':{'source_sha256':native['candidate_sha256'],'current_champion':43,
 'time_over_current_estimate':native['candidate_time_over_current_champion_estimate'],
 'comparison':'INFERRED current43 report-chain screen, not directcurrent source or eligibility',
 'paired_rows':sum(r['paired_rows'] for r in native['counts']),
 'ns_values':sum(r['ns_values'] for r in native['counts']),
 'checksum_pairs':sum(r['checksum_pairs'] for r in native['counts']),
 'proof':'NO_NEW_CORRECT_NATIVE_ONLY','decision':'STOP_PRIMARY_RECIPROCAL_PROOF_AND_PERFORMANCE_BUDGET'},
 'helper':helper,'actual_all12_gate':parent['full_gates'],
 'archive_repair':'reciprocal23-archive-parse-v4-receipt.json:253674B/21bbffda; only application whitespace, NOT_COMPILED/NOT_QUEUED',
 'diagnostic':'Profile failed missingstdio.h; no kernel-share or hardware-cause claim',
 'next':'Exact prepared-block16 v2 frozen by D inbatch8, alongside FP-only lazy; no block endpoint proof before native cost'}
(HERE/'batch6-native-result.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
candidate={'name':'public23-prepared-block16-unrolled-native-cost-v2','sha256':'14ab9f4fcd9e05a25bf8fdd30248eb3044742a2671661ef53ab552ec301beebc','bytes':252115,'actual_correct':False,'state':'FROZEN_PARENT_BATCH8_NATIVE_ONLY_NOT_YET_MEASURED'}
ready={'updated_at_utc':now,'first_clock_utc':'2026-10-29T19:46:53Z','deadline_utc':'2026-10-30T00:44:43Z',
 'role':'Dnative','communication':'STRICT_FILES_ONLY','git_ci_owner':'Droot',
 'preferred':'CI-REQUEST-15-PREPARED-BLOCK16-COST.json','candidate':candidate,
 'native_reciprocal_result':'batch6-native-result.json;1.1297896864x current43 INFERRED/insufficient; STOP further queue',
 'accepted_standalone':'ReciprocalUInt64ContractOnly-v4.lean/013a5fd2 four roots accepted40967910604, allowed printed AX only; not all12',
 'actual_reciprocal_all12':'9654b727 statement FAIL: helper application whitespace parse, unknownlemma/rewrite cascades; not math counterexample',
 'archive_only':'public23_reciprocal_archive_v4.py ->21bbffda/253674B, policy PASS, NOT_COMPILED/NOT_QUEUED',
 'dormant_composition':'a07324ab/254997B RMS+old reciprocal contains failed old compaction; no new queue or combined gain claim',
 'processed_parent':'BATCH6-NEGATIVE-TO-DENSE8.json/22:55; fixed deadline unchanged despite separate R continuation relay',
 'resources':{'tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN','model_cpu':'UNKNOWN','local_Lean_native_builds':0},
 'publication':'Only own snippets/recipes/receipts, full source private/ephemeral'}
(HERE/'READY.json').write_text(json.dumps(ready,indent=2)+'\n',encoding='utf-8')
status=dict(ready);status.update(active=True,state='WORD_BLOCK16_FROZEN_AWAIT_NATIVE_COST_NO_NEW_ENDPOINT_PROOF')
(HERE/'status.json').write_text(json.dumps(status,indent=2)+'\n',encoding='utf-8')
handoff=f'''# R27 native current handoff

{now}. Join19:46:53, common cutoff00:44:43 unchanged; no new long work00:00. Droot only Git/CI, native-only writes, STRICT_FILES_ONLY. No local Lean/native, formal submission/funds/reset; tokens/cache/CPU UNKNOWN. Separate R continuation does not extend this role.

- **Current route frozen:** request15, `public23_block16_cost_v2.py`/6526074a → **252115B/14ab9f4f…1beebc**, policyPASS, NativeOnly/no actual correct. Parentbatch8 freezes exact helper/recipe beside FP-only4950ac8f. Rows1 prepared dots reuse existing P/I+BX/BV; span<=11, fixed16 sum, one carry merge perblock. Other paths, sparse pruning, bias/finalizer preserved. No endpoint proof investment before actual cost.
- **Actual reciprocal native negative:** batch6/40967910604 c688f107 complete360pairs/720ns/checksums matched; current43 report-chain time **1.1297896864x INFERRED**, insufficient. Stop further reciprocal performance/integration-proof queue. Cause UNKNOWN; profiler failed missingstdio.h. Original bytes/logs retained in canonical CI-RESULTS-BATCH6, own subset `batch6-native-result.json`.
- **Verified reusable standalone proof:** v4 `ReciprocalUInt64ContractOnly-v4.lean`12500B/013a5fd2 four roots exit0, printed AX allowed; original log36517f2f…. This is helper acceptance only. Full9654b727 all12 **statement FAIL**, parser/application spacing in compact helper; unknownR27D.v and q/r rewrites cascade. No accepted new kernel.
- **Cheap archive repair only:** `public23_reciprocal_archive_v4.py`→253674B/21bbffda, policyPASS; restore application/binder spacing only. NOT_COMPILED/NOT_QUEUED; no extra gate or performance request. Olda07324ab RMS composition is dormant and contains failed old compaction.
- **Word proof boundary:**228 finite cases/79308 terms pass; span12 negative control detected. See BLOCK16-PREPARED-INTERFACE.md and BLOCK16-PROOF-SIZE-ROUTE.md. ExistingD8/Qsx/E2/C9/C8/I9 provide a smaller actual carrier interface; B generic UInt32-factor block theorem is not inherited for35bit prepared coefficients.

Next: collect original batch8 complete native cost/checksums and actual profile. Only useful wholemodel cost justifies actual block/proof connection. Freeze isolates follow-up inputs; no old source12+27 graft, no originalshipped new performance comparison, no gains added across routes. Whole unknown-license source stays private/ephemeral.
'''
(HERE/'HANDOFF.md').write_text(handoff,encoding='utf-8')
print(json.dumps({'updated_at_utc':now,'preferred':candidate,'reciprocal_current43_estimate':native['candidate_time_over_current_champion_estimate'],'standalone_helper':'PASS_FOUR_ROOTS_ONLY'}))
