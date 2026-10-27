"""Independent read-only CI13 raw parser/hash/ASM review; no build or candidate writes."""
from pathlib import Path
import hashlib
import json
import re
import shlex
from datetime import datetime,timezone

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40432634558'
RAW=RUN/'download-884dd1b31e484d1cb852942081f1d275'
COST=next(RAW.rglob('runtime-cost'))
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(p,v):p.write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
def command(path):
    t=json.loads(path.read_bytes());assert not t['synthetic']
    cmd=[x['message'][3:] for x in t['log'] if x['message'].startswith('.> ')]
    assert len(cmd)==1;return shlex.split(cmd[0])
def norm(args):
    result=[]
    for value in args:
        value=value.replace('/MainFull.', '/<ROOT>.').replace('/R19RuntimeCostMain.','/<ROOT>.')
        value=value.replace('/benchFull.','/<EXE>.').replace('/r19RuntimeCost.','/<EXE>.')
        for name in ('benchFull','r19RuntimeCost'):
            if value.endswith('/'+name):value=value[:-len(name)]+'<EXE>'
        result.append(value)
    return result
def parse(log,plan):
    expected={c['name']:c for c in plan['cases']};assert len(expected)==156
    rows={}
    for line in log.splitlines():
        m=re.fullmatch(r'(\S+) (true|false) (\d+) (\d+)',line)
        if not m:continue
        name,t,ns,check=m.groups();assert name in expected and name not in rows
        t=t=='true';ns=int(ns);check=int(check)
        assert t==expected[name]['timed'] and (ns>0 if t else ns==0)
        rows[name]={'timed':t,'best_ns':ns,'checksum':check}
    assert set(rows)==set(expected) and sum(x['timed'] for x in rows.values())==152
    return rows
def totals(rows,plan):
    result={op:sum(rows[c['name']]['best_ns'] for c in plan['cases'] if c['timed'] and c['kernel']==op) for op in ('add','mul','sum','bmm')}
    result['whole']=sum(result.values());assert result['whole']==sum(r['best_ns'] for r in rows.values())
    return result
def asm_functions(text):
    result={};name=None
    for lineno,line in enumerate(text.splitlines(),1):
        m=re.fullmatch(r'[0-9a-f]+ <([^>]+)>:',line)
        if m:name=m[1];result[name]=[];continue
        m=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)',line)
        if name and m and not m[2].startswith('R_'):result[name].append({'address':int(m[1],16),'mnemonic':m[2],'operands':m[3],'line':lineno})
    return result

def main():
    inventory=json.loads((RUN/'original-artifact-hashes.json').read_bytes());binding=[]
    assert inventory['artifact']['workflow_run']['head_sha']=='93fe24bf105ed11fd5e56f262adef82be9129b44'
    for relative,item in inventory['files'].items():
        p=RAW/relative;assert p.stat().st_size==item['bytes'] and sha(p)==item['sha256'],relative
        binding.append({'path':p.relative_to(ROOT).as_posix(),**item})
    assert len(binding)==121
    save(HERE/'all-originals.json',{'run':40432634558,'head_sha':inventory['artifact']['workflow_run']['head_sha'],'archive_digest':inventory['artifact']['digest'],
        'receipt_sha256':sha(RUN/'original-artifact-hashes.json'),'count':len(binding),'files':binding})
    stored=json.loads((COST/'result.json').read_bytes());runs=stored['runs'];assert len(runs)==8
    parsed={};samples=[];blocks=[];case_pairs=[]
    for seed in (1927003,1927005):
        plan=json.loads((COST/f'plan-{seed}.json').read_bytes());subset=[]
        for order,variant in enumerate(('control','guarded','guarded','control')):
            stem=f'{seed}-{order}-{variant}';rows=parse((COST/(stem+'.log')).read_text(),plan)
            assert rows==json.loads((COST/(stem+'-rows.json')).read_bytes())
            meta=runs[len(samples)];assert (meta['seed'],meta['order'],meta['variant'],meta['exit_code'])==(seed,order,variant,0)
            assert meta['environment']['BENCH_VARIANT']==variant and json.loads(meta['environment']['BENCH_PLAN'])==plan
            assert meta['environment']['BENCH_INNER']=='3' and meta['environment']['BENCH_PAIRS']=='500000'
            assert meta['argv'][:3]==['taskset','-c','0'] and meta['argv'][-1].endswith('/bin/r19RuntimeCost')
            assert sha(COST/(stem+'.log'))==meta['log_sha256']
            subset.append(rows);parsed[(seed,order)]=rows
            samples.append({'seed':seed,'order':order,'variant':variant,'rows':len(rows),'timed_rows':152,'seconds':meta['seconds'],'ns':totals(rows,plan)})
        assert all(all(subset[0][n]['checksum']==r[n]['checksum'] for n in subset[0]) for r in subset[1:])
        for block,(ci,gi) in enumerate(((0,1),(3,2))):
            c,g=totals(subset[ci],plan),totals(subset[gi],plan)
            value={'seed':seed,'block':block,'control_order':ci,'guarded_order':gi,'all156_checksums_equal':True,'operations':{}}
            for op in ('add','mul','sum','bmm','whole'):
                observed=stored['pairs'][0 if seed==1927003 else 1][f'block_{block}'][op]
                assert observed['control_ns_sum']==c[op] and observed['guarded_ns_sum']==g[op]
                assert observed['guarded_over_control']==g[op]/c[op]
                value['operations'][op]={'control_ns':c[op],'guarded_ns':g[op],'guarded_over_control':g[op]/c[op],'delta_ns':g[op]-c[op]}
            blocks.append(value)
            for item in plan['cases']:
                if item['timed']:
                    name=item['name'];cn=subset[ci][name]['best_ns'];gn=subset[gi][name]['best_ns']
                    case_pairs.append({'seed':seed,'block':block,'case':name,'kernel':item['kernel'],'control_ns':cn,'guarded_ns':gn,'ratio':gn/cn,'delta_ns':gn-cn})
    aggregate={}
    for op in ('add','mul','sum','bmm','whole'):
        c=sum(x['operations'][op]['control_ns'] for x in blocks);g=sum(x['operations'][op]['guarded_ns'] for x in blocks)
        aggregate[op]={'control_sum_ns':c,'guarded_sum_ns':g,'guarded_over_control':g/c,'scope':'Descriptive pooled four blocks only; no gate score/stability/probability inference'}
    flags={}
    for kind in ('compile','link','link_response'):
        old,new=[COST/(role+'-'+kind+'.raw') for role in ('original','new')]
        a,b=(shlex.split(old.read_text()),shlex.split(new.read_text())) if kind=='link_response' else (command(old),command(new))
        assert norm(a)==norm(b);flags[kind]={'equal_after_root_target_paths_only':True,'arguments':len(a),'original_sha256':sha(old),'new_sha256':sha(new)}
    prepare=json.loads((COST/'prepare.json').read_bytes());alternate=(COST/'alternate-lakefile.lean').read_bytes()
    assert hashlib.sha256(alternate[:prepare['alternate_config_original_prefix_bytes']]).hexdigest()==prepare['original_lakefile_sha256']
    assert sha(COST/'caller.lean')==prepare['owned_files'][next(n for n in prepare['owned_files'] if n.endswith('R19RuntimeCostMain.lean'))]
    assert sha(COST/'original-statement-MainFull.c')==prepare['original_build_before'][next(n for n in prepare['original_build_before'] if n.endswith('/MainFull.c'))]
    assert sha(COST/'original-statement-Submission.c')==prepare['original_build_before'][next(n for n in prepare['original_build_before'] if n.endswith('/Submission.c'))]
    input_source=next(p for p in RAW.rglob('Kernel.lean') if 'f01-r19-dev-runtime-cost1' in str(p))
    assert sha(input_source)==stored['source_sha256']=='74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc'
    c=(COST/'build-product-0-R19RuntimeCostMain.c').read_text();assert 'diagnosticEntry' not in c
    functions=asm_functions((COST/'own-object-0-asm.txt').read_text());guard=functions['lp_competition_main___lam__1'];control=functions['lp_competition_main___lam__3']
    ranges=[(0,0x2d),(0x76,0x88),(0x122,0x12f),(0x33d,0x3a4),(0xc06,0xc12)]
    fast=[i for i in guard if any(lo<=i['address']<=hi for lo,hi in ranges)]
    assert not any(i['mnemonic'].startswith('call') for i in fast)
    assert not any(('xmm' in i['operands'] or ' PTR [' in i['operands']) for i in fast)
    guard_prolog=guard[:6];control_prolog=control[:6]
    assert [(i['mnemonic'],i['operands']) for i in guard_prolog]==[(i['mnemonic'],i['operands']) for i in control_prolog]
    boxed_guard=functions['lp_competition_main___lam__1___boxed'];boxed_control=functions['lp_competition_main___lam__3___boxed']
    assert [(i['mnemonic'],i['operands'].replace('lam__1','lam__X')) for i in boxed_guard]==[(i['mnemonic'],i['operands'].replace('lam__3','lam__X')) for i in boxed_control]
    asm={'guarded_callback':'lp_competition_main___lam__1___boxed -> lp_competition_main___lam__1',
        'control_callback':'lp_competition_main___lam__3___boxed -> lp_competition_main___lam__3',
        'fast_domain':'1<=eu,ev<=254 and128<=eu+ev<=380','guarded_fast_path_ranges_hex':[[hex(a),hex(b)] for a,b in ranges],
        'guarded_fast_path':fast,'normal_path_no_call_FP_table_or_temporary_stack_access':True,
        'common_stack_frame':'Both typed callbacks push rbp/r15/r14/r12/rbx and sub rsp,16; same boxed wrapper with one common typed callback call',
        'boxed_wrappers_equal_after_symbol_mapping':True,'fallback_calls_FP_table_spill_remain':True,
        'harness_versus_official_caller_difference':'Both harness MUL closures have arity3 with one fixed capturedtrue Bool produced by variant comparison; original MainFull Suite MUL is a static arity2 closure. Shared captured parameter unboxing and register allocation are not exact official caller identity.',
        'closure_allocation_boundary':'One closure allocation/variant branch before Bench.Suite.run; capturedtrue Bool is still a dynamic typed parameter each scalar call.',
        'alias_symbol_exists_but_selected_lambda_inlines_body':True,'no_diagnosticEntry_reference_in_caller_C':True,
        'native_ELF_locally_retained':False,'boundary':'Disassembly of new caller object bound by remote object hash; physical final linked binary was not exported'}
    save(HERE/'callback-asm.json',asm);save(HERE/'raw-recomputed.json',{'samples':samples,'blocks':blocks,'all_four_blocks_pooled':aggregate,'case_pairs':case_pairs})
    statement_index=json.loads((COST.parent/'native-assembly-index.json').read_bytes())
    statement_mul=next(x for x in statement_index if x.get('symbol')=='lp_competition_main___lam__3')
    statement_functions=asm_functions((COST.parent/statement_mul['file']).read_text())
    official_control=statement_functions['lp_competition_main___lam__3']
    assert len(official_control)==326 and len(control)==345
    anomaly={op:sorted([x for x in case_pairs if x['seed']==1927003 and x['block']==1 and x['kernel']==op],key=lambda x:x['delta_ns'],reverse=True)[:5] for op in ('add','mul','sum')}
    review={'created_at_utc':datetime.now(timezone.utc).isoformat(),'run':40432634558,'head':'93fe24bf105ed11fd5e56f262adef82be9129b44','all121_original_hashes_verified':True,
        'source_sha256':sha(input_source),'harness_source_sha256':sha(COST/'caller.lean'),'actual_C_sha256':sha(COST/'build-product-0-R19RuntimeCostMain.c'),
        'ASM_sha256':sha(COST/'own-object-0-asm.txt'),'raw_result_sha256':sha(COST/'result.json'),'flags_link_rsp':flags,
        'measurement_and_originals_remote_assertions':{k:stored[k] for k in ('complete','measurement_complete','official_originals_unchanged','build_seconds','build_identities')},
        'before_after_limit':'Available C/trace/rsp bytes independently hash-checked. Original/new object and binary identity equality after all8 runs is a successful remote assertion; native ELF bytes not retained for independent local rehash.',
        'samples':samples,'blocks':blocks,'pooled':aggregate,'anomalous_block_preserved_top_deltas':anomaly,
        'official_statement_vs_timed_harness':{'original_MainFull_object_sha256':statement_mul['object_sha256'],
            'original_statement_MUL_typed_instructions':len(official_control),'harness_control_MUL_typed_instructions':len(control),
            'extra_dynamic_captured_bool_in_both_harness_variants':True,'original_MainFull_was_timed_in_this_experiment':False,
            'original_benchFull_sha256':prepare['original_build_before'][next(n for n in prepare['original_build_before'] if n.endswith('/bin/benchFull'))]},
        'resource_metadata':{'build_memory_mb':stored['execution_config']['build_memory_mb'],'bench_memory_mb':stored['execution_config']['benchmark_memory_mb'],
            'cpu':stored['execution_config']['requested_benchmark_cpu'],'recorded_entry_budget_remaining_before':stored['execution_config']['original_entry_budget_remaining_before'],
            'recorded_entry_budget_remaining_after':stored['original_entry_budget_remaining_after'],'inner_deadline_seconds':580,
            'note':'Remaining entry budget exceeds600; do not describe actual enclosing entry budget as default600. Diagnostic580s absolute deadline is separately recorded.'},
        'recommendation':'PARK_THIS_EXACT_RUNTIME_AND_DO_NOT_BUY_EXPENSIVE_PUBLIC_PROOF_FROM_THESE_COSTS',
        'reason':'All four blocks retained: MUL andwhole show mixed near-parity/slower outcomes. Seed3 block1 SUM1.2218 accompanies MUL1.1361 despite identical SUM callback; process/code-layout variation is plausible but cause UNKNOWN and not permission to delete the block. No adequate positive cost evidence.',
        'allowed_next_condition':'Reopen only for a materially different runtime, measured hot-domain evidence, or a low-cost independently validated caller condition without the shared variantBool capture. Such a condition needs its own diagnostic; this run cannot prove the underlying arithmetic always slower. No seen-seed reset or success probability.',
        'scope':'One runner, two already exposed plans, ABBA diagnostic composition. Not originalD/gate, not confirmation, not newMUL proof, not evidence of cross-runner stability.'}
    save(HERE/'review.json',review)
    print(json.dumps({'raw_files':len(binding),'samples':len(samples),'blocks':len(blocks),'pooled':aggregate,'flags':flags,'fast_instructions':len(fast)},indent=2))
if __name__=='__main__':main()
