"""Owned two-block lazy-word-preparation discriminator for historical R26.
Runtime-only; no Submission.correct is introduced or inherited. Droot owns CI.
"""
from pathlib import Path
import argparse,hashlib,json
from datetime import datetime,timezone
EXPECTED='ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540'

def transform(raw):
 assert hashlib.sha256(raw).hexdigest()==EXPECTED
 s=raw.decode('utf-8').replace('\r\n','\n')
 old='''def prepare (raw : Array UInt32) : Prepared :=
  ⟨R24PortableF64.prepare raw, prepareOperand raw⟩'''
 new='''def prepare (raw : Array UInt32) : Prepared :=
  ⟨R24PortableF64.prepare raw, ⟨#[], #[], 0, 0, true, true, false⟩⟩'''
 assert s.count(old)==1;s=s.replace(old,new)
 old='''  if guess == 0 then exact (pair left.word right.word) else guess'''
 new='''  if guess == 0 then
    exact (pair (prepareOperand left.fp.raw) (prepareOperand right.fp.raw))
  else guess'''
 assert s.count(old)==1;s=s.replace(old,new)
 assert 'left.word'not in s and 'right.word'not in s
 return s.encode('utf-8')

def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path);p.add_argument('--receipt',type=Path);a=p.parse_args()
 root=next(p for p in Path(__file__).resolve().parents if(p/'AGENTS.md').is_file())
 source=root/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/development/native/fp-word-conv6-local/Kernel.lean';raw=source.read_bytes();out=transform(raw)
 if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(out)
 r=dict(at_utc=datetime.now(timezone.utc).isoformat(),source_path=source.relative_to(root).as_posix(),source_sha256=EXPECTED,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),patch_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),change='Only R26WordFallback.prepare and dotPrepared miss branch change; FP arithmetic/checker/caches/callers unchanged. Dummy word field is unused; actual integer Operand prepared on demand for both original arrays after a miss. No lazy caching of integer state is assumed.',model_cost_counts='census/SUMMARY.json: eager5009400 terms vs uncachedlazy158320 for108oldseenb1cells',proof='UNPROVED_NATIVE_ONLY_NO_NEW_CORRECT',policy='NOT_RUN_ON_RECONSTRUCTED_FILE',native='NOT_RUN',champion='UNKNOWN',formal_submission=False,local_build=False)
 if a.receipt:a.receipt.write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
 print(json.dumps(r,ensure_ascii=False,indent=2))
if __name__=='__main__':main()
