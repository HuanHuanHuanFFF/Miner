from pathlib import Path
import datetime,hashlib,json
HERE=Path(__file__).resolve().parent
src=json.loads((HERE/'newer-mul-source-response.json').read_text(encoding='utf8'))
data=src['content'].encode('utf8')
(HERE/'sources/Newer-Arithmetic-LeanModel-MulDiv.lean').write_bytes(data)
(HERE/'newer-mul-source-receipt.json').write_text(json.dumps({k:v for k,v in src.items() if k!='content'}|{'sha256':hashlib.sha256(data).hexdigest(),'bytes':len(data)},indent=2)+'\n',encoding='utf8')
text=src['content']
start=text.index('theorem le_targetExponent_totalExponent_iff')
end=text.index('/--\nFor nonzero mantissas, the provisional quotient')
helpers=text[start:end]
draft=(HERE/'native-mul-bridge-draft.lean').read_text(encoding='utf8')
anchor='open Float.Model.UnpackedFloat\n'
draft=draft.replace(anchor,anchor+'open FloatLib.Floats.Formats.BinaryInterchange.Model\n\n/-\nThe three target-exponent lemmas below are ported from FloatLib Team, MIT,\ncommit 1f5771b3e36a98f17fcac2c6d76aaa024b36aa37,\nArithmetic/LeanModel/MulDiv.lean. Official pinned dependencies are unchanged.\n-/\n'+helpers)
draft=draft.replace('  cases hxmodel : Model.toModel x', '  have hzero := FloatFormat.supportsSignedZero_eq_true_of_isIEEE fmt hfmt\n  cases hxmodel : Model.toModel x',1)
signs='''Model.negZero_eq_ofModel_zero, hzero,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]'''
draft=draft.replace('Model.negZero_eq_ofModel_zero]',signs)
old='''  case finite.finite sign₁ mantissa₁ exponent₁ hmantissa₁ sign₂ mantissa₂ exponent₂ hmantissa₂ =>
    rw'''
new='''  case finite.finite sign₁ mantissa₁ exponent₁ hmantissa₁ sign₂ mantissa₂ exponent₂ hmantissa₂ =>
    have hle := add_le_targetExponent_totalExponent_mul (FloatFormat.toModel fmt)
      hmantissa₁ hmantissa₂
      (le_targetExponent_totalExponent_of_toModel_eq_finite x hxmodel)
      (le_targetExponent_totalExponent_of_toModel_eq_finite y hymodel)
    have hr (sign : Sign) :
        Float.Model.UnpackedFloat.roundWithAccuracy (FloatFormat.toModel fmt) sign
          (mantissa₁ * mantissa₂) (exponent₁ + exponent₂) .exact =
        Float.Model.UnpackedFloat.round (FloatFormat.toModel fmt) sign
          (mantissa₁ * mantissa₂) (exponent₁ + exponent₂) :=
      Model.roundWithAccuracy_exact_eq_round_of_le_targetExponent _ _ _ _ hle
    rw'''
assert old in draft
draft=draft.replace(old,new)
draft=draft.replace('''        Float.Model.UnpackedFloat.round]''','''        hr,
        show Sign.negative * Sign.negative = Sign.positive from rfl,
        show Sign.negative * Sign.positive = Sign.negative from rfl,
        show Sign.positive * Sign.negative = Sign.negative from rfl,
        show Sign.positive * Sign.positive = Sign.positive from rfl]''')
out=HERE/'native-mul-bridge-proof1.lean'
out.write_text(draft,encoding='utf8',newline='\n')
print(json.dumps({'path':str(out),'sha256':hashlib.sha256(out.read_bytes()).hexdigest(),'bytes':out.stat().st_size,'status':'PROOF_DRAFT_NOT_COMPILED','generated_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat()},indent=2))
