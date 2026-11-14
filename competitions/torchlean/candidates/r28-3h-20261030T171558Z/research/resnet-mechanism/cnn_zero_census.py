#!/usr/bin/env python3
"""Read-only old public workload replay for source11 route/zero coverage.

Exact integer finite model, NOT Lean execution or a performance measurement.
Uses legacy seed42 by default, known before the R28 freeze. No native/build tools.
"""
import argparse, hashlib, importlib.util, json, time
from pathlib import Path
P=Path(__file__).resolve().parent
MODEL=P.parents[2]/'r27-5h-20261029T194443Z'/'research'/'fp-proof'/'census'/'formula_snapshot.py'
spec=importlib.util.spec_from_file_location('r27model',MODEL)
F=importlib.util.module_from_spec(spec);spec.loader.exec_module(F)

def hasharr(a):
    h=2166136261
    for x in a:h=((h^x)*16777619)&0xffffffff
    return h
def extremes(a):
    exps=[(x>>23)&255 for x in a if x&0x7fffffff]
    return (min(exps,default=511),max(exps,default=0))
def yk(x):return max(x-1,0)
def guard11(inp,w,b,k):
    il,ih=extremes(inp);rows=[w[o*k:(o+1)*k] for o in range(len(b))]
    bw=[extremes(row) for row in rows]
    xm=yk(il)
    for (wl,wh),bi in zip(bw,b):
        xb=126+F.fields(bi)[2]
        if wl!=511 and F.fields(bi)[1] and xb<xm+yk(wl):xm=(xb-yk(wl))&((1<<64)-1)
    flags=[]
    for (wl,wh),bi in zip(bw,b):
        xb=126+F.fields(bi)[2]
        wm=(xb-xm)&((1<<64)-1) if wl==511 else yk(wl)
        wt_ok=xm<=xb if wl==511 else yk(wl)<=yk(wh) and yk(wh)-yk(wl)<=6 and yk(ih)-xm+yk(wh)-yk(wl)<=31
        flags.append(k<256 and ih!=255 and wh!=255 and xm<=yk(il)<=yk(ih) and yk(ih)-xm<=31 and wt_ok and (bi>>23)&255!=255 and (F.fields(bi)[1]==0 or xm+wm<=xb and xb-(xm+wm)<80))
    return all(flags),{'input_min_exp':il,'input_max_exp':ih,'xm':xm,'max_joint_span':max((yk(ih)-xm+yk(wh)-yk(wl) for wl,wh in bw if wl!=511),default=None),'weight_exp_bounds':bw,'row_guard':flags}

def conv(inp,cin,n,cout,w,b):
    x=list(map(F.key,inp));ww=list(map(F.key,w));bb=[F.key(a)<<149 for a in b]
    out=[];zero=terms=0;dotzero=0
    patches=[]
    for y in range(n):
      for z in range(n):
        q=[]
        for c in range(cin):
          for dy in range(3):
            for dx in range(3):
              yy=y+dy-1;xx=z+dx-1
              q.append(x[(c*n+yy)*n+xx] if 0<=yy<n and 0<=xx<n else 0)
        patches.append(q);zero+=q.count(0);terms+=len(q)
    k=cin*9
    for o in range(cout):
      row=ww[o*k:(o+1)*k]
      for q in patches:
        total=sum(a*c for a,c in zip(q,row))+bb[o]
        dotzero+=int(total==0)
        out.append(F.round_ratio(total,1,-298))
    hit,details=guard11(inp,w,b,k)
    stats={'cin':cin,'cout':cout,'side':n,'k':k,'guard_hit_model':hit,'input_zero_count':sum((a&0x7fffffff)==0 for a in inp),'input_size':len(inp),'window_zero_terms':zero,'window_total_terms':terms,'window_zero_fraction':zero/terms,'base_split_multiplies':2*cout*terms,'candidate_skipped_multiplies':4*(cout//2)*zero if hit else 0,'exact_zero_dot_outputs':dotzero,'output_checksum':hasharr(out),'guard':details}
    assert dotzero==0,'signed-zero reference not modeled in this helper'
    return out,stats

def bn(inp,c,hw,seed,layer,relu):
    scales=F.scale((seed+7*layer)&0xffffffff,c);bias=F.bias(seed,layer,c)
    out=[]
    for i,a in enumerate(inp):
        total=F.key(a)*F.key(scales[i//hw])+(F.key(bias[i//hw])<<149)
        out.append(0 if relu and total<=0 else F.round_ratio(total,1,-298))
    return out
def pool(inp,c,n):
    return [max((inp[(ch*n+2*y+dy)*n+2*x+dx] for dy in range(2) for dx in range(2)),key=F.key) for ch in range(c) for y in range(n//2) for x in range(n//2)]
def dimensions(seed,profile):
    r=F.lcg(8,seed^0x5bd1e995);d=lambda i,n:r[i]%n
    if profile=='legacy':return (12 if r[5]%2==0 else 16,4+d(3,5),8+d(4,9))
    if profile=='boundary':return 13+2*d(5,3),5+2*d(3,2),9+2*d(4,4)
    if profile=='scale':return 20+4*d(5,2),4+d(3,3),8+d(4,5)
    return 12+4*d(5,2),4+d(3,5),8+d(4,9)
def run(seed,kind,profile,batch):
    n,c1,c2=dimensions(seed,profile);inputs=F.gen(kind,batch*3*n*n,(seed+999)&0xffffffff)
    rows=[]
    weights={l:F.weights(kind,seed,l,ci*9,co*ci*9) for l,ci,co in [(1,3,c1),(4,c1,c1),(7,c1,c1),(10,c1,c2)]}
    biases={l:F.bias(seed,l,co) for l,co in [(2,c1),(5,c1),(8,c1),(11,c2)]}
    for sample in range(batch):
      x=inputs[sample*3*n*n:(sample+1)*3*n*n]
      saved=None
      for layer,ci,co,side,bnl,rel in [(1,3,c1,n,3,True),(4,c1,c1,n,6,True),(7,c1,c1,n,9,False),(10,c1,c2,n//2,12,True)]:
        x,s=conv(x,ci,side,co,weights[layer],biases[layer+1]);s.update(layer=layer,sample=sample);rows.append(s)
        x=bn(x,co,side*side,seed,bnl,rel)
        if layer==1:saved=x.copy()
        if layer==7:
          x=[0 if (v:=F.key(a)+F.key(b))<=0 else F.round_ratio(v,1,-149) for a,b in zip(x,saved)]
          x=pool(x,c1,n)
    base=sum(r['base_split_multiplies'] for r in rows);skip=sum(r['candidate_skipped_multiplies'] for r in rows)
    return {'seed':seed,'kind':kind,'profile':profile,'batch':batch,'dimensions':[n,c1,c2],'layers':rows,'modeled_guard_hits':sum(r['guard_hit_model'] for r in rows),'layer_calls':len(rows),'base_split_multiplies':base,'candidate_skipped_multiplies':skip,'split_multiply_reduction_fraction':skip/base}

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--profiles',default='legacy');ap.add_argument('--batches',default='1,4');args=ap.parse_args()
    t=time.time();rows=[]
    for profile in args.profiles.split(','):
      for kind in ['normal','wide','sparse']:
       for batch in map(int,args.batches.split(',')):
        r=run(42,kind,profile,batch);rows.append(r)
        print(json.dumps({k:r[k] for k in ['profile','kind','batch','modeled_guard_hits','layer_calls','split_multiply_reduction_fraction']}),flush=True)
    receipt={'state':'FINITE_EXACT_MODEL_ONLY','model_source':str(MODEL),'model_sha256':hashlib.sha256(MODEL.read_bytes()).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'elapsed_seconds':time.time()-t,'inputs':'Old public seed42; no frozen confirmation inputs/results','zero_sign_limitation':'Exact dot zero outputs asserted absent; ReLU maps nonpositive results to +0','rows':rows,'not_claimed':['actual Lean route coverage','native latency','whole-model >=10%','final model output checksum after avgpool/classifier']}
    (P/('cnn-zero-census-'+args.profiles.replace(',','-')+'.json')).write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
if __name__=='__main__':main()
