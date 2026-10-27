"""Parent critical check of archived selected-C closure claim and ASM coverage."""
from pathlib import Path
from hashlib import sha256
import json,re

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
report=json.loads((HERE/'astra-workers/matrix-structure/closure-evidence.json').read_bytes())
raw=(ROOT/report['C_source']).read_bytes()
assert sha256(raw).hexdigest()==report['C_sha256']
c=raw.decode()
checked=[]
for item in report['entries']:
    match=re.search(r'^LEAN_EXPORT [^\n]+?\b'+re.escape(item['symbol'])+r'\([^\n]*\)\{',c,re.M)
    assert match
    brace=c.index('{',match.start());end=brace+1;depth=1
    while depth:
        if c[end]=='{':depth+=1
        elif c[end]=='}':depth-=1
        end+=1
    body=c[match.start():end]
    assert sha256(body.encode()).hexdigest()==item['body_sha256']
    assert c.count('\n',0,match.start())+1==item['line_start']
    assert body.count('lean_alloc_closure(')==item['alloc_closure_sites']
    checked.append(dict(label=item['label'],line=item['line_start'],closures=item['alloc_closure_sites']))
diag=ROOT/'competitions/floatlib/candidates/f01-word-tensors/ci-diagnostics.py'
d=diag.read_bytes().decode()
lines=d.splitlines()
filters=[dict(line=i+1,text=s.strip())for i,s in enumerate(lines)if "'Submission' not in path.name" in s or "'Submission' in path.name" in s or "startswith('lp_competition_Submission_')" in s or 'R2W01b_fastOK' in s]
result=dict(status='VERIFIED_SELECTED_HISTORICAL_C_AND_DIAGNOSTIC_SOURCE_ONLY',
            source_run=report['run'],candidate_sha256=report['candidate_sha256'],C_sha256=sha256(raw).hexdigest(),
            checked_functions=checked,
            diagnostic_source_sha256=sha256(diag.read_bytes()).hexdigest(),diagnostic_filters=filters,
            conclusions=['Selected old B2/DC row/group/emitter bodies have no closure allocator; generic DC wrapper does.',
                         'Current diagnostic symbol/object filter is insufficient evidence for actual selected MainFull scalar ASM; extend only diagnostic collection if needed.',
                         'No claim about new candidate speed, physical allocation total, or current timed gate object.'],
            action='Send file evidence; finish all active CI; do not cancel or prejudge rowLoop timing.')
(HERE/'astra-review-selected-cost.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(result,indent=2))
