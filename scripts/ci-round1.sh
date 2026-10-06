#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
[[ ${GITHUB_REPOSITORY:-} == HuanHuanHuanFFF/Miner ]]
cd "${DEFLATE_ROOT:?}"
export PATH="$HOME/.local/bin:$HOME/.cargo/bin:$ELAN_HOME/bin:$PATH"
export VERIFY_CORPUS=corpus-stage1
export PYTHONPATH="$DEFLATE_ROOT/validator"
failed=0
for candidate in hash-wide probe2; do
    echo "CANDIDATE_GATE_BEGIN $candidate"
    if .venv/bin/python validator/verifier/verify.py "$GITHUB_WORKSPACE/candidates/$candidate" \
        --results "$RUNNER_TEMP/deflate-reports/$candidate-gate.json" --keep always; then
        cat "$RUNNER_TEMP/deflate-reports/$candidate-gate.json"
    else
        failed=1
    fi
    echo "CANDIDATE_GATE_END $candidate"
done
git diff --exit-code
exit "$failed"
