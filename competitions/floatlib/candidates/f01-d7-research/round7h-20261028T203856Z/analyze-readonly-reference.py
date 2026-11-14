"""Classify original profile receipts without modifying or rerunning inputs."""
from pathlib import Path
import collections, hashlib, json, math, re

HERE = Path(__file__).resolve().parent
RUN = HERE/'ci-runs/40786223288'
manifest = json.loads((RUN/'original-artifact-hashes.json').read_bytes())
root = RUN/manifest['directory']
for name, item in manifest['files'].items():
    raw = (root/name).read_bytes()
    assert len(raw) == item['bytes'] and hashlib.sha256(raw).hexdigest() == item['sha256']
summary_path = root/'summary.json'
data = json.loads(summary_path.read_bytes())
assert data['complete'] and data['protected_upstream_unchanged']
assert data['source_commit'] == 'c839fd40ab06520f1786d00dd3d3e2f5fca26ae9'
cpu = (root/'cpuinfo.raw').read_bytes()
assert hashlib.sha256(cpu).hexdigest() == data['cpuinfo_sha256']
result = {'run':40786223288,'source_commit':data['source_commit'],
    'upstream_commit':data['upstream_commit'],'summary_sha256':hashlib.sha256(summary_path.read_bytes()).hexdigest(),
    'raw_files':len(manifest['files']),'raw_bytes':sum(x['bytes'] for x in manifest['files'].values()),
    'cpu':sorted(set(re.findall(r'model name\s*:\s*(.*)',cpu.decode()))),'profile_cpu':data['profile_cpu'],
    'scope':'One original profile per model, normal/batch1, model42/input7, layer best5 INCLUDING hash/touch/ownership. No printed output checksums, independent audit, current5 source, new candidate or official score.',
    'reference_order':[x['name'] for x in data['references']],'references':[]}
dot_names = {'linear','gemm','conv2d','depthwise'}
for ref in data['references']:
    item = {'name':ref['name'],'source_sha256':ref['receipt']['input_sha256'],
        'original_VerifyExact_build':ref['typecheck'],'models':[]}
    for model in ref['profiles']:
        groups = collections.defaultdict(int)
        for row in model['rows']:
            if row['layer'] != 'total': groups[row['layer'].split()[0]] += row['microseconds_integer_truncated']
        total = model['reported_total_microseconds']
        dot = sum(v for k,v in groups.items() if k in dot_names)
        norm = groups['rmsnorm'] + groups['layernorm']
        item['models'].append({'model':model['model'],'total_us':total,
            'category_us':dict(groups),'dot_layer_us':dot,'norm_layer_us':norm,
            'dot_layer_share':dot/total,'norm_layer_share':norm/total,
            'truncation_gap_us':total-sum(groups.values())})
    if ref['name']=='former2':
        item['hypothetical_equal_family_layer_scenarios'] = {
            'half_dot_affected_layer_cost_ratio':math.prod(1-x['dot_layer_share']/2 for x in item['models'])**.2,
            'half_norm_affected_layer_cost_ratio':math.prod(1-x['norm_layer_share']/2 for x in item['models'])**.2,
            'boundary':'Analytic scenario only: assumes half of FULL affected layer time, includes observers. Not measured primitive speed, actual weighted profiles, current champion comparison, or a score forecast.'}
    result['references'].append(item)
result['decision'] = 'Prioritize fused dot/dense/conv path; norm certificates remain secondary. Former2 nmlp normalization exposure is6.20%, not shipped38.05%. Mixer26.08% norm alone cannot establish a10% overall route.'
(HERE/'development-reference-first-result.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'raw_hashes':'PASS','files':result['raw_files'],'bytes':result['raw_bytes'],
    'former2_scenarios':next(x for x in result['references'] if x['name']=='former2')['hypothetical_equal_family_layer_scenarios']}))
