"""Bounded source-size diagnosis, no Lean, candidate, Git or CI mutation."""
from pathlib import Path
import hashlib,json,re
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4]
path=ROOT/'competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean'
raw=path.read_bytes();text=raw.decode();assert len(raw)==248144
spans=[];i=0
while i<len(text):
    if text.startswith('"',i):
        i+=1
        while i<len(text):
            if text[i]=='\\':i+=2
            elif text[i]=='"':i+=1;break
            else:i+=1
    elif text.startswith('«',i):
        j=text.find('»',i+1);assert j>=0;i=j+1
    elif text.startswith('/-',i):
        start=i;i+=2;depth=1
        while depth:
            assert i<len(text)
            if text.startswith('/-',i):depth+=1;i+=2
            elif text.startswith('-/',i):depth-=1;i+=2
            else:i+=1
        spans.append((start,i,'block'))
    elif text.startswith('--',i):
        start=i;j=text.find('\n',i);i=j if j>=0 else len(text);spans.append((start,i,'line'))
    else:i+=1
eligible=[];preserved=[]
for start,end,kind in spans:
    line_start=text.rfind('\n',0,start)+1;line_end=text.find('\n',end);line_end=len(text) if line_end<0 else line_end
    stand_alone=not text[line_start:start].strip() and not text[end:line_end].strip()
    legal=bool(re.search(r'copyright|license|authors?\s*[:：]|SPDX|https?://|来源|作者|许可',text[start:end],re.I))
    if stand_alone and not legal:eligible.append((start,end))
    else:preserved.append({'line':text.count('\n',0,start)+1,'kind':kind,'reason':'attribution/source or inline-layout preserved'})
savings=sum(len(text[s:e].encode())-text[s:e].count('\n') for s,e in eligible)
report={'state':'SIZE_DIAGNOSIS_ONLY','kernel_sha256':hashlib.sha256(raw).hexdigest(),'bytes':len(raw),'current_headroom':256000-len(raw),'standalone_non_attribution_comments':len(eligible),'potential_comment_byte_reduction':savings,'possible_headroom':256000-len(raw)+savings,'preserved_comment_contexts':preserved,'scope':'No candidate changed/generated. Only standalone non-attribution comments are size opportunities; inline comments/quoted text and license/source attribution remain intact. Any eventual compacted candidate still needs exact full verification.'}
(OUT/'development-source-budget.json').write_bytes((json.dumps(report,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps({k:v for k,v in report.items() if k!='preserved_comment_contexts'}))
