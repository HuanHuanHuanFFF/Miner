"""Closed-form controls, no giant arrays or native claims."""
from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
B=1<<32;M=1<<64;MASK=M-1
def s64(x):return (x+M//2)%M-M//2
def repeated(n,p,signed):
 word=p&MASK;l=(n*word)&MASK
 qi=(p>>32) if signed else word>>32
 q=(n*qi)&MASK;a=(q<<32)&MASK
 high=(((s64(q)>>32) if signed else q>>32)+int(l<a))&MASK
 bits=(high<<64)|l
 return bits-(1<<128) if signed and high>>63 else bits
def main():
 vals=[]
 for signed,n,p,expected in [(True,B,-M//2+1,True),(True,B+1,-M//2+1,False),(False,B+1,M-1,True),(False,B+2,M-1,False)]:
  true=n*p;got=repeated(n,p,signed);assert (got==true)==expected
  vals.append({'signed':signed,'n':n,'p':str(p),'exact':str(true),'reconstructed':str(got),'equal':expected,'difference':str(got-true)})
 assert int(vals[1]['difference'])==1<<96
 out={'state':'PAPER_SHARP_BOUND_WITH_CLOSED_FORM_CONTROLS','at_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'signed_uniform_max_n':B,'unsigned_uniform_max_n':B+1,'cases':vals,'allocation':'No n-sized array created','original_runtime_draft':'Unchanged conservative n<2^32','Lean':'NOT_COMPILED','native':'NOT_RUN'}
 Path(__file__).with_name('sharp-length-result.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out))
if __name__=='__main__':main()
