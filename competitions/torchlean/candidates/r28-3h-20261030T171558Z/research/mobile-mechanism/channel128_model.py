"""Finite exact-word/carry model for channel128, separate from original Lean acceptance."""
from pathlib import Path
import importlib.util,json,hashlib,random,datetime,collections
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('mobile28',HERE/'mobile_census.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
F=M.F;MASK=(1<<64)-1;MASK128=(1<<128)-1
COUNTS=collections.Counter();ORIGINAL_CONV=M.conv

def add128(hi,lo,p):
    word=p&MASK;newlo=(lo+word)&MASK
    return (hi-(word>>63)+(newlo<lo))&MASK,newlo

def signed128(hi,lo):
    u=(hi<<64)|lo
    return u-(1<<128) if u>>127 else u

def quant(w,m):
    s,mant,e=F.fields(w)
    if not mant:return 0
    assert e>=m
    return s*(mant<<(e-m))

def audited_conv(x,cin,h,cout,k,pad,weights,bias,dw,label):
    out,row=ORIGINAL_CONV(x,cin,h,cout,k,pad,weights,bias,dw,label)
    if not dw:return out,row
    K=k*k;ho=h+2*pad-k+1
    split=[]
    for ch in range(cin):
      xx=x[ch*h*h:(ch+1)*h*h];ww=weights[ch*K:(ch+1)*K];bb=bias[ch]
      g=M.source53_guard(xx,ww,[bb],K,1);lo,hi=g['weight_bounds'][0]
      wg=max(lo-1,0);span=max(g['bp'][1]-1,0)-g['xm']+max(hi-1,0)-wg
      enabled=(g['g_narrow'] and span<=15 and not any((w&0x7fffffff)==0 for w in weights))
      for y in range(ho):
       for z in range(ho):
        vals=[]
        for t in range(K):
          yy=y+t//k-pad;zz=z+t%k-pad
          vals.append(xx[yy*h+zz] if 0<=yy<h and 0<=zz<h else 0)
        exact=sum(F.key(v)*F.key(w) for v,w in zip(vals,ww))+(F.key(bb)<<149)
        result=F.round_ratio(exact,1,-298);split.append(result)
        COUNTS['split_outputs_checked']+=1
        if enabled and z<ho//2*2:
          hh,ll=0,0;terms=[]
          for v,w in zip(vals,ww):
            product=quant(v,g['xm'])*quant(w,wg)
            assert -(1<<63)<product<(1<<63)
            hh,ll=add128(hh,ll,product);terms.append(product)
          assert signed128(hh,ll)==sum(terms)
          B=g['xm']+wg;_,bm,be=F.fields(bb)
          assert not bm or be+126>=B
          total=sum(terms)+(F.fields(bb)[0]*bm*(1<<(be+149-B)) if bm else 0)
          candidate=F.round_ratio(total,1,B-298)
          assert candidate==result
          COUNTS['singlemul_outputs_checked']+=1;COUNTS['singlemul_products_checked']+=K
    assert split==out
    return out,row

def main():
    M.conv=audited_conv
    rows=[M.one(seed,p,k) for seed in [42,12345] for p in ['typical','scale','boundary'] for k in ['normal','wide','sparse']]
    rng=random.Random(0x12853)
    for trial in range(20000):
      n=rng.randrange(1,33);terms=[];hh=ll=0
      for _ in range(n):
        p=rng.randrange(-(1<<63)+1,1<<63);terms.append(p);hh,ll=add128(hh,ll,p)
      assert signed128(hh,ll)==sum(terms)
    bad=((1<<24)-1)**2*(1<<16);bh,bl=add128(0,0,bad)
    assert signed128(bh,bl)!=bad
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Finite formula + machine-word carry checks. No Lean/native correctness, timing, all12 gate or ranking claim.','counts':dict(COUNTS),'adversarial_carry_sequences':20000,'mismatches':0,'model_correction':'First draft omitted oneW mantissa 2^23 from the Python bias alignment; detected by exact full output comparison and corrected 126 to149 in model only. Lean candidate reuses unchanged qCtx2 bias context, not this formula.','rejected_span16_counterexample':{'X':((1<<24)-1)<<10,'W':((1<<24)-1)<<6,'true_product':bad,'single_signed_word_value':signed128(bh,bl),'guard15_admits':False},'full_model_checksums':[{'seed':r['seed'],'profile':r['profile'],'kind':r['kind'],'checksum':r['formula_output_checksum']} for r in rows],'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in [Path(__file__),HERE/'mobile_census.py',HERE/'build_channel128.py']}}
    (HERE/'channel128-model.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps({k:v for k,v in out.items() if k not in ['full_model_checksums','source_hashes']},indent=2))
if __name__=='__main__':main()
