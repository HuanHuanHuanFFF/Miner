"""Complete old-plan cheap input-summary exactness certificate; no candidate/CI.

Primary bound n*maxAbsCoeffA*maxAbsCoeffB; stronger sufficient bound uses
min(L1A*maxB,maxA*L1B), both obtainable from input summaries. Zero products
are separated by analysis-only nonzero-position masks, not a proposed guard.
"""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,json,hashlib,time,argparse
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)

def blank():return [True,999,0,0,0,0] # finite, minimum normalized exponent, max raw magnitude, L1/minsub, nnz, bitset
def add(s,w,k):
 e=(w>>23)&255;f=w&0x7fffff
 if e==255:s[0]=False;return
 if (w&0x7fffffff)==0:return
 m=f|(0x800000 if e else 0);scale=max(e-1,0)
 quantum=scale-149+(m&-m).bit_length()-1
 s[1]=min(s[1],quantum);s[2]=max(s[2],w&0x7fffffff);s[3]+=m<<scale;s[4]+=1
 if k>=0:s[5]|=1<<k
def finish(s):
 if not s[0]:return {'finite':False,'q':0,'max':0,'l1':0,'nnz':s[4],'mask':s[5]}
 if not s[4]:return {'finite':True,'q':0,'max':0,'l1':0,'nnz':0,'mask':0}
 e=s[2]>>23;m=(s[2]&0x7fffff)|(0x800000 if e else 0);max_units=m<<max(e-1,0);shift=s[1]+149
 assert shift>=0 and max_units%(1<<shift)==0 and s[3]%(1<<shift)==0
 return {'finite':True,'q':s[1],'max':max_units>>shift,'l1':s[3]>>shift,'nnz':s[4],'mask':s[5]}
def cert(a,b,n):
 if not a['finite'] or not b['finite']:return False,False,'nonfinite',0,0,0
 if not a['nnz'] or not b['nnz']:return True,True,'zero',0,0,0
 q=a['q']+b['q'];mx=n*a['max']*b['max'];l1=min(mx,a['l1']*b['max'],a['max']*b['l1'])
 if q < -149 or q>103:return False,False,'quantum',q,mx.bit_length(),l1.bit_length()
 return mx<=1<<24,l1<=1<<24,'bounded',q,mx.bit_length(),l1.bit_length()

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--run',type=int,required=True);run=ap.parse_args().run
 assert run in [40168687803,40169957447,40171180249]
 st=time.monotonic();reads=0;rows=[];examples=[]
 base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());prefix='diagnostics/f01-d7-public-suite/public-suite/'
 plan,ph=M.load_checked(base,idx,prefix+'public-drawn-plan.json');verdict,vh=M.load_checked(base,idx,prefix+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,prefix+'public-cell-work.json');costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()};total=sum(costs.values())
 under=json.loads((D/f'underflow-summary-{run}.json').read_bytes());old43={r['name']:r['whole_certificates']['old43'] for r in under['cases']}
 for c in plan['cases']:
  if c['kernel']!='bmm' or not c['timed']:continue
  batch,m,n,p=(c[k] for k in ['batch','m','n','p']);ag=blank();bg=blank();shaa=hashlib.sha256();shab=hashlib.sha256();bounds=[];hit_examples=[]
  counts={'outputs':batch*m*p,'max_bound_hits':0,'L1_bound_hits':0,'max_hits_nonzero_products':0,'L1_hits_nonzero_products':0,'max_hits_zero_products':0,'L1_hits_zero_products':0,'allzero_input_dots':0,'nonfinite_reject':0,'quantum_reject':0,'coefficient_reject':0}
  for b in range(batch):
   ars=[]
   for r in range(m):
    s=blank()
    for k in range(n):
     w=M.E['element'](c,(b*m+r)*n+k,0,n);add(s,w,k);add(ag,w,-1);shaa.update(w.to_bytes(4,'little'))
    ars.append(finish(s))
   bcs=[blank() for _ in range(p)]
   for k in range(n):
    for j in range(p):
     w=M.E['element'](c,(b*n+k)*p+j,1,p);add(bcs[j],w,k);add(bg,w,-1);shab.update(w.to_bytes(4,'little'))
   bs=[finish(s) for s in bcs]
   for r,a in enumerate(ars):
    for j,bb in enumerate(bs):
     h,hl,why,q,nb,lb=cert(a,bb,n);nonzero=bool(a['mask']&bb['mask'])
     counts['max_bound_hits']+=h;counts['L1_bound_hits']+=hl
     counts['max_hits_nonzero_products']+=h and nonzero;counts['L1_hits_nonzero_products']+=hl and nonzero
     counts['max_hits_zero_products']+=h and not nonzero;counts['L1_hits_zero_products']+=hl and not nonzero
     counts['allzero_input_dots']+=a['finite'] and bb['finite'] and (not a['nnz'] or not bb['nnz'])
     counts['nonfinite_reject']+=why=='nonfinite';counts['quantum_reject']+=why=='quantum';counts['coefficient_reject']+=why=='bounded' and not hl
     if a['finite'] and bb['finite'] and nonzero:
      if len(bounds)<8:bounds.append({'q':q,'nmax_bits':nb,'L1_bits':lb})
     if hl and nonzero and len(hit_examples)<3:
      x={'batch':b,'row':r,'column':j,'qA':a['q'],'qB':bb['q'],'qProduct':q,'maxA':a['max'],'maxB':bb['max'],'L1A':a['l1'],'L1B':bb['l1'],'nmax_pass':h,'nmax_bits':nb,'L1_bits':lb}
      hit_examples.append(x)
   reads+=m*n+n*p
   if reads>3100000 or time.monotonic()-st>25:raise RuntimeError('Resource bound; partial data not accepted')
  ga,gb=finish(ag),finish(bg);gh,gl,why,q,nb,lb=cert(ga,gb,n)
  original=next(r for r in under['cases'] if r['name']==c['name']);assert shaa.hexdigest()==original['A_trace_sha256'] and shab.hexdigest()==original['B_trace_sha256']
  cell=':'.join(c['name'].split(':')[:2])
  rows.append({'name':c['name'],'shape':[batch,m,n,p],'cell':cell,'cell_share_whole':costs[cell]/total,'generator_mantBits':c['mantBits'],'old43_whole':old43[c['name']],'whole_summary_certificate':{'nmax_pass':gh,'L1_pass':gl,'reason':why,'q':q,'nmax_bits':nb,'L1_bits':lb},'counts':counts,'nonzero_hit_examples':hit_examples,'first_nonzero_bounds':bounds,'A_trace_sha256':shaa.hexdigest(),'B_trace_sha256':shab.hexdigest(),'standalone_summary_words':batch*n*(m+p),'summary_records':batch*(m+p),'coefficient_preparation_words_if_selected':batch*n*(m+p),'output_checks':batch*m*p})
 nz=[r for r in rows if r['counts']['L1_hits_nonzero_products']>0 and not r['old43_whole']];cells=sorted({r['cell'] for r in nz});whole=[r for r in rows if r['whole_summary_certificate']['L1_pass'] and not r['old43_whole']]
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'COMPLETE_CHEAP_SUMMARY_SOURCE_MODEL_ONLY','first_tool_utc':'2026-10-27T22:22:52Z','stage_deadline_utc':'2026-10-27T22:42:52Z','run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'source_script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'helper_source_sha256':hashlib.sha256((D/'same_exponent_add.py').read_bytes()).hexdigest(),'generator_translation_sha256':hashlib.sha256(M.G.read_bytes()).hexdigest(),'underflow_receipt_sha256':hashlib.sha256((D/f'underflow-summary-{run}.json').read_bytes()).hexdigest(),'reads':reads,'elapsed_seconds':time.monotonic()-st,'timed_BMM_cases':len(rows),'totals':{k:sum(r['counts'][k] for r in rows) for k in rows[0]['counts']},'new_nonzero_product_cases':[r['name'] for r in nz],'new_nonzero_affected_entire_cell_share_ceiling':sum(costs[k] for k in cells)/total,'new_nonzero_affected_cells':cells,'new_whole_certificate_cases':[r['name'] for r in whole],'cases':rows,'scope':'Exact source summaries of complete old inputs, crosschecked against prior complete A/B trace hashes. Not actual Lean-generated arrays, proof or performance. Nonzero position masks are analysis-only to keep zero-product hits separate; not proposed runtime.','mathematics':'PAPER: qA+qB in[-149,103] and min(n*M_A*M_B,L1_A*M_B,M_A*L1_B)<=2^24 guarantee all products and every original prefix exactly representable. Max-only bound is reported separately. Zero-sign and public/model/word proofs missing.','cost':'Standalone summary pass plus coefficient preparation/fallback/output checks all charged; fused preparation UNKNOWN. No candidate/CI, no reassociation without a validated certificate.'}
 (D/f'exact-lattice-{run}.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n');print(json.dumps({k:out[k] for k in ['run','reads','elapsed_seconds','totals','new_nonzero_product_cases','new_nonzero_affected_entire_cell_share_ceiling','new_whole_certificate_cases']}))
if __name__=='__main__':main()
