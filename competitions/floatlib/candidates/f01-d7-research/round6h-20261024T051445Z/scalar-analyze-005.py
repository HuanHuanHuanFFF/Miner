"""Exact005 full-gate discovery and actual59de MainFull mechanism analysis."""
from pathlib import Path
import hashlib,importlib.util,json,random,re,statistics

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40071334389'
OLD=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40067286343/download-5936990717ed4c0996f1c31b985d1aa3/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-combined-classifier/capture-ad2a97ee7ace4c67983e4c060817926c'
CANDIDATE='f01-d12-mul-existing-convert'
BASE='f01-d11-bmm-combined-classifier'
CONTROL='f01-r8-combined-result-guard'
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m


def asm_body(raw,name):
    match=re.search(r'^[0-9a-f]+ <'+re.escape(name)+r'>:\n.*?(?=\nDisassembly of section|\Z)',raw.decode(),re.M|re.S)
    assert match,name
    return match.group(0).strip().encode()


def main():
    index=json.loads((RUN/'original-artifact-hashes.json').read_bytes())
    directory=RUN/index['directory'];assert directory.resolve().is_relative_to(RUN.resolve())
    guard=load(HERE.parent/'adoption-guard.py','r12_005_guard')
    p=guard.load_run(ROOT,HERE.parent,40071334389,(CANDIDATE,BASE,CONTROL))
    verdicts=p['verdicts'];assert all(v['passed'] and v['stage']=='score' and len(v['rounds'])==25 for v in verdicts.values())
    relative=verdicts[CANDIDATE]['ratio']/verdicts[BASE]['ratio']
    values=[[s/i for i,s in verdicts[n]['rounds']]for n in (CANDIDATE,BASE)]
    rng=random.Random(90423)
    gains=sorted(1-statistics.median(values[0][rng.randrange(25)]for _ in range(25))/statistics.median(values[1][rng.randrange(25)]for _ in range(25)) for _ in range(2000))
    k=.05*1999;lo=int(k);p05=gains[lo]+(gains[lo+1]-gains[lo])*(k-lo)
    operations={};cells={}
    for op in ('add','mul','sum','bmm'):
        sums={n:{kind:sum(v['classes'][c][kind+'_ns']*w for c,w in p['cell_work'].items() if c.startswith(op+':'))for kind in ('submission','incumbent')}for n,v in verdicts.items()}
        operations[op]={'normalized_candidate_over_6c':(sums[CANDIDATE]['submission']/sums[CANDIDATE]['incumbent'])/(sums[BASE]['submission']/sums[BASE]['incumbent']), 'weighted_ns':sums}
    for cell in p['cell_work']:
        cells[cell]=verdicts[CANDIDATE]['classes'][cell]['ratio']/verdicts[BASE]['classes'][cell]['ratio']
    capture_names=[name for name in index['files'] if '/codegen/'+CANDIDATE+'/' in name and name.endswith('/capture-record.json')]
    assert len(capture_names)==1
    capture=directory/Path(capture_names[0]).parent
    capture_raw=(capture/'capture-record.json').read_bytes();record=json.loads(capture_raw)
    assert sha(capture_raw)==index['files'][capture_names[0]]['sha256']
    assert record['state']==record['snapshot']['state']=='CAPTURED' and record['kernel_sha256']==p['kernel_hashes'][CANDIDATE]
    assert sha((capture/'compiled-Submission.lean').read_bytes())==p['kernel_hashes'][CANDIDATE]
    for item in record['snapshot']['files']:
        data=(capture/item['artifact']).read_bytes();assert len(data)==item['bytes'] and sha(data)==item['sha256']
    assert record['private_objects_removed'] and record['private_directory_removed']
    main_obj=next(o for o in record['disassembly']['objects']if o['module']=='MainFull')
    asm={r['symbol']:r for r in main_obj['symbols']}
    for symbol in ('lp_competition_main___lam__0','lp_competition_main___lam__3','lp_competition_main___lam__3___boxed','_lean_main'):
        assert symbol in asm
        assert sha((capture/asm[symbol]['assembly']['artifact']).read_bytes())==asm[symbol]['assembly']['sha256']
    parser=load(HERE/'scalar-analyze-mainfull.py','r12_c_function_parser')
    current_c=(capture/'file-0-MainFull.c').read_bytes();old_c=(OLD/'file-0-MainFull.c').read_bytes()
    functions={name:parser.function(current_c,name)for name in ('lp_competition_main___lam__0','lp_competition_main___lam__3','lp_competition_main___lam__3___boxed','_lean_main')}
    add_c_equal=functions['lp_competition_main___lam__0']['sha256']==parser.function(old_c,'lp_competition_main___lam__0')['sha256']
    add_asm_equal=asm_body((capture/'asm-0-0.txt').read_bytes(),'lp_competition_main___lam__0')==asm_body((OLD/'asm-0-0.txt').read_bytes(),'lp_competition_main___lam__0')
    assert add_c_equal and add_asm_equal
    report={'run':40071334389,'seed':p['seed'],'source_commit':p['evidence']['source_commit'],
        'kernel_hashes':p['kernel_hashes'],'all_three_original_full_gate25':'PASS','evidence':p['evidence'],
        'normalization':'Separate original paired candidate/reference gates. Normalize candidate/reference by6c/reference; no direct candidate/6c paired-run claim.',
        'relative_normalized_ratio':relative,'gain_p05':p05,'bootstrap':{'samples':2000,'seed':90423,'statistic':'median of25 paired sub/ref ratios, independently resampled across candidate/6c gates'},
        'numerical_discovery_threshold':relative<=.97 and p05>0,'observer_present':p['codegen_present'],
        'eligible_clean_D':False,'adoption':'NOT_ADOPTED; original observer discovery cannot serve cleanD or frozen confirmation',
        'per_operation':operations,'per_cell_normalized':cells,'current6c_estimator_model':'UNCHANGED; no model/dashboard write',
        'capture_record_sha256':sha(capture_raw),'capture_directory':capture.relative_to(ROOT).as_posix(),
        'MainFull_c_sha256':sha(current_c),'MainFull_object_sha256':main_obj['object_sha256'],
        'MainFull_objects_and_asm':main_obj,'functions':functions,
        'all_capture_C_trace_bytes_rehashed':True,'exact_compiled_source_rehashed':True,'private_ELF_removed':True,
        'actual_public_dispatch':'BENCH_PLAN still passes closed1/add lam0 and closed5/mul lam3 to Bench.Suite.run; lambda1 is legacy non-plan.',
        'warm_numeric_path':{'verified':'exsum>=128, both existing converters choose numeric. Actual lam3 path0x26→0x1e5→0x20b→0x27c→0x2a5 uses twoUInt32 casts and two signed scale-table multiplies, then native multiply/ucomiss. No of_bits call or float spill/reload is executed on this path.',
            'retained_costs':'Per-input window checks, table loads, scale multiplies, prologue register saves/16B stack reservation and result to_bits tail0x2be remain.',
            'bounded_scope':'Not every call takes this path. of_bits fallback relocations remain0x4d/0x233; second-input fallback retains float spill/reload0x22c/0x237.'},
        'LowScale':'The exsum<128 branch remains at0x24→0x59 before any new converter guard; all source LowScale definitions and old tiny routing are unchanged. Actual prologue/register allocation differs, so binary-level whole-path cost is not inherited.',
        'add_control':{'C_body_identical':add_c_equal,'selected_asm_body_identical':add_asm_equal,
            'observed_normalized_ratio':operations['add']['normalized_candidate_over_6c'],
            'meaning':'Unchanged add also moved by about2.36percent; environmental/reference/layout variation remains. Do not attribute full whole gain solely to the converter from one observer sample.'},
        'mechanism_conclusion':'Observed active warm branch removes the two input bitcast calls and their float spill. Mul all7cells improved in this sample; full net gain has supporting discovery evidence but needs original no-observer cleanD plus frozen independent groups.',
        'next_action':'Root should validate exact59de without any observer under original complete full gate and the existing6c/41 controls. Do not alter candidate or add variants from this favorable sample.'}
    (HERE/'scalar-005-analysis.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'relative':relative,'p05':p05,'observer':p['codegen_present'],'clean_D':False,
        'MainFull_C':sha(current_c),'object':main_obj['object_sha256'],'lam3_bytes':asm['lp_competition_main___lam__3']['size_bytes'],
        'add_C_and_asm_unchanged':add_c_equal and add_asm_equal,'function_ranges':functions},indent=2))


if __name__=='__main__':
    main()
