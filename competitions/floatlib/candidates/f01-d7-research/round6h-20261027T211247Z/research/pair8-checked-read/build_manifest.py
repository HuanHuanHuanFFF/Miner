from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
files=['CheckedRead.lean.inc','INTERFACE.md','selected-read-receipt.json','selected-map.c.txt','selected-map.asm.txt']
out={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'OLD_BOUND_CHECK_PRESENT_NEW_PROOF_INTERFACE_NOT_RUN',
 'start_utc':'2026-10-27T22:53:15Z','bound_utc':'2026-10-27T23:08:15Z','shared_deadline_utc':'2026-10-28T03:12:47Z',
 'runtime_sha256':'cd0e33994753172e5a6d3521772a68499cfaa656092a6fae72543fcbd6d4feb5',
 'cache_proof_sha256':'2850a16cbce661e5ec242a8d24ac08e7fe6e8bb4556399974ef586d7411d93a5',
 'files':{f:{'bytes':(HERE/f).stat().st_size,'sha256':sha(HERE/f)} for f in files},
 'roots':['Submission.R22Pair8CheckedRead.'+n for n in ['cache_index_lt','read_eq_getD','advance_map_eq','pack_span']],
 'new_Lean':'NOT_RUN','new_candidate':False,'new_guard':False,'CI':False,'local_Lean':False,
 'deletion_premise':'The currentselectedloop retainscachebound/default check. Prop bounds can expressitsinternalinvariant; realnewC andcompletecost stillrequired.',
 'new_performance':'UNKNOWN'}
assert (HERE/'CheckedRead.lean.inc').stat().st_size<=2000
(HERE/'manifest.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='files'},indent=2))
