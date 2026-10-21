"""Decompose the retained reference discrepancy without manufacturing new scores."""
from pathlib import Path
import hashlib,json,statistics as st
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def raw(p,n):
    rows=[json.loads(x)for x in p.read_text().splitlines()];meta=rows[0];out={}
    for r in rows:
        if r['kind']!='file':continue
        methods={}
        for name in [n,'incumbent']:
            m=r['methods'][name];reps=[x for x in m['reps']if x['phase']=='measured'];assert len(reps)==11 and not m['errors']
            methods[name]={'median_total_s':st.median(x['total_s']for x in reps),'median_parse_s':st.median(x['time_s']for x in reps),'median_encode_s':st.median(x['encode_s']for x in reps),'total_range_s':[min(x['total_s']for x in reps),max(x['total_s']for x in reps)],'tokens_sha256':m['tokens_sha256'],'output_sha256':m['output_sha256']}
        out[r['file']]={'input_sha256':r['sha256'],'methods':methods}
    assert len(out)==28;return meta,out
def main():
    root=E/'38091944225/checkpoint-z1/gate';names=['public609','public609-shadow'];paths=[root/f'round1-{n}.jsonl'for n in names];data=[raw(p,n)for p,n in zip(paths,names)];a,b=[x[1]for x in data];ma,mb=[x[0]for x in data]
    assert ma['methods'][names[0]]['source_sha256']==mb['methods'][names[1]]['source_sha256'] and ma['methods'][names[0]]['lib_sha256']==mb['methods'][names[1]]['lib_sha256']
    assert ma['methods']['incumbent']['lib_sha256']==mb['methods']['incumbent']['lib_sha256']
    rows=[];corners={k:[]for k in ['A_over_A','B_over_A','A_over_B','B_over_B']}
    for f in a:
        assert a[f]['input_sha256']==b[f]['input_sha256']
        ac,ai=a[f]['methods'][names[0]],a[f]['methods']['incumbent'];bc,bi=b[f]['methods'][names[1]],b[f]['methods']['incumbent']
        for x,y in [(ac,bc),(ai,bi)]:assert x['tokens_sha256']==y['tokens_sha256'] and x['output_sha256']==y['output_sha256']
        ca,ia,cb,ib=[x['median_total_s']for x in [ac,ai,bc,bi]]
        for k,v in zip(corners,[ca/ia,cb/ia,ca/ib,cb/ib]):corners[k].append(v)
        rows.append({'file':f,'candidate_total_gap_pct':100*(cb/ca-1),'incumbent_total_gap_pct':100*(ib/ia-1),'weighted_axis_gap':(cb/ib-ca/ia)/28,'A_candidate':ac,'B_candidate':bc,'A_incumbent':ai,'B_incumbent':bi})
    axes={k:st.mean(v)for k,v in corners.items()};result={'status':'VERIFIED_RAW_DECOMPOSITION_DIAGNOSTIC_ONLY','source_receipts':[{'path':p.relative_to(ROOT).as_posix(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()}for p in paths],'observed_reference_gap_pct':100*(axes['B_over_B']/axes['A_over_A']-1),'four_corners':axes,'rows':rows,'meta_A':ma,'meta_B':mb,'ranked_hypotheses':['Candidate or incumbent time drift in a small subset of files changes the ratio; four-corner and perfile attribution distinguish the numerical contributor.','AllowedCPUs request may not impose actual singleton process affinity on this runner; compare unchanged paired original engine under cgroup-only versus explicit sched_setaffinity.','Execution order, shared host activity or library placement causes residual variation; earlier equal20ordering and sharedlibrary diagnostics did not eliminate all gaps.'],'limits':'Only A/A and B/B are original observed protocol axes. Crossed corners are diagnostic recombinations, not new benchmark scores or private predictions. Affinity metadata alone does not prove migrations occurred.'}
    p=E/'checkpoint-z-decomposition.json';assert not p.exists();p.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'gap_pct':result['observed_reference_gap_pct'],'corners':axes,'largest_contributors':[{k:r[k]for k in ['file','candidate_total_gap_pct','incumbent_total_gap_pct','weighted_axis_gap']}for r in sorted(rows,key=lambda x:abs(x['weighted_axis_gap']),reverse=True)[:6]],'A_affinity':ma.get('benchmark_provenance',{}).get('process_affinity'),'B_affinity':mb.get('benchmark_provenance',{}).get('process_affinity')},indent=2))
if __name__=='__main__':main()
