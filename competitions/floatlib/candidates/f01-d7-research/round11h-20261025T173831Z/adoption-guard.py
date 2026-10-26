"""Fail closed local retention rule; this is not official champion admission."""
from pathlib import Path
import hashlib
import json
import math
import random
import re
import subprocess
import statistics

OFFICIAL = '4b7e83841cc0c32c6529f533923c73d33b5ecf97'
SUITE_SHA = 'a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a'
GENERATOR_SHA = '7198464dfc08f4bb2a3a5e31ce5a105964d1d73ad6b11ee49e682a30c04daf69'
SELECTION_POLICY = {'method': 'LOCAL_INDEPENDENT_CROSS_GATE_BOOTSTRAP',
    'headline_normalized_ratio_max': 0.97, 'gain_p05_min_exclusive': 0.0,
    'bootstrap_samples': 2000, 'bootstrap_seed': 90423,
    'round_statistic': 'median(submission_ns/incumbent_ns)',
    'resampling': 'independent gates with paired reference/submission rounds'}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read(path):
    return json.loads(path.read_bytes())


def inside(base, relative):
    p = (base / relative).resolve()
    require(p.is_relative_to(base.resolve()), 'Path escapes evidence root')
    return p


def unique(rows, name):
    values = [r for r in rows if r['candidate'] == name]
    require(len(values) == 1, 'Missing/duplicate candidate ' + name)
    return values[0]


def positive(value):
    return type(value) in (int, float) and math.isfinite(value) and value > 0


def validate_packets(packets, candidate, previous, candidate_sha, baseline_sha):
    require(candidate != previous and len(packets) == 2, 'Two distinct candidate/baseline gates required')
    require(len({p['run_id'] for p in packets}) == 2 and
            len({p['job_id'] for p in packets}) == 2, 'Two distinct actual runs/jobs required')
    require(packets[0]['seed'] != packets[1]['seed'], 'Independent seed required')
    findings = []
    rng = random.Random(SELECTION_POLICY['bootstrap_seed'])
    for p in packets:
        plan = p['plan']
        require(plan.get('selection_policy') == SELECTION_POLICY and all(type(plan['selection_policy'][k]) is type(v) for k,v in SELECTION_POLICY.items()), 'Missing or changed pre-frozen selection_policy')
        require(plan.get('comparison_baseline') == previous, 'Wrong baseline name')
        require(p['hosted_ubuntu24'], 'Fresh hosted Ubuntu24 evidence missing')
        require(not p['codegen_present'] and not plan.get('profile_parent') and
                not plan.get('profile_current') and
                not any(r.get('capture_codegen') for r in plan['candidates']), 'Observer must be disabled')
        ratios = []
        for name, sha in [(candidate, candidate_sha), (previous, baseline_sha)]:
            require(unique(plan['candidates'], name)['sha256'] == sha and
                    p['kernel_hashes'][name] == sha, 'Kernel/baseline hash mismatch')
            v = p['verdicts'][name]
            # Failed statement verdicts legitimately carry seed0; reject on stage first.
            require(v['passed'] is True and v['mode'] == 'gate' and v['stage'] == 'score', 'Not a complete passed gate: ' + name)
            require(v['seed'] == p['seed'] == plan['seed'], 'Plan/summary/full-verdict seed mismatch')
            require(v['suite']['sha256'] == SUITE_SHA and
                    v['verifier_fingerprint'] == v['verifier_fingerprint_end'] and
                    bool(v['verifier_fingerprint']), 'Suite/verifier mismatch')
            require(positive(v['ratio']) and len(v['rounds']) == 25, '25 positive rounds required')
            require(all(len(r) == 2 and all(positive(x) for x in r) for r in v['rounds']), 'Invalid paired rounds')
            ratios.append([sub / inc for inc, sub in v['rounds']])
        require(p['verdicts'][candidate]['verifier_fingerprint'] ==
                p['verdicts'][previous]['verifier_fingerprint'], 'Candidate/baseline verifier mismatch')
        relative = p['verdicts'][candidate]['ratio'] / p['verdicts'][previous]['ratio']
        require(relative <= SELECTION_POLICY['headline_normalized_ratio_max'], 'Insufficient headline improvement')
        gains = []
        for _ in range(SELECTION_POLICY['bootstrap_samples']):
            medians = [statistics.median(values[rng.randrange(25)] for _ in range(25)) for values in ratios]
            gains.append(1 - medians[0] / medians[1])
        gains.sort()
        k = .05 * (len(gains) - 1)
        lo = int(k)
        p05 = gains[lo] + (gains[lo + 1] - gains[lo]) * (k - lo)
        require(p05 > SELECTION_POLICY['gain_p05_min_exclusive'], 'Local gain p05 is not positive')
        findings.append({'run': p['run_id'], 'job': p['job_id'], 'seed': p['seed'],
                         'relative_normalized_ratio': relative, 'gain_p05': p05})
    confirmation = unique(packets[1]['plan'].get('confirmation_candidates', []), candidate)
    require(confirmation['sha256'] == candidate_sha and
            confirmation['prior_discovery_run'] == packets[0]['run_id'], 'Confirmation freeze mismatch')
    return {'accepted': True, 'method': SELECTION_POLICY['method'], 'selection_policy': SELECTION_POLICY,
            'samples': findings, 'quantile': 'linear interpolation at (n-1)*0.05',
            'scope': 'Local retention only; independent cross-gate bootstrap, not official paired admission'}


def read_tree_blob(root, sha, relative):
    """Read immutable local Git objects only; no checkout, fetch, shell or mutation."""
    require(re.fullmatch(r'[0-9a-f]{40}', sha) is not None, 'Invalid run HEAD')
    require(not relative.startswith('/') and ':' not in relative and '\\' not in relative and
            '..' not in relative.split('/'), 'Invalid commit-tree path')
    return subprocess.check_output(['git', 'cat-file', 'blob', sha + ':' + relative],
                                   cwd=root, timeout=15)


def load_run(root, own, rid, names):
    rp = root / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs' / str(rid)
    ci = read(rp / 'ci-run.json'); index = read(rp / 'original-artifact-hashes.json')
    artifact = inside(rp, index['directory'])
    require(ci['databaseId'] == rid and ci['status'] == 'completed' and ci['event'] == 'workflow_dispatch', 'Wrong CI identity/status')
    require(index['artifact']['workflow_run']['id'] == rid and
            index['artifact']['workflow_run']['head_sha'] == ci['headSha'], 'Artifact/run HEAD mismatch')
    listed = [x for x in read(rp / 'artifacts.json')['artifacts'] if x['id'] == index['artifact']['id']]
    require(len(listed) == 1 and listed[0] == index['artifact'], 'Artifact index/listing identity mismatch')
    files = index['files']
    for filename, info in files.items():
        p = inside(artifact, filename)
        require(p.stat().st_size == info['bytes'] and digest(p) == info['sha256'], 'Artifact hash mismatch: ' + filename)
    def checked(relative):
        require(relative in files, 'Unindexed evidence: ' + relative)
        return inside(artifact, relative)
    provenance = read(checked('provenance.json'))
    require(str(provenance['run_id']) == str(rid) and provenance['source_commit'] == ci['headSha'], 'Provenance/run HEAD mismatch')
    prefix = 'diagnostics/f01-d7-public-suite/public-suite/'
    def evidence(name): return checked(prefix + name)
    summary = read(evidence('summary.json')); plan = read(evidence('requested-plan.json'))
    original_plan = read_tree_blob(root, ci['headSha'], 'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json')
    require(original_plan == evidence('requested-plan.json').read_bytes(), 'Original commit-tree plan differs from indexed request')
    original_adapter = read_tree_blob(root, ci['headSha'], 'competitions/floatlib/candidates/f01-d7-research/public-suite.py')
    require(original_adapter == (own / 'public-suite.py').read_bytes() and
            hashlib.sha256(original_adapter).hexdigest() == summary['adapter_sha256'], 'Original commit-tree adapter differs')
    require(summary['source_commit'] == ci['headSha'] and summary['official_commit'] == OFFICIAL and
            summary['complete'] is True and summary['rounds'] == 25 and summary['pairs'] == 500000,
            'Wrong/incomplete current full-suite protocol')
    require(plan.get('official_commit') == OFFICIAL and plan.get('suite') == 'suites/public-v2.json', 'Wrong requested protocol')
    require(all(summary.get(k) == v for k,v in read(evidence('provenance.json')).items()), 'Nested provenance/summary mismatch')
    require(summary['requested_plan_sha256'] == digest(evidence('requested-plan.json')) and
            summary['adapter_sha256'] == digest(own / 'public-suite.py') and
            summary['official_generator_sha256'] == GENERATOR_SHA and
            summary['suite_sha256'] == digest(evidence('public-v2.json')) == SUITE_SHA, 'Plan/adapter/generator/suite binding mismatch')
    require(evidence('official-source-clean.log').read_bytes() == b'', 'Official source changed')
    cases = read(evidence('public-drawn-plan.json'))['cases']
    require(len(cases) == 156 and sum(c['timed'] for c in cases) == 152 and len({c['name'] for c in cases}) == 156, 'Wrong public case coverage')
    work = read(evidence('public-cell-work.json'))
    expected = {c['name'].rsplit(':', 1)[0]: 0 for c in cases if c['timed']}
    for c in cases:
        if c['timed']: expected[c['name'].rsplit(':', 1)[0]] += c['work']
    require(work == expected and len(work) == 26 and all(positive(w) for w in work.values()), 'Cell work mismatch')
    verdicts = {}; hashes = {}; rows = {}; codegen = False
    for name in names:
        row = unique(summary['results'], name); rows[name] = row
        vp = evidence(row['verdict']); v = read(vp)
        require(re.fullmatch(r'[A-Za-z0-9_.-]+', name) is not None, 'Invalid candidate name')
        kp = evidence('inputs/' + name + '/Kernel.lean'); hashes[name] = digest(kp)
        original_kernel = read_tree_blob(root, ci['headSha'], 'competitions/floatlib/candidates/' + name + '/Kernel.lean')
        require(original_kernel == kp.read_bytes(), 'Original commit-tree Kernel differs: ' + name)
        require(row['kernel_sha256'] == hashes[name] and row['verdict_sha256'] == digest(vp), 'Input/verdict identity mismatch')
        require(row['full_gate'] is True and row['validation_mode'] == 'full-gate' and row['exit_code'] == 0 and
                v['passed'] is True and v['mode'] == 'gate' and v['stage'] == 'score', 'Not a complete passed gate: ' + name)
        require(v['submission'] == name and v['reference_complete'] is True and v['incumbent_failed'] is False and v['exhausted'] is False, 'Submission/reference completion mismatch')
        require(set(v['classes']) == set(work), 'Missing scored classes')
        require(all(positive(c[k]) for c in v['classes'].values() for k in ['submission_ns', 'incumbent_ns']), 'Invalid class time')
        totals = [sum(v['classes'][n][k] * work[n] for n in work) for k in ['submission_ns', 'incumbent_ns']]
        require(abs(totals[0] / totals[1] - v['ratio']) < 1e-10, 'Headline/classes mismatch')
        codegen |= row.get('codegen') is not None
        verdicts[name] = v
    jobs = [j for j in ci['jobs'] if j['name'] in ('verify', 'floatlib')]
    require(len(jobs) == 1 and jobs[0]['status'] == 'completed', 'Ambiguous/incomplete actual job')
    ci_log = (rp / 'ci.log').read_bytes()
    hosted = b'Image: ubuntu-24.04' in ci_log and b'Runner Image Provisioner' in ci_log
    return {'run_id': rid, 'job_id': jobs[0]['databaseId'],
            'run_conclusion': ci['conclusion'], 'job_conclusion': jobs[0]['conclusion'], 'job_name': jobs[0]['name'], 'hosted_ubuntu24': hosted,
            'seed': summary['seed'], 'plan': plan, 'verdicts': verdicts, 'kernel_hashes': hashes,
            'cell_work': work,
            'codegen_present': codegen or any(r.get('codegen') is not None for r in summary['results']) or any(k in summary for k in ('parent_stage_profile','current_stage_profile')),
            'evidence': {'ci_run_sha256': digest(rp / 'ci-run.json'), 'artifact_index_sha256': digest(rp / 'original-artifact-hashes.json'),
                'artifact_listing_sha256': digest(rp / 'artifacts.json'), 'summary_sha256': digest(evidence('summary.json')), 'plan_sha256': digest(evidence('requested-plan.json')),
                'source_commit': ci['headSha'], 'commit_tree_verified': ['suite-plan.json','public-suite.py'] + [n + '/Kernel.lean' for n in names],
                'run_conclusion': ci['conclusion'], 'job_conclusion': jobs[0]['conclusion'], 'job_name': jobs[0]['name'], 'input_sha256': hashes, 'suite_sha256': SUITE_SHA,
                'generator_sha256': GENERATOR_SHA, 'drawn_plan_sha256': digest(evidence('public-drawn-plan.json')),
                'ci_log_sha256': digest(rp / 'ci.log'), 'run_attempt': ci.get('runAttempt'),
                'runner': jobs[0].get('runnerName'), 'runner_basis': 'Distinct actual job IDs plus raw hosted Ubuntu24 setup log; absent runner/run_attempt fields remain unknown',
                'verdict_sha256': {n: digest(evidence(rows[n]['verdict'])) for n in names}}}


def verify_adoption(root, own, candidate, discovery, confirmation, previous):
    hashes = {n: digest(root / 'competitions/floatlib/candidates' / n / 'Kernel.lean') for n in (candidate, previous)}
    packets = [load_run(root, own, rid, (candidate, previous)) for rid in (discovery, confirmation)]
    require(all(p['run_conclusion'] == 'success' and p['job_conclusion'] == 'success' and p['job_name'] in ('verify', 'floatlib') for p in packets), 'Original run/job conclusions must both be success for adoption')
    references = {(v['incumbent_sha256'], v['champion_sha256']) for p in packets for v in p['verdicts'].values()}
    require(len(references) == 1, 'Shipped reference/champion identity changed across candidate/baseline gates')
    result = validate_packets(packets, candidate, previous, hashes[candidate], hashes[previous])
    result['identity'] = {'candidate': candidate, 'candidate_sha256': hashes[candidate], 'baseline': previous, 'baseline_sha256': hashes[previous]}
    result['evidence'] = [p['evidence'] for p in packets]
    result['random_stream'] = 'One Random(90423) stream; discovery then confirmation, candidate then baseline, 25 paired-round index draws each, 2000 replicates per run'
    result['helper_sha256'] = digest(Path(__file__).resolve())
    result['adapter_sha256'] = digest(own / 'public-suite.py')
    return result, packets
