# Typed repair for actual CI4 errors; original5ecf/frozen recipe remain unchanged.
# Frozen self-contained reconstruction recipe for pointwise128-nat53.
# Includes unchanged proof-spelling logic from parent compact53.py cce4552b...
# No external file imports, network, Lean build or proof claim in transform().
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

HELPER='''@[inline] def r28PMerge (a b:UInt32):UInt32:=
 ((min (a>>>16) (b>>>16))<<<16)+max (a&&&0xFFFF) (b&&&0xFFFF)
def r28PixScan (x:Array UInt32) (hw p n i:Nat) (v:UInt32):UInt32:=
 if h:i<n then
  let w:=x[i*hw+p]!&&&0x7fffffff
  r28PixScan x hw p n (i+1) (r28PMerge v ((((w-1)>>>23)<<<16)+(w>>>23)))
 else v
termination_by n-i
@[inline] def r28PixP (x:Array UInt32) (ms:Array Nat) (hw k:Nat):Array Nat:=
 YO 1 k.toUSize (fun p _ t=>YV x[t.toNat*hw+p.toNat]! (ms[p.toNat]!).toUInt64)
  (hw*k).toUSize 0 0 0 (Array.mkEmpty (hw*k))
lemma r28PixSize (x:Array UInt32) (ms:Array Nat) (hw k:Nat) (hp:0<hw) (hk:0<k)
 (hn:hw*k<4294967296):(r28PixP x ms hw k).size=hw*k:=by
 have hk32:k<4294967296:=lt_of_le_of_lt (Nat.le_mul_of_pos_left _ hp) hn
 unfold r28PixP
 rw[E1 _ _ _ (by simp) (by rw[Za _ hk32];exact hk) _ _ hn]
 simp
lemma r28Ix (a b c:Nat) (hc:0<c) (ha:a<b) (hn:b*c<4294967296)
 (t:USize) (ht:t<c.toUSize):((a*c).toUSize+t).toNat<b*c:=by
 have hb:0<b:=by omega
 have hc32:c<4294967296:=lt_of_le_of_lt (Nat.le_mul_of_pos_left _ hb) hn
 have hac:a*c<4294967296:=lt_trans (Nat.mul_lt_mul_of_pos_right ha hc) hn
 have htN:t.toNat<c:=by have hh:=USize.lt_iff_toNat_lt.mp ht;simpa only[Za _ hc32] using hh
 apply A9
 constructor
 · rw[Za _ hac]
   nlinarith
 · exact hn
@[specialize] def r28PC128 (n:USize) (f u v:(t:USize)→t<n→UInt64)
 (B C:UInt64) (bw cw:UInt32) (cb db:qCtx0) (z0 z1:UInt64→UInt32)
 (h0 l0 h1 l1:UInt64) (k:USize):UInt64:=
 if ht:k<n then
  let x:=f k ht-0x200000000000000
  let p:=x*(u k ht-0x80000000)
  let q:=x*(v k ht-0x80000000)
  let m:=l0+p
  let z:=l1+q
  r28PC128 n f u v B C bw cw cb db z0 z1
   (h0+((0:UInt64)-(p>>>63))+(if m<l0 then (1:UInt64) else 0)) m
   (h1+((0:UInt64)-(q>>>63))+(if z<l1 then (1:UInt64) else 0)) z (k+1)
 else (z0 (qCtx2 B bw cb h0 l0)).toUInt64 ||| ((z1 (qCtx2 C cw db h1 l1)).toUInt64<<<32)
termination_by n.toNat-k.toNat
decreasing_by exact ZI n k ht
def r28PW (s:ConvShape) (relu:Bool) (x w b:Array UInt32):Array UInt32:=
 if hs:s.kh=1 ∧ s.kw=1 ∧ s.stride=1 ∧ s.pad=0 ∧ 0<s.h ∧ 0<s.w ∧ 0<s.cin ∧ 0<s.cout ∧
  x.size=(s.h*s.w)*s.cin ∧ w.size=s.cout*s.cin ∧ s.cout<=b.size ∧
  (s.h*s.w)*s.cin<4294967296 ∧ s.cout*s.cin<4294967296 ∧ s.cout*(s.h*s.w)<4294967296 ∧
  s.cin<256 ∧ w.any (fun a=>a&&&0x7fffffff==0)=false then
  let hw:=s.h*s.w
  let k:=s.cin
  let C:=s.cout
  have hh:0<hw:=by dsimp[hw];exact Nat.mul_pos (by omega) (by omega)
  have hk:0<k:=by dsimp[k];omega
  have hN:hw*k<4294967296:=by dsimp[hw,k];omega
  have hNW:C*k<4294967296:=by dsimp[C,k];omega
  have hk32:k<4294967296:=lt_of_le_of_lt (Nat.le_mul_of_pos_left _ hh) hN
  let BX:Array UInt32:=Array.ofFn (n:=hw) (fun p=>r28PixScan x hw p.val k 0 0x01FF0000)
  let bp:=BX.foldl r28PMerge 0x01FF0000
  let BW:Array UInt32:=Array.ofFn (n:=C) (fun o=>Yc w k o.val)
  let xm:=Ybh bp BW b
  if hg:(Array.range C).all (fun o=>Ybg BW[o]! b[o]! bp k xm false) then
   let cap:UInt64:=(Array.range C).foldl (fun m o=>
    if Yf b[o]! == 0 then m else min m ((Yd oneW+Yd b[o]!)-Yk ((BW[o]! : UInt32)>>>16))) 510
   let MS:Array Nat:=BX.map (fun (v:UInt32)=>(min (Yk (v>>>16)) cap).toNat)
   let mlo:=MS.foldl min 510
   let mhi:=MS.foldl max 0
   let width:Nat:=mhi-mlo+1
   if hc:mlo<=mhi ∧ mhi<=510 ∧ C*width<1048576 then
    let P:=r28PixP x MS hw k
    have hP:P.size=hw*k:=r28PixSize x MS hw k hh hk hN
    let W:=YW2 w BW b xm k
    have hW:W.size=C*k:=by
     dsimp only[W]
     rw[B7 w BW b xm k (by dsimp[C,k] at hNW;omega) hk32]
     simp only[Array.size_ofFn]
     dsimp[C,k];omega
    let BC:=Array.ofFn (n:=C*width) (fun z=>
     let o:=z.val/width
     let mm:=(mlo+z.val%width).toUInt64
     qCtx1 (mm+Yk ((BW[o]! : UInt32)>>>16)) b[o]!)
    YOC C.toUSize s.h.toUSize s.w.toUSize (fun o y z=>
     if ho:o.toNat<C ∧ y.toNat<s.h ∧ z.toNat<s.w then
      let p:=y.toNat*s.w+z.toNat
      have hp:p<hw:=by dsimp[p,hw];nlinarith[ho.2.1,ho.2.2]
      let f: (t:USize)→t<k.toUSize→UInt64:=fun t ht=>
       (P.uget ((p*k).toUSize+t) (by rw[hP];exact r28Ix p hw k hk hp hN t ht)).toUInt64
      let u: (t:USize)→t<k.toUSize→UInt64:=fun t ht=>
       (W.uget ((o.toNat*k).toUSize+t) (by rw[hW];exact r28Ix o.toNat C k hk ho.1 hNW t ht)).toUInt64
      let mm:=(MS[p]!).toUInt64
      let B:=mm+Yk ((BW[o.toNat]! : UInt32)>>>16)
      let cb:=BC[o.toNat*width+(MS[p]!-mlo)]!
      let done0:=fun a:UInt64=>if a<0x100000000 then a.toUInt32 else Ybz s x w b k o y z false
      if ho2:o.toNat+1<C then
       let v: (t:USize)→t<k.toUSize→UInt64:=fun t ht=>
        (W.uget (((o.toNat+1)*k).toUSize+t) (by rw[hW];exact r28Ix (o.toNat+1) C k hk ho2 hNW t ht)).toUInt64
       let D:=mm+Yk ((BW[o.toNat+1]! : UInt32)>>>16)
       let db:=BC[(o.toNat+1)*width+(MS[p]!-mlo)]!
       let done1:=fun a:UInt64=>if a<0x100000000 then a.toUInt32 else Ybz s x w b k (o+1) y z false
       let empty:=((BX[p]! : UInt32)>>>16)==511
       let fast:=(empty || Yk ((BX[p]! : UInt32)&&&0xFFFF)-mm+YU BW[o.toNat]!<=15) &&
        (empty || Yk ((BX[p]! : UInt32)&&&0xFFFF)-mm+YU BW[o.toNat+1]!<=15)
       let ans:=if fast then r28PC128 k.toUSize f u v B D b[o.toNat]! b[o.toNat+1]! cb db done0 done1 0 0 0 0 0
        else qCtx7 k.toUSize f u v B D b[o.toNat]! b[o.toNat+1]! cb db done0 done1 0 0 0 0 0
       (act relu ans.toUInt32).toUInt64 ||| ((act relu (ans>>>32).toUInt32).toUInt64<<<32)
      else (act relu (done0 (Y5 k.toUSize f u B b[o.toNat]! 0 0 0))).toUInt64
     else 0) (((C+1)/2)*hw).toUSize 0 0 0 (Array.mkEmpty (C*hw)) (Array.mkEmpty hw)
   else ao s relu x w b
  else ao s relu x w b
 else ao s relu x w b
'''


def r28_remove_decl(s,name):
    pat=re.compile(r'(?m)^(?:@\[[^\n]+\]\s+)?(?:lemma|theorem) '+re.escape(name)+r'\b')
    matches=list(pat.finditer(s));assert len(matches)==1,(name,len(matches))
    a=matches[0].start();nxt=re.search(r'(?m)^(?:@\[[^\n]+\]\s+)?(?:def|lemma|theorem|set_option|structure|local|end)\b',s[matches[0].end():])
    assert nxt;b=matches[0].end()+nxt.start()
    return s[:a]+s[b:]

def transform(raw,submission,variant):
    assert submission==53 and variant=='pointwise128-nat-typed'
    assert hashlib.sha256(raw).hexdigest()==BASE_SHA
    s=raw.decode();removed=['correct','rBnCorrect','bCp','aq','ar','ax','av','au','az','poolProvedZero','an','aj','al']
    for name in removed:s=r28_remove_decl(s,name)
    for name in removed:
        if len(name)>=4:assert not re.search(r'\b'+re.escape(name)+r'\b',s),name
    mark='def kernels:Kernels where';assert s.count(mark)==1;s=s.replace(mark,HELPER+mark)
    assert s.count('conv:=⟨ao,ap⟩')==1;s=s.replace('conv:=⟨ao,ap⟩','conv:=⟨r28PW,ap⟩')
    result,_=build(s.encode(),strict_base=False)
    assert len(result)<=256000
    return result

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('source',type=Path);p.add_argument('output',type=Path);a=p.parse_args()
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(transform(a.source.read_bytes(),53,'pointwise128-nat-typed'))
