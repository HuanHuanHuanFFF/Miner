"""Original type-spelling compaction, preserving every declaration/proof body.

UNCOMPILED as a source transform; use inside an exact final candidate and re-gate.
Only standalone type constants after the prelude change, not namespace selectors.
"""
import hashlib,re
BASE_SHA='ea6f582fc7a416b8860adb5c71fe3ab670dd4add01999fac7190993110f605a3'
ALIASES={'UInt64':'UU','UInt32':'VV','Word':'WW','Array':'AA0','Nat':'NN'}
def compact(raw:bytes,strict_base=True)->bytes:
    if strict_base:assert hashlib.sha256(raw).hexdigest()==BASE_SHA
    s=raw.decode('utf-8');lines=s.splitlines(keepends=True)
    assert lines[0].strip()=='import ContractExact' and lines[1].strip()=='namespace Submission'
    # The long line3 owns namespace opening/renaming, notation and possibly declarations.
    pre=''.join(lines[:3]);body=''.join(lines[3:])
    for alias in ALIASES.values():assert not re.search(r'(?<![\w.])'+alias+r'(?![\w.])',s),alias
    for old,new in ALIASES.items():body=re.sub(r'(?<![\w.])'+old+r'(?![\w.])',new,body)
    notation=''.join(f'local notation "{new}" => {old}\n' for old,new in ALIASES.items())
    return (pre+notation+body).encode('utf-8')
