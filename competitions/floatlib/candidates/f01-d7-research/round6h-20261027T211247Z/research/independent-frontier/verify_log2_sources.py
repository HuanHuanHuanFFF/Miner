from pathlib import Path
from datetime import datetime, timezone
import hashlib, json
H = Path(__file__).resolve().parent
R = next(p for p in H.parents if (p/'AGENTS.md').exists())
idx = json.loads((H/'log2-source-index.json').read_text())
rows = []
for item in idx['files']:
    p = H/item['file']; b = p.read_bytes()
    blob = hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()
    assert blob == item['git_blob'], item['file']
    rows.append({**item, 'bytes': len(b), 'sha256': hashlib.sha256(b).hexdigest(), 'git_blob_verified': True})
header = R/'competitions/floatlib/candidates/f01-d7-research/round45m-20261027T074758Z/research/source-intake/lean-runtime-293d5d0c/lean.h'
hb = header.read_bytes()
assert hashlib.sha256(hb).hexdigest() == '982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
api = (H/'upstream-UInt-Log2.lean').read_text()
assert '@[extern "lean_uint32_log2"]' in api and 'def UInt32.log2' in api
loop = (H/'log2-LLVM-22.1.4-LoopIdiomRecognize.cpp').read_text()
assert 'recognizeShiftUntilLessThan()' in loop and 'if (LoopThreshold != 4)' in loop
assert '// log2(x) = w − 1 − clz(x)' in loop
test = (H/'log2-LLVM-22.1.4-ctlz.ll').read_text()
assert 'define i32 @floor_log2_use_inc' in test and 'call i64 @llvm.ctlz.i64' in test
probe = H/'Probe-log2-public-api.lean.inc'; pb = probe.read_bytes()
assert len(pb) < 1024 and b'@[extern' not in pb and b'unsafe ' not in pb
out = {'verified_utc': datetime.now(timezone.utc).isoformat(), 'files': rows,
       'pinned_header': {'path': str(header.relative_to(R)), 'sha256': hashlib.sha256(hb).hexdigest(), 'bytes': len(hb)},
       'probe': {'file': probe.name, 'bytes': len(pb), 'sha256': hashlib.sha256(pb).hexdigest(), 'Lean': 'NOT_RUN', 'machine_code': 'UNKNOWN'},
       'claim': 'PINNED_RELEASE_SOURCE_SUPPORTS_FLOOR_LOG2_LOOP_RECOGNITION; actual compiler binary/codegen UNKNOWN',
       'no_local_compiler_or_CI': True}
(H/'log2-source-verification.json').write_text(json.dumps(out, indent=2)+'\n')
print(json.dumps({'source_files': len(rows), 'source_bytes': sum(x['bytes'] for x in rows), 'probe': out['probe']}))
