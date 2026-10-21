#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
export PATH="$HOME/.elan/bin:$PATH"
python3 "$GITHUB_WORKSPACE/competitions/floatlib/scripts/run-gates.py"
