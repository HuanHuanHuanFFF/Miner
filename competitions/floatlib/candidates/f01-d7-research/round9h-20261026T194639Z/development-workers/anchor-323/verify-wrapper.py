"""Exercise adapter identity/save interception and reject a no-dry-run CLI."""
from contextlib import redirect_stdout
from copy import deepcopy
from datetime import datetime, timezone
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import subprocess
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
wrapper_path = HERE / 'estimator-reviewed323-draft.py'
spec = importlib.util.spec_from_file_location('r19_adapter_check', wrapper_path)
wrapper = importlib.util.module_from_spec(spec)
spec.loader.exec_module(wrapper)
est = wrapper.load_estimator()
if est.DEFAULT_ANCHOR != wrapper.DEFAULT_ANCHOR or est.main.__globals__ is not est.__dict__:
    raise ValueError('Adapter must return actual original module, not copied function aliases')
D7 = est.DATA
paths = [D7 / 'champion-time-estimate.json', D7 / 'multiplier-comparison.json',
         wrapper.ROOT / 'competitions/floatlib/coordination/development-status.json',
         D7 / 'current-official-snapshot.json']
before = {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
virtual_writes = {}
est.save = lambda path, value: virtual_writes.__setitem__(Path(path), deepcopy(value))
with redirect_stdout(io.StringIO()):
    # All three original save calls are intercepted in memory; no global writes.
    est.main([])
expected = set(paths[:3])
if set(virtual_writes) != expected:
    raise ValueError('Original save interception did not cover exactly model/view/state')
after = {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
if before != after:
    raise ValueError('Probe changed global bytes')
refused = subprocess.run([sys.executable, '-B', str(wrapper_path)], capture_output=True, text=True)
if refused.returncode != 2 or '--dry-run' not in refused.stderr:
    raise ValueError('Draft CLI did not reject write invocation')
receipt = {'status': 'PASS', 'verified_at_utc': datetime.now(timezone.utc).isoformat(),
    'wrapper_sha256': hashlib.sha256(wrapper_path.read_bytes()).hexdigest(),
    'original_sha256': wrapper.ORIGINAL_SHA256, 'anchor_sha256': wrapper.ANCHOR_SHA256,
    'returned_actual_original_module': True, 'default_anchor_override': str(est.DEFAULT_ANCHOR),
    'transaction_save_interception_works': True,
    'intercepted_in_memory_only_paths': sorted(p.relative_to(wrapper.ROOT).as_posix() for p in virtual_writes),
    'global_before_after_sha256': before, 'global_bytes_unchanged': True,
    'cli_without_dry_run_exit': refused.returncode,
    'scope': 'Adapter/API/read-only checks only. No adoption, gate, benchmark, source refit or global write was performed.'}
(HERE / 'wrapper-validation.json').write_bytes((json.dumps(receipt, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps({'status': 'PASS', 'transaction_save_interception_works': True, 'global_bytes_unchanged': True, 'cli_without_dry_run_exit': refused.returncode}))
