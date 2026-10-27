"""Read-only original-byte binding for the two independent prefix diagnostics.

No CI, Lean or candidate mutation. Scope witnesses are reported for R's causal
review; this script never activates the conditional proof or claims full proof.
"""
from pathlib import Path
import argparse,json,hashlib,re
D=Path(__file__).resolve().parent
ROOTS=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec']
B2='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
EXPECTED={'import-only':('239175fe9907a272f0b9816f700dbc310b5b3e33ffca567fde220339d93ffa70',18),
          'quotient-only':('014acd413d37ee012bdc55fb813591815ccb5dce0adf09f27dac9a17fd68573d',1341)}
MATH_EXPECTED={'math-outlet':('2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266',32332)}
H=lambda b:hashlib.sha256(b).hexdigest()
def read_json(p):return json.loads(p.read_bytes())
def inspect(root,check_original,math=False):
 top=read_json(root/'summary.json')
 assert top['schema_version']==2 and top['kernel_sha256']==B2
 assert top['mode']==('SINGLE_COMPLETE_MATH_MODULE' if math else 'INDEPENDENT_COMPLETE_PREFIX_PROCESSES')
 check_original(root/'summary.json')
 rows=[]
 for label,(expected,size) in (MATH_EXPECTED if math else EXPECTED).items():
  p=root/label;r=read_json(p/'summary.json')
  assert r['prefix']==label and r['schema_version']==2
  for name in ['summary.json','source.lean','output.raw','resources.json']:
   check_original(p/name)
  source=(p/'source.lean').read_bytes();raw=(p/'output.raw').read_bytes();res=(p/'resources.json').read_bytes()
  assert len(source)==size==r['source_bytes'] and H(source)==expected==r['source_sha256']
  assert len(raw)==r['output_bytes'] and H(raw)==r['output_sha256'] and H(res)==r['sampling_sha256']
  audit=None
  if (p/'helper-audit.json').exists():
   for name in ['helper-audit.json','helper-audit-source.lean','helper-axioms.raw']:check_original(p/name)
   audit=read_json(p/'helper-audit.json')
   assert audit['accepted'] and audit['kernel_replay'] and audit['expected_count']==4 and audit['names']==ROOTS
  assert (r['exit_code']==0)==r['typecheck_process_complete']
  samples=json.loads(res);groups={}
  for sample in samples:
   for group,metrics in sample.get('groups',{}).items():
    unit=group.rsplit('/',1)[-1]
    if not re.fullmatch(r'run-[A-Za-z0-9_.-]+\.scope',unit):continue
    item=groups.setdefault(unit,{'paths':set(),'peak':0,'max':set(),'events':[]})
    item['paths'].add(group)
    if metrics.get('memory.peak','').isdigit():item['peak']=max(item['peak'],int(metrics['memory.peak']))
    item['max'].add(metrics.get('memory.max','UNKNOWN'))
    events={}
    for line in metrics.get('memory.events','').splitlines():
     pair=line.split()
     if len(pair)==2 and pair[1].isdigit():events[pair[0]]=int(pair[1])
    item['events'].append(events)
  scopes=[]
  for scope in r.get('systemd_scopes',[]):
   props=dict(line.split('=',1) for line in scope.get('properties','').splitlines() if '=' in line)
   g=groups.get(scope['unit'])
   scopes.append({'unit':scope['unit'],'properties':props,'sampling_association':g is not None,
    'sampled_peak':g['peak'] if g else None,'sampled_max':sorted(g['max']) if g else [],
    'max_sampled_oom_kill':max((x.get('oom_kill',0) for x in g['events']),default=0) if g else None,
    'raw_scope_oom_witness':props.get('Result')=='oom-kill' and g is not None})
  rows.append({'prefix':label,'source_sha256':expected,'state':r['state'],'exit_code':r['exit_code'],
   'typecheck_process_complete':r['typecheck_process_complete'],'elapsed_seconds':r.get('elapsed_seconds'),
   'output_bytes':len(raw),'output_sha256':H(raw),'lean_error_lines':[x for x in raw.decode(errors='replace').splitlines() if 'error:' in x][:12],
   'sample_count':len(samples),'observed_sampled_scopes':sorted(groups),'scopes':scopes,
   'base_audit_copy_present':audit is not None})
 if math:
  b=rows[0]
  if b['exit_code']==0:decision='MATH_MODULE_TYPECHECK_EXIT_ZERO: new module replay/48root audit/full candidate still NOT_RUN'
  elif any(s['raw_scope_oom_witness'] for s in b['scopes']):decision='MATH_MODULE_SCOPE_OOM_WITNESS: verify target association; not a mathematical counterexample'
  elif b['lean_error_lines']:decision='MATH_MODULE_LEAN_ERROR: use actual goals for proof-only repair'
  else:decision='MATH_MODULE_INCOMPLETE_CAUSE_UNKNOWN'
  return {'base_B2_audit':top['base_B2_audit'],'prefixes':rows,'next_decision':decision,
   'limits':'Exact2177 single-module process only. Carrier four-root audit is not new module48roots; wholefa652 remains unaccepted.'}
 a,b=rows
 if a['exit_code']!=0:decision='IMPORT_CONTROL_NOT_PASS: do not activate resource1'
 elif b['exit_code']==0:decision='BOTH_PREFIXES_COMPLETE: original quotient not reproduced; resource1 remains HOLD'
 elif any(s['raw_scope_oom_witness'] for s in b['scopes']):decision='QUOTIENT_SCOPE_OOM_WITNESS: R must verify target association before release'
 elif b['lean_error_lines']:decision='QUOTIENT_LEAN_ERROR: use actual goals, not speculative resource rewrite'
 else:decision='QUOTIENT_INCOMPLETE_CAUSE_UNKNOWN: keep resource1 HOLD'
 return {'base_B2_audit':top['base_B2_audit'],'prefixes':rows,'next_decision':decision,
  'limits':'Complete-prefix process evidence only; no full1180/public proof or performance. RSS sum is never used as OOM proof.'}
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--run-dir',type=Path);ap.add_argument('--mock-root',type=Path);ap.add_argument('--math',action='store_true');args=ap.parse_args()
 assert bool(args.run_dir)!=bool(args.mock_root),'choose exactly one mode'
 if args.mock_root:
  result=inspect(args.mock_root,lambda p:None,args.math);result['state']='MOCK_ONLY_NO_ORIGINAL_BINDING';print(json.dumps(result,indent=2));return
 run=args.run_dir.resolve();idx=read_json(run/'original-artifact-hashes.json');base=run/idx['directory'];checked=[]
 def check(p):
  rel=p.relative_to(base).as_posix();m=idx['files'][rel];b=p.read_bytes()
  assert len(b)==m['bytes'] and H(b)==m['sha256'],str(p)
  checked.append({'path':rel,'bytes':len(b),'sha256':H(b)})
 candidate='f01-r19-dev-math-outlet-isolation1' if args.math else 'f01-r19-dev-prefix-isolation1'
 folder='math-isolation' if args.math else 'prefix-isolation'
 choices=[base/k for k in idx['files'] if k.endswith('/'+candidate+'/'+folder+'/summary.json')]
 assert len(choices)==1,choices
 inputs=[base/k for k in idx['files'] if k.endswith('/inputs/'+candidate+'/Kernel.lean')]
 assert len(inputs)==1,inputs
 check(inputs[0]);assert H(inputs[0].read_bytes())==B2
 result=inspect(choices[0].parent,check,args.math);result.update(state='ORIGINAL_BYTES_BOUND',run=run.name,verified_files=checked)
 out=D/(('math-review-' if args.math else 'prefix-review-')+run.name+'.json');out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8',newline='\n')
 print(json.dumps({k:result[k] for k in ['state','run','next_decision']},indent=2))
if __name__=='__main__':main()
