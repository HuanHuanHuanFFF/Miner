"""Bind A19 feedback to existing raw/role-separated evidence; no fresh scores."""
from pathlib import Path
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/route-a'

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    paths = [
        'evidence/round26/route-a/a19-paired-cost.json',
        'evidence/round26/route-a/a19-process-audit.json',
        'evidence/round26/extension4h/roles-b33-a19-29879.json',
        'evidence/round26/extension4h/analysis-b33-a19-29879.json',
        'evidence/round26/38224543411/screen-a19/gate/gate-summary.json',
        'evidence/round26/38224543411/screen-a19/gate/equivalence-research.json',
        'evidence/round26/38224543411/screen-a19/gate/research5/research.json',
        'evidence/round26/38224543411/screen-a19/gate/r12-decode/decode.json',
        'evidence/round26/measurement-diagnosis/decision-note.md',
        'evidence/round26/measurement-diagnosis/affinity-scope/receipt.json',
        'docs/rounds/round23.md',
    ]
    cost = json.loads((ROOT / paths[0]).read_bytes())
    proc = json.loads((ROOT / paths[1]).read_bytes())
    roles = json.loads((ROOT / paths[2]).read_bytes())
    name = 'r26-a-658-safe-word-offsets'
    summaries = [s for s in roles['summaries'] if name in s['candidate_names']]
    assert len(summaries) == 4
    assert all(s['at_least_5_count'] == s['at_least_10_count'] == 0 for s in summaries)
    source = ROOT / 'candidates' / name
    assert sha(source / 'parse.rs') == cost['hashes']['parse.rs']
    assert sha(source / 'Parse.lean') == cost['hashes']['Parse.lean']
    row9 = {'lean.txt','multibyte.txt','source.c.txt','source.rs.txt','sourcemap.map.txt'}
    slim = []
    for c in cost['comparisons']:
        s = {k:c[k] for k in ('A','B','block','same_source_binary','relative_total_axis_pct','components','changed_token_files')}
        affected = [f for f in c['files'] if f['file'] in row9]
        assert len(affected) == 5
        s['row9_five_file_components'] = {k:sum(f[k] for f in affected) for k in c['components']}
        slim.append(s)
    report = {
        'status':'VERIFIED_SCREEN_AND_DESCRIPTIVE_DIAGNOSIS_NO_STABLE_GAIN_NO_FULL_GATE',
        'run_id':'38224543411', 'source_commit':cost['source_commit'], 'candidate':name,
        'hashes':cost['hashes'], 'input_sha256':{p:sha(ROOT/p) for p in paths},
        'exact_source_change':'Only two additions in u118_common word-loop use wrapping_add; no be8, tail, route, search or budget change.',
        'finite_checks':'1548 actual helper cases, all 28 native tokens/output and original encoder/decode match public658; paired run retains 28 identities.',
        'extraction':'Precise candidate official extraction completed in this screen before measurements; extraction is not a Lean correctness gate.',
        'historical_score_context':{
            'label':'INFERRED_SAVED_SNAPSHOT_29879_NOT_A_NEW_OFFICIAL_QUERY',
            'snapshot':roles['snapshot'], 'role_separated_summaries':summaries,
            'interpretation':'Two discovery blocks on one runner. Main/copy and primary/shadow calibration views do not create independent samples or success probabilities. Formal admission, private data, payable share and rewards UNKNOWN.'},
        'paired_total_median_decomposition':slim,
        'same_source_distribution_findings':[
            'B2 parent shadow: 12/28 candidate encoder and 10/28 incumbent encoder files have all 11 measured values below the main range. Their encoder changes have matching sign on 26/28 files.',
            'B2 candidate shadow: encoder changes agree in sign with incumbent on 28/28 files. First five files are about 12-14% lower across stages, while lean/machine-code are about 13-14% higher. This is not a single global process multiplier.',
            'B2 parent tail from source.rs through weights-q8 generally moves lower together across parser, encoder and incumbent. Some small parser measurements and transition files are exceptions; inspect full audit.',
            'Every process fixes incumbent first, candidate second. Reverse blocks reverse separate process order only. Same-source processes are about 16 seconds apart.',
            'No per-call CPU/frequency or effective engine affinity/cgroup was saved. Driver process_affinity [0,1,2,3] is not proof the sandbox engine migrated. Requested sandbox AllowedCPUs=0 remains separate from effective state.'
        ],
        'decision':'Stop full proof/gate and new A19 timing allocation under predeclaration. Retain candidate, exact lowerings, 0.7763018502% primary-calibrated peak and 0.8848978929% shadow-calibrated peak plus every zero. Neither same-source candidate copy has a positive projected share. No stable positive gain or 5%/10% target established.',
        'diagnostic_allocation':{
            'existing_R23':'Equal-count fixed20/balanced20 already supports order effects but did not eliminate same-source residuals. A19 bands are compatible with unresolved changing machine/process state; equality of root cause UNKNOWN.',
            'next_specific_gap':'Capture actual original-sandbox engine PID affinity/cgroup effective CPU set and available sampled CPU/frequency in a future separately labeled diagnostic. Never infer engine placement from driver metadata.',
            'current_recommendation':'Do not repeat balanced-order CI or add reps for this exact thin component. No new timing job requested by this feedback. A future placement observation cannot retroactively identify this run or correct its score.'},
        'limits':['Algebraic parse/encode/denominator decomposition is descriptive, not causal attribution.',
                  'Stage medians in process audit diagnose distributions only; original total-median score remains unchanged.',
                  'Source, finite equivalence, extraction and public decode do not replace exact full Lean gate.',
                  'Performance signs on one runner do not prove the component universally slow; decision is budget allocation on available evidence.']}
    target = OUT / 'a19-screen-feedback.json'
    target.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({'feedback':target.relative_to(ROOT).as_posix(),'sha256':sha(target),
                      'summaries':[{k:s[k] for k in ('entry_role','calibration','minimum_pct','median_pct','maximum_pct','zero_count')} for s in summaries]},indent=2))

if __name__ == '__main__':
    main()
