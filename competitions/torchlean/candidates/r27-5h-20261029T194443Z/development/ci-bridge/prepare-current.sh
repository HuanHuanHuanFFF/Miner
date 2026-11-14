#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
[[ ${GITHUB_REPOSITORY:-} == HuanHuanHuanFFF/Miner ]]
official="$RUNNER_TEMP/floatlib-upstream"
reports="$RUNNER_TEMP/torchlean-reports"
mkdir -p "$reports"
exec > >(tee -a "$reports/prepare.log") 2>&1
commit=27fb1d19c712ead50ad34b4ad0d4ba597161e616
git init "$official"
git -C "$official" remote add origin https://github.com/conjectures-io/conjectures-optimisation-float-kernels.git
git -C "$official" fetch --depth 1 origin "$commit"
git -C "$official" checkout --detach FETCH_HEAD
test "$(git -C "$official" rev-parse HEAD)" = "$commit"
sudo apt-get update -qq
sudo apt-get install -y --no-install-recommends python3-venv curl git util-linux build-essential meson ninja-build pkg-config libcap-dev dbus-user-session
sudo sysctl -w kernel.apparmor_restrict_unprivileged_userns=0
sudo loginctl enable-linger "$USER"
sudo systemctl start "user@$(id -u).service"
export XDG_RUNTIME_DIR="/run/user/$(id -u)"
export DBUS_SESSION_BUS_ADDRESS="unix:path=$XDG_RUNTIME_DIR/bus"
systemd-run --user --wait --collect --property=MemoryMax=64M true
cpu=$(python3 -c 'import os; print(min(os.sched_getaffinity(0)))')
{
 echo "TORCHLEAN_ROOT=$official"
 echo "TORCHLEAN_REPORTS=$reports"
 echo "BENCH_CPU=$cpu"
 echo "XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR"
 echo "DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS"
 echo 'GIT_TERMINAL_PROMPT=0'
} >> "$GITHUB_ENV"
