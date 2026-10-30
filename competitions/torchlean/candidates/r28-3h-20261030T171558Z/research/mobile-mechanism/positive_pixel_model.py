"""Finite actual-producer replay of parent's one-sided unsigned affine dot proposal.

No frozen kernel change or new CI candidate; validates real pixel scales and correction.
"""
from pathlib import Path
import importlib.util,json,hashlib,datetime,collections
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r28positivebase',HERE/'pointwise128_model.py');P=importlib.util.module_from_spec(spec);spec.loader.exec_module(P)
M=P.M;F=M.F;B=P.B;MASK=(1<<64)-1;ORIGINAL=M.conv;counts=collections.Counter()

def unsigned_add(h,l,p):
    q=(l+p)&MASK
    return (h+(q<l))&MASK,q

def subtract128(h,l,n):
    nl=n&MASK;nh=n>>64
    return (h-nh-(l<nl))&MASK,(l-nl)&MASK

def one_layer(x,cin,h,cout,k,pad,weights,bias,dw,label):
    out,row=ORIGINAL(x,cin,h,cout,k,pad,weights,bias,dw,label)
    if dw or k!=1:return out,row
    if any((w&0x7fffffff)==0 for w in weights):return out,row
    g=M.source53_guard(x,weights,bias,cin,cout)
    if not g['g_narrow']:return out,row
    nonnegative=all(not(w>>31) or (w&0x7fffffff)==0 for w in x)
    counts['complete_pointwise_calls']+=1;counts['actual_nonnegative_calls']+=nonnegative
    if not nonnegative:return out,row
    hw=h*h;bounds=g['weight_bounds'];wm=[max(lo-1,0) for lo,hi in bounds]
    sw=[max(hi-1,0)-max(lo-1,0) for lo,hi in bounds]
    cap=min([510]+[F.fields(bias[o])[2]+126-wm[o] for o in range(cout) if F.fields(bias[o])[1]])
    px=[[x[t*hw+p] for t in range(cin)] for p in range(hw)];bp=[M.yscan(xx) for xx in px]
    ms=[min(max(lo-1,0),cap) for lo,hi in bp]
    xs=[[B.quant(v,ms[p]) for v in px[p]] for p in range(hw)];sums=[sum(v) for v in xs]
    assert all(0<=s<(1<<63) for s in sums)
    counts['prepared_row_sums']+=hw;counts['row_sum_additions']+=hw*cin
    ws=[[B.quant(v,wm[o]) for v in weights[o*cin:(o+1)*cin]] for o in range(cout)]
    for o in range(cout):
      q=1<<(24+sw[o]);wp=[v+q for v in ws[o]]
      assert all(0<v<(1<<31) for v in wp)
      for p in range(hw):
        partner=o-1 if o&1 else o+1
        admissible=lambda c:bp[p][0]==511 or max(bp[p][1]-1,0)-ms[p]+sw[c]<=15
        if partner>=cout or not(admissible(o) and admissible(partner)):continue
        hh=ll=bad_h=bad_l=0
        for a,v in zip(xs[p],wp):
          product=a*v;assert 0<=product<(1<<64)
          hh,ll=unsigned_add(hh,ll,product)
          bad_h,bad_l=B.add128(bad_h,bad_l,product)
          counts['products']+=1;counts['products_ge_signed64']+=product>=(1<<63)
        correction=q*sums[p]
        hh,ll=subtract128(hh,ll,correction);bad_h,bad_l=subtract128(bad_h,bad_l,correction)
        total=B.signed128(hh,ll);bad_total=B.signed128(bad_h,bad_l)
        assert total==sum(a*b for a,b in zip(xs[p],ws[o]))
        b0=ms[p]+wm[o];sg,bm,be=F.fields(bias[o]);bias_term=sg*bm*(1<<(be+149-b0)) if bm else 0
        value=F.round_ratio(total+bias_term,1,b0-298);bad_value=F.round_ratio(bad_total+bias_term,1,b0-298)
        assert value==out[o*hw+p]
        counts['fast_outputs_checked']+=1
        counts['would_be_wrong_with_signed_carry_outputs']+=bad_value!=value
    return out,row

def main():
    M.conv=one_layer
    rows=[M.one(seed,p,k) for seed in [42,12345] for p in ['typical','scale','boundary'] for k in ['normal','wide','sparse']]
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Actual old-formula pixel producer model for future one-sided positive input refinement; no frozen source mutation, no new candidate or native/gate claim','counts':dict(counts),'mismatches':0,'evidence_boundary':'Nonnegative current calls are observations only; an eventual kernel must test actual finite/sign domain, retain negative-zero replay and original excluded-input paths. UINT64 unsigned carry is mandatory.','source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in [Path(__file__),HERE/'pointwise128_model.py',HERE/'mobile_census.py']}}
    (HERE/'positive-pixel-model.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
if __name__=='__main__':main()
