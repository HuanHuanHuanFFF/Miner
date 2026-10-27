"""Finite ordered-expression and address check, no floating-point oracle or Lean."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,re
H=Path(__file__).resolve().parent;sha=lambda b:hashlib.sha256(b).hexdigest()
for name in('audit.py','build_rawpair_draft.py','validate_draft.py'):ast.parse((H/name).read_text())
rec=json.loads((H/'draft-receipt.json').read_text());b=(H/'Kernel-dc-rawpair.draft.lean').read_bytes()
assert sha(b)==rec['draft_sha256'] and len(b)==rec['draft_bytes']
src=(H/'RawPair.lean.inc').read_text()
assert all(s not in src for s in('.map','packB','R2W01b.convert','UInt32.toFloat32','sorry','axiom ','unsafe ','implemented_by','extern '))
assert src.count('ExecFloat.Binary.toFloat32 (')==3
assert 'if count = 1 then\n    RowStream.emit count' in src
assert 'if n ≤ 1 ∨ p ≤ 1 then DirectContinuous.core' in src
group_from=src[src.index('@[inline] def groupFrom'):src.index('@[inline] def group (')]
row=src[src.index('@[inline] def row ('):src.index('theorem row_prefix')]
assert ' / 'not in group_from and row.count('r.val / m')==1
def read(a,i):return a[i] if i<len(a) else 'POSZERO'
def old(n,ba,bb,p,A,B,k=0,acc='FZERO'):
    for t in range(k,n):acc=(acc,read(A,ba+t),read(B,bb+t*p))
    return acc
def pair(n,ba,bb,p,A,B,k=0,s0='FZERO',s1='FZERO'):
    for t in range(k,n):
        a=read(A,ba+t)
        s0=(s0,a,read(B,bb+t*p));s1=(s1,a,read(B,bb+1+t*p))
    return s0,s1
projection=0
for n in range(7):
 for k in range(n+2):
  for ba in range(4):
   for bb in range(4):
    for p in range(5):
     for la,lb in((0,0),(2,3),(9,11)):
      A=[f'A{i}'for i in range(la)];B=[f'B{i}'for i in range(lb)]
      x,y=pair(n,ba,bb,p,A,B,k,'S0','S1')
      assert x==old(n,ba,bb,p,A,B,k,'S0') and y==old(n,ba,bb+1,p,A,B,k,'S1');projection+=1
layouts=0;tails=0
for batch in range(4):
 for m in range(5):
  for n in range(6):
   for p in range(11):
    A=[f'A{i}'for i in range(batch*m*n)];B=[f'B{i}'for i in range(batch*n*p)]
    ref=[];out=[]
    for r in range(batch*m):
     ba=r*n;bb=(r//m)*n*p
     ref.extend((old(n,ba,bb+j,p,A,B),bb+j)for j in range(p))
     for g in range((p+1)//2):
      start=2*g;count=min(2,p-start)
      if count==1:
       out.append((old(n,ba,bb+start,p,A,B),bb+start));tails+=1
      else:
       v=pair(n,ba,bb+start,p,A,B)
       out.extend((v[j],bb+start+j)for j in range(count))
    if n<=1 or p<=1:out=ref[:]
    assert out==ref and len(out)==batch*m*p;layouts+=1
result=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='STATIC_INVERSE_AND_FINITE_ORDERED_EXPRESSION_PASS_LEAN_NOT_RUN',
 draft_sha256=sha(b),draft_bytes=len(b),projections=projection,full_shape_layouts=layouts,scalar_tail_evaluations=tails,
 semantics='Opaque per-lane ordered accumulator expression and original raw finish arguments; no commutation/reassociation/FMA assumptions',
 limitations='Finite model is not Lean acceptance, IEEE validation, code generation, timing or adoption; all remain NOT_RUN/UNKNOWN')
(H/'draft-validation.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result,indent=2))
