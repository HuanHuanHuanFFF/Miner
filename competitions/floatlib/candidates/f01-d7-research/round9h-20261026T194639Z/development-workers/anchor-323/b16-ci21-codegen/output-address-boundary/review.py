"""Only CI21 existing emit/group C/ASM. No source edits, math or all-raw re-audit."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
RAW=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40445341829/download-41554c5bc7e9461dbeb887ed8d86d23f'
DIAG=RAW/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-column4-broad2'
P='lp_competition_';EMIT=P+'Fin_foldl_loop___at___00Submission_R19Column4Temporal_output_spec__0';GROUP=P+'Fin_foldl_loop___at___00Submission_R19Column4Temporal_output_spec__1___redArg'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(name,v):(HERE/name).write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
def function(text,name):
    m=re.search(r'^LEAN_EXPORT [^\n]*\b'+re.escape(name)+r'\([^\n]*\)\{',text,re.M);assert m
    level=0
    for i in range(m.end()-1,len(text)):
        if text[i]=='{':level+=1
        if text[i]=='}':
            level-=1
            if not level:return {'line':text.count('\n',0,m.start())+1,'text':text[m.start():i+1]+'\n'}
def parse(text,name):
    a=text.index('0000000000000000 <'+name+'>:');b=text.find('\nDisassembly of section ',a);result=[]
    for lineno,line in enumerate(text[a:b if b>=0 else len(text)].splitlines(),1):
        r=re.match(r'\s*([0-9a-f]+):\s+(R_X86_64_\S+)\s+(\S+)',line)
        if r:result[-1].setdefault('relocations',[]).append({'offset':int(r[1],16),'target':re.sub(r'-0x[0-9a-f]+$','',r[3])});continue
        m=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)',line)
        if m:result.append({'address':int(m[1],16),'mnemonic':m[2],'operands':m[3]})
    return result

def main():
    previous=json.loads((HERE.parent/'review.json').read_bytes());cpath=DIAG/'candidate-generated-0.c'
    assert sha(cpath)==previous['Submission_C_sha256']
    index=json.loads((DIAG/'native-assembly-index.json').read_bytes());items={x.get('symbol'):x for x in index if x.get('symbol')}
    for name in (EMIT,GROUP):assert sha(DIAG/items[name]['file'])==items[name]['sha256'] and items[name]['object_sha256']==previous['statement_object_sha256']
    C=cpath.read_text();functions=[function(C,n)for n in (GROUP,EMIT,P+'Submission_Packed10_finish')]
    (HERE/'C-boundary.txt').write_text('\n'.join('// OriginalC line '+str(f['line'])+'\n'+f['text'] for f in functions),encoding='utf-8')
    emit=parse((DIAG/items[EMIT]['file']).read_text(),EMIT);group=parse((DIAG/items[GROUP]['file']).read_text(),GROUP)
    e={i['address']:i for i in emit}
    assert e[0x28]['mnemonic']==e[0x47]['mnemonic']==e[0x182]['mnemonic']=='mul'
    assert e[0x28]['operands']=='r14' and e[0x47]['operands']=='r14' and '[rsp+0x38]' in e[0x182]['operands']
    assert e[0x17d]['mnemonic']=='je' and '+0x1b0>' in e[0x17d]['operands']
    assert e[0x3d8]['mnemonic']=='jmp' and '+0xf0>' in e[0x3d8]['operands']
    assert all(e[a]['mnemonic']=='ucomiss' for a in (0x230,0x36d,0x47d,0x4fd))
    assert any(r['target']=='lean_float32_to_bits' for r in e[0x376].get('relocations',[]))
    assert any(r['target'].endswith('R7NaNReplay_replayLoop') for r in e[0x4bb].get('relocations',[]))
    assert not any(r['target'].endswith('Packed10_finish') for i in emit for r in i.get('relocations',[])) # Finish is inlined.
    assert any(r['target']==EMIT for i in group for r in i.get('relocations',[]))
    # Only preheader writes cached r*n and bi*n. No cached whole bi*n*p is updated in lane loop.
    writes=lambda slot:[i for i in emit if i['mnemonic'].startswith('mov') and i['operands'].startswith('QWORD PTR [rsp+'+slot+'],')]
    assert [i['address'] for i in writes('0x68')]==[0xad]
    assert [i['address'] for i in writes('0x60')]==[0xd0]
    assert e[0x1c6]['mnemonic']=='add' and e[0x1f4]['mnemonic']=='add'
    wanted=[0x28,0x47,0xad,0xd0,0xf0,0x17d,0x182,0x1c6,0x1f4,0x230,0x36d,0x370,0x376,0x3b7,0x3d8,0x47d,0x480,0x486,0x4bb,0x4fd,0x500]
    save('native-evidence.json',{'emit_symbol':EMIT,'group_symbol':GROUP,'instructions':[e[a]for a in wanted],
        'actual_group_to_emit_edges':[i for i in group if any(r['target']==EMIT for r in i.get('relocations',[]))]})
    report={'at_utc':datetime.now(timezone.utc).isoformat(),'input_run':40445341829,'source_sha256':'bb058c75f59ca36b4952cffae0c943fd296de02cb3e83d164409736b0252c061',
        'scope':'ExistingCI21 selectedemit/group C+ASM only; reuse130-file binding and accepted source audit, no math/fullraw repeat and no D22 read.',
        'bound_files':[{'path':p.relative_to(ROOT).as_posix(),'sha256':sha(p)}for p in (cpath,DIAG/items[EMIT]['file'],DIAG/items[GROUP]['file'],DIAG/'native-assembly-index.json',HERE.parent/'review.json')],
        'C_edges':{'group_line':functions[0]['line'],'emit_line':functions[1]['line'],'finish_line':functions[2]['line'],
            'behavior':'Cemit eagerly computes r*n,bi*n,(bi*n)*p+4g+j before selecting lane andcalling Packed10.finish. FinishC only uses addresses in NaN branch. Nativefinish has been inlined intoemit.'},
        'native_partial_CSE':{'r_times_n':'mul0x28 inpreheader, taggedcache rsp+0x68@0xad; ordinary smallNat no overflow reused everylane',
            'bi_times_n':'mul0x47 inpreheader, taggedcache rsp+0x60@0xd0; reused ordinarylane loop',
            'residual_hot':'mul0x182=(bi*n)*p inside loop@f0 before everylaneNaN test; add4g@1c6 thenj@1f4 alsohot. Backedge3d8→f0 repeats it; no fullproduct cache store.',
            'bi_zero_exception':'Ifbi*n==0, branch17d→1b0 skips residualmul; do not claim allfinite outputs repeat multiplication. Ordinarynonzero-batch addresses do.',
            'bigNat_boundary':'Perlane big/overflow helper calls remain beforeNaN tests; ordinaryCSE claims above are limited to smallNat/nonoverflow, not allNat execution.'},
        'normal_and_nan':{'lane_tests':['0x36d lane0','0x47d lane1','0x230 lane2','0x4fd lane3'],
            'finite':'NonNaN joins376→lean_float32_to_bits(rel377)→array_push3b7(rel3b8)→backedge3d8; addresswork precedes tests andexecutes withoutreplay.',
            'NaN':'Unorderedtests enter486; actualreplayLoop call4bb(rel4bc), usingbaseA/baseB alreadycomputed. No finite callto replayLoop.',
            'conclusion':'Threeperlane Csites is not three repeatednativemuls: twoordinary products alreadyhoisted. Only residualBbase product/adds are a live hot-sharing opportunity.'},
        'decision':'SCOPED_GO_GROUP_BBASE_CACHE_ONLY_NO_GO_R_TIMES_N_REWRITE_OR_THREE_REPEATED_MUL_CLAIM',
        'minimal_followup_design':'In a separate future unfrozen source, bind baseB=bi.val*n*p+4*g.val once in group just before RowStream.emit; callback passes baseB+j.val to unchanged Packed10.finish. Leave r*n optimization alone because nativealreadyhoists it. Do not invokeNaN replay earlier or add a finish/helper noinline hotcall.',
        'why_no_cold_work_is_pulled_forward':'Currentselected validFin group has>=1 output andalready executes the sameBbase workbeforefinite/NaN tests. Moving it fromeverylane tooncegroup does not introduce workcurrentlyguardedbyNaN. Keep originalfinish branch unchanged.',
        'lifecycle_and_codegen_obligations':'One NatBbase lives across up to4emit iterations; ordinarysmallNat is taggedimmediate, but bigNat allocation/RC/free lifetime mustbecharged. Callbackcapture set changes: specialization could erase it or produce a newclosure/stackpressure; mustinspect exactfuture selectedcaller, not assume. CurrentrawA/B/F4 lifetime andfinish/output/checksum/destruction remain.',
        'not_authorized_or_claimed':'No source written,no newCI,no change toD22 frozen source/no D22inputs/results read. ThisGO is one localized implementation opportunity forD toselect later, not measuredspeed or completeD/adoption advice.'}
    save('review.json',report)
    print(json.dumps({'actual_emit_finish_inlined':True,'first_two_muls_preheader':True,'remaining_mul_hot_perlane_nonzero_bi':True,'bi0_skip':True,'decision':report['decision']},indent=2))
if __name__=='__main__':main()
