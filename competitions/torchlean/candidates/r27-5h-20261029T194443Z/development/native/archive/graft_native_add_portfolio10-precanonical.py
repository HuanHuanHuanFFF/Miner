"""Independent pre9 nativeAdd/Mixer portfolio, keeping all12 actual obligations."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[1];C=BASE/'research/board-frontier'
def sha(x):return hashlib.sha256(x).hexdigest()
def load(path,name):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def once(s,a,b):assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def build(raw23,raw27):
 assert sha(raw23)=='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
 assert sha(raw27)=='f92ee2c9a29de78dc434ad158b7141c0e4b5a67a5a198a353d59a4703481aa67'
 first=load(C/'build_gemm27_on_public23_v2.py','r27_add_gemm').transform(raw23,23,'gemm27-all-positive-k',donor_raw=raw27)
 assert sha(first)=='6fe5feb6cf0b919a9700f5f05264b1e98e24d7ee74b9d2853c1e55be866d4ada'
 p=load(C/'build_gemm27_on_public23.py','r27_add_decls')
 cuts=json.loads((C/'MIXER-ADD-SPACE-CUTS.json').read_text(encoding='utf-8'))
 premise=json.loads((C/'MIXER-ADD-PREMISE.json').read_text(encoding='utf-8'))
 source=first.decode();donor=raw27.decode();dd=p.declarations(donor);base=p.declarations(source)
 removed=[]
 for row in premise['drop_RMS_budget_only']['removed']:
  name=row['name'];assert name in base
  piece=base[name];assert source.count(piece)==1
  source=source.replace(piece+'\n','',1);removed.append({'name':name,'bytes':len(piece.encode())})
 source=once(source,'norm:=⟨Ybb2,MYbc⟩','norm:=⟨kernels0.norm.rmsnorm,MYbc⟩')
 source=once(source,'ZcC,Zc0Q,T4b,Zdt]','ZcC,Zc0Q,W1,Zdt]')
 order={m.group(1):m.start() for m in p.DECL.finditer(donor)}
 names=sorted(cuts['new_names'],key=lambda n:order[n]);parts=[]
 for name in names:
  assert name not in base,name
  piece=cuts['proposed_owned_bridge_statements'].get(name,dd[name])
  parts.append(piece)
 closure='\n'.join(parts)+'\n'
 aliases_d=p.aliases(donor);aliases_b=p.aliases(source)
 used=set(re.findall(r"[\w'?!]+",closure))&aliases_d.keys()
 differences={n:[aliases_d[n],aliases_b.get(n)] for n in used if aliases_d[n]!=aliases_b.get(n)}
 groups={}
 for alias,(qualified,_) in differences.items():
  namespace,name=qualified.rsplit('.',1);groups.setdefault(namespace,[]).append((name,alias))
 opens='\n'.join('open '+ns+' renaming '+' '.join(name+'->'+alias for name,alias in items) for ns,items in groups.items())+'\n'
 source=once(source,'def kernels:Kernels where',opens+closure+'\ndef kernels:Kernels where')
 source=once(source,'elem:=kernels0.elem','elem:=⟨kernels0.elem.avgpool,kernels0.elem.maxpool,Ybf,kernels0.elem.scaleShift⟩')
 # Existing aliases may compact only proof declarations; no application whitespace rewrite.
 comp=load(HERE/'frozen_compact_public23.py','r27_add_compact');comp.PIN=sha(source.encode())
 final,changes,_=comp.transform(source.encode(),'proof')
 # Squeeze only horizontal spaces around proof punctuation. Keep all function
 # application/binder parentheses and line indentation, unlike failed9654.
 text=final.decode();saved=0
 for match,end in reversed(comp.ranges(text,comp.PROOF)):
  old=text[match.start():end];new=[]
  for line in old.splitlines(keepends=True):
   indent=line[:len(line)-len(line.lstrip(' \t'))];body=line[len(indent):]
   mask=comp.masked(body);pieces=[];pos=0
   for mm in re.finditer(r'[ \t]*([,:;])[ \t]*',body):
    op=mm.start(1)
    if mask[op]!=body[op]:continue
    pieces.extend([body[pos:mm.start()],mm.group(1)]);pos=mm.end()
   pieces.append(body[pos:]);new.append(indent+''.join(pieces))
  new=''.join(new);saved+=len(old.encode())-len(new.encode())
  text=text[:match.start()]+new+text[end:]
 final=text.encode()
 text=final.decode()
 refs={n:len(re.findall(r"(?<![\w'?!])"+re.escape(n)+r"(?![\w'?!])",text)) for n in [r['name'] for r in removed]}
 assert not any(refs.values()),refs
 assert len(final)<=256000,(len(final),differences)
 assert text.count('theorem correct:Obligation kernels:=')==1
 return final,{'removed_RMS_exclusive':removed,'removed_reference_counts':refs,'native_add_closure_bytes':len(closure.encode()),'alias_differences_locally_opened':differences,'late_open_bytes':len(opens.encode()),'extra_proof_alias_changes':len(changes),'proof_horizontal_punctuation_bytes_saved':saved}
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--source',type=Path,required=True);p.add_argument('--donor',type=Path,required=True);p.add_argument('--receipt',type=Path,required=True)
 a=p.parse_args();result,meta=build(a.source.read_bytes(),a.donor.read_bytes())
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'candidate_sha256':sha(result),'candidate_bytes':len(result),'free_bytes':256000-len(result),
  'recipe_sha256':sha(Path(__file__).read_bytes()),'policy':load(HERE/'patch_public.py','r27_add_policy').policy_check(result),**meta,
  'state':'ACTUAL_ALL12_NATIVE_ADD_GEMM_PORTFOLIO_NOT_COMPILED',
  'actual_binding':'denseYaV/Ya3Q retainedallpositivek; elem.addRelu=Ybf; LayerNormMYbc retained; RMSkernels0.norm.rmsnorm viaZbZ. finalcorrect usesW1/Zc0Q/Zdt',
  'runtime_cut':'Native64YaW retained; large-gap fallback directlyModel.add, native192 fallback removed. Ybf directArray.ofFn insteadYbd. CompleteMixer includesfallback cost',
  'scope':'Independentpre9source/premises only, no9input/nativeoutput read or tuning. Newexactsource needsoriginalall12gate andfreshstandardconfirmation',
  'publication':'Ownrecipe/receipts only; whole sources private/ephemeral'}
 a.receipt.write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
