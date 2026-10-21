from pathlib import Path
import datetime, hashlib, json, re

ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent
RUN = ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39586444651/download-f7491e72c5fd4d2aac0e6c0eeff0fbd8'
PARENT = ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39575944885/download-15ae6a8ce76c4773b19924ec53c7a2d3/diagnostics/f01-index-hoist-proof2/candidate-generated-0.c'
CURRENT = RUN/'diagnostics/f01-d1-direct-dot-loop/candidate-generated-0.c'

def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
def path(p): return str(p.relative_to(ROOT)).replace('\\','/')
def body(p, name):
    text=p.read_text(encoding='utf8')
    begin=text.index('LEAN_EXPORT uint32_t '+name+'(')
    begin=text.index('LEAN_EXPORT uint32_t '+name+'(',begin+1)
    end=text.index('LEAN_EXPORT ',begin+1)
    result=text[begin:end]
    counts={key:result.count(key) for key in [
      'lean_apply','lean_alloc','lean_nat_add','lean_nat_mul','lean_nat_dec_lt',
      'lean_array_get_size','lean_array_fget_borrowed','lean_unbox_uint32',
      'Submission_TunedAdd_add','Submission_FastMul_mul','goto _start']}
    return {'function':name,'signature':result.splitlines()[0],'calls':counts}

vpath=RUN/'f01-d1-direct-dot-loop-verdict.json'
v=json.loads(vpath.read_text(encoding='utf8'))
assert v['passed'] and v['mode']=='gate' and v['stage']=='score'
assert len(v['classes'])==12 and len(v['rounds'])==25
source=RUN/'inputs/f01-d1-direct-dot-loop/Kernel.lean'
frozen=ROOT/'competitions/floatlib/candidates/f01-r1-direct-dot-loop/Kernel.lean'
assert sha(source)==sha(frozen)=='cb09e9c6913100097f21ebdc5059345885bce090894f53f8f876377edad8fcab'
out={
 'checked_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'run':39586444651,'kernel_sha256':sha(source),'full_gate':'PASS_EXACT_FROZEN_SOURCE',
 'ratio_vs_shipped':v['ratio'],'rounds':len(v['rounds']),'classes':len(v['classes']),
 'bmm_ratio_vs_shipped':sum(x['submission_ns'] for k,x in v['classes'].items() if k.startswith('bmm:'))/sum(x['incumbent_ns'] for k,x in v['classes'].items() if k.startswith('bmm:')),
 'parent_loop':body(PARENT,'lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0'),
 'direct_loop':body(CURRENT,'lp_competition_Submission_dotLoop'),
 'artifacts':[{'path':path(p),'sha256':sha(p),'bytes':p.stat().st_size} for p in [source,vpath,RUN/'f01-d1-direct-dot-loop-gate.log',CURRENT,PARENT]],
 'conclusion':'Direct-loop source is fully verified in this run, but its parent already had a specialized uint32_t reduction loop. Same selected runtime-operation counts. The 6.64% bmm improvement is versus shipped reference, not a paired improvement over the hoisted parent. Do not attribute that whole improvement to removal of callbacks.',
 'champion_direct_comparison':'UNKNOWN'
}
(HERE/'direct-loop-audit.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
print(json.dumps(out,indent=2))
