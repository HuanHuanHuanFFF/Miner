"""Independent CI16 raw log/source/C/ASM audit. No gate/parser import or input generation."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,shlex
H=Path(__file__).resolve().parent;R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
RUN=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40436948264'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
def save(p,x):p.write_bytes((json.dumps(x,indent=2,ensure_ascii=False)+'\n').encode())
idx=RUN/'original-artifact-hashes.json';inv=json.loads(idx.read_text());RAW=RUN/inv['directory']
assert inv['artifact']['workflow_run']['head_sha']=='a6c829564d4964eee6319b04141f8598a3e8e24c'
total=0
for name,x in inv['files'].items():
 p=RAW/name;assert p.stat().st_size==x['bytes']and sha(p)==x['sha256'],name;total+=x['bytes']
assert {p.relative_to(RAW).as_posix()for p in RAW.rglob('*')if p.is_file()}==set(inv['files'])
assert len(inv['files'])==150
DATA=RAW/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-add-cost1/add-cost'
manifest_path=R/'competitions/floatlib/candidates/f01-r19-dev-add-cost1/manifest.json';manifest=json.loads(manifest_path.read_text())
assert sha(manifest_path)=='ada78534accd40265ea375122e72969152af022ffa05c19fa1b671e72eed5ff6'
for x in manifest['components']:
 p=R/x['path'];assert sha(p)==x['sha256']and p.stat().st_size==x['bytes']
source=RAW/'diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r19-dev-add-cost1/Kernel.lean'
assert sha(source)==manifest['candidate_sha256']=='d3c550da05a3e91b5b037bed77623545dbe72af385d826ebc73236d2ed7ec2b5'
assert (DATA/'caller.lean').read_bytes()==(H.parent/'R19AddCostMain.lean').read_bytes()
save(H/'originals.json',dict(run=40436948264,source_commit=inv['artifact']['workflow_run']['head_sha'],index_sha256=sha(idx),files=len(inv['files']),bytes=total,manifest_sha256=sha(manifest_path),source_sha256=sha(source),scope='Original archived bytes verified; current frozen manifest separately verified, not mislabelled as archived'))
def parse(path,plan):
 expected={c['name']:c for c in plan['cases']};rows={};assert len(expected)==156
 for line in path.read_text().splitlines():
  m=re.fullmatch(r'(\S+) (true|false) (\d+) (\d+)',line)
  if not m:continue
  n,t,ns,cs=m.groups();t=t=='true';ns=int(ns);cs=int(cs)
  assert n in expected and n not in rows and t==expected[n]['timed']and (ns>0 if t else ns==0)
  rows[n]=dict(timed=t,best_ns=ns,checksum=cs)
 assert set(rows)==set(expected)and sum(v['timed']for v in rows.values())==152
 return rows
def totals(rows,plan):
 out={op:sum(rows[c['name']]['best_ns']for c in plan['cases']if c['timed']and c['kernel']==op)for op in('add','mul','sum','bmm')}
 out['whole']=sum(out.values());assert out['whole']==sum(r['best_ns']for r in rows.values());return out
stored=json.loads((DATA/'result.json').read_text());assert stored['complete']and stored['source_sha256']==sha(source)
samples=[];blocks=[];casepairs=[];allpairs=[]
for seed in(1927003,1927005):
 plan=json.loads((DATA/f'plan-{seed}.json').read_text());cases={c['name']:c for c in plan['cases']};subset=[]
 assert sum(c['kernel']=='add'and c['timed']for c in plan['cases'])==42
 for order,variant in enumerate(('control','guarded','guarded','control')):
  stem=f'{seed}-{order}-{variant}';p=DATA/(stem+'.log');rows=parse(p,plan)
  assert rows==json.loads((DATA/(stem+'-rows.json')).read_text())
  meta=stored['runs'][len(samples)]
  assert (meta['seed'],meta['order'],meta['variant'],meta['exit_code'])==(seed,order,variant,0)
  assert json.loads(meta['environment']['BENCH_PLAN'])==plan and meta['environment']['BENCH_VARIANT']==variant
  assert meta['environment']['BENCH_PAIRS']=='500000'and meta['environment']['BENCH_INNER']=='3'
  assert meta['argv'][:3]==['taskset','-c','0']and meta['argv'][-1].endswith('/bin/r19AddCost')and meta['log_sha256']==sha(p)
  subset.append(rows);samples.append(dict(seed=seed,order=order,variant=variant,rows=156,timed_rows=152,process_seconds=meta['seconds'],ns=totals(rows,plan)))
 assert all(all(subset[0][n]['checksum']==v[n]['checksum']for n in subset[0])for v in subset[1:])
 for block,(ci,gi)in enumerate(((0,1),(3,2))):
  ct,gt=totals(subset[ci],plan),totals(subset[gi],plan);ops={}
  for op in('add','mul','sum','bmm','whole'):
   original=stored['pairs'][0 if seed==1927003 else 1][f'block_{block}'][op]
   assert original['control_ns_sum']==ct[op]and original['guarded_ns_sum']==gt[op]and original['guarded_over_control']==gt[op]/ct[op]
   ops[op]=dict(control_ns=ct[op],guarded_ns=gt[op],ratio=gt[op]/ct[op],delta_ns=gt[op]-ct[op])
  blockrec=dict(seed=seed,block=block,control_order=ci,guarded_order=gi,operations=ops)
  for name,c in cases.items():
   if not c['timed']:continue
   cn=subset[ci][name]['best_ns'];gn=subset[gi][name]['best_ns'];delta=gn-cn
   item=dict(seed=seed,block=block,name=name,kernel=c['kernel'],control_ns=cn,guarded_ns=gn,ratio=gn/cn,delta_ns=delta)
   allpairs.append(item)
   if c['kernel']=='add':
    item=dict(item,label=name.split(':')[1],eligible_fraction='UNKNOWN',
     control_whole_share=cn/ct['whole'],guarded_whole_share=gn/gt['whole'],add_delta_contribution=delta/ops['add']['delta_ns'],whole_delta_contribution=delta/ops['whole']['delta_ns'],
     plan_metadata={k:v for k,v in c.items()if k not in('name','kernel','timed')})
    casepairs.append(item)
  blockrec['largest_add_delta_cases']=sorted([x for x in casepairs if x['seed']==seed and x['block']==block],key=lambda x:x['delta_ns'],reverse=True)[:8]
  blocks.append(blockrec)
aggregate={}
for op in('add','mul','sum','bmm','whole'):
 cn=sum(b['operations'][op]['control_ns']for b in blocks);gn=sum(b['operations'][op]['guarded_ns']for b in blocks)
 aggregate[op]=dict(control_ns=cn,guarded_ns=gn,ratio=gn/cn,delta_ns=gn-cn)
bycase=[]
for name in sorted({x['name']for x in casepairs}):
 xs=[x for x in casepairs if x['name']==name];assert len(xs)==4
 cn=sum(x['control_ns']for x in xs);gn=sum(x['guarded_ns']for x in xs);delta=gn-cn
 bycase.append(dict(name=name,label=name.split(':')[1],control_ns=cn,guarded_ns=gn,ratio=gn/cn,delta_ns=delta,
   add_delta_contribution=delta/aggregate['add']['delta_ns'],whole_delta_contribution=delta/aggregate['whole']['delta_ns'],block_ratios=[x['ratio']for x in xs],eligible_fraction='UNKNOWN'))
bylabel=[]
for label in sorted({x['label']for x in casepairs}):
 xs=[x for x in casepairs if x['label']==label];cn=sum(x['control_ns']for x in xs);gn=sum(x['guarded_ns']for x in xs)
 bylabel.append(dict(label=label,case_block_pairs=len(xs),control_ns=cn,guarded_ns=gn,ratio=gn/cn,delta_ns=gn-cn,eligible_fraction='UNKNOWN'))
assert len(samples)==8 and len(blocks)==4 and len(casepairs)==168 and len(bycase)==42 and len(allpairs)==608
save(H/'raw-recomputed.json',dict(samples=samples,blocks=blocks,aggregate=aggregate,add_case_block_pairs=casepairs,add_cases_pooled=sorted(bycase,key=lambda x:x['delta_ns'],reverse=True),add_labels=bylabel,all608_case_pairs=allpairs,scope='All raw samples retained. Sums of original full case pass ns; pooled four-block description only, not score or stable cross-run result. Labels are measured case names, eligible fractions UNKNOWN.'))
cpath=DATA/'actual-new-main.c';ctext=cpath.read_text();assert cpath.read_bytes()==(DATA/'build-product-0-R19AddCostMain.c').read_bytes()
assert 'diagnosticEntry'not in ctext
def cbody(name):
 m=re.search(r'^LEAN_EXPORT[^;\n]*\b'+name+r'\([^\n]*\)\{',ctext,re.M);assert m
 a=m.start();i=ctext.index('{',a);depth=1;j=i+1
 while depth:depth+=(ctext[j]=='{')-(ctext[j]=='}');j+=1
 s=ctext[a:j];return dict(name=name,start_line=ctext.count('\n',0,a)+1,end_line=ctext.count('\n',0,j)+1,body=s)
for name in('lp_competition_r19CostControlAdd','lp_competition_r19CostGuardedAdd','lp_competition_r19CostControlAdd___boxed','lp_competition_r19CostGuardedAdd___boxed','_lean_main'):
 b=cbody(name);(H/(name+'.c.txt')).write_bytes((b['body']+'\n').encode())
asm=(DATA/'own-object-0-asm.txt').read_text();functions={}
matches=list(re.finditer(r'^([0-9a-f]+) <([^>]+)>:\n',asm,re.M))
for i,m in enumerate(matches):
 s=asm[m.start():(matches[i+1].start()if i+1<len(matches)else len(asm))]
 functions[m.group(2)]=s
for name in('lp_competition_r19CostControlAdd','lp_competition_r19CostGuardedAdd','lp_competition_r19CostControlAdd___boxed','lp_competition_r19CostGuardedAdd___boxed'):
 (H/(name+'.asm.txt')).write_bytes(functions[name].encode())
save(H/'source-bindings.json',dict(c_sha256=sha(cpath),asm_sha256=sha(DATA/'own-object-0-asm.txt'),caller_sha256=sha(DATA/'caller.lean'),C_scope='Actual built/measured new Main object; object/binary not exported, their unchanged identity is remote recorded evidence',C_functions=[{k:v for k,v in cbody(name).items()if k!='body'}for name in('lp_competition_r19CostControlAdd','lp_competition_r19CostGuardedAdd','_lean_main')]))
print(json.dumps(dict(original_files=len(inv['files']),original_bytes=total,aggregate=aggregate,blocks=[dict(seed=b['seed'],block=b['block'],ratios={op:x['ratio']for op,x in b['operations'].items()})for b in blocks],largest_add_cases=sorted(bycase,key=lambda x:x['delta_ns'],reverse=True)[:8],labels=bylabel),indent=2))
