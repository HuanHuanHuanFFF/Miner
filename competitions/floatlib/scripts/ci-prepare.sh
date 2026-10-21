#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
[[ ${GITHUB_REPOSITORY:-} == HuanHuanHuanFFF/Miner ]]
repo="$GITHUB_WORKSPACE"
official="$RUNNER_TEMP/floatlib-upstream"
reports="$RUNNER_TEMP/floatlib-reports"
mkdir -p "$reports"
exec > >(tee -a "$reports/prepare.log") 2>&1
commit=$(python3 -c 'import json,os; print(json.load(open(os.path.join(os.environ["GITHUB_WORKSPACE"],"competitions/floatlib/pins.json")))["official_commit"])')
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
  echo "FLOATLIB_ROOT=$official"
  echo "FLOATLIB_REPORTS=$reports"
  echo "BENCH_CPU=$cpu"
  echo 'BENCH_ROUNDS=25'
  echo 'BENCH_PAIRS=500000'
  echo "XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR"
  echo "DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS"
  echo 'GIT_TERMINAL_PROMPT=0'
} >> "$GITHUB_ENV"
python3 - "$repo" "$official" "$reports" "$cpu" <<'PY'
import sys,pathlib,json,hashlib,subprocess,datetime,platform
r,u,o=map(pathlib.Path,sys.argv[1:4]);cpu=sys.argv[4]
pins=json.loads((r/'competitions/floatlib/pins.json').read_text())
assert (u/'lean/lean-toolchain').read_text().strip()==pins['lean_toolchain']
tracked=subprocess.check_output(['git','ls-files','-z'],cwd=u).decode().split('\0')
hashes={p:hashlib.sha256((u/p).read_bytes()).hexdigest() for p in tracked if p and (u/p).is_file()}
record={'prepared_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'source_commit':subprocess.check_output(['git','rev-parse','HEAD'],cwd=r).decode().strip(),'official_commit':pins['official_commit'],'run_id':__import__('os').environ['GITHUB_RUN_ID'],'cpu_affinity':cpu,'platform':platform.platform(),'lscpu':subprocess.check_output(['lscpu'],text=True),'pins':pins,'official_tracked_sha256':hashes}
(o/'provenance.json').write_text(json.dumps(record,indent=2)+'\n')
PY
