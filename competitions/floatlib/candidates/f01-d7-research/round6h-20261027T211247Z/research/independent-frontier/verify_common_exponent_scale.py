from pathlib import Path
import json, hashlib
from datetime import datetime, timezone
D=Path(__file__).resolve().parent
files=[];rows=[]
for run in [40168687803,40169957447,40171180249]:
    p=D/f'common-exponent-scale-{run}.json';b=p.read_bytes();j=json.loads(b)
    script=D/('screen_common_exponent_scale-v2.py' if run==40171180249 else 'screen_common_exponent_scale.py')
    assert hashlib.sha256(script.read_bytes()).hexdigest()==j['script_sha256']
    assert j['state']=='COMPLETE_DOMAIN_SOURCE_SCREEN_PAPER_CERTIFICATE'
    assert sum(x['early_summary_words'] for x in j['cases'])==j['reads']
    full=[x for x in j['cases'] if x['whole_cert'] and x['nonzero_input_summary_hits']]
    assert all(x['kernel']=='bmm' and x['dimensions'][2]==1 for x in full)
    for x in full:
        _,m,n,pdim=x['dimensions']
        rows.append({'run':run,'name':x['name'],'shape':x['dimensions'],
                     'removed_input_scale_mul_at_most_per_batch':n*(m+pdim),
                     'added_output_scale_mul_per_batch':m*pdim})
    files.append({'file':p.name,'sha256':hashlib.sha256(b).hexdigest(),'bytes':len(b)})
assert len(rows)==4
out={'at_utc':datetime.now(timezone.utc).isoformat(),'decision':'PARK_NO_10_PERCENT_COST_PREMISE',
     'files':files,'whole_nonzero_cases':rows,'Lean':'NOT_RUN','runtime':'NONE',
     'actual_available_input_conversion_fraction':'UNKNOWN','no_new_CI':True}
(D/'common-exponent-scale-verification.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({'whole_nonzero_cases':rows,'decision':out['decision']}))
