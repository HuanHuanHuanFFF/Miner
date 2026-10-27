"""CI15 exact artifact/proof/caller review; no build, timing, Git or global writes."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib
import json
import re
import shlex

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40435830288'
RAW=RUN/'download-4bf7fb38305b4e43a843b00e5607a39a'
DIAG=next(p for p in RAW.rglob('f01-r19-dev-dual-temporal-a4-5') if (p/'helper-audit.json').is_file())
SOURCE='c36bc2502904bf946d442de1a4646e09689f016643f09ab0b6788f9bdd375250'
P='lp_competition_'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(name,value):(HERE/name).write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
def function(text,name):
    m=re.search(r'^LEAN_EXPORT [^\n]*\b'+re.escape(name)+r'\([^\n]*\)\{',text,re.M);assert m,name
    depth=0
    for i in range(m.end()-1,len(text)):
        if text[i]=='{':depth+=1
        if text[i]=='}':
            depth-=1
            if depth==0:return {'name':name,'line':text.count('\n',0,m.start())+1,'text':text[m.start():i+1]+'\n'}
    raise AssertionError(name)
def count(f,name):return len(re.findall(r'\b'+re.escape(name)+r'\(',f['text'].split('\n',1)[1]))
def asm_body(text,name):
    start=text.index('0000000000000000 <'+name+'>:');end=text.find('\nDisassembly of section ',start)
    return text[start:end if end>=0 else len(text)]
def instructions(text):
    result=[]
    for line in text.splitlines():
        m=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)',line)
        if m and not m[2].startswith('R_'):result.append({'address':int(m[1],16),'mnemonic':m[2],'operands':m[3]})
    return result
def select_path(ins,ranges):return [i for i in ins if any(a<=i['address']<=b for a,b in ranges)]

def main():
    inventory=json.loads((RUN/'original-artifact-hashes.json').read_bytes());bound=[]
    for name,item in inventory['files'].items():
        path=RAW/name;assert sha(path)==item['sha256'] and path.stat().st_size==item['bytes'],name
        bound.append({'path':path.relative_to(ROOT).as_posix(),**item})
    assert len(bound)==135
    save('all-originals.json',{'run':40435830288,'source_commit':inventory['artifact']['workflow_run']['head_sha'],'archive_digest':inventory['artifact']['digest'],
        'original_hash_receipt_sha256':sha(RUN/'original-artifact-hashes.json'),'count':135,'files':bound})
    kernel=next(p for p in RAW.rglob('Kernel.lean') if 'f01-r19-dev-dual-temporal-a4-5' in str(p))
    candidate=ROOT/'competitions/floatlib/candidates/f01-r19-dev-dual-temporal-a4-5';manifest=json.loads((candidate/'manifest.json').read_bytes())
    assert sha(kernel)==SOURCE==manifest['candidate_sha256'] and kernel.stat().st_size==241509 and kernel.read_bytes()==(candidate/'Kernel.lean').read_bytes()
    audit=json.loads((DIAG/'helper-audit.json').read_bytes());assert audit['kernel_sha256']==SOURCE and audit['accepted'] and audit['kernel_replay'] and audit['exit_code']==0
    assert audit['expected_count']==18 and audit['names']==manifest['explicit_helper_audit'] and len(audit['reports'])==18
    assert sha(DIAG/'helper-axioms.raw')==audit['output_sha256'] and sha(DIAG/'helper-audit-source.lean')==audit['audit_source_sha256']
    roots={n:set(x.strip() for x in a.split(',')) for n,a in re.findall(r"'([^']+)' depends on axioms: \[([^\]]*)\]",(DIAG/'helper-axioms.raw').read_text())}
    roots.update({name:set() for name in re.findall(r"'([^']+)' does not depend on any axioms",(DIAG/'helper-axioms.raw').read_text())})
    assert set(roots)==set(audit['names'])
    for name,axioms in audit['reports'].items():assert roots[name]==set(axioms)<=set(audit['allowed_axioms'])
    log=(DIAG/'replay.log').read_text()
    assert all(s in log for s in ('[statement] ok','Submission replays cleanly','VerifyFull replays cleanly','[helper-axioms] ok'))
    assert '[score] ok' not in log
    temporal=ROOT/'competitions/floatlib/candidates/f01-r19-dev-temporal-b2-1/Kernel.lean'
    def namespace(raw,name):return raw.split(b'namespace '+name.encode(),1)[1].split(b'end '+name.encode(),1)[0]
    old_namespace=namespace(kernel.read_bytes(),'Submission.R19Temporal')
    assert old_namespace==namespace(temporal.read_bytes(),'Submission.R19Temporal') and sha(temporal)=='c70cf9479ca48b4690990ebbd0b3781139cbeb94e46b28bbe61563e3eeaced1c'
    C=(DIAG/'candidate-generated-0.c').read_text();main=(DIAG/'candidate-generated-1.c').read_text()
    public=P+'Submission_bmm';dispatch=P+'Submission_R19DualTemporal_dispatch';output=P+'Submission_R19DualTemporal_output'
    row=P+'Fin_foldl_loop___at___00Submission_R19DualTemporal_output_spec__2'
    pair=P+'Fin_foldl_loop___at___00Submission_R19DualTemporal_output_spec__1___redArg'
    emit=P+'Fin_foldl_loop___at___00Submission_R19DualTemporal_output_spec__0'
    loop=P+'Submission_R19DualTemporal_loop___redArg';wrapper=P+'Submission_R19DualTemporal_loop';old=P+'Submission_R19Temporal_loop'
    pack=P+'Submission_R19DualTemporal_packOutput';packrow=P+'Fin_foldl_loop___at___00Submission_R19DualTemporal_packOutput_spec__1';packpoint=P+'Fin_foldl_loop___at___00Submission_R19DualTemporal_packOutput_spec__0'
    names=[public,dispatch,output,row,pair,loop,wrapper,emit,pack,packrow,packpoint,old,P+'Submission_R19Temporal_packB',P+'Submission_Packed10_finish']
    fs={n:function(C,n) for n in names};assert '.m_fun = (void*)lp_competition_Submission_bmm' in main
    paths=[[public,dispatch,output,row,pair,loop],[output,pack,packrow,packpoint]];edges=[]
    for path in paths:
        for parent,child in zip(path,path[1:]):
            assert count(fs[parent],child)>=1
            edges.append({'caller':parent,'C_line':fs[parent]['line'],'callee':child,'static_sites':count(fs[parent],child)})
    assert count(fs[output],pack)==count(fs[output],P+'Submission_R19Temporal_packB')==1
    assert count(fs[pack],'lean_mk_empty_array_with_capacity')==1
    assert count(fs[packrow],'lean_mk_empty_array_with_capacity')==0
    assert count(fs[pair],pack)==count(fs[pair],old)==count(fs[pair],wrapper)==0 and count(fs[pair],loop)==1
    for name in (loop,pair,row,emit,pack,packrow,packpoint):
        assert not any(s in fs[name]['text'] for s in ('lean_alloc_closure','lean_apply','lean_box_float32'))
    assert count(fs[loop],'lean_float32_of_bits')==0 and count(fs[old],'lean_float32_of_bits')==7
    assert count(fs[packpoint],'lean_float32_of_bits')==4 and count(fs[packpoint],'lean_alloc_ctor')==2
    assert count(fs[pair],'lean_nat_div')==1  # Retained pergroup address work, not newly hoisted.
    assert count(fs[loop],'lean_alloc_ctor')==count(fs[old],'lean_alloc_ctor')==4 # Mutually exclusive terminal branches.
    assert 'lean_dec_ref(v_packedA_' in fs[output]['text'] and 'lean_dec_ref(v_packedB_' in fs[output]['text']
    (HERE/'selected-chain.c.txt').write_text('\n'.join('// ORIGINAL C line '+str(fs[n]['line'])+'\n'+fs[n]['text'] for n in names),encoding='utf-8')
    index=json.loads((DIAG/'native-assembly-index.json').read_bytes());byname={x.get('symbol'):x for x in index if x.get('symbol')}
    assert loop in byname and old in byname and wrapper in byname and pair not in byname
    newasm=asm_body((DIAG/byname[loop]['file']).read_text(),loop);oldasm=asm_body((DIAG/byname[old]['file']).read_text(),old)
    for n,raw in (('new-redArg.asm.txt',newasm),('old-temporal-loop.asm.txt',oldasm)):(HERE/n).write_text(raw+'\n',encoding='utf-8')
    assert 'R_X86_64_' not in newasm+oldasm
    nr=[(0x50,0x68),(0x90,0x9a),(0x9c,0xca),(0xd0,0xd2),(0xe3,0x11b),(0x12c,0x1bd)]
    older=[(0x50,0x68),(0x130,0x13c),(0x85,0x129),(0x1f5,0x232),(0x234,0x287),(0x384,0x3bf),(0x476,0x48a),(0x48c,0x4cd),(0x585,0x60d)]
    fastnew=select_path(instructions(newasm),nr);fastold=select_path(instructions(oldasm),older)
    assert not any(i['mnemonic'].startswith('call') for i in fastnew)
    calls_old=[hex(i['address']) for i in fastold if i['mnemonic'].startswith('call')];assert calls_old==['0x221','0x276','0x479','0x585']
    def stack_float(ins):return [i for i in ins if '[rsp' in i['operands'] and ('xmm' in i['operands'])]
    assert len(stack_float(fastnew))==2 and len(stack_float(fastold))==16
    save('native-paths.json',{'scope':'Captured nominal callee bodies only; call target identities lack relocation, selected pair native body is absent. Counts document removed work, not speed.',
        'new_full4_smallNat_ranges':[[hex(a),hex(b)]for a,b in nr],'old_full4_smallNat_ranges':[[hex(a),hex(b)]for a,b in older],
        'new_path':fastnew,'old_path':fastold,'new_call_instructions':0,'old_call_sites':calls_old,
        'new_vector_stack_moves':stack_float(fastnew),'old_vector_stack_moves':stack_float(fastold),
        'new_stack_frame_bytes':184,'old_stack_frame_bytes':200,'both_push_count':6})
    compile_trace=json.loads((DIAG/'build-trace-11.txt').read_bytes());argv=[x['message'][3:] for x in compile_trace['log'] if x['message'].startswith('.> ')]
    assert len(argv)==1;argv=shlex.split(argv[0]);assert '-O3' in argv and '-ffp-contract=off' in argv
    assert not any(x.startswith('-flto')for x in argv)
    report={'at_utc':datetime.now(timezone.utc).isoformat(),'run':40435830288,'source_commit':inventory['artifact']['workflow_run']['head_sha'],
        'all135_original_hashes_verified':True,'source_sha256':SOURCE,'source_bytes':241509,'current_manifest_sha256':sha(candidate/'manifest.json'),
        'proof':{'statement':True,'complete_Submission_and_VerifyFull_replay':True,'explicit_roots':audit['names'],'reports':audit['reports'],'allowed_axioms':audit['allowed_axioms'],'accepted18':True,'full_gate':'NOT_RUN','performance':'UNKNOWN'},
        'Submission_C_sha256':sha(DIAG/'candidate-generated-0.c'),'MainFull_C_sha256':sha(DIAG/'candidate-generated-1.c'),'statement_object_sha256':byname[loop]['object_sha256'],
        'actual_compile_argv':argv,'environment':json.loads((RAW/'environment.json').read_bytes()),'selected_C_edges':edges,
        'old_c70_namespace_exact_raw_equal':{'bytes':len(old_namespace),'sha256':hashlib.sha256(old_namespace).hexdigest(),'source_sha256':sha(temporal)},
        'increment_relative_c70':{'removed':'Repeated pergroup rawA reads/unbox/bounds+four of_bits perfull4 block and their cross-call B8/A temporary saves; validA decoding moves to once-percall preparation.',
            'not_removed':'B8 packing/valid B decoding/destruction, ordered two MAC chains, F2 terminal result, finish/NaN replay, output boxes/push, original raw inputs; no c70 result tiles existed to delete.',
            'added':'One flat preparedA Array and one16B Float32 payload A4 record perrow perceil(n/4), tail padding, writes/reads/reference handling/destruction/peak memory.',
            'count_model':'rows=batch*m,T=ceil(n/4),G=ceil(p/2): old validA decodes rows*G*n; new rows*n; new A4 records rows*T. Counts are not time.',
            'ordinary_hot_observation':'Captured redArg full4 smallNat path has no call or codec, fixed A4 fields and B8 fields, 4ordered mulps/addps stages; retains one16B accumulator reload/store perblock and pointer stack loads. Cold bigNat/tail/terminal calls remain.',
            'pergroup_address_work':'row/m and raw replay bases remain pergroup in selectedC, as c70; no claim of row hoisting.'},
        'relative_B2':'Also includes the already-known c70 B8 layout and4k unrolling versus retainedB2; valid B decoding is not eliminated. Do not count inherited c70 gains as new Dual gain or presume Float32 input boxes existed in B2.',
        'native_selected_body_status':'Actual selectedC calls loop___redArg directly; this body and oldTemporal loop are captured. Plain loop is only an8byte wrapper. Final selected pair caller ASM/relocations/ELF absent, so native edge/inlining cannot be independently closed.',
        'decision':'WORTH_ONE_CLEAN_ORIGINAL_FULL_DISCOVERY_D_TO_MEASURE_NET_LIFECYCLE_COST_NO_GAIN_PROMISE',
        'decision_reason':'C realizes new independent reuse mechanism and captured nominal full4 body removes regular codecs/cross-call saves without new hot apply or boxes. Global A preparation/destruction is the remaining real tradeoff; full original cost is needed and may still lose.',
        'gate_unchanged':'whole<=.97 plus original positivep05/full gate/controls; diagnostic18root pass does not substitute, no adoption or confirmation claim.',
        'limits':'One statement-only runner. No local Lean/Git/CI/global/candidate edits; no timing result read for this new source and no speed estimate from counts.'}
    save('review.json',report)
    print(json.dumps({'originals':135,'roots':18,'C_edges':len(edges),'A_pack_once':True,'B_pack_once':True,'full4_new_calls':0,'old_full4_calls':4,'new_stack_float_moves':2,'old_stack_float_moves':16,'decision':report['decision']},indent=2))
if __name__=='__main__':main()
