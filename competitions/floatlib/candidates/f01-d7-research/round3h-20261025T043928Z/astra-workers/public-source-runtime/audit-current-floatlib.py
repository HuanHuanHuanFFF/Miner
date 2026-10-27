from pathlib import Path
import hashlib,json,re,datetime
root=Path(__file__).resolve().parent
rows=json.loads((root/"extra-connector-bodies.json").read_text())
selection=json.loads((root/"current-floatlib-tree-selection.json").read_text())
blobs={}
for x in selection["selected"]:
    for era in ["old","new"]:
        if x.get(era):blobs[(era,x["path"])]=x[era]["sha"]
keymap={"fl-new-toolchain":("new","lean-toolchain"),"fl-old-mul":("old","FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Multiplication/Runtime.lean"),"fl-new-mul":("new","FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Multiplication/Runtime.lean"),"fl-new-modelbridge":("new","FloatLib/Floats/ExecFloat/Backends/Word/Narrow/ModelBridge.lean"),"fl-old-native":("old","FloatLib/Floats/Formats/IEEE754/Native/Representation.lean"),"fl-new-native":("new","FloatLib/Floats/Formats/IEEE754/Native/Representation.lean")}
for x in rows:
    p=root/"sources"/(x["name"]+".txt");b=p.read_bytes()
    if len(b)==x["utf8_bytes"]+1 and b.endswith(b"\n"):
        b=b[:-1];p.write_bytes(b)
    assert len(b)==x["utf8_bytes"]
    x.update(file=str(p.relative_to(root)),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),
        git_blob_sha1=hashlib.sha1(b"blob "+str(len(b)).encode()+b"\0"+b).hexdigest(),
        http_status="NOT_EXPOSED_BY_CONNECTOR")
    if x["name"] in keymap:
        x["expected_git_blob_sha1"]=blobs[keymap[x["name"]]]
        assert x["expected_git_blob_sha1"]==x["git_blob_sha1"]
def body(n,name):
    t=(root/"sources"/(n+".txt")).read_text()
    b=t[t.index("@[inline] def "+name):t.rindex("\nend ")]
    return b.replace(name,"mulFiniteEquivalent?")
a=body("fl-old-mul","mulFiniteImpl?")
b=body("fl-new-mul","mulFiniteWord?")
assert a==b
rec=dict(state="VERIFIED_SELECTED_SOURCE_COMPARISON_NO_NEW_BINARY32_MUL_MECHANISM",
 queried_window_utc=["2026-10-25T05:00:15Z","2026-10-25T05:02:15Z"],
 sources=rows,main=selection["public_main"],toolchain=(root/"sources/fl-new-toolchain.txt").read_text().strip(),
 findings={"mulFiniteImpl_to_mulFiniteWord":"Selected exact finite multiplication runtime body byte-identical after the declaration name is normalized; comments outside body changed.",
 "native_representation":"Current Representation keeps same-width model/native roundtrips; no native Float-to-Float32 RNE theorem in this checked file.",
 "model_bridge":"New file contains word-to-dyadic/model bridge lemmas, no Float32 native operation or native Float.toFloat32 narrowing.",
 "fixed_environment":"No dependency update permissible or performed; any actual theorem backport would need own4.34 import and axiom audit."},
 counts={"all_tree_changed_or_added_blob_files":1068,"warning":"Tree diff count is discovery metadata, not a reviewed1068-file source corpus."},
 result="No low-cost new runtime source justified for CI from these selected differences.")
(root/"current-floatlib-comparison.json").write_text(json.dumps(rec,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps({"state":rec["state"],"main":rec["main"],"toolchain":rec["toolchain"],"selected_runtime_body_identical":a==b,"sources":len(rows)},indent=2))

