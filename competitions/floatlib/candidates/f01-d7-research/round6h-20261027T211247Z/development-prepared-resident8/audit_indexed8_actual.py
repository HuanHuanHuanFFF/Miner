"""Independent326-file receipt subset/checksum/caller/native/case review; no run."""
from pathlib import Path
import collections
import hashlib
import json
import re
import sys

sys.dont_write_bytecode=True
from audit_actual_resident16 import functions

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
DIAG=HERE.parent/('ci-runs/40611570030/download-032e40387a464ca39810735e751bed51/'
    'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-indexed8-cost1')
RUN=DIAG/'runtime-cost'
SOURCE='8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
sha=lambda b:hashlib.sha256(b).hexdigest()


def eligible(c):return c['n']>1 and c['m']>=4 and c['p']>=2


def main():
    bindings={}
    def raw(p):
        b=p.read_bytes();bindings[str(p.relative_to(ROOT)).replace('\\','/')]=sha(b);return b
    def read(p):return json.loads(raw(p))
    run_folder=HERE.parent/'ci-runs/40611570030'
    originals=read(run_folder/'original-artifact-hashes.json')
    original_root=run_folder/originals['directory']
    original_bytes=0
    for name,expected in originals['files'].items():
        f=(original_root/name).resolve()
        assert f.is_relative_to(original_root.resolve())
        b=f.read_bytes()
        assert len(b)==expected['bytes'] and sha(b)==expected['sha256'],name
        original_bytes+=len(b)
    result=read(RUN/'result.json');prep=read(RUN/'prepare.json')
    assert result['complete'] and result['measurement_complete'] and result['official_originals_unchanged']
    assert result['source_sha256']==SOURCE
    ci=read(DIAG/'candidate-c-index.json');ai=read(DIAG/'native-assembly-index.json')
    selected_c=next(x for x in ci if x['module']=='Submission')
    c_raw=raw(DIAG/selected_c['file']);assert sha(c_raw)==selected_c['sha256']
    old=prep['original_build_before']
    assert sha(c_raw)==next(v for k,v in old.items() if k.endswith('/ir/Submission.c'))
    assert raw(RUN/'original-statement-Submission.c')==c_raw
    obj=next(v for k,v in old.items() if k.endswith('/ir/Submission.c.o.export'))
    symbol='lp_competition_Submission_R22IndexedResident8_wordLoop___redArg'
    asm_item=next(x for x in ai if x.get('symbol')==symbol)
    asm_raw=raw(DIAG/asm_item['file'])
    assert asm_item['object_sha256']==obj and asm_item['kernel_sha256']==SOURCE and sha(asm_raw)==asm_item['sha256']
    asm=asm_raw.decode().split('<'+symbol+'>:',1)[1].split('\nDisassembly of section ',1)[0]
    (HERE/'indexed8-actual-wordLoop.asm.txt').write_text(asm,encoding='utf-8')
    inst=[]
    for line in asm.splitlines():
        m=re.match(r'\s*([0-9a-f]+):\s+(\w+)\s*(.*)',line)
        if m:inst.append((int(m[1],16),m[2],m[3]))
    counts=collections.Counter(v[1] for v in inst)
    calls=re.findall(r'R_X86_64_PLT32\s+([^\s]+)',asm)
    assert not any('lean_nat_' in x or 'usize_to_nat' in x for x in calls)
    assert counts['mulps']==counts['addps']==2 and counts['mulss']==4
    raw_symbol='lp_competition_Submission_R22Resident8_loop'
    raw_item=next(x for x in ai if x.get('symbol')==raw_symbol)
    raw_asm_bytes=raw(DIAG/raw_item['file'])
    assert raw_item['object_sha256']==obj and sha(raw_asm_bytes)==raw_item['sha256']
    raw_asm=raw_asm_bytes.decode().split('<'+raw_symbol+'>:',1)[1].split('\nDisassembly of section ',1)[0]
    assert 'sub    rsp,0x118' in raw_asm
    q_stack=[{'address':hex(a),'instruction':op+' '+args} for a,op,args in inst
        if 0x10b<=a<=0x128 and '[rsp' in args]
    assert len(q_stack)==4
    fs=functions(c_raw.decode())
    wanted=('wordLoop___redArg','within___redArg','tile___redArg','tiles___redArg',
            'rows4___redArg','core___redArg','guarded')
    chosen={};bodies=[]
    for short in wanted:
        name='lp_competition_Submission_R22IndexedResident8_'+short
        f=fs[name];body=f['body'];bodies.append(body)
        chosen[short]={'line':f['line'],'body_sha256':sha(body.encode()),
            'runtime_float_arguments':f['args'].count('float '),'runtime_word_arguments':f['args'].count('size_t '),
            'runtime_object_arguments':f['args'].count('lean_object*'),
            'calls':dict(collections.Counter(re.findall(r'\b((?:lean_|lp_competition_)\w+)\(',body)))}
    hot=fs[symbol]['body']
    assert hot.count('lean_array_uget_borrowed(')==5
    assert not any(x in hot for x in ('lean_nat_','_advance(','lean_apply_','lean_alloc_closure','lean_box_float32'))
    assert hot.count('lean_float32_mul(')==12 and hot.count('lean_float32_add(')==8
    # Numeric converter contains no add; the eight MAC additions remain exact.
    # Count scalar primitive sites separately from source-level expression mapping.
    (HERE/'indexed8-selected-actual.c').write_text('\n\n'.join(bodies),encoding='utf-8')
    caller=raw(RUN/'build-product-0-R22Indexed8CostMain.c')
    caller_fs=functions(caller.decode())
    for n in ('runControl','runRaw8','runIndexed8'):
        f=caller_fs['lp_competition_'+n]
        assert f['args']=='' and 'lean_alloc_closure' not in f['body']
    rows_by_seed={};drift=[];pairs=[];case_drift=[]
    for seed in (2220001,2220003):
        plan=read(RUN/f'plan-{seed}.json');cases=[c for c in plan['cases'] if c['timed']]
        allrows={}
        order=('control','raw8','raw8','control','control','indexed8','indexed8','control')
        for i,v in enumerate(order):allrows[i]=read(RUN/f'{seed}-{i}-{v}-rows.json')
        first=allrows[0]
        assert len(first)==156 and len(cases)==152
        assert all(set(r)==set(first) and all(r[n]['checksum']==first[n]['checksum'] for n in first) for r in allrows.values())
        for op in ('add','mul','sum','bmm','whole'):
            names=[c['name'] for c in cases if op=='whole' or c['kernel']==op]
            values={i:sum(allrows[i][n]['best_ns'] for n in names) for i in (0,3,4,7)}
            drift.append({'seed':seed,'kernel':op,'control_sums_ns_by_order':values,'max_over_min':max(values.values())/min(values.values())})
        for c in cases:
            if c['kernel']!='bmm':continue
            values={i:allrows[i][c['name']]['best_ns'] for i in (0,3,4,7)}
            case_drift.append({'seed':seed,'name':c['name'],'shape':[c['batch'],c['m'],c['n'],c['p']],
                'eligible':eligible(c),'control_ns_by_order':values,
                'max_over_min':max(values.values())/min(values.values())})
        for variant,cs,vs in (('raw8',0,1),('raw8',3,2),('indexed8',4,5),('indexed8',7,6)):
            cr,vr=allrows[cs],allrows[vs];buckets={}
            for key,pred in [('whole',lambda c:True),('add',lambda c:c['kernel']=='add'),('mul',lambda c:c['kernel']=='mul'),
                ('sum',lambda c:c['kernel']=='sum'),('bmm',lambda c:c['kernel']=='bmm'),
                ('bmm_static_eligible',lambda c:c['kernel']=='bmm' and eligible(c)),
                ('bmm_static_miss',lambda c:c['kernel']=='bmm' and not eligible(c))]:
                cc=[c for c in cases if pred(c)];ct=sum(cr[c['name']]['best_ns'] for c in cc);vt=sum(vr[c['name']]['best_ns'] for c in cc)
                buckets[key]={'cases':len(cc),'control_ns':ct,'variant_ns':vt,'ratio':vt/ct,'delta_ns':vt-ct}
            detail=[]
            for c in cases:
                if c['kernel']!='bmm':continue
                ct,vt=cr[c['name']]['best_ns'],vr[c['name']]['best_ns']
                detail.append({'name':c['name'],'shape':[c['batch'],c['m'],c['n'],c['p']],
                    'eligible':eligible(c),'control_ns':ct,'variant_ns':vt,'ratio':vt/ct,'delta_ns':vt-ct,
                    'tail_rows':c['m']%4,'padded_pair_cols':2*((c['p']+1)//2),'specRate':c['specRate'],'subPct':c['subPct']})
            pairs.append({'seed':seed,'variant':variant,'control_order':cs,'variant_order':vs,'buckets':buckets,
                'cases_by_delta_ns':sorted(detail,key=lambda x:x['delta_ns'])})
    report={'source_sha256':SOURCE,'C_sha256':sha(c_raw),'measured_linked_object_sha256':obj,
        'original_artifact_rehash':{'files':len(originals['files']),'bytes':original_bytes,'all_exact':True,
            'index_sha256':sha((run_folder/'original-artifact-hashes.json').read_bytes())},
        'object_pre_post_unchanged':True,'actual_C':chosen,
        'native_wordLoop':{'symbol':symbol,'file':asm_item['file'],'sha256':sha(asm_raw),
            'instruction_counts':dict(counts),'calls':calls,'frame_bytes':120,
            'normal_loop_no_Nat_helpers':True,'codec_ofBits_sites':4,
            'accumulator_stack_accesses_each_k':q_stack,'accumulator_stack_traffic_bytes_per_k':64,
            'all_accumulators_register_resident':False,'SIMD_MACs_real':True},
        'same_object_raw8':{'symbol':raw_symbol,'file':raw_item['file'],'sha256':sha(raw_asm_bytes),'frame_bytes':280},
        'all156_case_checksums_match_across_all8_processes_each_seed':True,
        'pairs':pairs,'all_controls':drift,'all_BMM_control_case_ranges':sorted(case_drift,key=lambda x:x['max_over_min'],reverse=True),
        'input_bindings':bindings,
        'scope':'Exact existing discovery receipt only. New index/control instructions removed, q-spills remain. No seed rerun/adoption/public proof claim.'}
    (HERE/'indexed8-actual-review.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'C':sha(c_raw),'object':obj,'q_stack_remains':q_stack,
        'pairs':[{'seed':p['seed'],'variant':p['variant'],'buckets':p['buckets']} for p in pairs],
        'controls':[{'seed':r['seed'],'op':r['kernel'],'max_over_min':r['max_over_min']} for r in drift]}))


if __name__=='__main__':main()
