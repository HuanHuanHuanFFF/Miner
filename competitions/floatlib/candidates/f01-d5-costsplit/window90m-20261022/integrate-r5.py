"""Freeze a complete package from exact, already full-gate accepted components."""
from pathlib import Path
import argparse, datetime, hashlib, json, re

ROOT=Path.cwd(); OWN=Path(__file__).resolve().parent
ap=argparse.ArgumentParser()
ap.add_argument('--base',required=True)
ap.add_argument('--pack')
ap.add_argument('--byte-lane',action='store_true')
ap.add_argument('--lazy-finish',action='store_true')
ap.add_argument('--name',required=True)
a=ap.parse_args()
assert re.fullmatch('f01-d5-[a-z0-9-]+',a.name)
records=json.loads((OWN/'summary.json').read_bytes())['records']
records+=json.loads((ROOT/'competitions/floatlib/candidates/f01-d4-global8/window2h-20261022/summary.json').read_bytes())['records']
parents={}

def load_accepted(name):
    p=ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean'
    raw=p.read_bytes(); digest=hashlib.sha256(raw).hexdigest()
    runs=[r['run'] for r in records if r['candidate']==name and r.get('full_gate') and r.get('passed') and r['kernel_sha256']==digest]
    assert runs,('No exact full-gate acceptance',name,digest)
    parents[name]={'kernel_sha256':digest,'kernel_bytes':len(raw),'full_gate_runs':runs}
    return raw.decode()

s=load_accepted(a.base)
if a.pack:
    assert 'native' in a.pack, 'Keep the measured original bit decoder in final package'
    donor=load_accepted(a.pack)
    i=donor.index('def packB (');j=donor.index('theorem packB_lane',i)
    block=donor[i:j].replace(', decodePacked_eq','')
    assert 'decodePacked' not in block
    i=s.index('def packB (');j=s.index('theorem packB_lane',i)
    s=s[:i]+block+s[j:]
if a.byte_lane:
    donor=load_accepted('f01-d5-byte-lane')
    i=donor.index('@[inline] def lane (v : F10)');j=donor.index('@[inline] def packet',i)
    block=donor[i:j]
    assert 'match l.val.toUInt8 with' in block
    i=s.index('@[inline] def lane (v : F10)');j=s.index('@[inline] def packet',i)
    s=s[:i]+block+s[j:]
if a.lazy_finish:
    donor=load_accepted('f01-d5-lazy-finish-full')
    i=donor.index('namespace Submission.LazyFinish')
    j=donor.index('\ndef output (',i)
    helper=donor[i:j].replace('namespace Submission.LazyFinish','namespace Submission.R5Finish')+'\nend Submission.R5Finish\n\n'
    i=s.index('namespace Submission.RowOutput')
    s=s[:i]+helper+s[i:]
    needle='Packed10.finish n baseA (baseB + j.val) p A.toArray B.toArray'
    assert s.count(needle)==1
    s=s.replace(needle,'R5Finish.finishAt m n p b.val i.val j.val A.toArray B.toArray')
raw=s.encode();assert len(raw)<=256000
dest=ROOT/'competitions/floatlib/candidates'/a.name;dest.mkdir(exist_ok=False)
(dest/'Kernel.lean').write_bytes(raw)
manifest={'candidate':a.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(raw).hexdigest(),'candidate_bytes':len(raw),'validation_mode':'full-gate','proof_status':'NOT_RUN_NEW_COMBINATION_REQUIRES_OWN_GATE','parents':parents,'selected_output_base':a.base,'selected_pack':a.pack,'selected_byte_lane':a.byte_lane,'selected_lazy_finish':a.lazy_finish,'frozen_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'mechanism':'Exact composition of accepted output layout, packing, bounded lane selection and optional delayed raw fallback addresses; scalar add/mul/sum remain R4 robust package. New integrated source still requires full gate and frozen independent confirmation.','formal_submission':'NOT_SUBMITTED'}
(dest/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(manifest,ensure_ascii=False,indent=2))
