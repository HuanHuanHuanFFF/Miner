"""Native-finish Winograd with a whole-call fallback when no input is admitted.
Previous owned/native sources remain unchanged. No new Correct is claimed.
"""
from __future__ import annotations
from datetime import datetime, timezone
import argparse, hashlib, importlib.util, json
from pathlib import Path

HERE = Path(__file__).resolve().parent
PARENT = '1af62f18ca8504564e50372f9d24a487ff8101cc6a3a00d4db475f23b41bb6a2'

def transform(raw, submission, variant='winograd12-nativefinish-v2'):
    assert submission == 12 and variant == 'winograd12-nativefinish-v2'
    spec = importlib.util.spec_from_file_location('r27_win_native_finish', HERE/'build_source12_nativefinish.py')
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    previous = module.transform(raw, 12)
    assert hashlib.sha256(previous).hexdigest() == PARENT
    source = previous.decode()
    start = source.index('def linear (rows n outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=')
    end = source.index('\nend R27Winograd', start)
    body = source[start:end]
    finite = 'X.all finiteWord && W.all finiteWord && b.all finiteWord'
    assert body.count(finite) == 1
    body = body.replace(finite, 'X.all finiteWord')
    old = '''    let BX := Array.ofFn (n := rows) (fun r => Submission.Yc X n r.val)
    let BW := Array.ofFn (n := outW) (fun j => Submission.Yc W n j.val)
    let A := Array.ofFn (n := rows) (fun r => prepare X (r.val*n) n BX[r.val]!)
    let B := Array.ofFn (n := outW) (fun j => prepare W (j.val*n) n BW[j.val]!)
'''
    new = '''    let BX := Array.ofFn (n := rows) (fun r => Submission.Yc X n r.val)
    let A := Array.ofFn (n := rows) (fun r => prepare X (r.val*n) n BX[r.val]!)
    if !(A.any (fun a => a.valid)) then
      Submission.retainedKernels.dense.linear rows n outW relu X W b
    else if !(W.all finiteWord && b.all finiteWord) then
      Submission.retainedKernels.dense.linear rows n outW relu X W b
    else
      let BW := Array.ofFn (n := outW) (fun j => Submission.Yc W n j.val)
      let B := Array.ofFn (n := outW) (fun j => prepare W (j.val*n) n BW[j.val]!)
'''
    assert body.count(old) == 1
    before, rest = body.split(old)
    body = before + new + '\n'.join('  '+line if line else line for line in rest.split('\n'))
    result = (source[:start]+body+source[end:]).encode()
    assert len(result) <= 256000
    return result

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--receipt', type=Path, required=True)
    args = parser.parse_args()
    result = transform(args.source.read_bytes(), 12)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(result)
    dependencies = ['build_source12_nativefinish.py', 'build_source12_probes.py', 'build_packed_probe.py',
                    'PackedLinearRuntime.lean', 'WinogradRuntime.lean.inc', 'WinogradNativeFinish.lean.inc']
    receipt = {'created_utc': datetime.now(timezone.utc).isoformat(),
      'state': 'UNCOMPILED_UNPROVED_NATIVE_ONLY_NO_CORRECT', 'parent_native_sha256': PARENT,
      'candidate_sha256': hashlib.sha256(result).hexdigest(), 'candidate_bytes': len(result),
      'builder_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
      'dependencies': {name: {'sha256': hashlib.sha256((HERE/name).read_bytes()).hexdigest(),
                              'bytes': (HERE/name).stat().st_size} for name in dependencies},
      'change': 'If all input factor caches are invalid, return strong original full linear before scanning/preparing weights; preserve four-row fallback fusion. Native word terminal from prior variant retained.',
      'evidence': 'nmlp-winograd-coverage.json: all9 sampled wide first-linear calls have no admitted input row',
      'comparison': 'Complete normalized_mlp cost only, against exact source12 internal control; current23 via explicitly inferred report chain only',
      'publication': 'Owned builder/metadata only; whole reconstructed source private'}
    args.receipt.write_text(json.dumps(receipt, indent=2), encoding='utf-8')
    print(json.dumps({key: receipt[key] for key in ['state', 'candidate_sha256', 'candidate_bytes', 'builder_sha256']}))

if __name__ == '__main__':
    main()
