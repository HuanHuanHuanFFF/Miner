#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
[[ ${GITHUB_REPOSITORY:-} == HuanHuanHuanFFF/Miner ]]

# Only this disposable hosted runner's unused SDKs are removed. No desktop runs.
df -h /
sudo rm -rf /usr/share/dotnet /usr/local/lib/android /opt/ghc \
    /usr/local/.ghcup /opt/hostedtoolcache/CodeQL /usr/share/swift
free_bytes=$(df -B1 --output=avail "$RUNNER_TEMP" | tail -1 | tr -d ' ')
if (( free_bytes < 24 * 1024 * 1024 * 1024 )); then
    echo 'Less than 24 GiB available after hosted-runner cleanup; stop before installing.' >&2
    exit 1
fi

sudo apt-get update -qq
sudo apt-get install -y --no-install-recommends build-essential bubblewrap curl \
    python3 python3-venv git pkg-config libssl-dev zlib1g-dev dbus-user-session
# This is the same disposable-runner namespace setting as upstream gate.yml.
sudo sysctl -w kernel.apparmor_restrict_unprivileged_userns=0
sudo loginctl enable-linger "$USER"
sudo systemctl start "user@$(id -u).service"
export XDG_RUNTIME_DIR="/run/user/$(id -u)"
export DBUS_SESSION_BUS_ADDRESS="unix:path=$XDG_RUNTIME_DIR/bus"

root="$RUNNER_TEMP/deflate-upstream"
export GIT_TERMINAL_PROMPT=0
git init "$root"
git -C "$root" remote add origin https://github.com/conjectures-io/conjectures-optimisation-deflate.git
git -C "$root" fetch --depth 1 origin a356bbff18b60c4527fbcc85d5a28ef9c20214e0
git -C "$root" checkout --detach FETCH_HEAD
test -L "$root/validator/slot/src/parse.rs"
python3 - "$root" <<'PY'
import hashlib, json, pathlib, sys
r = pathlib.Path(sys.argv[1]) / 'validator'
pins = json.loads((r/'verifier/PINS.json').read_text())
bad = [k for k,v in pins.items() if hashlib.sha256((r/k).read_bytes()).hexdigest() != v]
print(f'Official pinned source files: {len(pins)-len(bad)}/{len(pins)} match')
if bad:
    raise SystemExit(bad)
PY

mkdir -p "$RUNNER_TEMP/deflate-reports" "$RUNNER_TEMP/deflate-cache"
{
    echo "DEFLATE_ROOT=$root"
    echo "ELAN_HOME=$root/validator/.work/elan"
    echo "XDG_CACHE_HOME=$RUNNER_TEMP/deflate-cache"
    echo "UV_CACHE_DIR=$RUNNER_TEMP/deflate-cache/uv"
    echo "XDG_RUNTIME_DIR=/run/user/$(id -u)"
    echo "DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/$(id -u)/bus"
    echo 'VERIFY_CORPUS=corpus-stage1'
    echo 'VERIFY_SANDBOX=bwrap'
    echo 'GIT_TERMINAL_PROMPT=0'
} >> "$GITHUB_ENV"
systemd-run --user --wait --collect --property=MemoryMax=64M true
bwrap --ro-bind / / --unshare-net true
