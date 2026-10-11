"""Summarize641process disagreement and prepare one conditional diagnostic plan."""
from datetime import datetime, timezone
import importlib
import json

M = importlib.import_module('r26-score-map')
ROOT = M.ROOT
OUT = ROOT / 'evidence/round26/measurement-diagnosis'
OLD = ['evidence/round18/noise-as-analysis.json', 'evidence/round18/order-k-analysis.json',
       'evidence/round20/library-r-analysis.json', 'evidence/round23/diagnostic-analysis.json',
       'evidence/round24/affinity-af-analysis.json', 'evidence/round24/layout-av-analysis.json',
       'evidence/round24/confirmation-control-final.json']


def main():
    rawpath = OUT / 'raw-decomposition-29795.json'
    data = json.loads(rawpath.read_bytes())
    coherence = []
    for pair in data['same_source_pairs']:
        if pair['A'] != 'public641':
            continue
        fs = pair['files']
        positives = sum(f['encode_relative_pct_contribution'] > 0 for f in fs)
        disjoint = [f['file'] for f in fs if min(r['encode_s'] for r in f['B_candidate']['reps']) > max(r['encode_s'] for r in f['A_candidate']['reps'])]
        coherence.append({'run_id': pair['run_id'], 'block': pair['block'], 'axis_gap_pct': pair['axis_gap_pct'],
                          'components': pair['components'], 'encoder_positive_files': positives,
                          'B_all11_encode_above_A_all11_files': disjoint,
                          'top5_share_of_sum_absolute_file_axis_deltas': sum(abs(f['axis_delta']) for f in sorted(fs, key=lambda f: abs(f['axis_delta']), reverse=True)[:5]) / sum(abs(f['axis_delta']) for f in fs),
                          'top_files': [{k: f[k] for k in ['file', 'parse_relative_pct_contribution', 'encode_relative_pct_contribution', 'denominator_relative_pct_contribution']} for f in sorted(fs, key=lambda f: abs(f['axis_delta']), reverse=True)[:5]]})
    old = []
    for path in OLD:
        source = ROOT / path
        record = json.loads(source.read_bytes())
        old.append({'path': path, 'sha256': M.digest(source),
                    'scope': record.get('scope') or record.get('limits'),
                    'decision': record.get('decision'), 'summary': record.get('summary'),
                    'absolute_gap_medians': record.get('absolute_gap_medians')})
    inputs = dict(data['input_files'])
    for run in data['runs']:
        folder = ROOT / 'evidence/round26' / run['run_id'] / run['batch'] / 'gate'
        for file in ['state.json', 'ci-run.json', 'raw-artifact-files.json']:
            path = folder / file
            inputs[path.relative_to(ROOT).as_posix()] = {'sha256': M.digest(path), 'bytes': path.stat().st_size}
    for path in OLD + ['scripts/round4.py', 'scripts/decompose-round25-cost.py',
                       'sources/conjectures-optimisation-deflate/validator/measure/src/main.rs']:
        source = ROOT / path
        inputs[path] = {'sha256': M.digest(source), 'bytes': source.stat().st_size}
    folder = ROOT / 'evidence/round26/official-route2'
    receipt = json.loads((folder / 'receipt.json').read_bytes())
    for record in receipt['raw_response_files']:
        path = folder / record['file']
        assert M.digest(path) == record['sha256']
        inputs[path.relative_to(ROOT).as_posix()] = {'sha256': record['sha256'], 'bytes': record['bytes']}
    for file, record in receipt['derived_files'].items():
        path = folder / file
        assert M.digest(path) == record['sha256']
        inputs[path.relative_to(ROOT).as_posix()] = record
    summary = {'status': 'VERIFIED_DESCRIPTIVE_DIAGNOSIS_WITH_UNRESOLVED_CAUSE',
               'checked_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': data['snapshot'],
               'public641_coherence': coherence, 'prior_diagnostics_read': old,
               'input_hashes': inputs, 'raw_decomposition_sha256': M.digest(rawpath),
               'excluded': ['Input/token/output mismatch for same-source aliases in these raw captures.',
                            'Different parser binary, incumbent binary, engine hash, or repetition protocol within641aliaspairs.',
                            'A67block1issolelyincumbentdenominator: encoder contributes+1.20798%, denominator-0.06107%.',
                            'A67block1encoderdifference comes only from one slow repetition or one file:23positivefiles anddisjointall11distributions acrossmanyfiles.'],
               'unresolved': ['Process lifetime/runtime address or buffer/cache layout interactions: samebinaryhashdoesnotfixruntimeaddresses.',
                              'CPU migration, shared-host contention, frequency/cache state: actualaffinity[0,1,2,3], governorandtime-resolvedCPUcontextmissing.',
                              'Process sequencing and long-lived drift: reversedblockchanges signs, butdifferentprocesses preventcausalidentification.',
                              'Parser versus encoder stage effect is pair-specific: hash17ownaliasblock1isparserdominated; no universal correction.'],
               'recommendation_now': 'Do not allocate another mechanicalfixed11/fixed20/balanced20/library/affinity sweep to these candidates. All declared primaryshareviews on29795arezero and none reaches5even under641shadow. Continuealgorithmicresearchandpreserveconfirmationreserve.',
               'reopen_condition': 'A new frozencandidate has material original-protocolsignal near the5/10decisionboundary, and repeated641aliasdifferences can change its promotion decision. At that point a targetedencoderprocess probe may change whether to invest in newrunnerconfirmation or more stage-level diagnosis.',
               'limits': ['Capturedtrace replay catches the disagreement but does not reproduce its environmentalcause anew.',
                          'Percent components are exact descriptive contributions to relative balanced-axis change, notpool-sharepoints or causality.',
                          'Prior diagnoses constrain uniform-fix claims, not all641-specific mechanisms.',
                          'No newmeasurement, confirmation, correctedscore, formaladmission, orCIwas performed.']}
    M.dump(OUT / 'diagnosis-summary-29795.json', summary)
    a67 = next(p for p in data['same_source_pairs'] if p['run_id'] == '38179533008' and p['block'] == 1 and p['A'] == 'public641')
    files = ['machine-code.bin', 'source.c.txt', 'records.json.txt']
    selected = [next(f for f in a67['files'] if f['file'] == name) for name in files]
    # Data-only draft: no workflow input has been installed and no job dispatched.
    plan = {'status': 'DRAFT_NOT_IMPLEMENTED_NOT_DISPATCHED_CONDITIONAL_DIAGNOSTIC',
            'question': 'Does the641encoder show a coherent between-process offset after holding tokens and encoder code fixed, or a within-process call-order effect?',
            'purpose': 'Choose between spending the next verification budget onfreshindependentrunners versus targetedwithin-processstateinvestigation. Never substitute this protocol forofficial11rep total-timeconfirmation.',
            'activation_condition': summary['reopen_condition'],
            'frozen_parser': {'path': 'references/round26-public-641/parse.rs', 'sha256': '97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'},
            'codec_sha256': '172c240014f65d5e2762c1287e4982dd1cd426f2999f74e17011e05f2dc5fdec',
            'token_codec_sha256': '8bf5d962324b3a0890f3c75f713198be086c4b0659797c24b8b976978cea4917',
            'fixtures': [{'file': f['file'], 'input_sha256': f['input_sha256'],
                          'tokens_sha256': a67['files'][a67['files'].index(f)]['A_candidate'].get('tokens_sha256'),
                          'identity_source': 'evidence/round26/38179533008/screen-a67/gate/round1-public641.jsonl'} for f in selected],
            'preflight': ['Regenerate641tokens once with exact parser. Match capturedinput/token/outputhashes andoriginaldecode. Freezeoneimmutabletokenarray perfile.',
                          'Oneexactharnessbinary, pinnedoriginalencoder, noobserver changes orofficialtree mutation. LabelA/Bcalls execute thesamefunction andsame frozeninput.',
                          'Recordactualaffinity, governor ifavailable, processPID, currentCPUbefore/aftereachencodedcall, processstarttime, andtoken/outputbufferaddress. Preserve rawallcalls.'],
            'protocol': {'runner_jobs': 1, 'fresh_child_processes': 4, 'files': files, 'warmup_encode_calls_per_file': 1,
                         'measured_encode_calls_per_file_per_process': 20,
                         'within_process_schedule': 'FiveABBAquartets; second/fourthprocessuseBAAB. A/Barelabelsforidenticalcalls, notdifferentimplementations.',
                         'between_process_file_order': ['forward', 'reverse', 'reverse', 'forward'],
                         'measure': 'Originalencoderonly wall time; parser runsbeforetiming solelyto regenerateandfreezeidenticaltokens. Noincumbentdenominator, scoreprojection, orcandidatechange.',
                         'environment': 'KeepdefaultrecordedCPUset foronefactor comparison; noaffinity/ASLR/librarycondition sweep inthisjob.',
                         'enforced_job_timeout_minutes_proposed': 12},
            'decision_rules': ['Compareallwithin-processABlabeldifferences andbetween-processperfiledistributions. Preserveoppositesigns andallnegativecases.',
                               'Coherentprocessoffsetwithsmallwithin-processlabelgap supportsbetween-processcontext/state overisolatedoutlier explanation. It stillcannotdistinguishCPU/frequency/layoutcauses.',
                               'Largewithin-processlabel/positioneffect supportsstateororderinteractions; do notpromotebenchmark correction.',
                               'Ifneitherpatternreappears, reportnonreproduction. Do notdeclarethe641measurementproblemfixed; return tooriginalprotocolconfirmation.',
                               'No universalnoisebound, numericalcorrection, averagecoordinate payout, orprivate-successprobability isderived.'],
            'cost_scope': 'Lightweightpreparedsource andfixtures locally; compile/execution onlyontemporaryLinuxrunner. Estimatedruntime isunknown untilimplemented; 12min isproposedenforcedcap, notexisting enforcement.'}
    # Bind exact fixture token/output identities from the original record.
    path = ROOT / 'evidence/round26/38179533008/screen-a67/gate/round1-public641.jsonl'
    records = [json.loads(line) for line in path.read_text().splitlines()]
    by = {r['file']: r for r in records if r['kind'] == 'file'}
    for fixture in plan['fixtures']:
        method = by[fixture['file']]['methods']['public641']
        fixture['tokens_sha256'], fixture['output_sha256'] = method['tokens_sha256'], method['output_sha256']
    M.dump(OUT / 'conditional-encoder-process-plan.json', plan)
    print(json.dumps({'status': summary['status'], 'coherence': coherence, 'input_files': len(inputs), 'diagnostic_plan_status': plan['status']}, indent=2))


if __name__ == '__main__':
    main()
