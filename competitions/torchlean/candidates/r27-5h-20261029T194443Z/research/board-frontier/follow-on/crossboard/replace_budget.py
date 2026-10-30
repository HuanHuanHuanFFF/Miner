"""In-memory replacement budget: never emits a candidate, all full12 proof still needs validation."""
import re,json,hashlib
from pathlib import Path
from datetime import datetime,timezone
import dependency_census as d

def prune(s):
 removed=[]
 while True:
  ds=d.decls(s);counts={}
  for m in re.finditer(r"[A-Za-z_][A-Za-z_0-9'?!]*",d.c.masked(s)):counts[m.group()]=counts.get(m.group(),0)+1
  spans=[]
  for m,end in d.c.ranges(s,d.D):
   n=m.group(2)
   # Protect dotted methods, structures, requiredentry and attributes with potentialglobal effect.
   if '.'in n or m.group(1)=='structure' or n in ['kernels','correct']:continue
   if counts.get(n,0)==1:
    body=s[m.start():end]
    if '@[simp' in body or '@[instance' in body:continue
    spans.append((m.start(),end));removed.append({'name':n,'kind':m.group(1),'bytes':len(body.encode())})
  if not spans:return s,removed
  for a,b in reversed(spans):s=s[:a]+s[b:]

def main():
 raw=(d.ROOT/'submission5-Kernel.lean').read_bytes();s=raw.decode();cases=[]
 for label,replace,proofs in [('norm',{'norm:=⟨Ybb,Ybc⟩':'norm:=specNorm'},['R0','Q9']),('dense_norm',{'norm:=⟨Ybb,Ybc⟩':'norm:=specNorm','dense:=⟨YaV,Ya3⟩':'dense:=specDense'},['R0','Q9','ZcC','Zc0'])]:
  text=s
  for old,new in replace.items():assert text.count(old)==1;text=text.replace(old,new)
  k=text.index('theorem correct:Obligation kernels:=');head,tail=text[:k],text[k:]
  for name in proofs:tail=re.sub(r',\s*'+name+r'(?=[,\]])','',tail)
  text,removed=prune(head+tail)
  cases.append({'case':label,'bytes_before':len(raw),'bytes_after_dead_declaration_census':len(text.encode()),'freed_bytes':len(raw)-len(text.encode()),'room_under_cap':256000-len(text.encode()),'removed':removed,'not_a_candidate':True})
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'scope':'ISOLATED_IN_MEMORY_REPLACEMENT_BUDGET_ONLY','source5_sha256':hashlib.sha256(raw).hexdigest(),'cases':cases,'limits':['Replacement specNorm/specDense are budget placeholders, not optimization or costcandidate','No sourcefile emitted, compiled or gated','Lexicaldead-declaration removal excludes dottedmethods/structures/instance/simp','Full newoperatorproof andkernelconnection still required','Potentialimplicit/name-resolution dependencies needLean gate; countsnot formalclosure guarantee']};(d.HERE/'replace-budget.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps([{k:v for k,v in c.items()if k!='removed'}|{'removed_count':len(c['removed'])}for c in cases]))
if __name__=='__main__':main()
