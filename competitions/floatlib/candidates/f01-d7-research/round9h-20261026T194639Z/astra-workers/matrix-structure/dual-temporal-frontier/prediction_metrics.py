"""Derive break-even event ratios from the already-frozen cost screen; no new input/data generation."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
H=Path(__file__).resolve().parent
cost=H/'cost-screen.json';old=json.loads(cost.read_bytes())
source=H/'proof2/Kernel-dual-temporal-a4-proof2.lean'
digest=hashlib.sha256(source.read_bytes()).hexdigest()
assert digest=='d765bd41234a26640eaa6df6c7134e0d4d8dca760e50eaef3aa82eff1fac0847'
rows=[]
for g in old['groups']:
 s=g['source_counts'];R=s['new_A_packet_records'];N=s['new_valid_A_ofbits']
 rows.append({'seed':g['seed'],'run':g['run'],'removed_hot_A_conversions_per_added_A4_record':s['removed_A_ofbits']/R,
  'padding_fraction_of_new_A4_scalar_fields':s['new_A_padding_fields']/(4*R),
  'new_A_record_and_slot_requested_bytes_per_valid_A_scalar':(32*R)/N,
  'new_A_major_requested_bytes_across_plan':s['new_A_global_major_request_bytes'],
  'max_A_cache_requested_bytes_one_call':g['max_new_A_live_major_bytes'],
  'complete_touched_cell_whole_time_upper':g['selected_cell_whole_upper'],'actual_target_time':'UNKNOWN'})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':digest,'source_state':'PROOF2_NOT_RUN; no new compiler output discovered as of phase start','frozen_input_cost_file_sha256':hashlib.sha256(cost.read_bytes()).hexdigest(),'rows':rows,
 'equation':'Net new complete cost = new A prepare + new A release + change in native dot + change in cache/layout/control costs; B prepare and output/replay remain. Event-count reduction alone does not price these terms.',
 'generic_bounds':{'G':'ceil(p/2),2..4 in selected p3..8','T':'ceil(n/4)','removed_conversions_per_added_record':'(G-1)*n/T, between2 and12 for n>1','additional_A_requests':'32*batch*m*T+24, excludes closures, capacity slack and allocator classes'},
 'scope':'Prospective conditional source model only; all plans completed before original9a5 runtime freeze. No performance forecast, new benchmark, source mutation or historical verification rewrite.'}
(H/'callpath-prediction.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out))
