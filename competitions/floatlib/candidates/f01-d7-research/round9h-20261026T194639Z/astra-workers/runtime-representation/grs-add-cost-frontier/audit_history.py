"""Read historical semantics/benchmark and exact R16 selected C."""
from pathlib import Path
import hashlib,json,importlib.util,datetime
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
ROUND=HERE.parents[2];sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
old=ROOT/'competitions/floatlib/candidates/f01-grs-normal-add-prototype/Kernel.lean'
assert sha(old)=='6bef4c4b6835c31260cf0d0fdd1163905f0bb38338b189f90e6bde7c8bc215c8'
text=old.read_text();start=text.index('namespace GRSAdd');end=text.index('end GRSAdd',start)
rt=text[start:end]
assert 'if a >>> 31 != b >>> 31 then ExecFloat.add x y else' in rt
assert 'm.log2' in rt and 'by sorry' in text
rp=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39575344774'
idx=json.loads((rp/'original-artifact-hashes.json').read_text());art=rp/idx['directory']
vp=art/'f01-grs-normal-add-prototype-verdict.json';entry=idx['files'][vp.name]
assert sha(vp)==entry['sha256'] and vp.stat().st_size==entry['bytes']
v=json.loads(vp.read_text());assert v['mode']=='bench' and v['stage']=='score'
sp=importlib.util.spec_from_file_location('ccompare',HERE.parent/'compare_classifier_codegen.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
diag=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40189703522/download-6480abc393984675972cc19005e1e7f9/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r16-dev-native-add-high3'
sources,records=m.load(diag,'f7f4702f9191061bb70a274610c9b735967ce4460ca2ef6ae121b9264fad18dd')
selected=m.select(sources)['add'];assert selected['unboxed']=='lp_competition_main___lam__2'
assert hashlib.sha256((selected['body']+'\n').encode()).hexdigest()=='4e21dc0bc54b8bc1a9badfde27ee604c0bff323c49b8db1f0d6cc1670939fd89'
(HERE/'R16-selected-ADD.c').write_text(selected['body']+'\n',encoding='utf-8')
r16=ROOT/'competitions/floatlib/candidates/f01-r16-dev-native-add-high3/Kernel.lean'
fixed=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
roots=[ROUND/'astra-grs-add-paper.md',ROUND/'astra-grs-add-model.py',ROUND/'astra-workers/exact-arithmetic/grs-add-review.md',fixed,r16,HERE/'Runtime-grs32-add.lean.inc']
out={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'status':'BOUND_HISTORY_AND_COST_HYPOTHESIS_NO_NEW_COMPILE',
 'sources':[{'path':str(p),'sha256':sha(p),'bytes':p.stat().st_size} for p in roots],
 'old_GRS':{'source_sha256':sha(old),'bytes':old.stat().st_size,'benchmark_run':39575344774,'verdict_sha256':sha(vp),'mode':v['mode'],'ratio_to_old_reference':v['ratio'],'has_explicit_placeholder':True,'reachable_domain':'same-sign normal only; opposite-sign log2 branch dead under outer guard','scope':'Old legacy benchmark-only result, not B2/current public-v2 or full-gate acceptance. No source copied into new Kernel.'},
 'R16':{'input_sha256':sha(r16),'C_sources':records,'selected':{k:x for k,x in selected.items() if k!='body'},'selected_body_sha256':hashlib.sha256((selected['body']+'\n').encode()).hexdigest(),'accepted_native_shape':'One U32.toFloat32 plus one toBits already present; no table or FPadd/mul on accepted arm.','prior_negative':'Full whole/B2 1.29455085598,ADD/B2 1.87392268417 retained; repeated ordering is C evidence, not scalarASM attribution.'},
 'new_actual_differences':['UInt32 <2^28 GRS rather than UInt64 hand-round','All normal signs/gaps rather than same-sign only or gap<=7/highN only','Raw magnitude order once, carry eBig/sign values explicitly','No asserted hardware reduction before actual C/ASM'],
 'semantic_bridge_reuse':'B2 R2W01c.uint32_model_eq_roundDyadic is forall UInt32 without high-N premise; lowT raw field/carry and original normal/postE bridges still unproved.',
 'next':'No largeKernel/CI. A true concrete diagnostic caller may check sort/FFI/postguard costs after higher-priority proof work permits; public spec remains unproved.',
 'lean':'NOT_RUN','codegen':'NOT_RUN','full_gate':'NOT_RUN','performance':'UNKNOWN'}
(HERE/'history-and-cost.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'old_GRS_ratio':v['ratio'],'old_GRS_mode':v['mode'],'R16_selected':selected['unboxed'],'runtime_fragment_sha256':sha(HERE/'Runtime-grs32-add.lean.inc')}))
