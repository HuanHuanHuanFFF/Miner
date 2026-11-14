"""Read-only exact helper/public alignment; writes only this scope's line map."""
from pathlib import Path
import datetime
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
helper=HERE/'MathOutletR23Fix1.lean'
public=ROOT/'competitions/floatlib/candidates/f01-r23-dev-outline-public1/Kernel.lean'
hraw,praw=helper.read_bytes(),public.read_bytes()
assert hashlib.sha256(hraw).hexdigest()=='159e0633eee16fa1b054d2b0adcb0a99b0a5fc7dfe96e776097de6d9f4e467e9'
assert hashlib.sha256(praw).hexdigest()=='f90d42e346a1634ffeb537ea7e9980e0a91baea8499dc6c2235da5ab8fe0e85f'
htext,ptext=hraw.decode(),praw.decode()
start=htext.index('namespace BranchlessRNESeed')
stop=htext.index('#print axioms ')
helper_body=htext[start:stop].rstrip()
mapped_body=helper_body.replace('Submission.','R19BiasBase.')
assert ptext.count(mapped_body)==1
offset=ptext.index(mapped_body)
hstartline=htext[:start].count('\n')+1
pstartline=ptext[:offset].count('\n')+1
rows=[]
for match in re.finditer(r'(?m)^(private )?theorem (\S+)',helper_body):
    local=helper_body[:match.start()].count('\n')
    rows.append({'name':match.group(2),'private':bool(match.group(1)),
        'helper_line':hstartline+local,'public_line':pstartline+local})
assert len(rows)==51
record={'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'helper_sha256':hashlib.sha256(hraw).hexdigest(),'public_sha256':hashlib.sha256(praw).hexdigest(),
    'public_bytes':len(praw),'entire_helper_body_byte_identical_after_only_namespace_substitution':True,
    'helper_start_line':hstartline,'public_start_line':pstartline,'line_delta':pstartline-hstartline,
    'source_only_no_Lean_acceptance':True,'theorems':rows}
(HERE/'public-line-map.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'line_delta':record['line_delta'],'mapped_theorems':len(rows),
    'priority':[r for r in rows if r['name'] in ['roundP_normal','oldMantissa_nat','normalCore_eq_roundP','normalCore_eq_core','guardedMul_spec']]}))
