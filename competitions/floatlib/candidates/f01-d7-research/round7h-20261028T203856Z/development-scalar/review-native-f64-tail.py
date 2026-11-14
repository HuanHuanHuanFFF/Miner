"""Actual selected Tail ABI/hot-loop audit, not a speed or admission claim."""
from pathlib import Path
import hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent;ROUND=HERE.parent
BASE=ROUND/'ci-runs/40804860824/download-a29c9d41975b4c67b67aefb0158b1440/diagnostics/f01-d7-public-suite/public-suite/diagnostics'
TAIL=BASE/'f01-r24-dev-dot-tail-cost1/runtime-cost';OLD=BASE/'f01-r24-dev-dot-cost1/runtime-cost'
sha=lambda b:hashlib.sha256(b).hexdigest()
def main():
    c=(TAIL/'Submission.c').read_bytes();a=(TAIL/'Submission-asm.txt').read_bytes();ct=c.decode();at=a.decode()
    assert sha(c)=='763d12a687ac23ee252b4413b9ea33de7ea1afdabcdf39849834404c4b5636fe'
    assert sha(a)=='ad7e12dd84a961a6d74485fa272cb374cb29335691627e5d27393fdfb03e70bb'
    path=ROUND/'development-dot-cost/audit-callers.py';spec=importlib.util.spec_from_file_location('fixed_calls_tail',path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    funcs=m.functions(c);asm=m.asm_functions(at);find=lambda suffix:next(n for n in funcs if n.endswith(suffix))
    eager=find('Submission_R24DotProbe_eagerPrepared');lazy=find('Submission_R24DotProbe_lazyPrepared');attempt=find('Submission_R24PortableF64_attemptPrepared');worker=find('Submission_R24PortableF64_sumRemaining');boxed=find('Submission_R24PortableF64_sumRemaining___boxed')
    assert attempt in funcs[eager]['body'] and attempt in funcs[lazy]['body']
    assert worker+'(' in funcs[attempt]['body'] and boxed+'(' not in funcs[attempt]['body']
    header=funcs[worker]['header'];body=funcs[worker]['body'];machine=asm[worker]
    assert header.startswith('LEAN_EXPORT double ') and header.count('double')==2
    args=header[header.index('(')+1:header.rindex(')')].split(',');assert len(args)==5 and sum('double' in x for x in args)==1
    assert all(x not in body for x in ('lean_box_float','lean_unbox_float','lean_alloc_ctor','lean_alloc_closure','lean_apply'))
    assert 'v_acc_8076_ = v___x_8086_' in body and 'goto _start' in body
    assert worker in asm[attempt] and boxed not in asm[attempt]
    assert 'mulsd' in machine and 'addsd  xmm0' in machine
    assert not any(x in machine for x in ('mi_malloc','lean_inc_heartbeat','lean_box_float','lean_unbox_float'))
    assert re.search(r'c8:\s+jmp\s+60\b',machine)
    def line(needle):return ct.count('\n',0,ct.index(needle))+1
    def node(n):return {'symbol':n,'header':funcs[n]['header'],'C_definition_line':line(funcs[n]['header']),'definition_sha256':funcs[n]['body_sha256']}
    out=HERE/'native-f64-tail-review';out.mkdir(exist_ok=True)
    (out/'selected-worker.c.txt').write_bytes((header+'{'+body+'}\n').encode())
    (out/'selected-worker.asm.txt').write_bytes((worker+'\n'+machine).encode())
    (out/'selected-callers.c.txt').write_bytes(('\n'.join(funcs[n]['header']+'{'+funcs[n]['body']+'}\n' for n in (eager,lazy))+ '\nActual unboxed call:\n'+ '\n'.join(x for x in ct.splitlines() if worker+'(' in x and '=' in x)+'\n').encode())
    metadata={}
    for label,p in [('original',OLD),('tail',TAIL)]:
        r=json.loads((p/'result.json').read_bytes());assert r['complete'] and len(r['runs'])==32 and r['originals_unchanged']
        oracle=r['native_oracle'];assert oracle['dots']==148 and oracle['word_rounds']==1049 and oracle['known_actual_accept']==51
        metadata[label]={'source_sha256':r['source_sha256'],'complete':True,'processes':len(r['runs']),'originals_unchanged':r['originals_unchanged'],'native_oracle':oracle,'result_json_sha256':sha((p/'result.json').read_bytes())}
    assert metadata['original']['source_sha256']=='5bf2a8893b01a5ed44393e80065fbd91e9b3686133e9ddd5d4dfb633379d4d2a'
    assert metadata['tail']['source_sha256'].startswith('e50bf876')
    report={'status':'ACTUAL_SELECTED_TAIL_UNBOXED_ACC_CONFIRMED_PER_MAC_FLOAT_BOX_REMOVED','run':40804860824,
        'input_C':{'path':str(TAIL/'Submission.c'),'sha256':sha(c),'bytes':len(c)},'input_ASM':{'path':str(TAIL/'Submission-asm.txt'),'sha256':sha(a),'bytes':len(a)},
        'selected_path':[node(n) for n in (eager,lazy,attempt,worker)],'unboxed_call_line':line('v_sum_8471_ = '+worker),
        'C_evidence':'Worker returns double, accepts one double accumulator plus four object arguments; direct native FloatArray loads/mul/add and scalar backedge update. No Float box/unbox, tuple construction or dynamic apply in selected worker.',
        'ASM_evidence':{'header_line':at.count('\n',0,at.index('<'+worker+'>:'))+1,'actual_caller':'attemptPrepared ASM relocation0x99 directly targets sumRemaining, not ___boxed',
            'normal_small_Nat_path':'0x6b remaining tag/zero check;0x85 subtracttag2;0x91 index untag/inc/retag;0xb6/0xc2 direct double loads;0xc8→0x60 mulsd→0x64 addsd xmm0→0x6b',
            'allocation':'No mi_malloc/heartbeat/Float RC calls anywhere in this worker ASM. Big-Nat slow paths still call nat_big_add/sub and can allocate internally; FP caller index0,n≤2^30 keeps counters on small-Nat path.',
            'frame':'6 callee-save pushes plus one8-byte stack slot; accumulator remains xmm0 on normal MAC backedge, spills only around big-Nat cold calls.'},
        'unused_wrapper':'sumRemaining___boxed still has one box/unbox interface, but neither actual FP C caller nor ASM calls it. Do not diagnose selected path from a whole-file grep.',
        'mechanism_delta':'Old selected while reboxed the accumulator via surviving16B allocation per continued MAC and maintained a generic tuple state. New selected structural worker removes those Float boxes and tuple state; counters remain.',
        'runtime_integrity':metadata,'scope':'Causal implementation-work deletion verified. This report deliberately does not calculate speed, all-input correctness, competition score or adoption; root analyzes complete paired costs separately.',
        'snippets':[{'path':p.name,'sha256':sha(p.read_bytes()),'bytes':p.stat().st_size}for p in out.iterdir()if p.suffix=='.txt']}
    (out/'review.json').write_bytes((json.dumps(report,indent=2)+'\n').encode());print(json.dumps({k:report[k]for k in ('status','unboxed_call_line','ASM_evidence','mechanism_delta')},indent=2))
if __name__=='__main__':main()
