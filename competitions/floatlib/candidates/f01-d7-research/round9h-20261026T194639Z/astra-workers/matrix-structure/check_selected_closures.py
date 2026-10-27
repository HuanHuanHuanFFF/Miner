"""One exact historical B2 selected caller chain; excludes dead generic wrapper inference."""
from pathlib import Path
from datetime import datetime,timezone
import re,json,hashlib
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
root=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168024176/download-97e5567f5b7c4fc2a261a6d6dac40edc/diagnostics/f01-d7-public-suite/public-suite'
src=root/'inputs/f01-r15-dev-packed-b2-1/Kernel.lean'
cfile=root/'diagnostics/f01-r15-dev-packed-b2-1/candidate-generated-0.c'
sha=lambda b:hashlib.sha256(b).hexdigest()
assert sha(src.read_bytes())=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
raw=cfile.read_bytes();assert sha(raw)=='0e3c1fc9ee2b91c326fffa847a60350031e7260bb860ed8a6f62df5f2eee7268'
c=raw.decode();bodies={}
for m in re.finditer(r'^LEAN_EXPORT [^\n]+?\b(lp_competition_\w+)\([^\n]*\)\{',c,re.M):
 start=m.start();brace=c.find('{',m.start());depth=1;end=brace+1
 while depth:
  if c[end]=='{':depth+=1
  elif c[end]=='}':depth-=1
  end+=1
 bodies[m[1]]=(start,end,c[start:end])
select={
 'B2-output':'Submission_R15PackedB2_output',
 'B2-row-specialization':'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__1',
 'B2-group-specialization':'Fin_foldl_loop___at___00Submission_R15PackedB2_output_spec__0___redArg',
 'B2-emitter-specialization':'Fin_foldl_loop___at___00Submission_R15ThinPairs_output_spec__0',
 'DC-output':'Submission_DirectContinuous_output',
 'DC-row-specialization':'Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__1',
 'DC-emitter-specialization':'Fin_foldl_loop___at___00Submission_DirectContinuous_output_spec__0',
 'DC-generic-row-not-selected':'Submission_DirectContinuous_row___redArg',
 'DC-dispatch':'Submission_bmmBeforeR11Cross',
 'B2-dispatch':'Submission_R15PackedB2_dispatch',
 'public-bmm':'Submission_bmm',
}
entries=[];outdir=H/'closure-evidence';outdir.mkdir(exist_ok=True)
for label,suffix in select.items():
 symbol='lp_competition_'+suffix
 start,end,body=bodies[symbol]
 (outdir/(label+'.c.txt')).write_text(body+'\n')
 entries.append({'label':label,'symbol':symbol,'line_start':c.count('\n',0,start)+1,'line_end':c.count('\n',0,end)+1,'body_sha256':sha(body.encode()),'alloc_closure_sites':body.count('lean_alloc_closure('),'apply_sites':len(re.findall(r'lean_apply_\w+\(',body)),'direct_calls':sorted(set(re.findall(r'\b(lp_competition_\w+)\(',body))-{symbol}),'excerpt':'closure-evidence/'+label+'.c.txt'})
assert all(x['alloc_closure_sites']==0 for x in entries if x['label'] in ('B2-output','B2-row-specialization','B2-group-specialization','B2-emitter-specialization','DC-output','DC-row-specialization','DC-emitter-specialization'))
assert next(x for x in entries if x['label']=='DC-generic-row-not-selected')['alloc_closure_sites']==1
report={'at_utc':datetime.now(timezone.utc).isoformat(),'run':40168024176,'candidate_sha256':sha(src.read_bytes()),'C_source':str(cfile.relative_to(R)),'C_sha256':sha(raw),'entries':entries,'decision':'Reject inference from generic row wrapper to active B2/DC per-row closure allocation; the exact selected historical C has zero closure sites at each row/group/emitter layer. New implementation performance remains empirical, and current timed binary is not supplied by this historical diagnostic.','scope':'Static exact generated-C call chain, not dynamic timing, physical allocation or new-candidate rejection'}
(H/'closure-evidence.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({'run':report['run'],'C_sha256':report['C_sha256'],'functions':[{'name':e['label'],'line':e['line_start'],'closure_sites':e['alloc_closure_sites']} for e in entries]}))
