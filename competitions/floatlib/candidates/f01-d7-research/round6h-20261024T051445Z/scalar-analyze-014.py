"""Read-only014 None-native original-gate/codegen audit; preserve PARK decision."""
from pathlib import Path
import hashlib,importlib.util,json,random,re,statistics

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40078982864'
NEW='f01-d12-none-native-result';PARENT='f01-d12-scalar-combined';BASE='f01-d11-bmm-combined-classifier'
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def load(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m


def main():
    index_raw=(RUN/'original-artifact-hashes.json').read_bytes();idx=json.loads(index_raw);directory=RUN/idx['directory']
    guard=load(HERE.parent/'adoption-guard.py','r12_014_guard')
    p=guard.load_run(ROOT,HERE.parent,40078982864,(NEW,PARENT,BASE,'f01-r8-combined-result-guard'))
    vs=p['verdicts'];assert all(v['passed'] and v['stage']=='score' and len(v['rounds'])==25 for v in vs.values())
    def compare(baseline):
        values=[[s/i for i,s in vs[n]['rounds']]for n in (NEW,baseline)];rng=random.Random(90423)
        gains=sorted(1-statistics.median(values[0][rng.randrange(25)]for _ in range(25))/statistics.median(values[1][rng.randrange(25)]for _ in range(25))for _ in range(2000))
        k=.05*1999;lo=int(k);p05=gains[lo]+(gains[lo+1]-gains[lo])*(k-lo)
        ops={};cells={}
        for op in ('add','mul','sum','bmm'):
            sums={n:{kind:sum(vs[n]['classes'][c][kind+'_ns']*w for c,w in p['cell_work'].items()if c.startswith(op+':'))for kind in ('submission','incumbent')}for n in (NEW,baseline)}
            ops[op]=(sums[NEW]['submission']/sums[NEW]['incumbent'])/(sums[baseline]['submission']/sums[baseline]['incumbent'])
        for name in p['cell_work']:
            c,b=vs[NEW]['classes'][name],vs[baseline]['classes'][name]
            cells[name]={'normalized':c['ratio']/b['ratio'],'raw_submission':c['submission_ns']/b['submission_ns'],
                'raw_reference':c['incumbent_ns']/b['incumbent_ns']}
        return {'whole_normalized':vs[NEW]['ratio']/vs[baseline]['ratio'],'gain_p05':p05,'per_operation':ops,'per_cell':cells}
    paths=[name for name in idx['files']if '/codegen/'+NEW+'/'in name and name.endswith('/capture-record.json')];assert len(paths)==1
    folder=directory/Path(paths[0]).parent;files={}
    for path in sorted(folder.iterdir()):
        if path.is_file():
            raw=path.read_bytes();key=path.relative_to(directory).as_posix();expected=idx['files'][key]
            assert len(raw)==expected['bytes']and sha(raw)==expected['sha256']
            files[path.name]={'sha256':sha(raw),'bytes':len(raw),'original_index_match':True}
    record=json.loads((folder/'capture-record.json').read_bytes());assert record['state']==record['snapshot']['state']=='CAPTURED'
    assert record['kernel_sha256']==p['kernel_hashes'][NEW]=='42c76db28de3b6239dcfddcf17ae7ebec6d06e54b4f5cd7c0ac818c7f8ce4d0a'
    assert sha((folder/'compiled-Submission.lean').read_bytes())==record['kernel_sha256']
    assert record['private_objects_removed']and record['private_directory_removed']
    main_obj=next(o for o in record['disassembly']['objects']if o['module']=='MainFull')
    asm={s['symbol']:s for s in main_obj['symbols']}
    for name in ('lp_competition_main___lam__0','lp_competition_main___lam__3','lp_competition_main___lam__0___boxed','lp_competition_main___lam__3___boxed','_lean_main'):
        assert name in asm and asm[name]['assembly']['ok']
    parser=load(HERE/'scalar-analyze-mainfull.py','r12_014_c_parser')
    source=(folder/'file-0-MainFull.c').read_bytes()
    functions={n:parser.function(source,n)for n in ('lp_competition_main___lam__0','lp_competition_main___lam__3','_lean_main')}
    # Extract only the selected text body, not the empty section headers emitted
    # for all other functions by objdump --disassemble.
    def body(file,symbol):
        raw=(folder/file).read_text();match=re.search(r'^[0-9a-f]+ <'+re.escape(symbol)+r'>:\n.*?(?=\nDisassembly of section|\Z)',raw,re.M|re.S)
        assert match;return match.group(0)
    add=body('asm-0-0.txt','lp_competition_main___lam__0');mul=body('asm-0-2.txt','lp_competition_main___lam__3')
    assert 'addss' in add and 'ucomiss' in add and 'lean_float32_to_bits' in add
    assert 'mulss' in mul and 'ucomiss' in mul and 'lean_float32_to_bits' in mul
    assert 'mi_malloc'not in add and 'lean_alloc'not in add and 'mi_malloc'not in mul and 'lean_alloc'not in mul
    increment=compare(PARENT);primary=compare(BASE)
    report={'state':'PARK_NO_RELIABLE_INCREMENT','run':40078982864,'seed':p['seed'],'source_commit':p['evidence']['source_commit'],
        'evidence':p['evidence'],'original_artifact_index_sha256':sha(index_raw),'kernel_hashes':p['kernel_hashes'],
        'all_four_original_full25':'PASS','observer_present':p['codegen_present'],'increment_vs_same_run_df5c':increment,
        'primary_vs6c_not_increment':primary,'normalization':'Separate original paired sub/reference gates normalized by baseline/reference; no direct new/parent paired sweeps and no cross-seed component addition.',
        'capture_directory':folder.relative_to(ROOT).as_posix(),'capture_files_rehashed':files,'capture_record_sha256':files['capture-record.json']['sha256'],
        'exact_compiled_source_rehashed':True,'private_ELF_removed':True,'final_link_bytes':'UNKNOWN_NOT_RETAINED',
        'MainFull_object_sha256':main_obj['object_sha256'],'MainFull_C_sha256':sha(source),'functions':functions,
        'MainFull_selected_symbols':main_obj['symbols'],'MainFull_missing_symbols':main_obj['omitted_symbols'],
        'public_dispatch':'BENCH_PLAN→closed1 add lam0 boxed / closed5 mul lam3 boxed→Bench.Suite.run. Legacy lam1 is not the public mul entry.',
        'actual_add':{'size_bytes':asm['lp_competition_main___lam__0']['size_bytes'],
            'warm':'Existing numeric input conversions or of_bits fallbacks, addss0xbb, self-ucomiss0xbf and nonNaN branch0xc4→to_bits tail0xce.',
            'Some':'NaN branch0xd2 performs raw integer signaling/quiet priority and returns original selectedword|quietbit at0x135/0x158. No Option allocation or generic software add call remains in this actual MainFull body.',
            'None':'No raw operand selected: branches0x133/0x152 return to0xc4 and reuse xmm1 already produced by addss. No second add/converter run occurs.',
            'spill':'Second-input of_bits miss retains float store/reload0x7c/0x87. Numeric/numeric hit has no float store/reload.'},
        'actual_mul':{'size_bytes':asm['lp_competition_main___lam__3']['size_bytes'],
            'warm':'LowScale gate0x24→0x61 still precedes converter guards. Numeric hit0x1eb/0x284 performs two scale products then one product0x2ad, self-ucomiss0x2b1, to_bits tail0x2ca.',
            'Some':'Raw priority at0x3fb returns right quietedword0x45e or left0x487; no Option allocation in captured body.',
            'None':'No rawNaN selected branches0x458/0x481 jump to0x2ba, reusing xmm1 product. No extra native multiply/conversions on this branch.',
            'spill':'Second-input of_bits miss retains float store/reload0x234/0x23f. Numeric/numeric hit has no float spill. FiveGP callee-saved pushes and16B stack reservation remain.',
            'remaining_backend':'The full function still has a softwareMul backend relocation0x25c inside unchanged LowScale machinery. Do not say all generic backend work disappeared.'},
        'parent_machine_comparison':'UNKNOWN: this run captured42c only. The same-run df5c MainFull C/object/asm was not captured. Older59de/6c code is a different source/control and cannot establish a new spill or size delta attributable solely to None.',
        'controls_boundary':'sum dense/ml/sparse/extremes improveabout4.6–5.4percent despite never executing newNone return. First rawNaN sum repair always selectsSome. These movements cannot be called None execution savings; layout/system/compilation effects and tensor-caller assembly are UNKNOWN. Non-special mul cells regressabout0.1–2.3percent.',
        'tensor_callees':'CapturedSubmission C/nm remains available but the20symbol scalar budget omitted tensor-helper machine bodies. No claim about actualR7SinglePassSum/replay caller spills, branch cycles or prefix costs is inferred from the standalone MainFull body.',
        'proof_asset':'Exact42c complete gate accepted the full rawNone→ModelNone→native inputs nonNaN→R7Native/roundtrip chain with copied classifier proof; preserve it as an accepted mathematical/source asset.',
        'decision':'RootPARK confirmed: same-run whole0.995589 gain p05negative. Preserve proof and original failure/slow evidence; no extra None variant, sampling, fusion, source/helper/Git/CI mutation.'}
    (HERE/'scalar-014-none-analysis.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':report['state'],'files_rehashed':len(files),'increment_whole':increment['whole_normalized'],
        'increment_p05':increment['gain_p05'],'MainFull_C':sha(source),'MainFull_object':main_obj['object_sha256'],
        'MainFull_sizes':{n:asm[n]['size_bytes']for n in ('lp_competition_main___lam__0','lp_competition_main___lam__3')},
        'capture_missing_MainFull':main_obj['omitted_symbols'],'parent_asm':'UNKNOWN_NOT_CAPTURED'},indent=2))


if __name__=='__main__':main()
