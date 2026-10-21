"""Audit paired affinity diagnostics without converting them into candidate scores."""
from pathlib import Path
import argparse,hashlib,json,statistics as st
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    ap=argparse.ArgumentParser();ap.add_argument('folder',type=Path);ap.add_argument('--output',type=Path,required=True);a=ap.parse_args();p=a.folder.resolve();d=json.loads((p/'r24-affinity/affinity.json').read_bytes());inv=json.loads((p/'raw-artifact-files.json').read_bytes());ci=json.loads((p/'ci-run.json').read_bytes())
    assert ci['status']=='completed' and ci['conclusion']=='success' and ci['headSha']==d['git_sha'] and str(ci['databaseId'])==d['run_id']
    for f,v in inv['files'].items():
        path=(p/f).resolve();assert path.is_relative_to(p) and path.stat().st_size==v['bytes'] and sha(path)==v['sha256']
    report={'status':'VERIFIED_AFFINITY_DIAGNOSTIC_ONLY','run_id':d['run_id'],'context_probe':d['context_probe'],'source_files':d['source_files'],'original_status':d['status'],'rows':[],'scope':'Originalpairedengine/order/11reps at two explicit environment conditions; diagnostic, not replacement official performance or share evidence.'}
    if d['status']=='COMPLETE_CONTROLLED_PAIRED_AFFINITY_DIAGNOSTIC':
        assert len(d['blocks'])==16
        for row in d['blocks']:
            path=p/'r24-affinity'/row['raw_file'];assert sha(path)==row['raw_sha256'];raw=[json.loads(x)for x in path.read_text().splitlines()];assert raw[0]==row['metadata'];fs=[x for x in raw if x['kind']=='file'];assert len(fs)==28
            axis=st.mean(st.median(z['total_s']for z in f['methods'][row['method']]['reps']if z['phase']=='measured')/st.median(z['total_s']for z in f['methods']['incumbent']['reps']if z['phase']=='measured')for f in fs);assert abs(axis-row['diagnostic_time_axis'])<1e-12
            if row['mode']=='explicit_single_cpu':assert row['actual_context']['affinity_before_exec']==[int(d['requested_cpu'])]
        for mode in ['original_cgroup_request','explicit_single_cpu']:
            for block in [1,2]:
                rs={r['method']:r for r in d['blocks']if r['mode']==mode and r['block']==block};assert len(rs)==4
                gaps={}
                for name in ['public609','r24-609-price-groups']:
                    x,y=rs[name],rs[name+'-shadow'];assert x['metadata']['methods'][name]['lib_sha256']==y['metadata']['methods'][name+'-shadow']['lib_sha256'];gaps[name]=100*(y['diagnostic_time_axis']/x['diagnostic_time_axis']-1)
                report['rows'].append({'mode':mode,'block':block,'alias_gap_pct':gaps,'N_vs609_pct':100*(rs['r24-609-price-groups']['diagnostic_time_axis']/rs['public609']['diagnostic_time_axis']-1)})
        report['absolute_gap_medians']={mode:{name:st.median(abs(r['alias_gap_pct'][name])for r in report['rows']if r['mode']==mode)for name in ['public609','r24-609-price-groups']}for mode in ['original_cgroup_request','explicit_single_cpu']}
        report['decision']='Actualdefaultcontext is broader than requestedCPU; explicitbinding narrows parentmedian gap here but increases candidate median gap. It does not uniformly remove alias variation, and cannot justify replacing original scores or declaring stability.'
    else:assert d['status']=='COMPLETE_CONTEXT_ALREADY_SINGLETON_NO_TIMING_CONTRAST'
    assert not a.output.exists();a.output.write_bytes((json.dumps(report,indent=2)+'\n').encode());print(json.dumps({'status':report['status'],'rows':report['rows'],'absolute_gap_medians':report.get('absolute_gap_medians'),'decision':report.get('decision',d.get('decision'))},indent=2))
if __name__=='__main__':main()
