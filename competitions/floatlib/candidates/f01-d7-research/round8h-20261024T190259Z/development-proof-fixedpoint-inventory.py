"""Bounded proof-only leaf inventory; keeps all runtime definitions and parents."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter
import hashlib
import json
import re
import time

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
SOURCE=OUT/'development-combined-add-mul-draft1.lean'
EXPECTED='9a6913ee4da828ab83f78254bd0a1accd136b3274fdc80d8ecba45c2b7d6612a'
sha=lambda data:hashlib.sha256(data).hexdigest()

def mask(text):
    result=list(text);docs=[]
    i,depth,in_string,doc_start=0,0,False,None
    while i<len(text):
        if depth:
            if text.startswith('/-',i):
                depth+=1;result[i:i+2]='  ';i+=2
            elif text.startswith('-/',i):
                depth-=1;result[i:i+2]='  ';i+=2
                if not depth and doc_start is not None:docs.append((doc_start,i));doc_start=None
            else:
                if text[i]!='\n':result[i]=' '
                i+=1
        elif in_string:
            if text[i]=='\\' and i+1<len(text):result[i:i+2]='  ';i+=2
            else:
                in_string=text[i]!='"'
                if text[i]!='\n':result[i]=' '
                i+=1
        elif text.startswith('--',i):
            end=text.find('\n',i);end=len(text) if end<0 else end
            result[i:end]=' '*(end-i);i=end
        elif text.startswith('/-',i):
            doc_start=i if text.startswith('/--',i) else None
            depth=1;result[i:i+2]='  ';i+=2
        elif text[i]=='"':in_string=True;result[i]=' ';i+=1
        else:i+=1
    assert not depth and not in_string
    return ''.join(result),docs

def leaves(text):
    clean,docs=mask(text)
    assert not re.search(r'\b(?:exact\?|apply\?|library_search|aesop|solve_by_elim|grind\b)',clean)
    tokens=Counter(re.findall(r"[A-Za-z_][A-Za-z0-9_']*",clean))
    lines=clean.splitlines(keepends=True)
    starts=[];offset=0
    for line in lines:starts.append(offset);offset+=len(line)
    commands=[i for i,line in enumerate(lines) if re.match(r'^(?:@\[|(?:private\s+|protected\s+)?(?:theorem|lemma|def|abbrev|structure|inductive|instance|namespace|end|open|set_option|attribute|notation|noncomputable|variable|section|include|omit|import)\b)',line)]
    rows=[]
    for place,line_number in enumerate(commands):
        match=re.match(r'^(?:theorem|lemma) ([A-Za-z_][A-Za-z0-9_]*)\b',lines[line_number])
        if not match:continue
        name=match[1]
        if len(name)<8 or tokens[name]!=1 or name in ('add_spec','mul_spec','sum_spec','bmm_spec'):continue
        start=starts[line_number]
        if any(not clean[end:start].strip() for _,end in docs if end<=start):continue
        previous=next((lines[i].strip() for i in range(line_number-1,-1,-1) if lines[i].strip()),'')
        if previous.endswith(']') or previous.startswith('set_option') or '@[' in previous:continue
        end_line=commands[place+1] if place+1<len(commands) else len(lines)
        while end_line>line_number and not lines[end_line-1].strip():end_line-=1
        end=starts[end_line] if end_line<len(starts) else len(text)
        block=text[start:end].encode()
        if re.search(r'copyright|license|attribution',block.decode(),re.I):continue
        assert not re.search(r'\n(?:@\[|attribute|def |abbrev |structure |instance |namespace |end\b)',block.decode())
        rows.append(dict(name=name,character_start=start,character_end=end,bytes=len(block),sha256=sha(block)))
    return rows

started=time.perf_counter();raw=SOURCE.read_bytes()
assert sha(raw)==EXPECTED
text=raw.decode();rounds=[]
for iteration in range(20):
    rows=leaves(text)
    if not rows:break
    parent=text.encode();parts=[];position=0
    for row in rows:
        assert row['character_start']>=position
        parts.append(text[position:row['character_start']]);position=row['character_end']
    parts.append(text[position:]);text=''.join(parts)
    rounds.append(dict(iteration=iteration+1,parent_sha256=sha(parent),result_sha256=sha(text.encode()),
                       removed_bytes=len(parent)-len(text.encode()),rows=rows))
    assert time.perf_counter()-started<5,'Bounded inventory exceeded5 seconds; no Kernel changed'
assert not leaves(text),'Still has conservative proof leaves after20 rounds'
destination=OUT/'development-combined-add-mul-proof-pruned-draft1.lean'
assert not destination.exists();destination.write_bytes(text.encode())
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='STATIC_PROOF_ONLY_SIZE_INVENTORY',
            source=SOURCE.relative_to(ROOT).as_posix(),source_sha256=EXPECTED,source_bytes=len(raw),
            result=destination.relative_to(ROOT).as_posix(),result_sha256=sha(text.encode()),result_bytes=len(text.encode()),
            bytes_saved=len(raw)-len(text.encode()),over_limit=max(0,len(text.encode())-256000),rounds=rounds,
            wall_seconds=time.perf_counter()-started,
            scope='Only explicit unreferenced plain theorem/lemma declarations removed from an analysis derivative; no runtime definitions/options/imports/attributes/docstrings/attributions changed. Exact slices and all parents retained. Global-search tactics absent by conservative scan; actual elaboration and full gate remain NOT_RUN.')
(OUT/'development-proof-fixedpoint-inventory1.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps({k:v for k,v in record.items() if k!='rounds'}))
print(json.dumps([dict(iteration=r['iteration'],count=len(r['rows']),bytes=r['removed_bytes']) for r in rounds]))
