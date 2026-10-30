#!/usr/bin/env python3
"""Compare source arithmetic work on the same previously public inputs.
Not independent trials or runtime predictions. All kernel sources remain unchanged.
"""
from pathlib import Path
import hashlib,importlib.util,json,struct
P=Path(__file__).resolve().parent
s=importlib.util.spec_from_file_location('r28_work_compare',P/'verify_spatial_runtime.py')
V=importlib.util.module_from_spec(s);s.loader.exec_module(V);C=V.C
def main():
 original=C.conv;calls=[];identity={}
 def count(inp,ci,n,co,w,b):
  output,stat=original(inp,ci,n,co,w,b)
  base=stat['base_split_multiplies'];zero=base-stat['candidate_skipped_multiplies']
  live=stat['window_total_terms']-stat['window_zero_terms']
  support=stat['guard_hit_model'] and ci*9<128 and co>=4 and stat['input_zero_count']*4>=stat['input_size']
  sp,why=V.contexts(inp,ci,n,co,w,b)
  support_work=4*((co+1)//2)*live if support else base
  spatial_work=8*ci*co*n*n if sp is not None else base
  calls.append({**identity,'shape':[ci,n,n,co],'input_sha256':hashlib.sha256(b''.join(struct.pack('<I',x) for x in inp)).hexdigest(),'base_narrow_model':stat['guard_hit_model'],'base_split_products':base,'zero_pair_source_products':zero,'support_v2_source_products':support_work,'spatial_8e5_source_products':spatial_work,'support_guard_model':support,'spatial_guard_model':sp is not None,'spatial_guard_reason':why,'spatial_fewer_products_than_zero_pair':spatial_work<zero,'window_zero_fraction':stat['window_zero_fraction']})
  return output,stat
 C.conv=count
 for profile in ['legacy','scale','boundary']:
  for kind in ['normal','wide','sparse']:
   identity.update(profile=profile,kind=kind,batch=1)
   C.run(42,kind,profile,1)
 summary=[]
 for profile in ['legacy','scale','boundary']:
  for kind in ['normal','wide','sparse']:
   selected=[r for r in calls if r['profile']==profile and r['kind']==kind]
   sums={k:sum(r[k] for r in selected) for k in ['base_split_products','zero_pair_source_products','support_v2_source_products','spatial_8e5_source_products']}
   summary.append({'profile':profile,'kind':kind,**sums,'spatial_admitted_calls':sum(r['spatial_guard_model'] for r in selected),'spatial_fewer_products_calls':sum(r['spatial_fewer_products_than_zero_pair'] for r in selected)})
 r={'state':'PAIRED_SOURCE_WORK_COUNTS_NOT_TIMING','seed':42,'source_versions':{'zero_pair':'c6a4da975e84f9b00d606d63f2aeec77bf05e10534fe1267463dffbdff6d23f4','support_v2':'a498d9b70f9892a671943c6a726c36e2e745baae33fb986b899012ccf3f8b6c2','spatial':'8e5b27c03926667b2d4398f21519be91dc39b84a9097e24844af8657f0f1e1d3'},'summary':summary,'calls':calls,'interpretation':'For evencout, an input-skip direct tile has fewer exact products than spatial16 once its per-window zero fraction exceeds5/9. Counts do not include the very different branch/tuple/cache/control/preparation costs. Source11 itself does not skip zero weights. No hybrid or extra candidate is implemented or queued.','limits':['Original_narrow false rows use a common direct-product proxy for fallback work, not their actual triplet/fallback native counts; unchanged baseline portions are held equal.','Source product counts are not optimized C/ASM instruction counts.','Same-input models are one evidence family, not independent performance confirmations.','No official score or sample-success probability is inferred.'],'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
 (P/'mechanism-work-comparison.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
 print(json.dumps({'calls':len(calls),'spatial_admitted':sum(x['spatial_guard_model'] for x in calls),'spatial_fewer_products_than_zero_pair':sum(x['spatial_fewer_products_than_zero_pair'] for x in calls),'summary':summary},indent=2))
if __name__=='__main__':main()
