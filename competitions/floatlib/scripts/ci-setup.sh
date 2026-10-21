#!/usr/bin/env bash
set -euo pipefail
[[ ${GITHUB_ACTIONS:-} == true && ${RUNNER_OS:-} == Linux ]]
cd "$FLOATLIB_ROOT"
set -o pipefail
./setup.sh 2>&1 | tee "$FLOATLIB_REPORTS/setup.log"
./setup.sh --check 2>&1 | tee "$FLOATLIB_REPORTS/setup-check.log"
git diff --exit-code
python3 - "$FLOATLIB_REPORTS" <<'PY'
import pathlib,json,subprocess,sys,datetime
o=pathlib.Path(sys.argv[1]);p=o/'environment.json'
r={'checked_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'setup_exit':'PASS','lean':subprocess.check_output(['bash','-c','cd lean && "$HOME/.elan/bin/lake" env lean --version'],text=True).strip(),'python':subprocess.check_output(['.venv/bin/python','--version'],text=True).strip(),'bwrap':subprocess.check_output(['.venv/bin/bwrap','--version'],text=True).strip(),'systemd_caps':'ENABLED','official_source_diff':'CLEAN'}
p.write_text(json.dumps(r,indent=2)+'\n')
PY
