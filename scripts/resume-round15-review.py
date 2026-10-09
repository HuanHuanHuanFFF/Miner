"""Resume the pinned read-only capture without replacing failed/raw responses."""
from pathlib import Path
from datetime import datetime, timezone
from urllib.parse import urlparse, parse_qs
import hashlib, json, time, requests

ROOT = Path(__file__).resolve().parents[1]
DEST = ROOT / 'evidence/round15/official-review'
BASE = 'https://conjectures.io/v1/competitions/deflate'

def now(): return datetime.now(timezone.utc).isoformat()
def save(p,x): p.write_bytes((json.dumps(x,indent=2)+'\n').encode())
def read(p): return json.loads(p.read_bytes())

def main():
    assert not (DEST/'receipt.json').exists(), 'Already complete; no repeated capture'
    failure = read(DEST/'capture-failure.json')
    progress = DEST/'resume-progress.json'
    records = read(progress)['raw_response_files'] if progress.exists() else failure['raw_response_files']
    for r in records:
        raw=(DEST/r['file']).read_bytes()
        assert len(raw)==r['bytes'] and hashlib.sha256(raw).hexdigest()==r['sha256']
    session=requests.Session()
    def get(endpoint,label,params=None):
        wanted={k:[str(v)] for k,v in (params or {}).items()}
        for r in records:
            u=urlparse(r['url'])
            if r['http_status']==200 and u.scheme+'://'+u.netloc+u.path==BASE+endpoint and parse_qs(u.query)==wanted:
                return read(DEST/r['file'])
        # Each successful new request is spaced; a 429 stops immediately and
        # preserves Retry-After for the caller rather than evading the limit.
        time.sleep(2)
        start=now(); response=session.get(BASE+endpoint,params=params,timeout=35); raw=response.content
        i=1
        while (DEST/f'{label}.resume{i:02d}.response.json').exists(): i+=1
        filename=f'{label}.resume{i:02d}.response.json';(DEST/filename).write_bytes(raw)
        records.append({'file':filename,'url':response.url,'request_start_utc':start,'request_end_utc':now(),'http_status':response.status_code,'response_date_header':response.headers.get('Date'),'retry_after':response.headers.get('Retry-After'),'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest()})
        save(progress,{'status':'RESUME_IN_PROGRESS','raw_response_files':records})
        if response.status_code==429:
            raise RuntimeError('Rate limited; Retry-After='+str(response.headers.get('Retry-After'))+'; response preserved, no immediate retry')
        response.raise_for_status();return response.json()
    try:
        comp=get('','competition');snapshot=comp['current_snapshot_id'];derived={'competition.json':comp};pagination={}
        for endpoint,key,identity in [('pareto','items','id'),('leaderboard','ranking','hotkey')]:
            pages=[];cursor=None;seen=set()
            for n in range(1,21):
                params={'limit':100,'snapshot_id':snapshot}
                if cursor:params['cursor']=cursor
                page=get('/'+endpoint,f'{endpoint}-page-{n:03d}',params)
                assert str(page['context']['snapshot_id'])==str(snapshot)
                pages.append(page);cursor=page.get('next_cursor')
                if not cursor:break
                assert cursor not in seen;seen.add(cursor)
            else:raise RuntimeError('Bounded pagination exceeded')
            rows=[r for p in pages for r in p[key]];assert len(rows)==len({r[identity]for r in rows})
            derived[endpoint+'-pages.json']=pages;pagination[endpoint]={'pages':len(pages),'rows':len(rows),'terminal_next_cursor':cursor}
        weights=get('/weights/current','weights-current');derived['weights-current.json']=weights;files={}
        for name,value in derived.items():
            raw=(json.dumps(value,indent=2)+'\n').encode();p=DEST/name
            assert not p.exists() or p.read_bytes()==raw
            p.write_bytes(raw);files[name]={'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest()}
        receipt={'status':'VERIFIED_OFFICIAL_READ_ONLY_API_CAPTURE_RECOVERED','source_url':BASE,'snapshot_id':snapshot,'retrieval_start_utc':failure['started_utc'],'retrieval_end_utc':now(),'competition_context':comp['context'],'policy':comp['policy'],'pagination':pagination,'raw_response_files':records,'derived_files':files,'weights_context':weights.get('context'),'weights_same_snapshot':str(weights.get('context',{}).get('snapshot_id'))==str(snapshot),'prior_failure_preserved':'capture-failure.json','scope':'Pinned originalsnapshot recovered after rate-limit backoff; successful cached pages reused and429bytes retained. weights/current separately timed; freshness never upgraded.'}
        save(DEST/'receipt.json',receipt);save(progress,{'status':'RESUME_COMPLETED','raw_response_files':records})
        print(json.dumps({'snapshot_id':snapshot,'context':comp['context'],'pagination':pagination,'weights_same_snapshot':receipt['weights_same_snapshot']}))
    finally:session.close()

if __name__=='__main__':main()
