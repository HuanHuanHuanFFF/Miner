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

def transform(raw,submission,variant):
    assert submission==53 and hashlib.sha256(raw).hexdigest()==BASE_SHA
    s=raw.decode('utf-8');s,_=compact_proof_names(s)
    if variant in ['zero-channel','zero-both']:s=zero_channel(s)
    if variant in ['zero-spatial','zero-both']:s=zero_spatial(s)
    assert variant in ['compact-control','zero-channel','zero-spatial','zero-both']
    result=s.encode('utf-8');assert len(result)<=256000,len(result)
    assert result.startswith(b'import ContractExact\n')
    return result

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--base',type=Path,default=BASE);args=parser.parse_args()
    raw=args.base.read_bytes();_,mapping=compact_proof_names(raw.decode())
    outdir=HERE/'private';outdir.mkdir(exist_ok=True)
    rows=[]
    for variant in ['compact-control','zero-channel','zero-spatial','zero-both']:
      result=transform(raw,53,variant);out=outdir/(variant+'53.lean');out.write_bytes(result)
      rows.append({'variant':variant,'sha256':hashlib.sha256(result).hexdigest(),'bytes':len(result),'path':str(out)})
    receipt={'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'base_sha256':BASE_SHA,'base_bytes':len(raw),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'variants':rows,'proof_renames':mapping,'proof_state':'UNCOMPILED_EXACT_LOOP_PROOF; needs fresh original all12 gate','performance_state':'UNKNOWN; complete MobileNet quick paired measurement needed','preserved':'All #53 full paths, per-row guards, sparse weights, smallK fallback, same-exact-dot bias, finish/fallback behavior and all12 statement. Only skip terms whose existing prepared value is exactly arithmetic zero.'}
    (HERE/'zero-mobile53-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
