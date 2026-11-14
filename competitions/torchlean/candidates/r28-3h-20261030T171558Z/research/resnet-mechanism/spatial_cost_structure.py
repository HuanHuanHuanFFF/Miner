#!/usr/bin/env python3
"""Counts source-level work for the exact generated spatial prototype.
Not CPU instructions, cycle estimates, native timing or a second candidate.
"""
from pathlib import Path
import hashlib,json
P=Path(__file__).resolve().parent
def main():
 source=P/'spatial-runtime-model-receipt.json';d=json.loads(source.read_text())
 rows=[]
 for r in d['records']:
  ci,h,w,co=r['shape'];hw=h*w;tiles=(h//2)*(w//2);pairs=(co+1)//2
  oldmul=18*ci*co*hw;newmul=32*ci*co*tiles
  oldloops=(ci+1)*pairs*hw;newsteps=16*(ci+1)*co*tiles
  oldreads=9*ci*(pairs+co)*hw
  newreads=32*ci*co*tiles+16*ci*tiles+9*ci*co+32*co*tiles
  rows.append({'shape':r['shape'],'base_split_products':oldmul,'spatial_split_products':newmul,'product_reduction_fraction':1-newmul/oldmul,'base_unrolled_loop_body_visits':oldloops,'R8D_nonterminal_fuel_steps':newsteps,'fuel_step_ratio':newsteps/oldloops,'base_core_array_reads':oldreads,'spatial_core_plus_transform_and_partial_reads':newreads,'transformed_weight_payload_bytes':16*ci*co*8,'one_tile_input_payload_bytes':16*ci*8,'per_output_tile_partial_payload_bytes':32*8,'partial_array_objects_per_call':2*co*tiles,'R8D_result_pair_objects_before_compiler_optimization':co*tiles,'context_objects':co,'context_object_bytes':'UNKNOWN','output_init_and_set_count_each':co*hw})
 result={'state':'SOURCE_STRUCTURE_COST_DIAGNOSTIC_NOT_NATIVE','source_sha256':d['source_sha256'],'model_receipt_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'rows':rows,'key_risk':'R8D processes one transform coordinate per channel step:6.67–8times as many nonterminal recursive fuel steps as the old9-term unrolled paired-channel loop on the observed shapes. New getElem! uses Nat indexes; original core uses proof-backed USize uget. Product reduction alone is not a latency prediction.','count_scope':'Shared oldP2/W2 prep is retained and not counted again here. Array-read columns cover the main arithmetic/new transforms/partial reads, excluding some guards,bias contexts and finalizer raw replay. Counts describe source operations, not optimized machine loads or instructions.','future_discriminator':'If measured cost is poor, inspect actual R8D/R8I/R8W/R8O generated C and allocations first. Unroll4/16 coordinates or proof-backed getters are follow-on alternatives, not already implemented benefits. Do not spend full proof budget or add variants before the scheduled cost decision.','not_claimed':['native performance','whole-model speedup','all12 acceptance'],'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
 (P/'spatial-cost-structure.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
 print(json.dumps({'source':d['source_sha256'],'shapes':len(rows),'fuel_step_ratio_range':[min(x['fuel_step_ratio'] for x in rows),max(x['fuel_step_ratio'] for x in rows)],'partial_array_objects_range':[min(x['partial_array_objects_per_call'] for x in rows),max(x['partial_array_objects_per_call'] for x in rows)],'product_reduction':rows[0]['product_reduction_fraction']},indent=2))
if __name__=='__main__':main()
