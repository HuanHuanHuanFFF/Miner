#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
[[ ${GITHUB_REPOSITORY:-} == HuanHuanHuanFFF/Miner ]]
cd "${DEFLATE_ROOT:?}"
export PATH="$HOME/.local/bin:$HOME/.cargo/bin:$ELAN_HOME/bin:$PATH"
export VERIFY_CORPUS=corpus-stage1
export PYTHONPATH="$DEFLATE_ROOT/validator"
candidates=(probe3 probe2-nice16 probe2-nice64)
if [[ ${INCLUDE_BUCKET2:-false} == true ]]; then
    candidates=(bucket2 "${candidates[@]}")
fi
for candidate in "${candidates[@]}"; do
    echo "CANDIDATE_GATE_BEGIN $candidate"
    if [[ ${REUSE_VERIFIED_CONTROLS:-false} == true && $candidate != bucket2 ]]; then
        .venv/bin/python - "$candidate" <<'PY'
import hashlib, json, os, pathlib, sys
workspace = pathlib.Path(os.environ['GITHUB_WORKSPACE'])
candidate = sys.argv[1]
receipts = json.loads((workspace / 'evidence/round2/accepted-control-proofs.json').read_text())
assert receipts['official_revision'] == 'a356bbff18b60c4527fbcc85d5a28ef9c20214e0'
receipt = receipts['candidates'][candidate]
for filename in ('parse.rs', 'Parse.lean'):
    assert hashlib.sha256((workspace / 'candidates' / candidate / filename).read_bytes()).hexdigest() == receipt['sha256'][filename]
report = json.loads((workspace / receipt['gate_report']).read_text())
assert report['accepted'] and report['corpora'] == ['corpus-stage1']
report['proof_evidence'] = {'reuse': True, 'ci_run': receipts['ci_run'], 'commit': receipts['commit'],
                          'sha256': receipt['sha256'], 'scope': 'same source/proof, pinned official revision and toolchain; fresh timing follows'}
target = pathlib.Path(os.environ['RUNNER_TEMP']) / 'deflate-reports' / (candidate + '-gate.json')
target.write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps(report))
PY
        echo "CANDIDATE_GATE_END $candidate"
        continue
    fi
    # Keep independent gates running so one extraction failure does not discard
    # the other candidates' evidence. A later workflow step checks all verdicts.
    if .venv/bin/python validator/verifier/verify.py "$GITHUB_WORKSPACE/candidates/$candidate" \
        --results "$RUNNER_TEMP/deflate-reports/$candidate-gate.json" --keep always \
        2>&1 | tee "$RUNNER_TEMP/deflate-reports/$candidate-gate.log"; then
        cat "$RUNNER_TEMP/deflate-reports/$candidate-gate.json"
    else
        pipeline_exits=("${PIPESTATUS[@]}")
        gate_exit=${pipeline_exits[0]}
        if [[ ${pipeline_exits[1]} != 0 ]]; then
            echo 'Could not preserve official gate log; stop with a CI error.' >&2
            exit 2
        fi
        .venv/bin/python "$GITHUB_WORKSPACE/scripts/round2-gate-diagnostics.py" "$candidate"
        if [ -f "$RUNNER_TEMP/deflate-reports/$candidate-gate.json" ]; then
            cat "$RUNNER_TEMP/deflate-reports/$candidate-gate.json"
        else
            # The official verifier writes --results only after proof acceptance
            # reaches scoring. Preserve an explicit wrapper status when it exits
            # earlier; this is not an official scoring verdict.
            .venv/bin/python - "$candidate" "$gate_exit" <<'PY'
import json, os, pathlib, sys
path = pathlib.Path(os.environ['RUNNER_TEMP']) / 'deflate-reports' / (sys.argv[1] + '-gate.json')
report = {'accepted': False, 'origin': 'ci wrapper, official gate produced no scoring JSON',
          'gate_exit_code': int(sys.argv[2]), 'scope': 'see full gate log for rejection or validator error'}
path.write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps(report))
PY
        fi
        echo "CANDIDATE_GATE_FAILED $candidate"
        # An experimental proof rejection is distinct from a validator error.
        # Exit 2 means the environment/checker failed and must not be hidden.
        if [[ $gate_exit == 2 ]]; then
            exit 2
        fi
    fi
    echo "CANDIDATE_GATE_END $candidate"
done
git diff --exit-code
