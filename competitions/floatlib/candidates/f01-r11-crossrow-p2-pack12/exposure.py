"""Read only already-executed discovery inputs; no final confirmation data."""
from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[3]
source=ROOT/'competitions/floatlib/candidates/f01-d7-research/bmm-literature-20261024/opportunity.json'
inventory=json.loads(source.read_text())
def read_entry(i):
    e=inventory['inputs'][i];p=ROOT/e['path'];b=p.read_bytes()
    assert hashlib.sha256(b).hexdigest()==e['sha256']
    return json.loads(b)
plan=read_entry(2);timings=read_entry(3)
cases=[]
for c in plan['cases']:
    if c['kernel']!='bmm' or not c['timed'] or c['p']!=2 or c['batch']*c['m']<4 or c['n']==0:continue
    b,m,n,p=(c[k] for k in ['batch','m','n','p']);rows=b*m;groups=(rows+3)//4
    shared=sum(len({(4*g+i)//m for i in range(4)})==1 for g in range(groups))
    # Source-level conversion calls, excluding exact finishing/replay and output.
    # Original direct route decodes A and B for each of 2*rows*n MACs.
    original_decodes=4*rows*n
    packet_decodes=(6*shared+12*(groups-shared))*n
    cases.append({'name':c['name'],'shape':[b,m,n,p],'control_best_ns':timings[c['name']]['best_ns'],
                  'groups':groups,'shared_b_groups':shared,'cross_batch_groups':groups-shared,
                  'extra_tail_rows':4*groups-rows,'source_direct_decodes':original_decodes,
                  'source_packet_decodes':packet_decodes,'source_decode_ratio':packet_decodes/original_decodes,
                  'new_packet_objects':groups*n,'new_word8_objects':groups,
                  'extra_tail_macs':2*(4*groups-rows)*n})
total=inventory['bmm_control_best_ns_sum']
report={'status':'HISTORICAL_EXPOSURE_AND_SOURCE_COUNTS_ONLY','at_utc':datetime.now(timezone.utc).isoformat(),
        'seed':852,'run':40005234741,'sources':inventory['inputs'][2:4],
        'kernel_sha256':hashlib.sha256((HERE/'Kernel.lean').read_bytes()).hexdigest(),
        'case_count':len(cases),'control_best_ns_sum':sum(c['control_best_ns'] for c in cases),
        'fraction_bmm_old_control':sum(c['control_best_ns'] for c in cases)/total,'cases':cases,
        'scope':'Old control per-case best times, not official weights/predicted savings. Decode and object counts are source-level logical operations; optimization/inlining/RC/codegen can change actual work. Full packing, output, tail, finish and deallocation costs remain unknown.'}
(HERE/'exposure.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:report[k] for k in ['status','case_count','fraction_bmm_old_control']}))
for c in cases:print(json.dumps(c))
