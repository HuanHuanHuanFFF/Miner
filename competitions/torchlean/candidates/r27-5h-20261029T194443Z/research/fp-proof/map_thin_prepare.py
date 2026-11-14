from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
H=Path(__file__).parent;ROOT=Path.cwd();old=ROOT/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/development/native/fp-word-conv6-local/Kernel.lean';new=H.parent/'fp-cost/LazyFPOnly.lean'
a=old.read_text(encoding='utf-8-sig').replace('\r\n','\n');b=new.read_text(encoding='utf-8-sig').replace('\r\n','\n');assert hashlib.sha256(new.read_bytes()).hexdigest()=='7cc98e2bea5096e486800075e3f192589b9b1c35f277fe5af344b7fbf7626b21'
def scope(s):
 i=s.index('namespace Submission.R24PortableF64');return s[i:s.index('end Submission.R24PortableF64',i)]
a,b=scope(a),scope(b)
def cut(s,x,y):
 assert s.count(x)==1,(x,s.count(x))
 i=s.index(x);return s[i:s.index(y,i)].rstrip()+'\n'
blocks=[('bit_checker','@[inline] def finite64 (word : UInt64)','def sumRemaining ('),('sumRemaining','def sumRemaining (','/-- Zero is a miss sentinel.'),('widenBits','@[inline] def widenBits (word : UInt32)','def prepare (raw : Array UInt32)'),('ceilLog2','@[inline] def ceilLog2 (n : Nat)','@[inline] def finite64 (word : UInt64)'),('prepare_syntax','def prepare (raw : Array UInt32)','@[inline] def ceilLog2')]
rows=[]
for name,start,end in blocks:
 x,y=cut(a,start,end),cut(b,start,end)
 rows.append(dict(name=name,old_sha256_LF=hashlib.sha256(x.encode()).hexdigest(),new_sha256_LF=hashlib.sha256(y.encode()).hexdigest(),byte_identical_LF=x==y,identical_after_named_log2_substitution=x.replace('Submission.FastMul.fastLog2','log2word')==y,semantic_limit='Same prepare syntax still calls changed widenBits binding'if name=='prepare_syntax'else'No new entire-module correctness inference'))
r=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='READ_ONLY_MAPPING_NO_INTEGRATION_PROOF_EXPANSION',old_runtime_sha256=hashlib.sha256(old.read_bytes()).hexdigest(),new_owned_helper_sha256=hashlib.sha256(new.read_bytes()).hexdigest(),blocks=rows,accepted_reusable='UInt64 bitkey and finite rawReal lemmas independent of preparation; actualchecker extension pending but byte-identical bitblock means same owned proof view applicable after exactsource compile',new_required=['Bind actual public12 log2word implementation toNat.log2; do not claimrfl tooldFastMul source','Prove prepareFn n get n/values/peak/valid projections equal prepare(Array.ofFn n get), with same actual newwiden binding','Only then import prepared value/peak/sumerror and exactrawdot bridge; all12cachedlinear getters/bias/strongcallback separately'],priority='Wait newthin completecall nativecost as parent20:49requests before expanding integration proof',parallel_follow_on='Four-chain paper and18KB helper useoriginalradius forL>=3; old108cell exactRNE model agrees but not selected or queued',current_champion='UNKNOWN')
(H/'THIN-PREPARED-MAPPING.json').write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
p=H/'status.json';d=json.loads(p.read_bytes());d['updated_at_utc']=datetime.now(timezone.utc).isoformat();d['processed_inbox'].append('父R20:49thinFPcostsource');d['active_work']='Thinprepare mapping checked byte-for-byte; no integrationproof expansion beforecost. Four-chain follow-on preservesradius paper/source and108oldcohort finitechecks; currentproof requests unchanged.';p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r,ensure_ascii=False,indent=2))
