"""Exact finite replay of local-pixel preparation, context cache and mixed dot paths."""
from pathlib import Path
import importlib.util,hashlib,json,datetime,collections,random
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r28pwbase',HERE/'channel128_model.py');B=importlib.util.module_from_spec(spec);spec.loader.exec_module(B)
M=B.M;F=M.F;MASK=(1<<64)-1;ORIGINAL=M.conv;COUNTS=collections.Counter();DETAIL=[]

def split_sum(xs,ws):
    a0=a1=0
    for X,W in zip(xs,ws):
      x=(X+(1<<57))&MASK;w=(W+(1<<31))&((1<<32)-1)
      a0=(a0+(x&((1<<25)-1))*((w-(1<<31))&MASK))&MASK
      a1=(a1+(((x>>25)-(1<<32))&MASK)*((w-(1<<31))&MASK))&MASK
    limb=(a1<<25)&MASK;lo=(limb+a0)&MASK
    hi=((a1>>39)+((-(a1>>63)<<25)&MASK)-(a0>>63)+(lo<limb))&MASK
    return B.signed128(hi,lo)

def context_words(B0,b):
    sign,m,e=F.fields(b);s=(e+126-B0)&MASK;m<<=23
    bh=((m>>1)>>(63-s)) if s<64 else (m<<((s-64)&63))&MASK
    bl=(m<<s)&MASK if s<64 else 0
    return bh,bl,sign,(not m or s<=78) and B0<=1000

def audited(x,cin,h,cout,k,pad,weights,bias,dw,label):
    out,row=ORIGINAL(x,cin,h,cout,k,pad,weights,bias,dw,label)
    if dw or k!=1:return out,row
    if any((w&0x7fffffff)==0 for w in weights):
      COUNTS['sparse_original_outputs']+=len(out);return out,row
    g=M.source53_guard(x,weights,bias,cin,cout)
    if not g['g_narrow']:
      COUNTS['global_guard_original_outputs']+=len(out);return out,row
    hw=h*h; bw=g['weight_bounds']; wm=[max(lo-1,0) for lo,hi in bw]
    cap=510
    for o,b in enumerate(bias):
      if F.fields(b)[1]:
        assert F.fields(b)[2]+126>=wm[o]
        cap=min(cap,F.fields(b)[2]+126-wm[o])
    px=[[x[t*hw+p] for t in range(cin)] for p in range(hw)]
    bx=[M.yscan(xx) for xx in px];ms=[min(max(lo-1,0),cap) for lo,hi in bx]
    for p in range(hw):
      # Direct old Ybh with this pixel, sharing all weight rows, agrees with hoisted cap.
      assert ms[p]==M.source53_guard(px[p],weights,bias,cin,cout)['xm']
      assert ms[p]>=g['xm']
    ml,mh=min(ms),max(ms);width=mh-ml+1
    cache=[context_words(ml+q+wm[o],bias[o]) for o in range(cout) for q in range(width)]
    xp=[[B.quant(v,ms[p]) for v in px[p]] for p in range(hw)]
    wp=[[B.quant(v,wm[o]) for v in weights[o*cin:(o+1)*cin]] for o in range(cout)]
    restored=[];fast_count=0
    for o in range(cout):
      for p in range(hw):
        partner=o-1 if o&1 else o+1
        fast=lambda c:bx[p][0]==511 or max(bx[p][1]-1,0)-ms[p]+max(bw[c][1]-1,0)-wm[c]<=15
        paired=partner<cout
        enabled=paired and fast(o) and fast(partner)
        products=[a*b for a,b in zip(xp[p],wp[o])]
        if enabled:
          hh=ll=0
          for q in products:
            assert -(1<<63)<q<(1<<63)
            hh,ll=B.add128(hh,ll,q)
          total=B.signed128(hh,ll);fast_count+=1
        else:total=split_sum(xp[p],wp[o])
        assert total==sum(products)
        B0=ms[p]+wm[o];b=bias[o];sg,bm,be=F.fields(b)
        bh,bl,_,cf=cache[o*width+ms[p]-ml]
        COUNTS['cached_fast_finish_outputs']+=cf
        COUNTS['general_finish_outputs']+=not cf
        expected_bias=(bm<<(be+149-B0)) if bm else 0
        assert ((bh<<64)|bl)==expected_bias
        total+=sg*expected_bias
        value=F.round_ratio(total,1,B0-298);restored.append(value)
        COUNTS['pointwise_outputs_checked']+=1
        COUNTS['singlemul_outputs_checked']+=enabled
        COUNTS['singlemul_products_checked']+=enabled*cin
        COUNTS['split_fallback_outputs_checked']+=not enabled
    assert restored==out
    COUNTS['prepared_input_values']+=hw*cin;COUNTS['cached_bias_contexts']+=len(cache)
    DETAIL.append({'stage':label,'side':h,'cin':cin,'cout':cout,'scale_min':ml,'scale_max':mh,'distinct_scales':len(set(ms)),'cache_entries':len(cache),'outputs':len(out),'singlemul_outputs':fast_count})
    return out,row

def main():
    M.conv=audited
    rows=[M.one(seed,p,k) for seed in [42,12345] for p in ['typical','scale','boundary'] for k in ['normal','wide','sparse']]
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Finite complete formula replay of pointwise representation and cached bias arithmetic; NOT Lean/native/gate/benchmark','counts':dict(COUNTS),'mismatches':0,'details':DETAIL,'full_model_checksums':[{'seed':r['seed'],'profile':r['profile'],'kind':r['kind'],'checksum':r['formula_output_checksum']} for r in rows],'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in [Path(__file__),HERE/'channel128_model.py',HERE/'mobile_census.py',HERE/'build_pointwise128.py']}}
    (HERE/'pointwise128-model.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps({k:v for k,v in out.items() if k not in ['details','full_model_checksums','source_hashes']},indent=2))
if __name__=='__main__':main()
