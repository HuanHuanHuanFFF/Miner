"""Bounded namespace/selected-runtime-map audit of the uncompiled bundle."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, re, time
OUT = Path(__file__).resolve().parent
ROOT = next(p for p in OUT.parents if (p / "competitions/floatlib/pins.json").is_file())
start = time.monotonic(); sha = lambda b: hashlib.sha256(b).hexdigest()
bundle = (OUT / "Panel4-reusable-bundle.lean").read_bytes(); text = bundle.decode()
meta = json.loads((OUT / "panel-assets-and-capacity.json").read_bytes())
assert sha(bundle) == meta["bundle_sha256"]
parent = (ROOT / "competitions/floatlib/candidates/f01-r15-dev-matrix-only1/Kernel.lean").read_text(encoding="utf-8")
names = []; stack = []; namespaces = set()
for line in text.splitlines():
    ns = re.match(r"^namespace ([A-Za-z0-9_.]+)\s*$", line)
    en = re.match(r"^end ([A-Za-z0-9_.]+)\s*$", line)
    decl = re.match(r"^(?:@\[[^\n]+\]\s*)?(?:def|theorem|abbrev|structure) ([A-Za-z0-9_]+)\b",line)
    if ns:
        assert not stack, "Bundle uses fully-qualified nonnested namespaces"
        stack.append(ns.group(1)); namespaces.add(ns.group(1))
    elif en:
        assert stack and stack.pop() == en.group(1)
    elif decl:
        assert stack
        names.append(stack[-1]+"."+decl.group(1))
assert not stack and len(names) == len(set(names))
assert all("namespace "+ns not in parent for ns in namespaces)

# Inspect only the actual new entry's executable definitions. The old generic
# output helper intentionally retains its global A.map but is proof-only here.
entry = (OUT / "Panel4-entry-bridge.lean").read_text(encoding="utf-8")
runtime = []
for m in re.finditer(r"(?m)^(?:@\[[^\n]+\]\s*)?def ([A-Za-z0-9_]+)\b",entry):
    tail = entry[m.end():]
    following = re.search(r"(?m)^(?:@\[[^\n]+\]\s*)?(?:def |theorem |end )",tail)
    block = entry[m.start():m.end()+following.start()]
    assert ".map ExecFloat.Binary.toFloat32" not in block
    runtime.append({"name":"Submission.R15PanelEntry."+m.group(1),"source_sha256":sha(block.encode()),
                    "contains_global_A_map_text":False})
assert [r["name"].split(".")[-1] for r in runtime] == ["buildTiles","writeBatch","output","core"]
receipt = {"at_utc":datetime.now(timezone.utc).isoformat(),"status":"BOUNDED_TEXTUAL_CLOSURE_CHECK_PASS",
           "bundle_sha256":sha(bundle),"declaration_count":len(names),"duplicate_declarations":[],
           "new_namespaces":sorted(namespaces),"namespace_collisions_with_ec82":[],
           "new_entry_runtime":runtime,
           "runtime_call_route":["R15PanelEntry.core -> output -> packedB once + batch fold",
                                  "writeBatch -> complete block fold(buildTiles -> Panel4.block -> local packA once perblock) + Panel4Tail.tail",
                                  "complete block emitter -> existing inline emitBlock/emitRow -> original Packed10.finish",
                                  "tail -> local0..3row prepare -> shifted numeric dot -> original global raw finish base"],
           "remaining":"Text audit is not Lean name resolution, proof acceptance, compiler liveness, allocation/lifetime observation or performance.",
           "elapsed_seconds":time.monotonic()-start}
assert receipt["elapsed_seconds"]<5
(OUT / "panel-closure-check.json").write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps({"status":receipt["status"],"declarations":len(names),"new_runtime_definitions":len(runtime),"elapsed_seconds":receipt["elapsed_seconds"]}))
