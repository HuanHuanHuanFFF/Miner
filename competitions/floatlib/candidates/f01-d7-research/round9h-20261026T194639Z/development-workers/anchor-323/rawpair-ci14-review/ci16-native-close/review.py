"""CI16 native closure only; reuse CI14 C/proof findings, no rebuild or new experiment."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40436948264'
RAW=RUN/'download-2f6165a21e5d4de0b18207e85d2f3b4f'
DIAG=next(p for p in RAW.rglob('f01-r19-dev-dc-rawpair2') if (p/'native-assembly-index.json').is_file())
SOURCE='6a0c18c52d736a1b8856877d6056372e13f70b095e36e34bd05203bcb7a5d1c0'
OLD='lp_competition_Submission_NativeFinal_dotLoop'
NEW='lp_competition_Submission_R19DCRawPair_loop'
CALLER='lp_competition_Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__2'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(name,value):(HERE/name).write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
def body(text,name):
    start=text.index('0000000000000000 <'+name+'>:');end=text.find('\nDisassembly of section ',start)
    return text[start:end if end>=0 else len(text)]
def parse(text):
    out=[]
    for line in text.splitlines():
        m=re.match(r'\s*([0-9a-f]+):\s+(R_X86_64_\S+)\s+(\S+)',line)
        if m:
            assert out
            out[-1].setdefault('relocations',[]).append({'offset':int(m[1],16),'kind':m[2],'target':re.sub(r'-0x[0-9a-f]+$','',m[3])})
            continue
        m=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)',line)
        if m:out.append({'address':int(m[1],16),'mnemonic':m[2],'operands':m[3]})
    return out
def path(ins,ranges):
    selected=[i for lo,hi in ranges for i in ins if lo<=i['address']<=hi]
    assert len(selected)==len({i['address'] for i in selected})
    return selected
def summary(ins):
    floating=[i for i in ins if '[rsp' in i['operands'] and 'xmm' in i['operands']]
    size=lambda i:16 if 'XMMWORD PTR' in i['operands'] else 8 if 'QWORD PTR' in i['operands'] else 4 if 'DWORD PTR' in i['operands'] else 1
    return {'instructions':len(ins),'conditional_branches':sum(i['mnemonic'].startswith('j') and i['mnemonic']!='jmp' for i in ins),
        'unconditional_branches':sum(i['mnemonic']=='jmp' for i in ins),'calls':[i for i in ins if i['mnemonic'].startswith('call')],
        'floating_stack_moves':floating,'floating_stack_access_bytes':sum(size(i) for i in floating),
        'other_explicit_stack_accesses':sum('[rsp' in i['operands'] and 'xmm' not in i['operands'] for i in ins)}

def main():
    inventory=json.loads((RUN/'original-artifact-hashes.json').read_bytes());bindings=[]
    for name,item in inventory['files'].items():
        p=RAW/name;assert sha(p)==item['sha256'] and p.stat().st_size==item['bytes'],name
        bindings.append({'path':p.relative_to(ROOT).as_posix(),**item})
    assert len(bindings)==150
    save('all-originals.json',{'run':40436948264,'source_commit':inventory['artifact']['workflow_run']['head_sha'],'archive_digest':inventory['artifact']['digest'],
        'hash_receipt_sha256':sha(RUN/'original-artifact-hashes.json'),'count':150,'files':bindings})
    prior=json.loads((HERE.parent/'review.json').read_bytes());assert prior['source_sha256']==SOURCE
    assert sha(DIAG/'candidate-generated-0.c')==prior['Submission_C_sha256']
    assert sha(DIAG/'candidate-generated-1.c')==prior['MainFull_C_sha256']
    kernel=next(p for p in RAW.rglob('Kernel.lean') if 'f01-r19-dev-dc-rawpair2' in str(p));assert sha(kernel)==SOURCE
    index=json.loads((DIAG/'native-assembly-index.json').read_bytes());byname={x.get('symbol'):x for x in index if x.get('symbol')}
    texts={};ins={}
    for name,label in ((OLD,'old-dot'),(NEW,'new-pair'),(CALLER,'actual-pair-caller')):
        item=byname[name];assert item['kernel_sha256']==SOURCE and item['object_sha256']==prior['statement_Submission_object_sha256']
        p=DIAG/item['file'];assert sha(p)==item['sha256']
        texts[name]=body(p.read_text(),name);ins[name]=parse(texts[name]);(HERE/(label+'.asm.txt')).write_text(texts[name]+'\n',encoding='utf-8')
    def targets(instructions):return {r['target'] for i in instructions if i['mnemonic'].startswith('call') for r in i.get('relocations',[])}
    calltargets=targets(ins[CALLER]);assert NEW in calltargets and OLD not in calltargets
    new_call=next(i for i in ins[CALLER] if any(r['target']==NEW for r in i.get('relocations',[])))
    assert new_call['address']==0x194
    assert any(r['target'].endswith('output_spec__0') for i in ins[CALLER] for r in i.get('relocations',[]))
    assert any(r['target'].endswith('output_spec__1') for i in ins[CALLER] for r in i.get('relocations',[]))
    # Same legal inbounds small-Nat work; k>0 avoids first-iteration zero multiply shortcut.
    nr=[(0x90,0x146),(0x2c2,0x2ce),(0x163,0x285)]
    oldr=[(0x70,0x119),(0x213,0x220),(0x137,0x1d0)]
    # k=0 is kept separately because n may be2 and entry cost is material.
    nzero=[(0x90,0x132),(0x159,0x285)];ozero=[(0x70,0x105),(0x12c,0x1d0)]
    newp=path(ins[NEW],nr);oldp=path(ins[OLD],oldr);new0=path(ins[NEW],nzero);old0=path(ins[OLD],ozero)
    sn,so,sn0,so0=map(summary,(newp,oldp,new0,old0))
    assert len(sn['calls'])==3 and len(so['calls'])==2 and len(sn0['calls'])==3 and len(so0['calls'])==2
    assert targets(newp)==targets(oldp)=={'lean_float32_of_bits'}
    assert len(sn['floating_stack_moves'])==6 and sn['floating_stack_access_bytes']==96
    assert len(so['floating_stack_moves'])==4 and so['floating_stack_access_bytes']==16
    assert 'sub    rsp,0xa8' in texts[NEW] and 'sub    rsp,0x58' in texts[OLD]
    assert {'lean_inc_heartbeat','mi_malloc_small'}<=targets(ins[NEW])
    assert 'mi_malloc_small' not in targets(ins[OLD]) and 'lean_inc_heartbeat' not in targets(ins[OLD])
    assert 'lean_dec_ref_cold' in calltargets
    assert not any('lean_apply' in x or 'lean_box_float' in x for x in calltargets)
    compare={'scope':'One complete pair versus two sequential scalar dots; legal inbounds small-Nat paths. Instruction/branch/byte counts do not predict latency.',
        'new_steady':sn,'old_one_dot_steady':so,'new_k0':sn0,'old_one_dot_k0':so0,
        'equal_pair_steady':{'codec_calls_new':3,'codec_calls_old':4,'floating_stack_moves_new':6,'floating_stack_moves_old':8,
            'floating_stack_access_bytes_new':96,'floating_stack_access_bytes_old':32,
            'conditional_branches_new':sn['conditional_branches'],'conditional_branches_old_two_dots':2*so['conditional_branches'],
            'other_explicit_stack_accesses_new':sn['other_explicit_stack_accesses'],'other_explicit_stack_accesses_old_two_dots':2*so['other_explicit_stack_accesses'],
            'FP_work':'new one mulps+addps for two lanes; old two mulss+addss. Original order perlane retained; no speed conversion.'},
        'frame':'New168B+6push versus old88B+6push per sequential call; old frames do not coexist, so comparing new168 against summed176 would be misleading.',
        'first_and_terminal':'k0 shortcuts kept separately; old two independent function entries/returns versus new one loop plus terminal heapF2. n=2 makes fixedcost especially relevant.',
        'new_path':newp,'old_one_dot_path':oldp}
    save('equal-work-native.json',compare)
    report={'at_utc':datetime.now(timezone.utc).isoformat(),'run':40436948264,'source_commit':inventory['artifact']['workflow_run']['head_sha'],
        'all150_originals_hash_verified':True,'exact_source_sha256':SOURCE,'CI14_C_and_proof_reused_not_redone':{'review_sha256':sha(HERE.parent/'review.json'),
            'Submission_C_identical':True,'MainFull_C_identical':True,'statement_object_sha256_same':prior['statement_Submission_object_sha256'],'correctness':prior['correctness']},
        'native_artifacts':{name:byname[name] for name in (OLD,NEW,CALLER)},
        'closed_machine_edge':'Actual Fin paircaller0x194 PLT relocation directly calls RawPair.loop once;0x1c5 calls emit spec0. It is not an unused export helper or an inline/clone surrogate.',
        'odd_boundary':'Caller0x253 and cold360 target spec1; inherited unchangedC executes exactly one olddot for oddcount1. n<=1/p<=1 fallback and original dispatch guards unchanged; no performance observation outside their domain.',
        'new_terminal_cost':'Newloop0x5f9 lean_inc_heartbeat,0x603 mi_malloc_small withedi16; F2 twoFloat32 payload stored once. Actualcaller afteremit has RC test then0x40c lean_dec_ref_cold. OlddotLoop returnsFloat32 with no F2/heartbeat/malloc. Output boxes/finish/replay remain.',
        'normal_work_tradeoff':'3codec calls versus4; one iteration stream versus two; stackmove instructioncount6versus8 but actual FP stackbytes96versus32 and larger peak frame. Some branch/address work and two-lane FP instructions reduce; fixedpair count/emit/F2 costs added.',
        'positive_native_details':'SharedA andk*p, one iteration counter stream, normal smallNat baseB+1 precomputed in prologue (0x38/0x46), fewer branch/integer stack accesses and two-lane MAC are retained as genuine advantages. Their latency contribution is UNKNOWN.',
        'decision':'PARK_EXACT6A0C_NO_ORIGINAL_FULL_D_NO_NEW_VARIANT_REQUEST',
        'reason':'The native edge is now closed but the necessary cost premise is not strong: only25% codec-call removal is accompanied by3xFP stacktraffic and a new terminal allocation/free. Affected whole domain about5.98% needs about50.18% complete-local saving for3%whole; machine counts alone do not justify buying a scarce completeD.',
        'not_claimed':'No numeric speedup bound, regression proof, fullgate result or success probability. Stackbyte count is not a latency model; nonlinear/cache/call effects remainUNKNOWN.',
        'comparison_limit':'Hot counts compare one newloop to two olddotLoop bodies plus the nowclosed new paircaller. Old full NativeFinal.dot wrapper/finish native and complete output native were not recopied; their preservedC/14root semantics are inherited fromCI14. This is not a complete latency model.',
        'scope':'CI16statement object only, no runtime timing for6a0c. D17 c36 frozenwork neither read nor modified. No Git/CI/localLean/global/candidate changes.'}
    save('review.json',report)
    print(json.dumps({'all_originals':150,'native_caller_edge':True,'new_calls':3,'old_calls_equal_work':4,'new_FP_stack_bytes':96,'old_FP_stack_bytes_equal_work':32,
        'conditional_branches_new':sn['conditional_branches'],'conditional_branches_old_equal_work':2*so['conditional_branches'],'decision':report['decision']},indent=2))
if __name__=='__main__':main()
