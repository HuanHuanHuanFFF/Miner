"""CI23 B-base codegen comparison only; no D22/D24/confirmation reads or source edits."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40448580465'
RAW=RUN/'download-56ee92c691a94f4dbaebe6f2980167fd'
NEW=RAW/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-column4-bbase1'
OLD=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40445341829/download-41554c5bc7e9461dbeb887ed8d86d23f/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-column4-broad2'
P='lp_competition_';EMIT=P+'Fin_foldl_loop___at___00Submission_R19Column4Temporal_output_spec__0';GROUP=P+'Fin_foldl_loop___at___00Submission_R19Column4Temporal_output_spec__1___redArg';LOOP=P+'Submission_R19Column4Temporal_loop___redArg'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(name,v):(HERE/name).write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
def function(text,name):
    m=re.search(r'^LEAN_EXPORT [^\n]*\b'+re.escape(name)+r'\([^\n]*\)\{',text,re.M);assert m
    depth=0
    for i in range(m.end()-1,len(text)):
        if text[i]=='{':depth+=1
        if text[i]=='}':
            depth-=1
            if not depth:return {'line':text.count('\n',0,m.start())+1,'text':text[m.start():i+1]+'\n'}
def body(text,name):
    a=text.index('0000000000000000 <'+name+'>:');b=text.find('\nDisassembly of section ',a);return text[a:b if b>=0 else len(text)]
def parse(text):
    out=[]
    for line in text.splitlines():
        r=re.match(r'\s*([0-9a-f]+):\s+(R_X86_64_\S+)\s+(\S+)',line)
        if r:out[-1].setdefault('relocations',[]).append({'offset':int(r[1],16),'target':re.sub(r'-0x[0-9a-f]+$','',r[3])});continue
        m=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)',line)
        if m:out.append({'address':int(m[1],16),'mnemonic':m[2],'operands':m[3]})
    return out
def calltargets(ins):return {r['target']for i in ins if i['mnemonic'].startswith('call')for r in i.get('relocations',[])}

def main():
    inventory=json.loads((RUN/'original-artifact-hashes.json').read_bytes());bound=[]
    for name,item in inventory['files'].items():
        p=RAW/name;assert sha(p)==item['sha256'] and p.stat().st_size==item['bytes'],name
        bound.append({'path':p.relative_to(ROOT).as_posix(),**item})
    assert len(bound)==92
    save('all-originals.json',{'run':40448580465,'source_commit':inventory['artifact']['workflow_run']['head_sha'],'archive_digest':inventory['artifact']['digest'],
        'receipt_sha256':sha(RUN/'original-artifact-hashes.json'),'count':92,'files':bound})
    audit=json.loads((NEW/'helper-audit.json').read_bytes());assert audit['accepted'] and audit['kernel_replay'] and audit['expected_count']==20
    assert audit['kernel_sha256']=='f49458b99475b1b7e4a368908c81590b7f357a06938f38d0df141ffa3df5dc5d'
    kernel=next(p for p in RAW.rglob('Kernel.lean')if 'f01-r19-dev-column4-bbase1' in str(p));assert sha(kernel)==audit['kernel_sha256'] and kernel.stat().st_size==255745
    items={};asm={};native={};fs={};bindings=[]
    for role,directory in (('old',OLD),('new',NEW)):
        ix=json.loads((directory/'native-assembly-index.json').read_bytes());items[role]={x.get('symbol'):x for x in ix if x.get('symbol')}
        C=(directory/'candidate-generated-0.c').read_text();fs[role]={n:function(C,n)for n in (EMIT,GROUP,LOOP)};asm[role]={};native[role]={}
        for name in (EMIT,GROUP,LOOP):
            item=items[role][name];p=directory/item['file'];assert sha(p)==item['sha256']
            assert item['object_sha256']==items[role][LOOP]['object_sha256']
            asm[role][name]=body(p.read_text(),name);native[role][name]=parse(asm[role][name])
            bindings.append({'role':role,'symbol':name,'path':p.relative_to(ROOT).as_posix(),'sha256':sha(p),'object_sha256':item['object_sha256']})
        (HERE/(role+'-C.txt')).write_text('\n'.join('// OriginalC line '+str(fs[role][n]['line'])+'\n'+fs[role][n]['text']for n in (GROUP,EMIT)),encoding='utf-8')
        for n,label in ((GROUP,'group'),(EMIT,'emit')):(HERE/(role+'-'+label+'.asm.txt')).write_text(asm[role][n]+'\n',encoding='utf-8')
    assert asm['old'][LOOP]==asm['new'][LOOP] # No new core call/spill hidden behind sourcelet.
    protected=['Submission_R19DualTemporal_packOutput','Submission_R19Column4Temporal_packB','Submission_R19Column4Temporal_pack','Submission_R19Column4Temporal_pack___lam__0','Submission_R15PackedB2_dispatch']
    oldC=(OLD/'candidate-generated-0.c').read_text();newC=(NEW/'candidate-generated-0.c').read_text()
    for name in protected:assert function(oldC,P+name)['text']==function(newC,P+name)['text']
    e={i['address']:i for i in native['new'][EMIT]};g={i['address']:i for i in native['new'][GROUP]}
    oldm=[i for i in native['old'][EMIT]if i['mnemonic']=='mul'];newm=[i for i in native['new'][EMIT]if i['mnemonic']=='mul']
    assert [i['address']for i in oldm]==[0x28,0x47,0x182]
    assert [i['address']for i in newm]==[0x4c] and all(i['address']<0xa0 for i in newm)
    assert e[0x102]['mnemonic']=='add' and '[rsp+0x48]' in e[0x102]['operands'] # CachedbaseB+j only.
    corecall=next(i for i in native['new'][GROUP]if any(r['target']==LOOP for r in i.get('relocations',[])));assert corecall['address']==0x1f4
    assert g[0x232]['mnemonic']==g[0x27f]['mnemonic']=='mul' and g[0x301]['mnemonic']=='add'
    emitcalls=[i for i in native['new'][GROUP]if any(r['target']==EMIT for r in i.get('relocations',[]))];assert {i['address']for i in emitcalls}=={0x609,0x718}
    for role in ('old','new'):
        for n in (GROUP,EMIT):
            assert not any(x in fs[role][n]['text']for x in ('lean_alloc_closure','lean_apply','lean_box_float32','lean_alloc_ctor'))
            assert not any(re.search(r'^(?:r\w+|QWORD PTR)',i['operands'])for i in native[role][n]if i['mnemonic']=='call')
    assert 'sub    rsp,0x68' in asm['old'][GROUP] and 'sub    rsp,0x68' in asm['new'][GROUP]
    assert 'sub    rsp,0x88' in asm['old'][EMIT] and 'sub    rsp,0x58' in asm['new'][EMIT]
    assert 'lean_dec(v_baseB_' in fs['new'][GROUP]['text']
    assert any('R7NaNReplay_replayLoop' in x for x in calltargets(native['new'][EMIT]))
    assert 'lean_float32_to_bits' in calltargets(native['new'][EMIT])
    # SourceC remains specializedwith onefewer emit parameter, not a newcapture closure.
    arity=lambda f:len(f['text'].split('\n',1)[0].split('(',1)[1].split(')',1)[0].split(','))
    assert arity(fs['old'][EMIT])==11 and arity(fs['new'][EMIT])==10
    save('native-evidence.json',{'old_emit_mul':oldm,'new_emit_mul':newm,'new_runDot_edge':corecall,'new_Bbase_after_runDot':[g[a]for a in (0x232,0x27f,0x301)],
        'new_emit_edges':emitcalls,'new_lane_add':e[0x102],'core_native_body_exact_equal':True,'bindings':bindings})
    report={'at_utc':datetime.now(timezone.utc).isoformat(),'run':40448580465,'all92_original_hashes_verified':True,'source_sha256':audit['kernel_sha256'],'source_bytes':255745,
        'accepted_whole_modules_and20roots_bound':True,'math_not_reaudited':True,'actual_native_object_sha256':items['new'][LOOP]['object_sha256'],
        'old_source':'CI21bb058c75; prioractualcallerC/ASM reused, not oldR12/helper surrogate',
        'actual_work_removed':'CI21ordinarynonzero-bi lane loopmul0x182=(bi*n)*p and+4g0x1c6 are absent inCI23emit. Newemit has only r*n mul0x4c beforelane loop0xa0; looponly adds cachedbaseB+j0x102.',
        'actual_group_placement':'Realgroup calls originalcore0x1f4(rel1f5), returns, computesbi*n0x232 and×p0x27f plus4g0x301 once, then passesbaseB toactualemit609/718(rel60a/719).',
        'partial_CSE_scope':'r*n andbi*n were already onceperemit inoldordinarypath; no claimthatall3Csites repeated. bi0 skippedoldresidualmul; relativeeffect there is chiefly groupbase addition/control removal. No unseenworkload share estimated.',
        'capture_and_RC':'Bothgroup/emit remain specializeddirectfunctions, no newheapclosure/apply/Float32box or ctor in C/nativecaller. Emit arity11→10. CacheNat baseB held across3/4realoutputs, groupreleasesafteremit; ordinarysmallNat taggedimmediate, BigNatallocation/RC lifetime remainsrealcost.',
        'stack_and_calls':'Groupbaseframe104Bunchanged, emit136→88B, same6savedpushes. Fourlanecore nativebody is byte-text identical withCI21, so no newcore spill/call. Addressarith movedgroup once; not replaced with perlanehelper.',
        'protected_C_bodies_exact_equal':protected,
        'finish_boundary':'Sameinlinedfinite to_bits versusNaN replayLoop remainsafterselect. Neitherreplay work norinput preparation is newly executedonfinitepath; outputrawA/B,F4/finish/checksum/destruction charged. No lifecycle exclusion.',
        'decision':'GO_ONE_PREDEFINED_F494_CLEAN_ORIGINAL_FULL_D_ONLY','criterion':'Originalwhole<=.97+positivep05/fullgate/controls unchanged, no guarantee of measuredgain/adoption.',
        'caveat':'Physicalwork reduction is confirmed; instruction/multiply/frame counts are not a latency or whole-gain model. Widergroup coldcode layout and all lifecycle may still lose. No numericgainpredicted.',
        'limits':'Statementobject capture only, not timedELF. No D22/D24/confirmation input/result read. No Git/CI/Lean, source/global/frozen files changed; no new route opened.'}
    save('review.json',report)
    print(json.dumps({'all_originals':92,'real_emitter_saved_work':True,'core_native_unchanged':True,'new_closure':False,'group_frame':104,'old_emit_frame':136,'new_emit_frame':88,'decision':report['decision']},indent=2))
if __name__=='__main__':main()
