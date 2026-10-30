"""Conservative proof-space diagnostic; all runtime declarations are roots.

Only an explicit source-token reachability report, not a Lean dependency trace.
No source is pruned or candidate substituted by this diagnostic.
"""
from pathlib import Path
import importlib.util,hashlib,json,re,datetime
HERE=Path(__file__).resolve().parent;BASE=HERE.parents[1]/'competition-state/source-private/official-53.lean'
COMP=HERE.parent/'source-budget/compact53.py'
def main():
    spec=importlib.util.spec_from_file_location('r28reachlex',COMP);M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
    raw=BASE.read_bytes();s=raw.decode();commands=list(M.COMMAND.finditer(s));decls={};other=[]
    for i,m in enumerate(commands):
      end=commands[i+1].start() if i+1<len(commands) else len(s);chunk=s[m.start():end]
      name=re.match(r'\s+([A-Za-z][A-Za-z0-9_]*)',s[m.end():])
      if m[1] in ['def','lemma','theorem','abbrev','structure'] and name:
        decls[name[1]]={'kind':m[1],'start':m.start(),'end':end,'text':chunk}
      else:other.append(chunk)
    names=set(decls)
    def deps(text):
      ts={t for _,_,t in M.tokens(text)};ts|={t.rsplit('.',1)[-1] for t in ts}
      return ts&names
    graph={n:deps(d['text'])-{n} for n,d in decls.items()}
    roots={n for n,d in decls.items() if d['kind'] not in ['lemma','theorem']}|{'correct'}
    for text in other:roots|=deps(text)
    seen=set(roots);todo=list(roots)
    while todo:
      n=todo.pop()
      for q in graph[n]-seen:seen.add(q);todo.append(q)
    dead=[{'name':n,'bytes':len(d['text'].encode()),'sha256':hashlib.sha256(d['text'].encode()).hexdigest(),'kind':d['kind']} for n,d in decls.items() if n not in seen]
    dead.sort(key=lambda x:-x['bytes'])
    hazards=re.findall(r'@\[(?:simp|grind|aesop)[^\]]*\]|\b(?:attribute|aesop|library_search|exact\?|apply\?|simp\?)\b',s)
    # Word-level shadowing can over-retain lemmas. It does not justify deleting
    # any apparently dead item before an independent check and exact all12 gate.
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'base_sha256':hashlib.sha256(raw).hexdigest(),'base_bytes':len(raw),'runtime_declarations_all_roots':sum(d['kind'] not in ['lemma','theorem'] for d in decls.values()),'root_count':len(roots),'reachable_count':len(seen),'explicit_token_unreachable_proof_count':len(dead),'explicit_token_unreachable_proof_bytes':sum(x['bytes'] for x in dead),'potentially_unreachable_proofs':dead,'detected_global_proof_search_hazards':hazards,'semantic_status':'UNKNOWN: lexical dependency overapproximation only, not Lean elaborator dependency validation. No source mutation or pruning performed.','script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'lexer_sha256':hashlib.sha256(COMP.read_bytes()).hexdigest()}
    (HERE/'source-reachability.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps({k:v for k,v in out.items() if k!='potentially_unreachable_proofs'},indent=2));print(json.dumps(dead[:12],indent=2))
if __name__=='__main__':main()
