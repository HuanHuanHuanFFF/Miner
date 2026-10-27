"""Conservative lexical inventory of unreferenced, unannotated theorem spans.
No source is edited. Removal remains a new-version compiler check, not acceptance.
"""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
from time import monotonic
import re
import json

base=Path(__file__).resolve().parent; root=base.parents[4]
start=monotonic(); records=[]
for name in ['f01-r14-dev-integer-exponent1','f01-r14-dev-combined-slim1']:
    source=root/'competitions/floatlib/candidates'/name/'Kernel.lean'
    raw=source.read_bytes(); text=raw.decode('utf-8'); lines=text.splitlines(keepends=True)
    assert len(lines)<20000
    decl=re.compile(r'^(?:(?:private|protected|noncomputable)\s+)*(?:theorem|lemma)\s+([\w\'.]+)')
    boundary=re.compile(r'^(?:@\[|namespace\s|end(?:\s|$)|section(?:\s|$)|set_option\s|attribute\s|#|(?:(?:private|protected|noncomputable|opaque|unsafe|partial)\s+)*(?:def|abbrev|theorem|lemma|instance|structure|inductive|axiom)\s)')
    search_tactics=re.findall(r'\b(?:exact\?|apply\?|aesop|grind|simp\?)\b',text)
    candidates=[]
    protected={'add_eq','mul_eq','sum_eq','bmm_eq','add_spec','mul_spec','sum_spec','bmm_spec'}
    for i,line in enumerate(lines):
        match=decl.match(line)
        if not match: continue
        leaf=match.group(1).split('.')[-1]
        refs=len(re.findall(r'(?<![\w\'])'+re.escape(leaf)+r'(?![\w\'])',text))
        if refs!=1 or leaf in protected: continue
        previous=next((s.strip() for s in reversed(lines[:i]) if s.strip()),'')
        if previous.startswith('@['): continue
        end=next((j for j in range(i+1,len(lines)) if boundary.match(lines[j])),len(lines))
        # Keep namespace endings and following attributes out of the proposed span.
        span=''.join(lines[i:end]).encode('utf-8')
        candidates.append(dict(name=match.group(1),line=i+1,end_exclusive=end+1,
                               bytes=len(span),sha256=sha256(span).hexdigest(),
                               lexical_occurrences=refs,unannotated=True))
    records.append(dict(source=source.relative_to(root).as_posix(),source_bytes=len(raw),
                        source_sha256=sha256(raw).hexdigest(),
                        environment_search_tactics=search_tactics,
                        proposed_theorem_spans=candidates,
                        total_lexical_span_bytes=sum(c['bytes'] for c in candidates)))
    assert monotonic()-start<3.0
receipt=dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),state='LEXICAL_OPPORTUNITY_ONLY_NO_EDITS',
             script_sha256=sha256(Path(__file__).read_bytes()).hexdigest(),elapsed_seconds=monotonic()-start,
             records=records,
             caveats='Unqualified-name counts are conservative. Spans can include adjacent comments. No Lean parser/compiler has checked removal. Any adopted pruning is a new exact source; keep frozen originals, attribution and public obligations. Unannotated theorem deletion has no intended runtime change, but do not infer unchanged gate or generated executable before checking.')
Path(__file__).with_suffix('.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps(receipt,indent=2))
