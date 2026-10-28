"""Freeze the actual cache-to-four-readers chain as one bounded Lean component."""
from pathlib import Path
import hashlib,json,datetime,subprocess,sys,argparse
ROOT=next(p for p in Path(__file__).resolve().parents if (p/'AGENTS.md').is_file());HERE=Path(__file__).resolve().parent
def sha(b):return hashlib.sha256(b).hexdigest()
ap=argparse.ArgumentParser();ap.add_argument('--producer2',action='store_true');args=ap.parse_args()
suffix='2' if args.producer2 else ''
stem='reader'+suffix
base=ROOT/'competitions/floatlib/candidates/f01-r22-dev-indexed8-cost1/Kernel.lean'
raw=base.read_bytes();assert sha(raw)=='8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
nat=ROOT/'competitions/floatlib/candidates/f01-r22-dev-nat8-projection-probe1/Kernel.lean'
nb=nat.read_bytes();assert nb.startswith(raw);assert sha(nb)=='f7b19b9e9b90125291228351d6cf4ac36fe86ca7760dd4455a08a096083205b9'
pieces=[('original-runtime',base,raw),('accepted-nat-projection',nat,nb[len(raw):])]
producer=ROOT/('competitions/floatlib/candidates/f01-r23-research-indexed-producer'+suffix+'/Producer.lean.inc')
pb=producer.read_bytes()
if args.producer2:
    pm=json.loads((producer.parent/'manifest.json').read_bytes());assert sha(pb)==pm['producer_fragment_sha256']
    assert pm['candidate_sha256']==sha((producer.parent/'Kernel.lean').read_bytes())
else:assert sha(pb)=='6206241bdf0689a2b636c9f83bfbe811efbfb1561c380b040ad9601c02a7b356'
pieces.append(('actual-producer',producer,pb))
read=HERE/'producer/ReaderBinding.lean.inc';rb=read.read_bytes();assert sha(rb)=='74d037ab909a5daaac8c996841e5d8c858dd009155f993398e5a3424133244bc'
pieces.append(('actual-cache-view-zero',read,rb.split(b'theorem within_lane')[0]+b'\nend Submission.R23IndexedProducer\n'))
tile=HERE/'producer/NatTileBinding.lean.inc';tb=tile.read_bytes();assert sha(tb)=='4c26f0f3838f5e68f173de3cb04e0c579d0084a78a39425ebeda613a21e651d5'
pieces.append(('actual-nat-tile',tile,tb))
bridge=HERE/'prefix/NatReaderBridge.lean.inc';bb=bridge.read_bytes()
pieces.append(('four-reader-proposition',bridge,bb.split(b'theorem dot_point')[0]+b'\nend Submission.R23NatReaderBridge\n'))
packed=HERE/'prefix/PackedReaders.lean.inc';kb=packed.read_bytes()
assert sha(kb)=='42a96d4264a1ff24eecbe85860b85c2c078c2b7c45d528a4df4b7b853f0e091c'
pieces.append(('actual-column-readers',packed,kb.split(b'theorem all_reads')[0]+b'\nend Submission.R23NatReaderBridge\n'))
assembly=b'\n'.join(v for _,_,v in pieces)
src=HERE/(stem+'-assembly.NOT_RUN.lean');src.write_bytes(assembly)
subprocess.run([sys.executable,str(HERE/'proof-space-screen.py'),'--input',str(src),'--stem',stem,'--keep','packed_dot_reads','--keep','packed_getTile_word'],check=True,stdout=subprocess.DEVNULL)
blob=(HERE/(stem+'-base.NOT_RUN.lean')).read_bytes();assert len(blob)<=256000,len(blob)
out=ROOT/('competitions/floatlib/candidates/f01-r23-research-unconditional-reader'+suffix);out.mkdir(exist_ok=True)
(out/'Kernel.lean').write_bytes(blob)
helper='f01-d7-research/round9h-20261026T194639Z/development-helper-audit-v8.py'
roots=['Submission.R23NatReaderBridge.packed_dot_reads','Submission.R23NatReaderBridge.packed_getTile_word']
components=[dict(role=name,path=p.relative_to(ROOT).as_posix(),sha256=sha(p.read_bytes()),selected_bytes=len(value),selected_sha256=sha(value)) for name,p,value in pieces]
m=dict(candidate=out.name,candidate_file='Kernel.lean',candidate_sha256=sha(blob),candidate_bytes=len(blob),
 created_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),validation_mode='statement-only',diagnostic_only=True,diagnostic_timeout_seconds=180,
 proof_status='NOT_RUN_ACTUAL_UNCONDITIONAL_FOUR_READERS',performance='NO_NEW_PERFORMANCE_CLAIM',formal_submission='NOT_SUBMITTED',official_submission_inherited=False,
 helper_audit_module='development-helper-audit-v8.py',helper_audit_module_path=helper,
 helper_audit_module_sha256=sha((ROOT/'competitions/floatlib/candidates'/helper).read_bytes()),
 explicit_helper_audit=roots,helper_audit_required_endpoints=roots,helper_audit_expected_count=len(roots),helper_audit_source_sha256=sha(blob),diagnostic_evaluations=[],
 components=[dict(path=d['path'],sha256=d['sha256']) for d in components],
 scope='Actual R22 packB producer, Nat8 scalar projection, finish replay and actual four column readers. No hread/DotReads assumption. Exact old public B2 endpoints remain; full new output/public port not included.',
 source_space_screen=(HERE/(stem+'-screen.json')).relative_to(ROOT).as_posix(),source_pruning_status='NOT_RUN_ORIGINAL_GATE_MUST_RECHECK_ALL_PUBLIC_PROOFS')
(out/'manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf-8')
receipt=dict(**m,assembly_bytes=len(assembly),assembly_sha256=sha(assembly),assembly_components=components)
(HERE/('unconditional-reader'+suffix+'-source-receipt.json')).write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidate':out.name,'bytes':len(blob),'sha256':sha(blob),'roots':roots}))
