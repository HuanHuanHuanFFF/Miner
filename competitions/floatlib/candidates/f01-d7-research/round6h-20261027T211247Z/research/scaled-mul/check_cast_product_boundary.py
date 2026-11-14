"""Exact integer nearest-even discriminator for the optional product cast lemma."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib, json

HERE=Path(__file__).resolve().parent
def rounded_integer(n):
    shift=max(0,n.bit_length()-24)
    if not shift:return n
    q,r=divmod(n,1<<shift)
    half=1<<(shift-1)
    return (q+int(r>half or (r==half and q&1)))<<shift
rows=[]
for a,b in [(8388608,8388608),(16777215,16777215),(8388609,16777214),(16777217,16777217)]:
    direct=rounded_integer(a*b)
    factored=rounded_integer(rounded_integer(a)*rounded_integer(b))
    rows.append({'a':a,'b':b,'a_rounded':rounded_integer(a),'b_rounded':rounded_integer(b),
                 'direct_product_cast':direct,'separate_cast_then_mul':factored,'equal':direct==factored,
                 'in_proposed_domain':8388608<=a<16777216 and 8388608<=b<16777216})
assert all(r['equal'] for r in rows if r['in_proposed_domain'])
assert not rows[-1]['equal']
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'EXACT_INTEGER_BOUNDARY_DISCRIMINATOR',
     'source_sha256':hashlib.sha256((HERE/'Cast-product-equivalence.lean.inc').read_bytes()).hexdigest(),
     'rows':rows,'scope':'Exact four-case arithmetic only, not native execution or a Lean proof.',
     'decision':'The exact input decode condition cannot be dropped when replacing two UInt32 casts and Float32 multiplication by one UInt64 product cast.'}
(HERE/'cast-product-boundary.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,indent=2))
