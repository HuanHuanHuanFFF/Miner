from pathlib import Path
import argparse,hashlib,json
from datetime import datetime,timezone
from patch_lazy_prepare import transform,EXPECTED

def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path);p.add_argument('--receipt',type=Path);a=p.parse_args()
 here=Path(__file__).parent;root=next(p for p in here.parents if(p/'AGENTS.md').is_file())
 source=root/'competitions/torchlean/candidates/r26-1h-20261029T085515Z/development/native/fp-word-conv6-local/Kernel.lean'
 fragment=here/'LazyScalarEquivalence.lean.inc';out=transform(source.read_bytes())+b'\n'+fragment.read_text(encoding='utf-8-sig').encode('utf-8')
 if a.output:a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_bytes(out)
 r=dict(at_utc=datetime.now(timezone.utc).isoformat(),source_sha256=EXPECTED,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),fragment_sha256=hashlib.sha256(fragment.read_bytes()).hexdigest(),helper_roots=['Submission.R27LazyWordProof.cold_equivalent'],proof='NOT_RUN_RELATIVE_SCALAR_EQUIVALENCE_ONLY',full12='UNPROVED_NATIVE_ONLY',local_build=False,formal_submission=False,purpose='Two-block lazy prepare change plus exact same scalar output theorem vs historical eager branch for allrawarrays. Actual producer correctness and fullcachedmodel obligation remain separate.')
 if a.receipt:a.receipt.write_text(json.dumps(r,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
 print(json.dumps(r,ensure_ascii=False,indent=2))
if __name__=='__main__':main()
