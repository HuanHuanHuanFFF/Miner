"""Exact already-completed R15 plans: conditional source request counts, not timings."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,time
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic();sha=lambda b:hashlib.sha256(b).hexdigest()
old=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/matrix-architecture/analysis.json'
meta=json.loads(old.read_bytes());groups=[]
for group in meta['groups']:
 files={k:R/v['path'] for k,v in group['evidence'].items()}
 for k,f in files.items():assert sha(f.read_bytes())==group['evidence'][k]['sha256']
 plan,work,verdict=(json.loads(files[k].read_bytes()) for k in ('plan','work','verdict'))
 costs={k:work[k]*v['submission_ns'] for k,v in verdict['classes'].items()};whole=sum(costs.values())
 rows=[]
 for c in plan['cases']:
  if c['kernel']!='bmm' or not c['timed']:continue
  batch,m,n,p=(c[k] for k in ('batch','m','n','p'))
  if not(2<=p<=8 and n>1 and m>=4):continue
  G=(p+1)//2;T=(n+3)//4;tiles=batch*G
  rows.append({'name':c['name'],'shape':{k:c[k] for k in ('batch','m','n','p','work')},'old_packet_records':tiles*n,'new_packet_records':tiles*T,'old_packet_and_slot_request_bytes':tiles*24*n,'new_packet_and_slot_request_bytes':tiles*48*T,'unchanged_valid_B_decodes':tiles*2*n,'new_padded_fields_written':tiles*(8*T-2*n),'old_numeric_k_steps':batch*m*G*n,'new_numeric_packet_reads':batch*m*G*T,'unchanged_terminal_F2_count':batch*m*G,'unchanged_output_finish_count':batch*m*p,'n2_no_major_byte_reduction':n==2})
 cells={':'.join(row['name'].split(':')[:2]) for row in rows}
 sums={k:sum(row[k] for row in rows) for k in ('old_packet_records','new_packet_records','old_packet_and_slot_request_bytes','new_packet_and_slot_request_bytes','unchanged_valid_B_decodes','new_padded_fields_written','old_numeric_k_steps','new_numeric_packet_reads','unchanged_terminal_F2_count','unchanged_output_finish_count')}
 groups.append({'run':group['run'],'seed':group['seed'],'selected_shapes':len(rows),'selected_n2_shapes':sum(r['n2_no_major_byte_reduction'] for r in rows),'source_counts':sums,'same_source_BMM_whole_share':sum(v for k,v in costs.items() if k.startswith('bmm:'))/whole,'selected_cell_whole_upper':sum(costs[k] for k in cells)/whole,'actual_target_time':'UNKNOWN','actual_underflow_miss_frequency':'UNKNOWN','cases':rows})
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha((H/'Kernel-temporal-b2.lean').read_bytes()),'source_metadata_sha256':sha(old.read_bytes()),'groups':groups,'interpretation':'Conditional source request count for one complete plan evaluation, assuming every shape selection misses the underflow fastpath. Excludes closures, Array capacity slack, allocator classes, RC, Nat costs and all elapsed-time inference. Old source/request counts are exact formulas; new C representation still needs observation. All referenced groups are completed exposed historical data, not R19 holdouts.','elapsed_seconds':time.monotonic()-start}
(H/'cost-snapshot.json').write_text(json.dumps(receipt,indent=2)+'\n')
print(json.dumps([{k:g[k] for k in ('run','seed','selected_shapes','selected_n2_shapes','source_counts','same_source_BMM_whole_share','selected_cell_whole_upper')} for g in groups]))
