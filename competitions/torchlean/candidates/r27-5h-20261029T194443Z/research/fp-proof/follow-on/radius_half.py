from pathlib import Path
import json,hashlib,importlib.util,sys,collections
from datetime import datetime,timezone
sys.dont_write_bytecode=True
H=Path(__file__).parent;C=H.parent/'census';p=C/'fp_replay-frozen.py';spec=importlib.util.spec_from_file_location('fp_frozen_math',p);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
def units(w):
 if not(w&0x7fffffffffffffff):return 0
 e=(w>>52)&2047;mant=(1<<52)|(w&((1<<52)-1));shift=e-772
 if shift>=0:a=mant<<shift
 else:
  a,r=divmod(mant,1<<-shift);assert r==0
 return -a if w>>63 else a
rows=[];counts=collections.Counter()
for root in [26102901,26102903]:
 d=json.loads((C/f'fp-census-{root}.json').read_bytes())
 for c in d['cells']:
  for x in c['rejections']:
   S=units(int(x['sum_word'],16));R=1<<(x['H']+2*x['L']);q=int(x['guess'],16);assert R>1
   ok,reason=m.certify(int(x['sum_word'],16),m.bits64(m.rnd53(S-R//2)),m.bits64(m.rnd53(S+R//2)),q)
   counts['newly_accept'if ok else'still_reject']+=1
   assert x['error_over_radius'][0]<=R//2
   if ok:assert q==int(x['expected'],16)
   rows.append(dict(root=root,cell=c['cell'],n=x['n'],H=x['H'],L=x['L'],new_accept=ok,reason=reason))
assert len(rows)==155
result=dict(at_utc=datetime.now(timezone.utc).isoformat(),status='FOLLOW_ON_NOT_SELECTED',prior_rejections=155,counts=counts,rows=rows,source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),source_cohort='Only155stored rejects from108alreadyseenR26b1cells, not a new holdout',mathematical_route='SUM3 already derives |RN(x)-x|<=ulp(x)/2 and ulp<=p2(K-53), then weakens to full p2(K-53). Keeping the half yields p2(K-54); the unchanged loop induction would give radius H+2L-304 and word offset719. This paper reduction needs exact source/root acceptance before changing runtime.',decision='Do not replace primary radius or create another nativevariant now. Lazy preparation removes96.84percent of backup inputword work in thiscohort; tighter radius only affects155/69600calls and needs own proof/completecall cost. Revisit if lazy nativecost shows remaining misses dominate.',proof='NOT_RUN_NEW_HALF_BOUND',performance='UNKNOWN',formal_submission=False)
(H/'radius-half-opportunity.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8');print(json.dumps({'prior_rejects':155,'counts':counts,'status':result['status']}))
