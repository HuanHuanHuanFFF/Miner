#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
cd "${DEFLATE_ROOT:?}"
export PATH="$HOME/.local/bin:$HOME/.cargo/bin:$ELAN_HOME/bin:$PATH"
# Pinned Aeneas enables precompiled meta modules only when CI is absent.
# The official verifier's environment allowlist also omits CI. Build trusted
# dependencies with that same setting before the gate freezes them read-only.
unset CI
# Install every extraction component first: upstream's presence check otherwise
# mistakes a minimal nightly auto-installed by cargo for the full Charon toolchain.
rustup toolchain install nightly-2026-08-18 --profile minimal \
    --component rustc-dev,llvm-tools,rust-src
./setup.sh
just doctor
just check-pins
{
    git rev-parse HEAD
    lean --version
    rustc +nightly-2026-08-18 --version
    just --version
    uv --version
    uname -a
    lscpu | grep -E '^CPU\(s\):|^Model name:'
    sha256sum miner/template/parse.rs miner/template/Parse.lean
    sha256sum validator/lean/lake-manifest.json validator/verifier/PINS.json
    find data/benchmark/corpus-stage1 -maxdepth 1 -type f -print0 | sort -z | xargs -0 sha256sum
} | tee "$RUNNER_TEMP/deflate-reports/provenance.txt"
git diff --exit-code
df -h /
