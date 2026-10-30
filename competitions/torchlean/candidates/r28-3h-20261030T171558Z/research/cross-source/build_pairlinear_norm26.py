"""Optional complete-proof composition of two already isolated Mixer recipes.

Does not modify either frozen ingredient or any queued plan. No timings or
proof acceptance are inherited. Coordinator may choose this as one new exact
candidate instead of adding two more independent jobs.
"""
from pathlib import Path
from datetime import datetime,timezone
import argparse
import hashlib
import importlib.util
import json
import os
import re
import sys
sys.dont_write_bytecode=True
from build_norm26_36 import build as norm_build

HERE=Path(__file__).resolve().parent
PAIR_RECIPE="8a59c56f8c92d9f62d85375f3606224cd5bb9c756d4168519940fc4381391e08"
PAIR_SOURCE="7b6e0cbaa7165488eef9fdd2f482bef522bb9b6d165649a88494e210f2a06ae3"
NORM_SOURCE="79615bd5c5c697d27631b999d7211c41dc5d0c4374cd9604324b417b1ad417d7"
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:def|lemma|theorem|structure|abbrev)\s+([\w.']+)")


def sha(b):return hashlib.sha256(b).hexdigest()


def spans(s):
    matches=list(DECL.finditer(s))
    return {m.group(1):(m.start(),matches[i+1].start() if i+1<len(matches)else len(s))for i,m in enumerate(matches)}


def build(raw36,raw27,pair_recipe=None):
    if pair_recipe is None:
        local=HERE/'build_gemm36_pairlinear_v2.py'
        pair_recipe=local if local.is_file()else HERE.parents[1]/'development/native/build_gemm36_pairlinear_v2.py'
    assert sha(pair_recipe.read_bytes())==PAIR_RECIPE
    spec=importlib.util.spec_from_file_location('held_pairlinear_v2',pair_recipe);module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    paired,_=module.build(raw36,raw27);assert sha(paired)==PAIR_SOURCE
    norm,_=norm_build(raw36);assert sha(norm)==NORM_SOURCE
    source=paired.decode();normalized=norm.decode();base=raw36.decode()
    sp=spans(source);np=spans(normalized);bp=spans(base)
    replacements=[]
    for name in ['Ya7G','Ya7Ge']:
        a,b=sp[name];c,d=np[name];e,f=bp[name]
        assert source[a:b]==base[e:f],name
        replacements.append((a,b,normalized[c:d]))
    for a,b,new in sorted(replacements,reverse=True):source=source[:a]+new+source[b:]
    result=source.encode()
    assert len(result)<=256000
    assert 'if k<1||!(A.all finiteWord&&B.all finiteWord)' in source
    assert source.count('import ')==1 and source.startswith('import ContractExact\n')
    ns=spans(source);old_correct=paired.decode()[sp['correct'][0]:sp['correct'][1]]
    assert source[ns['correct'][0]:ns['correct'][1]]==old_correct
    return result


def transform(raw,submission=36,variant='pairlinear-norm26-36',donor_raw=None):
    assert submission==36 and variant=='pairlinear-norm26-36'
    if donor_raw is None:
        root=os.environ.get('TORCHLEAN_ROOT')
        path=Path(root)/'r28-source-private/official-27.lean' if root else HERE.parents[2]/'r27-5h-20261029T194443Z/competition-state/source-private/submission27-Kernel.lean'
        donor_raw=path.read_bytes()
    return build(raw,donor_raw)


def main():
    p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--donor',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    raw=a.source.read_bytes();donor=a.donor.read_bytes();result=build(raw,donor);a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(result)
    receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'OPTIONAL_NEW_COMPOSITION_ALL12_CONNECTED_UNCOMPILED',
      'base_submission':36,'base_sha256':sha(raw),'donor27_sha256':sha(donor),'candidate_sha256':sha(result),'candidate_bytes':len(result),'free_bytes':256000-len(result),
      'recipe_sha256':sha(Path(__file__).read_bytes()),'ingredients':{'pairlinear_allk_v2':PAIR_SOURCE,'norm26_36':NORM_SOURCE},
      'dependencies':{'build_gemm36_pairlinear_v2.py':PAIR_RECIPE,'build_gemm36_pairlinear.py':'80c7bbdd3a3042b4baed85a08ba46f55cb3e571251e4d1f037ba88a448347a96','build_norm26_36.py':sha((HERE/'build_norm26_36.py').read_bytes())},
      'scope':'Relative to exactpairlinearv2, only Ya7G guard and Ya7Ge proof blocks change. Allk finite GEMM bridge, originallinear/nativeadd/LayerNorm traversal/fullfallback stay; originalcorrect theorem textunchanged.',
      'measurement':'UNKNOWN. Complete newall12 and fullMixer paired cost required; component gains not additive and oldproofacceptance not inherited.',
      'freeze':'Bothingredient files and queuedplans untouched. This is only a separate optional newgroup candidate, not permission to replace frozen inputs/results.',
      'publication':'Ownrecipe/receipt only; fullsourceprivate/ephemeral'}
    a.receipt.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8');print(json.dumps({k:receipt[k]for k in ['candidate_sha256','candidate_bytes','free_bytes','state']}))


if __name__=='__main__':main()
