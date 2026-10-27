"""Bind original diagnostic C to the retained source and selected MainFull paths."""
from pathlib import Path
from collections import Counter
import hashlib, json, re, datetime
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
sha=lambda b:hashlib.sha256(b).hexdigest()
rel='competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168024176/download-97e5567f5b7c4fc2a261a6d6dac40edc/diagnostics/f01-d7-public-suite/public-suite'
diag=ROOT/rel/'diagnostics/f01-r15-dev-packed-b2-1'
base=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
original=ROOT/rel/'inputs/f01-r15-dev-packed-b2-1/Kernel.lean'
expected='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(base.read_bytes())==sha(original.read_bytes())==expected
index=json.loads((diag/'candidate-c-index.json').read_text())
sources={}
identities=[]
for row in index:
    p=diag/row['file']; data=p.read_bytes()
    assert sha(data)==row['sha256'] and row['kernel_sha256']==expected
    sources[row['module']]=data.decode()
    identities.append({'path':str(p),'sha256':sha(data),'bytes':len(data),'module':row['module'],'scope':row['scope']})
def body(module,symbol):
    txt=sources[module]
    m=re.search(r'^LEAN_EXPORT [^\n]+\b'+re.escape(symbol)+r'\([^\n]*\)\{',txt,re.M)
    assert m,symbol
    end=m.end(); depth=1
    while depth:
        if txt[end]=='{':depth+=1
        elif txt[end]=='}':depth-=1
        end+=1
    b=txt[m.start():end]
    return b,txt.count('\n',0,m.start())+1
main,_=body('MainFull','_lean_main')
assert 'v___f_1220_ = ((lean_object*)(lp_competition_main___closed__1));' in main
assert 'v___f_1221_ = ((lean_object*)(lp_competition_main___closed__5));' in main
assert 'lp_competition_Bench_Suite_run(v___f_1220_, v___f_1221_' in main
selected={'add':'lp_competition_main___lam__0','mul':'lp_competition_main___lam__3','sum':'lp_competition_Submission_sum','bmm':'lp_competition_Submission_bmm'}
symbols=[('MainFull',v) for k,v in selected.items() if k in ('add','mul')]+[
 ('MainFull','_lean_main'),('Submission',selected['sum']),('Submission',selected['bmm']),
 ('Submission','lp_competition_Submission_R7SinglePassSum_loop'),
 ('Submission','lp_competition_Submission_R7SinglePassSum_loop___redArg'),
 ('Submission','lp_competition_Submission_R15PackedB2_loop'),
 ('Submission','lp_competition_Submission_R15PackedB2_output'),
 ('Submission','lp_competition_Submission_R15PackedB2_packB___lam__0')]
outdir=HERE/'code-excerpts';outdir.mkdir(exist_ok=True)
functions=[]
for module,symbol in symbols:
    b,line=body(module,symbol)
    p=outdir/(symbol+'.c');p.write_text(b+'\n',encoding='utf-8',newline='\n')
    funcs=Counter(re.findall(r'\b(lean_[A-Za-z0-9_]+)\(',b))
    functions.append({'module':module,'symbol':symbol,'line':line,'bytes':len(b.encode()),'sha256':sha(b.encode()),'static_primitive_sites':dict(funcs),'excerpt':str(p)})
result={'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'state':'VERIFIED_STATIC_PATH_ONLY','candidate_sha256':expected,'run':40168024176,
 'sources':identities,'selected_public_suite_callbacks':selected,
 'selection_note':'BENCH_PLAN present branch passes closure1(add lambda0), closure5(mul lambda3), closure3(sum boxed), closure4(bmm). Default legacy mul lambda1 is not the selected suite callback.',
 'functions':functions,
 'findings':[
  'B2 loop has native float accumulators, borrowed A/B reads, no per-k Float32 allocation; terminal F2 allocation only.',
  'B2 loop retains two Nat additions, A size/default branch, loop Nat compare, and external float32_of_bits; preparation remains outside row fold.',
  'Scalar selected wrappers return UInt32; pinned 64-bit lean_box_uint32 is tagged immediate, not allocation.',
  'Selected ADD/MUL inline table decoder and fastOK short-circuit structure into MainFull; actual compiled branch layout UNKNOWN.',
  'SUM already has USize loop and manual classification; proposed fastOK rewrite does not replace that manual classifier.'
 ],
 'scope':'Successful original statement/bench-build diagnostic C; not cleaned timed gate object; static sites are not dynamic counts or measured time.',
 'new_candidate':'Kernel-eager-classifier.lean; separate exact manifest; Lean/codegen/timing NOT_RUN'}
(HERE/'runtime-audit.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'bound_sources':len(identities),'extracted_functions':len(functions),'selected':selected}))
