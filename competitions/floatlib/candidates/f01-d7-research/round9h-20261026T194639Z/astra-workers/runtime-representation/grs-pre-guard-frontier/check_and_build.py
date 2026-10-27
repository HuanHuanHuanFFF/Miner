"""One hard-bound pre-guard discriminator, no threshold sweep/Lean/CI."""
from pathlib import Path
from types import SimpleNamespace
import ast,datetime,difflib,hashlib,json
HERE=Path(__file__).resolve().parent;W=HERE.parent;ROUND=W.parent.parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
H=lambda b:hashlib.sha256(b).hexdigest();M=(1<<32)-1;B=1<<23

def load_defs(p,names,ns):
 tree=ast.parse(p.read_text());nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef) and (names is None or n.name in names)]
 exec(compile(ast.Module(body=nodes,type_ignores=[]),str(p),'exec'),ns)

def binding(p):
 b=p.read_bytes();return {'path':str(p.relative_to(ROOT)).replace('\\','/'),'bytes':len(b),'sha256':H(b)}

def coords(u,v):
 eu,ev=(u>>23)&255,(v>>23)&255
 if not(1<=eu<=254 and 1<=ev<=254):return None
 hi,lo,eh,el=(v,u,ev,eu) if (u&0x7fffffff)<(v&0x7fffffff) else (u,v,eu,ev)
 x=((hi&0x7fffff)|B)<<3;y=((lo&0x7fffff)|B)<<3;d=eh-el
 j=(y>>d)|int((y&((1<<d)-1))!=0) if d<32 else 1
 t=x+j if ((u^v)&0x80000000)==0 else x-j
 assert t==0 or 4<=t<=(1<<28)-16
 return hi,eh,d,t

def main():
 rootp=ROUND/'astra-grs-add-model.py';modelp=W/'grs-add-cost-frontier/check_runtime_model.py'
 genp=ROUND.parent/'round8h-20261024T190259Z/astra-public-input-domain.py'
 rootns={'BASE':B,'MASK':M};load_defs(rootp,{'rne','exact_add_normal'},rootns)
 ns={'B':B,'M':M,'q':SimpleNamespace(rne=rootns['rne'])};load_defs(modelp,{'numeric_bits','typed'},ns)
 g={'U32':M,'U64':(1<<64)-1};load_defs(genp,None,g)
 def check(u,v):
  c=coords(u,v)
  if c is None:return False
  hi,eh,d,t=c
  if t==0:value=0
  else:
   mid=ns['numeric_bits'](t);ne=mid>>23;assert 129<=ne<=154
   if not25(eh):return False
   assert 1<=ne+eh-153<=254
   delta=((((eh-153)&M)<<23)+(hi&0x80000000))&M
   value=(mid+delta)&M
  assert value==ns['typed'](u,v)==rootns['exact_add_normal'](u,v)
  return True
 def not25(eh):return not(25<=eh<=253)
 directed=[]
 def word(e,m,negative=False):return (int(negative)<<31)|(e<<23)|(m-B)
 for eh in (24,25,253,254):
  for sign in (False,True):
   u=word(eh,B,sign);v=word(eh-1,2*B-1,not sign)
   hit=check(u,v);directed.append({'kind':'minimumT','u':hex(u),'v':hex(v),'T':4,'eh':eh,'accepted':hit})
   u=word(eh,2*B-1,sign);v=u
   hit=check(u,v);directed.append({'kind':'maximumT','u':hex(u),'v':hex(v),'T':(1<<28)-16,'eh':eh,'accepted':hit})
 for eh in (1,24,25,253,254):
  u=word(eh,B);v=u^0x80000000;assert check(u,v)
  directed.append({'kind':'zero','u':hex(u),'v':hex(v),'T':0,'eh':eh,'accepted':True})
 previous=json.loads((W/'grs-add-threegroup-threshold/results.json').read_text());results=[]
 for r in previous['runs']:
  planp=ROOT/r['bindings'][0]['path'];assert H(planp.read_bytes())==r['bindings'][0]['sha256']
  plan=json.loads(planp.read_text());cellcounts={k:{'sampled':0,'hit':0,'work_hit':0.,'new_old_hit':0} for k in r['cells']}
  for c in plan['cases']:
   if c['kernel']!='add' or not c['timed']:continue
   n=min(256,c['work']);hit=0;old=0
   for z in range(n):
    lo,hi=z*c['work']//n,(z+1)*c['work']//n;i=lo+g['word'](c['seed'],z,63)%(hi-lo)
    u=g['element'](c,i,0,31);v=g['partner'](c,i,u)
    hit+=check(u,v);old+=ns['typed'](u,v) is not None
   cell=':'.join(c['name'].split(':')[:2]);cc=cellcounts[cell]
   cc['sampled']+=n;cc['hit']+=hit;cc['new_old_hit']+=old;cc['work_hit']+=c['work']*hit/n
  f=0
  for k,c in cellcounts.items():
   c['work_hit_rate']=c['work_hit']/r['cells'][k]['work'];c['whole_cost_proxy']=c['work_hit_rate']*r['cells'][k]['B2_whole_cost_share_proxy'];f+=c['whole_cost_proxy']
  assert sum(c['new_old_hit'] for c in cellcounts.values())==r['counts']['new_hit']
  results.append({'run':r['run'],'sampled':sum(c['sampled'] for c in cellcounts.values()),'hit':sum(c['hit'] for c in cellcounts.values()),'old_postguard_hit':r['counts']['new_hit'],'Fproxy':f,'required_drop_for10pct_zero_miss_overhead':.1/f,'cells':cellcounts})
 oldp=W/'grs-add-type-repair1/Runtime-grs32-add-type-repair1.lean.inc';old=oldp.read_bytes();assert H(old)=='b4625c0f6891e1a0edcf805138cca0a82d637b977f41f0dcc5e30d8dcffe0304'
 before='''    else
      let mid := t.toFloat32.toBits
      let e := (mid >>> 23) + eh - (153 : UInt32)
      if e - 1 ≤ (253 : UInt32) then
        R7W02.fromRaw ((hi &&& (0x80000000 : UInt32)) ||| (e <<< 23) ||| (mid &&& 0x7fffff))
      else fallback x y'''
 after='''    else if eh - (25 : UInt32) ≤ (228 : UInt32) then
      let delta := ((eh - (153 : UInt32)) <<< 23) + (hi &&& (0x80000000 : UInt32))
      let mid := t.toFloat32.toBits
      R7W02.fromRaw (mid + delta)
    else fallback x y'''
 text=old.decode();assert text.count(before)==1;new=text.replace(before,after,1)
 assert new.replace(after,before,1)==text
 frag=HERE/'Runtime-grs32-pre-guard.lean.inc';frag.write_text(new,encoding='utf-8',newline='\n')
 basep=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean';base=basep.read_bytes();assert H(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
 kernel=HERE/'Kernel-grs32-pre-guard.lean';kernel.write_bytes(base+new.encode())
 roots=(W/'grs-add-type-repair1/HelperAudit-grs-add-runtime-repair1.lean.inc').read_bytes();(HERE/'HelperAudit-grs32-pre-guard.lean.inc').write_bytes(roots)
 (HERE/'inverse.patch').write_text(''.join(difflib.unified_diff(new.splitlines(True),text.splitlines(True),fromfile='pre-guard/Runtime.lean.inc',tofile='7737/Runtime.lean.inc')),encoding='utf-8',newline='\n')
 result={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'ONE_PRE_GUARD_COST_DISCRIMINATOR_NOT_RUN','fixed_domain':'T0 unchanged; nonzero requires25<=eBig<=253 from universal4<=T<=2^28-16, not fitted threshold',
  'directed_boundaries':directed,'same_old_three_groups':results,'all_accepted_agree_with_old_typed_and_integer_oracle':True,
  'generator_Lean_alignment':'UNKNOWN_NOT_INDEPENDENTLY_VALIDATED','coverage_cost_proxy':'Same previously exposed256/case samples; equal oldcost within cell; not timing or strict upper bound',
  'fragment':binding(frag),'kernel':binding(kernel),'inputs':[binding(oldp),binding(basep),binding(rootp),binding(modelp),binding(genp)],
  'inverse_exact':True,'original7737_unchanged':H(oldp.read_bytes())=='b4625c0f6891e1a0edcf805138cca0a82d637b977f41f0dcc5e30d8dcffe0304',
  'public_dispatch':'OriginalB2 remainspublic; same7 roots auditoldspecs+3definitions, no newADD proof',
  'cost_hypothesis':'No fallback after codec; only delta sourcevalue needed after call. Actual saved registers/spills stillUNKNOWN untilcompiledcaller.',
  'proof':'Paper/finite model only; RTO originalADD bridge and newTbound/modular-repack Lean proof NOT_RUN','statement':'NOT_RUN','codegen':'NOT_RUN','performance':'UNKNOWN','CI_dispatched':False}
 (HERE/'manifest.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
 print(json.dumps({'fragment':result['fragment'],'kernel':result['kernel'],'runs':[{k:v for k,v in r.items() if k!='cells'} for r in results],'manifest_sha':H((HERE/'manifest.json').read_bytes())},indent=2))

if __name__=='__main__':main()
