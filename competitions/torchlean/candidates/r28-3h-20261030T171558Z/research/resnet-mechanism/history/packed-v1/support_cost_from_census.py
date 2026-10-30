#!/usr/bin/env python3
"""Source-operation/space accounting of the actual native-only support prototype.
No timing model or speedup claim; odd output channels' redundant source products stay counted.
"""
from pathlib import Path
import hashlib,json,math
P=Path(__file__).resolve().parent
def main():
    source=P/'cnn-zero-census-legacy.json';raw=json.loads(source.read_text())
    cells=[]
    for cell in raw['rows']:
      rows=[];base=proposed=prep=peak=bytes_total=0
      for r in cell['layers']:
        n=r['side']**2;terms=r['window_total_terms'];live=terms-r['window_zero_terms'];k=r['k'];C=r['cout']
        hit=r['guard_hit_model'] and k<128 and C>=4 and r['input_zero_count']*4>=r['input_size']
        muls=4*((C+1)//2)*live if hit else r['base_split_multiplies']
        # The runtime reserves all original terms plus sentinels, even when most are zero.
        capacity=(terms+n)*8 if hit else 0;used=(live+n)*8 if hit else 0
        cache_iters=((C+1)//2)*(live+n) if hit else 0
        base+=r['base_split_multiplies'];proposed+=muls;prep+=terms if hit else 0;peak=max(peak,capacity);bytes_total+=capacity
        rows.append({'layer':r['layer'],'sample':r['sample'],'support_route_model':hit,'base_products':r['base_split_multiplies'],'prototype_source_products':muls,'prep_patch_visits':terms if hit else 0,'cache_consumer_iterations':cache_iters,'cache_capacity_bytes_excluding_header':capacity,'cache_live_bytes_excluding_header':used,'odd_output_extra_accumulator':hit and C%2==1})
      cells.append({'kind':cell['kind'],'batch':cell['batch'],'profile':cell['profile'],'base_products':base,'prototype_source_products':proposed,'product_reduction_fraction':1-proposed/base,'additional_prep_patch_visits':prep,'peak_reserved_cache_bytes':peak,'sum_reserved_cache_bytes_over_calls':bytes_total,'rows':rows})
    result={'state':'SOURCE_OPERATION_AND_SPACE_ACCOUNTING_ONLY','source_census_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'runtime_sha256':hashlib.sha256((P/'PackedSupportRuntime.lean.inc').read_bytes()).hexdigest(),'candidate_sha256':'6bf92e5fa5367e2143fb2d02bae466781be540761bba50b0375ae7fc7c472539','cells':cells,'limits':['No memory allocator/header/deallocation timing measured','No compiler folding assumed for unused second accumulator at odd cout','Density pass and fallback prepasses have nonzero work but no cycle estimate','Array storage excludes Lean object headers and possible capacity rounding','Not a complete model latency or adoption result'],'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (P/'support-cost-model.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps([{k:c[k] for k in ['kind','batch','product_reduction_fraction','additional_prep_patch_visits','peak_reserved_cache_bytes']} for c in cells],indent=2))
if __name__=='__main__':main()
