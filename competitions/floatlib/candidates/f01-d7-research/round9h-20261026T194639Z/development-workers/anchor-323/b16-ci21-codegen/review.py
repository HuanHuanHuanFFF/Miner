"""CI21 exact codegen closure; read original130 files, no math re-audit/build/timing."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib
import json
import re
import shlex

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40445341829'
RAW=RUN/'download-41554c5bc7e9461dbeb887ed8d86d23f'
DIAG=next(p for p in RAW.rglob('f01-r19-dev-column4-broad2') if (p/'native-assembly-index.json').is_file())
P='lp_competition_'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(name,v):(HERE/name).write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
def function(text,name):
    m=re.search(r'^LEAN_EXPORT [^\n]*\b'+re.escape(name)+r'\([^\n]*\)\{',text,re.M);assert m,name
    depth=0
    for i in range(m.end()-1,len(text)):
        if text[i]=='{':depth+=1
        if text[i]=='}':
            depth-=1
            if depth==0:return {'line':text.count('\n',0,m.start())+1,'text':text[m.start():i+1]+'\n'}
    raise AssertionError(name)
def calls(f,n):return len(re.findall(r'\b'+re.escape(n)+r'\(',f['text'].split('\n',1)[1]))
def body(text,name):
    a=text.index('0000000000000000 <'+name+'>:');b=text.find('\nDisassembly of section ',a);return text[a:b if b>=0 else len(text)]
def parse(text):
    out=[]
    for line in text.splitlines():
        r=re.match(r'\s*([0-9a-f]+):\s+(R_X86_64_\S+)\s+(\S+)',line)
        if r:
            out[-1].setdefault('relocations',[]).append({'offset':int(r[1],16),'kind':r[2],'target':re.sub(r'-0x[0-9a-f]+$','',r[3])});continue
        m=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)',line)
        if m:out.append({'address':int(m[1],16),'mnemonic':m[2],'operands':m[3]})
    return out
def targets(ins):return {r['target'] for i in ins for r in i.get('relocations',[]) if i['mnemonic'].startswith('call')}

def main():
    inventory=json.loads((RUN/'original-artifact-hashes.json').read_bytes());bound=[]
    for name,item in inventory['files'].items():
        path=RAW/name;assert sha(path)==item['sha256'] and path.stat().st_size==item['bytes'],name
        bound.append({'path':path.relative_to(ROOT).as_posix(),**item})
    assert len(bound)==130
    save('all-originals.json',{'run':40445341829,'source_commit':inventory['artifact']['workflow_run']['head_sha'],'archive_digest':inventory['artifact']['digest'],
        'hash_receipt_sha256':sha(RUN/'original-artifact-hashes.json'),'count':130,'files':bound})
    accepted=[]
    for name,source,length,roots in [('f01-r19-dev-column4-core4','c7e7ad380238b3a7e848b460c28fd6bbe6d4aa5c354b57483ef1243b91eb844a',249694,13),
        ('f01-r19-dev-column4-broad2','bb058c75f59ca36b4952cffae0c943fd296de02cb3e83d164409736b0252c061',255724,20)]:
        d=next(p for p in RAW.rglob(name)if (p/'helper-audit.json').is_file());audit=json.loads((d/'helper-audit.json').read_bytes())
        kernel=next(p for p in RAW.rglob('Kernel.lean')if name in str(p));assert sha(kernel)==source and kernel.stat().st_size==length
        assert audit['accepted'] and audit['kernel_replay'] and audit['expected_count']==roots and audit['kernel_sha256']==source
        accepted.append({'name':name,'source_sha256':source,'bytes':length,'accepted_root_count':roots,'whole_modules_replayed':True,'receipt_sha256':sha(d/'helper-audit.json'),'scope':'Bind existing acceptance receipt only; no expanded math review.'})
    C=(DIAG/'candidate-generated-0.c').read_text();main=(DIAG/'candidate-generated-1.c').read_text()
    public=P+'Submission_bmm';dispatch=P+'Submission_R19Column4Temporal_dispatch';output=P+'Submission_R19Column4Temporal_output'
    row=P+'Fin_foldl_loop___at___00Submission_R19Column4Temporal_output_spec__2'
    group=P+'Fin_foldl_loop___at___00Submission_R19Column4Temporal_output_spec__1___redArg'
    emit=P+'Fin_foldl_loop___at___00Submission_R19Column4Temporal_output_spec__0'
    loop=P+'Submission_R19Column4Temporal_loop___redArg';pack=P+'Submission_R19Column4Temporal_packB'
    pack_outer=P+'Submission_R19Column4Temporal_packB___lam__0';inner=P+'Submission_R19Column4Temporal_pack';packet=P+'Submission_R19Column4Temporal_pack___lam__0'
    apack=P+'Submission_R19DualTemporal_packOutput';fallback=P+'Submission_R15PackedB2_dispatch'
    names=[public,dispatch,output,row,group,loop,emit,pack,pack_outer,inner,packet,apack,fallback]
    f={n:function(C,n)for n in names};assert '.m_fun = (void*)lp_competition_Submission_bmm' in main
    edges=[]
    for route in ([public,dispatch,output,row,group,loop],[output,pack],[pack_outer,inner]):
        for parent,child in zip(route,route[1:]):
            assert calls(f[parent],child)>0;edges.append({'caller':parent,'C_line':f[parent]['line'],'callee':child,'static_C_sites':calls(f[parent],child)})
    assert calls(f[dispatch],fallback)==4 and calls(f[dispatch],output)==1
    assert calls(f[public],P+'Submission_UnderflowZero_zeros')>=1
    assert calls(f[output],apack)==calls(f[output],pack)==1
    assert 'lean_dec_ref(v_PA_' in f[output]['text'] and 'lean_dec_ref(v_PB_' in f[output]['text']
    assert calls(f[group],loop)==1 and calls(f[group],apack)==calls(f[group],pack)==0
    assert calls(f[loop],'lean_float32_of_bits')==0 and calls(f[packet],'lean_float32_of_bits')==16
    assert calls(f[loop],'lean_alloc_ctor')==4 and 'lean_alloc_ctor(0, 0, 16)' in f[loop]['text']
    for n in (loop,group,emit):assert not any(s in f[n]['text'] for s in ('lean_alloc_closure','lean_apply','lean_box_float32','R19Temporal_pack','R19Column4Temporal_low','R19Column4Temporal_high','R19Column4Temporal_join'))
    assert calls(f[pack],'lean_alloc_closure')==calls(f[inner],'lean_alloc_closure')==1
    assert calls(f[packet],'lean_box_float32')==0 and 'lean_alloc_ctor(0, 0, 64)' in f[packet]['text']
    assert 'R19Temporal_' not in f[packet]['text']
    assert calls(f[group],'lean_alloc_ctor')==calls(f[row],'lean_alloc_ctor')==0
    (HERE/'selected-C.txt').write_text('\n'.join('// ORIGINAL C line '+str(f[n]['line'])+'\n'+f[n]['text'] for n in names),encoding='utf-8')
    ix=json.loads((DIAG/'native-assembly-index.json').read_bytes());byname={x.get('symbol'):x for x in ix if x.get('symbol')}
    native={}
    for name,label in ((group,'actual-group'),(loop,'actual-loop'),(emit,'actual-emit'),(pack,'packB'),(pack_outer,'packB-callback'),(inner,'inner-pack'),(packet,'actual-packet-callback')):
        item=byname[name];assert item['kernel_sha256']==accepted[1]['source_sha256'] and item['object_sha256']==byname[loop]['object_sha256']
        assert sha(DIAG/item['file'])==item['sha256'];text=body((DIAG/item['file']).read_text(),name);native[name]=parse(text)
        (HERE/(label+'.asm.txt')).write_text(text+'\n',encoding='utf-8')
    call=next(i for i in native[group]if any(r['target']==loop for r in i.get('relocations',[])));assert call['address']==0x1f6
    assert loop in targets(native[group])
    assert any(r['target']==P+'Submission_R19Column4Temporal_pack' for i in native[pack_outer] for r in i.get('relocations',[])) # Tail jump.
    nr=[(0x50,0x68),(0x90,0x9a),(0x9c,0xca),(0xd0,0xd2),(0xe3,0x11b),(0x12c,0x1b9)]
    fast=[i for lo,hi in nr for i in native[loop]if lo<=i['address']<=hi]
    assert not any(i['mnemonic'].startswith('call')for i in fast)
    stack=[i for i in fast if 'xmm' in i['operands'] and '[rsp' in i['operands']];assert len(stack)==2
    assert sum(i['mnemonic']=='mulps'for i in fast)==sum(i['mnemonic']=='addps'for i in fast)==4
    assert {'mi_malloc_small','lean_inc_heartbeat'}<=targets(native[loop])
    assert 'lean_dec_ref_cold' in targets(native[group])
    save('native-full4.json',{'domain':'smallNat/inbounds full4k normalpath; coldNat/tails/terminal retained','ranges_hex':[[hex(a),hex(b)]for a,b in nr],
        'path':fast,'codec_calls':0,'normal_calls':0,'floating_stack_moves':stack,'frame_bytes':184,'pushes':6,
        'new_group_edge':call,'terminal_F4':'mi_malloc_small requested24B,16B nativeFloat32 payload+header; group drops it afteremit',
        'not_speed_evidence':'SIMD/no-codec shape is mechanism verification, not new gain versus historicalR12 or an instruction-to-time conversion.'})
    trace_item=next(x for x in ix if x.get('kind')=='trace' and x['source'].endswith('/Submission.c.o.export.trace'))
    trace=json.loads((DIAG/trace_item['file']).read_bytes());commands=[x['message'][3:] for x in trace['log']if x['message'].startswith('.> ')]
    assert len(commands)==1;argv=shlex.split(commands[0]);assert '-O3' in argv and '-ffp-contract=off' in argv and not any(x.startswith('-flto')for x in argv)
    report={'at_utc':datetime.now(timezone.utc).isoformat(),'run':40445341829,'all130_original_hashes_verified':True,'acceptance_bound':accepted,
        'Submission_C_sha256':sha(DIAG/'candidate-generated-0.c'),'MainFull_C_sha256':sha(DIAG/'candidate-generated-1.c'),'statement_object_sha256':byname[loop]['object_sha256'],
        'actual_compile_argv':argv,'compile_trace_sha256':sha(DIAG/trace_item['file']),'environment':json.loads((RAW/'environment.json').read_bytes()),
        'selected_C_edges':edges,'actual_group_loop_native_relocation':call,'fallback_C':'Four miss arms allretainedPackedB2; truearm onlybroadoutput, outerUnderflowZero remains beforedispatcher.',
        'preparation':'OneA4 packOutput+oneB16 packB before rowfold, no perrow/group repetition; oneouterofFn closure plus oneinnerofFn closure perBpacketvector are real preparation costs. Packetcallback has16original codec sites and oneB16 record perpacket (mutually exclusive ctor branches), no Float32 boxes.',
        'no_B8_or_resulttile':'Selected loop/group/packet callback contains no low/high/join/B8 rebuilding or resulttile cache. Standalone exportedpacket is not mistaken for selectedpack___lam__0 body.',
        'hot_loop':'Actualgrouprelocation calls inspectedredArg; full4k normalpath no codec/dynamicapply/heap/call, fixed A4/B16 fields and four orderedlaneMAC. One16B accumulator reload/store perblock and pointerstackloads remain;184B frame,6push, coldNat/tail calls kept.',
        'terminal_and_emit':'OneF4 terminal per4columngroup, malloc24+heartbeat thenRCdrop afteremit. Up to4realoutput lane finish/replay/UInt32box/push retained. EmitC still exposes3Natmul address sites peroutput lane and group calls ix___redArg; do not assign0cost.',
        'broad_cost_boundary':'OldDualoverlapA4 mayalreadyexist, but newlyDC/wide routes acquire full A4/B16 preparation,residency,destruction. DC p3mod4 phantomlane remainscomputed notemitted. Originalfullpass finish/checksum/cleanup remaininside budget; no lifecycle moved outside.',
        'decision':'GO_ONE_CLEAN_ORIGINAL_FULL_D_NO_GAIN_PROMISE','criterion':'Originalwhole<=.97+positivep05/fullgate/controls unchanged; currentstatement/replay/20roots is not thatD or adoption.',
        'reason':'Actualselected code realizes the proposed mechanism with no hotdynamiccall or B8/resulttile rebuild. Remaining netA4/B16 preparation and output/lifecycle tradeoff requires completepass measurement.',
        'limits':'No timing sampled or futureD/confirmation inputs/results read. Capturedstatement object is not cleaned-uptimed object; finalELF/top-levelnativeentry edges not exported. No Git/CI/Lean/source edits or broader math review.'}
    save('review.json',report)
    print(json.dumps({'all_originals':130,'C_edges':len(edges),'native_group_call_hex':hex(call['address']),'hot_calls':0,'hot_FP_stack_moves':2,'decision':report['decision']},indent=2))
if __name__=='__main__':main()
