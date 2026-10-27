"""Replay saved CI10 failure seam; no Lean, Git, CI or v1 mutation."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,sys

H=Path(__file__).resolve().parent
R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40425497337'
ixp=run/'original-artifact-hashes.json';ix=json.loads(ixp.read_text());down=run/ix['directory']
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
for name,row in ix['files'].items():
    p=down/name;assert p.stat().st_size==row['bytes']and sha(p)==row['sha256'],name
assert set(ix['files'])=={p.relative_to(down).as_posix()for p in down.rglob('*')if p.is_file()}
d=down/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-route-profile1'
data=d/'route-profile';progress=json.loads((data/'partial-progress.json').read_text())
error=json.loads((data/'error.json').read_text());audit=json.loads((d/'route-audit.json').read_text())
lines=(d/'replay.log').read_text().splitlines();causal=[dict(line=i+1,text=s)for i,s in enumerate(lines)if'lake env lean exit='in s or'lake timed out'in s or'taskset -c 0 exit='in s]
first=(data/'labels-1927003.log').read_text();second=(data/'labels-1927005.log').read_text()
assert len([s for s in first.splitlines()if s.startswith('ROUTE19 ')])==35
assert not second.strip()
assert any('lake env lean exit=0 in 30.0s'in r['text']for r in causal)
assert any('lake timed out after 22s'in r['text']for r in causal)
assert progress['current']['stage']=='labels-1927005-returned'and progress['current']['exit_code']==124
assert progress['current']['elapsed_seconds']>=60 and audit['requested_cap_seconds']==audit['effective_cap_seconds']==60
assert [p['seed']for p in error['partial_results']]==[1927003]
assert len(error['partial_results'][0]['complete_case_rows'])==2
assert audit['collection_complete']is False and error['error']=='metadata failed'
req=json.loads((data/'request.json').read_text())
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='VERIFIED_SECOND_METADATA_TIMEOUT_NOT_FIRST_MAIN_EXIT_FAILURE',
            run=40425497337,original_index_sha256=sha(ixp),original_files_verified=len(ix['files']),
            first_metadata=dict(seed=1927003,actual_g_own_exit=0,seconds=30.0,labels=35,two_original_binary_processes_exit=0),
            failed_metadata=dict(seed=1927005,actual_g_own_exit=124,logged_timeout_seconds=22,stdout_bytes=(data/'labels-1927005.log').stat().st_size,
                                 total_module_elapsed=progress['current']['elapsed_seconds']),
            causal_log=causal,module_cap_seconds=60,inner_process_age_at_start=audit['inner_process_age_seconds'],
            memory_evidence='No OOM/137 evidence in retained route logs; immediate failure is explicit timeout124. Metadata-specific RSS unavailable.',
            type_evidence='Same compiled metadata program completed first plan with exit0 and35 labels; no type/main-return error is recorded',
            cause='First plan metadata30s plus original timers2.5/4.6s left about22s; second metadata hit remaining60s deadline. Generic error hid the seed/exit.',
            cost_mechanism='v1 metadata eagerly materializes every A/B vector before all-small, about6.03M source elements over two plans; time by substage is not measured',
            unchanged_constraints=dict(cap=60,inner_timeout=120,nested_statement=180,plans=[1927003,1927005],BENCH_INNER=3,BENCH_PAIRS=500000),
            proposed_minimal_fix='v2 metadata computes exact same all-small predicates lazily from original element/float, stopping at first false; timer binary/inputs/flags unchanged; keep strict exit0',
            bindings=[dict(path=p.relative_to(R).as_posix(),sha256=sha(p))for p in(d/'replay.log',d/'route-audit.json',data/'error.json',data/'partial-progress.json',data/'labels-1927003.log',data/'labels-1927005.log',data/'RouteLabels.lean',data/'driver-source.py')])
(H/'cause.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps({k:record[k]for k in('state','first_metadata','failed_metadata','cause')},indent=2))
if '--assert-complete'in sys.argv:
    assert audit['collection_complete'],'RED trace: actual CI10 route collection is incomplete at second metadata exit124'
