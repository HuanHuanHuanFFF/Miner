"""Owned, token-aware proof-only spelling compactor for the public #53 source.

No proofs are deleted and no runtime definitions or arithmetic are replaced.
Original whole source stays private; original gate is still required afterward.
"""
from pathlib import Path
import argparse
import hashlib
import itertools
import json
import re
import string
import unicodedata

BASE_SHA = '3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb'
ALIASES = {'UInt64':'ق', 'UInt32':'ك', 'USize':'م', 'Array':'ل',
           'Bool':'ه', 'Nat':'ٽ', 'Int':'پ'}
COMMAND = re.compile(r'(?m)^(?:@\[[^\n]*?\]\s+)?(?:private\s+)?(lemma|theorem|def|abbrev|structure|instance|set_option|local|open|namespace|end)\b')

def identchar(c):
    return c in "_'" or unicodedata.category(c)[0] in 'LMN'

def tokens(text):
    """Yield mutable identifiers, skipping strings and nested Lean comments.

    Dotted identifiers are kept whole so e.g. UInt64.toNat is never replaced
    with an invalid notation projection. Quoted identifiers are kept opaque.
    """
    i=0; n=len(text)
    while i<n:
        if text.startswith('--',i):
            e=text.find('\n',i); i=n if e<0 else e+1
        elif text.startswith('/-',i):
            i+=2; depth=1
            while i<n and depth:
                if text.startswith('/-',i):depth+=1;i+=2
                elif text.startswith('-/',i):depth-=1;i+=2
                else:i+=1
        elif text[i]=='"':
            i+=1
            while i<n:
                if text[i]=='\\':i+=2
                elif text[i]=='"':i+=1;break
                else:i+=1
        elif text[i]=='«':
            e=text.find('»',i+1); i=n if e<0 else e+1
        elif identchar(text[i]) and not text[i].isdigit():
            j=i+1
            while j<n and (identchar(text[j]) or
                    (text[j]=='.' and j+1<n and identchar(text[j+1]))):j+=1
            yield i,j,text[i:j]
            i=j
        else:i+=1

def replace(text, mapping):
    parts=[]; p=0; counts={}
    for a,b,t in tokens(text):
        if t in mapping:
            parts.extend((text[p:a],mapping[t]));p=b
            counts[t]=counts.get(t,0)+1
    parts.append(text[p:]);return ''.join(parts),counts

def build(raw, strict_base=True):
    if strict_base:assert hashlib.sha256(raw).hexdigest()==BASE_SHA
    text=raw.decode('utf-8'); all_tokens={t for _,_,t in tokens(text)}
    declarations=list(COMMAND.finditer(text)); names=[]
    for m in declarations:
        if m[1] in ('lemma','theorem'):
            nm=re.match(r'\s+([A-Za-z][A-Za-z0-9_]*)',text[m.end():])
            if nm and len(nm[1])>5 and nm[1]!='correct':names.append(nm[1])
    candidates=('p'+a+b for a,b in itertools.product(string.ascii_letters,repeat=2))
    rename={}
    for old in dict.fromkeys(names):
        new=next(s for s in candidates if s not in all_tokens)
        rename[old]=new;all_tokens.add(new)
    renamed,rename_counts=replace(text,rename)
    # Exact invertibility of global alpha-renaming, including all proof uses.
    restored,_=replace(renamed,{v:k for k,v in rename.items()})
    assert restored==text
    commands=list(COMMAND.finditer(renamed));out=[];cursor=0;alias_counts={};runtime=[]
    for i,m in enumerate(commands):
        end=commands[i+1].start() if i+1<len(commands) else len(renamed)
        chunk=renamed[m.start():end];out.append(renamed[cursor:m.start()])
        if m[1] in ('lemma','theorem'):
            chunk,ct=replace(chunk,ALIASES)
            for k,v in ct.items():alias_counts[k]=alias_counts.get(k,0)+v
        elif m[1] in ('def','abbrev','structure','instance'):
            # Runtime-bearing source chunks untouched except lemma spelling.
            runtime.append(hashlib.sha256(chunk.encode()).hexdigest())
        out.append(chunk);cursor=end
    out.append(renamed[cursor:]);result=''.join(out).encode()
    new_commands=list(COMMAND.finditer(result.decode()));runtime_after=[]
    for i,m in enumerate(new_commands):
        if m[1] in ('def','abbrev','structure','instance'):
            end=new_commands[i+1].start() if i+1<len(new_commands) else len(result.decode())
            runtime_after.append(hashlib.sha256(result.decode()[m.start():end].encode()).hexdigest())
    assert runtime==runtime_after
    receipt={'base_sha256':hashlib.sha256(raw).hexdigest(),'base_bytes':len(raw),
        'candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
        'saved_bytes':len(raw)-len(result),'free_bytes':256000-len(result),
        'lemma_renames':rename,'lemma_rename_occurrences':rename_counts,
        'proof_type_alias_occurrences':alias_counts,
        'runtime_declaration_chunks_unchanged_after_lemma_alpha_rename':len(runtime),
        'alpha_rename_inverse_exact':True,'proof_deletions':0,
        'compile_status':'NOT_RUN','full_original_gate':'NOT_RUN',
        'runtime_equivalence':'INFERRED_FROM_PROOF_ONLY_TEXT_CHANGE_NOT_COMPILED'}
    return result,receipt

def transform(raw, submission_id, mode, **kwargs):
    assert submission_id==53 and mode=='proof-compact53'
    return build(raw)[0]

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('source',type=Path);p.add_argument('output',type=Path);p.add_argument('--receipt',type=Path,required=True);a=p.parse_args()
    out,rec=build(a.source.read_bytes());a.output.parent.mkdir(parents=True,exist_ok=True)
    a.output.write_bytes(out);a.receipt.write_text(json.dumps(rec,indent=2,ensure_ascii=False)+'\n',encoding='utf-8')
    print(json.dumps({k:v for k,v in rec.items() if k not in ['lemma_renames','lemma_rename_occurrences','proof_type_alias_occurrences']}))
