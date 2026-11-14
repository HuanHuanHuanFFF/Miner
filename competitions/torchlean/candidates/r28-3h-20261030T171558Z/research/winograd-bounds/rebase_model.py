"""Exact dyadic/bias rebase checks; no native execution or all12 proof."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,random
def main():
 here=Path(__file__).resolve().parent;root=next(p for p in here.parents if (p/'AGENTS.md').is_file())
 helper=root/'competitions/torchlean/candidates/r27-5h-20261029T194443Z/research/board-frontier/norm_frontier.py'
 sp=importlib.util.spec_from_file_location('r28_rebase_round',helper);f=importlib.util.module_from_spec(sp);sp.loader.exec_module(f)
 rng=random.Random(0x284);n=0;zero=0;old_cb_wrong=0
 for _ in range(20000):
  B=rng.choice([2,3,26,100,200,240,300,380,400,511])
  body=rng.randrange(-(1<<90),1<<90)
  e=rng.randrange(255);mant=rng.randrange(1<<23) if e==0 else (1<<23)+rng.randrange(1<<23)
  sign=rng.randrange(2);idx=max(e-1,0)
  if idx+126<B:mant=0
  bias=(-1 if sign else 1)*(mant<<(idx+149-B)) if mant else 0
  old=body+bias;new=4*body+4*bias
  assert new==4*old
  a=f.round_ratio(old,1,B-298);b=f.round_ratio(new,1,B-300)
  assert a==b;n+=1
  zero+=old==0
  if bias and f.round_ratio(4*body+bias,1,B-300)!=a:old_cb_wrong+=1
 # A directed unchanged-context counterexample: body0,bias1 at B240.
 bias=(1<<149) # numeric denominator representation isn't used here; use pure lattice units next.
 B=240;body=0;bias=1<<58
 correct=f.round_ratio(body+bias,1,B-298)
 wrong=f.round_ratio(4*body+bias,1,B-300)
 assert correct==0x3f800000 and wrong==0x3e800000
 out={'state':'EXACT_DYADIC_MODEL_ONLY','at_utc':datetime.now(timezone.utc).isoformat(),
  'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
  'finite_rounding_checks':n,'unchanged_bias_context_differences':old_cb_wrong,
  'directed_old_context_failure':{'B0':240,'old_value_word':'3f800000','wrong_unchanged_context_word':'3e800000'},
  'UInt64_subtract_guard':'B0>=2 required; B0=0/1 fallback',
  'signedzero':'Raw provenance fallback still required, not discharged by this integer model',
  'Lean':'NOT_COMPILED','Kernel':'NOT_IMPLEMENTED','native':'NOT_RUN'}
 (here/'rebase-result.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out))
if __name__=='__main__':main()
