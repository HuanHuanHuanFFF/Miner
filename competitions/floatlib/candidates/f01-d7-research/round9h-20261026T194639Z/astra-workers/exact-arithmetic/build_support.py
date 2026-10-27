from pathlib import Path
import re,json,hashlib
D=Path(__file__).resolve().parent
F=D.parents[4]
old=F/'candidates/f01-d7-research/round11h-20261025T173831Z/astra-workers/structural-frontier/integer-normal-mul/public-entry-repair1/Kernel.lean'
s=old.read_text(encoding='utf8')
s=s[s.index('section R17UInt64InterfaceProbe'):]
def ns(name):
    return 'namespace Submission.'+name+'\n\nopen FloatLib.Floats Competition\nopen FloatLib.Floats.Formats.BinaryInterchange\nopen FloatLib.Numerics\n\n'
def theorem(name):
    # Name is unique in this exact file when extracting only the required support.
    m=list(re.finditer(r'^theorem '+re.escape(name)+r'\b',s,re.M))
    assert len(m)==1,(name,len(m))
    start=m[0].start()
    e=re.search(r'^((?:@\[[^\n]*\]\s*)?(?:theorem|def|end|namespace)\b|/[-*])',s[m[0].end():],re.M)
    assert e
    return s[start:m[0].end()+e.start()].rstrip()+'\n\n'
nat=['leading_bounds','no_carry_at_47','mantissa_bounds']
text=ns('R14NatNormal')+''.join(theorem(n) for n in nat)+'end Submission.R14NatNormal\n\n'
text+=ns('R14ExponentShift')
text+='def product (mx my : UInt32) : Nat := mx.toNat * my.toNat\ndef middleExponent (p : Nat) : Nat := p.log2 + R14NatNormal.carry p + 127\ndef storedFraction (p : Nat) : Nat := R14NatNormal.mantissa p - 8388608\n\n'
text+=''.join(theorem(n) for n in ['product_bounds','middle_bounds'])+'end Submission.R14ExponentShift\n\n'
support=(old.parent.parent/'Old-model-support-v1.lean.inc').read_text(encoding='utf8')
st=support.index('namespace Submission.R14NatNormal')
en=support.index('end Submission.R14NatNormal',st)+len('end Submission.R14NatNormal')
support=support[:st]+support[en:]
text+=support
(D/'Verified-model-support.lean.inc').write_text(text,encoding='utf8',newline='\n')
rec={'source':str(old),'sha256':hashlib.sha256(old.read_bytes()).hexdigest(),'new_bytes':len(text.encode()),'new_sha256':hashlib.sha256(text.encode()).hexdigest(),'scope':'Exact R18 verified support declarations with R18 namespace changed to Submission; duplicate U32-foundation raw_normal_decode omitted; full new package needs validation.'}
(D/'support-manifest.json').write_text(json.dumps(rec,indent=2)+'\n',encoding='utf8')
print(json.dumps(rec,indent=2))
