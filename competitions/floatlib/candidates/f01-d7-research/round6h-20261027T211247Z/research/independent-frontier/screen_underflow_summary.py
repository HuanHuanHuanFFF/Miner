"""Complete exposed-plan A/B summary scan, not a benchmark or Lean proof.

No threshold sweep: retained43, symmetric51, max effective-exponent sum102,
and the prior raw-exponent sum102 sufficient bounds only.
"""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,json,hashlib,time,argparse
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--run',type=int,required=True);args=ap.parse_args();run=args.run
 assert run in [40168687803,40169957447,40171180249]
 st=time.monotonic();reads=0;base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
 idx=json.loads((base/'original-artifact-hashes.json').read_bytes());prefix='diagnostics/f01-d7-public-suite/public-suite/'
 plan,ph=M.load_checked(base,idx,prefix+'public-drawn-plan.json');verdict,vh=M.load_checked(base,idx,prefix+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,prefix+'public-cell-work.json')
 costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()};total=sum(costs.values());rows=[]
 for c in plan['cases']:
  if c['kernel']!='bmm' or not c['timed']:continue
  m,n,p=(c[k] for k in ['m','n','p']);batch=c['batch'];NA=batch*m*n;NB=batch*n*p
  a_hist=[0]*256;b_hist=[0]*256;firstA=[NA]*256;firstB=[NB]*256;shaA=hashlib.sha256();shaB=hashlib.sha256()
  outputs={'all':batch*m*p,'old43_rowcol':0,'symmetric51_rowcol':0,'effective102_rowcol':0,'raw102_rowcol':0,'finite_zero_rowcol':0,'raw102_or_zero_rowcol':0}
  allAZero=True;allBZero=True
  for b in range(batch):
   ars=[]
   for r in range(m):
    mx=0;finite=True;zero=True
    for k in range(n):
     i=(b*m+r)*n+k;w=M.E['element'](c,i,0,n);e=(w>>23)&255
     a_hist[e]+=1;firstA[e]=min(firstA[e],i);mx=max(mx,e);finite &= e<255;zero &= (w&0x7fffffff)==0;shaA.update(w.to_bytes(4,'little'))
    ars.append((mx,finite,zero));allAZero &= zero
   bmax=[0]*p;bfinite=[True]*p;bzero=[True]*p
   for k in range(n):
    for j in range(p):
     i=b*n*p+k*p+j;w=M.E['element'](c,i,1,p);e=(w>>23)&255
     b_hist[e]+=1;firstB[e]=min(firstB[e],i);bmax[j]=max(bmax[j],e);bfinite[j] &= e<255;bzero[j] &= (w&0x7fffffff)==0;shaB.update(w.to_bytes(4,'little'))
   allBZero &= all(bzero)
   bh=[0]*255;zeroCols=0
   for j in range(p):
    if bfinite[j]:bh[bmax[j]]+=1;zeroCols+=bzero[j]
   cumulative=[];t=0
   for z in bh:t+=z;cumulative.append(t)
   finiteCols=t
   def at(q):return 0 if q<0 else cumulative[min(254,q)]
   for e,finite,zero in ars:
    if not finite:continue
    outputs['old43_rowcol']+=at(43) if e<=43 else 0
    outputs['symmetric51_rowcol']+=at(51) if e<=51 else 0
    outputs['raw102_rowcol']+=at(102-e)
    # E_eff=max(E,1); at raw threshold >=1 includes both E0 and E1.
    limit=102-max(e,1)
    outputs['effective102_rowcol']+=at(limit) if limit>=1 else 0
    zeros=finiteCols if zero else zeroCols
    outputs['finite_zero_rowcol']+=zeros
    # Union avoids counting zero columns twice when their E0 also meets sum bound.
    outputs['raw102_or_zero_rowcol']+=finiteCols if zero else at(102-e)+(zeroCols if e>102 else 0)
   reads+=m*n+n*p
   if reads>3100000 or time.monotonic()-st>20:raise RuntimeError('Bound exceeded; no partial result accepted')
  ma=max((e for e,nc in enumerate(a_hist) if nc),default=0);mb=max((e for e,nc in enumerate(b_hist) if nc),default=0)
  fa=a_hist[255]==0;fb=b_hist[255]==0
  old=ma<=43 and mb<=43;sym=ma<=51 and mb<=51;eff=fa and fb and max(ma,1)+max(mb,1)<=102;raw=fa and fb and ma+mb<=102
  zwhole=fa and fb and (allAZero or allBZero)
  def stop(first,limit,size):return min([first[e] for e in range(limit+1,256)]+[size])
  def fixed_reads(limit):
   a=stop(firstA,limit,NA)
   if a<NA:return a+1
   b=stop(firstB,limit,NB);return NA+(b+1 if b<NB else NB)
  # A max scan rejects E>102 immediately. If A finishes, B rejects >102-maxA.
  a=stop(firstA,102,NA)
  if a<NA:rawscan=a+1
  else:
   bb=stop(firstB,102-ma,NB);rawscan=NA+(bb+1 if bb<NB else NB)
  # The effective version rejects A_eff>101 before scanning B.
  a=stop(firstA,101,NA)
  if a<NA:effscan=a+1
  else:
   limit=102-max(ma,1);bb=stop(firstB,limit,NB);effscan=NA+(bb+1 if bb<NB else NB)
  cell=':'.join(c['name'].split(':')[:2])
  rows.append({'name':c['name'],'shape':[batch,m,n,p],'cell':cell,'cell_share_whole':costs[cell]/total,'A_words':NA,'B_words':NB,'A_max_raw_exp':ma,'B_max_raw_exp':mb,'A_nonfinite':a_hist[255],'B_nonfinite':b_hist[255],'A_allzero':allAZero,'B_allzero':allBZero,'A_trace_sha256':shaA.hexdigest(),'B_trace_sha256':shaB.hexdigest(),'whole_certificates':{'old43':old,'symmetric51':sym,'effective102':eff,'raw102':raw,'raw102_or_finite_zero':raw or zwhole},'output_certificates':outputs,'new_outputs_beyond_retained_whole':{k:(0 if old else v) for k,v in outputs.items() if k!='all'},'scan_reads':{'old43_shortcircuit':fixed_reads(43),'symmetric51_shortcircuit':fixed_reads(51),'effective102_A_then_B':effscan,'raw102_A_then_B':rawscan,'rowcol_full_summaries':NA+NB},'summary_entries':batch*(m+p)})
 totals={}
 for key in ['symmetric51','effective102','raw102','raw102_or_finite_zero']:
  hits=[r for r in rows if r['whole_certificates'][key] and not r['whole_certificates']['old43']]
  cells=sorted({r['cell'] for r in hits})
  totals[key]={'new_whole_cases':[r['name'] for r in hits],'new_whole_outputs':sum(r['output_certificates']['all'] for r in hits),'new_whole_MACs':sum(r['output_certificates']['all']*r['shape'][2] for r in hits),'affected_entire_cell_share_ceiling':sum(costs[c] for c in cells)/total,'affected_cells':cells}
 for key in ['old43_rowcol','symmetric51_rowcol','effective102_rowcol','raw102_rowcol','raw102_or_zero_rowcol']:
  hits=[r for r in rows if r['new_outputs_beyond_retained_whole'][key]>0];cells=sorted({r['cell'] for r in hits})
  totals[key]={'new_outputs':sum(r['new_outputs_beyond_retained_whole'][key] for r in hits),'new_MACs':sum(r['new_outputs_beyond_retained_whole'][key]*r['shape'][2] for r in hits),'affected_cells':cells,'affected_entire_cell_share_ceiling':sum(costs[c] for c in cells)/total,'cases':[{'name':r['name'],'new_outputs':r['new_outputs_beyond_retained_whole'][key],'total_outputs':r['output_certificates']['all']} for r in hits]}
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'run':run,'state':'COMPLETE_SOURCE_TRANSCRIPTION_SUMMARIES','first_subtask_tool_utc':'2026-10-27T22:01:36Z','subtask_deadline_utc':'2026-10-27T22:16:36Z','plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'reads':reads,'elapsed_seconds':time.monotonic()-st,'totals':totals,'scan_totals':{k:sum(r['scan_reads'][k] for r in rows) for k in rows[0]['scan_reads']},'cases':rows,'limits':'Every A/B word in all35 timed BMM cases; 3.1M reads and20 seconds internal, separate external25s timeout. Transcription not crosschecked with Lean-generated words. No new Lean or candidate.','claims':'Bounds are sufficient real RNE zero-product paper premises, not rounded-small heuristics. Row/col paths require new scan/transport proof and cost. Entire affected cell time is a deliberately coarse ceiling, not actual eligible time. Counts cannot be converted to speed.'}
 (D/f'underflow-summary-{run}.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n')
 print(json.dumps({'run':run,'reads':reads,'elapsed_seconds':out['elapsed_seconds'],'totals':totals,'scan_totals':out['scan_totals']}))
if __name__=='__main__':main()
