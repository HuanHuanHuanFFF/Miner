"""Held complete-cost prototype on accepted norm26 runtime, no extra CI request.

Exact UInt32 quotient certificate, arbitrary Float proposal, scalar quotient
return and remainder reconstruction; one reciprocal computed per output row.
All old runtime definitions match norm26. New all12 proof is absent.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse
import hashlib
import json
import re
import sys
sys.dont_write_bytecode=True
from build_centered36_cost import build as pruned_with_center
from build_norm26_36 import build as norm26_build

HERE=Path(__file__).resolve().parent
PIN='595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b'
NORM='79615bd5c5c697d27631b999d7211c41dc5d0c4374cd9604324b417b1ad417d7'
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(def|lemma|theorem|structure|abbrev)\s+([\w.']+)")


def once(s,a,b):
    assert s.count(a)==1,(a,s.count(a));return s.replace(a,b)


def ranges(s):
    m=list(DECL.finditer(s));return {x.group(2):(x.start(),m[i+1].start()if i+1<len(m)else len(s))for i,x in enumerate(m)}


def transform(raw,submission=36,variant='checked-norm-division-cost'):
    assert submission==36 and variant=='checked-norm-division-cost'
    assert hashlib.sha256(raw).hexdigest()==PIN
    original=raw.decode();norm,_=norm26_build(raw);assert hashlib.sha256(norm).hexdigest()==NORM;norm=norm.decode()
    pruned,_=pruned_with_center(raw);source=pruned.decode();rr=ranges(source)
    remove=[span for name,span in rr.items()if name.startswith('R28C')];assert len(remove)==12
    for a,b in sorted(remove,reverse=True):source=source[:a]+source[b:]
    source=once(source,'dense:=⟨R28CenteredLinear,R28CenteredGemm⟩','dense:=⟨YaVM,Ya3M⟩')
    sr=ranges(source);nr=ranges(norm)
    replace=[]
    for name in ['Ya7G','Ya7Ge']:
        a,b=sr[name];c,d=nr[name];replace.append((a,b,norm[c:d]))
    for a,b,body in sorted(replace,reverse=True):source=source[:a]+body+source[b:]
    rr=ranges(source)
    get=lambda name:source[rr[name][0]:rr[name][1]]
    body=get('Ya7G')
    # The extracted runtime block includes following section/open commands;
    # exclude those when appending a second definition inside Submission.
    tail=re.search(r'(?m)^end\b',body)
    if tail:body=body[:tail.start()]
    body=once(body,'def Ya7G ','def R28DivYa7G ')
    body=once(body,'(S1a:ו):ο :=','(S1a:ו) (inverse:Float):ο :=')
    body=once(body,'   let q0:=cv/D\n   let r0:=cv%D*Yf gw\n   let qq:=q0*Yf gw+r0/D',
              '   let q0:=R28CheckedQuotient cv D inverse\n   let r0:=(cv-q0*D)*Yf gw\n   let q1:=R28CheckedQuotient r0 D inverse\n   let remainder1:=r0-q1*D\n   let qq:=q0*Yf gw+q1')
    body=once(body,'    let ra:=(r0%D)<<<ks','    let ra:=remainder1<<<ks')
    body=once(body,'    let qa:=(qq<<<ks)+ra/D\n    let rr:=ra%D',
              '    let q2:=R28CheckedQuotient ra D inverse\n    let qa:=(qq<<<ks)+q2\n    let rr:=ra-q2*D')
    inner=get('LNj');inner=re.sub(r'\bLNj\b','R28DivLNj',inner)
    inner=once(inner,'(S1a:ו) (j:Nat)','(S1a:ו) (inverse:Float) (j:Nat)')
    inner=once(inner,'S1n S1a (j+1)','S1n S1a inverse (j+1)')
    inner=once(inner,'(Ya7G n ','(R28DivYa7G n ')
    inner=once(inner,'S1n S1a))','S1n S1a inverse))')
    outer=get('LNr');outer=re.sub(r'\bLNr\b','R28DivLNr',outer)
    outer=once(outer,'  let u:=aux[r]!\n','  let u:=aux[r]!\n  let inverse:Float:=1.0/(nU*Yf s.2.2).toFloat\n')
    outer=once(outer,'(LNj x g b ','(R28DivLNj x g b ')
    outer=once(outer,'u.1 u.2.1 0 out','u.1 u.2.1 inverse 0 out')
    top=get('YbcN');top=once(top,'def YbcN ','def R28DivLayerNorm ');top=once(top,'  LNr x g b ','  R28DivLNr x g b ')
    addition=(HERE/'CheckedNormDivision.leanfrag').read_text(encoding='utf-8')+'\n'+body+'\n'+inner+outer+top
    source=once(source,'def kernels:Kernels where',addition+'\ndef kernels:Kernels where')
    source=once(source,'norm:=⟨rmsnormSpec,YbcN⟩','norm:=⟨rmsnormSpec,R28DivLayerNorm⟩')
    result=source.encode();assert len(result)<=256000
    assert not re.search(r'(?m)^(?:theorem|lemma) correct\b',source)
    assert source.count('import ')==1 and source.startswith('import ContractExact\n')
    return result


def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    raw=a.source.read_bytes();result=transform(raw);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'HELD_NEW_NORM_COST_PROTOTYPE_NO_CORRECT_NO_QUEUE',
      'raw36_sha256':PIN,'runtime_baseline_norm26_sha256':NORM,'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
      'dependencies':{name:hashlib.sha256((HERE/name).read_bytes()).hexdigest()for name in ['build_centered36_cost.py','CenteredDotRuntime.leanfrag','build_norm26_36.py','CheckedNormDivision.leanfrag']},
      'mechanism':'Threeactual cv/r0/ra quotient pairs usecached Float1/D proposals andexactwidenedUInt32 rangechecks, neighbors then hardwaredivision fallback. Quotientonlyscalar return, remainder=a-q*D; no newruntime pairconstructor or reciprocalarray. OneFloatdivision perrowinsideLNr, allprep/drop counted.',
      'arithmetic':'Certificatecorrectness doesnot assume Floataccuracy or cacheidentity. d,qUInt32 makeqdexactinUInt64; product<=a and a-product<d implyq=a/d. Remainderreconstructionexactincludingd0 ifqfromoriginaldivision. FormalintegrationstillOPEN.',
      'evidence':'mixer-checked-division-census.json:34296oldseenquotientpairs,34218firstcheck,78exactfallback(q>=2^32),18completeoldoutputs unchanged. Notnativecost.',
      'new_premise':'CI3norm26 full12PASS and5.56percentgain; measuredreferenceLayerNorm22-45.5percent of4entrytime. OldR27Floatcheckerwasnever timed; integerreciprocalc688negative notsameimplementation.',
      'comparison':'Futurecost must identify exactnorm26control, orcompareboth toexact36 and separateknownnorm26gain. Do notmultiply a ratioagainstnorm26 bytheunadjusted36/championchain.',
      'queue':'No modificationtoCI3/CI4 orrequestforextrajob. Rootmaychooseonlyaftercurrentbudget/nearboardevidence; actualfull12/restorationbytebudget/nativecostUNKNOWN.',
      'publication':'Ownrecipe/runtimefragment/models only; fullsourceprivate.'}
    a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps({k:receipt[k]for k in ['candidate_sha256','candidate_bytes','state']}))


if __name__=='__main__':main()
