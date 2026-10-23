from pathlib import Path
import datetime, hashlib, json

out=Path(__file__).resolve().parent
parent=out.parent/'f01-r10-bmm-singleton-native/Kernel.lean'
raw=parent.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='ff34b1b7e2166b7b22f53d5f3e656b6567fd7487d457343e3599885757ab25ad'
assert not (out/'Kernel.lean').exists(), 'Frozen source cannot be overwritten'
s=raw.decode()
start=s.index('\ndef singletonCore (')
end=s.index('\ndef bmm (batch m n p : Nat)',start)
old=s[start:end]
new=old.replace('(D7SingletonNative.nativeProduct (A.toArray.getD','(Submission.mul (A.toArray.getD').replace('  rw [D7SingletonNative.nativeProduct_eq]\n','')
assert new!=old and 'D7SingletonNative.nativeProduct' not in new
result=(s[:start]+new+s[end:]).encode()
assert len(result)<=256000
(out/'Kernel.lean').write_bytes(result)
donor=out.parent/'f01-d7-singleton-normalize/Kernel.lean'
donor_text=donor.read_text()
donor_block=donor_text[donor_text.index('\ndef singletonCore ('):donor_text.index('\ndef bmm (batch m n p : Nat)',donor_text.index('\ndef singletonCore ('))]
assert new==donor_block, 'Runtime/proof port must exactly match the historical normalized scalar singleton block'
m={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(result).hexdigest(),'candidate_bytes':len(result),
   'parent':parent.parent.name,'parent_sha256':hashlib.sha256(raw).hexdigest(),'retained_baseline_sha256':'41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7',
   'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
   'historical_runtime_source':donor.parent.name,'historical_source_sha256':hashlib.sha256(donor.read_bytes()).hexdigest(),
   'mechanism':'Exact historical scalar-product singleton block transplanted onto current proven ff34/41. n=1 uses current tuned Submission.mul (including raw low-exponent path), then exact negative-zero seed normalization; n!=1 retained41. Unlike6ba no raw-product-to-native conversion or native accumulator is introduced.',
   'delta':'Only one runtime call nativeProduct -> Submission.mul and removal of its now-unneeded equality rewrite. All other parent bytes retained.',
   'validation_mode':'full-gate','proof_status':'NOT_RUN_EXACT_NEW_SOURCE','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_bytes((json.dumps(m,indent=2)+'\n').encode())
print(json.dumps(m))
