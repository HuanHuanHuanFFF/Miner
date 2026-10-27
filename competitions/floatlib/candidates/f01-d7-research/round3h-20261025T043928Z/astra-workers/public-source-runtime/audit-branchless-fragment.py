from pathlib import Path
import hashlib,json,re,ast,datetime
OUT=Path(__file__).resolve().parent;REPO=OUT.parents[6]
R15=OUT.parents[1]
C=REPO/"competitions/floatlib/candidates"
parent=C/"f01-r14-dev-mul-cache-rse2/Kernel.lean";cand=C/"f01-r15-dev-mul-branchless1/Kernel.lean"
frag=R15/"development-branchless-normal-mul1.lean";builder=R15/"development-build-branchless-normal-mul.py"
sha=lambda b:hashlib.sha256(b).hexdigest()
p=parent.read_bytes();c=cand.read_bytes();f=frag.read_bytes()
assert sha(p)=="9038f8d653f030a8812c3187733488f70995253a1a7b284759c4f58b96378c19"
assert sha(c)=="f529f4d4a693b6bee91aa10882237d30112637383cb447f3037057ff9bdb70d9" and len(c)==236154
tree=ast.parse(builder.read_text(encoding="utf-8-sig"))
needle=next(ast.literal_eval(n.value) for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(x,ast.Name) and x.id=="needle" for x in n.targets))
assert p.count(needle)==c.count(f)==1
assert p.replace(needle,f)==c and c.replace(f,needle)==p
RUN=REPO/"competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40166091242/download-28fddc7db9b44ad0af963b3257d6c11f/diagnostics/f01-d7-public-suite/public-suite"
D=RUN/"diagnostics/f01-r15-dev-mul-branchless1"
assert (RUN/"inputs/f01-r15-dev-mul-branchless1/Kernel.lean").read_bytes()==c
index=json.loads((D/"candidate-c-index.json").read_text())
records=[]
for e in index:
    b=(D/e["file"]).read_bytes()
    assert sha(b)==e["sha256"] and e["kernel_sha256"]==sha(c)
    records.append(dict(module=e["module"],file=str((D/e["file"]).relative_to(REPO)),sha256=sha(b),bytes=len(b)))
def extract(path,name):
    b=path.read_bytes();t=b.decode();m=re.search(r"^LEAN_EXPORT [^\n;]*\b"+name+r"\([^\n]*\)\{",t,re.M)
    assert m,name
    start=m.start();i=t.index("{",start)+1;depth=1
    while depth:
        if t[i]=="{":depth+=1
        elif t[i]=="}":depth-=1
        i+=1
    s=t[start:i];calls={}
    for x in re.findall(r"\b((?:lean_|lp_)\w+)\(",s):
        if x!=name:calls[x]=calls.get(x,0)+1
    return s,dict(name=name,source_line=t[:start].count("\n")+1,end_line=t[:i].count("\n")+1,
      sha256=sha(s.encode()),bytes=len(s.encode()),static_calls=calls,
      if_sites=len(re.findall(r"\bif\s*\(",s)),caveat="Generated diagnostic C only; static sites, not machine branches or runtime call counts.")
exdir=OUT/"branchless-code-excerpts";exdir.mkdir(exist_ok=True)
functions=[]
for name in ["lp_competition_Submission_R15BranchlessNormal_round","lp_competition_Submission_R15BranchlessNormal_core"]:
    s,r=extract(D/"candidate-generated-0.c",name);functions.append(r);(exdir/(name+".c")).write_text(s,encoding="utf-8")
s,r=extract(D/"candidate-generated-1.c","lp_competition_main___lam__3");functions.append(r)
ls=s.splitlines();tail=ls[-330:]
(exdir/"selected-main-mul-tail.txt").write_text("\n".join(f"{r['end_line']-len(tail)+i+1}: {x}" for i,x in enumerate(tail))+"\n",encoding="utf-8")
main=(D/"candidate-generated-1.c").read_text()
numbered=main.splitlines()
focus=[]
for lo,hi in [(65,73),(7356,7533),(8478,8576),(8585,8618)]:
    focus.append(f'/* MainFull.c lines {lo}-{hi}; exact source hash authenticated above. */')
    focus.extend(f'{i}: {numbered[i-1]}' for i in range(lo,hi+1))
(exdir/'selected-normal-path.txt').write_text('\n'.join(focus)+'\n',encoding='utf-8')
assert 'lp_competition_main___lam__3___boxed' in main and 'lp_competition_Bench_Suite_run(v___f_2922_, v___f_2923_' in main
verdict=json.loads((RUN/"f01-r15-dev-mul-branchless1-verdict.json").read_text())
assert verdict["passed"] is True and verdict["mode"]=="diagnostic-statement-only" and verdict["stage"]=="statement" and verdict["ratio"] is None and verdict["diagnostic_only"] is True
rec=dict(state="STATIC_REVIEW_AND_AUTHENTICATED_STATEMENT_ONLY",generated_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
candidate=dict(path=str(cand.relative_to(REPO)),sha256=sha(c),bytes=len(c)),
parent=dict(path=str(parent.relative_to(REPO)),sha256=sha(p),bytes=len(p),old_negative="whole1.047144/MUL1.290801 vsDF; retained original D failure, not retried under another seed"),
fragment=dict(path=str(frag.relative_to(REPO)),sha256=sha(f),bytes=len(f)),
inverse_splice_exact=True,unchanged_outside_exported_mul_splice=True,
statement=dict(run=40166091242,source_commit="256245a60f56e7aa87506297275b550c11df59d6",verdict_path=str((RUN/"f01-r15-dev-mul-branchless1-verdict.json").relative_to(REPO)),
    verdict_sha256=sha((RUN/"f01-r15-dev-mul-branchless1-verdict.json").read_bytes()),passed=True,seconds=verdict["seconds"],full_gate="NOT_ESTABLISHED_BY_THIS_RECEIPT",performance="NOT_RUN"),
generated_C=records,functions=functions,
selected_entry=dict(condition="BENCH_PLAN environment present",path="_lean_main -> closed__5 -> main___lam__3___boxed -> main___lam__3 -> inlined MUL",evidence_lines=[71,8611,8614],scope="Diagnostic benchFull generation, not a timed run"),
unknown=["Same-SHA9038 actual timed scalar C/ELF unavailable","New selected scalar machine branch shape; attached native asm only Packed10Index","Net whole/per-kernel performance","Full gate and axiom/checksum acceptance of f529"],
model_evidence="branchless-finite-model.json",no_candidate_or_CI_or_compile_performed=True)
(OUT/"branchless-review-evidence.json").write_text(json.dumps(rec,ensure_ascii=False,indent=2)+"\n",encoding="utf-8")
print(json.dumps(dict(state=rec["state"],inverse_splice=True,statement_pass=True,candidate_sha=sha(c),
 functions=[dict(name=x["name"],lines=[x["source_line"],x["end_line"]],if_sites=x["if_sites"],u64_multiply_static_sites=x["static_calls"].get("lean_uint64_mul",0)) for x in functions]),indent=2))

