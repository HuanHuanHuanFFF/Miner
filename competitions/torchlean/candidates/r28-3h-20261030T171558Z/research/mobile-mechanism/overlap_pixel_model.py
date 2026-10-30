"""Actual old pointwise producer replay of parent's overlap32 accumulator.

Both signed current products and unsigned one-sided products; no frozen code edit.
"""
from pathlib import Path
import importlib.util,hashlib,json,datetime,collections
HERE=Path(__file__).resolve().parent
sp=importlib.util.spec_from_file_location('r28overlapbase',HERE/'pointwise128_model.py');P=importlib.util.module_from_spec(sp);sp.loader.exec_module(P)
M=P.M;F=M.F;B=P.B;MASK=(1<<64)-1;ORIGINAL=M.conv;COUNTS=collections.Counter()
def sint(w):return w-(1<<64) if w>>63 else w
def overlap(values,unsigned):
    L=Q=0
    for p in values:
      assert (0<=p<(1<<64)) if unsigned else (-(1<<63)<=p<(1<<63))
      word=p&MASK;L=(L+word)&MASK
      part=(word>>32) if unsigned else p//(1<<32)
      Q=(Q+part)&MASK
    hi=((Q>>32) if unsigned else sint(Q)//(1<<32))+(L<((Q<<32)&MASK))
    hi&=MASK
    return ((hi<<64)|L) if unsigned else B.signed128(hi,L)
def audit(x,ci,h,co,k,pad,w,b,dw,label):
    out,row=ORIGINAL(x,ci,h,co,k,pad,w,b,dw,label)
    if dw or k!=1 or any((v&0x7fffffff)==0 for v in w):return out,row
    g=M.source53_guard(x,w,b,ci,co)
    if not g['g_narrow']:return out,row
    hw=h*h;bounds=g['weight_bounds'];wm=[max(lo-1,0) for lo,hi in bounds];sw=[max(hi-1,0)-max(lo-1,0) for lo,hi in bounds]
    cap=min([510]+[F.fields(b[o])[2]+126-wm[o] for o in range(co) if F.fields(b[o])[1]])
    for p in range(hw):
      raw=[x[t*hw+p] for t in range(ci)];bp=M.yscan(raw);scale=min(max(bp[0]-1,0),cap)
      X=[B.quant(v,scale) for v in raw]
      assert all(v>=0 for v in X)
      for o in range(co):
        partner=o-1 if o&1 else o+1
        ok=lambda c:bp[0]==511 or max(bp[1]-1,0)-scale+sw[c]<=15
        if partner>=co or not(ok(o) and ok(partner)):continue
        W=[B.quant(v,wm[o]) for v in w[o*ci:(o+1)*ci]]
        signed=[a*v for a,v in zip(X,W)]
        body=overlap(signed,False);assert body==sum(signed)
        q=1<<(24+sw[o]);unsigned=[a*(v+q) for a,v in zip(X,W)]
        corrected=overlap(unsigned,True)-q*sum(X);assert corrected==body
        B0=scale+wm[o];sg,bm,be=F.fields(b[o]);bv=sg*bm*(1<<(be+149-B0)) if bm else 0
        assert F.round_ratio(body+bv,1,B0-298)==out[o*hw+p]
        COUNTS['outputs']+=1;COUNTS['products']+=ci;COUNTS['negative_signed_products']+=sum(v<0 for v in signed);COUNTS['unsigned_products_ge_2pow63']+=sum(v>=(1<<63) for v in unsigned)
    return out,row
def main():
    M.conv=audit
    for seed in [42,12345]:
      for profile in ['typical','scale','boundary']:
       for kind in ['normal','wide','sparse']:M.one(seed,profile,kind)
    # Independent extremal singleton/prefix signs exercise arithmetic versus logical shift.
    fixtures=[[-1],[-(1<<63)],[(1<<63)-1],[-1,1],[-(1<<63),(1<<63)-1],[-(1<<63)]*255,[(1<<63)-1]*255]
    for values in fixtures:assert overlap(values,False)==sum(values)
    for values in [[(1<<64)-1],[(1<<64)-1]*255,[0,(1<<64)-1,1]]:assert overlap(values,True)==sum(values)
    result={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Finite real old-formula producer replay and extremal word fixtures for shared overlap32 proposal. No new kernel/CI/timing/Lean acceptance.','counts':dict(COUNTS),'extremal_fixtures':len(fixtures)+3,'mismatches':0,'source_level_comparison':{'per_product_carry_tests_removed_in_model':COUNTS['products'],'terminal_carry_tests_added_in_model':COUNTS['outputs'],'note':'Source dependency counts only; LLVM may already use efficient ADC and extra SAR may not improve elapsed time.'},'open':'Actual UInt64.toInt64/Int64.shiftRight refinement, sum range invariant, final qCtx2 bridge and whole-model cost','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (HERE/'overlap-pixel-model.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result,indent=2))
if __name__=='__main__':main()
