"""Remove standalone prose comments only; preserve code lines, attribution and line numbers."""
from pathlib import Path
import argparse,hashlib,json,re

def compact(raw):
    text=raw.decode('utf-8');spans=[];i=0
    while i<len(text):
        if text[i]=='"':
            i+=1
            while i<len(text):
                if text[i]=='\\':i+=2
                elif text[i]=='"':i+=1;break
                else:i+=1
        elif text[i]=='«':
            j=text.find('»',i+1);assert j>=0;i=j+1
        elif text.startswith('/-',i):
            start=i;i+=2;depth=1
            while depth:
                assert i<len(text)
                if text.startswith('/-',i):depth+=1;i+=2
                elif text.startswith('-/',i):depth-=1;i+=2
                else:i+=1
            spans.append((start,i))
        elif text.startswith('--',i):
            start=i;j=text.find('\n',i);i=j if j>=0 else len(text);spans.append((start,i))
        else:i+=1
    selected=[]
    for start,end in spans:
        ls=text.rfind('\n',0,start)+1;le=text.find('\n',end);le=len(text) if le<0 else le
        own_line=not text[ls:start].strip() and not text[end:le].strip()
        attribution=re.search(r'copyright|license|authors?\s*[:：]|SPDX|https?://|来源|作者|许可',text[start:end],re.I)
        if own_line and not attribution:selected.append((start,end))
    output=[];at=0;removed=[]
    for start,end in selected:
        output += [text[at:start], '\n'*text[start:end].count('\n')]
        removed.append({'line':text.count('\n',0,start)+1,'end_line':text.count('\n',0,end)+1,'bytes':len(text[start:end].encode()),'sha256':hashlib.sha256(text[start:end].encode()).hexdigest()})
        at=end
    output.append(text[at:]);result=''.join(output)
    assert result.count('\n')==text.count('\n')
    # Non-comment text outside selected spans is concatenated without alteration.
    restored=[];at=0
    for start,end in selected:restored.append(text[at:start]);at=end
    restored.append(text[at:])
    assert ''.join(restored).replace('\n','')==result.replace('\n','')
    return result.encode(),removed

if __name__=='__main__':
    ap=argparse.ArgumentParser();ap.add_argument('--input',type=Path,required=True);ap.add_argument('--output',type=Path,required=True);ap.add_argument('--report',type=Path,required=True);a=ap.parse_args()
    root=Path(__file__).resolve().parents[5];source=a.input.resolve();target=a.output.resolve();report=a.report.resolve()
    assert source.is_relative_to(root) and target.is_relative_to(root/'competitions/floatlib/candidates') and report.is_relative_to(root)
    assert not target.exists() and not report.exists() and source.stat().st_size<=1000000
    raw=source.read_bytes()
    assert hashlib.sha256(raw).hexdigest()=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172', 'This lexer was reviewed only for the frozen retained source; append new proof fragments after compacting that base.'
    result,removed=compact(raw)
    target.parent.mkdir(parents=True,exist_ok=True);target.write_bytes(result)
    value={'input':source.relative_to(root).as_posix(),'input_sha256':hashlib.sha256(raw).hexdigest(),'output':target.relative_to(root).as_posix(),'output_sha256':hashlib.sha256(result).hexdigest(),'input_bytes':len(raw),'output_bytes':len(result),'same_line_count':True,'unchanged_all_non_selected_text':True,'removed_comments':removed,'scope':'Standalone non-attribution comments only. No code token/layout, import, definition, theorem or public API changed. This is not Lean or runtime validation; the eventual exact combined candidate must pass full original gate.'}
    report.write_bytes((json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
    print(json.dumps({k:v for k,v in value.items() if k!='removed_comments'}))
