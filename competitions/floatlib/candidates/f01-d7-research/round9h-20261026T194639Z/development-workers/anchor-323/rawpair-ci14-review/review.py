"""CI14 bounded evidence check. Only read originals and write this review directory."""
from pathlib import Path
import hashlib
import json
import re
import shlex
from datetime import datetime,timezone

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40435031251'
RAW=RUN/'download-e00306f2bd374e2bbddf2dfa8bb06495'
DIAG=next(p for p in RAW.rglob('f01-r19-dev-dc-rawpair2') if (p/'helper-audit.json').is_file())
SOURCE='6a0c18c52d736a1b8856877d6056372e13f70b095e36e34bd05203bcb7a5d1c0'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(name,value):(HERE/name).write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())

def function(text,name):
    match=re.search(r'^LEAN_EXPORT [^\n]*\b'+re.escape(name)+r'\([^\n]*\)\{',text,re.M)
    assert match,name
    start=match.start();opening=match.end()-1;depth=0
    # Selected numeric functions have no braces inside C string literals.
    for i in range(opening,len(text)):
        if text[i]=='{':depth+=1
        if text[i]=='}':
            depth-=1
            if depth==0:return {'name':name,'line':text.count('\n',0,start)+1,'text':text[start:i+1]+'\n'}
    raise AssertionError(name)

def calls(value,name):return len(re.findall(r'\b'+re.escape(name)+r'\(',value['text'].split('\n',1)[1]))

def main():
    inventory=json.loads((RUN/'original-artifact-hashes.json').read_bytes());bound=[]
    for name,item in inventory['files'].items():
        p=RAW/name;assert p.stat().st_size==item['bytes'] and sha(p)==item['sha256'],name
        bound.append({'path':p.relative_to(ROOT).as_posix(),**item})
    assert len(bound)==75
    save('all-originals.json',{'run':40435031251,'head':inventory['artifact']['workflow_run']['head_sha'],'archive_digest':inventory['artifact']['digest'],
        'original_hash_receipt_sha256':sha(RUN/'original-artifact-hashes.json'),'count':len(bound),'files':bound})
    kernel=next(p for p in RAW.rglob('Kernel.lean') if 'f01-r19-dev-dc-rawpair2' in str(p));assert sha(kernel)==SOURCE and kernel.stat().st_size==235456
    candidate=ROOT/'competitions/floatlib/candidates/f01-r19-dev-dc-rawpair2';assert (candidate/'Kernel.lean').read_bytes()==kernel.read_bytes()
    manifest=json.loads((candidate/'manifest.json').read_bytes());audit=json.loads((DIAG/'helper-audit.json').read_bytes())
    assert manifest['candidate_sha256']==audit['kernel_sha256']==SOURCE
    assert audit['accepted'] and audit['kernel_replay'] and audit['expected_count']==14 and audit['exit_code']==0
    assert audit['names']==manifest['explicit_helper_audit'] and len(audit['reports'])==14
    assert sha(DIAG/'helper-axioms.raw')==audit['output_sha256'] and sha(DIAG/'helper-audit-source.lean')==audit['audit_source_sha256']
    raw_reports={name:set(x.strip() for x in axioms.split(',')) for name,axioms in re.findall(r"'([^']+)' depends on axioms: \[([^\]]*)\]",(DIAG/'helper-axioms.raw').read_text())}
    assert set(raw_reports)==set(audit['names'])
    for name,allowed in audit['reports'].items():assert raw_reports[name]==set(allowed)<=set(audit['allowed_axioms'])
    log=(DIAG/'replay.log').read_text()
    assert '[statement] ok' in log and '[helper-kernel] ok' in log and '[helper-axioms] ok' in log
    assert 'Submission replays cleanly' in log and 'VerifyFull replays cleanly' in log
    assert '[score] ok' not in log
    C=(DIAG/'candidate-generated-0.c').read_text();MAIN=(DIAG/'candidate-generated-1.c').read_text()
    prefix='lp_competition_';old=prefix+'Submission_NativeFinal_dotLoop';new=prefix+'Submission_R19DCRawPair_loop'
    row=prefix+'Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__3'
    pair=prefix+'Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__2'
    emit=prefix+'Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__0'
    odd=prefix+'Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__1'
    names=[prefix+x for x in ('Submission_bmm','Submission_R15PackedB2_dispatch','Submission_R14ThinBCache_dispatch','Submission_bmmBeforeR11Cross','Submission_R19DCRawPair_core','Submission_R19DCRawPair_output')]+[row,pair,emit,odd,new,old,prefix+'Submission_Packed10_finish',prefix+'Submission_NativeFinal_dot',prefix+'Submission_R19DCRawPair_groupFrom']
    funcs={name:function(C,name) for name in names}
    assert '.m_fun = (void*)lp_competition_Submission_bmm' in MAIN
    path=names[:6]+[row,pair,new]
    edges=[]
    for parent,child in zip(path,path[1:]):
        assert calls(funcs[parent],child)>=1,(parent,child)
        edges.append({'caller':parent,'line':funcs[parent]['line'],'callee':child,'C_call_sites':calls(funcs[parent],child)})
    assert calls(funcs[pair],new)==1 and calls(funcs[pair],emit)==1 and calls(funcs[pair],odd)==1
    assert calls(funcs[emit],new)==0 and calls(funcs[emit],prefix+'Submission_NativeFinal_dot')==0
    assert calls(funcs[odd],prefix+'Submission_NativeFinal_dot')==1 and calls(funcs[odd],new)==0
    assert calls(funcs[row],'lean_nat_div')==1 and calls(funcs[pair],'lean_nat_div')==0
    assert calls(funcs[row],'lean_nat_mul')==3
    assert calls(funcs[new],'lean_float32_of_bits')==3 and calls(funcs[old],'lean_float32_of_bits')==2
    assert calls(funcs[new],'lean_alloc_ctor')==1 and 'lean_alloc_ctor(0, 0, 8)' in funcs[new]['text']
    assert calls(funcs[pair],'lean_dec_ref')==1
    for name in (row,pair,emit,odd,new):
        assert not any(s in funcs[name]['text'] for s in ('lean_apply','lean_alloc_closure','lean_box_float32'))
    metrics={}
    for name in (new,old,row,pair,emit,odd):
        metrics[name]={'C_line':funcs[name]['line'],**{call:calls(funcs[name],call) for call in ('lean_float32_of_bits','lean_array_fget_borrowed','lean_nat_add','lean_nat_mul','lean_nat_div','lean_nat_dec_lt','lean_alloc_ctor','lean_alloc_closure','lean_box_float32','lean_box_uint32','lean_array_push')}}
    selected='\n'.join('// ORIGINAL C line '+str(funcs[name]['line'])+'\n'+funcs[name]['text'] for name in names)
    (HERE/'selected-chain.c.txt').write_text(selected,encoding='utf-8')
    index=json.loads((DIAG/'native-assembly-index.json').read_bytes());new_asm=next(x for x in index if x.get('symbol')==new)
    assert not any(x.get('symbol')==old for x in index) and not any(x.get('symbol')==pair for x in index)
    asm=(DIAG/new_asm['file']).read_text();assert sha(DIAG/new_asm['file'])==new_asm['sha256']
    assert 'R_X86_64_' not in asm
    start=asm.index('0000000000000000 <'+new+'>:');end=asm.index('\nDisassembly of section ',start)
    body=asm[start:end];(HERE/'new-loop.asm.txt').write_text(body+'\n',encoding='utf-8')
    assert 'sub    rsp,0xa8' in body
    for address in ('[rsp+0x90]','[rsp+0x80]','[rsp+0x40]'):assert body.count('XMMWORD PTR '+address)>=2
    assert 'mulps' in body and 'addps' in body
    baseline=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
    def namespace(raw,name):return raw.split(b'namespace '+name.encode(),1)[1].split(b'end '+name.encode(),1)[0]
    old_namespace=namespace(kernel.read_bytes(),'NativeFinal')
    assert old_namespace==namespace(baseline.read_bytes(),'NativeFinal')
    selector=ROOT/'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
    compile_trace=json.loads((DIAG/'build-trace-10.txt').read_bytes())
    argv=[x['message'][3:] for x in compile_trace['log'] if x['message'].startswith('.> ')]
    assert len(argv)==1
    compile_argv=shlex.split(argv[0]);assert '-O3' in compile_argv and '-ffp-contract=off' in compile_argv
    assert not any(x.startswith('-flto') for x in compile_argv)
    environment=json.loads((RAW/'environment.json').read_bytes())
    gatecheck={'statement':True,'complete_Submission_and_VerifyFull_replay':True,'explicit14_root_axiom_audit':True,
        'allowed_axioms':audit['allowed_axioms'],'names':audit['names'],'public_new_BMM_spec_included':True,'full_gate':'NOT_RUN','performance':'UNKNOWN'}
    report={'created_at_utc':datetime.now(timezone.utc).isoformat(),'run':40435031251,'source_commit':inventory['artifact']['workflow_run']['head_sha'],
        'all75_originals_hash_verified':True,'source_sha256':SOURCE,'source_bytes':kernel.stat().st_size,'manifest_current_sha256':sha(candidate/'manifest.json'),
        'Submission_C_sha256':sha(DIAG/'candidate-generated-0.c'),'MainFull_C_sha256':sha(DIAG/'candidate-generated-1.c'),
        'statement_Submission_object_sha256':new_asm['object_sha256'],'statement_only_not_timed_object':True,'correctness':gatecheck,
        'toolchain_environment':environment,'compile_trace_sha256':sha(DIAG/'build-trace-10.txt'),'actual_compile_argv':compile_argv,
        'unchanged_old_loop_source':{'B2_source_sha256':sha(baseline),'NativeFinal_namespace_raw_bytes':len(old_namespace),'NativeFinal_namespace_sha256':hashlib.sha256(old_namespace).hexdigest(),'exact_raw_namespace_equals_B2':True},
        'selected_C_edges':edges,'C_metrics':metrics,
        'selected_vs_exported':{'actual_C_pair_caller':pair,'actual_row_caller':row,'exported_groupFrom_not_on_selected_C_path':True,
            'selected_C_calls_exported_newloop':True,'selected_pair_native_ASM_retained':False,'cannot_prove_exported_newloop_ASM_is_final_caller_execution_body':True},
        'conditions':{'shared_A_once_per_pair_k':'VERIFIED_C','three_original_codec_calls':'VERIFIED_C_NOT_RELOC_NATIVE',
            'each_full_pair_one_loop_shared_F2':'VERIFIED_C','no_hot_apply_closure_Float32_box':'VERIFIED_C',
            'baseA_baseB_row_once_no_pair_division':'VERIFIED_C','terminal_F2_once_per_pair_then_release_after_emit':'VERIFIED_C',
            'odd_one_original_dot_no_new_pairloop':'VERIFIED_C','NaN_finish_and_replay_remain':'VERIFIED_C',
            'new_vs_old_hot_spill_comparison':'UNKNOWN_MISSING_OLD_ASM','native_selected_caller_not_just_helper':'UNKNOWN_MISSING_CALLER_ASM',
            'native_call_targets':'UNKNOWN_NO_RELOCATIONS'},
        'native_new_exported_loop':{'artifact':new_asm['file'],'sha256':new_asm['sha256'],'stack_frame_bytes':168,'callee_saved_pushes':6,
            'hot_save_reload_slots':{'A':'16B rsp+0x90','B0':'16B rsp+0x80','pair_accumulators':'16B rsp+0x40'},
            'common_smallNat_inbounds_path_observation':'Three call instructions at0x111/0x1ae/0x22f; mapping to codecs inferred from C, not relocation-verified. Old exportloop native absent; do not claim less/more spill.',
            'packed_mul_add':'mulps/addps on two Float32 lanes, no fused-FMA claim','terminal':'C one8B F2 payload; exported ASM malloc-size16 path at0x603, actual callee target lacks relocation'},
        'next_capture':{'object':'Submission.c.o.export built from the same exact6a0c source; original NativeFinal namespace equals622d',
            'required_symbols':[old,new,pair],'use':'objdump -dr --no-show-raw-insn -Mintel --disassemble=<exactsymbol> <exactactualobject>',
            'use_original_flags_no_recompile':'Capture existing object during original statement; do not rebuild C or add a diagnostic hot wrapper',
            'optional_caller_symbols':[row,emit,odd],
            'selector_source_current_sha256':sha(selector),'selector_reason':'Submission_ prefix loop whitelist accepts R19DCRawPair/Packed/etc but not NativeFinal; Fin_foldl specialized caller lacks Submission_ prefix; objdump uses-d rather than-dr.'},
        'decision':'DO_NOT_ADVANCE_TO_FULL_D_YET_RETAIN_PROVED_SOURCE_AND_WAIT_FOR_SAME_SOURCE_NATIVE_CAPTURE_IN_SPARE_STATEMENT_SLOT',
        'decision_basis':'C premises largely pass, but mandatory old/new relocation and selectednative caller/spill comparison remains open. Domain about5.98%whole from one already seen plan needs about50.18% complete-local saving for3%whole; fewer codec calls is not a speed estimate.',
        'limits':'No actualtiming/new gate/confirmation or adoption claim. Native ELF not retained. No Git/CI/Lean and no candidate/global/Harness changes.'}
    save('review.json',report)
    print(json.dumps({'all_originals':len(bound),'roots':len(audit['names']),'selected_C_edges':len(edges),'three_codec_C_sites':metrics[new]['lean_float32_of_bits'],'old_loop_ASM':False,'selected_pair_caller_ASM':False,'relocations':False,'decision':report['decision']},indent=2))
if __name__=='__main__':main()
