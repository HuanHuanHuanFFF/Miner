"""Mixer portfolio cost/proof reconstruction from two exact released sources.

Use public23's dense path and layernorm; recover public27's complete small-k
GEMM and native residual add. Non-Mixer RMS retains the already-proved generic
implementation. Pruning removes only declarations outside a conservative
reference closure. The exact resulting source still requires the original gate.
"""
from pathlib import Path
import hashlib,importlib.util,os,re,unicodedata
HERE=Path(__file__).resolve().parent
TOKEN=re.compile(r"[\w'?!]+")
STOP=re.compile(r"(?m)^(?:(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected)\s+)*(?:def|theorem|lemma|structure|abbrev|instance|class)\b|(?:local\s+)?(?:section|end|open|set_option|attribute|namespace|notation|postfix|prefix|infix|instance|macro|elab)\b)")
DECL=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected)\s+)*(def|theorem|lemma|structure|abbrev)\s+([\w.'?!]+)")
def sha(x):return hashlib.sha256(x).hexdigest()
def load(name):
 p=HERE/name;s=importlib.util.spec_from_file_location('r27_portfolio_'+p.stem,p)
 m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def declarations(text):
 bounds=[x.start() for x in STOP.finditer(text)];out={}
 for m in DECL.finditer(text):
  end=next((x for x in bounds if x>m.start()),len(text));name=m[2]
  assert name not in out,('duplicate declaration needs scope-aware handling',name)
  out[name]=(m.start(),end,m[1],text[m.start():end])
 return out
def once(s,a,b):
 assert s.count(a)==1,(a,s.count(a));return s.replace(a,b,1)
def build(raw,donor):
 base=load('build_gemm27_on_public23_v2.py').transform(raw,23,'gemm27-all-positive-k',donor)
 assert sha(base)=='6fe5feb6cf0b919a9700f5f05264b1e98e24d7ee74b9d2853c1e55be866d4ada'
 text=base.decode();dtext=donor.decode();donor_decls=declarations(dtext);old=declarations(text)
 original23=declarations(raw.decode())
 # Restore the donor's fast small-k engine, instead of routing small GEMMs
 # through an additional transpose and the dense wrapper.
 # Names are reused for unrelated facts across retired submissions. Reuse a
 # dependency only when its ORIGINAL declaration bytes match; rename every
 # copied declaration and all its references to avoid accidental proof binding.
 def normalized(x):return re.sub(r'\s+','',re.sub(r'/-.*?-/','',x,flags=re.S))
 shared={n for n in donor_decls if n in original23 and normalized(donor_decls[n][3])==normalized(original23[n][3])}
 interface_shared=set()
 changed=True
 while changed:
  changed=False
  for n,x in donor_decls.items():
   if n in shared or n not in original23 or x[2] not in {'lemma','theorem'}:continue
   header=x[3].split(':=',1)[0];other=original23[n][3].split(':=',1)[0]
   dependencies=(set(TOKEN.findall(header))&donor_decls.keys())-{n}
   if normalized(header)==normalized(other) and dependencies<=shared:
    shared.add(n);interface_shared.add(n);changed=True
 wanted=set();stack=['Ybf','W1']
 while stack:
  n=stack.pop()
  if n in shared or n in wanted:continue
  assert n in donor_decls,n;wanted.add(n)
  stack.extend((set(TOKEN.findall(donor_decls[n][3]))&donor_decls.keys())-shared-wanted)
 parts='\n'.join(x[3].rstrip() for n,x in sorted(donor_decls.items(),key=lambda p:p[1][0]) if n in wanted)+'\n'
 common=load('build_gemm27_on_public23.py');da=common.aliases(dtext);ba=common.aliases(text)
 diffs={n:da[n] for n in set(TOKEN.findall(parts))&da.keys() if ba.get(n)!=da[n]}
 for n,qualified in sorted(diffs.items(),key=lambda p:-len(p[0])):
  parts=re.sub(r"(?<![\w'?!])"+re.escape(n)+r"(?![\w'?!])",qualified,parts)
 pool=[chr(i) for i in range(0x400,0x530) if unicodedata.category(chr(i)) in {'Lu','Ll'} and chr(i) not in text+dtext]
 assert len(pool)>=len(wanted)
 compact_names=dict(zip(sorted(wanted),pool))
 parts=TOKEN.sub(lambda m:compact_names.get(m[0],m[0]),parts)
 text=once(text,'def kernels:Kernels where',parts+'def kernels:Kernels where')
 text=once(text,'elem:=kernels0.elem','elem:=⟨kernels0.elem.avgpool,kernels0.elem.maxpool,'+compact_names['Ybf']+',kernels0.elem.scaleShift⟩')
 text=once(text,'norm:=⟨Ybb2,MYbc⟩','norm:=⟨kernels0.norm.rmsnorm,MYbc⟩')
 text=once(text,'ZcC,Zc0Q,T4b,Zdt]','ZcC,Zc0Q,'+compact_names['W1']+',Zdt]')
 # Non-Mixer fields may use the exact specifications directly. This removes
 # the aggregate kernels0 proof as an unnecessary dependency root; dense,
 # GEMM, residual add and layernorm retain the optimized implementations.
 text=once(text,'core:=kernels0.core','core:=specKernels.core')
 text=once(text,'conv:=kernels0.conv','conv:=specKernels.conv')
 text=once(text,'elem:=⟨kernels0.elem.avgpool,kernels0.elem.maxpool,','elem:=⟨specKernels.elem.avgpool,specKernels.elem.maxpool,')
 text=once(text,',kernels0.elem.scaleShift⟩',',specKernels.elem.scaleShift⟩')
 text=once(text,'norm:=⟨kernels0.norm.rmsnorm,MYbc⟩','norm:=⟨specKernels.norm.rmsnorm,MYbc⟩')
 text=once(text,'by have h:kernels0=specKernels:=ZbZ;simp only[Obligation,kernels,h,','by simp only[Obligation,kernels,')
 # Mixer token-mixing uses the donor's strided small-matrix engine. Use that
 # already-proved engine for the complete GEMM field; larger shapes retain
 # its generic fallback. The unused transpose/dense wrapper can then be pruned.
 all_defs=declarations(text);names=set(all_defs)
 # Keep command scaffolding and implicit theorem registrations. Local tactic
 # variables can add false dependency edges; this conservatively keeps extras.
 spans=sorted((x[0],x[1]) for x in all_defs.values());cursor=0;scaffold=[]
 for a,b in spans:scaffold.append(text[cursor:a]);cursor=b
 scaffold.append(text[cursor:])
 keep={'kernels','correct'}|{n for n in names if '.' in n}|(set(TOKEN.findall(''.join(scaffold)))&names)
 keep|={n for n,x in all_defs.items() if x[2] in {'structure','abbrev'} or
        (x[2] in {'lemma','theorem'} and x[3].startswith('@['))}
 graph={n:set(TOKEN.findall(x[3]))&names for n,x in all_defs.items()}
 stack=list(keep)
 while stack:
  n=stack.pop()
  for dep in graph[n]-keep:keep.add(dep);stack.append(dep)
 removed=[n for n in all_defs if n not in keep]
 for n in sorted(removed,key=lambda n:all_defs[n][0],reverse=True):
  a,b,_,_=all_defs[n];text=text[:a]+text[b:]
 prefix_end=text.index('structure Acc');prefix,tail=text[:prefix_end],text[prefix_end:]
 used=set(TOKEN.findall(tail));removed_aliases=[]
 def trim_open(m):
  ns,items=m[1],m[2];kept=[]
  for original,alias in re.findall(r"([\w.'?!]+)->([\w'?!]+)",items):
   if alias in used or original.split('.')[-1] in used:kept.append(original+'->'+alias)
   else:removed_aliases.append(ns+'.'+original+'->'+alias)
  return 'open '+ns+(' renaming '+','.join(kept) if kept else '')+' '
 prefix=re.sub(r'\bopen\s+([\w.]+)\s+renaming\s+(.+?)(?=\s+open\s+|\s+local\s+notation|\s+local\s+postfix|$)',trim_open,prefix)
 text=prefix+tail
 result=text.encode()
 assert ('def '+compact_names['Ybf']+' ') in text and 'theorem correct:' in text
 assert 'norm:=⟨specKernels.norm.rmsnorm,MYbc⟩' in text
 meta={'removed_unused_open_aliases':removed_aliases,'shared_theorem_same_statement':sorted(interface_shared),'compact_donor_names':compact_names,'added_donor_declarations':sorted(wanted),'added_donor_bytes':len(parts.encode()),
       'resolved_aliases':diffs,'removed_declarations':removed,
       'before_prune_bytes':len(base)+len(parts.encode()),'final_bytes':len(result),
       'runtime':'Dense23 + provedGEMM9 + nativeAdd27; MYbc23; otherfields directspec fallback',
       'proof':'Actual correct connected to ZcC/Zc0Q/W1/Zdt plus ZbZ; NOT_COMPILED'}
 return result,meta
def transform(raw,submission=23,variant='mixer-native-add',donor_raw=None):
 assert submission==23 and variant=='mixer-native-add'
 if donor_raw is None:donor_raw=(Path(os.environ['TORCHLEAN_ROOT'])/'r27-source-private/official-27.lean').read_bytes()
 result=build(raw,donor_raw)[0];assert len(result)<=256000,len(result)
 return result
