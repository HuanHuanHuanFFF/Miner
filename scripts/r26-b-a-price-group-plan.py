"""Freeze original current-price group opportunity with original B22 coverage checks."""
from pathlib import Path
import hashlib
import importlib
import json
import sys

sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1]
CAPTURE='evidence/round26/extension4h/official-b29-live/pareto-pages.json'


def main():
    folder=ROOT/'evidence/round26/route-b';out=folder/'b34-price-group-native.json';assert not out.exists()
    spec=json.loads((folder/'b19-tree-edge-native.json').read_bytes())
    spec.pop('r26_b_tree_edge_counts');spec['r26_b_a_price_group_counts']=True
    spec['snapshot_pages']=CAPTURE
    spec['description']='B34 unchanged original552 current dc-price contiguous record/inherited-domain runs. Separate new different-distance groups from oldANsame-distance, preserve all original min/recurrence/writes, count query setup/vector-width/winning owner-ordinal burden only. Original28tokens/decode and exactB22original term/query coverage assertions; no candidate or performance,15min cap.'
    deps=['scripts/r26-b-a-price-group-counts.py','scripts/r26-b-a-price-group-model.py','scripts/r26-b-a-price-group-plan.py',
          'scripts/r26-b-preflight-draft.py','scripts/r26-b-fix-shared-cache.py','scripts/prepare-round24-extract-repro.py',
          'scripts/research-round13-counts.py','evidence/round26/route-b/b34-price-group-predeclared.md',
          'evidence/round26/route-b/b30-price-group-finite-model.json',CAPTURE,
          'evidence/round26/38217519276/compiler-b22-native/diagnostics/r26-b-a-compiler/receipt.json']
    spec['r26_required_files']={p:hashlib.sha256((ROOT/p).read_bytes()).hexdigest() for p in deps}
    check=importlib.import_module('r26-b-a-price-group-counts').preflight(spec)
    out.write_text(json.dumps(spec,indent=2)+'\n')
    pre=folder/'b34-price-group-structure-preflight.json';assert not pre.exists();pre.write_text(json.dumps(check,indent=2)+'\n')
    print(json.dumps({'draft':out.relative_to(ROOT).as_posix(),**check}))


if __name__=='__main__':main()
