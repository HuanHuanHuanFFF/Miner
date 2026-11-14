"""Prefreeze released-source operator binding/proof inventory; no performance inference."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;sys.path.insert(0,str(HERE/'crossboard'));import dependency_census as dc
GROUP={'core':['sum','dot'],'dense':['linear','gemm'],'conv':['conv2d','depthwise'],'elem':['avgpool','maxpool','addRelu','scaleShift'],'norm':['rmsnorm','layernorm']}
SPECS={x+'Spec':x for v in GROUP.values()for x in v}
def fields(s,ds,n):
 body=ds[n]['body'];return{m.group(1):m.group(2).strip()for m in re.finditer(r'(?m)^\s*(core|dense|conv|elem|norm):=(.*)$',body)}
def tuples(x):
 assert x.startswith('⟨')and x.endswith('⟩'),x
 return[x.strip()for x in x[1:-1].split(',')]
def bindings(s,ds):
 base=fields(s,ds,'kernels0');final=fields(s,ds,'kernels');b={k:tuples(v)for k,v in base.items()};out={}
 for group,names in GROUP.items():
  e=final[group];cells=b[group]if e=='kernels0.'+group else tuples(e)
  for i,expr in enumerate(cells):
   match=re.fullmatch(r'kernels0\.(\w+)\.(\w+)',expr)
   if match:
    g,a=match.groups();j=int(a)-1 if a.isdigit()else GROUP[g].index(a);expr=b[g][j]
   out[group+'.'+names[i]]=expr
 return out

def main():
 rows=[]
 for sid in [5,12,13,19,23,27]:
  f=dc.ROOT/f'submission{sid}-Kernel.lean';raw=f.read_bytes();s=raw.decode();ds=dc.decls(s);runtime={n:d for n,d in ds.items()if d['kind']in['def','structure','abbrev']};g=dc.graph(s,ds);gr={n:g[n]&runtime.keys()for n in runtime};bind=bindings(s,ds);roots=set()
  for exp in bind.values():roots.update(set(re.findall(r"[\w.'?!]+",exp))&runtime.keys())
  reachable=dc.closure(roots,gr)
  eq=[]
  for name,d in ds.items():
   if d['kind']not in['lemma','theorem']:continue
   stmt=d['body'].split(':=',1)[0]
   for m in re.finditer(r":\s*([A-Za-z_][\w'?!]*)\s*=\s*(sumSpec|dotSpec|linearSpec|gemmSpec|conv2dSpec|depthwiseSpec|avgpoolSpec|maxpoolSpec|addReluSpec|scaleShiftSpec|rmsnormSpec|layernormSpec)\b",stmt):
    target,spec=m.groups();direct=[k for k,v in bind.items()if v==target]
    eq.append({'lemma':name,'function':target,'spec':spec,'proof_line':d['line'],'proof_sha256':hashlib.sha256(d['body'].encode()).hexdigest(),'function_bytes':len(ds[target]['body'].encode())if target in ds else None,'direct_final_fields':direct,'runtime_transitively_reachable':target in reachable})
  desc={}
  for field,expr in bind.items():
   tokens=set(re.findall(r"[\w.'?!]+",expr));local=sorted(tokens&runtime.keys());desc[field]={'expression':expr,'local_runtime_roots':{n:{'line':runtime[n]['line'],'bytes':len(runtime[n]['body'].encode()),'sha256':hashlib.sha256(runtime[n]['body'].encode()).hexdigest()}for n in local},'direct_imported_spec_or_wrapper':not local or expr.split()[0]not in runtime}
  report=f.parent.parent/f'submission{sid}-report.raw';meta=None
  if report.exists():
   r=json.loads(report.read_bytes());sub=r['submission'];assert sub['source_sha256']==hashlib.sha256(raw).hexdigest();meta={'report_sha256':hashlib.sha256(report.read_bytes()).hexdigest(),'proof_state_at_saved_report':sub.get('proof_state'),'source_available_at_saved_report':sub.get('source_available')}
  rows.append({'submission':sid,'source_sha256':hashlib.sha256(raw).hexdigest(),'source_bytes':len(raw),'saved_report':meta,'resolved_fields':desc,'operator_equality_lemmas':eq,'proved_roots_not_runtime_reachable':[x for x in eq if not x['runtime_transitively_reachable']],'runtime_reachability_limit':'Lexicalnamedruntimegraph; conservativefalsepositives possible, notLean callgraphproof'})
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'STATIC_PROVED_INTERFACE_BINDING_INVENTORY_NOT_PERFORMANCE_OR_NEW_GATE','official_proof_identity':'3a69968c7210ab18b325047e518ddfa942e642e21268a241e8693b075377bee6','floatlib_commit':'0d91825727839f597fd06b22fdd038ea21480f0c','scope':'Onlybefore9-freezereleasedsourcecache; no9inputs/results','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'rows':rows,'limits':['Sourcecorrectdeclaration existence isnotanindependentfreshgate','Equalitysearchcoversdirect function=Spec statements, notallpointwisestatements or tacticderivedtheorems','Reachabilitymayoverapproximate vialocalnames; absenceofnewopportunity notmathematicalexhaustiveness','No currentchampion sourceavailable, no speedfromsource-size/hash']};(HERE/'operator-binding-matrix.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps([{'submission':r['submission'],'fields':{k:v['expression']for k,v in r['resolved_fields'].items()},'unused_proved_roots':r['proved_roots_not_runtime_reachable']}for r in rows]))
if __name__=='__main__':main()
