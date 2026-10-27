from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
ROOT=Path(__file__).resolve().parents[4];HERE=Path(__file__).resolve().parent
p=ROOT/'competitions/floatlib/candidates/f01-r7-canonical-bridge-probe/Kernel.lean';b=p.read_bytes();assert hashlib.sha256(b).hexdigest()=='e7bdae87f9fa14cee018add947401eba9a2f1ae0f700d5b41ac955374b700a13'
s=b.decode();assert s.count('-1#_')==1 and s.count('0#_')==1
s=s.replace('-1#_','-1#8').replace('0#_','0#23');out=s.encode();d=ROOT/'competitions/floatlib/candidates/f01-r7-canonical-bridge-probe-policy1';d.mkdir(exist_ok=False);(d/'Kernel.lean').write_bytes(out)
m=json.loads(p.with_name('manifest.json').read_text());m.update(candidate=d.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=p.parent.name,parent_sha256=hashlib.sha256(b).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),proof_status='NOT_RUN_POLICY_SPELLING_REPAIR',repair='Originale7 static gate regex rejects inferred BitVec width literal #_. In actual fixed binary32 unpackExponent/unpackMantissa, give concrete widths8/23. Only two literal width spellings change; original full source retained. No Lean acceptance inherited.')
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
block=HERE/'canonical-native-block.lean';old=block.read_bytes();(HERE/'canonical-native-block.prepolicy.lean').write_bytes(old);block.write_text(old.decode().replace('-1#_','-1#8').replace('0#_','0#23'))
(HERE/'canonical-prepolicy-failure.json').write_text(json.dumps({'recorded_at_utc':datetime.now(timezone.utc).isoformat(),'candidate':p.parent.name,'sha256':hashlib.sha256(b).hexdigest(),'status':'STATIC_POLICY_FAIL_NOT_LEAN_RUN','token':'#_','replacement':d.name,'source_changes':'Only explicit widths8and23; original retained underold candidate name'},indent=2)+'\n');print(json.dumps(m,indent=2))
