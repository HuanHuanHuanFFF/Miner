"""Native cost discriminator; old proof stays bound only to retained kernels.

Read the exact released public23 source at runtime. Never claim the new kernels
have inherited its correctness proof. No whole upstream body is redistributed.
"""
import hashlib
import re

PIN='1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe'

def declaration(text,name):
    pattern=r'(?m)^(?:@\[[^\n]*\] )?def '+name+r'\b'
    start=re.search(pattern,text);assert start,name
    following=re.search(r'(?m)^(?:@\[[^\n]*\] )?(?:def |theorem |lemma |structure |namespace |end\b)',text[start.end():])
    return text[start.start():start.end()+following.start()]

def once(text,before,after):
    assert text.count(before)==1,(before,text.count(before))
    return text.replace(before,after,1)

def transform(data,submission=23,variant='reciprocal-cost'):
    assert submission==23 and variant=='reciprocal-cost'
    assert hashlib.sha256(data).hexdigest()==PIN
    text=data.decode('utf-8')
    output=declaration(text,'Ya7G')
    output=once(output,'def Ya7G ','def R27CostOutput ')
    output=once(output,'(S1a:UInt64):Word :=','(S1a R27R:UInt64):Word :=')
    output=once(output,'let q0:=cv/D\n   let r0:=cv%D*Yf gw\n   let qq:=q0*Yf gw+r0/D',
      'let qr0:=R27CostDiv cv D R27R\n   let q0:=qr0.1\n   let r0:=qr0.2*Yf gw\n   let qr1:=R27CostDiv r0 D R27R\n   let qq:=q0*Yf gw+qr1.1')
    output=once(output,'let ra:=(r0%D)<<<ks\n    let qa:=(qq<<<ks)+ra/D\n    let rr:=ra%D',
      'let ra:=qr1.2<<<ks\n    let qr2:=R27CostDiv ra D R27R\n    let qa:=(qq<<<ks)+qr2.1\n    let rr:=qr2.2')
    model=declaration(text,'MYbc')
    model=once(model,'def MYbc ','def R27CostNorm ')
    model=once(model,'  let nU:=if n < 4096 then n.toUInt64 else 0\n',
      '  let nU:=if n < 4096 then n.toUInt64 else 0\n  let recs:=Array.ofFn (n:=rows) fun r=>(0xffffffffffffffff:UInt64)/(nU*Yf st[r.val]!.2.2)\n')
    model=once(model,';Ya7G n ', ';R27CostOutput n ')
    model=once(model,' nU u.2.2 u.1 u.2.1\n',' nU u.2.2 u.1 u.2.1 recs[r]!\n')
    kernel=declaration(text,'kernels')
    kernel=once(kernel,'norm:=⟨Ybb2,MYbc⟩','norm:=⟨Ybb2,R27CostNorm⟩')
    text=once(text,'def kernels:Kernels','def retainedKernels:Kernels')
    theorem=re.search(r'(?m)^theorem correct:.*$',text);assert theorem
    proof=re.sub(r'\bkernels\b','retainedKernels',theorem.group())
    proof=once(proof,'theorem correct:','theorem retainedCorrect:')
    text=text[:theorem.start()]+proof+text[theorem.end():]
    runtime='''@[inline] def R27CostDiv (a d mu:UInt64):UInt64×UInt64 :=
 if d == 0 then (a/d,a%d) else
 let q:=(m64 a mu).1
 let r:=a-q*d
 if d ≤ r then (q+1,r-d) else (q,r)
'''
    result=once(text,'end Submission',runtime+output+model+kernel+'end Submission').encode('utf-8')
    assert len(result)<=256000,len(result)
    assert b'theorem correct:' not in result
    return result
