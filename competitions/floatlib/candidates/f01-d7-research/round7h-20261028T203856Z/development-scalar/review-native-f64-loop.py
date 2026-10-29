"""Selected-call-path C/ASM audit for the first native pilot. Read-only inputs."""
from pathlib import Path
import hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
ROUND=HERE.parent
BASE=ROUND/'ci-runs/40801622733/download-97d8744240234398acfcef2a61f34e19/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r24-dev-dot-cost1/runtime-cost'
sha=lambda b:hashlib.sha256(b).hexdigest()
def main():
    c=(BASE/'Submission.c').read_bytes();a=(BASE/'Submission-asm.txt').read_bytes()
    assert sha(c)=='be640672b6f6ed893610f3cf6a2c8517bf23a00b3572e7c68ffcf56e7d46dab9'
    assert sha(a)=='22a13b08a34367b4c25fac6e8aeb373b71474ceb3e0ce22d8ab5c944038458db'
    path=ROUND/'development-dot-cost/audit-callers.py';s=importlib.util.spec_from_file_location('fixed_native_functions',path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m)
    ct=c.decode();at=a.decode();functions=m.functions(c);asm=m.asm_functions(at)
    find=lambda suffix:next(n for n in functions if n.endswith(suffix))
    eager=find('Submission_R24DotProbe_eagerPrepared');lazy=find('Submission_R24DotProbe_lazyPrepared')
    attempt=find('Submission_R24PortableF64_attemptPrepared')
    loop=next(n for n in functions if n.endswith('repeatM_erased___at___00Submission_R24PortableF64_attemptPrepared_spec__0___redArg'))
    assert attempt in functions[eager]['body'] and attempt in functions[lazy]['body']
    assert loop in functions[attempt]['body'] and loop in asm
    body=functions[loop]['body'];machine=asm[loop]
    assert 'lean_unbox_float' in body and 'lean_box_float' in body
    box_pos=body.index('lean_box_float')
    assert box_pos<body.index('if (v_isShared_8081_ == 0)',box_pos)
    assert 'lean_ctor_set(v___x_8080_' in body and 'v_a_8076_ = v___x_8097_' in body and 'goto _start' in body
    assert 'mov    edi,0x10' in machine and 'mi_malloc_small' in machine and 'mulsd' in machine and 'addsd' in machine
    assert re.search(r'188:\s+je\s+30\b',machine) and re.search(r'1bb:\s+jmp\s+3b\b',machine)
    def line(needle):
        pos=ct.index(needle);return ct.count('\n',0,pos)+1
    def node(n):
        v=functions[n];return {'symbol':n,'header':v['header'],'definition_line':line(v['header']),
            'definition_sha256':v['body_sha256']}
    out=HERE/'native-f64-loop-review';out.mkdir(exist_ok=True)
    (out/'selected-mac.c.txt').write_bytes((functions[loop]['header']+'{'+body+'}\n').encode())
    (out/'selected-mac.asm.txt').write_bytes((loop+'\n'+machine).encode())
    callers='\n'.join(functions[n]['header']+'{'+functions[n]['body']+'}\n' for n in (eager,lazy))
    callers+='\n/* Actual outer FP call into this loop, not an unused export. */\n'
    rows=ct.splitlines();call_line=next(i for i,x in enumerate(rows,1) if loop+'(' in x and '=' in x and 'v_n_8474_' in x)
    callers+='\n'.join(f'{i}: {rows[i-1]}' for i in range(call_line-2,call_line+8))+'\n'
    (out/'selected-callers.c.txt').write_bytes(callers.encode())
    report={'status':'ACTUAL_SELECTED_FP_MAC_FLOAT_BOXING_CONFIRMED_TAIL_CONDITION_MET','run':40801622733,
        'input_C':{'path':str(BASE/'Submission.c'),'sha256':sha(c),'bytes':len(c)},
        'input_ASM':{'path':str(BASE/'Submission-asm.txt'),'sha256':sha(a),'bytes':len(a)},
        'selected_path':[node(n) for n in (eager,lazy,attempt,loop)],'actual_loop_call_line':call_line,
        'C_evidence':{'unbox_old_acc_line':line('v___x_8091_ = lean_unbox_float(v_fst_8077_)'),
            'box_new_acc_line':line('v___x_8095_ = lean_box_float(v___x_8092_)'),
            'tuple_state':'Exclusive-state path reuses constructor; shared-state path conditionally allocates. Do not claim a fresh tuple per MAC.'},
        'ASM_evidence':{'function_header_line':at.count('\n',0,at.index('<'+loop+'>:'))+1,
            'normal_MAC_float_box_allocation':'0x144 mov edi,0x10; 0x149 call mi_malloc_small (reloc0x14a)',
            'floating_ops':['0x160 mulsd','0x16c addsd','0x17e store double into new Float box'],
            'backedges':['0x188→0x30→0x3b exclusive-state loop','0x1bb→0x3b shared-state loop'],
            'state_tuple_allocation':'0x198 call mi_malloc_small with edi0x18 is conditional shared continuation;0x28e exit allocation also conditional.',
            'frame':'6 callee-save pushes and0x28-byte stack frame; accumulator and both loaded input doubles are spilled around allocator/free work.',
            'input_loads':'FloatArray getters lower to native double loads, not boxed Float elements.'},
        'interpretation':'On each continued MAC, the accumulator is unboxed, previous box reference released, next accumulator boxed via a surviving16-byte allocation. State constructor bookkeeping is also present but tuple allocation is conditional.',
        'activation':'Evidence supports testing the single already-frozen Tail5bd alternative, subject to root decision. It does not establish Tail unboxing or speed.',
        'performance':'NO_NEW_COST_CLAIM; pilot timings partial after outer120s timeout; full32 rerun required.',
        'Tail_native':'NOT_RUN','Tail_cost':'NOT_RUN','fixed_parser_sha256':sha(path.read_bytes()),
        'snippets':[{'path':p.name,'bytes':p.stat().st_size,'sha256':sha(p.read_bytes())}for p in out.iterdir() if p.suffix=='.txt']}
    (out/'review.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    print(json.dumps({k:report[k] for k in ('status','actual_loop_call_line','C_evidence','ASM_evidence','activation')} ,indent=2))
if __name__=='__main__':main()
