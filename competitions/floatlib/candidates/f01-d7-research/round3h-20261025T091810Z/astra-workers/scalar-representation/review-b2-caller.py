"""Read-only extraction of the exact B2 diagnostic MainFull selected public-suite caller."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
DIR=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168024176/download-97e5567f5b7c4fc2a261a6d6dac40edc/diagnostics/f01-d7-public-suite/public-suite'
diag=DIR/'diagnostics/f01-r15-dev-packed-b2-1'
input=DIR/'inputs/f01-r15-dev-packed-b2-1/Kernel.lean'
expected='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert hashlib.sha256(input.read_bytes()).hexdigest()==expected
index=json.loads((diag/'candidate-c-index.json').read_bytes())
sources={}
for row in index:
    p=diag/row['file']; data=p.read_bytes()
    assert hashlib.sha256(data).hexdigest()==row['sha256']
    assert row['kernel_sha256']==expected
    sources[row['module']]=(p,data.decode())

def body(src,symbol):
    m=re.search(r'^LEAN_EXPORT[^\n]*\b'+re.escape(symbol)+r'\([^;\n]*\)\{',src,re.M)
    assert m,symbol
    opening=src.index('{',m.start()); depth=1; end=opening+1
    while depth:
        depth+=(src[end]=='{')-(src[end]=='}'); end+=1
    return src[m.start():end]+'\n',src.count('\n',0,m.start())+1

selected='lp_competition_main___lam__3'
src=sources['MainFull'][1]
main,mainline=body(src,'_lean_main')
assert 'lp_competition_Bench_Suite_run(v___f_1220_, v___f_1221_' in main
assert 'v___f_1221_ = ((lean_object*)(lp_competition_main___closed__5))' in main
assert re.search(r'closed__5_value[^\n]*\.m_fun = \(void\*\)'+selected+r'___boxed',src)
rows=[]
for module,symbol in [('MainFull',selected),('Submission','lp_competition_Submission_mul'),('Submission','lp_competition_Submission_nativeMul')]:
    p,s=sources[module]; b,line=body(s,symbol)
    path=HERE/(symbol+'.b2.c'); path.write_bytes(b.encode())
    rows.append({'module':module,'symbol':symbol,'original_line':line,'body_bytes':len(b.encode()),
      'body_sha256':hashlib.sha256(b.encode()).hexdigest(),
      'static_sites':{name:len(re.findall(r'\b'+name+r'\(',b)) for name in
       ['lean_uint32_to_float32','lean_float32_mul','lean_array_fget_borrowed','lean_float32_of_bits','lean_float32_beq','lean_float32_to_bits','lean_alloc_ctor','lean_apply_2']}})
(HERE/'b2-selected-main.c').write_bytes(main.encode())
report={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'EXACT_B2_DIAGNOSTIC_C_REVIEW',
 'kernel_sha256':expected,'run':40168024176,
 'input_path':str(input.relative_to(ROOT)),
 'source_files':[{'path':str(p.relative_to(ROOT)),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p,s in sources.values()],
 'selection':{'environment':'BENCH_PLAN present -> Bench.Suite.run','closure':'closed__5','symbol':selected,'main_original_line':mainline},
 'functions':rows,
 'limits':'C sites are not dynamic cycles. The public-suite closure is selected in this diagnostic MainFull; timed ELF identity is not established. Normal arm inspection identifies 2 casts/2 table reads/3 multiplies; fallback legitimately contains software arithmetic and other paths.'}
(HERE/'b2-caller-review.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report['functions'],indent=2))
