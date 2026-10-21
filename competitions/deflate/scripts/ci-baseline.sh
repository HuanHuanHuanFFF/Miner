#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
cd "${DEFLATE_ROOT:?}"
export PATH="$HOME/.local/bin:$HOME/.cargo/bin:$ELAN_HOME/bin:$PATH"
export VERIFY_CORPUS=corpus-stage1
export PYTHONPATH="$DEFLATE_ROOT/validator"
.venv/bin/python validator/verifier/verify.py miner/template \
    --results "$RUNNER_TEMP/deflate-reports/baseline.json" --keep always
cat "$RUNNER_TEMP/deflate-reports/baseline.json"
git diff --exit-code
