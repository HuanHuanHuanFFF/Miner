from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,time
H=Path(__file__).resolve().parent;R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file());start=time.monotonic()
def hashes(p):
 d=p.read_bytes();return dict(bytes=len(d),sha256=hashlib.sha256(d).hexdigest(),git_blob_sha1=hashlib.sha1(b'blob '+str(len(d)).encode()+b'\0'+d).hexdigest())
castdir=R/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/development-sources/lean-int-casts'
receipt=json.loads((castdir/'receipt.json').read_text());checks=[]
for name in ('Float32-runtime.lean.raw','Float32-model.lean.raw'):
 row=next(x for x in receipt['files'] if x['path'].endswith(name));p=R/row['path'];facts=hashes(p)
 assert all(facts[k]==row[k] for k in ('bytes','sha256','git_blob_sha1'))
 checks.append(dict(path=str(p.relative_to(R)),url=row['url'],**facts))
pub=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/astra-workers/public-source-runtime'
idx=json.loads((pub/'source-index.json').read_text())
for name in ('lean-header.txt',):
 row=next(x for x in idx['sources'] if x['file'].replace('\\','/').endswith('/'+name));p=pub/row['file'];facts=hashes(p);assert facts['sha256']==row['sha256']
 checks.append(dict(path=str(p.relative_to(R)),url=row['url'],**facts))
tag=json.loads((pub/'sources/lean-tag.txt').read_text());assert tag['object']['sha']=='293d5d0c0c3f3dded4688b3ccd6a33939ac5102b'
checks.append(dict(path=str((pub/'sources/lean-tag.txt').relative_to(R)),url=tag['url'],**hashes(pub/'sources/lean-tag.txt')))
expected={'ToNat.lean':('0ceda6d0614e06b8acbfe872921378edaa442f5f',3832),'OfNat.lean':('4abdecf71d1340f858d62d582fe4dad0ee068c26',2424)}
for name,(blob,n) in expected.items():
 p=H/name;facts=hashes(p);assert facts['git_blob_sha1']==blob and facts['bytes']==n
 checks.append(dict(path=str(p.relative_to(R)),url='https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Unpacked/Operations/'+name,**facts))
ops=H/'Operations.lean';checks.append(dict(path=str(ops.relative_to(R)),url='https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Unpacked/Operations.lean',**hashes(ops)))
N=2164260735
record=dict(checked_utc=datetime.now(timezone.utc).isoformat(),state='AVAILABLE_UNFOLDABLE_MODEL_NOT_CLOSED_ROUNDTRIP_PROOF',
 lean_commit=tag['object']['sha'],first_discriminator='Float32.toUInt32 is def, not opaque; imported public model reaches UnpackedFloat.toUInt32/toInt/roundToInt and UInt32.ofNatClamp',
 declarations=[dict(file='Float32-runtime.lean.raw',lines=[223,224],name='Float32.toUInt32'),dict(file='Float32-model.lean.raw',lines=[270,270],name='Float32.Model.toUInt32'),dict(file='ToNat.lean',lines=[56,57],name='Float.Model.UnpackedFloat.toUInt32'),dict(file='ToNat.lean',lines=[22,25],name='Float.Model.UnpackedFloat.roundToInt')],
 source_bindings=checks,
 bound_arithmetic=dict(Nmax=N,UInt32_size=2**32,highest_possible_bit=N.bit_length()-1,maximum_nonnegative_RNE_shift=N.bit_length()-1-23,loose_RNE_upper=N+128,loose_upper_below_uint32=N+128<2**32,
  warning='d<=7 is input alignment gap; carry can make h=31 and shift8. These integer identities do not prove the Float32 roundtrip.'),
 proof_gap='No already-closed theorem for this complete bounded UInt32->Float32->UInt32/repack family established in the bounded inspection; prove finite integer rounded value, no clamp, exact truncate, and integer repack equality.',
 compiled='NOT_RUN',timing='UNKNOWN',full_candidate=False,new_axioms=False,ci=False,elapsed_seconds=time.monotonic()-start)
assert record['elapsed_seconds']<4.5
(H/'receipt.json').write_text(json.dumps(record,indent=2)+'\n')
print(json.dumps(dict(state=record['state'],sources=len(checks),bounds=record['bound_arithmetic'],seconds=record['elapsed_seconds'])))
