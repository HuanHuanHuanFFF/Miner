"""Read-only crossboard source/proof dependency census, not an elaborated closure."""
from pathlib import Path
from datetime import datetime,timezone
import sys,re,json,hashlib
HERE=Path(__file__).resolve().parent
OWN=HERE.parents[1];sys.path.insert(0,str(OWN))
import compact_public23 as c
ROOT=OWN.parent.parent/'competition-state/source-private'
D=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(?:(?:noncomputable|private|protected)\s+)*(def|lemma|theorem|structure|abbrev)\s+([\w.'?!]+)")
def decls(s):
 return {m.group(2):{'kind':m.group(1),'body':s[m.start():end].rstrip(),'line':s[:m.start()].count('\n')+1}for m,end in c.ranges(s,D)}
def graph(s,ds):
 names=set(ds);leaves={}
 for n in names:leaves.setdefault(n.rsplit('.',1)[-1],set()).add(n)
 out={}
 for n,v in ds.items():
  code=c.masked(v['body']);words=set(re.findall(r"[\w.'?!]+",code));deps=words&names
  for word in words:
   if '.'in word:deps.update(leaves.get(word.rsplit('.',1)[-1],set()))
  out[n]=deps-{n}
 return out

def closure(roots,g):
 todo=list(roots);seen=set()
 while todo:
  n=todo.pop()
  if n in seen:continue
  seen.add(n);todo.extend(g[n]-seen)
 return seen

def alias_map(s):
 pre=s[:s.index('structure Acc')];out={}
 for g in re.finditer(r"\bopen\s+([\w.]+)\s+renaming\s+(.+?)(?=\s+open\s+|\s+local\s+notation|\s+local\s+postfix|$)",pre):
  for src,dst in re.findall(r"([\w.'?!]+)->([\w'?!]+)",g.group(2)):out[dst]=g.group(1)+'.'+src
 for symbol,target in re.findall(r'local\s+notation\s*"([^"]+)"\s*=>\s*([\w.]+)',pre):
  if target!='by':out[symbol]=target
 for symbol,target in re.findall(r'local\s+(?:postfix:max|notation:max x:max)\s*"([^"]+)"\s*=>\s*([\w.]+)',pre):
  out[symbol]='@POSTFIX@'+target.rsplit('.',1)[-1]
 return out

def canonical(s,aliases):
 # Conservative textual aid only; local shadowing/notation are not resolved.
 text=c.masked(s)
 for old,new in sorted(aliases.items(),key=lambda kv:-len(kv[0])):
  if new.startswith('@POSTFIX@'):text=text.replace(old,'.'+new.removeprefix('@POSTFIX@'))
  else:text=re.sub(r"(?<![\w.'?!])"+re.escape(old)+r"(?![\w.'?!])",new,text)
 text=re.sub(r'\b0x[0-9a-fA-F]+\b',lambda m:str(int(m.group(),16)),text)
 return re.sub(r'\s+','',text)

def main():
 s5=(ROOT/'submission5-Kernel.lean').read_bytes();s23=(ROOT/'submission23-Kernel.lean').read_bytes();assert hashlib.sha256(s5).hexdigest()=='bc580a4c413c1c44ae626a3b6ebfa69aa1acbfd751dd501981ee8bca9b7e83c3';assert hashlib.sha256(s23).hexdigest()=='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'
 a=decls(s5.decode());b=decls(s23.decode());ga=graph(s5.decode(),a);am=alias_map(s5.decode());bm=alias_map(s23.decode())
 roots={'conv_runtime':['Ybp','dwQ'],'conv_with_proof':['Ybp','dwQ','T4','T3'],'elem_runtime':['Ybk','Ybl','Ybf','Ybe'],'elem_with_proof':['Ybk','Ybl','Ybf','Ybe','T2','T1','U1','U2'],'all_conv_elem_with_proof':['Ybp','dwQ','Ybk','Ybl','Ybf','Ybe','T4','T3','T2','T1','U1','U2']}
 sets={k:closure(v,ga)for k,v in roots.items()};rows={}
 for k,names in sets.items():
  exact=[n for n in names if n in b and a[n]['body']==b[n]['body']]
  text=[n for n in names if n in b and canonical(a[n]['body'],am)==canonical(b[n]['body'],bm)]
  missing=[n for n in names if n not in b];conflict=[n for n in names if n in b and n not in text]
  rows[k]={'roots':roots[k],'declarations':len(names),'bytes':sum(len(a[n]['body'].encode())+1 for n in names),'runtime_bytes':sum(len(a[n]['body'].encode())+1 for n in names if a[n]['kind']in['def','structure','abbrev']),'exact_shared_names':exact,'alias_text_shared_names':text,'missing_names':missing,'conflicting_same_names':conflict,'bytes_after_exact_shared_excluded':sum(len(a[n]['body'].encode())+1 for n in names if n not in exact),'bytes_after_alias_text_shared_excluded':sum(len(a[n]['body'].encode())+1 for n in names if n not in text),'largest':[{'name':n,'bytes':len(a[n]['body'].encode()),'kind':a[n]['kind'],'line':a[n]['line']}for n in sorted(names,key=lambda n:len(a[n]['body'].encode()),reverse=True)[:15]],'closure_names':sorted(names)}
 out={'at_utc':datetime.now(timezone.utc).isoformat(),'scope':'POST_SOURCE_FREEZE_FOLLOW_ON_STATIC_ONLY_NO_CI_NO_CANDIDATE','input_sha256':{'source5':hashlib.sha256(s5).hexdigest(),'source23':hashlib.sha256(s23).hexdigest()},'rows':rows,'total_declarations':{'source5':len(a),'source23':len(b)},'base23_bytes':len(s23),'base23_proof_alias_compact_bytes':248185,'uncompiled_compact_space':7815,'limits':['Lexical dependencies include possiblelocal shadow falsepositives','Implicit notation/typeclass/simp dependencies not elaborated: not guaranteedcompleteLeanclosure','Alias-normalized textidentity is only migration aid, not semanticproof','No new source candidate; wholethirdparty sourceprivate','Currentoverall8 performance UNKNOWN; no gaininferredfromcrossboardcomposition']}
 (HERE/'dependency-census.json').write_text(json.dumps(out,indent=2),encoding='utf8');print(json.dumps({k:{n:v[n]for n in ['declarations','bytes','runtime_bytes','bytes_after_exact_shared_excluded','bytes_after_alias_text_shared_excluded']}for k,v in rows.items()}))
if __name__=='__main__':main()
