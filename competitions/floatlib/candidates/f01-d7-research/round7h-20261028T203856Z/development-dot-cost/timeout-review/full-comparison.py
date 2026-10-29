from __future__ import annotations
import argparse
import hashlib
import json
import re
import statistics
from pathlib import Path

OWNER = Path(__file__).resolve().parent
FIXTURE_PATH = OWNER.parent / 'fixtures.json'
EXPECTED_PREFIXES = {'original': '5bf2a8893b01a5ed44393e80065fbd91e9b3686133e9ddd5d4dfb633379d4d2a', 'tail': 'e50'}
NORMAL_KINDS = {'narrow', 'moderate', 'wide'}
EXPECTED_AXIOMS = {'Classical.choice', 'Quot.sound', 'propext'}
EXPECTED_VARIANTS = ['exact', 'eager', 'eager', 'exact', 'exact', 'lazy', 'lazy', 'exact']
EXPECTED_ROWS = 49
EXPECTED_RUNS = 32
EXPECTED_PAIRS = 16
EXPECTED_RAW_SAMPLES = 4704


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()

def load_json(path: Path):
    return json.loads(path.read_bytes())

def norm_key(value: str) -> str:
    return re.sub(r'[^a-z0-9]', '', value.lower())

def recursively_find(obj, wanted: set[str], path='$'):
    found = []
    if isinstance(obj, dict):
        for key, value in obj.items():
            if norm_key(str(key)) in wanted:
                found.append((f'{path}.{key}', value))
            found.extend(recursively_find(value, wanted, f'{path}.{key}'))
    elif isinstance(obj, list):
        for i, value in enumerate(obj):
            found.extend(recursively_find(value, wanted, f'{path}[{i}]'))
    return found

def resolve_run_roots(run_dir: Path):
    run_dir = run_dir.resolve()
    index_path = run_dir / 'original-artifact-hashes.json'
    if index_path.is_file():
        index_base = run_dir
    elif (run_dir.parent / 'original-artifact-hashes.json').is_file():
        index_path = run_dir.parent / 'original-artifact-hashes.json'
        index_base = run_dir.parent
    else:
        raise FileNotFoundError(f'original-artifact-hashes.json not found at {run_dir} or its parent')
    index = load_json(index_path)
    artifact_root = (index_base / index['directory']).resolve()
    if not artifact_root.exists() and run_dir.name == index['directory']:
        artifact_root = run_dir
    if not artifact_root.is_dir():
        raise FileNotFoundError(f'indexed artifact directory is missing: {artifact_root}')
    return run_dir, index_path.resolve(), index, artifact_root.resolve()

def verify_artifact(index_path: Path, index: dict, artifact_root: Path):
    records = index.get('files')
    if not isinstance(records, dict):
        return {'status': 'HASH_MISMATCH', 'reason': 'original artifact index has no files map'}
    expected_paths = set(records)
    actual_paths = {p.relative_to(artifact_root).as_posix() for p in artifact_root.rglob('*') if p.is_file()}
    missing = sorted(expected_paths - actual_paths)
    extra = sorted(actual_paths - expected_paths)
    checked, failures = [], []
    for rel in sorted(expected_paths):
        path = (artifact_root / Path(rel)).resolve()
        if not path.is_relative_to(artifact_root) or not path.is_file():
            failures.append({'path': rel, 'reason': 'missing_or_escaped'})
            continue
        data = path.read_bytes()
        expected = records[rel]
        actual_sha, actual_bytes = sha(data), len(data)
        ok = actual_sha == expected.get('sha256') and actual_bytes == expected.get('bytes')
        item = {'path': rel, 'expected_sha256': expected.get('sha256'), 'actual_sha256': actual_sha,
                'expected_bytes': expected.get('bytes'), 'actual_bytes': actual_bytes, 'pass': ok}
        checked.append(item)
        if not ok:
            failures.append(item)
    ok = not missing and not extra and not failures and len(expected_paths) == len(actual_paths)
    return {
        'status': 'PASS' if ok else 'HASH_MISMATCH',
        'artifact_id': index.get('artifact', {}).get('id'),
        'workflow_run_id': index.get('artifact', {}).get('workflow_run', {}).get('id'),
        'hash_index_sha256': sha(index_path.read_bytes()),
        'artifact_zip_sha256_receipt_only': str(index.get('artifact', {}).get('digest', '')).removeprefix('sha256:'),
        'artifact_zip_digest_recomputed': False,
        'listed_files': len(expected_paths), 'actual_files': len(actual_paths),
        'matched_files': sum(x['pass'] for x in checked),
        'uncompressed_bytes': sum(x['actual_bytes'] for x in checked),
        'missing_paths': missing, 'unexpected_paths': extra, 'failures': failures,
        'per_file': checked,
    }

def find_final_originals_flag(candidate_root: Path, result: dict):
    locations = []
    for key_path, value in recursively_find(result, {'finaloriginalsunchanged','originalsunchanged'}):
        locations.append({'source': 'result.json', 'path': key_path, 'value': value})
    for path in sorted(candidate_root.rglob('*.json')):
        if path.name == 'result.json':
            continue
        try:
            data = load_json(path)
        except (ValueError, OSError):
            continue
        for key_path, value in recursively_find(data, {'finaloriginalsunchanged','originalsunchanged'}):
            locations.append({'source': str(path.relative_to(candidate_root)), 'path': key_path, 'value': value})
    bools = [x['value'] for x in locations if isinstance(x['value'], bool)]
    return {'present': bool(locations), 'all_true': bool(bools) and all(bools) and len(bools) == len(locations),
            'evidence': locations}

def get_fixture_sha(prepare: dict):
    owned = prepare.get('owned_files', {})
    matches = [v for path, v in owned.items() if str(path).replace('\\','/').endswith('/R24DotFixtures.json')]
    return matches[0] if len(matches) == 1 else None

def parse_cpuinfo(path: Path):
    if not path.is_file():
        return []
    blocks=[]
    current={}
    for line in path.read_text(encoding='utf-8',errors='replace').splitlines():
        if not line.strip():
            if current:
                blocks.append(current);current={}
            continue
        if ':' in line:
            key,value=line.split(':',1)
            current[key.strip()]=value.strip()
    if current:
        blocks.append(current)
    return blocks

def cpuinfo_raw_differences(left: Path, right: Path):
    a,b=parse_cpuinfo(left),parse_cpuinfo(right)
    if len(a)!=len(b):
        return {'same_block_count':False,'block_count_left':len(a),'block_count_right':len(b),
                'differing_fields':['<processor-block-count>'],'only_cpu_mhz_differs':False}
    fields=set()
    for x,y in zip(a,b):
        fields.update(k for k in set(x)|set(y) if x.get(k)!=y.get(k))
    return {'same_block_count':True,'block_count_left':len(a),'block_count_right':len(b),
            'differing_fields':sorted(fields),'only_cpu_mhz_differs':bool(fields) and fields=={'cpu MHz'}}

def stable_cpu_identity(path: Path):
    if not path.is_file():
        return None
    blocks=[]
    current={}
    for line in path.read_text(encoding='utf-8',errors='replace').splitlines():
        if not line.strip():
            if current:
                blocks.append(current);current={}
            continue
        if ':' not in line:
            continue
        key,value=line.split(':',1)
        current[key.strip().lower()]=value.strip()
    if current:
        blocks.append(current)
    stable_keys=('processor','vendor_id','cpu family','model','model name','stepping','physical id','core id','siblings','cpu cores','flags')
    normalized=[]
    for block in blocks:
        if block.get('model name'):
            normalized.append({k:block.get(k) for k in stable_keys if k in block})
    if not normalized:
        return None
    unique={json.dumps(x,sort_keys=True,separators=(',',':')) for x in normalized}
    return {'cpu_blocks':len(normalized),'stable_block_sha256':sha('\n'.join(sorted(unique)).encode()),
            'vendor_ids':sorted({x.get('vendor_id') for x in normalized if x.get('vendor_id')}),
            'families':sorted({x.get('cpu family') for x in normalized if x.get('cpu family')}),
            'models':sorted({x.get('model') for x in normalized if x.get('model')}),
            'model_names':sorted({x.get('model name') for x in normalized if x.get('model name')}),
            'steppings':sorted({x.get('stepping') for x in normalized if x.get('stepping')}),
            'flags_sha256':sha('\n'.join(sorted({x.get('flags','') for x in normalized})).encode())}

def within_body_premeasurement(result: dict):
    flags=result.get('flags',{})
    if not all(flags.get(stage,{}).get('equal_after_only_root_mapping') is True for stage in ('compile','link','response')):
        return {'pass':False,'reason':'compile/link/response arguments differ after root mapping'}
    compile_removed=flags.get('compile',{}).get('only_owned_barrier_removed')
    link_removed=flags.get('link',{}).get('only_owned_barrier_removed')
    response_removed=flags.get('response',{}).get('only_owned_barrier_removed')
    if compile_removed != [] or link_removed != [] or not isinstance(response_removed,list) or len(response_removed)!=1:
        return {'pass':False,'reason':'unexpected premeasurement change set'}
    if not str(response_removed[0].get('path','')).replace('\\','/').endswith('/R24DotBarrier.c.o.export'):
        return {'pass':False,'reason':'response change is not the owned barrier object'}
    audit=result.get('actual_caller_audit',{})
    records=audit.get('records',[])
    if audit.get('pass') is not True or len(records)!=6 or not all(x.get('pass') is True for x in records):
        return {'pass':False,'reason':'actual typed-call/barrier caller audit is incomplete'}
    for record in records:
        adapters=record.get('typed_adapter',[])
        witnesses=record.get('native_loop_witnesses',[])
        if not adapters or not all(x.get('uint32_return_two_args') is True and x.get('header','').count('lean_object*')>=2 for x in adapters):
            return {'pass':False,'reason':f"typed two-argument UInt32 adapter missing for {record.get('pass_suffix')}"}
        if not witnesses:
            return {'pass':False,'reason':f"native loop witness missing for {record.get('pass_suffix')}"}
        for witness in witnesses:
            backedge=witness.get('backedge',[])
            if len(backedge)!=2 or any(not isinstance(x,int) for x in backedge):
                return {'pass':False,'reason':f"invalid native loop backedge for {record.get('pass_suffix')}"}
            for call in witness.get('barrier_call_offsets',[])+witness.get('adapter_call_offsets',[]):
                if not isinstance(call,int) or not (backedge[0] <= call <= backedge[1]):
                    return {'pass':False,'reason':f"barrier/adapter call escaped backedge for {record.get('pass_suffix')}"}
    return {'pass':True,'compile_removed':compile_removed,'link_removed':link_removed,
            'response_removed':response_removed,'call_audit_records':len(records),
            'typed_two_arg_adapter_records':sum(bool(x.get('typed_adapter')) for x in records),
            'barrier_and_adapter_within_backedge_records':sum(bool(x.get('native_loop_witnesses')) for x in records),
            'pass_suffixes':[x.get('pass_suffix') for x in records]}

def case_rollup(names, control_rows, variant_rows):
    if not names:
        return {'case_count': 0, 'ratio_of_summed_medians': None, 'sum_of_per_case_ratios': None,
                'best_case': None, 'worst_case': None, 'regressions': []}
    control_sum = sum(control_rows[n]['median_ns'] for n in names)
    variant_sum = sum(variant_rows[n]['median_ns'] for n in names)
    ratios = {n: variant_rows[n]['median_ns'] / control_rows[n]['median_ns'] for n in names}
    best, worst = min(ratios, key=ratios.get), max(ratios, key=ratios.get)
    def detail(name):
        return {'name': name, 'ratio': ratios[name], 'kind': control_rows[name]['kind'], 'n': control_rows[name]['n']}
    regressions = [detail(n) for n in sorted(ratios, key=ratios.get, reverse=True) if ratios[n] > 1]
    return {'case_count': len(names), 'control_median_ns_sum': control_sum, 'variant_median_ns_sum': variant_sum,
            'ratio_of_summed_medians': variant_sum / control_sum, 'sum_of_per_case_ratios': sum(ratios.values()),
            'best_case': detail(best), 'worst_case': detail(worst), 'regressions': regressions}

def make_pairs(body, fixture_cases):
    result = body['result']
    runs = result['runs']
    groups = sorted({str(r['group']) for r in runs})
    if len(groups) != 2:
        raise ValueError(f"expected exactly two fixed groups, got {groups}")
    run_map = {(str(r['group']), r['boundary'], int(r['order'])):r for r in runs}
    expected_keys = {(g,b,o) for g in groups for b in ('full','prepared') for o in range(8)}
    if set(run_map) != expected_keys:
        raise ValueError('run set is not two groups x two boundaries x eight orders')
    for group in groups:
        for boundary in ('full','prepared'):
            block = [run_map[(group,boundary,o)] for o in range(8)]
            if [r['variant'] for r in block] != EXPECTED_VARIANTS:
                raise ValueError(f'ABBA variant order differs for {group}/{boundary}')
    case_defs_by_group = {g:{c['name']:c for c in fixture_cases if c.get('timed') and c.get('group') in (g,'directed')} for g in groups}
    if any(len(v) != EXPECTED_ROWS for v in case_defs_by_group.values()):
        raise ValueError('frozen fixture does not yield 49 timed cases per group')
    affinities=set()
    for run in runs:
        group, boundary, order = str(run['group']), run['boundary'], int(run['order'])
        rows = run.get('rows')
        if not isinstance(rows, dict) or set(rows) != set(case_defs_by_group[group]):
            raise ValueError(f'case rows are incomplete or differ from fixture at {group}/{boundary}/{order}')
        if run.get('exit_code') != 0:
            raise ValueError(f'measurement subprocess failed at {group}/{boundary}/{order}')
        env = run.get('env', {})
        if str(env.get('BENCH_DOT_MACS')) != '131072':
            raise ValueError(f'fixed work count mismatch at {group}/{boundary}/{order}')
        if str(env.get('BENCH_DOT_GROUP')) != group or env.get('BENCH_DOT_BOUNDARY') != boundary or env.get('BENCH_DOT_VARIANT') != run.get('variant'):
            raise ValueError(f'run environment does not match recorded group/boundary/variant at {group}/{boundary}/{order}')
        argv=run.get('argv',[])
        if len(argv)<4 or argv[0]!='taskset' or argv[1]!='-c':
            raise ValueError(f'CPU affinity is not explicitly pinned at {group}/{boundary}/{order}')
        affinities.add(str(argv[2]))
        for name,row in rows.items():
            definition = case_defs_by_group[group][name]
            samples = row.get('samples', [])
            raw_ns = [sample.get('ns') for sample in samples]
            if len(raw_ns) != 3 or any(not isinstance(x,int) or x <= 0 for x in raw_ns):
                raise ValueError(f'expected three positive raw ns samples: {name}')
            if row.get('median_ns') != statistics.median(raw_ns):
                raise ValueError(f'median does not equal median of all three raw ns: {name}')
            if row.get('kind') != definition.get('kind') or row.get('n') != len(definition.get('x',[])):
                raise ValueError(f'case kind/length differs from frozen fixture: {name}')
    pair_specs = [('eager',1,0,1),('eager',2,3,2),('lazy',1,4,5),('lazy',2,7,6)]
    pairs = []
    for group in groups:
        for boundary in ('full','prepared'):
            for variant,replicate,control_order,variant_order in pair_specs:
                control = run_map[(group,boundary,control_order)]
                treatment = run_map[(group,boundary,variant_order)]
                crows, vrows = control['rows'], treatment['rows']
                names = sorted(crows)
                all49 = case_rollup(names,crows,vrows)
                per_case = {n:vrows[n]['median_ns']/crows[n]['median_ns'] for n in names}
                by_kind = {}
                kinds = sorted({case_defs_by_group[group][n]['kind'] for n in names})
                for kind in kinds:
                    by_kind[kind] = case_rollup([n for n in names if case_defs_by_group[group][n]['kind']==kind],crows,vrows)
                n_lt32 = [n for n in names if len(case_defs_by_group[group][n]['x']) < 32]
                n_ge32 = [n for n in names if len(case_defs_by_group[group][n]['x']) >= 32]
                normal_long = [n for n in n_ge32 if case_defs_by_group[group][n]['kind'] in NORMAL_KINDS]
                normal_short = [n for n in n_lt32 if case_defs_by_group[group][n]['kind'] in NORMAL_KINDS]
                long_by_kind = {kind:case_rollup([n for n in normal_long if case_defs_by_group[group][n]['kind']==kind],crows,vrows)
                                for kind in ('narrow','moderate','wide')}
                pairs.append({
                    'group':group,'boundary':boundary,'variant':variant,'replicate':replicate,
                    'control_order':control_order,'variant_order':variant_order,
                    'process_wall_ratio':(treatment['wall_seconds']/control['wall_seconds'])
                        if isinstance(treatment.get('wall_seconds'),(int,float)) and treatment['wall_seconds']>0
                        and isinstance(control.get('wall_seconds'),(int,float)) and control['wall_seconds']>0 else None,
                    'all_49':all49,'per_case_ratios':per_case,'per_case_regressions':all49['regressions'],
                    'by_kind':by_kind,
                    'by_length':{'n_lt32':case_rollup(n_lt32,crows,vrows),'n_ge32':case_rollup(n_ge32,crows,vrows),
                                 'normal_n_lt32':case_rollup(normal_short,crows,vrows),'long_normal_n_ge32':case_rollup(normal_long,crows,vrows),
                                 'long_normal_by_kind_n_ge32':long_by_kind},
                })
    if len(pairs) != EXPECTED_PAIRS:
        raise ValueError(f'expected 16 paired records per body, got {len(pairs)}')
    return groups, run_map, pairs, case_defs_by_group, sorted(affinities)

def validate_body(role: str, path: Path, result: dict, artifact_root: Path, expected_fixture_sha: str):
    reasons = []
    candidate_root = path.parent.parent
    prep_path = path.parent / 'prepare.json'
    prepare = load_json(prep_path) if prep_path.is_file() else {}
    final_flag = find_final_originals_flag(candidate_root, result)
    premeasurement = within_body_premeasurement(result)
    cpu_identity = stable_cpu_identity(path.parent/'cpuinfo.raw')
    native = result.get('native_oracle', {})
    runs = result.get('runs', [])
    checks = {
        'result_complete_true': result.get('complete') is True,
        'exactly_32_process_records': len(runs) == EXPECTED_RUNS,
        'native_exit_zero': result.get('native_oracle_exit_code') == 0,
        'native_148_dots': native.get('dots') == 148,
        'native_1049_word_rounds': native.get('word_rounds') == 1049,
        'native_86_known_fast_cases': native.get('known_fast_cases') == 86,
        'native_51_known_accepts': native.get('known_actual_accept') == 51,
        'native_word_and_accept_miss_checks': native.get('all_complete_words_match') is True and native.get('all_expected_accept_miss_match') is True,
        'final_originals_unchanged_true': final_flag['all_true'],
        'within_body_flags_and_call_audit_valid': premeasurement.get('pass') is True,
        'stable_cpu_identity_available': cpu_identity is not None,
    }
    if not prepare:
        checks['prepare_receipt_present'] = False
    else:
        checks['prepare_receipt_present'] = True
    fixture_sha = get_fixture_sha(prepare) if prepare else None
    checks['fixture_sha_matches_frozen_source'] = fixture_sha == expected_fixture_sha
    checks['cpu_fingerprint_present'] = isinstance(result.get('cpuinfo_sha256'),str) and bool(result.get('cpuinfo_sha256'))
    if result.get('source_sha256') != EXPECTED_PREFIXES[role] and not result.get('source_sha256','').startswith(EXPECTED_PREFIXES[role]):
        checks['expected_source_sha'] = False
    else:
        checks['expected_source_sha'] = True
    pair_count = None
    groups = []
    pair_results = None
    run_map = None
    case_defs = None
    affinity_sets = None
    try:
        groups, run_map, pair_results, case_defs, affinity_sets = make_pairs({'result':result}, json.loads(FIXTURE_PATH.read_bytes())['cases'])
        checks['exactly_16_pair_records'] = len(pair_results) == EXPECTED_PAIRS
        pair_count = len(pair_results)
    except (KeyError, ValueError, TypeError, ZeroDivisionError) as error:
        checks['exactly_16_pair_records'] = False
        reasons.append(f'pairing/data validation: {type(error).__name__}: {error}')
    for key,passed in checks.items():
        if not passed:
            reasons.append(key)
    return {
        'role':role,'result_path':str(path.relative_to(artifact_root)),'source_sha256':result.get('source_sha256'),
        'candidate_name':candidate_root.name,'result_complete':result.get('complete'),
        'process_records':len(runs),'paired_records':pair_count,'raw_sample_values_expected':len(runs)*EXPECTED_ROWS*3,
        'raw_sample_values_complete':len(runs)==EXPECTED_RUNS and checks.get('exactly_16_pair_records') is True,
        'fixture_sha256':fixture_sha,'cpuinfo_sha256':result.get('cpuinfo_sha256'),
        'stable_cpu_identity':cpu_identity,'affinity_cpu_sets':affinity_sets,'within_body_premeasurement':premeasurement,
        'final_originals_unchanged_evidence':final_flag,'native_evidence':{k:v for k,v in checks.items() if k.startswith('native_')},
        'checks':checks,'blocking_reasons':reasons,
        'prepare':prepare,'result':result,'groups':groups,'run_map':run_map,'pairs':pair_results,'case_defs':case_defs,
        'complete_for_comparison':not reasons,
    }

def inspect_math35_audit(artifact_root: Path):
    audits=[]
    for path in sorted(artifact_root.rglob('*.json')):
        relative=path.relative_to(artifact_root).as_posix().lower()
        if 'math35' not in relative or not ('helper' in relative or 'audit' in relative):
            continue
        try:
            data=load_json(path)
        except (OSError,ValueError) as error:
            audits.append({'path':path.relative_to(artifact_root).as_posix(),'status':'UNVERIFIED','error':type(error).__name__})
            continue
        accepted=recursively_find(data,{'accepted'})
        replay=recursively_find(data,{'replay','kernelreplay'})
        reports=recursively_find(data,{'reports'})
        allowed=recursively_find(data,{'allowedaxioms'})
        report_obj=reports[0][1] if len(reports)==1 else None
        report_count=len(report_obj) if isinstance(report_obj,(dict,list)) else None
        report_axioms=[]
        if isinstance(report_obj,dict):
            report_axioms=[a for v in report_obj.values() if isinstance(v,list) for a in v]
        elif isinstance(report_obj,list):
            report_axioms=[a for v in report_obj if isinstance(v,dict) for a in v.get('axioms',[]) if isinstance(a,str)]
        allowed_list=allowed[0][1] if len(allowed)==1 and isinstance(allowed[0][1],list) else []
        accepted_ok=bool(accepted) and all(v is True for _,v in accepted)
        replay_ok=bool(replay) and all(v is True or (isinstance(v,str) and v.lower() in ('pass','passed','true')) for _,v in replay)
        axioms_ok=set(allowed_list)==EXPECTED_AXIOMS and set(report_axioms)<=EXPECTED_AXIOMS
        helpers=next((v for _,v in recursively_find(data,{'helpercount','helpers'}) if isinstance(v,int)),None)
        old_roots=next((v for _,v in recursively_find(data,{'oldrootcount','oldroots','originalrootcount'}) if isinstance(v,int)),None)
        reports_ok=report_count==35
        audits.append({'path':path.relative_to(artifact_root).as_posix(),'status':'PASS' if accepted_ok and replay_ok and reports_ok and axioms_ok else 'UNVERIFIED',
                       'accepted_true':accepted_ok,'Replay_true':replay_ok,'report_count':report_count,
                       'allowed_axioms':sorted(set(allowed_list)),'report_axioms_only_allowed':axioms_ok,
                       'helper_count':helpers,'old_root_count':old_roots,
                       'scope_note':'Expected scope is 31 helpers plus 4 old roots; this audit remains separate from the cost body.'})
    if not audits:
        return {'status':'ABSENT','audit_files':[],
                'expected_scope_counts':{'helpers':31,'old_roots':4,'verified_from_this_artifact':False},
                'scope_note':'No math35 helper audit found. The expected mathematical source scope is 31 helpers plus 4 old roots, but these counts are not verified from this artifact; cost-body correctness remains UNPROVED.'}
    return {'status':'PASS' if all(x['status']=='PASS' for x in audits) else 'UNVERIFIED','audit_files':audits,
            'scope_note':'Mathematical proof source is separate from the cost body, whose correctness remains UNPROVED.'}

def main():
    parser=argparse.ArgumentParser(description='Fail-closed full comparison for the R24 original and tail cost bodies.')
    parser.add_argument('--run-dir',required=True,type=Path)
    parser.add_argument('--output',default='full-comparison-results.json')
    args=parser.parse_args()
    output_path=(OWNER/args.output).resolve()
    if output_path.parent != OWNER.resolve() or not output_path.name.startswith('full-'):
        raise SystemExit('--output must be a full-* filename inside timeout-review')
    report={'status':'INCOMPLETE_NUMERIC_ONLY','numeric_only':True,'run_dir':str(args.run_dir.resolve()),
            'comparison':None,'official_score':None,'success_probability':None,'formal_adoption':None,
            'cost_body_correctness':'UNPROVED','proof_source_audit':{'status':'NOT_CHECKED'},'blocking_reasons':[]}
    try:
        run_dir,index_path,index,artifact_root=resolve_run_roots(args.run_dir)
        audit=verify_artifact(index_path,index,artifact_root)
    except (OSError,ValueError,KeyError) as error:
        report.update(status='HASH_MISMATCH',blocking_reasons=[f'{type(error).__name__}: {error}'])
        output_path.write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
        print(json.dumps({k:v for k,v in report.items() if k!='comparison'},indent=2))
        raise SystemExit(2)
    report['artifact_integrity']=audit
    if audit['status']!='PASS':
        report.update(status='HASH_MISMATCH',blocking_reasons=['original artifact hash or size mismatch'])
        output_path.write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
        print(json.dumps({'status':report['status'],'matched_files':audit['matched_files'],'listed_files':audit['listed_files']},indent=2))
        raise SystemExit(2)
    receipt_candidates=[run_dir/'ci-run.json',index_path.parent/'ci-run.json']
    receipt_path=next((p for p in receipt_candidates if p.is_file()),None)
    if receipt_path:
        try:
            receipt=load_json(receipt_path)
            report['workflow_receipt']={'path':str(receipt_path),'sha256':sha(receipt_path.read_bytes()),
                                        'status':receipt.get('status'),'conclusion':receipt.get('conclusion'),
                                        'head_sha':receipt.get('headSha'),'head_branch':receipt.get('headBranch'),
                                        'jobs':[{'name':j.get('name'),'status':j.get('status'),'conclusion':j.get('conclusion')}
                                                for j in receipt.get('jobs',[])]}
        except (OSError,ValueError):
            report['workflow_receipt']={'path':str(receipt_path),'status':'UNREADABLE'}
    else:
        report['workflow_receipt']={'status':'NOT_FOUND'}
    result_paths=sorted(artifact_root.rglob('runtime-cost/result.json'))
    found={role:[] for role in EXPECTED_PREFIXES}
    observed=[]
    for path in result_paths:
        try:
            data=load_json(path)
        except (OSError,ValueError):
            continue
        source=data.get('source_sha256','')
        role=next((r for r,prefix in EXPECTED_PREFIXES.items() if source.startswith(prefix)),None)
        if role:
            found[role].append((path,data))
        observed.append({'path':path.relative_to(artifact_root).as_posix(),'source_sha256':source,
                         'complete':data.get('complete'),'processes':len(data.get('runs',[]))})
    report['observed_runtime_results']=observed
    reasons=[]
    bodies={}
    if not FIXTURE_PATH.is_file():
        reasons.append('frozen fixture source unavailable')
        fixture_sha=None
    else:
        fixture_sha=sha(FIXTURE_PATH.read_bytes())
    report['frozen_fixture_sha256']=fixture_sha
    for role in EXPECTED_PREFIXES:
        matches=found[role]
        if len(matches)!=1:
            reasons.append(f'{role}: expected one runtime-cost/result.json, found {len(matches)}')
            continue
        path,data=matches[0]
        body=validate_body(role,path,data,artifact_root,fixture_sha)
        bodies[role]=body
        reasons.extend(f"{role}: {r}" for r in body['blocking_reasons'])
    report['body_validation']={role:{k:v for k,v in body.items() if k not in ('prepare','result','groups','run_map','pairs','case_defs')}
                               for role,body in bodies.items()}
    report['proof_source_audit']=inspect_math35_audit(artifact_root)
    report['body_roles_found']=sorted(bodies)
    report['source_hashes']={role:body['source_sha256'] for role,body in bodies.items()}
    if set(bodies)!=set(EXPECTED_PREFIXES):
        reasons.append('both original 5bf and tail e50 result bodies are required')
    if len(bodies)==2:
        original,tail=bodies['original'],bodies['tail']
        if original.get('fixture_sha256')!=tail.get('fixture_sha256') or original.get('fixture_sha256')!=fixture_sha:
            reasons.append('fixed fixture hashes differ or do not match the frozen fixture')
        if original.get('stable_cpu_identity')!=tail.get('stable_cpu_identity'):
            reasons.append('stable CPU model/family/stepping/flags differ between frontends')
        if original.get('affinity_cpu_sets')!=tail.get('affinity_cpu_sets'):
            reasons.append('pinned CPU affinity differs between frontends')
        if original.get('within_body_premeasurement',{}).get('response_removed') != tail.get('within_body_premeasurement',{}).get('response_removed'):
            reasons.append('owned response-barrier delta differs between frontends')
        op,tp=original.get('prepare',{}),tail.get('prepare',{})
        if op.get('official_before')!=tp.get('official_before'):
            reasons.append('official source baseline differs between frontends')
        ob_a,ob_b=op.get('original_build_before',{}),tp.get('original_build_before',{})
        if set(ob_a)!=set(ob_b):
            reasons.append('original build snapshot file sets differ')
        else:
            derived_suffixes=('/.lake/build/bin/benchfull','/.lake/build/bin/benchfull.trace',
                              '/.lake/build/ir/submission.c','/.lake/build/ir/submission.c.o.export')
            changed_build={p for p in ob_a if ob_a[p]!=ob_b[p]}
            unexpected_build={p for p in changed_build if not p.lower().endswith(derived_suffixes)}
            mainfull=[p for p in ob_a if p.lower().endswith('/.lake/build/ir/mainfull.c')]
            if unexpected_build:
                reasons.append('unexplained prebuild snapshot differences beyond candidate-derived files')
            if len(mainfull)!=1 or ob_a.get(mainfull[0])!=ob_b.get(mainfull[0]):
                reasons.append('shared MainFull source fragment hash differs or is missing')
            original['candidate_derived_prebuild_differences']=[{'path':p,'original_before_sha256':ob_a[p],'tail_before_sha256':ob_b[p]} for p in sorted(changed_build)]
            original['shared_baseline_mainfull_sha256']=ob_a.get(mainfull[0]) if len(mainfull)==1 else None
        oo, to = op.get('owned_files',{}), tp.get('owned_files',{})
        excluded_frontend={p for p in set(oo)|set(to) if p.replace('\\','/').endswith('/R24DotCostMain.lean')}
        common_o=set(oo)-excluded_frontend
        common_t=set(to)-excluded_frontend
        if common_o != common_t:
            reasons.append('shared owned-file set differs beyond the allowed R24DotCostMain frontend')
        shared=common_o & common_t
        if any(oo[p]!=to[p] for p in shared):
            reasons.append('shared harness, barrier, fixture, or control source hashes differ')
        if get_fixture_sha(op)!=get_fixture_sha(tp):
            reasons.append('prepared fixture object differs between frontends')
        if original.get('groups')!=tail.get('groups'):
            reasons.append('fixed seed groups differ between frontends')
        if original.get('run_map') and tail.get('run_map'):
            for key in original['run_map']:
                if set(original['run_map'][key]['rows'])!=set(tail['run_map'][key]['rows']):
                    reasons.append(f'case sets differ at {key}')
                    break
    if reasons:
        report['blocking_reasons']=sorted(set(reasons))
        report['status']='INCOMPLETE_NUMERIC_ONLY'
        report['comparison']=None
        report['cost_body_correctness']='UNPROVED'
        output_path.write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
        print(json.dumps({'status':report['status'],'numeric_only':True,'matched_artifact_files':audit['matched_files'],
                          'bodies_found':report['body_roles_found'],'blocking_reasons':report['blocking_reasons'],
                          'output':str(output_path)},indent=2))
        return

    original,tail=bodies['original'],bodies['tail']
    original_cpuinfo_path=artifact_root/Path(original['result_path']).parent/'cpuinfo.raw'
    tail_cpuinfo_path=artifact_root/Path(tail['result_path']).parent/'cpuinfo.raw'
    cpuinfo_diff=cpuinfo_raw_differences(original_cpuinfo_path,tail_cpuinfo_path)
    def public_body(body):
        return {'source_sha256':body['source_sha256'],'candidate_name':body['candidate_name'],'processes':EXPECTED_RUNS,
                'paired_records':len(body['pairs']),'raw_samples_used':EXPECTED_RAW_SAMPLES,
                'fixture_sha256':body['fixture_sha256'],'cpuinfo_sha256':body['cpuinfo_sha256'],
                'stable_cpu_identity':body['stable_cpu_identity'],'affinity_cpu_sets':body['affinity_cpu_sets'],
                'within_body_premeasurement':body['within_body_premeasurement'],
                'native_evidence':body['native_evidence'],'final_originals_unchanged':body['final_originals_unchanged_evidence'],
                'paired_results':body['pairs']}
    cross=[]
    for key in sorted(original['run_map']):
        orow,trow=original['run_map'][key],tail['run_map'][key]
        if orow['variant']!=trow['variant']:
            raise AssertionError(f'frontends use different variants at {key}')
        o,t=orow['rows'],trow['rows']
        names=sorted(o)
        roll=case_rollup(names,o,t)
        cross.append({'group':key[0],'boundary':key[1],'order':key[2],'variant':orow['variant'],
                      'tail_over_original':roll,'per_case_ratios':{n:t[n]['median_ns']/o[n]['median_ns'] for n in names}})
    four_rep=[]
    for role,body in [('original',original),('tail',tail)]:
        for boundary in ('full','prepared'):
            for variant in ('eager','lazy'):
                selected=[p for p in body['pairs'] if p['boundary']==boundary and p['variant']==variant]
                ratios=[p['all_49']['ratio_of_summed_medians'] for p in selected]
                if len(selected)!=4:
                    raise AssertionError('expected four paired ratios per variant/boundary')
                four_rep.append({'body':role,'boundary':boundary,'variant':variant,'pair_count':4,
                                 'four_ratios':ratios,'minimum_observed':min(ratios),'maximum_observed':max(ratios),
                                 'median_of_four':statistics.median(ratios)})
    op,tp=original['prepare'],tail['prepare']
    shared_paths=set(op.get('owned_files',{})) & set(tp.get('owned_files',{}))
    shared_paths={p for p in shared_paths if not p.replace('\\','/').endswith('/R24DotCostMain.lean')}
    report.update(status='COMPLETE_EXPLORATORY_NUMERIC_ONLY',numeric_only=True,
                  blocking_reasons=[],bodies={'original':public_body(original),'tail':public_body(tail)},
                  comparison={'same_fixed_fixture_and_shared_control_verified':True,
                              'control_identity':{'official_source_baseline_identical':op.get('official_before')==tp.get('official_before'),
                                                  'shared_MainFull_source_fragment_sha256':original.get('shared_baseline_mainfull_sha256'),
                                                  'candidate_derived_prebuild_differences':original.get('candidate_derived_prebuild_differences',[]),
                                                  'shared_owned_file_hashes_identical_except_R24DotCostMain':all(op['owned_files'][p]==tp['owned_files'][p] for p in shared_paths),
                                                  'within_body_flag_and_call_audits_valid':True,
                                                  'stable_cpu_identity_equal':original['stable_cpu_identity']==tail['stable_cpu_identity'],
                                                  'pinned_affinity_equal':original['affinity_cpu_sets']==tail['affinity_cpu_sets'],
                                                  'raw_cpuinfo_sha256_equal':original['cpuinfo_sha256']==tail['cpuinfo_sha256'],
                                                  'raw_cpuinfo_field_differences':cpuinfo_diff},
                              'cross_frontend_matched_runs':cross,
                              'four_replica_summary_per_variant_boundary':four_rep},
                  cost_body_correctness='UNPROVED',official_score=None,success_probability=None,
                  interpretation='Exploratory paired cost ratios only; not official score, proof, adoption, or success probability.')
    output_path.write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'status':report['status'],'paired_records_each_body':EXPECTED_PAIRS,
                      'cross_frontend_run_pairs':len(cross),'output':str(output_path)},indent=2))

if __name__=='__main__':
    main()
