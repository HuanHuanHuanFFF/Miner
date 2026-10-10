"""Replay bounded score geometry at actual quality; grid points are not timings."""
from pathlib import Path
import argparse,importlib,json
context=importlib.import_module('round20-impact').context

ROOT=Path(__file__).resolve().parents[1]

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--capture',type=Path,required=True)
    ap.add_argument('--native',type=Path,required=True)
    ap.add_argument('--output',type=Path,required=True)
    a=ap.parse_args()
    comp,ctx,rows,sc,b,front,top,check=context(a.capture)
    formal=next(r for r in rows if str(r['id'])=='595')['metrics']
    native=json.loads(a.native.read_bytes())
    quality={r['candidate']:r['public_size_pct'] for r in native['summary']}
    assert 'public595' in quality
    results=[]
    for name,size in quality.items():
        if name=='public514':continue
        y=formal['mean_file_compression_pct']*size/quality['public595']
        rs=[]
        for i in range(801):
            delta=-3+i*.005
            x=formal['balanced_time_ratio']*(1+delta/100)
            extras=[] if any(p.time_s<=x and p.ratio_pct<=y for p in front) else [sc.Point('__new__',x,y)]
            nf=sc.pareto_front(front+extras)
            w=sc.local_global_improvement_space_log_weights(nf,b)
            rs.append({'synthetic_time_delta_pct':delta,'x':x,'y':y,'single_pool_share_pct':100*comp['policy']['pareto_share']*w.get('__new__',0),'new_frontier_ids':[p.name for p in nf]})
        segments=[];active=[]
        for r in rs:
            if r['single_pool_share_pct']>=10:active.append(r)
            elif active:segments.append(active);active=[]
        if active:segments.append(active)
        results.append({'candidate':name,'quality_verified_run':native['run_id'],'public_size_pct':size,'conditional_projected_size_pct':y,'best_synthetic_grid_point':max(rs,key=lambda r:r['single_pool_share_pct']),'ten_pct_grid_intervals':[{'delta_start_pct':s[0]['synthetic_time_delta_pct'],'delta_end_pct':s[-1]['synthetic_time_delta_pct'],'width_pct':s[-1]['synthetic_time_delta_pct']-s[0]['synthetic_time_delta_pct'],'left':s[0],'right':s[-1]} for s in segments],'grid':rs})
    result={'status':'INFERRED_BOUNDED_GEOMETRY_NOT_PERFORMANCE','snapshot':ctx,'policy_validation':check,'formal_anchor':'595','public_native_receipt':a.native.resolve().relative_to(ROOT).as_posix(),'scope':'Actual native size is VERIFIED finite-corpus data. Time points are synthetic and do not establish a measurement, stability bound, success probability or formal reward. Quality transfer is conditional. Grid resolution0.005percent in -3to+1percentparenttime range, not an exact boundary proof.','candidates':results}
    a.output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps([{'candidate':r['candidate'],'conditional_size':r['conditional_projected_size_pct'],'intervals':[{k:v for k,v in s.items() if k not in ('left','right')} for s in r['ten_pct_grid_intervals']]} for r in results],indent=2))

if __name__=='__main__':main()
