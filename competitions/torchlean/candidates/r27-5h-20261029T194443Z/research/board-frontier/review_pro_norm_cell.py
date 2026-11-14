"""C independent actual-row/numerator/midpoint review of the Pro normalization intake."""
from __future__ import annotations
from collections import Counter
from datetime import datetime,timezone
from pathlib import Path
import hashlib,json,math,struct,sys,importlib.util
sys.dont_write_bytecode=True
import norm_frontier as nf
M=(1<<64)-1
HERE=Path(__file__).resolve().parent

def pair(x):return x>>64,x&M
def join(x):return (x[0]<<64)+x[1]
def add(a,b):
 l=(a[1]+b[1])&M;return(a[0]+b[0]+int(l<a[1]))&M,l
def sub(a,b):return(a[0]-b[0]-int(a[1]<b[1]))&M,(a[1]-b[1])&M
def mul(a,b):
 p=(a&0xffffffff)*b;q=(a>>32)*b;l=(p+((q<<32)&M))&M
 return(q>>32)+int(l<p),l
def fits(a,s):
 if s==0:return True
 if s<64:return(a[0]>>(64-s))==0
 if s==64:return a[0]==0
 if s<128:return a[0]==0 and(a[1]>>(128-s))==0
 return False
def shift(a,s):
 if s==0:return a
 if s<64:return((a[0]<<s)|(a[1]>>(64-s)))&M,(a[1]<<s)&M
 return(a[1]<<((s-64)%64))&M,0
def field(w):
 e=(w>>23)&255;return bool(w>>31),(w&0x7fffff)+(0 if e==0 else 1<<23),max(0,e-1),e

def parts(n,b0,ss,sa,dw,w,g,b):
 sd,md,idd,ed=field(dw);sw,mw,iw,ew=field(w);sg,mg,ig,eg=field(g);sb,mb,ib,eb=field(b)
 if n==0 or n>=4096 or b0>255 or sa>=1<<60 or ed in[0,255]or sd or 255 in[ew,eg,eb]:return None,'outer_guard'
 if mw and(not b0<=iw or iw-b0>24):return None,'input_shift_guard'
 x=0 if mw==0 else(n*((mw<<((iw-b0)%64))&M))&M
 cs=(sw if sa<=x else not sw)if sw==ss else sw
 cv=((x-sa if sa<=x else sa-x)if sw==ss else x+sa)&M
 assert x<1<<60 and cv<1<<61
 az=cv==0 or mg==0;bz=mb==0
 if az and bz:return None,'exact_zero_fallback'
 d=n*md;alpha=b0+ig;beta=ib+idd;c=beta if az else alpha if bz else min(alpha,beta);ks=0 if az else alpha-c;bs=0 if bz else beta-c
 a0=mul(cv,mg);b0w=(0,d*mb);assert join(a0)==cv*mg and d*mb<1<<60
 if not(fits(a0,ks)and fits(b0w,bs)):return None,'alignment_guard'
 a=shift(a0,ks);bb=shift(b0w,bs)
 assert join(a)==cv*mg*(1<<ks) and join(bb)==d*mb*(1<<bs)
 if a[0]>>63 or bb[0]>>63:return None,'term127_guard'
 s1=cs!=sg
 if s1==sb:sp=(s1,add(a,bb))
 elif a<bb:sp=(sb,sub(bb,a))
 else:sp=(s1,sub(a,bb))
 want=(-1 if s1 else 1)*join(a)+(-1 if sb else 1)*join(bb)
 assert(-1 if sp[0]else 1)*join(sp[1])==want
 if join(sp[1])==0:return None,'cancellation_zero_fallback'
 return(sp[0],sp[1],d,c,idd,{'ks':ks,'bs':bs,'P_bits':join(sp[1]).bit_length()}),'formed'

def cert(s,p,d,c,idd,q):
 sq,_,_,e=field(q)
 if e in[0,255]or sq!=s or d==0 or d>=1<<36 or join(p)==0:return False
 f=q&0x7fffff;m=(1<<23)+f;l=(0,d*(4*m-(1 if f==0 and e>1 else 2)));u=(0,d*(4*m+2));assert u[1]<1<<62
 a=(idd+e)&M;b=(c+3)&M
 if a<=b:
  k=b-a
  return fits(p,k)and l<shift(p,k)<u
 k=a-b
 return fits(u,k)and shift(l,k)<p<shift(u,k)

def proposal(z):
 s,p,d,c,idd,_=z;v=float(p[0])*2.0**64+float(p[1]);v=(v/float(d))*math.ldexp(1.0,c+874-idd-1023)
 try:q=struct.unpack('<I',struct.pack('<f',v))[0]
 except OverflowError:q=0x7f800000
 return(q&0x7fffffff)|(0x80000000 if s else 0)

def rowcheck(words,g,b,eps,counts,stats):
 n=len(words);K=list(map(nf.key,words));SK=sum(K);Q=sum(x*x for x in K);den=nf.sqrt_ratio(n*Q-SK*SK+n*n*nf.key(eps)*(1<<149),n*n<<298);DK=nf.key(den)
 fs=list(map(field,words));b0=min((i for _,m,i,_ in fs if m),default=255);S=sum((-1 if s else 1)*(m<<max(0,i-b0))for s,m,i,_ in fs);sa=abs(S)if abs(S)<1<<60 else 1<<60;nu=n if n<4096 else 0
 for j,w in enumerate(words):
  z,state=parts(nu,b0,S<0,sa,den,w,g[j],b[j]);counts[state]+=1
  if z is None:continue
  sign,p,d,c,idd,meta=z;num=(n*K[j]-SK)*nf.key(g[j])+n*DK*nf.key(b[j]);dn=n*DK
  N=(-1 if sign else 1)*join(p);ln=N<<max(0,c-idd);ld=d<<max(0,idd-c)
  assert ln*dn==num*ld,(words,g,b,j,z,num,dn)
  assert c<=508 and idd<=253 and 621<=c+874-idd<=1382
  expected=nf.round_ratio(num,dn,-149);q=proposal(z)
  stats['formed']+=1;stats['max_P_bits']=max(stats['max_P_bits'],meta['P_bits']);stats['max_shift']=max(stats['max_shift'],meta['ks'],meta['bs'])
  for trial in [q,expected,expected^1,(expected+1)&0xffffffff,(expected-1)&0xffffffff,expected^0x80000000]:
   accepted=cert(sign,p,d,c,idd,trial);stats['certificate_trials']+=1
   if accepted:assert trial==expected,(z,trial,expected)
  if cert(sign,p,d,c,idd,q):stats['proposal_accepted']+=1

def main():
 counts=Counter();stats={'formed':0,'max_P_bits':0,'max_shift':0,'certificate_trials':0,'proposal_accepted':0};cells=0
 # ActualMYbc states fromthealreadyseen pre-freezecompleteNMLP formulas.
 for seed in [27051001,27151004,27251007]:
  for profile in ['typical','scale','boundary']:
   i,h,h2=nf.dimensions(seed,profile)
   for kind in ['normal','wide','sparse']:
    for rows in [1,8]:
     x=nf.gen(kind,rows*i,seed+999);x=nf.linear(x,rows,i,h,nf.weights(kind,seed,1,i,h*i),nf.bias(seed,2,h),True);x=nf.norm(x,rows,h,nf.scale(seed+3,h));x=nf.linear(x,rows,h,h2,nf.weights(kind,seed,4,h,h2*h),nf.bias(seed,5,h2),True)
     g=nf.scale(seed+6,h2);b=nf.bias(seed,7,h2)
     for r in range(rows):rowcheck(x[r*h2:(r+1)*h2],g,b,nf.EPS,counts,stats)
     cells+=1
 official_stats=dict(stats);official_counts=dict(counts)
 # Actualfinite rows stresszero-awarealign and 127-bit terms, not arbitraryincoherentmetadata.
 idx=[0,1,63,64,65,125,126,127,190,204,205,206,253]
 for ig in idx:
  for ib in idx:
   for neg in [0,0x80000000]:
    gw=((ig+1)<<23)|0x7fffff;bw=(((ib+1)<<23)|0x7fffff)^neg
    rowcheck([0x3f800000,0xbf800000],[gw]*2,[bw]*2,nf.EPS,counts,stats)
 for n in [1,2,31,255,256,4095,4096]:
  for word in [0,0x80000000,0xbf800000,0x7f7fffff]:
   rowcheck([word]*n,[0x3f800000]*n,[0x3f800000]*n,nf.EPS,counts,stats)
 # Existingauxstores NOT(S1<0). Omittingtheintegrationnegation produces anacceptedwrongnumerator.
 n=1;w=0xbf800000;g=0x3f800000;b=0;dw=nf.sqrt_ratio(nf.key(nf.EPS),1<<149)
 correct,st=parts(1,126,True,1<<23,dw,w,g,b);assert correct is None
 bad,_=parts(1,126,False,1<<23,dw,w,g,b);q=proposal(bad);assert cert(*bad[:5],q)and q!=0
 sign_counter={'rows':1,'n':1,'x':['bf800000'],'gamma':['3f800000'],'bias':['00000000'],'epsilon':f'{nf.EPS:08x}','S1':-(1<<23),'aux_u1':False,'correct_Ssign':True,'wrong_without_bang_word':f'{q:08x}','correct_word':'00000000'}
 # Boundsaremandatory inword-level certify theorem; thiscannotoccurthroughattempt.
 bad_id=(1<<64)-124;assert cert(False,(0,4*(1<<23)),1,0,bad_id,0x3f800000)
 exponent_counter={'d':1,'c':0,'id':bad_id,'P':4*(1<<23),'accepted_q':'3f800000','exact_floorlog2':-(1<<64),'correct_round32':'00000000','scope':'Standalonecertify withoutcaller c/idbounds ONLY; actualattempt excludes this.'}
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'INDEPENDENT_ACTUAL_ROW_NAT_ORACLE_AND_WORD_MODEL_REVIEW_NO_LEAN','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'official_old_cells':cells,'official_counts':official_counts,'official_stats':official_stats,'all_counts':dict(counts),'all_stats':stats,'missing_sign_negation_mutant':sign_counter,'unbounded_standalone_certify_mutant':exponent_counter,'observed_wrong_acceptances_actual_integration':0,'limits':['NotLean ornativeexecution','No new full12correct','Countsnotcostshare/probability','Onlypreviouslyseenformulaandnewadversarialrows, no9confirmationdata']};(HERE/'pro-norm-intake-independent-model.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps(out))
if __name__=='__main__':main()
