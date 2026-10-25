"""Authenticate selected native core C before investing in full-cost timing."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,subprocess
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4]
BASE=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40182114389'
sha=lambda b:hashlib.sha256(b).hexdigest()
idx=json.loads((BASE/'original-artifact-hashes.json').read_bytes());stage=BASE/idx['directory']
for name,info in idx['files'].items():
    data=(stage/name).read_bytes();assert sha(data)==info['sha256'] and len(data)==info['bytes']
candidate='f01-r16-dev-native-repack1';prefix=stage/'diagnostics/f01-d7-public-suite/public-suite'
kernel=(prefix/'inputs'/candidate/'Kernel.lean').read_bytes()
ci=json.loads((BASE/'ci-run.json').read_bytes())
assert kernel==subprocess.check_output(['git','show',ci['headSha']+':competitions/floatlib/candidates/'+candidate+'/Kernel.lean'],cwd=ROOT)
folder=prefix/'diagnostics'/candidate;cidx=json.loads((folder/'candidate-c-index.json').read_bytes())
entry=next(x for x in cidx if x['module']=='Submission');raw=(folder/entry['file']).read_bytes()
assert sha(raw)==entry['sha256'] and entry['kernel_sha256']==sha(kernel)
text=raw.decode();symbol='lp_competition_Submission_R14ExponentShift_core'
m=re.search(r'^LEAN_EXPORT [^\n]*\b'+symbol+r'\([^;\n]*\)\s*\{',text,re.M);assert m
depth=0
lex=re.compile(r'"(?:\\.|[^"\\])*"|//[^\n]*|/\*[\s\S]*?\*/|[{}]')
for t in lex.finditer(text,m.end()-1):
    if t[0]=='{':depth+=1
    elif t[0]=='}':
        depth-=1
        if depth==0:body=text[m.start():t.end()];break
names=['lean_uint32_to_float32','lean_float32_mul','lean_float32_to_bits','lean_float32_of_bits',
       'lean_float32_beq','lean_array_fget_borrowed','lean_alloc_ctor','lean_box_float32','lean_apply_2']
counts={n:len(re.findall(r'\b'+n+r'\s*\(',body)) for n in names}
assert counts['lean_uint32_to_float32']==2 and counts['lean_float32_mul']==1 and counts['lean_float32_to_bits']==1
assert counts['lean_array_fget_borrowed']==counts['lean_float32_beq']==counts['lean_alloc_ctor']==counts['lean_box_float32']==0
piece=HERE/'development-native-core-statement.c';assert not piece.exists();piece.write_bytes(body.encode())
report=dict(checked_utc=datetime.now(timezone.utc).isoformat(),run=40182114389,source_commit=ci['headSha'],
    kernel_sha256=sha(kernel),source_file=(folder/entry['file']).relative_to(ROOT).as_posix(),source_sha256=sha(raw),
    symbol=symbol,body_sha256=sha(body.encode()),body=piece.relative_to(ROOT).as_posix(),static_sites=counts,
    scope='Actual statement-layer exported normal core, not a timed-object or dynamic count. Entry guard/fallback and whole MainFull caller costs still require full original gates and timing.')
(HERE/'development-native-core-C-evidence.json').write_bytes((json.dumps(report,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(report))
