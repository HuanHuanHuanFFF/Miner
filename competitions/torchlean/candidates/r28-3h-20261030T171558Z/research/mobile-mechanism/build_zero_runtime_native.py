# Self-contained owned proof-pruner for a runtime-identical zero53 cost diagnostic.
"""Original exact source recipe for public #53: arithmetic-zero paired-dot elision.

Full third-party base and generated source remain private. No local Lean/native build.
"""
from pathlib import Path
import argparse,hashlib,json,re,datetime
HERE=Path(__file__).resolve().parent
BASE_SHA='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb'
BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
Z='0x200000000000000'

def compact_proof_names(s):
    names=re.findall(r'(?m)^(?:lemma|theorem)\s+([A-Za-z][A-Za-z0-9_]+)',s)
    names=[n for n in names if len(n)>=12 and n!='correct']
    mapping={n:'rz'+str(i) for i,n in enumerate(names)}
    for old,new in mapping.items():
      assert not re.search(r'\b'+re.escape(new)+r'\b',s)
    for old,new in mapping.items():s=re.sub(r'\b'+re.escape(old)+r'\b',new,s)
    return s,mapping

def section(s,start,end):
    a=s.index(start);b=s.index(end,a);return a,b,s[a:b]

def zero_channel(s):
    a,b,body=section(s,'@[specialize] def qCtx7 ','lemma qCtx8 ')
    p='  let x:=fa k h\n';assert body.count(p)==1
    body=body.replace(p,p+f'  if hz:x={Z} then\n   qCtx7 n fa fb0 fb1 B0 B1 bw0 bw1 cb0 cb1 z0 z1 a0 a1 b0 b1 (k+1)\n  else\n')
    body=body.replace('  let u:=','   let u:=').replace('  let v:=','   let v:=').replace('  qCtx7 n fa fb0 fb1 B0 B1 bw0 bw1 cb0 cb1 z0 z1 (','   qCtx7 n fa fb0 fb1 B0 B1 bw0 bw1 cb0 cb1 z0 z1 (')
    body=body.replace('decreasing_by exact ZI n k h','decreasing_by all_goals exact ZI n k h')
    s=s[:a]+body+s[b:]
    a,b,body=section(s,'lemma qCtx8 ','@[specialize] def qCtx9 ')
    old='   exact qCtx8 n fa fb fc B C bw cw cb0 cb1 hc0 hc1 z0 z1 _ _ _ _ (k+1)'
    assert body.count(old)==1
    body=body.replace(old,f'''   by_cases hz:fa k h={Z}
   · simp only [dif_pos hz]
     simpa [hz,Y9,cq1] using qCtx8 n fa fb fc B C bw cw cb0 cb1 hc0 hc1 z0 z1 a b c d (k+1)
   · simp only [dif_neg hz]
     exact qCtx8 n fa fb fc B C bw cw cb0 cb1 hc0 hc1 z0 z1 _ _ _ _ (k+1)''')
    return s[:a]+body+s[b:]

def zero_spatial(s):
    a,b,body=section(s,'@[specialize] def qCtx13 ','lemma qCtx14 ')
    p='  let y:=fa1 k h\n';assert body.count(p)==1
    body=body.replace(p,p+f'  if hz:x={Z} ∧ y={Z} then\n   qCtx13 n fa0 fa1 fb B0 bw cb finish0 finish1 a0 a1 b0 b1 (k+1)\n  else\n')
    body=body.replace('  let w:=','   let w:=').replace('  qCtx13 n fa0 fa1 fb B0 bw cb finish0 finish1 (','   qCtx13 n fa0 fa1 fb B0 bw cb finish0 finish1 (')
    body=body.replace('decreasing_by exact ZI n k h','decreasing_by all_goals exact ZI n k h')
    s=s[:a]+body+s[b:]
    a,b,body=section(s,'lemma qCtx14 ','@[inline] def qCtx15 ')
    old='   exact qCtx14 n f g w B bw cb hc z0 z1 _ _ _ _ (k+1)';assert body.count(old)==1
    body=body.replace(old,f'''   by_cases hz:f k h={Z} ∧ g k h={Z}
   · simp only [dif_pos hz]
     simpa [hz.1,hz.2,Y9,cq1] using qCtx14 n f g w B bw cb hc z0 z1 a b c d (k+1)
   · simp only [dif_neg hz]
     exact qCtx14 n f g w B bw cb hc z0 z1 _ _ _ _ (k+1)''')
    return s[:a]+body+s[b:]

def make_zero(raw,submission,variant):
    assert submission==53 and hashlib.sha256(raw).hexdigest()==BASE_SHA
    s=raw.decode('utf-8');s,_=compact_proof_names(s)
    if variant in ['zero-channel','zero-both']:s=zero_channel(s)
    if variant in ['zero-spatial','zero-both']:s=zero_spatial(s)
    assert variant in ['compact-control','zero-channel','zero-spatial','zero-both']
    result=s.encode('utf-8');assert len(result)<=256000,len(result)
    assert result.startswith(b'import ContractExact\n')
    return result


COMMAND=re.compile(r'(?m)^(?:@\[[^\n]*?\]\s+)?(?:private\s+)?(lemma|theorem|def|abbrev|structure|instance|set_option|local|open|namespace|end)\b')

def declaration_blocks(s):
    ms=list(COMMAND.finditer(s));out=[]
    for i,m in enumerate(ms):
        end=ms[i+1].start() if i+1<len(ms) else len(s)
        nm=re.match(r'\s+([A-Za-z][A-Za-z0-9_]*)',s[m.end():])
        out.append({'kind':m[1],'name':nm[1] if nm and m[1] in ['lemma','theorem','def','abbrev','structure'] else None,'start':m.start(),'end':end,'text':s[m.start():end]})
    return out

def identifiers(s):
    # Base is pinned, and all removed declarations have plain ASCII identifiers.
    # Strings/comments are forbidden from creating dependency claims here.
    assert '"' not in s and '/-' not in s and '--' not in s
    ts=set(re.findall(r'(?<![A-Za-z0-9_])(?:Submission\.)?[A-Za-z][A-Za-z0-9_]*',s))
    return {t.removeprefix('Submission.') for t in ts}

def prune(raw):
    source=make_zero(raw,53,'zero-both').decode()
    assert hashlib.sha256(source.encode()).hexdigest()=='dc610a600468a1982b96ab9421cbb59c3feb0aee058c05f8d2e0e42f992b0d4f'
    blocks=declaration_blocks(source)
    proofs={b['name']:b for b in blocks if b['kind'] in ['lemma','theorem']}
    deps={n:(identifiers(b['text']) & set(proofs))-{n} for n,b in proofs.items()}
    removed={'qCtx8','qCtx14'};why={n:['explicit timeout-root exclusion'] for n in removed}
    while True:
        new={n for n in proofs if n not in removed and deps[n]&removed}
        if not new:break
        for n in new:why[n]=sorted(deps[n]&removed)
        removed|=new
    assert 'correct' in removed
    runtime={b['name']:b['text'] for b in blocks if b['kind'] in ['def','structure','abbrev']}
    residual={n:sorted(identifiers(t)&removed) for n,t in runtime.items() if identifiers(t)&removed}
    assert not residual,residual
    result=source
    for b in reversed(blocks):
        if b['name'] in removed:result=result[:b['start']]+result[b['end']:]
    current={b['name']:b['text'] for b in declaration_blocks(result) if b['kind'] in ['def','structure','abbrev']}
    assert runtime==current
    assert not re.search(r'\b(sorry|admit|axiom|unsafe|native_decide|implemented_by|extern)\b',result)
    assert not re.search(r'(?m)^(?:lemma|theorem) correct\b',result)
    assert len(result.encode())<=256000
    info={'removed_proofs':[{ 'name':n,'depends_on':why[n],'bytes':len(proofs[n]['text'].encode()),'sha256':hashlib.sha256(proofs[n]['text'].encode()).hexdigest()} for n in sorted(removed)],'runtime_declaration_count':len(runtime),'runtime_declaration_chunks_byte_identical':True,'runtime_references_to_removed_proofs':residual,'kept_proof_count':len(proofs)-len(removed)}
    return result.encode(),info

def transform(raw,submission,variant):
    assert submission==53 and variant=='zero-runtime-native'
    assert hashlib.sha256(raw).hexdigest()==BASE_SHA
    return prune(raw)[0]

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--base',type=Path,default=BASE);p.add_argument('--output',type=Path,default=HERE/'private/zero-runtime-native53.lean');a=p.parse_args()
    data,info=prune(a.base.read_bytes());a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(data)
    info.update(at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),base_sha256=BASE_SHA,candidate_sha256=hashlib.sha256(data).hexdigest(),candidate_bytes=len(data),recipe_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),file_dependencies=[],proof_state='UNPROVED_NATIVE_RESEARCH_ONLY; no changed Submission.correct',scope='Runtime-identical to dc610a60; only qCtx8/qCtx14 and explicit transitive proof dependents removed. No arithmetic/guard/shape/array change. Native build may still be slow if recursive definitions are the cause.')
    (HERE/'zero-runtime-native-receipt.json').write_text(json.dumps(info,indent=2)+'\n');print(json.dumps(info,indent=2))
