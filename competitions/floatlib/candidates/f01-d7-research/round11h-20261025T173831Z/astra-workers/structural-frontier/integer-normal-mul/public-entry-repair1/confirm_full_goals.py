from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
mp=R/'competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/development-compiler-error-map-40307208739.json'
c=next(x for x in json.loads(mp.read_text())['candidates'] if x['candidate']=='f01-r17-dev-u64-public1')
raw=R/c['original_output']
assert hashlib.sha256(raw.read_bytes()).hexdigest()==c['original_output_sha256']
assert c['kernel_sha256']=='23adf0984bef02e611143cfc7e40d64d65c99caa0f4d11a0648812b2fb6f1e73'
fixed=H/'Kernel.lean';digest=hashlib.sha256(fixed.read_bytes()).hexdigest()
assert digest=='00ab99c7ff16a8f0f58c5a0b6ad5c87c10c2407589ee17c5f9cba444b7cfd080'
manifest=json.loads((H/'manifest.json').read_text())
expected={x['line']:x['new'] for x in manifest['changes']}
lines=fixed.read_text().splitlines();records=[]
for e in c['errors']:
 records.append(dict(line=e['line'],declaration=e['declaration'],
  explicit_ofNat_in_actual_goal='UInt32.ofNat' in e['message'],
  OfNat_literal_failed_pattern='(OfNat.ofNat ?m.' in e['message'],
  repair_line=lines[e['line']-1],matches_frozen_repair=lines[e['line']-1]==expected[e['line']]))
assert len(records)==3 and all(x['explicit_ofNat_in_actual_goal'] and x['OfNat_literal_failed_pattern'] and x['matches_frozen_repair'] for x in records)
record=dict(checked_utc=datetime.now(timezone.utc).isoformat(),
 state='EXACT_FULL_GOALS_CONFIRM_EXISTING00AB_DIRECTION_NO_NEW_SOURCE',diagnostic_run=40307208739,
 diagnosed_source_sha256=c['kernel_sha256'],repair_source_sha256=digest,
 raw_output_path=str(raw.relative_to(R)),raw_output_sha256=c['original_output_sha256'],
 error_map_sha256=hashlib.sha256(mp.read_bytes()).hexdigest(),matches=records,
 interpretation='All three actual targets retain explicit UInt32.ofNat; the fixed primed lemma matches them.00ab limited simplification retains the subsequent bound proofs. No new problem requiring an edit found.',
 repair_compilation='NOT_RUN; diagnostic run40307208739 checked original23ad, not00ab',
 next='D can use exact00ab for full gate/performance without waiting for unrelated ADD repair from this U64 proof check',
 new_version_created=False,source_modified=False,CI=False,Git=False,local_Lean=False)
(H/'full-goal-confirmation-40307208739.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
status=json.loads((H/'status.json').read_text())
status.update(updated_utc=record['checked_utc'],state='EXACT_GOALS_CONFIRM00AB_READY_FOR_D',
 compiler_goals_saved=True,full_goal_confirmation='full-goal-confirmation-40307208739.json',next=record['next'])
(H/'status.json').write_bytes((json.dumps(status,indent=2)+'\n').encode())
print(json.dumps(dict(state=record['state'],matched_goals=len(records),source_unchanged=True,diagnosed_source=c['kernel_sha256'])))
