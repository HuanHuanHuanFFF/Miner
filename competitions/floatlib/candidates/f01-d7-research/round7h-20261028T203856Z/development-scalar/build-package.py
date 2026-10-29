"""Assemble a diagnostic package from pinned retained sources; never builds Lean."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z'
PUB = ROOT / 'competitions/floatlib/candidates'
NAME = 'f01-r24-dev-scalar-routes-cost1'
TARGET = PUB / NAME
sha = lambda raw: hashlib.sha256(raw).hexdigest()

def write(path, raw):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(raw if isinstance(raw, bytes) else raw.encode())

def replace_once(text, old, new):
    assert text.count(old) == 1, (old[:100], text.count(old))
    return text.replace(old, new)

base = (PUB / 'f01-r23-dev-outline-public1/Kernel.lean').read_bytes()
assert sha(base) == 'f90d42e346a1634ffeb537ea7e9980e0a91baea8499dc6c2235da5ab8fe0e85f'
runtime = '''
namespace Submission.R24Scalar
open FloatLib.Floats Competition
@[inline] def pairOK (u v : UInt32) : Bool :=
  (((u &&& 0x7fffffff)-0x20000000) |||
   ((v &&& 0x7fffffff)-0x20000000)) < (0x40000000 : UInt32)
@[inline] def hotMul (x y : Binary32) : Binary32 :=
  ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 * R2W01b.tableProduct y.raw.1)
@[inline] def nativeMul (x y : Binary32) : Binary32 :=
  if pairOK x.raw.1 y.raw.1 then hotMul x y
  else R19BiasBase.R19DirectBias.retainedMul x y
@[inline] def nativeFirst (x y : Binary32) : Binary32 :=
  if pairOK x.raw.1 y.raw.1 then hotMul x y else Submission.mul x y
@[inline] def integerFirst (x y : Binary32) : Binary32 :=
  R19BiasBase.R19DirectBias.guardedMul nativeMul x y
end Submission.R24Scalar
'''
source = base + runtime.encode()
assert len(source) <= 256000, len(source)
write(HERE / 'ScalarRoutes.lean.inc', runtime)
write(TARGET / 'Kernel.lean', source)

main = '''import BenchFull
import BenchSuite
import Submission
open Competition
@[noinline] def runControl : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add R19BiasBase.mul R19BiasBase.sum R19BiasBase.bmm
@[noinline] def runNative : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add Submission.R24Scalar.nativeMul R19BiasBase.sum R19BiasBase.bmm
@[noinline] def runInteger : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add Submission.mul R19BiasBase.sum R19BiasBase.bmm
@[noinline] def runNativeFirst : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add Submission.R24Scalar.nativeFirst R19BiasBase.sum R19BiasBase.bmm
@[noinline] def runIntegerFirst : IO UInt32 :=
  Bench.Suite.run R19BiasBase.add Submission.R24Scalar.integerFirst R19BiasBase.sum R19BiasBase.bmm
def main : IO UInt32 := do
  let variant ← IO.getEnv "BENCH_VARIANT"
  if variant == some "control" then runControl
  else if variant == some "native" then runNative
  else if variant == some "integer" then runInteger
  else if variant == some "nativefirst" then runNativeFirst
  else if variant == some "integerfirst" then runIntegerFirst
  else throw (IO.userError "BENCH_VARIANT invalid for R24 scalar diagnostic")
'''
write(HERE / 'R24ScalarCostMain.lean', main)

# This target is separate from the timed Main, so its observer cannot enter a callback.
domain = '''import BenchFull
import BenchSuite
import Submission
open Competition Lean
def main : IO UInt32 := do
  let some text ← IO.getEnv "BENCH_PLAN"
    | throw (IO.userError "BENCH_PLAN is required")
  let plan ← match Json.parse text >>= fromJson? (α := Bench.Suite.Plan) with
    | .ok p => pure p
    | .error e => throw (IO.userError e)
  if plan.version != "suite-v2" then throw (IO.userError "plan version")
  for c in plan.cases do
    if c.kernel == "mul" then
      let mut both := 0
      let mut integerOnly := 0
      let mut nativeOnly := 0
      let mut neither := 0
      let mut sink : UInt32 := 0
      let mut bu : UInt32 := 0
      let mut bv : UInt32 := 0
      let mut iu : UInt32 := 0
      let mut iv : UInt32 := 0
      let mut nu : UInt32 := 0
      let mut nv : UInt32 := 0
      let mut zu : UInt32 := 0
      let mut zv : UInt32 := 0
      for i in [0:c.work] do
        let u := Bench.Suite.element c i 0 31
        let v := Bench.Suite.partner c i u
        let native := Submission.R24Scalar.pairOK u v
        let eu := (u >>> 23) &&& (255 : UInt32)
        let ev := (v >>> 23) &&& (255 : UInt32)
        let integer := eu-1 ≤ (253 : UInt32) && ev-1 ≤ (253 : UInt32) && eu+ev-128 ≤ (252 : UInt32)
        if native && integer then
          if both == 0 then
            bu := u
            bv := v
          both := both+1
        else if integer then
          if integerOnly == 0 then
            iu := u
            iv := v
          integerOnly := integerOnly+1
        else if native then
          if nativeOnly == 0 then
            nu := u
            nv := v
          nativeOnly := nativeOnly+1
        else
          if neither == 0 then
            zu := u
            zv := v
          neither := neither+1
        sink := (sink ^^^ u ^^^ v) * 16777619
      IO.println s!"DOMAIN {c.name} {c.work} {both} {integerOnly} {nativeOnly} {neither} {sink}"
      IO.println s!"EXAMPLE {c.name} {bu} {bv} {iu} {iv} {nu} {nv} {zu} {zv}"
  return 0
'''
write(HERE / 'R24ScalarDomainMain.lean', domain)
write(HERE / 'static_runner_audit.py', (OLD / 'development-nativecold/static_runner_audit.py').read_bytes())

driver = (OLD / 'development-nativecold/driver.py').read_text()
driver = driver.replace('R22NativeColdCostMain', 'R24ScalarCostMain').replace('r22NativeColdCost', 'r24ScalarCost').replace('R22MultiStaticCostLake', 'R24ScalarCostLake')
driver = replace_once(driver, "SOURCE = '5d610468556f5660c0b80551be22149c9d086badbe10342ddecc3f6509ea8d93'", f"SOURCE = '{sha(source)}'")
driver = replace_once(driver, 'SEEDS = (2220001, 2220003)', 'SEEDS = (2240001, 2240003)')
driver = replace_once(driver, "VARIANTS = ('th0','nativeinline','nativecold','nativeadd')", "VARIANTS = ('native','integer','nativefirst','integerfirst')")
driver = driver.replace("('runControl','runTh0','runNativeInline','runNativeCold','runNativeAdd')", "('runControl','runNative','runInteger','runNativeFirst','runIntegerFirst')")
driver = driver.replace('Exact compiledR22Cost runtime required', 'Exact R24 scalar-route source required')
driver = driver.replace("'processes':32", "'processes':32")
driver = replace_once(driver,
    "source = g.WORK.parent/'R24ScalarCostMain.lean'",
    "source = g.WORK.parent/'R24ScalarCostMain.lean'\n    domain_source = g.WORK.parent/'R24ScalarDomainMain.lean'\n    require(not domain_source.exists(), 'Fresh domain source required')")
driver = replace_once(driver,
    "owned_config = config + b'\\n\\nlean_exe r24ScalarCost where\\n  srcDir := \"work\"\\n  root := `R24ScalarCostMain\\n'",
    "owned_config = config + b'\\n\\nlean_exe r24ScalarCost where\\n  srcDir := \"work\"\\n  root := `R24ScalarCostMain\\n\\nlean_exe r24ScalarDomain where\\n  srcDir := \"work\"\\n  root := `R24ScalarDomainMain\\n'")
driver = replace_once(driver,
    'for path, raw in ((source, template), (alternate, owned_config)):',
    "for path, raw in ((source, template), (domain_source, (HERE/'R24ScalarDomainMain.lean').read_bytes()), (alternate, owned_config)):")
driver = replace_once(driver,
    "'owned_files': {str(source): sha(source), str(alternate): sha(alternate)},",
    "'owned_files': {str(source): sha(source), str(domain_source): sha(domain_source), str(alternate): sha(alternate)},")
driver = driver.replace('Only writes two owned work files', 'Only writes three owned work files')
driver = replace_once(driver,
    "'build', 'r24ScalarCost']", "'build', 'r24ScalarCost', 'r24ScalarDomain']")
driver = driver.replace("('R24ScalarCostMain','r24ScalarCost')", "('R24ScalarCostMain','r24ScalarCost','R24ScalarDomainMain','r24ScalarDomain')")
driver = replace_once(driver,
    "'source_sha256':SOURCE, 'runs':[], 'caller_C_ASM_review'",
    "'source_sha256':SOURCE, 'runs':[], 'domain_runs':[], 'caller_C_ASM_review'")
driver = replace_once(driver,
    "deadline = min(time.monotonic()+300,absolute_deadline-52); pairs=[]",
    "deadline = min(time.monotonic()+300,absolute_deadline-72); pairs=[]")
driver = replace_once(driver,
    "pair[variant+'_block_1']=summarize(plan,results[k+3],results[k+2])",
    "pair[variant+'_block_1']=summarize(plan,results[k+3],results[k+2])\n                seed_runs=[r for r in record['runs'] if r['seed']==seed]\n                pair[variant+'_process_wall']={\n                    'block_0':{'control_seconds':seed_runs[k]['seconds'],'variant_seconds':seed_runs[k+1]['seconds'],'variant_over_control':seed_runs[k+1]['seconds']/seed_runs[k]['seconds']},\n                    'block_1':{'control_seconds':seed_runs[k+3]['seconds'],'variant_seconds':seed_runs[k+2]['seconds'],'variant_over_control':seed_runs[k+2]['seconds']/seed_runs[k+3]['seconds']},\n                    'scope':'Full process elapsed via original g.own: includes input preparation, warmup, sweeps, output, cleanup and sandbox/process overhead; not official score or isolated kernel time.'}")
old_scope = 'Full156-case diagnostic composition,152 timed cases and two discovery seeds; not original25-round score/adoption. Variants nativeadd changesADD; nativeinline/nativecold andmechanism-onlyth0 changeMUL; all other callbacks areB2. All prep,cache/state allocation,odd tails,finish anddestruction retained. Actual public proof/caller and independent confirmation remain required.'
driver = replace_once(driver, old_scope,
    'Full156-case diagnostic,152 timed cases,two discovery seeds; five static Suite entries with ADD/SUM/BMM fixed B2. Only scalar MUL route changes. Case ns follow unmodified BenchSuite timers: operand generation excluded; callback/fallback/boxing inside, case-owned operands released after. Full-process wall separately includes generation, initialization, release and process overhead. No gate/adoption/official-score claim. Actual public proof/caller and independent confirmation remain required.')
driver = replace_once(driver,
    "capture=load_module(CAPTURE,'r19_reused_bounded_capture'); tools=[];tool_end=min(time.monotonic()+32,absolute_deadline-20)",
    "collect_domains(g, prepared, out, record, budget, absolute_deadline)\n        persist()\n        capture=load_module(CAPTURE,'r19_reused_bounded_capture'); tools=[];tool_end=min(time.monotonic()+32,absolute_deadline-20)")
domain_fn = '''

def parse_domains(log, plan):
    expected={c['name']:c for c in plan['cases'] if c['kernel']=='mul'}
    rows={};examples={}
    for line in log.splitlines():
        words=line.split()
        if words[:1]==['DOMAIN']:
            require(len(words)==8,'Domain record width')
            name=words[1];require(name in expected and name not in rows,'Unknown or duplicate domain case')
            values=list(map(int,words[2:]));work,both,integer_only,native_only,neither,sink=values
            require(work==expected[name]['work'] and both+integer_only+native_only+neither==work,'Incomplete domain census')
            rows[name]=dict(zip(('work','both','integer_only','native_only','neither','raw_operand_checksum'),values))
        elif words[:1]==['EXAMPLE']:
            require(len(words)==10,'Example record width')
            require(words[1] in expected and words[1] not in examples,'Unknown/duplicate example')
            examples[words[1]]=list(map(int,words[2:]))
    require(set(rows)==set(expected)==set(examples),'Missing MUL census records')
    for name,row in rows.items():
        row['first_examples_if_count_positive']={k:examples[name][2*i:2*i+2] for i,k in enumerate(('both','integer_only','native_only','neither')) if row[k]>0}
    return rows


def collect_domains(g, prepared, out, record, budget, absolute_deadline):
    binary=g.BUILD/'bin/r24ScalarDomain'
    require(visible(g,binary).is_file(),'Domain observer binary absent')
    # Domain enumeration is AFTER measured runs and in a separate executable.
    end=min(time.monotonic()+20,absolute_deadline-52)
    for seed in SEEDS:
        plan=json.loads((out/f'plan-{seed}.json').read_bytes())
        env={'BENCH_PLAN':json.dumps(plan,separators=(',',':')),'LEAN_ABORT_ON_PANIC':'1'}
        begun=time.monotonic()
        code,log=g.own([str(binary)],budget.cap('domains-'+str(seed),20,52,end),build='read',env_extra=env,memory_mb=g._BENCH_MEMORY_MB)
        (out/f'domains-{seed}.log').write_bytes(log.encode())
        record['domain_runs'].append({'seed':seed,'exit_code':code,'seconds':time.monotonic()-begun,'log_sha256':hashlib.sha256(log.encode()).hexdigest()})
        require(code==0,'Domain observer failed; measured raw runs remain retained')
        (out/f'domains-{seed}.json').write_bytes(encode(parse_domains(log,plan)))
    for stem in ('R24ScalarDomainMain.c','R24ScalarDomainMain.c.o.export.trace'):
        p=visible(g,g.BUILD/'ir'/stem)
        require(p.is_file(),'Domain observer build evidence missing')
        (out/('domain-build-'+stem)).write_bytes(p.read_bytes())
    record['domain_binary_sha256']=sha(visible(g,binary))
'''
driver = replace_once(driver, '\ndef cleanup_owned(prepared):', domain_fn+'\n\ndef cleanup_owned(prepared):')
write(HERE / 'driver.py', driver)

audit = (OLD/'development-nativecold-cost-audit.py').read_text()
audit = audit.replace('development-nativecold', 'development-scalar')
audit = replace_once(audit,
    "SOURCE = '5d610468556f5660c0b80551be22149c9d086badbe10342ddecc3f6509ea8d93'",
    f"SOURCE = '{sha(source)}'")
# The old stage was at the round root, this stage lives beside its own driver.
audit = audit.replace("path.is_relative_to(here/'development-scalar')", 'path.is_relative_to(here)')
audit = replace_once(audit, "driver = here/'development-scalar/driver.py'", "driver = here/'driver.py'")
audit = replace_once(audit,
    "'prior_components':'ExactB2_622d_prefix; NativeColdADD_MUL not proved',",
    "'prior_components':'Exactf90_prefix; new scalar-native composition helpers not yet proved',")
audit = replace_once(audit, "'new_public_ADD_MUL_correctness':'UNKNOWN'", "'new_diagnostic_MUL_helpers_correctness':'UNKNOWN'")
audit = audit.replace('Do not rerun historical7root/replay', 'New route helper proof/replay is a later gate, not this cost diagnostic')
write(HERE/'scalar-cost-audit.py', audit)

components=[]
for name in ('driver.py','scalar-cost-audit.py','ScalarRoutes.lean.inc','R24ScalarCostMain.lean','R24ScalarDomainMain.lean','static_runner_audit.py'):
    path=HERE/name;raw=path.read_bytes()
    components.append({'path':path.relative_to(ROOT).as_posix(),'bytes':len(raw),'sha256':sha(raw)})
manifest={
    'candidate':NAME,'candidate_file':'Kernel.lean','candidate_sha256':sha(source),'candidate_bytes':len(source),
    'parent_sha256':sha(base),'validation_mode':'statement-only','diagnostic_only':True,'diagnostic_timeout_seconds':600,
    'helper_audit_module':'scalar-cost-audit.py',
    'helper_audit_module_path':(HERE/'scalar-cost-audit.py').relative_to(PUB).as_posix(),
    'helper_audit_module_sha256':sha((HERE/'scalar-cost-audit.py').read_bytes()),
    'proof_status':'NOT_RUN_NEW_DIAGNOSTIC_HELPERS_PUBLIC_ENDPOINTS_RETAIN_EXACT_F90_PREFIX',
    'performance':'NOT_RUN','formal_submission':'NOT_SUBMITTED','official_submission_inherited':False,
    'components':components,
    'runtime_cost':{'overall_budget_seconds_from_stage_registration':580,'build_cap_seconds':180,'measure_phase_cap_seconds':300,
        'seeds':[2240001,2240003],'order_per_seed':[x for v in ('native','integer','nativefirst','integerfirst') for x in ('control',v,v,'control')],
        'processes':32,'pairs':500000,'inner':3,'observer_in_measured_process':False,'domain_processes_after_measurement':2},
    'scope':'Five separate static Suite IO entries; all miss routes retain B2. Native pair guard E64..191; integer normal E1..254,S128..380. ADD/SUM/BMM fixed B2, scalar MUL route only. Includes complete official caller, callbacks, misses, boxing and release; process wall reports input preparation/cleanup separately from official case ns. Exact F7 ADD is intentionally absent to isolate MUL; F7 source is a negative mechanism reference, not a seed-retry candidate.',
    'source_parts':{'f90_exact_prefix':sha(base),'appended_runtime':sha(runtime.encode())},
    'pending_parent_action':'Wire existing statement-only diagnostic stage to this driver; inspect static callback chain/C/ASM before cost decision. No CI dispatched by scalar agent.'}
write(TARGET/'manifest.json',json.dumps(manifest,ensure_ascii=False,indent=2)+'\n')
write(HERE/'READY.json',json.dumps({'status':'PREPARED_PENDING_LOCAL_PREFLIGHT','candidate':TARGET.relative_to(ROOT).as_posix(),'source_sha256':sha(source),'source_bytes':len(source),'headroom_bytes':256000-len(source),'manifest':(TARGET/'manifest.json').relative_to(ROOT).as_posix(),'components':components},indent=2)+'\n')
print(json.dumps({'candidate':NAME,'sha256':sha(source),'bytes':len(source),'headroom':256000-len(source)}))
