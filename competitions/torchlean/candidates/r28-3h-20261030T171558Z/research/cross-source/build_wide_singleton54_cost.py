"""Isolated native-cost transfer of public54's wide-row mechanism onto36.

Keeps all138 old runtime declarations and all non-singleton paths. This is
not singleton578f and not a modification of frozen CI3. No correct theorem.
Only a future complete-cost decision can justify the source-specific proof.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse
import hashlib
import json
import re
import sys
sys.dont_write_bytecode=True
from build_centered36_cost import build as diagnostic_base

HERE=Path(__file__).resolve().parent
BASE="595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b"
PRUNED_DIAGNOSTIC="51fd24bd4597980fe64ae9eb0b7cf13147cefc6deb1e16f5e67a9fcc2ef1fc48"
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(def|lemma|theorem|abbrev|structure)\s+([\w.']+)")


def transform(raw,submission=36,variant='wide-singleton54-on36'):
    assert submission==36 and variant=='wide-singleton54-on36'
    assert hashlib.sha256(raw).hexdigest()==BASE
    diagnostic,_=diagnostic_base(raw)
    assert hashlib.sha256(diagnostic).hexdigest()==PRUNED_DIAGNOSTIC
    text=diagnostic.decode();matches=list(DECL.finditer(text));remove=[]
    for i,match in enumerate(matches):
        if match.group(2).startswith('R28C'):
            remove.append((match.start(),matches[i+1].start()))
    assert len(remove)==12,len(remove)
    for start,end in reversed(remove):text=text[:start]+text[end:]
    old='dense:=⟨R28CenteredLinear,R28CenteredGemm⟩'
    assert text.count(old)==1
    text=text.replace(old,'dense:=⟨R28WideSingleton,Ya3M⟩')
    fragment=(HERE/'WideSingleton54Runtime.leanfrag').read_text(encoding='utf-8')
    assert text.count('def kernels:Kernels where')==1
    text=text.replace('def kernels:Kernels where',fragment+'\ndef kernels:Kernels where')
    result=text.encode();assert len(result)<=256000
    assert not re.search(r'(?m)^(?:theorem|lemma) correct\b',text)
    assert text.count('import ')==1 and text.startswith('import ContractExact\n')
    return result


def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    raw=a.source.read_bytes();result=transform(raw);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    donor=HERE.parents[1]/'competition-state/source-private/official-54.lean'
    receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'UNQUEUED_NATIVE_RESEARCH_ONLY_NO_CORRECT',
             'base_sha256':BASE,'mechanism_source54_sha256':hashlib.sha256(donor.read_bytes()).hexdigest(),
             'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),'recipe_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
             'dependencies':{name:hashlib.sha256((HERE/name).read_bytes()).hexdigest()for name in ['build_centered36_cost.py','CenteredDotRuntime.leanfrag','WideSingleton54Runtime.leanfrag']},
             'scope':'Only rows=1,0<n<16384,inputspan<=47 obtains input-only packedcache; originalperoutputweightspan<=7/base>=0/biasgap<80 guard. Allrows>=2 immediatelycalloriginalYaVM; originalscalarGEMM/nativeadd/LN/smallK/nonfinite/zero fallback remain.',
             'distinction':'Old578fhit14880/64500classifierMACs with70950prepitems in18oldcells. Thismechanism finitehitsall64500 with6450inputprepitems; no speed inferred.',
             'proof':'No Submission.correct, no all12 acceptance. Public54 includes a proof foritsownsource only; transplant/packedproducer/modularcorrection/caller proof andproductionbytebudget OPEN.',
             'queue':'No request to addCI or changefrozenCI3; onefuture classifier discriminator only if fullprofile/cost supports investing.',
             'publication':'Onlyownrecipe/fragment/model/receipt public; fullsourceprivate. No wholepublic54body copied orpublished.'}
    a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps({k:receipt[k]for k in ['candidate_sha256','candidate_bytes','state']}))


if __name__=='__main__':main()
