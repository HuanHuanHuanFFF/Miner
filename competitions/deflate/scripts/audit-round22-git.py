"""Verify committed R22 raw/source/package bytes against the local delivery."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,subprocess
ROOT=Path(__file__).resolve().parents[1]

def main():
    head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT,text=True).strip()
    names=subprocess.check_output(['git','ls-tree','-r','--name-only',head],cwd=ROOT,text=True).splitlines()
    names=[n for n in names if (n.startswith(('evidence/round22/','candidates/r22-')) or n in ('references/round21-public-595/parse.rs','references/round21-public-595/Parse.lean')) and n!='evidence/round22/git-byte-audit.json']
    request=''.join(head+':'+n+'\n' for n in names).encode()
    raw=subprocess.check_output(['git','cat-file','--batch'],cwd=ROOT,input=request)
    pos=0;rows={}
    for name in names:
        end=raw.index(b'\n',pos);parts=raw[pos:end].split();assert parts[1]==b'blob';size=int(parts[2]);pos=end+1
        content=raw[pos:pos+size];pos+=size;assert raw[pos:pos+1]==b'\n';pos+=1
        assert content==(ROOT/name).read_bytes(), name
        rows[name]={'bytes':size,'sha256':hashlib.sha256(content).hexdigest()}
    assert pos==len(raw)
    result={'status':'VERIFIED_COMMITTED_R22_BYTES_MATCH_LOCAL','source_head':head,'checked_at_utc':datetime.now(timezone.utc).isoformat(),'files':rows,'file_count':len(rows),'bytes':sum(r['bytes'] for r in rows.values()),'scope':'All committed R22 evidence/candidate files and exact595 source reference at this immutable commit. This receipt excludes itself. Later closing metadata does not change frozen source or raw receipts.'}
    (ROOT/'evidence/round22/git-byte-audit.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({k:result[k] for k in ('status','source_head','file_count','bytes')}))

if __name__=='__main__':main()
