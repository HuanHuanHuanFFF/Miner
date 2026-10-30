"""Exact wrapped-word mutant counterexample for the RMS rrsG integration guards."""

from pathlib import Path

from datetime import datetime,timezone

import json,hashlib

import norm_frontier as nf

M=(1<<64)-1

def sh(x,s):return (x<<(s%64))&M

def raw_rrs(s,N,D,U,V):

 i=(max(0,N.bit_length()-1)-max(0,D.bit_length()-1))&M

 R=(i-1)&M if N<sh(D,i)else i

 a=sh(N,(23-R)&M)if R<=23 else N

 b=D if R<=23 else sh(D,(R-23)&M)

 q=a//b if b else 0;r=a%b if b else a;tw=(2*r)&M

 m=q if tw<b else(q+1)&M if b<tw else q if q%2==0 else(q+1)&M

 k=int(m==16777216);RU=(R+U)&M;e=(RU+k-V)&M

 if V<RU and e<=254:

  f=(((8388608 if k==1 else m)-8388608)&M)&0x7fffff

  return(int(s)<<31)|((e&255)<<23)|f,{'i':i,'R':R,'a':a,'b':b,'rounded_m':m,'encoded_e':e}

 return None,{'i':i,'R':R,'a':a,'b':b,'rounded_m':m,'encoded_e':e}

def main():

 w,g,d=1,0x3f800000,0x00ffffff

 sw,mw,iw=nf.fields(w);sg,mg,ig=nf.fields(g);sd,md,idd=nf.fields(d)

 got,steps=raw_rrs(sw!=sg,mw*mg,md,iw+ig,idd+22)

 exact=nf.round_ratio(sw*sg*mw*mg,md,iw+ig-idd-149)

 assert md>mw*mg and got!=exact

 unit,_=raw_rrs(False,1<<46,1<<23,252,149)

 assert unit==0x3f000000

 # A reachable stableRMS call: one minimumsubnormal input, finite largegamma, positivefiniteeps.
 x=1;gamma=0x7f000000;eps=0x407ffffe
 den=nf.sqrt_ratio(nf.key(x)**2+nf.key(eps)*(1<<149),1<<298)
 sx,mx,ix=nf.fields(x);sg,mg,ig=nf.fields(gamma);sd,md,idd=nf.fields(den)
 bad,trace=raw_rrs(sx!=sg,mx*mg,md,ix+ig,idd+22)
 expected=nf.round_ratio(sx*sg*mx*mg,md,ix+ig-idd-149)
 assert den==0x3fffffff and bad==0x34000000 and expected==0x34000001
 assert all(((v>>23)&255)<255 for v in [x,gamma,eps]) and eps>0
 reachable={'rows':1,'n':1,'x':['00000001'],'gamma':['7f000000'],'epsilon':'407ffffe','rounded_denominator':f'{den:08x}','correct':f'{expected:08x}','unguarded_rrsG':f'{bad:08x}','stable_domain':'Positive n, exactsize arrays, allfinite words, positivefiniteepsilon','steps':trace}
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'CONCRETE_FLOAT32_MUTANT_COUNTEREXAMPLES_WORD_MODEL_NOT_LEAN','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'reachable_rms_call':reachable,'guard_drop':{'w':f'{w:08x}','gamma':f'{g:08x}','denominator':f'{d:08x}','N':mw*mg,'D':md,'correct':f'{exact:08x}','unguarded_rrsG':f'{got:08x}','steps':steps},'offset_mutant':{'w':'3f800000','gamma':'3f800000','denominator':'3f800000','correct':'3f800000','wrongV_idxD_plus23':f'{unit:08x}'},'source_binding':{'rrsG':'retired23/1010c074 lines2403-2410','mkBits_repository':'lean-dojo/FloatLib','mkBits_commit':'0d91825727839f597fd06b22fdd038ea21480f0c','mkBits_path':'FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean','mkBits_git_blob':'dc080c68fa47df803354e28654c3973c6d2b48a2','mkBits_behavior':'Mask exponent8bits/fraction23bits beforepack; not unmasked OR'},'decision':'Preserve D<=N and V=idxD+22 exactly; nativecandidate24b04283 includesboth. These inputs exercisefallback and do notchange frozen candidate.'};Path(__file__).with_name('rms-guard-counterexample.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps(out))

if __name__=='__main__':main()

