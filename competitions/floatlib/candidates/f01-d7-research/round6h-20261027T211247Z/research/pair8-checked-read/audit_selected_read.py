from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,collections

HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
D=ROUND/'ci-runs/40596173085/download-9fa63d247cdc40339053b06f8b6eb6c8/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-pair8-cost1'
R=D/'runtime-cost'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
result=json.loads((R/'result.json').read_text())
assert result['source_sha256']=='0ec168de06c5e2da6098ff362b4adc07946bb5f42d81fd06309bd8d246706fd8'
C=D/'candidate-generated-0.c';M=R/'build-product-0-R22Pair8CostMain.c'
assert C.read_bytes()==(R/'original-statement-Submission.c').read_bytes()
key=next(k for k in result['build_identities'] if k.endswith('/R22Pair8CostMain.c'))
assert sha(M)==result['build_identities'][key]
main=M.read_text();start='lp_competition_Submission_R22Pair8_guarded'
assert re.search(r'\.m_fun = \(void\*\)'+start+r',',main)
assert not re.search(r'^LEAN_EXPORT [^;\n]*\b'+start+r'\([^;\n]*\)\{',main,re.M)
text=C.read_text();funcs={}
for m in re.finditer(r'(?m)^(?:LEAN_EXPORT |static )?[^;\n]*\b(lp_competition_[A-Za-z0-9_]+)\([^;\n]*\)\{',text):
    depth=0;end=None
    for i in range(m.end()-1,len(text)):
        if text[i]=='{':depth+=1
        elif text[i]=='}':
            depth-=1
            if depth==0:end=i+1;break
    if end:funcs[m[1]]=text[m.start():end]
target='lp_competition___private_Init_Data_Array_Basic_0__Array_mapFinIdxMUnsafe_map___at___00Submission_R22Pair8_loop_spec__0___redArg'
queue=collections.deque([[start]]);seen={start};path=None
while queue:
    current=queue.popleft()
    if current[-1]==target:path=current;break
    calls=set(re.findall(r'\b(lp_competition_[A-Za-z0-9_]+)\(',funcs.get(current[-1],'')))
    for nxt in calls:
        if nxt in funcs and nxt not in seen:seen.add(nxt);queue.append(current+[nxt])
assert path
body=funcs[target]
assert 'lean_array_get_size(v_cache_' in body and 'lean_nat_dec_lt(' in body and 'R22Pair8_zeroPair' in body
(HERE/'selected-map.c.txt').write_text(body+'\n',encoding='utf-8')
ai=json.loads((D/'native-assembly-index.json').read_text())
entry=next(x for x in ai if x.get('symbol')==target)
ap=D/entry['file'];assert sha(ap)==entry['sha256']
asm=ap.read_text();head=re.search(r'(?m)^0+ <'+re.escape(target)+r'>:\s*$',asm);assert head
body_start=asm.index('\n',head.start())+1
end=re.search(r'(?m)^(Disassembly of section|0[0-9a-f]+ <)',asm[body_start:])
asm_body=asm[body_start:body_start+end.start()] if end else asm[body_start:]
assert re.search(r'(?m)^\s*110:\s+cmp\s+rax,rsi',asm_body)
assert re.search(r'(?m)^\s*113:\s+jae\s+200\b',asm_body)
assert 'R22Pair8_zeroPair' in asm_body
(HERE/'selected-map.asm.txt').write_text(asm_body,encoding='utf-8')
out={
 'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'ACTUAL_SELECTED_PAIR8_CACHE_BOUND_CHECK_REMAINS',
 'run_id':40596173085,'kernel_sha256':result['source_sha256'],
 'main_C_sha256':sha(M),'Submission_C_sha256':sha(C),
 'actual_BMM_callback':start,'selected_call_path':path,
 'selected_path_C_hashes':{name:hashlib.sha256(funcs[name].encode()).hexdigest() for name in path},
 'ASM':{'path':str(ap.relative_to(ROOT)).replace('\\','/'),'sha256':sha(ap),'object_sha256_from_original_index':entry['object_sha256'],
        'small_Nat_compare':'0x110 cmp rax,rsi','default_branch':'0x113 jae0x200','default_value':'zeroPair global at0x203 relocation'},
 'scope':'OriginalSubmission source is byteidentical around the ownedtimedMain; Main selects this externalguarded path. ASM is the source-bound statementdiagnostic object, not a newchecked-read/finalgateELF.',
 'new_read_variant':'NOT_RUN_NOT_ASSEMBLED',
 'performance_causality':'The oldcheck remains; no measured cycle share, branch prediction effect or newvariant gain. No repeatedseed experiment requested.',
}
(HERE/'selected-read-receipt.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='selected_path_C_hashes'},indent=2))
