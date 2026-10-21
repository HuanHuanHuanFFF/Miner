#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
[[ ${GITHUB_REPOSITORY:-} == HuanHuanHuanFFF/Miner ]]
export GIT_TERMINAL_PROMPT=0
upstream="$RUNNER_TEMP/deflate-native-upstream"
git init "$upstream"
git -C "$upstream" remote add origin https://github.com/conjectures-io/conjectures-optimisation-deflate.git
git -C "$upstream" fetch --depth 1 origin a356bbff18b60c4527fbcc85d5a28ef9c20214e0
git -C "$upstream" checkout --detach FETCH_HEAD
python3 - "$upstream" <<'PY'
import hashlib, json, pathlib, sys
root = pathlib.Path(sys.argv[1]) / 'validator'
pins = json.loads((root / 'verifier/PINS.json').read_bytes())
assert all(hashlib.sha256((root/p).read_bytes()).hexdigest()==h for p,h in pins.items())
print('VERIFIED_SOURCE_PINS', len(pins))
PY
bash "$upstream/scripts/pull-corpus.sh" --stage 1
rustup toolchain install nightly-2026-08-18 --profile minimal
rustc +nightly-2026-08-18 --version
git -C "$upstream" diff --exit-code
echo "DEFLATE_ROOT=$upstream" >> "$GITHUB_ENV"
