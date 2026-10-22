"""Specialize the verified ten-lane ordered matrix path without altering scalar kernels."""
from pathlib import Path
import hashlib,json,re

ROOT=Path(__file__).resolve().parents[1]
PARENT=ROOT/'f01-d5-stream-pack/Kernel.lean'
raw=PARENT.read_bytes();source=raw.decode('utf-8')
assert hashlib.sha256(raw).hexdigest()=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'

def trim_tuples(text,width):
    def split(body):
        parts=[];start=0;depth=0
        for i,c in enumerate(body):
            if c in '([{⟨':depth+=1
            elif c in ')]}⟩':depth-=1
            elif c==',' and depth==0:parts.append(body[start:i]);start=i+1
        parts.append(body[start:]);return parts
    result='';i=0
    while i<len(text):
        if text[i]!='⟨':result+=text[i];i+=1;continue
        depth=1;j=i+1
        while depth:
            if text[j]=='⟨':depth+=1
            elif text[j]=='⟩':depth-=1
            j+=1
        body=trim_tuples(text[i+1:j-1],width);parts=split(body)
        if len(parts)==10 and all(re.match(r'\s*s'+str(n)+r'\b',p) for n,p in enumerate(parts)):
            body=','.join(parts[:width])
        result+='⟨'+body+'⟩';i=j
    return result

def discard_updates(text,width):
    for n in range(width,10):
        pattern=re.compile(r'\(s'+str(n)+r'\s*\+')
        while (match:=pattern.search(text)):
            i=match.start();j=i+1;depth=1
            while depth:
                if text[j]=='(':depth+=1
                elif text[j]==')':depth-=1
                j+=1
            text=text[:i]+text[j:]
    return text

for width in [4,8]:
    name=f'f01-d7-width{width}'
    start=source.index('namespace Packed10\n')
    prefix=source[:start];body=source[start:]
    body=body.replace('Packed10',f'Packed{width}').replace('F10',f'F{width}').replace('zero10',f'zero{width}').replace('dot10',f'dot{width}')
    # Only the packed matrix section contains lane-count literals to specialize.
    body=re.sub(r'\b10\b',str(width),body)
    body=body.replace('(p + 9)',f'(p + {width-1})')
    body=body.replace(' '.join(f's{i}' for i in range(10)),' '.join(f's{i}' for i in range(width)))
    body=body.replace(' '.join(['zero32']*10),' '.join(['zero32']*width))
    body=discard_updates(body,width)
    body=trim_tuples(body,width)
    # These five constructors contain projections rather than accumulator variables.
    a=body.index(f'structure F{width} where');b=body.index('theorem lane_packet',a)
    fields='\n'.join(f'  s{i} : Float32' for i in range(width))
    choices='\n'.join(f'  | {i} => v.s{i}' for i in range(width-1))+f'\n  | _ => v.s{width-1}'
    packet=', '.join('read col' if i==0 else f'read (col + {i})' for i in range(width))
    updates=', '.join(f'acc.s{i} + a * v.s{i}' for i in range(width))
    constructors=f'''structure F{width} where
{fields}

@[inline] def zero32 : Float32 := Float32.ofBits 0

@[inline] def zero{width} : F{width} := ⟨{', '.join(['zero32']*width)}⟩

@[inline] def lane (v : F{width}) (l : Fin {width}) : Float32 :=
  match l.val with
{choices}

@[inline] def packet (read : Nat → Float32) (col : Nat) : F{width} :=
  ⟨{packet}⟩

@[inline] def update (acc : F{width}) (a : Float32) (v : F{width}) : F{width} :=
  ⟨{updates}⟩

'''
    body=body[:a]+constructors+body[b:]
    body=body.replace(' ∨ '.join(f'l = {i}' for i in range(10)),' ∨ '.join(f'l = {i}' for i in range(width)))
    body=body.replace(' | '.join(['rfl']*10),' | '.join(['rfl']*width))
    assert not re.search(r'\bs[89]\b',body) if width==8 else not re.search(r'\bs[4-9]\b',body)
    payload=(prefix+body).encode('utf-8')
    out=ROOT/name;out.mkdir(exist_ok=True)
    (out/'Kernel.lean').write_bytes(payload)
    manifest={'candidate':name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(payload).hexdigest(),'candidate_bytes':len(payload),'validation_mode':'full-gate','proof_status':'NOT_RUN','parent':PARENT.as_posix(),'parent_sha256':hashlib.sha256(raw).hexdigest(),'mechanism':f'{width} independent ordered lanes in the existing stream-pack pipeline; no arithmetic or scalar change; reduced padding on narrow output shapes','applicability':'all dimensions, same exact fallback and lane projection proofs; first current public-v2 diagnostic, not a promotion','formal_submission':'NOT_SUBMITTED'}
    (out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n','utf-8')
    print(name,len(payload),manifest['candidate_sha256'])
