"""Conservative local-name graph for source capacity; no Lean/kernel execution."""
from pathlib import Path
from datetime import datetime, timezone
from collections import defaultdict
import ast
import hashlib
import json
import re
import time

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
SOURCE=OUT/'development-combined-add-mul-dead-helper-pruned-draft1.lean'
EXPECTED='0ce5e17c640e4bd4119273a01615b5e1903410f8ab11a40f9933194a0f018154'
sha=lambda b:hashlib.sha256(b).hexdigest()
prior=OUT/'development-proof-fixedpoint-inventory.py'
nodes=[n for n in ast.parse(prior.read_bytes()).body if isinstance(n,ast.FunctionDef) and n.name=='mask']
env={};exec(compile(ast.Module(body=nodes,type_ignores=[]),str(prior),'exec'),env)
started=time.perf_counter();raw=SOURCE.read_bytes();assert sha(raw)==EXPECTED
text=raw.decode();clean,docs=env['mask'](text)
assert not re.search(r'\b(?:exact\?|apply\?|library_search|aesop|solve_by_elim|grind|elab|syntax|macro|initialize)\b',clean)
lines=clean.splitlines(keepends=True);starts=[];offset=0
for line in lines:starts.append(offset);offset+=len(line)
command=re.compile(r'^(?:@\[|(?:private\s+|protected\s+)?(?:theorem|lemma|def|abbrev|structure|inductive|instance|namespace|end|open|set_option|attribute|notation|noncomputable|variable|section|include|omit|import)\b)')
commands=[i for i,line in enumerate(lines) if command.match(line)]
declaration=re.compile(r'^(?P<attr>@\[[^\n]*\]\s*)?(?P<visibility>(?:private|protected)\s+)?(?P<kind>theorem|lemma|def|abbrev|structure|inductive|instance)\s+(?P<name>[A-Za-z_][A-Za-z0-9_\'.]*)\b')
scope='';stack=[];rows=[];other=[]
for place,line_number in enumerate(commands):
    line=lines[line_number]
    if match:=re.match(r'^namespace\s+([A-Za-z_][A-Za-z0-9_.]*)',line):
        stack.append(scope);scope=(scope+'.' if scope else '')+match[1];continue
    if re.match(r'^section\b',line):stack.append(scope);continue
    if re.match(r'^end(?:\s|$)',line):
        assert stack,(line_number,line)
        scope=stack.pop();continue
    end_line=commands[place+1] if place+1<len(commands) else len(lines)
    match=declaration.match(line)
    if not match:
        if not re.match(r'^(?:open|import|set_option|variable|include|omit|@\[)',line):
            other.append(clean[starts[line_number]:starts[end_line] if end_line<len(starts) else len(clean)])
        continue
    data=match.groupdict();name=data['name'];qualified=(scope+'.' if scope else '')+name
    start=starts[line_number]
    while end_line>line_number and not lines[end_line-1].strip():end_line-=1
    end=starts[end_line] if end_line<len(starts) else len(text)
    previous=next((lines[i].strip() for i in range(line_number-1,-1,-1) if lines[i].strip()),'')
    attr=data['attr'] or (previous if previous.startswith('@[') else '')
    registration_attribute=bool(attr and attr.strip() not in ('@[inline]','@[noinline]'))
    doc=next(((lo,hi) for lo,hi in reversed(docs) if hi<=start and not clean[hi:start].strip()),None)
    if doc:start=doc[0]
    # Standalone inline markers travel with their unused declaration.
    if previous in ('@[inline]','@[noinline]'):
        marker=clean.rfind(previous,0,starts[line_number]);assert marker>=0
        start=min(start,marker)
    block=text[start:end].encode()
    protected=bool(re.search(r'copyright|licen[cs]e|attribution|author|apache|\bMIT\b|source:',block.decode(),re.I))
    if previous.startswith('set_option') or previous.endswith(' in'):protected=True
    root=registration_attribute or protected or data['kind'] in ('instance','structure','inductive')
    rows.append(dict(name=qualified,leaf=name.split('.')[-1],scope=scope,kind=data['kind'],
                     character_start=start,character_end=end,bytes=len(block),sha256=sha(block),
                     root=root,attribute=attr.strip(),protected=protected,
                     body=clean[starts[line_number]:end]))
assert not stack and not scope
by_name={r['name']:r for r in rows};assert len(by_name)==len(rows),'Ambiguous declaration parser'
by_suffix=defaultdict(set)
for name in by_name:
    parts=name.split('.')
    for pos in range(len(parts)):by_suffix['.'.join(parts[pos:])].add(name)
tokens=re.compile(r"[A-Za-z_][A-Za-z0-9_']*(?:\.[A-Za-z_][A-Za-z0-9_']*)*")
def references(body,scope):
    found=set();prefixes=[];parts=scope.split('.') if scope else []
    for count in range(len(parts),-1,-1):prefixes.append('.'.join(parts[:count]))
    for token in tokens.findall(body):
        direct=next((candidate for prefix in prefixes if (candidate:=(prefix+'.' if prefix else '')+token) in by_name),None)
        if direct is not None:found.add(direct)
        elif token in by_suffix:found.update(by_suffix[token])
        elif '.' in token:found.update(by_suffix[token.rsplit('.',1)[-1]])
    return found
roots={'Submission.'+n for n in ('add','mul','sum','bmm','add_spec','mul_spec','sum_spec','bmm_spec','add_eq','mul_eq','referenceBmm','referenceSum','referenceBmm_spec')}
assert roots<=by_name.keys(),roots-by_name.keys()
roots.update(r['name'] for r in rows if r['root'])
for body in other:roots.update(references(body,''))
edges={r['name']:sorted(references(r['body'],r['scope'])) for r in rows}
live=set(roots);pending=list(roots)
while pending:
    for child in edges[pending.pop()]:
        if child not in live:live.add(child);pending.append(child)
dead=[r for r in rows if r['name'] not in live]
assert all(not r['root'] for r in dead)
parts=[];position=0
for row in dead:
    assert row['character_start']>=position
    parts.append(text[position:row['character_start']]);position=row['character_end']
parts.append(text[position:]);result=''.join(parts).encode()
destination=OUT/'development-combined-add-mul-graph-pruned-draft1.lean'
assert not destination.exists();destination.write_bytes(result)
assert time.perf_counter()-started<5
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='STATIC_LOCAL_NAME_REACHABILITY_ONLY',
            source=SOURCE.relative_to(ROOT).as_posix(),source_sha256=EXPECTED,source_bytes=len(raw),
            result=destination.relative_to(ROOT).as_posix(),result_sha256=sha(result),result_bytes=len(result),
            bytes_saved=len(raw)-len(result),over_limit=max(0,len(result)-256000),wall_seconds=time.perf_counter()-started,
            declaration_count=len(rows),root_count=len(roots),live_count=len(live),
            roots=sorted(roots),edges=edges,
            removed=[{k:v for k,v in r.items() if k!='body'} for r in dead],
            scope='Analysis derivative only, not a candidate. Names resolved first against current namespace prefixes; unmatched names conservatively retain every local suffix match, including dot-notation leaves. Attributes other than inline/noinline, instances, structures, public roots, scoped options and attributions retained. This does not implement the Lean elaborator and cannot establish correctness/runtime equivalence; complete exact-source gate is mandatory before adoption.')
(OUT/'development-local-dependency-graph1.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps({k:v for k,v in record.items() if k not in ('roots','edges','removed')}))
print(json.dumps([dict(name=r['name'],kind=r['kind'],bytes=r['bytes']) for r in dead]))
