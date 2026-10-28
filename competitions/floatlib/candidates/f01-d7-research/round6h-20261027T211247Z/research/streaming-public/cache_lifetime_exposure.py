"""Already-exposed R15 plans only; conditional source work, not a benchmark."""
from pathlib import Path
import json, hashlib
from datetime import datetime, timezone
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
meta_path = ROOT/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/matrix-architecture/analysis.json'
meta = json.loads(meta_path.read_bytes())
sha = lambda b: hashlib.sha256(b).hexdigest()
groups=[]
for group in meta['groups']:
    data={}
    for k,rec in group['evidence'].items():
        raw=(ROOT/rec['path']).read_bytes()
        assert sha(raw)==rec['sha256'], k
        data[k]=json.loads(raw)
    costs={k:data['work'][k]*v['submission_ns'] for k,v in data['verdict']['classes'].items()}
    total=sum(costs.values()); rows=[]
    for c in data['plan']['cases']:
        if c['kernel']!='bmm' or not c['timed']: continue
        b,m,n,p=(c[k] for k in ('batch','m','n','p'))
        if not (2<=p<=8 and n>1 and m>=4): continue
        G=(p+1)//2
        rows.append(dict(name=c['name'],batch=b,m=m,n=n,p=p,
            global_packet_slot_request_B=24*b*G*n,
            local_packet_slot_request_B=24*G*n,
            additional_outer_array_header_request_B=24*(b-1),
            unchanged_packet_records=b*G*n,
            unchanged_valid_B_conversions=b*n*p,
            unchanged_all_B_conversions=2*b*G*n,
            unchanged_output_finish=b*m*p))
    selected=[r for r in rows if r['batch']>1]
    cells={':'.join(r['name'].split(':')[:2]) for r in selected}
    groups.append(dict(run=group['run'],seed=group['seed'],B2_shapes=len(rows),
        multibatch_B2_shapes=len(selected),
        touched_class_whole_upper=sum(costs[k] for k in cells)/total,
        actual_lifetime_cost_share='UNKNOWN',actual_underflow_miss_frequency='UNKNOWN',
        max_global_packet_slot_request_B=max(r['global_packet_slot_request_B'] for r in rows),
        max_local_packet_slot_request_B=max(r['local_packet_slot_request_B'] for r in rows),
        additional_outer_array_header_request_B_one_plan=sum(r['additional_outer_array_header_request_B'] for r in rows),
        rows=rows,evidence=group['evidence']))
report=dict(at_utc=datetime.now(timezone.utc).isoformat(),
    input_scope='Previously exposed R15 discovery and old completed A/B; no R22 confirmation inputs.',
    original_bytes_rehashed=True,meta_sha256=sha(meta_path.read_bytes()),groups=groups,
    interpretation='Conditional packet+pointer-slot request model on fixed64bit scalar F2 representation. Excludes allocator classes, capacity, closures, inner headers, RC, output, and all elapsed-time inference. Header delta is only the extra outer array per batch. Total B decode/packet writes do not decrease. No candidate or native benchmark.')
(HERE/'cache-lifetime-exposure.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps([{k:g[k] for k in ['run','B2_shapes','multibatch_B2_shapes','touched_class_whole_upper','max_global_packet_slot_request_B','max_local_packet_slot_request_B','additional_outer_array_header_request_B_one_plan']} for g in groups]))
