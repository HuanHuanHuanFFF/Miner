# Self-contained archival v3 proof prefix package; no new CI request.
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

def old_make_zero(raw,submission,variant):
    assert submission==53 and hashlib.sha256(raw).hexdigest()==BASE_SHA
    s=raw.decode('utf-8');s,_=compact_proof_names(s)
    if variant in ['zero-channel','zero-both']:s=zero_channel(s)
    if variant in ['zero-spatial','zero-both']:s=zero_spatial(s)
    assert variant in ['compact-control','zero-channel','zero-spatial','zero-both']
    result=s.encode('utf-8');assert len(result)<=256000,len(result)
    assert result.startswith(b'import ContractExact\n')
    return result

HELPERS='lemma r28Z9 (w:ق):Y9 0x200000000000000 w=0:=by\n simp only[Y9,show ((0x200000000000000:ق)&&&0x1FFFFFF)=0 from by decide,UInt64.zero_mul]\nlemma r28Z1 (w:ق):cq1 0x200000000000000 w=0:=by\n simp only[cq1,show (((0x200000000000000:ق)>>>25)-0x100000000)=0 from by decide,UInt64.zero_mul]\n'

def fixed(raw):
    s=old_make_zero(raw,53,'zero-both').decode()
    mark='@[specialize] def qCtx7 ';assert s.count(mark)==1;s=s.replace(mark,HELPERS+mark)
    before='''   · simp only [dif_pos hz]
     simpa [hz,Y9,cq1] using qCtx8 n fa fb fc B C bw cw cb0 cb1 hc0 hc1 z0 z1 a b c d (k+1)'''
    after='''   · rw[dif_pos hz]
     conv_rhs => simp only[hz,r28Z9,r28Z1,UInt64.add_zero]
     exact qCtx8 n fa fb fc B C bw cw cb0 cb1 hc0 hc1 z0 z1 a b c d (k+1)'''
    assert s.count(before)==1;s=s.replace(before,after)
    before='''   · simp only [dif_pos hz]
     simpa [hz.1,hz.2,Y9,cq1] using qCtx14 n f g w B bw cb hc z0 z1 a b c d (k+1)'''
    after='''   · rw[dif_pos hz]
     conv_rhs => simp only[hz.1,hz.2,r28Z9,r28Z1,UInt64.add_zero]
     exact qCtx14 n f g w B bw cb hc z0 z1 a b c d (k+1)'''
    assert s.count(before)==1;s=s.replace(before,after)
    result=s.encode();assert len(result)<=256000,len(result)
    return result

def transform(raw,submission,variant):
    assert submission==53 and variant in ['zero-both-proof-v3','repair-q14-v3']
    assert hashlib.sha256(raw).hexdigest()==BASE_SHA
    s=fixed(raw).decode()
    for start,end in [('lemma qCtx8 ','@[specialize] def qCtx9 '),('lemma qCtx14 ','@[inline] def qCtx15 ')]:
        a=s.index(start);b=s.index(end,a);part=s[a:b]
        key='decreasing_by exact ZI n k ‹k<n›';assert part.count(key)==1
        part=part.replace(key,'decreasing_by all_goals exact ZI n k ‹k<n›');s=s[:a]+part+s[b:]
    if variant=='repair-q14-v3':s=s[:s.index('@[inline] def qCtx15 ')]+'\nend Submission\n'
    result=s.encode()
    expected={'zero-both-proof-v3':('1176e3f14238491bebaeec6df72bf3a6ccf6c53827998b1fecebabc94b1d56ad',255768),'repair-q14-v3':('22889ae6e2aa4124d9e1b5d1697ae8772e99ca3a8804bdb7631d1fbb5c59cbc8',170187)}[variant]
    assert hashlib.sha256(result).hexdigest()==expected[0] and len(result)==expected[1]
    return result
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('source',type=Path);p.add_argument('output',type=Path);p.add_argument('--variant',default='repair-q14-v3');a=p.parse_args()
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(transform(a.source.read_bytes(),53,a.variant))
