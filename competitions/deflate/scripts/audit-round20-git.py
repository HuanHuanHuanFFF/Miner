"""Verify immutable/frozen R20 local bytes against one committed Git tree."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,subprocess
ROOT=Path(__file__).resolve().parents[1]
def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--commit',default='HEAD');ap.add_argument('--output',type=Path,required=True);a=ap.parse_args()
    commit=subprocess.check_output(['git','rev-parse',a.commit],cwd=ROOT,text=True).strip();output=a.output.resolve()
    paths=[p for p in (ROOT/'evidence/round20').rglob('*')if p.is_file()and p.resolve()!=output]
    for folder in list((ROOT/'candidates').glob('r20-*'))+[ROOT/'references/round20-public-535',ROOT/'references/round20-public-599']:
        paths.extend(folder/f for f in ['parse.rs','Parse.lean'])
    paths=sorted(set(paths));names=[p.relative_to(ROOT).as_posix()for p in paths]
    proc=subprocess.run(['git','cat-file','--batch'],cwd=ROOT,input=''.join(commit+':'+n+'\n'for n in names).encode(),capture_output=True,check=True);raw=proc.stdout;offset=0;size=0;fail=[]
    for path,name in zip(paths,names):
        end=raw.index(b'\n',offset);header=raw[offset:end].split();assert len(header)==3 and header[1]==b'blob',(name,header)
        n=int(header[2]);stored=raw[end+1:end+1+n];local=path.read_bytes();size+=len(local)
        if stored!=local:fail.append(name)
        offset=end+1+n+1
    assert offset==len(raw)and not fail,fail
    result={'status':'VERIFIED_LOCAL_BYTES_EQUAL_COMMITTED_TREE','checked_at_utc':datetime.now(timezone.utc).isoformat(),'data_commit':commit,'files':len(paths),'bytes':size,'mismatches':fail,'scope':'All R20 evidence files present before this receipt, all new candidate Rust/Lean and two public reference pairs. This audit receipt is excluded to avoid recursive self-hashing. Source/receipt identities are also checked by audit-round20.py.'}
    output.write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))
if __name__=='__main__':main()
