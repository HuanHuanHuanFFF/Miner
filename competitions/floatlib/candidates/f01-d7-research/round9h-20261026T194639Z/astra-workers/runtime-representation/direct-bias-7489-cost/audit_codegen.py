"""Rehash original diagnostic evidence; no compilation or performance inference."""
from pathlib import Path
from collections import Counter
import datetime, hashlib, importlib.util, json, re

HERE=Path(__file__).resolve().parent
WORKER=HERE.parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=WORKER.parent.parent
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40420540388/download-dc507616807e4785a2f3fef3abb4fb38/diagnostics/f01-d7-public-suite/public-suite'
DIAG=RUN/'diagnostics/f01-r19-dev-direct-bias-runtime1'
EXPECTED='74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc'
SHA=lambda x:hashlib.sha256(x).hexdigest()
spec=importlib.util.spec_from_file_location('selected_c',WORKER/'compare_classifier_codegen.py')
cc=importlib.util.module_from_spec(spec);spec.loader.exec_module(cc)

def bind(path,expected=None):
    b=path.read_bytes();h=SHA(b)
    if expected:assert h==expected,(str(path),h,expected)
    return {'path':str(path.relative_to(ROOT)).replace('\\','/'),'bytes':len(b),'sha256':h}

def asm_body(path,symbol):
    text=path.read_text();m=re.search(r'^0+ <'+re.escape(symbol)+r'>:\n',text,re.M)
    assert m,symbol
    end=text.find('\nDisassembly of section ',m.end())
    return text[m.start():end if end>=0 else len(text)].rstrip()+'\n'

def instructions(body):
    out=[]
    for line in body.splitlines():
        m=re.match(r'\s*([0-9a-f]+):\s+(\w+)\s*(.*)',line)
        if m:out.append({'address':int(m[1],16),'hex':m[1],'op':m[2],'operands':m[3],'line':line})
    assert out
    return out

def path_rows(rows,ranges):
    found=[]
    for lo,hi in ranges:
        sub=[r for r in rows if lo<=r['address']<=hi]
        assert sub and sub[0]['address']==lo and sub[-1]['address']==hi,(lo,hi)
        found.extend(sub)
    return found

def shape(rows):
    return {'instruction_count_not_cycles':len(rows),'opcodes':dict(Counter(r['op'] for r in rows)),
      'calls':[r for r in rows if r['op']=='call'],
      'branches':[r for r in rows if r['op'].startswith('j')],
      'variable_shifts':[r for r in rows if r['op'] in ('shr','shl','sar') and r['operands'].endswith(',cl')],
      'data_memory':[r for r in rows if '[' in r['operands'] and r['op']!='lea'],
      'stack_data':[r for r in rows if '[rsp' in r['operands']],
      'pushes':[r['operands'] for r in rows if r['op']=='push'],
      'pops':[r['operands'] for r in rows if r['op']=='pop'],
      'floating_point':[r for r in rows if 'xmm' in r['operands'] or r['op'].startswith('cvt')]}

def write_excerpt(name,text):
    p=HERE/name;p.write_text(text,encoding='utf-8',newline='\n');return bind(p)

def main():
    kernel=bind(RUN/'inputs/f01-r19-dev-direct-bias-runtime1/Kernel.lean',EXPECTED)
    bindings=[kernel]
    baseline_input=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
    bindings.append(bind(baseline_input,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'))
    basebytes=baseline_input.read_bytes()
    assert (RUN/'inputs/f01-r19-dev-direct-bias-runtime1/Kernel.lean').read_bytes().startswith(basebytes)
    provenance=json.loads((RUN/'provenance.json').read_text())
    bindings.append(bind(RUN/'provenance.json'))
    bindings.append(bind(RUN/'requested-plan.json',provenance['requested_plan_sha256']))
    assert provenance['official_commit']=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
    assert provenance['source_commit']=='ce3e26f9c6efaf3a7435570d46a13db93cf8c463'
    for filename in ('candidate-c-index.json','native-assembly-index.json'):
        bindings.append(bind(DIAG/filename))
        for r in json.loads((DIAG/filename).read_text()):
            if 'kernel_sha256' in r:assert r['kernel_sha256']==EXPECTED
            bindings.append(bind(DIAG/r['file'],r['sha256']))
    for filename in ('diagnostic-only-verdict.json','helper-audit.json','helper-axioms.raw','helper-audit-source.lean','replay.log','index.json'):
        bindings.append(bind(DIAG/filename))
    verdict=json.loads((DIAG/'diagnostic-only-verdict.json').read_text())
    assert verdict['passed'] and verdict['diagnostic_only'] and verdict['ratio'] is None
    replay=(DIAG/'replay.log').read_text()
    assert 'Submission replays cleanly' in replay and 'VerifyFull replays cleanly' in replay
    roots=re.findall(r"^'([^']+)' depends on axioms: \[([^]]+)\]",(DIAG/'helper-axioms.raw').read_text(),re.M)
    assert len(roots)==7
    assert all(set(a.split(', '))<=set(['propext','Classical.choice','Quot.sound']) for _,a in roots)
    sources,crecords=cc.load(DIAG,EXPECTED)
    old,oldrecords=cc.load(cc.BASE,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58')
    selected,oldselected=cc.select(sources),cc.select(old)
    sel={}
    for op,row in selected.items():
        sel[op]={k:v for k,v in row.items() if k!='body'}
        sel[op]['normalized_body_equal_B2']=cc.normalize(row['body'])==cc.normalize(oldselected[op]['body'])
        sel[op]['body_sha256']=SHA(row['body'].encode())
        assert sel[op]['normalized_body_equal_B2']
    artifacts=[]
    for label in ('diagnosticEntry','normalCore'):
        sym='lp_competition_Submission_R19DirectBias_'+label
        artifacts.append(write_excerpt(label+'.c',cc.extract(sources['Submission'],sym)+'\n'))
        file='native-loop-6.asm.txt' if label=='diagnosticEntry' else 'native-loop-7.asm.txt'
        body=asm_body(DIAG/file,sym)
        artifacts.append(write_excerpt(label+'.asm.txt',body))
        if label=='diagnosticEntry':entryrows=instructions(body)
        else:corerows=instructions(body)
    ranges=[(0,0x2d),(0x74,0x86),(0x266,0x272),(0x45b,0x4bd),(0xb47,0xb53)]
    accepted=path_rows(entryrows,ranges)
    fast=path_rows(entryrows,[(0x45b,0x4bd)])
    artifacts.append(write_excerpt('accepted-diagnostic-path.asm.txt','\n'.join(r['line'] for r in accepted)+'\n'))
    success=shape(accepted);core=shape(corerows);full=shape(entryrows)
    assert success['opcodes']['imul']==1 and not success['calls'] and not success['floating_point']
    assert not success['data_memory'] and not success['stack_data']
    assert success['pushes']==['rbp','r15','r14','r12','rbx']
    assert len(success['variable_shifts'])==1
    assert core['opcodes']['imul']==1 and not core['pushes'] and not core['branches']
    jamframe=json.loads((WORKER/'jam-frame-frontier/frame-evidence.json').read_text())
    jamp=ROOT/jamframe['ASM_binding']['path'];bindings.append(bind(jamp,jamframe['ASM_binding']['sha256']))
    jamrows=instructions(asm_body(jamp,'lp_competition_main___lam__3'))
    jamranges=[(0,0x2d),(0x74,0x86),(0x266,0x272),(0x45b,0x4cf),(0xb59,0xb65)]
    jamaccepted=path_rows(jamrows,jamranges)
    guard=lambda rs:[(r['op'],r['operands'].split(' <')[0]) for r in rs if r['address']<=0x272]
    assert guard(accepted)==guard(jamaccepted)
    artifacts.append(write_excerpt('b271-accepted-MainFull-path.asm.txt','\n'.join(r['line'] for r in jamaccepted)+'\n'))
    history=json.loads((ROUND/'astra-workers/exact-arithmetic/bias-frontier/history-and-manifest.json').read_text())
    hist={}
    for key in ('f529_source','f529_full_input','f529_verdict','f529_result','f529_selected_C'):
        row=history['historical_bindings'][key];hist[key]=bind(ROOT/row['path'],row['sha256'])
    oldv=json.loads((ROOT/history['historical_bindings']['f529_verdict']['path']).read_text());assert oldv['passed'] and oldv['stage']=='score'
    oldcost=json.loads((ROOT/history['historical_bindings']['f529_result']['path']).read_text())
    result={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'DIAGNOSTIC_COST_MECHANISM_VERIFIED_PUBLIC_PROOF_AND_PERFORMANCE_NOT_RUN',
      'run':40420540388,'source_commit':'ce3e26f9c6efaf3a7435570d46a13db93cf8c463','kernel':kernel,
      'official_commit':provenance['official_commit'],'B2_prefix_byte_identical':True,
      'toolchain':'Lean 4.34.0 / 293d5d0c0c3f3dded4688b3ccd6a33939ac5102b; fixed clang -c -O3; no LTO flag',
      'verdict_scope':'Runtime definitions typecheck, old public specs replay. Seven roots contain no theorem equating diagnosticEntry to multiplication.',
      'roots':dict(roots),'selected_public_MainFull':sel,'B2_C_bindings':oldrecords,
      'accepted_ranges_inclusive':[[hex(a),hex(b)] for a,b in ranges],'accepted':success,'normalCore':core,
      'entire_entry_shape_static_not_dynamic':full,'b271_actual_selected_MainFull':shape(jamaccepted),
      'b271_and_7489_accepted_guard_prologue_identical':True,
      'cold_fallback':'Inlined B2; not external tail fallback. r14 unused on success, rbp only prepares early exponent; shared frame and all five callee saves remain. All explicit [rsp] data stores/loads and calls are outside success.',
      'binary_object_hashes_from_index_only':{'Submission':'0000a5aa27fb6babc8e0503d9e3fe12cbf4d7c7e9828f2e0647d38399fa7d36c','MainFull':'7ab237954778ea0dd4a154d31cd17923a098fd84ccc853c9c4e8caeafa3bd24a'},
      'raw_binary_rehashed':False,'evidence_bindings':bindings,'f529_bindings':hist,
      'f529_historical_boundary':{'whole_vs_df5c':oldcost['relative_normalized_ratio'],'mul_vs_df5c':oldcost['per_operation_normalized']['mul'],'optimized_scalar_ASM':'NOT_CAPTURED; cannot establish machine-work equality or claim old two products execute'},
      'artifacts':artifacts,'decision':'Continue the already selected public proof, not an extra runtime variant; require actual selected MainFull code and original full D before any speed claim.',
      'performance':'NOT_MEASURED; diagnostic object not timed ELF; no public diagnostic dispatch in this source'}
    (HERE/'audit.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'accepted':{k:success[k] for k in ('instruction_count_not_cycles','opcodes','pushes')},'normalCore':core['opcodes'],'public_MainFull_equals_B2':True,'bindings':len(bindings),'audit_sha256':SHA((HERE/'audit.json').read_bytes())}))

if __name__=='__main__':main()
