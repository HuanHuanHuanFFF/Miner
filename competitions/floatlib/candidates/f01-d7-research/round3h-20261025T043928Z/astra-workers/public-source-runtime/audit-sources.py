from pathlib import Path
import json, hashlib, re, datetime
ROOT=Path(__file__).resolve().parent
REPO=ROOT.parents[6]
SOURCES={
"official-main.json":("https://api.github.com/repos/conjectures-io/conjectures-optimisation-float-kernels/commits/main",None,"Conjectures.io","metadata"),
"validator-main.json":("https://api.github.com/repos/conjectures-io/conjectures-validator/commits/main",None,"Conjectures.io","metadata"),
"official-manifest.json":("https://raw.githubusercontent.com/conjectures-io/conjectures-optimisation-float-kernels/4b7e83841cc0c32c6529f533923c73d33b5ecf97/lean/lake-manifest.json","9c2792ba5869fc4c363434ac9fb0318d8a490609","Conjectures.io","MIT"),
"validator-router.txt":("https://raw.githubusercontent.com/conjectures-io/conjectures-validator/38533e8620a9da0cd66568d79b82e0041eef55e0/submission_api/routers/floatlib.py",None,"Conjectures.io","not copied into a candidate; repo license not independently re-fetched"),
"official-license.txt":("https://raw.githubusercontent.com/conjectures-io/conjectures-optimisation-float-kernels/4b7e83841cc0c32c6529f533923c73d33b5ecf97/LICENSE","4cbbea334cfa64cfbd92fddbad7b4c5bfa29c883","Conjectures.io","MIT"),
"official-branches.json":("https://api.github.com/repos/conjectures-io/conjectures-optimisation-float-kernels/branches?per_page=100",None,"Conjectures.io","metadata"),
"lean-object.txt":("https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp","49213d7be079e11589f1efcfe880dba44622a6e7","Leonardo de Moura; Microsoft Corporation; original headers retained","Apache-2.0"),
"lean-header.txt":("https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/include/lean/lean.h",None,"Leonardo de Moura; Microsoft Corporation; original headers retained","Apache-2.0"),
"lean-license.txt":("https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/LICENSE",None,"Lean contributors","Apache-2.0"),
"floatlib-license.txt":("https://raw.githubusercontent.com/lean-dojo/FloatLib/0d91825727839f597fd06b22fdd038ea21480f0c/LICENSE","e58f952dfd0b19ccef5061920b3af3d76a111f3f","FloatLib","MIT"),
"floatlib-dispatch-mul.txt":("https://raw.githubusercontent.com/lean-dojo/FloatLib/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Dispatch/Mul/Runtime.lean",None,"FloatLib Team","MIT"),
"official-incumbent.txt":("https://raw.githubusercontent.com/conjectures-io/conjectures-optimisation-float-kernels/4b7e83841cc0c32c6529f533923c73d33b5ecf97/kernels/full/incumbent/Kernel.lean","c37f21e407bc6b76a55654d11f7354506d7f7fe6","Conjectures.io","MIT"),
}
def digest(b): return hashlib.sha256(b).hexdigest()
def blob(b): return hashlib.sha1(b"blob "+str(len(b)).encode()+b"\0"+b).hexdigest()
source_rows=[]
body_lengths=json.loads((ROOT/'connector-body-lengths.json').read_text())
for name,(url,expected,author,license_) in SOURCES.items():
    f=ROOT/"sources"/name
    b=f.read_bytes()
    remote_length=body_lengths[name.rsplit('.',1)[0]]["utf8_bytes"]
    if len(b)==remote_length+1 and b.endswith(b'\n'):
        b=b[:-1];f.write_bytes(b)
    assert len(b)==remote_length,(name,len(b),remote_length)
    # apply_patch represents each final newline as an added line. Correct only
    # this known transport newline when the GitHub blob identity proves it.
    corrected=False
    if expected and blob(b)!=expected and b.endswith(b"\n") and blob(b[:-1])==expected:
        b=b[:-1];f.write_bytes(b);corrected=True
    source_rows.append(dict(file=str(f.relative_to(ROOT)),url=url,bytes=len(b),sha256=digest(b),
        git_blob_sha1=blob(b),expected_git_blob_sha1=expected,
        blob_verified=blob(b)==expected if expected else "NOT_CHECKED",
        connector_utf8_bytes=remote_length,transport_normalization='Removed apply_patch extra final newline when present; saved source bytes have connector-reported UTF-8 length',author=author,license=license_,
        retrieval="GitHub connector UTF-8 body; HTTP status not exposed"))
df=REPO/"competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean"
assert digest(df.read_bytes())=="df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172"
base=REPO/"competitions/floatlib/references/official-incumbent/Kernel.lean"
source_rows[-1]["equals_local_reference_bytes"]=base.read_bytes()==(ROOT/"sources/official-incumbent.txt").read_bytes()
cp=REPO/"competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40092014611/download-40d1f19ff0684c7d95f29a632be22848/diagnostics/f01-d13-cost-profile/cost-profile"
inputdf=cp/"inputs/f01-d12-scalar-combined/Kernel.lean"
assert inputdf.read_bytes()==df.read_bytes()
cpath=cp/"measurement/profile-r13-original-Submission.c"
cbytes=cpath.read_bytes(); c=cbytes.decode()
names=["lp_competition_R2W01b_convert","lp_competition_Submission_add","lp_competition_Submission_nativeMul","lp_competition_Submission_mul"]
functions=[]
excerpts=[]
for name in names:
    m=re.search(r"^LEAN_EXPORT [^\n;]*\b"+name+r"\([^\n]*\)\{",c,re.M)
    assert m,name
    start=m.start();level=1;end=c.index("{",start)+1
    while level:
        if c[end]=="{":level+=1
        elif c[end]=="}":level-=1
        end+=1
    text=c[start:end]
    first=c[:start].count("\n")+1;last=c[:end].count("\n")+1
    calls={}
    for fn in re.findall(r"\b((?:lean_|lp_)\w+)\(",text):
        if fn!=name:calls[fn]=calls.get(fn,0)+1
    funcs=dict(name=name,signature=text.splitlines()[0],first_line=first,last_line=last,
      source_bytes=len(text.encode()),sha256=digest(text.encode()),
      calls_static_sites=calls,
      contains_lean_apply=any(k.startswith("lean_apply") for k in calls),
      contains_explicit_alloc=any(k.startswith("lean_alloc") for k in calls),
      caveat="Static generated-C sites only. Transitive callees and machine optimization/dynamic counts not inferred.")
    functions.append(funcs)
    out=ROOT/"code-excerpts"/(name+".c")
    out.parent.mkdir(exist_ok=True)
    out.write_bytes(text.encode())
report=dict(state="VERIFIED_SOURCE_AND_GENERATED_C_ONLY",generated_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
    candidate_sha256=digest(df.read_bytes()),candidate_bytes=len(df.read_bytes()),
    original_C=dict(path=str(cpath.relative_to(REPO)),bytes=len(cbytes),sha256=digest(cbytes),
       run=40092014611,input_sha256=digest(inputdf.read_bytes()),
       note="R13 retained exact-DF original Submission.c before diagnostic instrumentation; not certified selected timed MainFull ELF."),
    sources=source_rows,functions=functions,
    failures=[dict(url="https://raw.githubusercontent.com/leanprover/lean4/v4.34.0/src/runtime/float.cpp",result="connector404; correct existing implementation located in object.cpp; no retry loop")],
    performance="NOT_RUN",lean="NOT_RUN",ci="NOT_DISPATCHED")
(ROOT/"source-index.json").write_text(json.dumps(report,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps(dict(state=report["state"],sources=len(source_rows),byte_identity=source_rows[-1]["equals_local_reference_bytes"],
    failed_blob_checks=[x["file"] for x in source_rows if x["blob_verified"] is False],
    functions=[{k:f[k] for k in ["name","first_line","last_line","contains_lean_apply","contains_explicit_alloc"]} for f in functions]),ensure_ascii=False,indent=2))

