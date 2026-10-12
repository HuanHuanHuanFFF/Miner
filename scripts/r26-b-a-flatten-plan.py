"""Freeze isolated A-flatten original encoder, pure profile and full-state observer."""
from pathlib import Path
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
NAME = 'r26-b-552-a-flatten'
CAPTURE = 'evidence/round26/extension4h/official-b23-live/pareto-pages.json'


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def main():
    folder = ROOT/'evidence/round26/route-b'
    out = folder/'b31-a-flatten-native.json'
    assert not out.exists()
    spec = json.loads((folder/'b21-tree-prefix-native.json').read_bytes())
    candidate = next(e for e in spec['entries'] if not e['control'])
    candidate.update(name=NAME, path='candidates/'+NAME,
                     hashes={f: sha((ROOT/'candidates'/NAME/f).read_bytes()) for f in ('parse.rs','Parse.lean')})
    names = [e['name'] for e in spec['entries']]
    spec.update(snapshot_pages=CAPTURE, r15_profile_entry=NAME, r26_b_a_flatten_counts=True,
                r15_profile_functions=['parse','a_engine','a_find_all','a_dp_pass','a_sample_pass'],
                screen_orders=[names,names[::-1]],
                description='B31 isolate public652 A helper+DP consumer only onto original552;8KiB full fill/overshoot/rounded/mapping/odd-tail work retained. Original28encoder equality then pure production coarse profile and full cost/ch original reference recomputation on every actual DP invocation. Newcounter clones excluded from production profile,25mincap, no paired/gate/share claim.')
    deps = ['scripts/r26-b-build-a-flatten.py','scripts/r26-b-a-flatten-model.py','scripts/r26-b-a-flatten-counts.py',
            'scripts/r26-b-a-flatten-plan.py','scripts/r26-b-preflight-draft.py',
            'evidence/round26/route-b/b31-a-flatten-predeclared.md','evidence/round26/route-b/b31-a-flatten-finite-model.json',
            'references/round26-public-652/parse.rs','references/round26-public-652/source-receipt.json',CAPTURE]
    spec['r26_required_files'] = {p: sha((ROOT/p).read_bytes()) for p in deps}
    check = importlib.import_module('r26-b-a-flatten-counts').preflight(spec)
    out.write_text(json.dumps(spec,indent=2)+'\n')
    pre = folder/'b31-a-flatten-structure-preflight.json'
    assert not pre.exists()
    pre.write_text(json.dumps(check,indent=2)+'\n')
    print(json.dumps({'draft':out.relative_to(ROOT).as_posix(),'hashes':candidate['hashes'],**check}))


if __name__=='__main__':
    main()
