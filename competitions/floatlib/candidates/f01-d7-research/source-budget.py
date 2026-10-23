"""Prepare a local whole-file size report without changing the input Kernel.lean."""
import argparse
import hashlib
import json
import re
from pathlib import Path

LICENCE_WORDS=(b'copyright',b'license',b'licence',b'spdx',b'third-party notices',
               b'attribution',b'author',b'adapted',b'derived from',b'ported from',
               b'copied from',b'taken from',b'based on',b'provenance',b'contributor')

def is_notice(comment):
    lower=comment.lower()
    return (any(word in lower for word in LICENCE_WORDS) or '©'.encode() in comment or
            re.search(rb'\bsources?\s*:|\b(?:mit|apache|bsd|gpl|lgpl|mpl)\b|\(c\)(?:\s|\d)',lower) is not None)

def comment_spans(raw):
    spans=[];i=0
    while i<len(raw):
        if raw[i:i+2]==b'--':
            end=raw.find(b'\n',i);end=len(raw) if end<0 else end
            spans.append((i,end));i=end
        elif raw[i:i+2]==b'/-':
            start=i;i+=2;depth=1
            while depth and i<len(raw):
                if raw[i:i+2]==b'/-':depth+=1;i+=2
                elif raw[i:i+2]==b'-/':depth-=1;i+=2
                else:i+=1
            if depth:raise ValueError('Unterminated block comment')
            spans.append((start,i))
        else:
            if raw[i] in (34,96) or raw[i:i+2] in ('«'.encode(),'»'.encode()):
                raise ValueError('Unsupported live string, quotation or quoted identifier; leave source unchanged')
            i+=1
    return spans

def protected_spans(raw):
    paragraphs=[]
    for span in comment_spans(raw):
        if paragraphs and not raw[paragraphs[-1][-1][1]:span[0]].strip(b' \t\r\n'):
            paragraphs[-1].append(span)
        else:paragraphs.append([span])
    return {span for paragraph in paragraphs
            if any(is_notice(raw[start:end]) for start,end in paragraph)
            for span in paragraph}

def prepare(raw):
    raw.decode('utf8')
    protected=protected_spans(raw)
    changes=[]
    for start,end in comment_spans(raw):
        line_start=raw.rfind(b'\n',0,start)+1
        line_end=raw.find(b'\n',end);line_end=len(raw) if line_end<0 else line_end
        if raw[line_start:start].strip(b' \t\r') or raw[end:line_end].strip(b' \t\r'):
            continue
        if (start,end) in protected:
            continue
        has_newline=line_end<len(raw)
        eol=b'\r\n' if has_newline and raw[line_end-1:line_end]==b'\r' else b'\n' if has_newline else b''
        changes.append((line_start,line_end+int(has_newline),eol))
    result=raw
    for start,end,replacement in reversed(changes):result=result[:start]+replacement+result[end:]
    return result

def code_lines(raw):
    live=bytearray(raw)
    for start,end in comment_spans(raw):
        for i in range(start,end):
            if raw[i]!=10:live[i]=32
    original_lines=raw.split(b'\n');live_lines=bytes(live).split(b'\n')
    return b''.join(source+(b'\n' if i<len(original_lines)-1 else b'')
                    for i,(source,visible) in enumerate(zip(original_lines,live_lines))
                    if visible.strip(b' \t\r'))

def licence_hashes(raw):
    protected=protected_spans(raw)
    return [hashlib.sha256(raw[start:end]).hexdigest() for start,end in comment_spans(raw)
            if (start,end) in protected]

def report_for(original,prepared):
    before,after=code_lines(original),code_lines(prepared)
    licences=licence_hashes(original)
    if before!=after:raise ValueError('Live code lines or indentation changed')
    if licences!=licence_hashes(prepared):raise ValueError('Licence or attribution comment bytes changed')
    return {'input_sha256':hashlib.sha256(original).hexdigest(),'input_bytes':len(original),
        'prepared_sha256':hashlib.sha256(prepared).hexdigest(),'prepared_bytes':len(prepared),
        'saved_bytes':len(original)-len(prepared),'official_size_cap':256000,
        'prepared_fits_size_cap':len(prepared)<=256000,
        'code_lines_sha256':hashlib.sha256(before).hexdigest(),'code_lines_byte_equal':True,
        'licence_comment_hashes':licences,
        'removed_comment_count':len(comment_spans(original))-len(comment_spans(prepared)),
        'new_Lean_fullgate':'NOT_RUN',
        'notice_policy':'Recognized licence/copyright/attribution/source cues protect the complete adjacent comment paragraph through the next code boundary, including its grant/disclaimer lines. The exact cue list is in this script; this is not a universal natural-language legal classifier.',
        'scope':'Local source packaging only. Entire live physical code lines including indentation and inline comments are byte-identical; documentation metadata/line numbers may change. This does not establish Lean acceptance or performance. Strings/quotations/quoted identifiers are unsupported and rejected.'}

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--input',required=True,type=Path)
    ap.add_argument('--prepared-output',required=True,type=Path)
    ap.add_argument('--report',required=True,type=Path)
    a=ap.parse_args()
    if len({p.resolve() for p in (a.input,a.prepared_output,a.report)})!=3:
        ap.error('Input, prepared output and report must be distinct paths')
    for path in (a.prepared_output,a.report):
        if path.exists() or path.is_symlink():ap.error('Refusing to overwrite existing artifact: '+str(path))
        if not path.parent.is_dir():ap.error('Output parent must already exist: '+str(path.parent))
    original=a.input.read_bytes()
    try:
        prepared=prepare(original);report=report_for(original,prepared)
    except (ValueError,UnicodeDecodeError) as error:ap.error(str(error))
    if a.input.read_bytes()!=original:ap.error('Input changed during preparation')
    with a.prepared_output.open('xb') as stream:stream.write(prepared)
    with a.report.open('x',encoding='utf8',newline='\n') as stream:
        stream.write(json.dumps(report,indent=2)+'\n')

if __name__=='__main__':main()
