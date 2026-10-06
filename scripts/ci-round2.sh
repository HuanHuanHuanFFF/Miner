#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
[[ ${GITHUB_REPOSITORY:-} == HuanHuanHuanFFF/Miner ]]
cd "${DEFLATE_ROOT:?}"
export PATH="$HOME/.local/bin:$HOME/.cargo/bin:$ELAN_HOME/bin:$PATH"
export VERIFY_CORPUS=corpus-stage1
export PYTHONPATH="$DEFLATE_ROOT/validator"
for candidate in bucket2 probe3 probe2-nice16 probe2-nice64; do
    echo "CANDIDATE_GATE_BEGIN $candidate"
    # Keep independent gates running so one extraction failure does not discard
    # the other candidates' evidence. A later workflow step checks all verdicts.
    if .venv/bin/python validator/verifier/verify.py "$GITHUB_WORKSPACE/candidates/$candidate" \
        --results "$RUNNER_TEMP/deflate-reports/$candidate-gate.json" --keep always; then
        cat "$RUNNER_TEMP/deflate-reports/$candidate-gate.json"
    else
        if [ -f "$RUNNER_TEMP/deflate-reports/$candidate-gate.json" ]; then
            cat "$RUNNER_TEMP/deflate-reports/$candidate-gate.json"
        fi
        echo "CANDIDATE_GATE_FAILED $candidate"
    fi
    echo "CANDIDATE_GATE_END $candidate"
done
git diff --exit-code
