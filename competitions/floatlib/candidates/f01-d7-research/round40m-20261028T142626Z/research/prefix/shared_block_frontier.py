"""Read-only old-discovery cost bound; no new benchmark or input generation."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

here=Path(__file__).resolve().parent
source=here.parent/'producer/cost-frontier.json'
raw=source.read_bytes()
d=json.loads(raw)
rows=[]
for seed in [2220001,2220003]:
    for block in [0,1]:
        rs=[r for r in d['all_bmm_rows'] if r['seed']==seed and r['block']==block]
        g=next(r for r in d['groups'] if r['seed']==seed and r['block']==block)
        whole=g['control_ns']/g['control_share_of_whole']
        bmm=sum(r['control_ns'] for r in rs)/whole
        batch4=sum(r['control_ns'] for r in rs if r['shape'][0]>=4)/whole
        rows.append(dict(seed=seed,block=block,whole_ns=whole,bmm_share=bmm,
            batch4_share=batch4,bmm_speedup_for_10pct=bmm/(bmm-.1),
            batch4_speedup_for_10pct=batch4/(batch4-.1),
            n_le_2_entire_case_share=sum(r['control_ns'] for r in rs if r['shape'][2]<=2)/whole,
            n_ge_4_entire_case_share=sum(r['control_ns'] for r in rs if r['shape'][2]>=4)/whole,
            n_ge_4_bypass_entire_case_share=sum(r['control_ns'] for r in rs if r['shape'][2]>=4 and r['category']=='shape_bypass')/whole))
receipt=dict(checked_utc=datetime.now(timezone.utc).isoformat(),source=str(source),
    source_sha256=hashlib.sha256(raw).hexdigest(),
    script_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    source_cost_basis='Historical R22 exact8e27, run40611570030, two already-seen seeds/four paired blocks. Producer cost-frontier preserves raw source hashes.',
    scope='Entire-case touch ceilings only. No data guard hit reconstruction, per-stage costs, new timing, confirmation or current private-suite claim.',
    rows=rows,decision='PARK_CURRENT_PUBLIC_10PCT_MAIN_ROUTE_BEFORE_CANDIDATE')
(here/'shared-block-frontier.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,indent=2))
