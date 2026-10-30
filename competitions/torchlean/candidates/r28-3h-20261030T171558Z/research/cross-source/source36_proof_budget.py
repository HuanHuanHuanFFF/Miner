"""Conservative lexical proof-budget census; not a compiled dependency closure.

No upstream source is emitted. Unreferenced names may have implicit elaboration
dependencies, so these byte counts are opportunity bounds, never acceptance.
"""
from pathlib import Path
from datetime import datetime,timezone
import collections
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
SOURCE=HERE.parents[1]/'competition-state/source-private/official-36.lean'
PIN='595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b'
D=re.compile(r"(?m)^(?:@\[[^\n]*\]\s*)?(def|lemma|theorem|structure|abbrev)\s+([\w.'?!]+)")


def main():
    raw=SOURCE.read_bytes();assert hashlib.sha256(raw).hexdigest()==PIN
    s=raw.decode();matches=list(D.finditer(s));decls={};tail_total=0
    for i,m in enumerate(matches):
        end=matches[i+1].start()if i+1<len(matches)else len(s)
        body=s[m.start():end]
        tail=re.search(r'(?m)^(?:end\b|section\b|namespace\b|open\b|local\b|attribute\b|set_option\b)',body)
        if tail:
            tail_total+=len(body[tail.start():].encode());body=body[:tail.start()]
        decls[m.group(2)]={'kind':m.group(1),'body':body,'bytes':len(body.encode())}
    names=set(decls);leaves=collections.defaultdict(set)
    for name in names:leaves[name.rsplit('.',1)[-1]].add(name)
    graph={}
    for name,decl in decls.items():
        body=decl['body']
        words=set(re.findall(r"[\w.'?!]+",body))
        deps=(words&names)-{name}
        for word in words:
            if '.'in word:deps.update(leaves[word.rsplit('.',1)[-1]])
        if 'Acc.mk' in words:deps.add('Acc')
        graph[name]=deps-{name}
    explicit_attribute_roots={name for name,decl in decls.items()if re.match(r'@\[(?:simp|instance)',decl['body'])}
    roots={'kernels','correct'}|explicit_attribute_roots
    seen=set();todo=list(roots)
    while todo:
        n=todo.pop()
        if n in seen:continue
        seen.add(n);todo.extend(graph[n]-seen)
    unused=names-seen
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'LEXICAL_SOURCE_BUDGET_DIAGNOSTIC_NOT_ELABORATED',
      'base_sha256':PIN,'base_bytes':len(raw),'declarations':len(names),'roots':sorted(roots),'reachable_count':len(seen),
      'unreferenced_count':len(unused),'unreferenced_bytes':sum(decls[n]['bytes']for n in unused),
      'unreferenced_runtime_bytes':sum(decls[n]['bytes']for n in unused if decls[n]['kind']in['def','abbrev','structure']),
      'retained_section_command_bytes':tail_total,
      'unreferenced':[{'name':n,'kind':decls[n]['kind'],'bytes':decls[n]['bytes']}for n in sorted(unused,key=lambda n:decls[n]['bytes'],reverse=True)],
      'limits':['Identifier/projection lexical graph, not Lean parser or elaborator','Local variable name collisions may retain excess declarations','Implicit instance/simp/notation dependencies may be missed; no source removal, no bound on valid finalsize','Full newcorrect still needs exact whole-source originalgate']}
    (HERE/'source36-proof-budget.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:result[k]for k in ['declarations','reachable_count','unreferenced_count','unreferenced_bytes','unreferenced_runtime_bytes']},indent=2));print(result['unreferenced'][:25])


if __name__=='__main__':main()
