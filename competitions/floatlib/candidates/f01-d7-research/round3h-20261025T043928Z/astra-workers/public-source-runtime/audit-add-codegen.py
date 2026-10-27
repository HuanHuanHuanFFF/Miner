from pathlib import Path
import hashlib,json,re,datetime,difflib
OUT=Path(__file__).resolve().parent;REPO=OUT.parents[6];R15=OUT.parents[1]
names=["f01-r15-dev-column-pairs2","f01-r15-dev-mul-branchless1"]
keys=["b116","f529"]
sha=lambda b:hashlib.sha256(b).hexdigest()
diag=REPO/"competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40166091242/download-28fddc7db9b44ad0af963b3257d6c11f/diagnostics/f01-d7-public-suite/public-suite"
timed=REPO/"competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40166656717/download-dfd0ddefe1e14ba38fac6acbfc673912/diagnostics/f01-d7-public-suite/public-suite"
art=OUT/"add-codegen-excerpts";art.mkdir(exist_ok=True)
kernels=[];runners=[];texts=[]
for key,n in zip(keys,names):
    b=(REPO/"competitions/floatlib/candidates"/n/"Kernel.lean").read_bytes()
    res=json.loads((R15/f"result-1526005-{n}-vs-f01-d12-scalar-combined.json").read_text())
    assert sha(b)==res["sha256"] and res["codegen_present"] is False
    assert (diag/"inputs"/n/"Kernel.lean").read_bytes()==b
    assert (timed/"inputs"/n/"Kernel.lean").read_bytes()==b
    idx=json.loads((diag/"diagnostics"/n/"candidate-c-index.json").read_text())
    cc={}
    for e in idx:
        p=diag/"diagnostics"/n/e["file"];cb=p.read_bytes()
        assert sha(cb)==e["sha256"] and e["kernel_sha256"]==sha(b)
        cc[e["module"]]=(p,cb.decode())
    texts.append(cc);kernels.append(b)
    runners.append(dict(key=key,name=n,kernel_sha256=sha(b),kernel_bytes=len(b),timed_run=40166656717,
       diagnostic_run=40166091242,codegen_present_in_timed_run=False,
       c_files=[dict(module=mod,path=str(p.relative_to(REPO)),sha256=sha(t.encode()),bytes=len(t.encode())) for mod,(p,t) in cc.items()],
       result_sha256=sha((R15/f"result-1526005-{n}-vs-f01-d12-scalar-combined.json").read_bytes()),
       whole=res["relative_normalized_ratio"],add=res["per_operation_normalized"]["add"],first_D_decision="FAILED_PRESERVED"))
def extract(t,name):
    m=re.search(r"^(?:LEAN_EXPORT|static) [^\n;]*\b"+re.escape(name)+r"\([^\n]*\)\{",t,re.M)
    assert m,name
    a=m.start();i=t.index("{",a)+1;depth=1
    while depth:
        if t[i]=="{":depth+=1
        elif t[i]=="}":depth-=1
        i+=1
    return t[a:i],t[:a].count("\n")+1,t[:i].count("\n")+1
def alpha(t):
    # Only generated local SSA names and join labels are renamed. No numeric
    # constants, global/callee symbols, operators, control order or types change.
    mapping={}
    def sub(m):
        x=m.group()
        if x not in mapping:mapping[x]="local_"+str(len(mapping))
        return mapping[x]
    return re.sub(r"\s+"," ",re.sub(r"\bv_[A-Za-z0-9_]+\b",sub,t)).strip()
funcs=[
("MainFull","_lean_main"),
("MainFull","lp_competition_main___lam__0"),
("MainFull","lp_competition_main___lam__0___boxed"),
("Submission","lp_competition_Submission_add"),
("Submission","lp_competition_Submission_ScalarNaN_add"),
("Submission","lp_competition_Submission_DWordNaN_rawChoose"),
("Submission","lp_competition_R2W01b_convert"),
("Submission","lp_competition_R2W01b_tableProduct"),
("Submission","lp_competition_R2W01b_scaleAt"),
("Submission","lp_competition_R2W01b_scaleTable___lam__0"),
("Submission","_init_lp_competition_R2W01b_scaleTable___closed__1"),
("Submission","_init_lp_competition_R2W01b_scaleTable"),
("Submission","lp_competition_R7W04_nonNaN")]
results=[]
for mod,name in funcs:
    bodies=[];rec=dict(module=mod,symbol=name,versions={})
    for key,tt in zip(keys,texts):
        body,lo,hi=extract(tt[mod][1],name);bodies.append(body)
        rec["versions"][key]=dict(first_line=lo,last_line=hi,bytes=len(body.encode()),sha256=sha(body.encode()),alpha_sha256=sha(alpha(body).encode()))
        if name in ["lp_competition_main___lam__0","lp_competition_Submission_add","lp_competition_main___lam__0___boxed","_lean_main"]:
            (art/f"{key}-{name}.c").write_text(body,encoding="utf-8")
            (art/f"{key}-{name}.alpha.c").write_text(alpha(body)+"\n",encoding="utf-8")
    rec.update(raw_equal=bodies[0]==bodies[1],alpha_equal=alpha(bodies[0])==alpha(bodies[1]))
    if not rec['raw_equal']:
        (art/(name+'.raw.diff')).write_text('\n'.join(difflib.unified_diff(bodies[0].splitlines(),bodies[1].splitlines(),fromfile='b116',tofile='f529'))+'\n',encoding='utf-8')
    if not rec["alpha_equal"]:
        (art/(name+".diff")).write_text("\n".join(difflib.unified_diff(alpha(bodies[0]).split(),alpha(bodies[1]).split(),fromfile="b116",tofile="f529"))+"\n",encoding="utf-8")
    results.append(rec)
a,b=kernels
diff=next((i for i,(x,y) in enumerate(zip(a,b)) if x!=y),min(len(a),len(b)))
ends=[]
for v in kernels:
    st=v.index(b"@[inline] def add (x y : Binary32)",v.index(b"end ScalarNaN"))
    en=v.index(b"@[inline] def nativeMul",st)
    ends.append((st,en))
assert ends[0]==ends[1]
st,en=ends[0]
source=dict(first_different_byte_offset0=diff,first_different_line=a[:diff].count(b"\n")+1,
 common_prefix_sha256=sha(a[:diff]),common_prefix_bytes=diff,
 prefix_through_public_add_equal=a[:en]==b[:en],prefix_through_public_add_bytes=en,prefix_sha256=sha(a[:en]),
 public_add_and_spec=dict(first_line=a[:st].count(b"\n")+1,last_line=a[:en].count(b"\n"),bytes=en-st,sha256=sha(a[st:en]),exact_equal=a[st:en]==b[st:en]),
 coverage="Entire byte-identical prefix includes R7W04, R2W01b table/decoder, rawChoose, ScalarNaN.add, all pre-export helper definitions/proofs, public add/spec; imported ContractTensor unchanged.")
entries=[]
for key,tt in zip(keys,texts):
    t=tt["MainFull"][1];ls=t.splitlines()
    lines=[(i+1,l) for i,l in enumerate(ls) if "main___closed__1" in l or "Bench_Suite_run(" in l or "main___lam__0" in l]
    entries.append(dict(key=key,lines=lines,selected="BENCH_PLAN-present _lean_main passes closed__1 as first argument to Bench.Suite.run; closed__1 points to main___lam__0___boxed, which calls unboxed main___lam__0"))
    (art/f"{key}-add-caller-lines.txt").write_text("\n".join(f"{i}: {l}" for i,l in lines)+"\n",encoding="utf-8")
closure_lines=[]
for tt in texts:
    closure_lines.append([l for l in tt['MainFull'][1].splitlines() if 'static const lean_closure_object lp_competition_main___closed__1_value' in l])
assert all(len(x)==1 for x in closure_lines)
ratio=runners[0]["add"]/runners[1]["add"]
report=dict(state="VERIFIED_IDENTICAL_ADD_SOURCE_AND_DIAGNOSTIC_C",at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
 versions=runners,source=source,functions=results,caller=entries,add_closure_declaration_exact_equal=closure_lines[0]==closure_lines[1],
 normalized_add_ratio_b116_over_f529=ratio,
 normalization="Rename only v_* local SSA/register/join labels by first occurrence, then whitespace collapse; preserve all symbols/constants/operators/types/control order.",
 scope="Code belongs to prior same-kernel statement diagnostic40166091242. Timed40166656717 codegen missing. No machine equivalence or cause-of-time-variation claim.",
 exclusions=["No changed public add/helper source before nativeMul","No difference in inspected selected add body after bounded alpha normalization"],
 unknown=["Timed binary ADD instructions/alignment/layout","Constant-table runtime address/cache placement despite identical construction C","Whole-module clang inlining/link/context and benchmark caller machine code","CPU/scheduling/frequency/cache cause of7% timing spread"],
 policy="Both failed first D outcomes remain; do not discard slow sample, reseed, or rerun on this evidence.")
(OUT/"add-codegen-comparison.json").write_text(json.dumps(report,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps(dict(state=report["state"],source=source,ratio=ratio,comparisons=[dict(symbol=x["symbol"],raw_equal=x["raw_equal"],alpha_equal=x["alpha_equal"],hashes=x["versions"]) for x in results]),ensure_ascii=False,indent=2))

