#!/usr/bin/env python3
"""Independent finite interpreter of the generated transform/inverse expressions.
Checks the actual row/column layout and B0-2 finish plan, not Lean/native execution.
"""
from pathlib import Path
import hashlib,importlib.util,json,re,random,time
P=Path(__file__).resolve().parent
def load(name,path):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
B=load('spatial_builder_review',P/'build_spatial11.py')
Q=load('spatial_pipeline_review',P/'spatial_word_pipeline.py');C=Q.C;F=Q.F;W=Q.W
MASK=(1<<64)-1
def generated_transform(matrix,kind):
    runtime=B.runtime();start=runtime.index('def R8'+kind+'(')
    end=runtime.find('\ndef ',start+5)
    text=runtime[start:end if end!=-1 else None]
    center=1<<58 if kind=='I' else 1<<35
    env={'R8X':1<<58,'R8Q':1<<35}
    for r,row in enumerate(matrix):
      for c,value in enumerate(row):env[f'a{r}{c}']=value&MASK
    out=[]
    for line in text.splitlines():
      line=line.strip()
      if re.match(r'let r\d\d:=',line):
        name,expr=line[4:].split(':=',1)
        assert re.fullmatch(r'[a-zA-Z0-9_+\-]+',expr)
        env[name]=eval(expr,{'__builtins__':{}},env)&MASK
      elif line.startswith('v:=v.push(('):
        expr=line[len('v:=v.push(('):-len(').toNat)')]
        assert re.fullmatch(r'[a-zA-Z0-9_+\-]+',expr)
        out.append(eval(expr,{'__builtins__':{}},env)&MASK)
    assert len(out)==16
    expected=W.transform(matrix,W.BT if kind=='I' else W.G)
    assert out==[expected[r][c]+center for c in range(4) for r in range(4)]
    assert all(0<v<(1<<59 if kind=='I' else 1<<36) for v in out)
    return out
def generated_inverse(partials):
    runtime=B.runtime();start=runtime.index('@[inline] def R8O(');end=runtime.index('\ndef R8Run(',start)
    text=runtime[start:end]
    env={f'm{i}':Q.combine_split(*partials[i]) for i in range(16)}
    for line in text.splitlines():
      line=line.strip()
      if not line.startswith('let ') or ':=' not in line:continue
      name,expr=line[4:].split(':=',1)
      if name.startswith('t') or name in ['a','b0','c','d']:
        if expr.startswith('R8A('):op=Q.add
        elif expr.startswith('R8S('):op=Q.sub
        else:continue
        refs=re.findall(r'\bm\d+\b|\bt\d\d\b',expr)
        assert len(refs)==3,(line,refs)
        env[name]=op(op(env[refs[0]],env[refs[1]]),env[refs[2]])
    got=[[env['a'],env['b0']],[env['c'],env['d']]]
    expected=Q.inverse([[env[f'm{c*4+r}'] for c in range(4)] for r in range(4)])
    assert got==expected
    return got
def contexts(inp,ci,n,co,w,b):
    hit,g=C.guard11(inp,w,b,ci*9)
    if ci>8 or ci==0 or n==0 or n%2 or co<4:return None,'shape'
    if any(F.fields(x)[1]==0 for x in w):return None,'zero_weight'
    if not hit:return None,'original_narrow'
    xm=g['xm'];rows=[]
    for (wl,wh),bias in zip(g['weight_exp_bounds'],b):
      wm=C.yk(wl);e=xm+wm;sh=126+F.fields(bias)[2]-e
      if not(2<=e<=1000 and (F.fields(bias)[1]==0 or sh<=76)):return None,'rebase_bias'
      rows.append((wm,e-2))
    return (xm,rows),'admitted'
def actual_runtime_model(inp,ci,n,co,w,b):
    ctx,why=contexts(inp,ci,n,co,w,b)
    if ctx is None:return None,why,None
    xm,rows=ctx;k=ci*9
    keys=list(map(F.key,inp));wk=list(map(F.key,w))
    aligned=[v//(1<<xm) for v in keys]
    U=[]
    for o in range(co):
      row=wk[o*k:(o+1)*k];wm,_=rows[o]
      a=[v//(1<<wm) for v in row]
      for c in range(ci):U.extend(generated_transform([a[c*9+r*3:c*9+r*3+3] for r in range(3)],'W'))
    out=[None]*(co*n*n);big_partials=0;zero_replays=0
    for y in range(0,n,2):
      for x in range(0,n,2):
        V=[]
        for c in range(ci):
          matrix=[[aligned[(c*n+yy)*n+xx] if 0<=yy<n and 0<=xx<n else 0 for xx in range(x-1,x+3)] for yy in range(y-1,y+3)]
          V.extend(generated_transform(matrix,'I'))
        for o in range(co):
          fuel=16*(ci+1);q=c=0;a0=a1=0;L=[];H=[]
          while fuel:
            fuel-=1
            if c<ci:
              xv=V[c*16+q];wv=(U[(o*ci+c)*16+q]-(1<<35))&MASK
              a0=(a0+(xv&((1<<25)-1))*wv)&MASK
              a1=(a1+(((xv>>25)-(1<<33))&MASK)*wv)&MASK;c+=1
            else:
              lo=(a0+(1<<62))&MASK;hi=(a1+(1<<62))&MASK
              big_partials+=int(lo>=1<<63)+int(hi>=1<<63)
              L.append(lo);H.append(hi);q+=1;c=0;a0=a1=0
          assert q==16 and len(L)==len(H)==16
          partials=[((l-(1<<62))&MASK,(h-(1<<62))&MASK) for l,h in zip(L,H)]
          tile=generated_inverse(partials);_,e=rows[o]
          biasfull=F.key(b[o])<<149
          assert biasfull%(1<<e)==0
          for dy in range(2):
            for dx in range(2):
              total=Q.add(tile[dy][dx],Q.words(biasfull//(1<<e)));z=Q.signed128(total)
              direct=sum(F.key(Q.get(inp,ci,n,n,c,y+dy+r-1,x+dx+s-1))*wk[o*k+c*9+r*3+s] for c in range(ci) for r in range(3) for s in range(3))+biasfull
              assert z*(1<<e)==direct
              if z==0:
                zero_replays+=1;result=0x80000000 if Q.zero_sign(inp,w,b,ci,n,n,o,y+dy,x+dx) else 0
              else:result=F.round_ratio(z,1,e-298)
              out[(o*n+y+dy)*n+x+dx]=result
    assert all(v is not None for v in out)
    return out,why,{'big_nat_partial_stores':big_partials,'zero_replays':zero_replays,'outputs':len(out)}
def main():
    t=time.time();records=[];fallback={};original=C.conv
    def compare(inp,ci,n,co,w,b):
      expected,stats=original(inp,ci,n,co,w,b)
      result,why,counts=actual_runtime_model(inp,ci,n,co,w,b)
      if result is None:fallback[why]=fallback.get(why,0)+1
      else:
        assert result==expected
        records.append({'shape':[ci,n,n,co],'input_checksum':C.hasharr(inp),'expected_checksum':C.hasharr(expected),'runtime_model_checksum':C.hasharr(result),'counts':counts})
      return expected,stats
    C.conv=compare
    for profile in ['legacy','scale','boundary']:
      for kind in ['normal','wide','sparse']:C.run(42,kind,profile,1)
    rng=random.Random(28001818)
    for _ in range(100):
      g=rng.randrange(32);f=rng.randrange(min(6,31-g)+1)
      d=[[rng.randrange(-(1<<(24+g))+1,1<<(24+g)) for _ in range(4)] for _ in range(4)]
      w=[[rng.randrange(-(1<<(24+f))+1,1<<(24+f)) for _ in range(3)] for _ in range(3)]
      generated_transform(d,'I');generated_transform(w,'W')
    raw=(P.parents[1]/'competition-state/source-private/official-11.lean').read_bytes();result=B.transform(raw)
    r={'state':'GENERATED_EXPRESSIONS_AND_REBASED_FULL_CONV_MODEL_MATCH','source_sha256':hashlib.sha256(result).hexdigest(),'recipe_sha256':hashlib.sha256((P/'build_spatial11.py').read_bytes()).hexdigest(),'runtime_sha256':hashlib.sha256(B.runtime().encode()).hexdigest(),'old_public_seed':42,'profiles':['legacy','scale','boundary'],'admitted_calls':len(records),'matched_outputs':sum(x['counts']['outputs'] for x in records),'fallback_calls':fallback,'records':records,'random_transform_pairs':100,'big_nat_partial_stores_observed':sum(x['counts']['big_nat_partial_stores'] for x in records),'scope':'Parses generated transform and inverse expressions; separately emulates exact fuel loop, partial cache encoding and B0-2 bias. Input/weight getters use source-derived indices. Not Lean compilation or actual native execution. Shared final rounder; pre-round integer independently compared.','resource_elapsed_seconds':time.time()-t,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'not_claimed':['all12 proof','native speedup','formal champion result']}
    (P/'spatial-runtime-model-receipt.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:r[k] for k in ['state','source_sha256','admitted_calls','matched_outputs','fallback_calls','random_transform_pairs','big_nat_partial_stores_observed','resource_elapsed_seconds']},indent=2))
if __name__=='__main__':main()
