from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
ROOT=Path(__file__).resolve().parents[4]
for name,old,new in [
 ('f01-r6-active-bias','namespace Submission\n\nnamespace R6Domain','namespace Submission\n\nopen FloatLib.Floats Competition\n\nnamespace R6Domain'),
 ('f01-r6-web-absorption26','end Submission.Absorption26\n\nnamespace Submission','end Submission.Absorption26\n\nnamespace Submission\n\nopen FloatLib.Floats Competition')]:
    d=ROOT/'competitions/floatlib/candidates'/name
    b=(d/'Kernel.lean').read_bytes();s=b.decode();assert s.count(old)==1,(name,s.count(old))
    out=s.replace(old,new).encode();dest=d.with_name(name+'-proof1');dest.mkdir(exist_ok=True)
    (dest/'Kernel.lean').write_bytes(out)
    m=json.loads((d/'manifest.json').read_text());m.update(candidate=dest.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=name,parent_sha256=hashlib.sha256(b).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),proof_status='NOT_RUN',repair='Proactive integration scope audit after705 namespace failure: restore open FloatLib.Floats Competition after closing/reopening Submission for the global web proof fragment. Runtime expressions unchanged. Previous original retained; this exact version needs full gate.')
    (dest/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
