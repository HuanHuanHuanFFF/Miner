"""Bounded read of explicitly selected, currently dominated public source references."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,requests
ROOT=Path(__file__).resolve().parents[1]
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--capture',type=Path,required=True);ap.add_argument('--destination',type=Path,required=True);ap.add_argument('ids',nargs='+');a=ap.parse_args()
    assert 1<=len(a.ids)<=5 and all(x.isdigit() for x in a.ids) and len(a.ids)==len(set(a.ids))
    dest=a.destination.resolve();assert dest.is_relative_to((ROOT/'evidence/round24').resolve());dest.mkdir(exist_ok=False)
    pages=json.loads((a.capture/'pareto-pages.json').read_bytes());rows={str(r['id']):r for p in pages for r in p['items']};snapshot=pages[0]['context']['snapshot_id']
    session=requests.Session();records=[]
    try:
        for id in a.ids:
            row=rows[id]
            if (row.get('score')or{}).get('on_frontier'):
                records.append({'id':id,'status':'NOT_REQUESTED_CURRENT_FRONTIER','snapshot_id':snapshot});continue
            url=f'https://conjectures.io/v1/competitions/deflate/submissions/{id}/source';start=datetime.now(timezone.utc).isoformat();r=session.get(url,timeout=35);(dest/f'{id}.response.json').write_bytes(r.content)
            rec={'id':id,'url':url,'snapshot_id':snapshot,'request_start_utc':start,'request_end_utc':datetime.now(timezone.utc).isoformat(),'http_status':r.status_code,'bytes':len(r.content),'sha256':hashlib.sha256(r.content).hexdigest(),'author_hotkey':row.get('hotkey'),'metrics':row.get('metrics')}
            records.append(rec)
            if r.status_code!=200:continue
            x=r.json();assert str(x['id'])==id;ref=ROOT/f'references/round24-public-{id}';ref.mkdir(exist_ok=False);rec['files']={}
            for name,key in [('parse.rs','parse_rs'),('Parse.lean','proof_lean')]:
                raw=x[key].encode();assert 0<len(raw)<=524288;(ref/name).write_bytes(raw);rec['files'][name]={'sha256':hashlib.sha256(raw).hexdigest(),'bytes':len(raw)}
            (ref/'source-receipt.json').write_bytes((json.dumps(rec,indent=2)+'\n').encode())
    finally:
        (dest/'receipt.json').write_bytes((json.dumps(records,indent=2)+'\n').encode());session.close()
    print(json.dumps([{'id':r['id'],'status':r.get('http_status',r.get('status')),'files':r.get('files')} for r in records],indent=2))
if __name__=='__main__':main()
