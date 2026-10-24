from pathlib import Path
import hashlib,json
h=Path(__file__).resolve().parent;p=h.parent/'f01-d11-bmm-direct-batch-rows/Kernel.lean'
a=p.read_bytes();assert hashlib.sha256(a).hexdigest()=='1c544655a8bc6e1d5267dcf98fc1359263cba5da71bc9c72924119b0fa60e6e2'
s=a.index(b'def batchRowIndex (');e=a.index(b'\n\n/-- Both input batch bases',s)
o=a[s:e];assert o.count(b'rw [Nat.add_mul] at h')==1
n=o.replace(b'rw [Nat.add_mul] at h',b'rw [Nat.succ_mul] at h');b=a[:s]+n+a[e:]
assert b.replace(n,o)==a and (h/'Kernel.lean').read_bytes()==b
m=json.loads((h/'manifest.json').read_bytes());assert hashlib.sha256(b).hexdigest()==m['candidate_sha256'] and len(b)==m['candidate_bytes']<=256000
print(json.dumps({'exact_one_proof_edit_and_inverse':'PASS','sha256':m['candidate_sha256'],'bytes':len(b),'new_Lean':'NOT_RUN'}))
