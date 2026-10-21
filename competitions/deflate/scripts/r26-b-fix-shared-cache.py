"""Preserve failed B3 and fix only misplaced owner transfers in a new pair."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json
import re

ROOT=Path(__file__).resolve().parents[1]
BAD=ROOT/'candidates/r26-b-628-shared-cache'
OUT=ROOT/'candidates/r26-b-628-shared-cache-fix1'
E=ROOT/'evidence/round26/route-b'
BAD_SHA='bb6bbbf7048bf86a489ed6796208c0c46e929a15b30cf512cc8a49719e98239a'


def sha(raw):return hashlib.sha256(raw).hexdigest()


def masked(text):
    chars=list(text);i=0
    while i<len(text):
        if text.startswith('//',i):
            stop=text.find('\n',i);stop=len(text)if stop<0 else stop
        elif text.startswith('/*',i):
            depth=1;stop=i+2
            while depth:
                assert stop<len(text),'unterminatedcomment'
                if text.startswith('/*',stop):depth+=1;stop+=2
                elif text.startswith('*/',stop):depth-=1;stop+=2
                else:stop+=1
        elif text[i]=='"':
            stop=i+1
            while stop<len(text):
                if text[stop]=='\\':stop+=2
                elif text[stop]=='"':stop+=1;break
                else:stop+=1
        elif text[i]=="'" and ((i+2<len(text)and text[i+2]=="'")or(i+3<len(text)and text[i+1]=='\\'and text[i+3]=="'")):
            stop=i+3 if text[i+2]=="'"else i+4
        else:
            i+=1;continue
        for j in range(i,min(stop,len(text))):
            if chars[j]!='\n':chars[j]=' '
        i=stop
    return ''.join(chars)


def spans(text):
    code=masked(text);stack=[];pairs={}
    for i,char in enumerate(code):
        if char=='{':stack.append(i)
        elif char=='}':
            if not stack:raise ValueError(f'unexpected closing brace at line{text.count(chr(10),0,i)+1}')
            pairs[stack.pop()]=i
    assert not stack,'unclosed brace'
    functions={}
    for match in re.finditer(r'\bpub\s+fn\s+([A-Za-z0-9_]+)\s*(?:<[^{}]*>)?\s*\(',code):
        brace=code.index('{',match.end());assert brace in pairs
        functions[match.group(1)]=(match.start(),pairs[brace]+1)
    return functions


def build():
    raw=(BAD/'parse.rs').read_bytes();assert sha(raw)==BAD_SHA
    old=raw.decode()
    try:spans(old)
    except ValueError as error:
        assert str(error)=='unexpected closing brace at line14409',str(error)
        reproduced=str(error)
    else:raise AssertionError('Must reproduce B3 misplaced closingbrace')
    # The original span helper retains trailing newline. body[:-1] removed it,
    # leaving the old closingbrace before the generated ownership transfer.
    first='\n}\n if cache_mp.len()==0{*cache_mp=mp;*cache_mb=mb;*cache_fmt=0;}\n}'
    second='\n}\n if cache_mp.len()==0{*cache_mp=mstart;*cache_mb=mc;*cache_fmt=1;}\n}'
    assert old.count(first)==3 and old.count(second)==1
    fixed=old.replace(first,first.replace('\n}\n if','\n if',1)).replace(second,second.replace('\n}\n if','\n if',1))
    function_spans=spans(fixed)
    checks={}
    for name in ('Z144','Z185','Z308','Z336'):
        lo,hi=function_spans['r26_b_'+name]
        body=fixed[lo:hi]
        assert body.count('if cache_mp.len()==0')==1 and body.rstrip().endswith(';}\n}')
        checks[name]={'start_line':fixed.count('\n',0,lo)+1,'end_line':fixed.count('\n',0,hi)+1,
                      'ownership_transfer_inside_function':True,'function_sha256':sha(body.encode())}
    assert sha((BAD/'parse.rs').read_bytes())==BAD_SHA
    builder=importlib.import_module('r26-b-build-shared-cache')
    files,manifest=builder.build();assert files['parse.rs']==raw
    files['parse.rs']=fixed.encode()
    manifest.update(candidate=OUT.name,parent=BAD.name,
                    hashes={f:sha(files[f])for f in ('parse.rs','Parse.lean')},
                    failure_parent={'rust_sha256':BAD_SHA,'run_id':'38176708101','failure':'unexpected closing delimiter at parse.rs14409; owner transfer placed outside clonedplanner'},
                    substantive_change='Syntax repair only: move the four existing transferstatements inside their intendedcloned planner bodies. Preserve failedparent bytes and originalstrongseed/SF consumer policy.',
                    source_reversal='Reinsert the four closingbraces to restore exact failedB3. For original628 reversal use the parent builder.',
                    proof_status='INHERITED_LEAN_UNCHANGED_DRAFT_MISSING_NEW_OWNER_AND_CONSUMER_SPECS')
    files['manifest.json']=(json.dumps(manifest,indent=2,ensure_ascii=False)+'\n').encode()
    audit={'status':'VERIFIED_SOURCE_SYNTAX_BOUNDARY_RED_GREEN_ONLY','failed_source_sha256':BAD_SHA,
           'fixed_source_sha256':sha(files['parse.rs']),'reproduced_failure':reproduced,
           'total_pub_function_spans':len(function_spans),'planner_checks':checks,
           'limits':['Lightweight lexical brace/span check, not Rustcompile or Leanverification.',
                     'All four transfer sites are inside their intended function; real native compile/encoder/decode required next.']}
    return files,manifest,audit


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    files,manifest,audit=build()
    if args.check:
        assert all((OUT/f).read_bytes()==b for f,b in files.items())
        assert json.loads((E/'shared-cache-fix1-preflight.json').read_bytes())==audit
    else:
        OUT.mkdir(exist_ok=False)
        for f,b in files.items():(OUT/f).write_bytes(b)
        (E/'shared-cache-fix1-preflight.json').write_bytes((json.dumps(audit,indent=2)+'\n').encode())
    print(json.dumps({'candidate':OUT.name,'hashes':manifest['hashes'],'preflight':audit},indent=2))


if __name__=='__main__':main()
