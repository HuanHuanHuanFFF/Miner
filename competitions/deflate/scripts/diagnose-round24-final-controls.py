"""Decompose the largest actually observed final same-source control difference."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib,json,statistics as st
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24';raw=importlib.import_module('diagnose-round24-checkpoint').raw
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--out',type=Path,required=True);a=ap.parse_args();assert not a.out.exists();plan=json.loads((E/'confirm-final-plan.json').read_bytes());an,bn=plan['candidates'];runs=[('38106900587','confirm-final-1'),('38106909000','confirm-final-2'),('38106920250','confirm-final-3')];options=[];available=[]
    for run,batch in runs:
        folder=E/run/batch/'gate'
        if not(folder/'state.json').exists():continue
        ci=json.loads((folder/'ci-run.json').read_bytes());assert ci['status']=='completed'and ci['conclusion']=='success';state=json.loads((folder/'state.json').read_bytes());by={(r['candidate'],r['round']):r for r in state['metrics']};available.append(run)
        for block in [1,2,3]:
            for first,second in [('public609','public609-shadow'),(an,an+'-shadow'),(bn,bn+'-shadow'),(an,'fast-stack')]:
                if(first,block)not in by or(second,block)not in by:continue
                gap=100*(by[second,block]['time']/by[first,block]['time']-1);options.append({'run_id':run,'batch':batch,'block':block,'first':first,'second':second,'axis_gap_pct':gap,'folder':folder})
    assert options;choice=max(options,key=lambda r:abs(r['axis_gap_pct']));names=[choice['first'],choice['second']];paths=[choice['folder']/f"round{choice['block']}-{n}.jsonl"for n in names];data=[raw(p,n)for p,n in zip(paths,names)];ma,mb=[d[0]for d in data];aa,bb=[d[1]for d in data]
    assert ma['methods'][names[0]]['source_sha256']==mb['methods'][names[1]]['source_sha256']and ma['methods'][names[0]]['lib_sha256']==mb['methods'][names[1]]['lib_sha256'];assert ma['methods']['incumbent']['lib_sha256']==mb['methods']['incumbent']['lib_sha256'];corners={k:[]for k in ['A_over_A','B_over_A','A_over_B','B_over_B']};rows=[]
    for f in aa:
        assert aa[f]['input_sha256']==bb[f]['input_sha256'];ac,ai,bc,bi=[d['methods'][n]for d,n in [(aa[f],names[0]),(aa[f],'incumbent'),(bb[f],names[1]),(bb[f],'incumbent')]]
        for x,y in [(ac,bc),(ai,bi)]:assert x['tokens_sha256']==y['tokens_sha256']and x['output_sha256']==y['output_sha256']
        ca,ia,cb,ib=[x['median_total_s']for x in [ac,ai,bc,bi]]
        for k,v in zip(corners,[ca/ia,cb/ia,ca/ib,cb/ib]):corners[k].append(v)
        rows.append({'file':f,'weighted_axis_gap':(cb/ib-ca/ia)/28,'candidate_total_gap_pct':100*(cb/ca-1),'incumbent_total_gap_pct':100*(ib/ia-1),'candidate_parse_gap_pct':100*(bc['median_parse_s']/ac['median_parse_s']-1),'incumbent_parse_gap_pct':100*(bi['median_parse_s']/ai['median_parse_s']-1),'A_candidate':ac,'B_candidate':bc,'A_incumbent':ai,'B_incumbent':bi})
    c={k:st.mean(v)for k,v in corners.items()};result={'status':'VERIFIED_ORIGINAL_RAW_CONTROL_DECOMPOSITION_DIAGNOSTIC_ONLY','analyzed_utc':datetime.now(timezone.utc).isoformat(),'available_completed_runs':available,'selection':'Largest absolute normalized-axis gap among all complete declaredcandidate/ownshadow,609shadow andA/actual-parent-alias pairs; not selected for flattering candidate score.','chosen':{k:v for k,v in choice.items()if k!='folder'},'raw_receipts':[{'path':p.relative_to(ROOT).as_posix(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()}for p in paths],'four_corners':c,'rows':rows,'all_observed_control_gaps':[{k:v for k,v in o.items()if k!='folder'}for o in options],'limits':'OnlyA/A andB/B areoriginalobservedaxes. Crosscorners diagnose numericalcontributions andarenot newbenchmark scores, correctedpredictions oridentifiedmicroarchitecturalcauses. Doesnotincreaseindependentconfirmationblockcount.'};a.out.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'available_runs':available,'chosen':result['chosen'],'corners':c,'top_files':[{k:r[k]for k in ['file','weighted_axis_gap','candidate_total_gap_pct','incumbent_total_gap_pct']}for r in sorted(rows,key=lambda r:abs(r['weighted_axis_gap']),reverse=True)[:5]]},indent=2))
if __name__=='__main__':main()
