"""Read A20 completed telemetry, bind PID identity, retain unknowns; never score."""
from pathlib import Path
import argparse
import collections
import hashlib
import json

ROOT=Path(__file__).resolve().parents[1]

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('folder',help='collected diagnostics/r26-a-engine-placement')
    args=ap.parse_args()
    folder=Path(args.folder)
    folder=folder if folder.is_absolute() else ROOT/folder
    receipt=json.loads((folder/'receipt.json').read_bytes())
    telemetry=json.loads((folder/'telemetry.json').read_bytes())
    for f,h in receipt.get('artifacts',{}).items():
        assert sha(folder/f)==h,(f,'artifact hash mismatch')
    assert receipt['status']=='COMPLETE_EXACT_ENGINE_PLACEMENT_OBSERVATION_NOT_A_SCORE'
    assert receipt['pins_before']==receipt['pins_after']
    identity=receipt['engine_identity']
    assert identity['exe_sha256_via_proc']==receipt['engine_sha256']
    pid=identity['process']['pid']
    start=identity['process']['starttime_ticks']
    samples=[]
    for sample in telemetry['samples']:
        for e in sample['engines']:
            assert e['pid']==pid and e['starttime_ticks']==start
            assert e['exe']==identity['process']['exe']
            assert [pid,start] in sample['tree_pid_start_pairs']
            samples.append({'unix_ns':sample['unix_ns'],**e})
    assert len(samples)==receipt['engine_sample_count'] and samples
    unique=lambda values: list({json.dumps(v,sort_keys=True):v for v in values}.values())
    freq={}
    cg={}
    for e in samples:
        for k,v in e['frequency_files'].items():
            freq.setdefault(k,[]).append(v)
        for k,v in e['cgroup_files'].items():
            cg.setdefault(k,[]).append(v)
    historical=ROOT/'evidence/round26/38224543411/screen-a19/gate/round1-public658.jsonl'
    old=[json.loads(s) for s in historical.read_text().splitlines()]
    current=[json.loads(s) for s in (folder/'original-engine.raw.jsonl').read_text().splitlines()]
    oldfiles={r['file']:r for r in old if r['kind']=='file'}
    newfiles={r['file']:r for r in current if r['kind']=='file'}
    assert oldfiles.keys()==newfiles.keys() and len(newfiles)==28
    for f,row in newfiles.items():
        assert row['sha256']==oldfiles[f]['sha256']
        for method in ('incumbent','public658'):
            for k in ('tokens_sha256','output_sha256','output_bytes'):
                assert row['methods'][method][k]==oldfiles[f]['methods'][method][k]
    prior=ROOT/'evidence/round24/affinity-af-analysis.json'
    feedback={
        'status':'VERIFIED_CURRENT_EXACT_ENGINE_PLACEMENT_NOT_HISTORICAL_CAUSE_OR_PERFORMANCE',
        'run_id':receipt['run_id'],'git_sha':receipt['git_sha'],
        'inputs':{str(p.relative_to(ROOT)).replace('\\','/'):sha(p) for p in [folder/'receipt.json',folder/'telemetry.json',folder/'original-engine.raw.jsonl',historical,prior]},
        'engine_sha256':receipt['engine_sha256'],'engine_pid':pid,'engine_starttime_ticks':start,
        'engine_samples':len(samples),'sampled_cpu_set':sorted({e['sampled_cpu'] for e in samples}),
        'sampled_cpu_counts':dict(collections.Counter(e['sampled_cpu'] for e in samples)),
        'sampled_cpu_transitions':[{'seconds_since_first_sample':(b['unix_ns']-samples[0]['unix_ns'])/1e9,
                                   'from_cpu':a['sampled_cpu'],'to_cpu':b['sampled_cpu']}
                                  for a,b in zip(samples,samples[1:]) if a['sampled_cpu']!=b['sampled_cpu']],
        'engine_metadata':{k:receipt['metadata'][k] for k in ('cpu_model','cpu_governor','rustc_version')},
        'sampled_cpu_semantics':'/proc/PID/stat field39: processor on which this task last executed at the read; not a per-call CPU trace.',
        'effective_affinity_observations':unique(e['effective_affinity'] for e in samples),
        'engine_status_observations':unique(e['status'] for e in samples),
        'requested_cpus':receipt['driver_provenance']['cpus'],
        'driver_process_affinity':receipt['driver_provenance']['process_affinity'],
        'monitor':{k:v for k,v in telemetry.items() if k.startswith('monitor_')},
        'cgroup_memberships':unique(e['cgroup'] for e in samples),
        'cgroup_files':{k:unique(v) for k,v in cg.items()},
        'frequency_files':{k:unique(v) for k,v in freq.items()},
        'original_protocol':{'files':28,'warmup':current[0]['warmup_rounds'],'measured':current[0]['measured_rounds'],
                             'public658_and_incumbent_tokens_output_match_prior_files':28,
                             'same_engine_sha256_as_A19':current[0].get('benchmark_provenance',{}).get('engine_sha256','NOT_IN_RAW_META'),
                             'library_identity_equal_to_prior':{n:current[0]['methods'][n]['lib_sha256']==old[0]['methods'][n]['lib_sha256'] for n in ('incumbent','public658')}},
        'prior_R24_boundary':'R24 already observed a pre-exec wrapper mask 0-3 under CPU0 request. Its explicit binding reduced parent alias difference but increased candidate alias difference; no universal fix. A20 adds current actual-exec identity and runtime samples, not a first global discovery.',
        'placement_conclusion':'Original requested CPU0 did not restrict this measured engine to CPU0: effective affinity was observed directly, and its last-executed CPU samples cover both0and2. The reason for missing per-scope cpuset/cpu.max files is not established.',
        'limits':['All timings are diagnostic and excluded from candidate scores and confirmation.',
                  'No historical A19 placement, CPU frequency or root cause is reconstructed.',
                  '4Hz last-executed CPU samples cannot exclude between-sample migrations; distinct values establish execution on multiple CPUs for this PID only.',
                  'Visible frequency values are sysfs observations, not per-call measured CPU cycles or instantaneous frequency.',
                  'Unavailable fields remain UNKNOWN; a request is not evidence of enforcement.']}
    # Bind engine equality to actual saved provenance separately from the diagnostic raw meta.
    feedback['original_protocol']['same_engine_sha256_as_A19']=(receipt['engine_sha256']==old[0]['benchmark_provenance']['engine_sha256'])
    out=ROOT/'evidence/round26/route-a/a20-placement-feedback.json'
    out.write_text(json.dumps(feedback,indent=2)+'\n')
    print(json.dumps({k:feedback[k] for k in ('status','run_id','engine_samples','sampled_cpu_set','effective_affinity_observations','monitor','cgroup_files','frequency_files')},indent=2))

if __name__=='__main__':
    main()
