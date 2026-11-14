"""Rebuild the final shared-operand pilot ratios from original native logs."""
from pathlib import Path
from collections import defaultdict
from statistics import median
import datetime
import hashlib
import json
import math

HERE=Path(__file__).resolve().parent
ROUND=HERE.parent
RESULT=ROUND/'ci-runs/40811305126/download-daa0fb1a3e304ebd8555ece28d2d6dab/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-dot-bank-cost2/runtime-cost/result.json'
SOURCE='b2855ceccccde7f8416a6210a635a3785107b010a12d009f29292607c9c580e8'
ORDER=['exact','eager','eager','exact','exact','lazy','lazy','exact']


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    result=json.loads(RESULT.read_bytes())
    assert result['complete'] and result['originals_unchanged'] and result['source_sha256']==SOURCE
    assert len(result['runs'])==16 and result['native_oracle_exit_code']==0
    oracle=result['native_oracle']
    assert oracle['cases']==6 and oracle['output_words']==464 and oracle['backends']==3
    assert oracle['bank_sum_checks']==18 and oracle['all_case_sums_match']
    tables={};logs=[];raw_samples=0
    for run in result['runs']:
        g,b,o,v=str(run['group']),run['boundary'],run['order'],run['variant']
        assert run['exit_code']==0 and b=='full' and ORDER[o]==v
        assert run['argv'][:3]==['taskset','-c','0']
        path=RESULT.parent/f'{g}-{b}-{o}-{v}.log'
        assert sha(path)==run['log_sha256']
        rows=defaultdict(dict)
        for line in path.read_text(encoding='utf-8').splitlines():
            f=line.split('\t')
            if f[0]!='BANK_SAMPLE':continue
            assert len(f)==13
            _,name,group,variant,boundary,trial,work,iters,macs,ns,sink,expected,keep=f
            assert (group,variant,boundary)==(g,v,b)
            trial,work,iters,macs,ns,sink,expected,keep=map(int,(trial,work,iters,macs,ns,sink,expected,keep))
            assert trial not in rows[name] and work*iters==macs and ns>0 and sink==expected
            cached=next(s for s in run['rows'][name]['samples'] if s['trial']==trial)
            assert (work,iters,macs,ns,sink,expected,keep)==tuple(cached[k] for k in ('work','iters','actual_macs','ns','sink','expected_sink','keep_word'))
            rows[name][trial]=ns;raw_samples+=1
        assert len(rows)==3 and set(rows)==set(run['rows'])
        table={}
        for name,values in rows.items():
            assert set(values)=={0,1,2}
            table[name]=median(values.values())
            assert table[name]==run['rows'][name]['median_ns']
        tables[(g,o)]=table
        logs.append({'path':path.relative_to(ROUND).as_posix(),'sha256':sha(path)})
    assert set(tables)=={(g,o) for g in ('24282601','24282603') for o in range(8)}
    ratios=[]
    for pair in result['paired']['pairs']:
        control=tables[(pair['group'],pair['control_order'])]
        variant=tables[(pair['group'],pair['candidate_order'])]
        assert set(control)==set(variant)
        ratio=sum(variant.values())/sum(control.values())
        assert math.isclose(ratio,pair['ratio'],rel_tol=1e-14)
        per_case={n:variant[n]/control[n] for n in control}
        assert {n for n in control if variant[n]>control[n]}=={x['name'] for x in pair['regressions']}
        for n,r in per_case.items():assert math.isclose(r,pair['per_case'][n]['ratio'],rel_tol=1e-14)
        ratios.append({'group':pair['group'],'variant':pair['variant'],'replicate':pair['replicate'],'ratio':ratio,'per_case':per_case})
    assert raw_samples==144 and len(ratios)==8
    eager=[x['ratio'] for x in ratios if x['variant']=='eager']
    lazy=[x['ratio'] for x in ratios if x['variant']=='lazy']
    receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
             'status':'PASS_INDEPENDENT_RAW_RECONSTRUCTION_NUMERIC_ONLY',
             'workflow_run':40811305126,'source_sha256':SOURCE,'result_sha256':sha(RESULT),
             'processes':16,'raw_ns_values':raw_samples,'paired_records':8,
             'native_finite_checks':oracle,'eager_ratios':eager,'lazy_ratios':lazy,
             'eager_elapsed_reduction_range':[1-max(eager),1-min(eager)],
             'lazy_elapsed_reduction_range':[1-max(lazy),1-min(lazy)],
             'ratios':ratios,'original_logs':logs,
             'boundary':'Whole synthetic bank call with resident raw input arrays; prepares each main operand once, produces/observes/releases all output words inside each native iteration. Lazy misses still prepare exact operands per output pair.',
             'scope':'Two fixed seed groups, three shapes: rows4/cols8/dot32, rows6/cols12/dot64, rows8/cols16/dot128. Compared with own word64/128 control, not official BMM, former2, or current champion.',
             'limits':['Same-run exploratory diagnostic, not frozen independent new-runner confirmation.',
                       'Whole runtime correctness remains UNPROVED; finite word checks are not a proof.',
                       'No whole-model/official score, formal adoption, policy share or reward conclusion.',
                       'Independent D audits cover C/ASM/caller/flags; this receipt rebuilds raw numbers and keeps their separate scope.']}
    (HERE/'bank-cost-independent-review.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({k:receipt[k] for k in ('status','processes','raw_ns_values','eager_elapsed_reduction_range','lazy_elapsed_reduction_range')}))


if __name__=='__main__':main()
