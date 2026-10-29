"""Require typed fixed adapters and an external input barrier inside native loops."""
from pathlib import Path
import hashlib, re

SUFFIXES={'ExactFull':'exactFull','EagerFull':'eagerFull','LazyFull':'lazyFull',
          'ExactPrepared':'exactPrepared','EagerPrepared':'eagerPrepared','LazyPrepared':'lazyPrepared'}

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
    barriers=[];targets=[];back=[]
    for line in text.splitlines():
        pc=re.match(r'\s*([0-9a-f]+):',line)
        if not pc:continue
        address=int(pc[1],16)
        if 'R24DotBarrier_touch' in line:barriers.append(max(0,address-1))
        if 'Submission_R24DotProbe_'+adapter in line:targets.append(max(0,address-1))
        jump=re.match(r'\s*[0-9a-f]+:\s+j[a-z]+\s+(?:0x)?([0-9a-f]+)(?:\s|$)',line)
        if jump:
            dest=int(jump[1],16)
            if dest<address:back.append((dest,address))
    for low,high in back:
        bs=[x for x in barriers if low<=x<=high];ts=[x for x in targets if low<=x<=high]
        if bs and ts:return {'backedge':[low,high],'barrier_call_offsets':bs,'adapter_call_offsets':ts}
    return None

def review(out):
    out=Path(out);main=functions((out/'R24DotCostMain.c').read_bytes());barrier=functions((out/'R24DotBarrier.c').read_bytes())
    submission=functions((out/'Submission.c').read_bytes());owned={**main,**barrier}
    asm=asm_functions((out/'R24DotCostMain-asm.txt').read_text(errors='replace'))
    allnames=set(owned);records=[]
    for suffix,adapter in SUFFIXES.items():
        needle='R24DotCostHarness_pass'+suffix
        roots=[n for n in main if (n.endswith(needle) or n.endswith(needle+'___redArg')) and '___boxed' not in n]
        reachable=set();pending=list(roots)
        while pending:
            name=pending.pop()
            if name in reachable:continue
            reachable.add(name)
            pending += list((set(re.findall(r'\b[A-Za-z_]\w*\b',owned[name]['body']))&allnames)-reachable)
        dynamic=[n for n in reachable if re.search(r'\blean_apply(?:_\d+|_m|_n)?\s*\(',owned[n]['body'])]
        cbar=[n for n in reachable if 'R24DotBarrier_touch' in n]
        adapter_defs=[(n,v) for n,v in submission.items() if n.endswith('Submission_R24DotProbe_'+adapter)]
        typed=[]
        for n,v in adapter_defs:
            h=v['header'];ret=h[:h.index(n)];args=h[h.index('(')+1:h.rindex(')')].split(',')
            typed.append({'symbol':n,'header':h,'body_sha256':v['body_sha256'],
                'uint32_return_two_args':'uint32_t' in ret and len(args)==2})
        witnesses=[]
        for n in reachable:
            if n in asm:
                witness=loop_witness(asm[n],adapter)
                if witness:witnesses.append({'symbol':n,**witness})
        ok=bool(roots and cbar and typed and all(x['uint32_return_two_args'] for x in typed) and not dynamic and witnesses)
        records.append({'pass_suffix':suffix,'roots':roots,'reachable_harness_functions':sorted(reachable),
            'dynamic_apply_in_pass_graph':dynamic,'external_barriers':cbar,'typed_adapter':typed,
            'native_loop_witnesses':witnesses,'pass':ok})
    return {'pass':len(records)==6 and all(x['pass'] for x in records),'records':records,
        'scope':'Actual selected C/static closure and ASM backedge proof of repeated external barrier+fixed adapter. No assertion of kernel speed, zero allocations, or algorithm correctness.'}
