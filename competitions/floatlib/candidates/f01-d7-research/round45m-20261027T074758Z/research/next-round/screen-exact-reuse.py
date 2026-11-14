"""Bounded, already-seen source-model screen for exact row/column equivalence.
No associativity, hardware timing, future inputs, or candidate changes.
"""
from pathlib import Path
import datetime, hashlib, json, time, types
HERE=Path(__file__).resolve().parent
ROOT=Path(__file__).resolve().parents[7]
MODEL=ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-public-input-domain.py'
GEN=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/BenchSuite.lean'
PLAN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168687803/download-13caf4644cf1467e8717d9474d417b8a/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
code=MODEL.read_text(encoding='utf-8')
old="GEN = HERE / 'astra-official-source/lean/bench/BenchSuite.lean'"
assert code.count(old)==1
module=types.ModuleType('exact_reuse_seen_model'); module.__file__=str(MODEL)
exec(compile(code.replace(old,'GEN = ROOT / '+repr(GEN.relative_to(ROOT).as_posix())),str(MODEL),'exec'),module.__dict__)
start=time.monotonic(); reads=0; rows=[]; trace=hashlib.sha256()
def elem(c,i,role,width):
    global reads
    assert reads<1_000_000 and time.monotonic()-start<8
    word=module.element(c,i,role,width); reads+=1; trace.update(word.to_bytes(4,'little'))
    return word
for c in json.loads(PLAN.read_bytes())['cases']:
    if c['kernel']!='bmm' or not c['timed']: continue
    n,m,p=c['n'],c['m'],c['p']; samples=min(3,c['batch'])
    # Preserve complete rows/columns for exact equality; sample at most64 of each.
    ridx=sorted({j*m//min(64,m) for j in range(min(64,m))})
    cidx=sorted({j*p//min(64,p) for j in range(min(64,p))})
    estimated=samples*n*(len(ridx)+len(cidx))
    if reads+estimated>1_000_000:
        rows.append({'case':c['name'],'state':'SKIPPED_BOUNDED_READ_BUDGET','estimated_raw_reads':estimated}); continue
    for j in range(samples):
        bi=j*c['batch']//samples
        ar=[tuple(elem(c,(bi*m+r)*n+k,0,n) for k in range(n)) for r in ridx]
        bc=[tuple(elem(c,bi*n*p+k*p+col,1,p) for k in range(n)) for col in cidx]
        ua,ub=len(set(ar)),len(set(bc))
        pairs=[(cidx[q],cidx[q+1]) for q in range(len(cidx)-1) if cidx[q]%2==0 and cidx[q+1]==cidx[q]+1 and bc[q]==bc[q+1]]
        rows.append({'case':c['name'],'batch_index':bi,'shape':[c['batch'],m,n,p],
          'sampled_rows':len(ar),'unique_raw_rows':ua,'sampled_columns':len(bc),'unique_raw_columns':ub,
          'identical_adjacent_pairs':pairs,'n':n,
          'sampled_MACs':len(ar)*len(bc)*n,'ideal_unique_pair_MACs':ua*ub*n,
          'all_rows_sampled':len(ar)==m,'all_columns_sampled':len(bc)==p})
valid=[r for r in rows if 'sampled_MACs' in r]
total=sum(r['sampled_MACs'] for r in valid); unique=sum(r['ideal_unique_pair_MACs'] for r in valid)
out={'observed_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'SEEN_SOURCE_MODEL_ONLY',
 'plan':str(PLAN),'plan_sha256':hashlib.sha256(PLAN.read_bytes()).hexdigest(),
 'generator_sha256':hashlib.sha256(GEN.read_bytes()).hexdigest(),'translation_sha256':hashlib.sha256(MODEL.read_bytes()).hexdigest(),
 'alignment_to_Lean_execution':'NOT_INDEPENDENTLY_VERIFIED', 'raw_reads':reads,'trace_sha256':trace.hexdigest(),
 'sampled_MACs':total,'ideal_unique_pair_MACs':unique,'ideal_arithmetic_work_reduction_fraction':None if not total else 1-unique/total,
 'rows_with_exact_column_reuse':sum(r['unique_raw_columns']<r['sampled_columns'] for r in valid),
 'rows_with_exact_row_reuse':sum(r['unique_raw_rows']<r['sampled_rows'] for r in valid),
 'identical_adjacent_column_pairs':sum(len(r['identical_adjacent_pairs']) for r in valid),
 'seconds':time.monotonic()-start,'rows':rows,
 'limitations':'Raw equality is sufficient for equal ordered dot terms including NaN words, but equality-to-public-spec proof NOT_RUN. MAC count ignores certificate, comparisons, dedup metadata, preparation, output construction/checksum and fallback. This is not time share, overall speed, official coverage or confirmation. Inputs were already exposed in R15; no holdout inspected.'}
(HERE/'exact-reuse-screen.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='rows'},ensure_ascii=False))
