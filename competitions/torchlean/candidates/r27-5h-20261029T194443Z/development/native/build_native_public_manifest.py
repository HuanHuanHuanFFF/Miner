"""Own-scope final source/evidence inventory, no deletion or Git operation."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,ast
HERE=Path(__file__).resolve().parent
mutable={'READY.json','status.json','HANDOFF.md','NATIVE-PUBLIC-MANIFEST.json'}
rows=[];local=[];parse=[]
for p in sorted(HERE.rglob('*')):
 if not p.is_file():continue
 rel=p.relative_to(HERE).as_posix()
 if '__pycache__' in p.parts:continue
 raw=p.read_bytes();row={'path':rel,'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest()}
 if p.name=='Kernel.lean' or p.suffix in ['.zip','.c','.o','.dll','.exe'] or 'source-private' in p.parts:
  row['policy']='LOCAL_MATERIALIZED_OR_BULK_ARCHIVE_HASH_ONLY_NOT_PUBLIC_ALLOWLIST'
  local.append(row);continue
 if p.name in mutable:
  row['policy']='MUTABLE_ROLE_INDEX_SNAPSHOT_ONLY'
 else:row['policy']='OWN_RECIPE_FRAGMENT_METADATA_OR_RAW_DIAGNOSTIC'
 rows.append(row)
 if p.suffix=='.py':
  ast.parse(raw.decode('utf-8-sig'),filename=rel);parse.append(rel)
out={'at_utc':datetime.now(timezone.utc).isoformat(),'role_scope':str(HERE),
 'public_candidates':rows,'local_only_hash_receipts':local,'python_syntax_parsed_files':len(parse),
 'scope':'Inventory and Python syntax only; not Lean/native/full12/benchmark verification. No file deleted, moved or published',
 'selection':'Droot public whitelist owner must inspect sources/provenance. Whole materializedKernel and bulkduplicateZIP retained locally with hashes; own patches/helper proofs/receipts may be selected',
 'mutable_indices':'READY/status/HANDOFF snapshots maychange at final cutoff; source/receipt hashes bind this inventory time',
 'new_long_work':'Closed00:00; original deadline00:44:43 unchanged'}
(HERE/'NATIVE-PUBLIC-MANIFEST.json').write_bytes((json.dumps(out,indent=2)+'\n').encode())
print(json.dumps({'at_utc':out['at_utc'],'public_candidate_files':len(rows),'local_only_files':len(local),'python_files_parsed':len(parse),'public_candidate_bytes':sum(x['bytes'] for x in rows)}))
