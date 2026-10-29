"""Require typed fixed array-return banks and an external input barrier inside native loops."""
from pathlib import Path
import hashlib, re

SUFFIXES={'Exact':'exactBank','Eager':'eagerBank','Lazy':'lazyBank'}

def functions(raw):
    text=raw.decode(errors='replace')
    masked=re.sub(r'/\*[\s\S]*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',lambda m:' '*len(m[0]),text)
    pat=re.compile(r'(?m)^(?:LEAN_EXPORT\s+)?(?:LEAN_NOINLINE\s+)?(?:static\s+)?[A-Za-z_][A-Za-z0-9_ \t*]*\b([A-Za-z0-9_]+)\s*\([^;\n]*\)\s*\{')
    result={}
    for m in pat.finditer(masked):
        end=m.end();depth=1
        while depth and end<len(masked):depth+=(masked[end]=='{')-(masked[end]=='}');end+=1
        result[m[1]]={'header':text[m.start():m.end()-1].strip(),'body':text[m.end():end-1],
            'body_sha256':hashlib.sha256(text[m.start():end].encode()).hexdigest()}
    return result

def asm_functions(text):
    matches=list(re.finditer(r'(?m)^\s*[0-9a-f]+ <([^>]+)>:\s*$',text));result={}
    for i,m in enumerate(matches):result[m[1]]=text[m.end():matches[i+1].start() if i+1<len(matches) else len(text)]
    return result

def loop_witness(text,adapter):
    barriers=[];targets=[];observers=[];back=[]
    for line in text.splitlines():
        pc=re.match(r'\s*([0-9a-f]+):',line)
        if not pc:continue
        address=int(pc[1],16)
        if 'R24DotBarrier_touch' in line:barriers.append(max(0,address-1))
        if 'Submission_R24GenericDotBank_'+adapter in line:targets.append(max(0,address-1))
        if re.search(r'R24DotBankHarness_(?:hashAll|sumRemaining)',line):observers.append(max(0,address-1))
        jump=re.match(r'\s*[0-9a-f]+:\s+j[a-z]+\s+(?:0x)?([0-9a-f]+)(?:\s|$)',line)
        if jump:
            dest=int(jump[1],16)
            if dest<address:back.append((dest,address))
    for low,high in back:
        bs=[x for x in barriers if low<=x<=high];ts=[x for x in targets if low<=x<=high]
        hs=[x for x in observers if low<=x<=high]
        if bs and ts and hs:return {'backedge':[low,high],'barrier_call_offsets':bs,'adapter_call_offsets':ts,'all_output_observer_call_offsets':hs}
    return None

def review(out):
    out=Path(out);main=functions((out/'R24DotCostMain.c').read_bytes());barrier=functions((out/'R24DotBarrier.c').read_bytes())
    submission=functions((out/'Submission.c').read_bytes());owned={**main,**barrier}
    asm=asm_functions((out/'R24DotCostMain-asm.txt').read_text(errors='replace'))
    allnames=set(owned);records=[]
    for suffix,adapter in SUFFIXES.items():
        needle='R24DotBankHarness_pass'+suffix
        roots=[n for n in main if (n.endswith(needle) or n.endswith(needle+'___redArg')) and '___boxed' not in n]
        reachable=set();pending=list(roots)
        while pending:
            name=pending.pop()
            if name in reachable:continue
            reachable.add(name)
            pending += list((set(re.findall(r'\b[A-Za-z_]\w*\b',owned[name]['body']))&allnames)-reachable)
        dynamic=[n for n in reachable if re.search(r'\blean_apply(?:_\d+|_m|_n)?\s*\(',owned[n]['body'])]
        cbar=[n for n in reachable if 'R24DotBarrier_touch' in n]
        adapter_defs=[(n,v) for n,v in submission.items() if n.endswith('Submission_R24GenericDotBank_'+adapter)]
        typed=[]
        for n,v in adapter_defs:
            h=v['header'];ret=h[:h.index(n)];args=h[h.index('(')+1:h.rindex(')')].split(',')
            typed.append({'symbol':n,'header':h,'body_sha256':v['body_sha256'],
                'array_return_two_args':'lean_object*' in ret.replace(' ','') and len(args)==2 and all('lean_object*' in a.replace(' ','') for a in args)})
        witnesses=[]
        for n in reachable:
            if n in asm:
                witness=loop_witness(asm[n],adapter)
                if witness:witnesses.append({'symbol':n,**witness})
        observer=[n for n in reachable if 'R24DotBankHarness_hashAll' in n or 'R24DotBankHarness_sumRemaining' in n]
        observer_elements=[n for n in observer if re.search(r'lean_array_(?:uget|fget|get)(?:\s*\(|_)|l_Array_get',owned[n]['body'])]
        observer_loops=[n for n in observer if 'goto ' in owned[n]['body'] or n+'(' in owned[n]['body'].replace(' ','')]
        releases=[]
        for n in observer:
            h=owned[n]['header'];first=h[h.index('(')+1:h.rindex(')')].split(',')[0]
            arg=re.findall(r'[A-Za-z_]\w*',first)[-1]
            if re.search(r'\blean_dec(?:_ref)?\s*\(\s*'+re.escape(arg)+r'\s*\)',owned[n]['body']):releases.append({'symbol':n,'array_parameter':arg})
        dataflow=[]
        for n in reachable:
            body=owned[n]['body']
            for call in re.finditer(r'(\w+)\s*=\s*(\w*Submission_R24GenericDotBank_'+re.escape(adapter)+r')\s*\([^;]*\)\s*;',body):
                var=call[1]
                if re.search(r'\b\w*R24DotBankHarness_hashAll\s*\(\s*'+re.escape(var)+r'\s*\)',body[call.end():]):
                    released_here=bool(re.search(r'\blean_dec(?:_ref)?\s*\(\s*'+re.escape(var)+r'\s*\)',body[call.end():]))
                    dataflow.append({'symbol':n,'bank_result_variable':var,'bank_callee':call[2],'consumer':'hashAll(same_variable)','same_result_released_in_pass':released_here,'consumed_in_observer':bool(releases)})
        ok=bool(observer and observer_elements and observer_loops and dataflow and all(x['same_result_released_in_pass'] or x['consumed_in_observer'] for x in dataflow) and roots and cbar and typed and all(x['array_return_two_args'] for x in typed) and not dynamic and witnesses)
        records.append({'pass_suffix':suffix,'roots':roots,'reachable_harness_functions':sorted(reachable),
            'dynamic_apply_in_pass_graph':dynamic,'all_word_observer_graph':observer,'observer_element_access':observer_elements,'observer_loop_functions':observer_loops,'array_release_sites':releases,'bank_result_consumer_dataflow':dataflow,'external_barriers':cbar,'typed_adapter':typed,
            'native_loop_witnesses':witnesses,'pass':ok})
    return {'pass':len(records)==3 and all(x['pass'] for x in records),'records':records,
        'scope':'Actual selected C/static closure and ASM backedge proof of repeated external barrier+fixed array-return bank. Selected fixed-source bank-result def-use, element-loop/array-release and in-backedge observer witnesses recorded; independent raw-C review still required. Not a general C proof, kernel score or all-input correctness claim.'}
