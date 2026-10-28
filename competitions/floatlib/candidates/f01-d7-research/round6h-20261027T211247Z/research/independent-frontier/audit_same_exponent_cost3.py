"""One selected-caller/negative-cost audit of completed cost3 originals. No rerun."""
from pathlib import Path
from datetime import datetime,timezone
import re,json,hashlib
D=Path(__file__).resolve().parent;R=next(p for p in D.parents if (p/'AGENTS.md').exists())
B=R/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/ci-runs/40590900980'
idx=json.loads((B/'original-artifact-hashes.json').read_bytes());A=B/idx['directory'];pre='diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-runtime-cost3/runtime-cost/'
checked=[]
def read(name):
 key=pre+name;p=A/key;b=p.read_bytes();h=hashlib.sha256(b).hexdigest();assert h==idx['files'][key]['sha256'],key
 checked.append({'path':str(p.relative_to(R)),'sha256':h,'bytes':len(b)});return b
result=json.loads(read('result.json'));assert result['source_sha256']=='4538290d51c47c699e76c73f382c7cb9fc799bde370b05f36fcb3d84222395c4' and result['measurement_complete']
C=read('build-product-0-R22RuntimeCost3Main.c').decode();ASM=read('own-object-0-asm.txt').decode();NM=read('own-object-0-nm.txt').decode();caller=read('caller.lean').decode();flags=json.loads(read('flags-and-link.json'));cpu=read('cpuinfo.txt').decode();read('prepare.json');read('stage-receipt.json');read('build-product-1-R22RuntimeCost3Main.c.o.export.trace');read('build-product-2-r22RuntimeCost3.trace');read('build-product-3-r22RuntimeCost3.rsp')
assert all(flags[k]['equal_after_only_root_target_path_mapping'] for k in ['compile','link','link_response'])
assert 'Bench.Suite.run r22CostSameExponentAdd Submission.mul Submission.sum Submission.bmm' in caller
assert '"sameexp"' in C and '.m_fun = (void*)lp_competition_main___lam__0___boxed' in C
assert 'v___f_6444_ = ((lean_object*)(lp_competition_main___closed__15));' in C
assert 'lp_competition_Bench_Suite_run(v___f_6444_,' in C
assert '.m_fun = (void*)lp_competition_main___lam__2___boxed' in C

def cbody(sym):
 m=re.search(r'LEAN_EXPORT [^;\n]*\b'+re.escape(sym)+r'\([^\n]*\)\{',C);assert m
 level=1;j=m.end()
 while level:
  if C[j]=='{':level+=1
  elif C[j]=='}':level-=1
  j+=1
 return C[m.start():j]+'\n'
def asmfn(sym):
 m=re.search(r'^0+ <'+re.escape(sym)+r'>:\n',ASM,re.M);assert m
 end=ASM.find('\nDisassembly of section ',m.end());return ASM[m.start():end if end!=-1 else len(ASM)]
new=cbody('lp_competition_main___lam__0');old=cbody('lp_competition_main___lam__2')
newasm=asmfn('lp_competition_main___lam__0');oldasm=asmfn('lp_competition_main___lam__2')
newbox=asmfn('lp_competition_main___lam__0___boxed');oldbox=asmfn('lp_competition_main___lam__2___boxed')
canon=lambda x:re.sub(r'lp_competition_main___lam__[02]','ADD_CALLBACK',x)
assert canon(newbox)==canon(oldbox),'Wrapper changed beyond callback name'
for name,s in [('sameexp-selected.c',new),('control-selected.c',old),('sameexp-selected.asm.txt',newasm),('control-selected.asm.txt',oldasm)]:
 (D/name).write_text(s,encoding='utf8',newline='\n')

blocks=[]
for seed in [2220001,2220003]:
 for block,ni,ci in [(0,17,16),(1,18,19)]:
  vals={}
  for variant,order in [('sameexp',ni),('control',ci)]:
   name=f'{seed}-{order}-{variant}'
   log=read(name+'.log').decode();saved=json.loads(read(name+'-rows.json'))
   rows={}
   for line in log.splitlines():
    m=re.fullmatch(r'(\S+) (true|false) ([0-9]+) ([0-9]+)',line)
    if m:rows[m[1]]={'timed':m[2]=='true','best_ns':int(m[3]),'checksum':int(m[4])}
   assert rows==saved and len(rows)==156
   vals[variant]=rows
  assert all(vals['sameexp'][k]['checksum']==vals['control'][k]['checksum'] for k in vals['control'])
  def sums(v):
   groups={};ops={};whole=0
   for k,r in v.items():
    if not r['timed']:continue
    cell=':'.join(k.split(':')[:2]);op=k.split(':')[0];ns=r['best_ns'];groups[cell]=groups.get(cell,0)+ns;ops[op]=ops.get(op,0)+ns;whole+=ns
   return groups,ops,whole
  ng,no,nw=sums(vals['sameexp']);cg,co,cw=sums(vals['control'])
  blocks.append({'seed':seed,'block':block,'whole_ratio':nw/cw,'add_ratio':no['add']/co['add'],'add_cells':{k:ng[k]/cg[k] for k in cg if k.startswith('add:')},'rows_per_process':156,'checksum_match':True})
assert all(r['add_ratio']>1.12 and r['whole_ratio']>1.04 for r in blocks)
sizes={}
for sym in ['lp_competition_main___lam__0','lp_competition_main___lam__2','lp_competition_main___lam__0___boxed','lp_competition_main___lam__2___boxed']:
 m=re.search(r'^\S+ ([0-9a-f]+) \S '+re.escape(sym)+r'$',NM,re.M);assert m;sizes[sym]=int(m[1],16)
out={'verified_at_utc':datetime.now(timezone.utc).isoformat(),'run':40590900980,'source_sha256':result['source_sha256'],'selected_chain':'BENCH_VARIANT=sameexp -> closed12/closed11 string -> closed15 -> main.lam0.boxed -> main.lam0; control -> closed18 -> main.lam2.boxed -> main.lam2','selected_symbols':sizes,'box_wrapper_equal_after_name_mapping':True,'complete_native_hit_path':'0x0..0x23 -> 0xf6..0x115 -> 0x121..0x13e; E0 takes0x132 and E254 takes0x117. Relocated tailjmp at0xf1 is toFloat32.toBits on fallback, not an internal fallthrough.','observed_code':'Accepted scalar path has mask/add/bt/adc/shift/pack and no calls/table reads/FP/heap/data spill. Both control and new entry save rbp,r14,rbx and reserve16 stack bytes. Guard miss adds xor/compare/conditional branch before original decoder path. No branch-counter attribution.','blocks':blocks,'CPU':re.search(r'model name\s*:\s*(.+)',cpu).group(1),'compile_flags_equal_except_owned_target_paths':True,'build_identities':result.get('build_identities'),'checked_files':checked,'scope':'Actual owned object linked into diagnostic timing binary; source, C, ASM and raw logs verified against recovered index. Object/binary digest fields are producer records, not locally rehashed binaries (not retained here). Original25-round gate, public new ADD proof and adoption NOT_RUN.','decision':'PARK exact same-E body and full proof attempt. Do not rerun same body/seeds or expand proof based on leaf arithmetic. Normalization/wider guard needs new independent cost premise.'}
(D/'same-exponent-cost3-audit.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({'checked_files':len(checked),'blocks':blocks,'sizes':sizes,'box_wrapper_equal':True}))
