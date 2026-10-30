"""Original finite full-MobileNet formula census, not Lean/native or timing evidence."""
from __future__ import annotations
from pathlib import Path
import hashlib, importlib.util, json, collections, datetime

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
FORMULA=ROOT/'competitions/torchlean/candidates/r27-5h-20261029T194443Z/research/fp-proof/census/formula_snapshot.py'
spec=importlib.util.spec_from_file_location('formula',FORMULA); F=importlib.util.module_from_spec(spec);spec.loader.exec_module(F)

def shape(seed,profile):
    r=F.lcg(8,seed^0x5bd1e995)
    if profile=='boundary': return 13+2*(r[5]%3),5+2*(r[3]%2),9+2*(r[4]%4)
    if profile=='scale': return 20+4*(r[5]%2),4+r[3]%3,8+r[4]%5
    return 12+4*(r[5]%2),4+r[3]%5,8+r[4]%9

def bn(x,c,n,seed,k):
    scales=F.scale((seed+7*k)&F.MASK,c); bias=F.bias(seed,k,c)
    return [maxzero(F.round_ratio(F.key(v)*F.key(scales[j//n])+(F.key(bias[j//n])<<149),1,-298)) for j,v in enumerate(x)]

def maxzero(w): return 0 if w>>31 or (w&0x7fffffff)==0 else w

def yscan(a):
    lo,hi=511,0
    for w in a:
      v=w&0x7fffffff;lo=min(lo,((v-1)&F.MASK)>>23);hi=max(hi,v>>23)
    return lo,hi

def source53_guard(x,w,b,K,C):
    bp=yscan(x);bw=[yscan(w[o*K:(o+1)*K]) for o in range(C)]
    yk=lambda e:max(e-1,0)
    yd=lambda w:F.fields(w)[2]
    ym=lambda w:F.fields(w)[1]
    u64=lambda n:n&((1<<64)-1)
    xm=yk(bp[0])
    for o,(lo,hi) in enumerate(bw):
      xb=126+yd(b[o]);wm=yk(lo)
      if lo!=511 and ym(b[o]) and xb<u64(xm+wm):xm=u64(xb-wm)
    def valid(o,wide):
      lo,hi=bw[o];bias=b[o];xb=126+yd(bias)
      yg=u64(xb-xm) if lo==511 else yk(lo)
      span=u64(yk(bp[1])-xm);wspan=u64(yk(hi)-yk(lo))
      return (K<(4096 if wide else 256) and bp[1]!=255 and hi!=255 and xm<=yk(bp[0]) and yk(bp[0])<=yk(bp[1]) and span<=(39 if wide else 31)
       and (xm<=xb if lo==511 else yk(lo)<=yk(hi) and wspan<=6 and u64(span+wspan)<=(45 if wide else 31))
       and (bias>>23)&255!=255 and (not ym(bias) or (u64(xm+yg)<=xb and u64(xb-u64(xm+yg))<80)))
    narrow=all(valid(o,False) for o in range(C));wide=not narrow and all(valid(o,True) for o in range(C))
    return {'g_narrow':narrow,'g_wide':wide,'xm':xm,'bp':bp,'weight_bounds':bw}

def pool(x,c,h,k):
    o=h//k; out=[]
    for ch in range(c):
      for y in range(o):
       for z in range(o):
        # Contract rounds exact sum once, then divides that rounded result.
        s=sum(F.key(x[(ch*h+y*k+dy)*h+z*k+dx]) for dy in range(k) for dx in range(k))
        w=F.round_ratio(s,1,-149)
        out.append(F.round_ratio(F.key(w),k*k,-149))
    return out

def conv(x,cin,h,cout,k,pad,weights,bias,dw,label):
    cout=cin if dw else cout; K=k*k if dw else cin*k*k; ho=h+2*pad-k+1
    xk=list(map(F.key,x)); wk=list(map(F.key,weights)); bk=[F.key(z)<<149 for z in bias]
    stats=collections.Counter(outputs=cout*ho*ho,logical_macs=cout*ho*ho*K,
        prepared_input_words=cin*(h+2*pad)**2,prepared_weight_words=len(weights))
    stats['weight_zero_count']=sum(v==0 for v in wk)
    guard=source53_guard(x,weights,bias,K,cout)
    out=[]; xs=[]
    for ch in range(cout):
      for y in range(ho):
       for z in range(ho):
        terms=[]; total=bk[ch]
        for t in range(K):
          ic=ch if dw else t//(k*k); dy=(t//k)%k; dx=t%k; yy=y+dy-pad; zz=z+dx-pad
          v=xk[(ic*h+yy)*h+zz] if 0<=yy<h and 0<=zz<h else 0
          w=wk[ch*K+t]; total+=v*w; terms.append((v,w))
          stats['zero_input_macs']+=v==0
          stats['weight_nonzero_macs']+=w!=0
          stats['zero_input_nonzero_weight_macs']+=(v==0 and w!=0)
        out.append(F.round_ratio(total,1,-298));xs.append(terms)
    # Existing dense channel pairing shares x. Existing sparse/depthwise pairing shares w.
    for ch in range(cout):
      for y in range(ho):
       for z in range(0,ho-1,2):
        a=xs[(ch*ho+y)*ho+z]; b=xs[(ch*ho+y)*ho+z+1]
        for (v,w),(v2,w2) in zip(a,b):
          assert w==w2
          if w:
            stats['spatial_pair_nonzero_weight_terms']+=1
            stats['spatial_pair_both_input_zero_terms']+=(v==0 and v2==0)
    nonzero=[F.fields(w)[2] for w in x if w&0x7fffffff]
    stats['input_exponent_span']=max(nonzero)-min(nonzero) if nonzero else 0
    rows=[]
    for ch in range(cin):
      ex=[F.fields(w)[2] for w in x[ch*h*h:(ch+1)*h*h] if w&0x7fffffff]
      rows.append(max(ex)-min(ex) if ex else 0)
    stats['channel_exponent_span_min']=min(rows);stats['channel_exponent_span_max']=max(rows)
    narrow15=0
    for lo,hi in guard['weight_bounds']:
      ws=0 if lo==511 else max(hi-1,0)-max(lo-1,0)
      narrow15+=(guard['g_narrow'] and max(guard['bp'][1]-1,0)-guard['xm']+ws<=15)*ho*ho
    stats['global_singlemul15_outputs']=narrow15
    if dw:
      admitted=0;spans=[]
      for ch in range(cin):
        gg=source53_guard(x[ch*h*h:(ch+1)*h*h],weights[ch*K:(ch+1)*K],bias[ch:ch+1],K,1)
        lo,hi=gg['weight_bounds'][0];ws=0 if lo==511 else max(hi-1,0)-max(lo-1,0)
        span=max(gg['bp'][1]-1,0)-gg['xm']+ws;spans.append(span)
        admitted+=(gg['g_narrow'] and span<=15)*ho*ho
      stats['channel_singlemul15_outputs']=admitted
      stats['channel_singlemul15_spans']=spans
    if k==1:
      admitted=0;minima=collections.Counter();hist=collections.Counter()
      for pos in range(h*h):
        xx=[x[ch*h*h+pos] for ch in range(cin)]
        gg=source53_guard(xx,weights,bias,K,cout);minima[gg['xm']]+=1
        for lo,hi in gg['weight_bounds']:
          ws=0 if lo==511 else max(hi-1,0)-max(lo-1,0)
          span=max(gg['bp'][1]-1,0)-gg['xm']+ws;hist[span]+=1
          admitted+=gg['g_narrow'] and span<=15
      stats['pixel_singlemul15_outputs']=admitted
      stats['pixel_prepared_minima']=dict(minima)
      stats['pixel_singlemul15_span_histogram']=dict(hist)
    return out,{'stage':label,'cin':cin,'cout':cout,'side':h,'K':K,'depthwise':dw,'source53_guard':guard,**stats}

def one(seed,profile,kind):
    n,c1,c2=shape(seed,profile); x=F.gen(kind,3*n*n,(seed+999)&F.MASK); report=[]
    def cv(x,ci,h,co,k,p,wi,bi,dw,label):
      fan=k*k if dw else ci*k*k; count=ci*fan if dw else co*fan
      out,row=conv(x,ci,h,co,k,p,F.weights(kind,seed,wi,fan,count),F.bias(seed,bi,ci if dw else co),dw,label)
      report.append(row);return out
    x=bn(cv(x,3,n,c1,3,1,1,2,False,'stem'),c1,n*n,seed,3)
    x=bn(cv(x,c1,n,c1,3,1,4,5,True,'dw1'),c1,n*n,seed,6)
    x=bn(cv(x,c1,n,c2,1,0,7,8,False,'pw1'),c2,n*n,seed,9)
    x=pool(x,c2,n,2); n2=n//2
    x=bn(cv(x,c2,n2,c2,3,1,10,11,True,'dw2'),c2,n2*n2,seed,12)
    x=bn(cv(x,c2,n2,c2,1,0,13,14,False,'pw2'),c2,n2*n2,seed,15)
    x=pool(x,c2,n2,n2)
    out=F.linear(x,1,c2,10,F.weights(kind,seed,16,c2,c2*10),F.bias(seed,17,10),False)
    checksum=2166136261
    for w in out:checksum=((checksum^w)*16777619)&F.MASK
    return {'seed':seed,'profile':profile,'kind':kind,'batch':1,'shape':[n,c1,c2], 'stages':report,'formula_output_checksum':checksum}

def main():
    rows=[one(seed,profile,kind) for seed in [42,12345] for profile in ['typical','scale','boundary'] for kind in ['normal','wide','sparse']]
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Finite formula census only; no native cost, original all12 gate or champion claim','formula_dependency_sha256':hashlib.sha256(FORMULA.read_bytes()).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'rows':rows}
    (HERE/'mobile-census.json').write_text(json.dumps(out,indent=2)+'\n')
    for stage in ['stem','dw1','pw1','dw2','pw2']:
      ss=[s for r in rows for s in r['stages'] if s['stage']==stage]
      a=sum(s['zero_input_nonzero_weight_macs'] for s in ss);b=sum(s['weight_nonzero_macs'] for s in ss)
      p=sum(s['spatial_pair_both_input_zero_terms'] for s in ss);q=sum(s['spatial_pair_nonzero_weight_terms'] for s in ss)
      print(stage, 'zero_input_nonzero_weight',a,b,round(a/b,4),'both_zero_spatial_pairs',p,q,round(p/q,4))
if __name__=='__main__':main()
