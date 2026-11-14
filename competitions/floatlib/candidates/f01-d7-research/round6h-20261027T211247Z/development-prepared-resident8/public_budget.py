"""Read-only proof packaging budget. Does not trim or emit a Lean candidate."""
from pathlib import Path
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda b:hashlib.sha256(b).hexdigest()


def main():
    raw=(HERE/'KernelIndexed8Cost.lean').read_bytes();s=raw.decode();i=0;blocks=[]
    while i<len(s):
        if s[i]=='"':
            i+=1
            while i<len(s):
                if s[i]=='\\':i+=2
                elif s[i]=='"':i+=1;break
                else:i+=1
        elif s.startswith('--',i):
            i=s.find('\n',i)
            if i<0:break
        elif s.startswith('/-',i):
            start=i;i+=2;depth=1
            while depth:
                if s.startswith('/-',i):depth+=1;i+=2
                elif s.startswith('-/',i):depth-=1;i+=2
                else:i+=1
            block=s[start:i];before=s[s.rfind('\n',0,start)+1:start]
            eol=s.find('\n',i);after=s[i:eol if eol>=0 else len(s)]
            full_line=not before.strip() and not after.strip()
            legal=bool(re.search(r'copyright|license|spdx|©',block,re.I))
            blocks.append({'start_line':s.count('\n',0,start)+1,'bytes':len(block.encode()),
                'full_line':full_line,'preserve_legal':legal,'start_char':start,'end_char':i,'sha256':sha(block.encode())})
        else:i+=1
    removable=sum(b['bytes'] for b in blocks if b['full_line'] and not b['preserve_legal'])
    dead_start=raw.index(b'namespace Submission.DirectRows')
    dead_end=raw.index(b'end Submission.DirectRows',dead_start)+len(b'end Submission.DirectRows')
    base=raw[:226829]
    # No external qualified DirectRows reference is present; actual cleanup still
    # needs fresh whole-source elaboration, as unqualified lookup is not a graph.
    outside=base[:dead_start]+base[dead_end:]
    directrows_qualified_refs=len(re.findall(rb'\bDirectRows\.',outside))
    blank_bytes=sum(len(line) for line in raw.splitlines(keepends=True) if not line.strip())
    legal=[b for b in blocks if b['preserve_legal']]
    exact_legal_duplicates=len(legal)>1 and len({b['sha256'] for b in legal})==1
    # In-memory packaging scenario only: retain one complete legal notice,
    # remove only full-line nonlegal comments and the independent dead namespace.
    cuts=[(b['start_char'],b['end_char']) for b in blocks if b['full_line'] and not b['preserve_legal']]
    if exact_legal_duplicates:cuts.extend((b['start_char'],b['end_char']) for b in legal[1:])
    ds=s.index('namespace Submission.DirectRows');de=s.index('end Submission.DirectRows',ds)+len('end Submission.DirectRows')
    cuts.append((ds,de));budget_text=s
    for a,b in sorted(cuts,reverse=True):budget_text=budget_text[:a]+'\n'+budget_text[b:]
    # Preserve the retained notice byte-for-byte; drop blank lines only outside it.
    retained=s[legal[0]['start_char']:legal[0]['end_char']] if legal else ''
    if retained:
        a=budget_text.index(retained);b=a+len(retained)
        left=''.join(l for l in budget_text[:a].splitlines(keepends=True) if l.strip())
        right=''.join(l for l in budget_text[b:].splitlines(keepends=True) if l.strip())
        budget_text=left+retained+'\n'+right
    report={'source_sha256':sha(raw),'source_bytes':len(raw),'limit':256000,
        'current_headroom':256000-len(raw),'full_line_nonlegal_block_comment_bytes':removable,
        'block_comment_count':len(blocks),'preserved_legal_block_comments':[b for b in blocks if b['preserve_legal']],
        'blank_line_bytes_upper_count':blank_bytes,
        'dead_DirectRows_namespace_bytes':dead_end-dead_start,
        'qualified_DirectRows_refs_outside_namespace':directrows_qualified_refs,
        'conservative_headroom_after_comments_only':256000-len(raw)+removable,
        'identical_full_legal_notice_copies':len(legal),'exact_legal_notice_duplicates':exact_legal_duplicates,
        'one_full_legal_notice_sha256':legal[0]['sha256'] if legal else None,
        'in_memory_cleanup_scenario_bytes':len(budget_text.encode()),
        'in_memory_cleanup_scenario_proof_headroom':256000-len(budget_text.encode()),
        'limits':'Budget only; comments are standalone and legal notices excluded. No source edited/emitted. Removing comments needs preserved layout/newlines and fresh exact-source verification. Unqualified refs not resolved.'}
    (HERE/'indexed8-public-budget.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report))


if __name__=='__main__':main()
