"""Pinned B2 + finite F64 numeric-decode ADD; diagnostic only, no Lean execution."""
from pathlib import Path
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
OLD=PUB/'f01-d7-research/round6h-20261027T211247Z'
NAME='f01-r24-dev-scalar-f64array-cost1'
TARGET=PUB/NAME
sha=lambda b:hashlib.sha256(b).hexdigest()
def write(p,raw):
    p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(raw if isinstance(raw,bytes) else raw.encode())
def once(s,a,b):
    assert s.count(a)==1,(a[:80],s.count(a));return s.replace(a,b)
base=(PUB/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes()
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
runtime='''
/- R24 finite F64 numerical decoder: COST DIAGNOSTIC ONLY, not a proved ADD.
   Imported Float.toFloat32 is opaque. Four public functions/specs stay B2. -/
namespace Submission.R24F64Add
open FloatLib.Floats Competition
@[inline] def scaleWord (j : UInt32) : UInt64 :=
  let e := (j &&& 255).toUInt64
  let s := (j &&& 256).toUInt64 <<< 55
  let E := if e == 0 then (874 : UInt64) else e+873
  s ||| (E <<< 52)
def boxedScales : Array Float :=
  Array.ofFn (n := 512) fun j => Float.ofBits (scaleWord (UInt32.ofNat j.val))
def nativeScales : FloatArray :=
  (List.range 512).foldl
    (fun (a : FloatArray) j => a.push (Float.ofBits (scaleWord (UInt32.ofNat j))))
    (FloatArray.emptyWithCapacity 512)
@[inline] def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x7fffff) ||| (if u &&& 0x7f800000 == 0 then 0 else 0x800000)
@[inline] def finite (u : UInt32) : Bool :=
  u &&& (0x7f800000 : UInt32) != 0x7f800000
@[inline] def decodeNative (u : UInt32) : Float :=
  (mantissa u).toFloat * nativeScales.get! ((u >>> 23).toNat)
@[inline] def decodeBoxed (u : UInt32) : Float :=
  (mantissa u).toFloat * boxedScales[(u >>> 23).toNat]!
/- Finite binary64 word to nearest-even binary32 word. New unproved GRS core.
   Unlike the cast control, every operation here has a fixed Lean model. -/
@[inline] def narrowWord (w : UInt64) : UInt32 :=
  let sign := (w >>> 32).toUInt32 &&& (0x80000000 : UInt32)
  let e := (w >>> 52) &&& (2047 : UInt64)
  if e < 873 then sign
  else if e > 1150 then sign ||| 0x7f800000
  else
    let m := (w &&& (0xfffffffffffff : UInt64)) ||| (0x10000000000000 : UInt64)
    if e < 897 then
      let d := (926 : UInt64)-e
      let q := (m + (((1 : UInt64) <<< (d-1))-1) + ((m >>> d) &&& 1)) >>> d
      sign ||| q.toUInt32
    else
      let q := ((m + (0xfffffff : UInt64) + ((m >>> 29) &&& 1)) >>> 29).toUInt32
      sign ||| (((e.toUInt32-897) <<< 23)+q)
@[noinline] def retainedAdd (x y : Binary32) : Binary32 := Submission.add x y
@[inline] def nativeArrayAdd (x y : Binary32) : Binary32 :=
  if finite x.raw.1 && finite y.raw.1 then
    R7W02.fromRaw (narrowWord (decodeNative x.raw.1 + decodeNative y.raw.1).toBits)
  else retainedAdd x y
@[inline] def boxedArrayAdd (x y : Binary32) : Binary32 :=
  if finite x.raw.1 && finite y.raw.1 then
    R7W02.fromRaw (narrowWord (decodeBoxed x.raw.1 + decodeBoxed y.raw.1).toBits)
  else retainedAdd x y
/- Engineering lower-bound control only: opaque narrowing cannot justify adoption. -/
@[inline] def nativeCastAdd (x y : Binary32) : Binary32 :=
  if finite x.raw.1 && finite y.raw.1 then
    R7W02.fromRaw ((decodeNative x.raw.1 + decodeNative y.raw.1).toFloat32.toBits)
  else retainedAdd x y
end Submission.R24F64Add
'''
source=base+runtime.encode();assert len(source)<=256000
write(HERE/'F64ArrayAdd.lean.inc',runtime);write(TARGET/'Kernel.lean',source)
main='''import BenchFull
import BenchSuite
import Submission
open Competition
@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm
@[noinline] def runF64Native : IO UInt32 :=
  Bench.Suite.run Submission.R24F64Add.nativeArrayAdd Submission.mul Submission.sum Submission.bmm
@[noinline] def runF64Boxed : IO UInt32 :=
  Bench.Suite.run Submission.R24F64Add.boxedArrayAdd Submission.mul Submission.sum Submission.bmm
@[noinline] def runF64Cast : IO UInt32 :=
  Bench.Suite.run Submission.R24F64Add.nativeCastAdd Submission.mul Submission.sum Submission.bmm
def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "f64native" then runF64Native
  else if variant == some "f64boxed" then runF64Boxed
  else if variant == some "f64cast" then runF64Cast
  else throw (IO.userError "BENCH_VARIANT invalid for R24 F64 ADD cost")
'''
write(HERE/'R24ScalarF64CostMain.lean',main)
write(HERE/'static_runner_audit.py',(OLD/'development-nativecold/static_runner_audit.py').read_bytes())
driver=(OLD/'development-nativecold/driver.py').read_text()
driver=driver.replace('R22NativeColdCostMain','R24ScalarF64CostMain').replace('r22NativeColdCost','r24ScalarF64Cost').replace('R22MultiStaticCostLake','R24ScalarF64CostLake')
driver=once(driver,"SOURCE = '5d610468556f5660c0b80551be22149c9d086badbe10342ddecc3f6509ea8d93'",f"SOURCE = '{sha(source)}'")
driver=once(driver,'SEEDS = (2220001, 2220003)','SEEDS = (2240101, 2240103)')
driver=once(driver,"VARIANTS = ('th0','nativeinline','nativecold','nativeadd')","VARIANTS = ('f64native','f64boxed','f64cast')")
driver=driver.replace("('runControl','runTh0','runNativeInline','runNativeCold','runNativeAdd')","('runControl','runF64Native','runF64Boxed','runF64Cast')")
driver=driver.replace("template.count(b'Bench.Suite.run ') == 5", "template.count(b'Bench.Suite.run ') == 4")
driver=driver.replace('Five separate static Suite IO runners required','Four separate static Suite IO runners required')
driver=driver.replace('Exact compiledR22Cost runtime required','Exact finite F64 decode ADD source required')
driver=once(driver,"'processes':32","'processes':24")
driver=once(driver,
    "pair[variant+'_block_1']=summarize(plan,results[k+3],results[k+2])",
    "pair[variant+'_block_1']=summarize(plan,results[k+3],results[k+2])\n                seed_runs=[r for r in record['runs'] if r['seed']==seed]\n                pair[variant+'_process_wall']={\n                    'block_0':{'control_seconds':seed_runs[k]['seconds'],'variant_seconds':seed_runs[k+1]['seconds'],'variant_over_control':seed_runs[k+1]['seconds']/seed_runs[k]['seconds']},\n                    'block_1':{'control_seconds':seed_runs[k+3]['seconds'],'variant_seconds':seed_runs[k+2]['seconds'],'variant_over_control':seed_runs[k+2]['seconds']/seed_runs[k+3]['seconds']},\n                    'scope':'Complete process wall includes both diagnostic global table initializations, operand preparation, warmup, sweeps, output, release and process overhead; not official score or a standalone B2 process baseline.'}")
old='Full156-case diagnostic composition,152 timed cases and two discovery seeds; not original25-round score/adoption. Variants nativeadd changesADD; nativeinline/nativecold andmechanism-onlyth0 changeMUL; all other callbacks areB2. All prep,cache/state allocation,odd tails,finish anddestruction retained. Actual public proof/caller and independent confirmation remain required.'
new='Full156-case/152 timed diagnostic,24 complete processes,two discovery seeds. ADD changes only; MUL/SUM/BMM fixed B2. F64 fullfinite numeric decode/native binary64 ADD, then same-width Float.toBits and new UInt64 GRS/RNE word narrowing for f64native/f64boxed. f64cast uses opaque Float.toFloat32 as an engineering lower-bound control only, never a provable-candidate claim. NaN/Inf retain B2. FloatArray versus ArrayFloat signed scale tables attribute layout. Case ns exclude operand/global preparation; full-process wall separately includes both tables/prep/cleanup. All new helpers NOT_PROVED, not admissible score/adoption; standalone package startup cost UNKNOWN.'
driver=once(driver,old,new)
write(HERE/'driver.py',driver)
audit=(OLD/'development-nativecold-cost-audit.py').read_text()
audit=once(audit,"SOURCE = '5d610468556f5660c0b80551be22149c9d086badbe10342ddecc3f6509ea8d93'",f"SOURCE = '{sha(source)}'")
audit=audit.replace("path.is_relative_to(here/'development-nativecold')",'path.is_relative_to(here)')
audit=audit.replace("driver = here/'development-nativecold/driver.py'","driver = here/'driver.py'")
audit=audit.replace("'prior_components':'ExactB2_622d_prefix; NativeColdADD_MUL not proved'","'prior_components':'ExactB2_622d_prefix; F64 decode/add and UInt64 RNE narrowing are NOT_PROVED; cast control opaque'")
audit=audit.replace("'new_public_ADD_MUL_correctness':'UNKNOWN'","'new_diagnostic_ADD_correctness':'UNKNOWN_NEW_LEGAL_GRS_CORE_AND_OPAQUE_LOWER_BOUND_CONTROL'")
write(HERE/'f64-cost-audit.py',audit)
components=[]
for name in ('driver.py','f64-cost-audit.py','F64ArrayAdd.lean.inc','R24ScalarF64CostMain.lean','static_runner_audit.py'):
    p=HERE/name;raw=p.read_bytes();components.append({'path':p.relative_to(ROOT).as_posix(),'bytes':len(raw),'sha256':sha(raw)})
manifest={'candidate':NAME,'candidate_file':'Kernel.lean','candidate_sha256':sha(source),'candidate_bytes':len(source),
    'parent_sha256':sha(base),'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':600,
    'helper_audit_module':'f64-cost-audit.py','helper_audit_module_path':(HERE/'f64-cost-audit.py').relative_to(PUB).as_posix(),
    'helper_audit_module_sha256':sha((HERE/'f64-cost-audit.py').read_bytes()),'components':components,
    'proof_status':'NOT_RUN_PUBLIC4SPEC_B2_NEW_F64_DECODE_ADD_GRS_HELPERS_UNPROVED_CAST_CONTROL_OPAQUE',
    'performance':'NOT_RUN','formal_submission':'NOT_SUBMITTED','official_submission_inherited':False,
    'runtime_cost':{'overall_budget_seconds_from_stage_registration':580,'build_cap_seconds':180,'measure_phase_cap_seconds':300,
       'seeds':[2240101,2240103],'order_per_seed':[x for v in ('f64native','f64boxed','f64cast') for x in ('control',v,v,'control')],
       'processes':24,'pairs':500000,'inner':3,'observer':False},
    'scope':new,'source_parts':{'exact_B2_prefix':sha(base),'runtime':sha(runtime.encode())},
    'semantic_domain':'All finite binary32 E0..254 including signed zeros/subnormals; e=0 scale2^-149, e>0 scale2^(e-150), signed Float64 scales all normal. NaN/Inf fallback B2.',
    'trust_gap':'Legal paths use fixed-model primitives plus new unproved UInt64 GRS core; finite decode/native ADD/double-round bridge and fallback composition remain unproved. The opaque Float.toFloat32 control is engineering lower-bound only and cannot be adopted or substitute for legal-path cost.'}
write(TARGET/'manifest.json',json.dumps(manifest,ensure_ascii=False,indent=2)+'\n')
write(HERE/'READY.json',json.dumps({'status':'PREPARED_PENDING_LOCAL_PREFLIGHT','candidate':TARGET.relative_to(ROOT).as_posix(),'source_sha256':sha(source),'bytes':len(source),'components':components},indent=2)+'\n')
print(json.dumps({'candidate':NAME,'source_sha256':sha(source),'bytes':len(source),'helper_audit_module_sha256':manifest['helper_audit_module_sha256']}))
