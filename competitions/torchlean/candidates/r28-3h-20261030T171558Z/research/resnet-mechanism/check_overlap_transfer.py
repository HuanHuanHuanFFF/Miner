#!/usr/bin/env python3
"""Exact counterexample to feeding truncated spatial products to overlap32.
Also checks the inclusive length endpoint algebraically, without huge arrays.
"""
from pathlib import Path
import hashlib,importlib.util,json
P=Path(__file__).resolve().parent
def load(name,file):
 s=importlib.util.spec_from_file_location(name,file);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
V=load('overlap_transfer_mixed',P/'verify_spatial_mixed.py');F=V.F;C=V.C;Q=V.V.Q;W=V.V.W
MASK=(1<<64)-1
def signed(x):return (x&MASK)-(1<<64) if x&(1<<63) else x&MASK
def overlap_constant(p,n,signed_products):
 l=(n*p)&MASK
 q=p//(1<<32) if signed_products else (p&MASK)>>32
 qword=(n*q)&MASK
 upper=(signed(qword)>>32) if signed_products else qword>>32
 high=(upper+int(l<((qword<<32)&MASK)))&MASK
 return (high,l)
def main():
 hi=0x4c7fffff;lo=0x3cffffff
 inp=[hi]*36;inp[-1]=lo;weights=[lo]*36;bias=[0]*4
 ctx,why=V.contexts(inp,1,6,4,weights,bias);assert ctx is not None and why=='admitted'
 xm,rows=ctx;wm,e=rows[0]
 X=F.key(hi)//(1<<xm);U0=F.key(lo)//(1<<wm)
 tv=W.transform([[X]*4 for _ in range(4)],W.BT)
 tu=W.transform([[U0]*3 for _ in range(3)],W.G)
 product=tv[1][1]*tu[1][1];assert product>1<<64
 p64=product&MASK
 exact_word=F.round_ratio(product,1,e-298)
 wrong_unsigned=F.round_ratio(Q.signed128(overlap_constant(p64,1,False)),1,e-298)
 wrong_signed=F.round_ratio(Q.signed128(overlap_constant(signed(p64),1,True)),1,e-298)
 assert exact_word!=wrong_unsigned and exact_word!=wrong_signed
 inclusive=[]
 for p in [-(1<<63),-1,0,1,(1<<63)-1]:
  n=1<<32;actual=Q.signed128(overlap_constant(p,n,True));assert actual==p*n
  inclusive.append({'p':str(p),'n':n,'sum':str(actual)})
 p=-(1<<63);n=(1<<32)+1
 failed=Q.signed128(overlap_constant(p,n,True));assert failed!=p*n
 result={'state':'SOURCE_DOMAIN_TRANSFER_COUNTEREXAMPLE_AND_LENGTH_ENDPOINT_REVIEW','source_domain':'Preferred spatial ce1a narrow/finite/even/row-nonzero guard; Python modeled admission, not actual Lean execution','shape':{'cin':1,'h':6,'w':6,'cout':4,'kh':3,'kw':3,'stride':1,'pad':1},'raw_input_hi':f'{hi:08x}','raw_input_low_at_bottom_right':f'{lo:08x}','raw_weights':f'{lo:08x}','bias':'00000000','tile':'output origin(2,2), input rows/cols1..4, allhi','xm':xm,'wm':wm,'new_scale':e,'transformed_product':str(product),'product_bits':product.bit_length(),'truncated_u64':str(p64),'exact_output_word':f'{exact_word:08x}','wrong_unsigned_overlap_word':f'{wrong_unsigned:08x}','wrong_signed_overlap_word':f'{wrong_signed:08x}','interpretation':'Overlap32 is valid only if each supplied64-bit product is exact in the stipulated signed/unsigned sense. It cannot recover the missing highbits of this85-bit spatial product, even withone term. This does not refute overlap32 or source11/ce1a; those spatial sources retain split25 products.','inclusive_endpoint':'The paper n<2^32 condition can conservatively be strengthened to n<=2^32: Q>=-2^63 inclusive,Q<2^63,andR<=2^64-2^32. Current kernels are far smaller; no current performance gain is implied.','endpoint_checks':inclusive,'first_outside_closed_counterexample':{'n':n,'p':str(p),'expected':str(p*n),'wrong':str(failed)},'actual_compile_native':'NOT_RUN','new_CI_or_kernel':False,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
 (P/'overlap-transfer-review.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result,indent=2))
if __name__=='__main__':main()
