"""One fixed-validator review of exact selected callbacks, flags, C/ASM and24 runs."""
from pathlib import Path
from collections import Counter
import hashlib,importlib.util,json,re,shlex,sys
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
ROUND=HERE.parent.parent
RUN=ROUND/'ci-runs/40774570580'
RAW=RUN/'download-ceaa12059ced42f6b5ce2ce97b97aff7'
COST=RAW/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-scalar-f64array-cost1/runtime-cost'
OLD=ROOT/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/development-outline-mul'
SOURCE='08a0208ec09eeb583f9d8e451234a4f5e29cfa75eaa90d525073b7296b5584a2'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def load(p,name):
    s=importlib.util.spec_from_file_location(name,p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def save(p,data):p.write_bytes((json.dumps(data,ensure_ascii=False,indent=2)+'\n').encode())
def norm_c(s):
    s=re.sub(r'\b(lp_competition_\w+)\(', 'FUNCTION(',s,count=1);names={}
    return re.sub(r'\bv_\w+\b',lambda m:names.setdefault(m[0],f'v{len(names)}'),s)
def main():
    artifact=json.loads((RUN/'original-artifact-hashes.json').read_bytes())
    head=artifact['artifact']['workflow_run']['head_sha'];assert head=='6f57a6ad59fa967db4d8c5f06afed7954ce4fec1'
    total=0
    for rel,item in artifact['files'].items():
        p=(RAW/rel).resolve();assert p.is_relative_to(RAW.resolve())
        assert p.stat().st_size==item['bytes'] and sha(p)==item['sha256'],rel
        total+=item['bytes']
    src=next(RAW/k for k in artifact['files'] if '/inputs/f01-r24-dev-scalar-f64array-cost1/Kernel.lean' in k)
    assert sha(src)==SOURCE
    assert src.read_bytes().startswith((ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes())
    d=load(HERE/'driver.py','r24_actual_driver')
    sa=load(HERE/'static_runner_audit.py','r24_actual_static_audit')
    inventory=load(OLD/'inventory_callbacks.py','r24_fixed_callback_inventory')
    cpath=COST/'actual-main-premeasurement.c';apath=COST/'own-object-0-asm.txt'
    assert sha(cpath)==sha(COST/'build-product-0-R24ScalarF64CostMain.c')
    assert sha(COST/'caller.lean')==sha(HERE/'R24ScalarF64CostMain.lean')
    c=cpath.read_bytes().decode();asm=apath.read_bytes().decode()
    wanted=('runControl','runF64Native','runF64Boxed','runF64Cast')
    pref=sa.audit_static_runners(cpath.read_bytes(),wanted=wanted)
    inv=inventory.inventory(cpath,apath)
    closures={x['constant']:x for x in inv['static_closures']}
    assert not inv['runtime_closures'] if 'runtime_closures' in inv else not inv.get('dynamic_closures',[])
    chains={};functions=inv['C_function_graph']
    for name in wanted:
        io=functions[pref['entries'][name]['symbol']];b=c[io['start']:io['end']]
        aliases=dict(re.findall(r'(?m)^(\w+) = \(\(lean_object\*\)\((\w+)\)\);$',b))
        calls=re.findall(r'lp_competition_Bench_Suite_run\(([^)]+)\)',b);assert len(calls)==1
        args=[x.strip() for x in calls[0].split(',')];assert len(args)==4
        chosen=[closures[aliases[x]] for x in args]
        box=chosen[0]['function'];typed=box.removesuffix('___boxed');f=functions[typed]
        assert chosen[0]['arity']==2 and chosen[0]['fixed']==0
        assert f['return_type']=='uint32_t' and re.fullmatch(r'uint32_t \w+, uint32_t \w+',f['parameters'])
        assert typed in functions[box]['calls']
        body=c[f['start']:f['end']];boxed=c[functions[box]['start']:functions[box]['end']]
        pc=Counter(re.findall(r'\b(lean_\w+)\s*\(',body))
        badcalls=[x for x in pc if any(k in x for k in ('mk_empty','alloc_array','array_push')) or x.startswith('lean_box_float')]
        assert not badcalls,(name,badcalls)
        shape=inv['ASM_function_shapes'][typed]
        chains[name]={'Suite_arguments_add_mul_sum_bmm':[{k:x[k] for k in ('constant','function','arity','fixed')} for x in chosen],
            'ADD_boxed':box,'ADD_typed':typed,'typed_signature':f['parameters'],'C_body_sha256':f['body_sha256'],
            'C_primitives':dict(sorted(pc.items())),'no_per_call_table_construction':not badcalls,
            'boxed_wrapper_counts':{k:boxed.count(k+'(') for k in ('lean_unbox_uint32','lean_dec','lean_box_uint32')},
            'ASM':shape}
        if name in ('runF64Native','runF64Boxed'):
            assert pc['lean_float_to_bits']==1 and pc['lean_float_to_float32']==0
            assert pc['lean_uint64_shift_right']>=4 and pc['lean_uint64_add']>=3
        if name in ('runF64Native','runF64Cast'):assert pc['lean_float_array_get']==2
        if name=='runF64Boxed':assert pc['lean_unbox_float']==2
        if name=='runF64Cast':assert pc['lean_float_to_float32']==pc['lean_float32_to_bits']==1
        (HERE/f'actual407745-{name}-selected.c.txt').write_bytes(body.encode())
        start=asm.index('<'+typed+'>:');start=asm.rfind('\n',0,start)+1
        end=asm.find('\nDisassembly of section ',start)
        (HERE/f'actual407745-{name}-selected.asm.txt').write_bytes(asm[start:end if end>=0 else len(asm)].encode())
    common=chains['runControl']['Suite_arguments_add_mul_sum_bmm']
    assert all(chains[n]['Suite_arguments_add_mul_sum_bmm'][i]['function']==common[i]['function'] for n in wanted for i in (2,3))
    mul_norm=[]
    for n in wanted:
        sym=chains[n]['Suite_arguments_add_mul_sum_bmm'][1]['function'].removesuffix('___boxed');f=functions[sym]
        mul_norm.append(norm_c(c[f['start']:f['end']]))
    flags={}
    for kind in ('compile','link','link_response'):
        p,q=COST/('original-'+kind+'.raw'),COST/('new-'+kind+'.raw')
        av,bv=(shlex.split(p.read_text()),shlex.split(q.read_text())) if kind=='link_response' else (d.trace_command(p),d.trace_command(q))
        assert d.normalize(av)==d.normalize(bv)
        flags[kind]={'same_after_root_target_mapping_only':True,'original_sha256':sha(p),'new_sha256':sha(q)}
    result=json.loads((COST/'result.json').read_bytes());assert result['complete'] and result['measurement_complete'] and result['official_originals_unchanged']
    assert result['source_sha256']==SOURCE and len(result['runs'])==24
    parser=d.load_module(d.R13,'r24_fixed_rows');blocks=[];samples=[];seen=0
    for seed in d.SEEDS:
        plan=json.loads((COST/f'plan-{seed}.json').read_bytes());rows=[]
        assert len(plan['cases'])==156 and sum(c['timed'] for c in plan['cases'])==152
        for i,var in enumerate(d.ORDER):
            meta=result['runs'][seen];seen+=1
            assert (meta['seed'],meta['order'],meta['variant'],meta['exit_code'])==(seed,i,var,0)
            assert json.loads(meta['environment']['BENCH_PLAN'])==plan and meta['environment']['BENCH_VARIANT']==var
            assert meta['environment']['BENCH_INNER']=='3' and meta['environment']['BENCH_PAIRS']=='500000'
            p=COST/f'{seed}-{i}-{var}.log';assert sha(p)==meta['log_sha256']
            row=parser.bench_rows(p.read_text(),plan);rows.append(row)
            assert row==json.loads((COST/f'{seed}-{i}-{var}-rows.json').read_bytes())
            samples.append({'seed':seed,'order':i,'variant':var,'log_sha256':sha(p),'rows':len(row),'seconds':meta['seconds']})
        for r in rows[1:]:parser.verify_same_seed(rows[0],r)
        stored=next(x for x in result['pairs'] if x['seed']==seed)
        for vi,var in enumerate(d.VARIANTS):
            k=4*vi
            for block,(control,variant) in enumerate(((k,k+1),(k+3,k+2))):
                values=d.summarize(plan,rows[control],rows[variant]);assert values==stored[f'{var}_block_{block}']
                blocks.append({'seed':seed,'variant':var,'block':block,'ratios':{op:v['variant_over_control'] for op,v in values.items()},
                    'control_ADD_share':values['add']['control_ns_sum']/values['whole']['control_ns_sum']})
    submission=(COST/'original-statement-Submission.c').read_bytes().decode()
    table={'global_native_symbol_present':'lp_competition_Submission_R24F64Add_nativeScales' in submission,
        'native_array_push_calls':submission.count('lean_float_array_push('),'native_empty_calls':submission.count('lean_mk_empty_float_array('),
        'note':'Global construction source plus no construction in actual selected ADD bodies; all measured checksums match. No timed claim about initialization or C++-level array implementation.'}
    report={'status':'ACTUAL_CALLBACK_FLAGS_TABLE_AND_24_PROCESS_REVIEW_PASS_LEGAL_BODY_PARKED',
        'run':40774570580,'source_commit':head,'source_sha256':SOURCE,'raw_files_rehashed':len(artifact['files']),'raw_bytes_rehashed':total,
        'actual_Main_C_sha256':sha(cpath),'ASM_sha256':sha(apath),'result_sha256':sha(COST/'result.json'),
        'static_prefilter_pass':pref['passed'],'fixed_inventory_script_sha256':sha(OLD/'inventory_callbacks.py'),
        'Main_object_hashes':{k:v for k,v in result['build_identities'].items() if '.o.' in k},'flags':flags,'chains':chains,
        'SUM_BMM_selected_function_shared':True,'MUL_C_normalized_identical':len(set(mul_norm))==1,'table_construction':table,
        'samples':samples,'blocks':blocks,'decision':'Park exact08a legal GRS body; no seed retry or large proof. Opaque cast is not admissible or a legal-cost substitute.',
        'scope':'Actual selected static Suite ADD callbacks and captured original isolated build C/ASM,24 complete discovery processes. Native object/binary bytes were not exported; identities bound to remote receipt, raw C/ASM rehashed. No official-score/adoption/new-track or formal-proof claim.'}
    save(HERE/'actual407745-review.json',report)
    print(json.dumps({'status':report['status'],'raw_files':report['raw_files_rehashed'],'raw_bytes':total,'MUL_C_same':report['MUL_C_normalized_identical'],
        'ASM_instructions_not_cycles':{k:v['ASM']['instruction_count_not_cycles'] for k,v in chains.items()},
        'legal_ADD':[b['ratios']['add'] for b in blocks if b['variant']=='f64native']}))
if __name__=='__main__':main()
