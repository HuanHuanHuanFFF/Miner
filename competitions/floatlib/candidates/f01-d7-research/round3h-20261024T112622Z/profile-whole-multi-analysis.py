"""Validate exposed-input whole diagnostic; no holdout access or scoring."""
from pathlib import Path
import collections,hashlib,importlib.util,json,statistics
HERE=Path(__file__).resolve().parent
REPO=next(p for p in HERE.parents if (p/'competitions/floatlib').is_dir())
def module(name,file,expected):
    p=HERE/file;assert hashlib.sha256(p.read_bytes()).hexdigest()==expected
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
m=module('r13_exact_routes','profile-coarse-analyze.py','1c453b30f90754ede6b39cda5f6dfee6f38ccd78c5c2a40731ef7d124a63b48b')
w=module('r13_whole_parser','profile-whole-multi-current.py','8726e1e5debcfc335a11585d2a432a74ef379727fa393c686abecf631fedd23e')
SEEDS=(1224011,1224091,1224092)


def run():
    root=REPO/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40099316795'
    original=m.Originals(root/'original-artifact-hashes.json')
    folder=original.root/'diagnostics/f01-d13-cost-profile/cost-profile/measurement'
    def read(name):return original.read(folder/(w.PREFIX+name))
    d=json.loads(read('result.json'))
    assert d['complete']is True and d['diagnostic_only']is True and d['full_gate']is False
    assert d['kernel_sha256']==w.SOURCE and d['official_commit']==w.HEAD
    assert d['initial_context_seed']==1224016 and d['actual_seeds']==list(SEEDS)
    assert d['pairs']==500000 and d['inner']==3 and d['processes_per_seed']==2
    assert d['module_sha256']==hashlib.sha256((HERE/'profile-whole-multi-current.py').read_bytes()).hexdigest()
    assert hashlib.sha256(read('Kernel.lean')).hexdigest()==w.SOURCE
    assert hashlib.sha256(read('original-Submission.c')).hexdigest()==d['build_identities']['before']['source_c_sha256']
    assert d['build_identities']['before']==d['build_identities']['after']
    assert b'pr13_'not in read('original-Submission.c')
    assert json.loads(read('config.json'))==d['config']
    assert len(d['executions'])==6 and [(e['seed'],e['process'])for e in d['executions']]==[(s,p)for s in SEEDS for p in range(2)]
    assert [s['seed']for s in d['seeds']]==list(SEEDS)
    # Frozen R12 index exposes exactly these already seen plans, excluding all new holdouts.
    oldindex=REPO/'competitions/floatlib/candidates/f01-d7-research/round6h-20261024T051445Z/public-index-at-adoption.json'
    old=json.loads(oldindex.read_bytes());oldplans={};old_receipts=[]
    for seed in SEEDS:
        rs=[r for r in old['records']if r.get('kernel_sha256')==w.SOURCE and r.get('seed')==seed]
        assert len(rs)==1
        rec=rs[0];runroot=REPO/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'/str(rec['run'])
        check=m.Originals(runroot/'original-artifact-hashes.json')
        path=(REPO/rec['verdict']).parent/'public-drawn-plan.json'
        oldplans[seed]=json.loads(check.read(path));old_receipts.append({'seed':seed,'run':rec['run'],'plan_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),
            'index_sha256':hashlib.sha256(check.path.read_bytes()).hexdigest()})
    seeds=[]
    for data in d['seeds']:
        seed=data['seed'];plan=data['plan'];assert plan==oldplans[seed]
        assert len(plan['cases'])==156 and len({c['name']for c in plan['cases']})==156 and data['cases']==156
        assert json.loads(read(f'seed-{seed}-plan.json'))==plan
        compact=json.dumps(plan,separators=(',',':'))
        assert hashlib.sha256(compact.encode()).hexdigest()==data['plan_compact_sha256']
        assert data['same_seed_checksums_match']is True and [p['process']for p in data['processes']]==[0,1]
        for p in data['processes']:
            number=p['process'];name=f'seed-{seed}-process-{number}';raw=read(name+'.log');rows=w.bench_rows(raw.decode(),plan)
            assert rows==p['rows']==json.loads(read(name+'-rows.json'))
            assert hashlib.sha256(raw).hexdigest()==p['log_sha256']
            e=next(e for e in d['executions']if e['seed']==seed and e['process']==number)
            assert e['name']==name and e['exit_code']==0 and e['log_sha256']==p['log_sha256']
            env=e['environment'];assert env['BENCH_SEED']==str(seed)and env['BENCH_INNER']=='3'and env['BENCH_PAIRS']=='500000'
            assert json.loads(env['BENCH_PLAN'])==plan
        w.verify_same_seed(data['processes'][0]['rows'],data['processes'][1]['rows'])
        assert json.loads(read(f'seed-{seed}-result.json'))==data
        cases=[]
        for c in plan['cases']:
            rows=[p['rows'][c['name']]for p in data['processes']]
            times=[r['best_ns']for r in rows];route=m.classify(c)
            cases.append({'name':c['name'],'kernel':c['kernel'],'cell':':'.join(c['name'].split(':')[:2]),'timed':c['timed'],
                'shape':{k:c[k]for k in ('batch','m','n','p','length','work')},'route':route,
                'whole_best_ns_processes':times,'whole_process_mean_ns':statistics.mean(times),'same_seed_checksum':rows[0]['checksum'],
                'output_elements':c['batch']*c['m']*c['p']if c['kernel']=='bmm'else None})
        timed=[c for c in cases if c['timed']];total=sum(c['whole_process_mean_ns']for c in timed)
        optotals={k:sum(c['whole_process_mean_ns']for c in timed if c['kernel']==k)for k in ('add','mul','sum','bmm')}
        def group(rows):
            amount=sum(c['whole_process_mean_ns']for c in rows)
            return {'cases':len(rows),'whole_process_mean_ns_sum':amount,'whole_share':amount/total,
                'BMM_share':amount/optotals['bmm']if rows and all(c['kernel']=='bmm'for c in rows)else None,
                'process_ns_sums':[sum(c['whole_best_ns_processes'][p]for c in rows)for p in range(2)],
                'case_names':[c['name']for c in rows]}
        operations={k:group([c for c in timed if c['kernel']==k])for k in optotals}
        cells={k:group([c for c in timed if c['cell']==k])for k in sorted({c['cell']for c in timed})}
        routes={k:group([c for c in timed if c['kernel']=='bmm'and c['route']['route']==k])for k in sorted({c['route']['route']for c in timed if c['kernel']=='bmm'})}
        n1shape=[c for c in timed if c['kernel']=='bmm'and c['shape']['n']==1 and c['shape']['p']>2]
        n1=[c for c in n1shape if c['route']['route']=='DirectContinuous']
        cross=[c for c in timed if c['kernel']=='bmm'and c['route']['route']=='Cross']
        crossn1=[c for c in cross if c['shape']['n']==1]
        def shapes(rows):
            return {**group(rows),'shape_ranges':{k:[min(c['shape'][k]for c in rows),max(c['shape'][k]for c in rows)]if rows else None for k in ('batch','m','n','p')},
                'output_elements_range':[min(c['output_elements']for c in rows),max(c['output_elements']for c in rows)]if rows else None,
                'cases_by_output_elements_desc':[{'name':c['name'],'shape':c['shape'],'route':c['route']['route'],
                    'outputs':c['output_elements'],'whole_process_mean_ns':c['whole_process_mean_ns'],
                    'whole_share':c['whole_process_mean_ns']/total,'BMM_share':c['whole_process_mean_ns']/optotals['bmm']}for c in sorted(rows,key=lambda c:-c['output_elements'])]}
        seeds.append({'seed':seed,'cases':cases,'timed_cases':len(timed),'whole_process_mean_ns_sum':total,
            'operations':operations,'cells':cells,'BMM_routes':routes,'n1_p_gt2_shape':shapes(n1shape),'n1_DirectContinuous_effective':shapes(n1),
            'p2_Cross_all':shapes(cross),'p2_Cross_n1':shapes(crossn1),
            'high_output_definition':'No arbitrary cutoff: report all source-eligible p2 Cross output-element ranges, and n1 subset separately.',
            'top_BMM_cases':sorted([c for c in timed if c['kernel']=='bmm'],key=lambda c:-c['whole_process_mean_ns'])[:5]})
    for name in original.files:original.read(original.root/name)
    def ranges(section,key,metric='whole_share'):
        vals=[s[section].get(key,{}).get(metric,0)for s in seeds]
        return {'by_seed':dict(zip(SEEDS,vals)),'min':min(vals),'max':max(vals)}
    variation={'operation_whole_shares':{k:ranges('operations',k)for k in ('add','mul','sum','bmm')},
        'BMM_route_BMM_shares':{k:ranges('BMM_routes',k,'BMM_share')for k in sorted({k for s in seeds for k in s['BMM_routes']})},
        'n1_DirectContinuous_whole_shares':{s['seed']:s['n1_DirectContinuous_effective']['whole_share']for s in seeds},
        'p2_Cross_whole_shares':{s['seed']:s['p2_Cross_all']['whole_share']for s in seeds}}
    output={'state':'VALIDATED_EXPOSED_WHOLE_DIAGNOSTIC','diagnostic_only':True,'run':40099316795,'exactDF':w.SOURCE,
        'actual_seeds':list(SEEDS),'seed_cases':468,'whole_row_observations':936,'checksums_compared_only_same_seed':True,
        'seeds':seeds,'cross_seed_variation':variation,
        'evidence':{'result_sha256':hashlib.sha256(read('result.json')).hexdigest(),'index_sha256':hashlib.sha256(original.path.read_bytes()).hexdigest(),
            'original_file_count':len(original.checked),'original_files':original.checked,'frozen_R12_index_sha256':hashlib.sha256(oldindex.read_bytes()).hexdigest(),
            'previously_exposed_original_plans':old_receipts,'build_identity':d['build_identities'],'config':d['config'],
            'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()},
        'interpretation':['Per-case arithmetic mean across two complete uninstrumented processes; each original row is best of3 sweeps after checksum/warmup. Shares describe this diagnostic workload, not an official score.',
            'All three plans equal their original already exposed R12 plan bytes as parsed; no new holdout is generated or read.',
            'Routes use the prior verified literal BenchSuite.element source model, not machine branch traces.',
            'N1 DirectContinuous affects only its n1/p>2 effective path; Cross n1, general DirectContinuous n2..4, DirectSmall, RowStream and Underflow routes remain outside it.',
            'Cross fusion affects p2 Cross materialization, not all BMM shapes or all its prep/compute. RowStream-only changes omit the other routes.',
            'Different-seed checksums are not compared. Same runner/shared binary and only two processes are diagnostic, not independent performance confirmation or candidate benefit.']}
    dest=HERE/'profile-whole-multi-analysis-40099316795.json';assert not dest.exists()
    dest.write_text(json.dumps(output,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':output['state'],'sha256':hashlib.sha256(dest.read_bytes()).hexdigest(),'files':len(original.checked),'seed_cases':468,'row_observations':936,'variation':variation}))


if __name__=='__main__':run()
