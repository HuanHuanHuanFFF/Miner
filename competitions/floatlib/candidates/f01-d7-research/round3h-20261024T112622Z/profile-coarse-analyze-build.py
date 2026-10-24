"""Independent coarse reader derived from the frozen, validated fine reader."""
from pathlib import Path
import hashlib
HERE=Path(__file__).resolve().parent
BASE='76a91231e8d8b1f2b3b3e010d10524de37298fea5f16b9cadfabdf5211866ea4'
COARSE='a61018514107d585cfd23c1a240f07177092d2d858bc829836703fbc98868529'
CATS=('whole_bmm','whole_sum','rowstream_amap','rowstream_bpack','rowstream_scope',
    'cross_words','cross_scope','direct_continuous','direct_small','underflow_fill')

SUMMARY='''def summarize(d):
    cases=[];groups=collections.defaultdict(list)
    for item in d['cases']:
        c=item['case'];route=classify(c);measurements=item['profile_measurements']
        exc={cat:statistics.mean(r['stages_all_checksum_and_timed_sweeps'][cat]['exclusive_ns']for r in measurements)for cat in CATEGORIES}
        inc={cat:statistics.mean(r['stages_all_checksum_and_timed_sweeps'][cat]['inclusive_ns']for r in measurements)for cat in CATEGORIES}
        counts={cat:[r['stages_all_checksum_and_timed_sweeps'][cat]['calls']for r in measurements]for cat in CATEGORIES}
        pure=sum(exc.values());anchor=item['original_whole_row']['best_ns']
        whole=[r['benchmark_row']['best_ns']for r in measurements]
        row={'name':c['name'],'kernel':c['kernel'],'official_cell':':'.join(c['name'].split(':')[:2]),'timed':c['timed'],
            'route':route,'work':c['work'],'original_whole_row':item['original_whole_row'],
            'profile_whole_rows':[r['benchmark_row']for r in measurements],
            'profile_vs_original_context_and_instrumentation_ratio':statistics.mean(whole)/anchor if anchor else None,
            'profile_vs_original_process_ratios':[n/anchor for n in whole]if anchor else None,
            'boundary_call_counts':counts,'inclusive_ns_mean_per_profile_process':inc,
            'exclusive_ns_mean_per_profile_process':exc,'measured_pure_root_ns_mean_per_process':pure,
            'exclusive_fraction_of_instrumented_pure_root':{k:v/pure if pure else None for k,v in exc.items()},
            'coarse_intervals':{'cross_words_prepare_compute_repair':inc['cross_words'],
                'cross_core_exclusive_output_and_cleanup':exc['cross_scope'],
                'rowstream_Amap_complete':inc['rowstream_amap'],'rowstream_packB_complete':inc['rowstream_bpack'],
                'rowstream_exclusive_compute_output_cleanup':exc['rowstream_scope'],
                'direct_continuous_complete_compute_output':inc['direct_continuous']},
            'inseparable_cost':'UNKNOWN: fused prep/compute, conversion/allocation/fill, compute/output and timer/layout/context costs are not separated.'}
        cases.append(row)
        groups['route:'+route['route']].append(row);groups['cell:'+row['official_cell']].append(row)
        groups['kernel:'+c['kernel']].append(row)
    summary={}
    for key,allrows in sorted(groups.items()):
        summary[key]={}
        for label,rows in [('timed',[r for r in allrows if r['timed']]),('untimed',[r for r in allrows if not r['timed']])]:
            exc={cat:sum(r['exclusive_ns_mean_per_profile_process'][cat]for r in rows)for cat in CATEGORIES};pure=sum(exc.values())
            inc={cat:sum(r['inclusive_ns_mean_per_profile_process'][cat]for r in rows)for cat in CATEGORIES}
            anchor=sum(r['original_whole_row']['best_ns']for r in rows)
            whole=sum(statistics.mean(n['best_ns']for n in r['profile_whole_rows'])for r in rows)
            ratios=[r['profile_vs_original_context_and_instrumentation_ratio']for r in rows if r['profile_vs_original_context_and_instrumentation_ratio']is not None]
            summary[key][label]={'cases':len(rows),'original_whole_best_ns_sum':anchor,
                'profile_whole_case_process_means_ns_sum':whole,
                'profile_vs_original_context_and_instrumentation_ratio':{'sum_ratio':whole/anchor if anchor else None,
                    'case_median':statistics.median(ratios)if ratios else None,'case_min':min(ratios)if ratios else None,'case_max':max(ratios)if ratios else None},
                'inclusive_ns_sum_of_per_case_process_means':inc,
                'exclusive_ns_sum_of_per_case_process_means':exc,
                'exclusive_fraction_of_instrumented_pure_roots':{k:v/pure if pure else None for k,v in exc.items()}}
    return {'diagnostic_only':True,'formal_score_prediction':None,'case_count':len(cases),'cases':cases,'groups':summary,
        'interpretation':{'whole':'Original fastest sweep includes caller checksum and cleanup; stages aggregate warmup + three timed sweeps in two separate processes.',
            'disturbance':'Profile/original ratios combine timer, compiler/layout, process/cache and system context. They are not isolated timer-overhead estimates or candidate speedups.',
            'cross':'words inclusive combines preparation, packets, compute and repair; core exclusive covers output materialization and cleanup outside words.',
            'rowstream':'Amap and packB are complete low-frequency outer helpers. RowStream scope exclusive combines all remaining compute, output and cleanup.',
            'direct':'DirectContinuous and DirectSmall are complete compute/output scopes. No per-row or per-output timers exist.',
            'conversion':'Amap/packB include allocation, fill and conversion; none of their duration is an established removable-cost upper bound.',
            'fractions':'Nested-exclusive fractions refer only to instrumented pure-root durations of this workload, never official-score shares.',
            'route':'SOURCE_MODEL from exact generator words + frozen DF control flow; no per-branch machine trace.',
            'unknown':'Unseparated work and missing/unexecuted boundaries remain UNKNOWN; no official-score or champion multiplier is estimated.'}}


'''


def build():
    raw=(HERE/'profile-analyze.py').read_bytes();assert hashlib.sha256(raw).hexdigest()==BASE
    text=raw.decode()
    text=text.replace("MODULE='0b973c9c309b4e86d8e0576a32873ab097a41a1db3b45c1600f3892ac538a334'",'MODULE='+repr(COARSE))
    old="CATEGORIES=('whole_bmm','whole_sum','amap','bpack','cross_prepare','compute','output','repair','dispatch_scan')"
    assert text.count(old)==1;text=text.replace(old,'CATEGORIES='+repr(CATS))
    text=text.replace("PREFIX='profile-r13-'","PREFIX='profile-r13-coarse-'")
    text=text.replace('FL13','FC13').replace('0<=c<9','0<=c<len(CATEGORIES)').replace('range(9)','range(len(CATEGORIES))')
    text=text.replace("'profile-current.py'","'profile-coarse-current.py'")
    text=text.replace("r['category']=='amap'","r['category']=='rowstream_amap'")
    start=text.index('def summarize(d):');end=text.index('def analyze(',start)
    text=text[:start]+SUMMARY+text[end:]
    old="            require(sum(v['exclusive_ns']for v in stages.values())==root_ns,'exclusive partition does not equal measured pure roots')"
    assert text.count(old)==1
    text=text.replace(old,old+"\n            require(all(stages[cat]['calls']<=bmm for cat in CATEGORIES[2:]),'coarse boundary called per output/packet')")
    old="    original=Originals(index_path);result_path=Path(result_path).resolve();folder=result_path.parent"
    assert text.count(old)==1
    text=text.replace(old,old+"\n    require(result_path.name==PREFIX+'result.json','not coarse data: fine profile explicitly rejected')")
    text=text.replace('Read-only exactDF R13 profile validation and diagnostic cost distributions.',
        'Read-only exactDF R13 COARSE profile validation and complete-call disturbance.')
    (HERE/'profile-coarse-analyze.py').write_bytes(text.encode())
    print(hashlib.sha256(text.encode()).hexdigest())


if __name__=='__main__':build()
