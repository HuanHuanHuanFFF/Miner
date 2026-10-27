"""CI12-only B16 intended-guard sensitivity; no future runs, build or candidate writes."""
from pathlib import Path
from fractions import Fraction
from datetime import datetime,timezone
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40430974047'
RAW=RUN/'download-08d56bf17d524b209ff9058819a9b0c8'
PROFILE=next(p.parent for p in RAW.rglob('route-results.json') if 'f01-r19-dev-route-profile2' in str(p))
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(name,value):(HERE/name).write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
def parse(path,plan):
    rows={};expected={c['name']:c for c in plan['cases']};assert len(expected)==156
    for line in path.read_text().splitlines():
        m=re.fullmatch(r'(\S+) (true|false) (\d+) (\d+)',line)
        if not m:continue
        name,t,ns,checksum=m.groups();assert name in expected and name not in rows
        timed=t=='true';ns=int(ns);assert timed==expected[name]['timed'] and (ns>0 if timed else ns==0)
        rows[name]={'timed':timed,'best_ns':ns,'checksum':int(checksum)}
    assert set(rows)==set(expected) and sum(r['timed'] for r in rows.values())==152
    return rows
def guard(c):return 3<=c['p']<=8 and c['m']>=4 and c['n']>1 and 4*((c['p']+3)//4)==2*((c['p']+1)//2)
def coverage_guard(c):return c['m']>0 and c['n']>1 and c['p']>=3 and 4*((c['p']+3)//4)==2*((c['p']+1)//2)

def main():
    assert [p for p in range(3,9) if 4*((p+3)//4)==2*((p+1)//2)]==[3,4,7,8]
    inventory=json.loads((RUN/'original-artifact-hashes.json').read_bytes());originals=[]
    for relative,item in inventory['files'].items():
        path=RAW/relative;assert sha(path)==item['sha256'] and path.stat().st_size==item['bytes'],relative
        originals.append({'path':path.relative_to(ROOT).as_posix(),**item})
    save('all-CI12-originals.json',{'run':40430974047,'source_commit':inventory['artifact']['workflow_run']['head_sha'],'archive_digest':inventory['artifact']['digest'],
        'hash_receipt_sha256':sha(RUN/'original-artifact-hashes.json'),'count':len(originals),'files':originals})
    route=json.loads((PROFILE/'route-results.json').read_bytes());assert route['complete'] is True and route['diagnostic_only'] is True
    assert route['kernel_sha256']=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
    assert route['build_identity_before']==route['build_identity_after']
    assert [r['seed'] for r in route['results']]==[1927003,1927005]
    results=[]
    for record in route['results']:
        seed=record['seed'];plan_path=PROFILE/f'seen-{seed}-plan.json';plan=json.loads(plan_path.read_bytes())
        assert sha(plan_path)==record['plan_sha256']
        assert sha(plan_path)=={1927003:'b3d19580bc8d5c6674edcbfa4eda0c405d0f83bcef9064af827243503e5bb6a9',1927005:'8c385cab83fdb6243420ed4dc80c8dbf9e843564e249602bccab16288c8eec90'}[seed]
        labels=json.loads((PROFILE/f'labels-{seed}.json').read_bytes());assert labels==record['labels']
        raw=[]
        for process in (0,1):
            rows=parse(PROFILE/f'whole-{seed}-{process}.log',plan)
            assert rows==json.loads((PROFILE/f'rows-{seed}-{process}.json').read_bytes())==record['complete_case_rows'][process]
            raw.append(rows)
        assert all(raw[0][name]['checksum']==raw[1][name]['checksum'] for name in raw[0])
        # Explicitly average each case first, retaining both fast and slow samples.
        mean={name:Fraction(raw[0][name]['best_ns']+raw[1][name]['best_ns'],2) for name in raw[0]}
        whole=sum(mean[c['name']] for c in plan['cases'] if c['timed'])
        bmm=sum(mean[c['name']] for c in plan['cases'] if c['timed'] and c['kernel']=='bmm')
        b2=sum(mean[c['name']] for c in plan['cases'] if c['timed'] and c['kernel']=='bmm' and labels[c['name']]['route']=='B2')
        selected=[];guard_but_other=[];all_case_means=[]
        for c in plan['cases']:
            name=c['name'];active=c['kernel']=='bmm' and c['timed'] and guard(c) and labels[name]['route']=='B2'
            all_case_means.append({'case':name,'timed':c['timed'],'mean_complete_pass_ns':float(mean[name]),'selected':active})
            if c['kernel']=='bmm' and c['timed'] and guard(c) and labels[name]['route']!='B2':guard_but_other.append({'case':name,'route':labels[name]['route'],'shape':[c[k] for k in ('batch','m','n','p')]})
            if active:selected.append({'case':name,'shape_order':'batch,m,n,p','shape':[c[k] for k in ('batch','m','n','p')],
                'route':labels[name]['route'],'process0_ns':raw[0][name]['best_ns'],'process1_ns':raw[1][name]['best_ns'],
                'mean_complete_pass_ns':float(mean[name]),'whole_share':float(mean[name]/whole)})
        selected_ns=sum(Fraction(c['process0_ns']+c['process1_ns'],2) for c in selected);share=selected_ns/whole
        assert whole==record['timing']['mean_of_case_timers']['whole_ns'] and bmm==record['timing']['mean_of_case_timers']['BMM_ns']
        assert b2==record['timing']['mean_of_case_timers']['routes']['B2']['ns']
        process_totals=[]
        for rows in raw:
            W=sum(r['best_ns'] for r in rows.values());S=sum(rows[c['case']]['best_ns'] for c in selected)
            process_totals.append({'whole_ns':W,'selected_ns':S,'selected_whole_share':S/W})
        n2=sum(Fraction(c['process0_ns']+c['process1_ns'],2) for c in selected if c['shape'][2]==2)
        coverage={name:{'ns':Fraction(0),'cases':[]} for name in ('B2','DirectContinuous','Packed10','B1','UnderflowZero')}
        for c in plan['cases']:
            if c['kernel']=='bmm' and coverage_guard(c):
                name=c['name'];label=labels[name]['route'];coverage[label]['ns']+=mean[name]
                coverage[label]['cases'].append({'case':name,'timed':c['timed'],'shape_order':'batch,m,n,p','shape':[c[k] for k in ('batch','m','n','p')],
                    'process0_ns':raw[0][name]['best_ns'],'process1_ns':raw[1][name]['best_ns'],'mean_complete_pass_ns':float(mean[name])})
        coverage_ns=sum(value['ns'] for value in coverage.values())
        coverage_result={name:{'mean_complete_pass_ns':float(value['ns']),'whole_share':float(value['ns']/whole),
            'timed_case_count':sum(c['timed'] for c in value['cases']),'all_case_count':len(value['cases']),'cases':value['cases']} for name,value in coverage.items()}
        results.append({'seed':seed,'plan_sha256':sha(plan_path),'rows_per_log':156,'timed_rows':152,'timed_BMM_rows':34,'all156_checksums_match':True,
            'processes':process_totals,'whole_mean_ns':float(whole),'BMM_mean_ns':float(bmm),'all_B2_mean_ns':float(b2),
            'selected_case_count':len(selected),'selected_mean_ns':float(selected_ns),'selected_whole_share':float(share),'selected_B2_share':float(selected_ns/b2),
            'n2_mean_ns':float(n2),'n2_fraction_of_selected':float(n2/selected_ns),'selected_cases':selected,'guard_shapes_routed_elsewhere_not_counted':guard_but_other,
            'counterfactuals_others_fixed':{'selected_entire_pass_cost_zero':{'whole_ns':float(whole-selected_ns),'whole_ratio':float(1-share),'whole_reduction':float(share)},
                'selected_entire_pass_cost_halved':{'whole_ns':float(whole-selected_ns/2),'whole_ratio':float(1-share/2),'whole_reduction':float(share/2)},
                'whole3pct_required_selected_entire_pass_reduction':float(Fraction(3,100)/share)},
            'selection_only_expanded_shape_coverage':{'guard':'m>0,n>1,p>=3 and4*ceil(p/4)=2*ceil(p/2); no p<=8 bound and no existingB2 requirement',
                'by_original_route':coverage_result,'total_mean_complete_pass_ns':float(coverage_ns),'total_whole_share':float(coverage_ns/whole),
                'excluding_UnderflowZero_whole_share':float((coverage_ns-coverage['UnderflowZero']['ns'])/whole),
                'whole3pct_algebraic_required_local_pass_reduction':float(Fraction(3,100)*whole/coverage_ns),
                'scope':'Shape coverage for research selection only, including explicit oldUnderflowZero ledger and untimedchecks at0ns. Not removable cost or an implementation grant. Additional preparation/net benefit UNKNOWN.'},
            'all_case_means':all_case_means})
    report={'at_utc':datetime.now(timezone.utc).isoformat(),'input_run':40430974047,'route_results_sha256':sha(PROFILE/'route-results.json'),
        'source_sha256':route['kernel_sha256'],'intended_guard':'3<=p<=8,m>=4,n>1 and4*ceil(p/4)=2*ceil(p/2),equivalentp3/4/7/8; intersect timed actualB2 route',
        'calculation':'Parse all4 raw timer logs independently. Average two observations percase, then sum complete timedpass ns; no ns/work,MAC weighting,sample trimming or pooling seeds.',
        'results':results,'decision':'KEEP_TYPED_CORE_ASSET_DEFER_FULL_PUBLIC_INTEGRATION_FOR_THIS_NARROW_GUARD',
        'reason':'The two oldseed shares are4.2873%/3.1457%whole, so3%whole needs69.974%/95.369% complete-local-pass reduction. Halving affected fullpass cost misses3% onboth. This gives little basis to spend on public integration now.',
        'sensitivity_only':'Zero/half cases are algebraic counterfactuals with every other case fixed, including unchanged timer/checksum/cleanup inside selectedpass. They are not achievable gains, a generalizable wide-domain bound or a probability.',
        'expanded_coverage_decision':'Droppingm>=4/oldB2 requirement adds mainly oldDC coverage, while widePacked10 contributes little in these two plans. Combined eligible completepass shares about7.34%/6.05% are selection information only; sameB16 cache preparation, actualcaller viability and net improvement remainUNKNOWN. No wider source implementation authorized or performed.',
        'not_read':'D17 inputs/timing, D18inflight core proof results and any new confirmation were not read. No claim on currentB16 proof or native performance.',
        'scope':'CI12 observed complete-pass timings only. No Git/CI/Lean or changes outside this review directory; no new framework.'}
    save('scope-bound.json',report)
    print(json.dumps([{'seed':r['seed'],'cases':r['selected_case_count'],'whole_share':r['selected_whole_share'],'zero_ratio':r['counterfactuals_others_fixed']['selected_entire_pass_cost_zero']['whole_ratio'],
        'half_ratio':r['counterfactuals_others_fixed']['selected_entire_pass_cost_halved']['whole_ratio'],'required_local_drop':r['counterfactuals_others_fixed']['whole3pct_required_selected_entire_pass_reduction']} for r in results],indent=2))
if __name__=='__main__':main()
