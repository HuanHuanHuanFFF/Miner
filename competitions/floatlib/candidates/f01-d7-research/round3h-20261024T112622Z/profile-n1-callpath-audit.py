"""Read-only actualDF n=1 direct-column opportunity audit, no candidate/build."""
from pathlib import Path
import hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r13_pinned_reader',HERE/'profile-coarse-analyze.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
sp=importlib.util.spec_from_file_location('r13_pinned_c_parser',HERE/'profile-current.py')
cparser=importlib.util.module_from_spec(sp);sp.loader.exec_module(cparser)


def run():
    runroot=m.REPO/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40094358287'
    originals=m.Originals(runroot/'original-artifact-hashes.json')
    folder=originals.root/'diagnostics/f01-d13-cost-profile/cost-profile/measurement'
    cp=folder/'profile-r13-coarse-original-Submission.c';raw=originals.read(cp);text=raw.decode()
    result=json.loads(originals.read(folder/'profile-r13-coarse-result.json'))
    commands=json.loads(originals.read(folder/'profile-r13-coarse-build-commands.json'))
    rsp=originals.read(folder/'profile-r13-coarse-link-response-0.rsp').decode()
    kernel=originals.read(folder/'profile-r13-coarse-Kernel.lean')
    assert hashlib.sha256(kernel).hexdigest()==m.SOURCE and result['kernel_sha256']==m.SOURCE
    rows=cparser.functions(text);byname={r['symbol']:r for r in rows}
    names=[
        'lp_competition_Submission_bmm','lp_competition_Submission_bmmBeforeUnderflowZero',
        'lp_competition_Submission_bmmBeforeR11Cross','lp_competition_Submission_DirectContinuous_output',
        'lp_competition_Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__1',
        'lp_competition_Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__0',
        'lp_competition_Submission_NativeFinal_dot','lp_competition_Submission_NativeFinal_dotLoop',
        'lp_competition_Submission_DirectContinuous_row___redArg___lam__0']
    symbols={}
    for name in names:
        r=byname[name];body=cparser.mask_c(r['body']);body=body[body.index('{')+1:]
        symbols[name]={'source_line':text.count('\n',0,r['start'])+1,'body_sha256':hashlib.sha256(r['body'].encode()).hexdigest(),
            'direct_calls':{n:len(re.findall(r'\b'+re.escape(n)+r'\s*\(',body))for n in names if re.search(r'\b'+re.escape(n)+r'\s*\(',body)},
            'of_bits_sites':len(re.findall(r'\blean_float32_of_bits\s*\(',body)),
            'lean_apply_sites':len(re.findall(r'\blean_apply_[0-9]+\s*\(',body)),
            'float_parameter':bool(re.search(r'\([^\n]*\bfloat\s',r['body'][:r['body'].index('{')])),
            'snippet':r['body']}
    dot=byname['lp_competition_Submission_NativeFinal_dotLoop']['body']
    col=byname[names[5]]['body'];row=byname[names[4]]['body']
    assert dot.count('lean_float32_of_bits(')==2 and 'lean_nat_dec_lt(v_k_11671_, v_n_11665_)'in dot
    assert 'goto _start;'in dot and 'lean_nat_add(v_k_11671_'in dot
    assert symbols[names[5]]['direct_calls'][names[6]]==1 and symbols[names[5]]['lean_apply_sites']==0
    assert 'lean_float32_of_bits('not in col and 'lean_float32_of_bits('not in row
    assert 'lean_float32_add('in dot and 'lean_float32_mul('in dot
    mainfull_files=[key for key in originals.files if 'MainFull.c'in key]
    outer_asm=json.loads(originals.read(originals.root/'diagnostics/f01-d13-cost-profile/native-assembly-index.json'))
    asm_kernels=sorted({v['kernel_sha256']for v in outer_asm if 'kernel_sha256'in v})
    candidates=[]
    for item in result['cases']:
        c=item['case']
        if c['kernel']=='bmm'and c['n']==1:
            route=m.classify(c)['route'];rows_count=c['batch']*c['m'];outputs=rows_count*c['p']
            candidates.append({'case':c['name'],'route_source_model':route,'batch':c['batch'],'m':c['m'],'n':1,'p':c['p'],
                'rows':rows_count,'outputs':outputs,'original_whole_ns':item['original_whole_row']['best_ns'],
                'applicable_to_DirectContinuous_n1':route=='DirectContinuous',
                'source_scheduled_A_decode_savings_if_once_per_row':outputs-rows_count if route=='DirectContinuous'else 0})
    eligible=[c for c in candidates if c['applicable_to_DirectContinuous_n1']]
    compile_lines=[s for s in commands if 'clang -c 'in s and 'Submission.c 'in s]
    assert len(compile_lines)==1
    out={'state':'SOURCE_OPPORTUNITY_VERIFIED_MACHINE_HOIST_UNKNOWN','exactDF':m.SOURCE,'run':40094358287,
        'source_c':{'path':str(cp),'sha256':hashlib.sha256(raw).hexdigest()},
        'original_object_and_whole_binary_identity':result['build_identities']['before'],
        'verified_C_chain':names[:8],'symbols':symbols,
        'source_findings':[
            'Actual row-specialized Fin loop hoists baseA and baseB indices only, then calls a specialized column Fin loop.',
            'The column loop directly calls NativeFinal.dot for every output; it carries raw A/B and dynamic n/baseA/p, no predecoded native A float.',
            'dot initializes k=0 and positive zero, calls dynamic dotLoop, tests native result self-equality, then returns bits or raw-input replayEarly.',
            'dotLoop performs A and B size/bounds/get/unbox/of_bits within each k iteration, dynamic k<n test and k+1 tail goto.',
            'For n=1 each output still traverses this ordinary C route; no n1 specialization or cross-column A conversion hoist is present in generated C.',
            'The actual column-specialized C uses a direct dot call and no lean_apply; the unused generic row wrapper uses a boxed closure.'],
        'LLVM_boundary':{'status':'UNKNOWN','actual_DF_dotLoop_assembly_exported':False,
            'mainfull_C_files_in_original_index':mainfull_files,'mainfull_DF_call_chain':'UNKNOWN: no actualDF MainFull C bytes captured in this artifact',
            'trace_mentions_MainFull_compile':any('MainFull.c 'in s for s in commands),
            'link_mentions_MainFull_object':'MainFull.c.o.export'in rsp,
            'original_compile_argv':compile_lines[0],'flto_seen_in_compile_or_link':any('-flto'in s for s in [*commands,rsp]),
            'outer_disassembly_kernel_sha256':asm_kernels,
            'outer_disassembly_rejected':'Outer8eb carrier assembly is not exactDF. No inference that clang retains every generated-C operation after O3.'},
        'public_seed1224016_n1_cases':candidates,
        'eligible_DirectContinuous_n1':{'cases':len(eligible),'original_whole_anchor_ns_sum':sum(c['original_whole_ns']for c in eligible),
            'source_scheduled_redundant_A_decodes_per_one_sweep':sum(c['source_scheduled_A_decode_savings_if_once_per_row']for c in eligible),
            'interpretation':'Source operation count only; no official score/cycle saving, and Cross n1 is excluded.'},
        'new_candidate_codegen_checks':[
            'Find A getD/of_bits once in each row before the column fold; verify the actual public specialization is reached.',
            'Prefer a native float argument in the actual specialized column loop; inspect Float32 boxing/capture, repeated unbox, closure allocation and lean_apply calls rather than assuming closure specialization.',
            'Retain positive-zero + fa*fb, result nonNaN test, raw-input replayEarly and one final array; replacing +0 with product can change signed-zero behavior.',
            'If extra float boxing, lean_apply or allocation offsets the saved A decode/dynamic dot overhead, require the complete same-run gate to reject it.'],
        'scope':'Read-only mechanism precondition audit. No candidate, tests, CI, runtime modification or machine speedup claim.',
        'checked_originals':originals.checked,
        'audit_source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    dest=HERE/'profile-n1-callpath-audit.json';dest.write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':out['state'],'sha256':hashlib.sha256(dest.read_bytes()).hexdigest(),'eligible':out['eligible_DirectContinuous_n1'],'actual_MainFull':'UNKNOWN','original_object_sha256':result['build_identities']['before']['object']['sha256']}))


if __name__=='__main__':run()
