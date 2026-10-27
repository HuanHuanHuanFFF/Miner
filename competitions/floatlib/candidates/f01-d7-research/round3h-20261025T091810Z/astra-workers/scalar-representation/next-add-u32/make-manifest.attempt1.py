"""Bind this finite feasibility note to read-only historical sources; no compilation."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
def ident(p):
    b=p.read_bytes();return {'path':str(p.relative_to(ROOT)),'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()}
paths=[
 'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean',
 'competitions/floatlib/candidates/f01-r14-dev-word-add-entry2/Kernel.lean',
 'competitions/floatlib/candidates/f01-d2-decoder-helpers/Kernel.lean',
 'competitions/floatlib/candidates/f01-d2-decoder-helpers/manifest.json',
 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-aligned-add-math-review.md',
 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-common-rounding-boundary-review.md',
 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-web-pro-materials/common-rounding/originals/R14_common_rounding_repaired.lean',
 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-add-upstream-index.json',
 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/development-round-results.json',
 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-upstream/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean',
 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-upstream/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Agreement.lean',
 'competitions/floatlib/research/materials/20261022/R2-W01c/FloatLib_R2-W01c/public_sources/floatlib_fixed/FloatLib/Floats/Formats/BinaryInterchange/Model/Lean.lean']
sources=[ident(ROOT/p) for p in paths]
assert sources[0]['sha256']=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sources[1]['sha256']=='f958071e037ea5627a34d41b296d07cc97fd13eec41117de7c9b184bf0fad653'
cpath=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168024176/download-97e5567f5b7c4fc2a261a6d6dac40edc/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r15-dev-packed-b2-1/candidate-generated-1.c'
assert ident(cpath)['sha256']=='94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb'
s=cpath.read_text(encoding='utf-8');m=re.search(r'^LEAN_EXPORT uint32_t lp_competition_main___lam__0\([^;\n]*\)\{',s,re.M);assert m
start=s.index('{',m.start());end=start+1;depth=1
while depth:depth+=(s[end]=='{')-(s[end]=='}');end+=1
body=s[m.start():end]+'\n';(HERE/'B2-selected-add.c').write_bytes(body.encode())
counts={name:len(re.findall(r'\b'+name+r'\(',body)) for name in ['lean_uint32_to_float32','lean_float32_add','lean_float32_mul','lean_array_fget_borrowed','lean_float32_beq','lean_float32_to_bits','lean_alloc_ctor','lean_apply_2']}
assert counts['lean_uint32_to_float32']==2 and counts['lean_float32_add']==1 and counts['lean_float32_mul']==2
assert counts['lean_array_fget_borrowed']==2
fragment=HERE/'UInt32NativeRound-interface.lean'
assert not re.search(r'\b(sorry|admit|axiom|unsafe|native_decide)\b',fragment.read_text())
report={'created_utc':datetime.now(timezone.utc).isoformat(),'state':'FEASIBILITY_COMPLETE_PROOF_DRAFT_NOT_COMPILED',
 'source_records':sources,'B2_selected_C_source':ident(cpath),'B2_add_C_body':ident(HERE/'B2-selected-add.c'),'B2_add_C_static_sites':counts,
 'new_fragment':ident(fragment),'finite_screen':ident(HERE/'screen.json'),'screen_script':ident(HERE/'add-u32-screen.py'),
 'failed_first_screen_source':ident(HERE/'add-u32-screen.attempt1.py'),'failed_first_screen_stderr':ident(HERE/'screen.attempt1.stderr.txt'),
 'decision':ident(HERE/'decision.md'),
 'provenance':'Project R2/R14 helper proofs are project artifacts; fixed upstream model/runtime API declarations are FloatLib Team/MIT and Lean/Microsoft/Apache2.0. Common-rounding webpage original remains NOT_RUN. No claim of new IEEE mathematics.',
 'scope':'Only new next-add-u32 directory written; no current40183711165 data read, no c972 or previous audit edited, no Git/CI/localLean/nested agents.',
 'input_tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN','output_tokens':'UNKNOWN','reasoning_tokens':'UNKNOWN','ci_occupancy_seconds':0}
(HERE/'manifest.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'state':report['state'],'fragment':report['new_fragment'],'finite_screen':report['finite_screen'],'B2_add_C_static_sites':counts},indent=2))
