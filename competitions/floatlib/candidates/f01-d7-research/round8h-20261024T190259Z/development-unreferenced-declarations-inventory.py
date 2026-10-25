"""Source-size analysis: explicit non-attributed leaves, including dead helpers."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter
import ast
import hashlib
import json
import re
import time

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
SOURCE=OUT/'development-combined-add-mul-proof-pruned-draft1.lean'
EXPECTED='859a3470076798efe25ece58b9b608e9df889ec761b4d4b03675c333cc2a387a'
sha=lambda data:hashlib.sha256(data).hexdigest()
# Reuse only the frozen lexer's pure function, never execute its top-level work.
prior=OUT/'development-proof-fixedpoint-inventory.py'
nodes=[n for n in ast.parse(prior.read_bytes()).body if isinstance(n,ast.FunctionDef) and n.name=='mask']
assert len(nodes)==1
env={};exec(compile(ast.Module(body=nodes,type_ignores=[]),str(prior),'exec'),env)
mask=env['mask']
roots={'add','mul','sum','bmm','add_spec','mul_spec','sum_spec','bmm_spec','add_eq','mul_eq',
       'referenceBmm','referenceSum','referenceBmm_spec','referenceSum_spec','posZero'}

def leaves(text):
    clean,docs=mask(text)
    assert not re.search(r'\b(?:exact\?|apply\?|library_search|aesop|solve_by_elim|grind\b)',clean)
    tokens=Counter(re.findall(r"[A-Za-z_][A-Za-z0-9_']*",clean))
    lines=clean.splitlines(keepends=True);starts=[];offset=0
    for line in lines:starts.append(offset);offset+=len(line)
    commands=[i for i,line in enumerate(lines) if re.match(r'^(?:@\[|(?:private\s+|protected\s+)?(?:theorem|lemma|def|abbrev|structure|inductive|instance|namespace|end|open|set_option|attribute|notation|noncomputable|variable|section|include|omit|import)\b)',line)]
    rows=[]
    for position,line_number in enumerate(commands):
        match=re.match(r'^(theorem|lemma|def|abbrev) ([A-Za-z_][A-Za-z0-9_]*)\b',lines[line_number])
        if not match:continue
        kind,name=match.groups()
        if name in roots or len(name)<8 or tokens[name]!=1:continue
        declaration_start=starts[line_number];start=declaration_start
        previous=next((lines[i].strip() for i in range(line_number-1,-1,-1) if lines[i].strip()),'')
        if previous.endswith(']') or previous.startswith('set_option') or '@[' in previous:continue
        doc=next(((lo,hi) for lo,hi in reversed(docs) if hi<=start and not clean[hi:start].strip()),None)
        if doc:
            doc_text=text[doc[0]:doc[1]]
            if re.search(r'copyright|licen[cs]e|attribution|author|apache|\bMIT\b|derived.from|source:',doc_text,re.I):continue
            start=doc[0]
        end_line=commands[position+1] if position+1<len(commands) else len(lines)
        while end_line>line_number and not lines[end_line-1].strip():end_line-=1
        end=starts[end_line] if end_line<len(starts) else len(text)
        block=text[start:end].encode()
        if re.search(r'copyright|licen[cs]e|attribution|author|apache|\bMIT\b|source:',block.decode(),re.I):continue
        assert '@[' not in clean[declaration_start:end]
        assert not re.search(r'\n(?:attribute|namespace |end\b|instance )',clean[declaration_start:end])
        rows.append(dict(kind=kind,name=name,character_start=start,declaration_start=declaration_start,
                         character_end=end,bytes=len(block),sha256=sha(block),docstring_removed=doc is not None))
    return rows

started=time.perf_counter();raw=SOURCE.read_bytes();assert sha(raw)==EXPECTED
text=raw.decode();rounds=[]
for iteration in range(50):
    rows=leaves(text)
    if not rows:break
    parent=text.encode();parts=[];position=0
    for row in rows:
        assert row['character_start']>=position
        block=text[row['character_start']:row['character_end']].encode()
        assert sha(block)==row['sha256']
        parts.append(text[position:row['character_start']]);position=row['character_end']
    parts.append(text[position:]);text=''.join(parts)
    rounds.append(dict(iteration=iteration+1,parent_sha256=sha(parent),result_sha256=sha(text.encode()),
                       removed_bytes=len(parent)-len(text.encode()),rows=rows))
    assert time.perf_counter()-started<5,'Inventory exceeded5 seconds; no candidate changed'
assert not leaves(text),'More than50 dependency rounds needed'
destination=OUT/'development-combined-add-mul-dead-helper-pruned-draft1.lean'
assert not destination.exists();destination.write_bytes(text.encode())
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='STATIC_DECLARATION_DEPENDENCY_ANALYSIS',
            source=SOURCE.relative_to(ROOT).as_posix(),source_sha256=EXPECTED,source_bytes=len(raw),
            result=destination.relative_to(ROOT).as_posix(),result_sha256=sha(text.encode()),result_bytes=len(text.encode()),
            bytes_saved=len(raw)-len(text.encode()),over_limit=max(0,len(text.encode())-256000),rounds=rounds,
            wall_seconds=time.perf_counter()-started,protected_names=sorted(roots),
            scope='Only explicit plain theorem/lemma/def/abbrev leaves with one lexical occurrence, including attached non-attribution docstrings. Runtime definitions that remain are byte-identical; some unreachable plain definitions are removed. All attributes, instances, public roots, options, licenses and parents remain. This static analysis is not a Lean dependency proof or runtime equivalence claim; exact compilation and full gates remain NOT_RUN.')
(OUT/'development-unreferenced-declarations-inventory1.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps({k:v for k,v in record.items() if k!='rounds'}))
print(json.dumps([dict(iteration=r['iteration'],count=len(r['rows']),bytes=r['removed_bytes']) for r in rounds]))
