"""Execute only exact pinned static intake/policy functions on local sources.

Original functions/constants are selected unchanged by AST, to avoid importing
Linux build/process plumbing. No Lean/native/full gate is run or implied.
"""
from __future__ import annotations
import ast
from datetime import datetime,timezone
import hashlib,json,re
from pathlib import Path

ROOT=Path(__file__).resolve().parent
PINS={"official-sandbox.py":"13c4f7b71e678a27d024613e5198e0d75667de4e",
      "official-duplicates.py":"3e8eb21d1a50cce44090e29a816e3b55c0ad3fd9"}


def selected(path,names):
    raw=path.read_bytes()
    blob=hashlib.sha1(b'blob '+str(len(raw)).encode()+b'\0'+raw).hexdigest()
    assert blob==PINS[path.name],(path,blob)
    tree=ast.parse(raw.decode())
    keep=[];found=set()
    for node in tree.body:
        node_names=[]
        if isinstance(node,(ast.FunctionDef,ast.AsyncFunctionDef)):node_names=[node.name]
        elif isinstance(node,ast.Assign):node_names=[n.id for n in node.targets if isinstance(n,ast.Name)]
        if set(node_names)&names:keep.append(node);found.update(set(node_names)&names)
    assert found==names,(names-found)
    return keep,{'file':path.name,'git_blob_sha':blob,'sha256':hashlib.sha256(raw).hexdigest()}


def main():
    d,dp=selected(ROOT/'private/official-duplicates.py',{'_CODE','_COMMENT','normalized'})
    s,sp=selected(ROOT/'private/official-sandbox.py',{'_MAX_BYTES','ATTRIBUTES','BANNED','OPTIONS','GLOBAL',
        'intake','policy','options','global_declarations'})
    future=ast.parse('from __future__ import annotations').body
    namespace={'re':re,'Path':Path}
    module=ast.fix_missing_locations(ast.Module(body=future+d+s,type_ignores=[]))
    exec(compile(module,'<unchanged-pinned-static-functions>','exec'),namespace)
    paths=['private/norm-guard26-v2/Kernel.lean','private/pruned27-control/Kernel.lean',
           'private/packed-native-v1/Kernel.lean','private/winograd-native-v1/Kernel.lean',
           'PackedLinearRuntime.lean','PackedCoefficientProof.lean','CheckedCarry128.lean','NormMomentRuntime.lean']
    results=[]
    for name in paths:
        p=ROOT/name;raw=p.read_bytes()
        item={'path':name,'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),
              'intake_error':namespace['intake'](p,None),'policy_error':namespace['policy'](p,None)}
        assert p.read_bytes()==raw
        results.append(item)
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'scope':'EXACT_PINNED_STATIC_FUNCTIONS_ONLY_NO_LEAN_OR_FULL_GATE',
         'method':'Unchanged AST-selected pure functions/constants; Linux build/process imports not executed',
         'original_sources':[sp,dp],'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
         'results':results,'all_passed':all(r['intake_error']is None and r['policy_error']is None for r in results)}
    p=ROOT/'static-policy-preflight.json';p.write_text(json.dumps(out,indent=2),encoding='utf-8')
    print(json.dumps(out))


if __name__=='__main__':main()
