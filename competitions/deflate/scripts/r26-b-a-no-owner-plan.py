"""Freeze one owner-free real consumer using existing strict all-call reference observer."""
from pathlib import Path
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1]
NAME='r26-b-552-a-no-owner'
CAPTURE='evidence/round26/extension4h/official-b29-live/pareto-pages.json'


def main():
    folder=ROOT/'evidence/round26/route-b';out=folder/'b36-a-no-owner-native.json';assert not out.exists()
    spec=json.loads((folder/'b31-a-flatten-native.json').read_bytes())
    entry=next(e for e in spec['entries'] if not e['control'])
    parent=dict(entry);parent['control']=True
    for k in ['comparison_baseline','native_decode_reference','expected_equivalent_to']:parent.pop(k,None)
    spec['entries'].append(parent)
    entry.update(name=NAME,path='candidates/'+NAME,hashes={f:hashlib.sha256((ROOT/'candidates'/NAME/f).read_bytes()).hexdigest() for f in ('parse.rs','Parse.lean')})
    names=[e['name'] for e in spec['entries']]
    spec.update(snapshot_pages=CAPTURE,r15_profile_entry=NAME,r26_b_a_flatten_module='r26-b-a-no-owner-counts',
                native_encoder_references=['public552','r26-b-552-a-flatten'],screen_orders=[names,names[::-1]],
                description='B36 one final owner-free flatten realconsumer: remove4KiB dl/init and564Mowner stores, retainfullbl/roundscan/odd fallback, winninglength recoversactualoriginalowner. Reuseexact everyDPcall fullcost/ch reference and original28encoder, pureproductionprofile;smallrealownerread counts only.25mincap, no proof/stable share.')
    deps=['scripts/r26-b-build-a-no-owner.py','scripts/r26-b-a-no-owner-model.py','scripts/r26-b-a-no-owner-counts.py','scripts/r26-b-a-no-owner-plan.py',
          'scripts/r26-b-a-flatten-counts.py','scripts/r26-b-a-flatten-model.py','scripts/r26-b-preflight-draft.py',
          'evidence/round26/route-b/b36-a-no-owner-predeclared.md','evidence/round26/route-b/b36-a-no-owner-finite-model.json',CAPTURE]
    spec['r26_required_files']={p:hashlib.sha256((ROOT/p).read_bytes()).hexdigest() for p in deps}
    check=importlib.import_module('r26-b-a-no-owner-counts').preflight(spec)
    out.write_text(json.dumps(spec,indent=2)+'\n')
    pre=folder/'b36-a-no-owner-structure-preflight.json';assert not pre.exists();pre.write_text(json.dumps(check,indent=2)+'\n')
    print(json.dumps({'draft':out.relative_to(ROOT).as_posix(),**check}))


if __name__=='__main__':main()
