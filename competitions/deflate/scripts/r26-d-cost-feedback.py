"""Decompose original D1 total-axis differences; arithmetic attribution is not causality."""
from pathlib import Path
import json, hashlib, statistics, argparse
ROOT=Path(__file__).resolve().parents[1]
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--output',type=Path,required=True);a=ap.parse_args();assert not a.output.exists()
 base=ROOT/'evidence/round26/38267276245/screen90-d1/gate';names=['public658','public658-shadow','r26-d-658-selective-depth','r26-d-658-selective-depth-shadow'];data={};raw={}
 for name in names:
  p=base/('round1-'+name+'.jsonl');raw[p.relative_to(ROOT).as_posix()]=hashlib.sha256(p.read_bytes()).hexdigest();rows=[json.loads(s)for s in p.read_text().splitlines()];data[name]={}
  for row in rows:
   if row['kind']!='file':continue
   methods={}
   for m in (name,'incumbent'):
    reps=[x for x in row['methods'][m]['reps']if x['phase']=='measured'];assert len(reps)==11
    z=sorted(reps,key=lambda x:x['total_s'])[5];assert abs(z['total_s']-z['time_s']-z['encode_s'])<1e-12
    methods[m]={'total':z['total_s'],'parser':z['time_s'],'encoder':z['encode_s'],'observed_total_range':[min(x['total_s']for x in reps),max(x['total_s']for x in reps)]}
   data[name][row['file']]={'methods':methods,'tokens_sha256':row['methods'][name]['tokens_sha256'],'output_bytes':row['methods'][name]['output_bytes']}
 comparisons=[]
 for name in names[2:]:
  for parent in names[:2]:
   rows=[];x0=statistics.mean(v['methods'][parent]['total']/v['methods']['incumbent']['total']for v in data[parent].values())
   for f,v in data[name].items():
    w=data[parent][f];c=v['methods'][name];b=w['methods'][parent];ic=v['methods']['incumbent']['total'];ip=w['methods']['incumbent']['total'];terms={'parser':(c['parser']-b['parser'])/ic,'encoder':(c['encoder']-b['encoder'])/ic,'paired_incumbent':b['total']*(1/ic-1/ip)};actual=c['total']/ic-b['total']/ip;assert abs(sum(terms.values())-actual)<1e-12
    rows.append({'file':f,'tokens_changed':v['tokens_sha256']!=w['tokens_sha256'],'candidate':c,'parent':b,'candidate_incumbent_total':ic,'parent_incumbent_total':ip,'relative_total_axis_contribution_pp':actual/28/x0*100,'components_pp':{k:x/28/x0*100 for k,x in terms.items()},'output_bytes_delta':v['output_bytes']-w['output_bytes']})
   groups={}
   for label,selected in [('all',rows),('changed_tokens',[x for x in rows if x['tokens_changed']]),('same_tokens',[x for x in rows if not x['tokens_changed']])]:groups[label]={'files':len(selected),'total_axis_change_pp':sum(x['relative_total_axis_contribution_pp']for x in selected),'components_pp':{k:sum(x['components_pp'][k]for x in selected)for k in ['parser','encoder','paired_incumbent']}}
   comparisons.append({'candidate':name,'parent':parent,'groups':groups,'rows':rows})
 result={'status':'VERIFIED_RAW_TOTAL_AXIS_ARITHMETIC_DECOMPOSITION_NOT_CAUSAL','run_id':'38267276245','raw_sha256':raw,'comparisons':comparisons,'limits':['One discovery runner and one block; copies/calibrations are not independent samples.','Parser and encoder come from the same rep selected by median total, not independently selected medians.','The paired-incumbent term is an identity explaining the denominator change, not a timing correction.','Same-token files can still differ by machine/code-layout or noise; these observations cannot separate those causes.','No diagnostic corrected time or share is claimed.']}
 a.output.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps([{'candidate':x['candidate'],'parent':x['parent'],'groups':x['groups']}for x in comparisons]))
if __name__=='__main__':main()
