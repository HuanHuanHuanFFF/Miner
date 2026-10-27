"""Bounded existing-evidence falsification, not a timing reproduction or new benchmark."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,subprocess,sys,time
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'AGENTS.md').exists())
D=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40187127847/download-b017ff557ebd42d897cd761098245dbc'
S=D/'diagnostics/f01-d7-public-suite/public-suite'
def ident(p):
 b=p.read_bytes();return {'path':str(p.relative_to(R)),'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()}
def worker():
 t=time.perf_counter();kp=S/'inputs/f01-r15-dev-packed-b2-1/Kernel.lean';ki=ident(kp)
 assert ki['sha256']=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
 text=kp.read_text();assert 'decide (24 ≤ e) && decide (e ≤ 254)' in text
 assert 's ||| ((e - 23) <<< 23)' in text
 table=[]
 for j in range(512):
  assert time.perf_counter()-t<4.5
  e=j&255;sg=(j&256)<<23
  word=sg|((e-23)<<23) if 24<=e<=254 else sg
  table.append(word)
 sub=[j for j,w in enumerate(table) if (w&0x7f800000)==0 and (w&0x7fffff)!=0]
 assert not sub
 pp=S/'public-drawn-plan.json';plan=json.loads(pp.read_bytes());dense=[]
 for c in plan['cases']:
  if c['timed'] and c['name'].startswith('add:dense:'):
   assert c['mag']==0 and c['scaleBlock']==0 and c['zeroPct']==c['subPct']==c['specRate']==0 and c['relation']==0
   lo=max(1,c['center']-c['spread']);hi=min(254,c['center']+c['spread'])
   dense.append({'name':c['name'],'min_raw_exponent':lo,'max_raw_exponent':hi,'min_nonzero_sum_quantum_power':lo-150})
 assert len(dense)==6 and min(x['min_raw_exponent'] for x in dense)==68
 ci=D/'diagnostics/f01-d7-public-suite/candidate-c-index.json';cidx=json.loads(ci.read_bytes())
 for x in cidx:assert ident(ci.parent/x['file'])['sha256']==x['sha256']
 assert all(x['kernel_sha256']=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045' for x in cidx)
 dec=H.parents[1]/'development-baseline-control-decomposition-40187127847.json'
 # The round directory is three parents above this file's owned directory.
 dec=H.parents[2]/'development-baseline-control-decomposition-40187127847.json'
 decomposition=json.loads(dec.read_bytes())
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'TABLE_SUBNORMAL_FACTOR_MECHANISM_EXCLUDED_SOURCE_AND_COMPLETED_PLAN',
  'archived_B2_input':ki,'scale_table_model':{'complete_indices':512,'subnormal_entries':sub,'normal_nonzero_entries':462,'signed_zero_entries':50},
  'source_rule':'scaleBits e24..254 -> exponent e-23 in1..231, fraction0; all other table entries are signed zero. fastOK only zero or rawE24..254, low normal/raw subnormal inputs fall back to ofBits.',
  'completed_plan':ident(pp),'dense_case_ranges':dense,
  'dense_consequence':'Every dense input has rawE>=68; every exact nonzero sum is an integer multiple of2^-82 or larger, so cannot round to a nonzero subnormal. No subnormal scale factor exists in any cell.',
  'anomaly_add_decomposition':decomposition['operations']['add'],
  'decomposition_receipt':ident(dec),'available_C_index':ident(ci),'available_C_kernel_sha256':sorted(set(x['kernel_sha256'] for x in cidx)),
  'B2_timed_ELF_selected_caller_identity':'UNKNOWN; archived C is outer8eb carrier, not622d B2',
  'environment':ident(D/'environment.json'),'actual_CPU_model_clock_MXCSR_affinity':'UNKNOWN; ci.log has configured BENCH_CPU=0 and taskset availability only',
  'elapsed_seconds':time.perf_counter()-t,'external_timeout_seconds':5,'limitations':'Complete finite512-entry transcription plus full six-case descriptor bounds; no local Lean/native execution or hardware timing reproduction. No current401882/holdout data read.'}
 print(json.dumps(out,indent=2))
if __name__=='__main__':
 if '--worker' in sys.argv:worker()
 else:
  t=time.perf_counter();p=subprocess.run([sys.executable,str(Path(__file__)),'--worker'],capture_output=True,text=True,timeout=5)
  (H/'scale-check.stdout.txt').write_text(p.stdout,encoding='utf-8');(H/'scale-check.stderr.txt').write_text(p.stderr,encoding='utf-8')
  assert p.returncode==0,p.stderr
  r=json.loads(p.stdout);r['controller_seconds']=time.perf_counter()-t;r['worker_exit_code']=p.returncode
  (H/'scale-mechanism-check.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
  print(json.dumps({'state':r['state'],'table':r['scale_table_model'],'dense':r['dense_case_ranges'],'seconds':r['controller_seconds'],'caller':r['B2_timed_ELF_selected_caller_identity']},indent=2))
