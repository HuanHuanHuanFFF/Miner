"""Old-input census for a future empty/singleton pixel refinement, same sparse-input family."""
from pathlib import Path
import importlib.util,collections,hashlib,json,datetime
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r28s01',HERE/'mobile_census.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
ORIGINAL=M.conv;ROWS=[]
def audit(x,ci,h,co,k,pad,w,b,dw,label):
    out,row=ORIGINAL(x,ci,h,co,k,pad,w,b,dw,label)
    if not dw and k==1:
      hist=collections.Counter(sum((x[t*h*h+p]&0x7fffffff)!=0 for t in range(ci)) for p in range(h*h))
      dense=not any((a&0x7fffffff)==0 for a in w)
      g=M.source53_guard(x,w,b,ci,co)
      ROWS.append({'stage':label,'side':h,'cin':ci,'cout':co,'dense_weights':dense,'narrow':g['g_narrow'],'pixel_support_histogram':dict(hist),'total_outputs':co*h*h,'zero_support_outputs':hist[0]*co,'one_support_outputs':hist[1]*co,'nonzero_bias_rows':sum(M.F.fields(a)[1]!=0 for a in b)})
    return out,row
def main():
    M.conv=audit
    for seed in [42,12345]:
      for profile in ['typical','scale','boundary']:
       for kind in ['normal','wide','sparse']:
        before=len(ROWS);M.one(seed,profile,kind)
        for row in ROWS[before:]:row.update(seed=seed,profile=profile,kind=kind)
    sums=[]
    for stage in ['pw1','pw2']:
      for dense in [True,False]:
        rows=[r for r in ROWS if r['stage']==stage and r['dense_weights']==dense]
        sums.append({'stage':stage,'dense_weights':dense,'calls':len(rows),'outputs':sum(r['total_outputs'] for r in rows),'empty_outputs':sum(r['zero_support_outputs'] for r in rows),'singleton_outputs':sum(r['one_support_outputs'] for r in rows)})
    result={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Finite old formula input census only; same parent/A sparse-input family, not an independent route or timing evidence. No frozen code or CI change.','summary':sums,'rows':ROWS,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'producer_sha256':hashlib.sha256((HERE/'mobile_census.py').read_bytes()).hexdigest()}
    (HERE/'support01-census.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(sums,indent=2))
if __name__=='__main__':main()
