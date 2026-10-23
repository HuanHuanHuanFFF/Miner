"""One BMM cold-path candidate; verify by default, create only with --write."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, ast, hashlib, importlib.util, json, re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
PARENT = HERE.parent / 'f01-r8-combined-result-guard/Kernel.lean'
REPORT = HERE.parent / 'f01-d7-research/round1h-20261023T125752Z/astra-bmm.json'

def sha(b): return hashlib.sha256(b).hexdigest()

def main():
    ap = argparse.ArgumentParser(); ap.add_argument('--write', action='store_true'); args = ap.parse_args()
    raw = PARENT.read_bytes(); assert sha(raw) == '41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
    old = raw.decode(); assert '\r' not in old
    addition = (HERE / 'increment.lean').read_bytes().decode(); assert '\r' not in addition
    begin = old.index('namespace R7NaNReplay\n'); end = old.index('end R7NaNReplay', begin)
    block = old[begin:end]
    marker = 'def replayEarly (n baseA baseB p : Nat)'
    assert block.count(marker) == 1 and 'r9_nativeReplay' not in old
    source = block.replace(marker, addition + '\n' + marker)
    before = '  replayLoop n baseA baseB p Araw Braw 0 posZero'
    after = '  r9_nativeReplay n baseA baseB p Araw Braw'
    assert source.count(before) == 1; source = source.replace(before, after)
    proof_before = '  exact replayLoop_eq n baseA baseB p Araw Braw 0 posZero'
    proof_after = '  exact r9_nativeReplay_eq n baseA baseB p Araw Braw'
    assert source.count(proof_before) == 1; source = source.replace(proof_before, proof_after)
    result = old[:begin] + source + old[end:]; data = result.encode(); assert len(data) <= 256000
    inverse = source.replace(addition + '\n', '', 1).replace(after, before, 1).replace(proof_after, proof_before, 1)
    assert inverse == block and (old[:begin] + inverse + old[end:]).encode() == raw
    spec = importlib.util.spec_from_file_location('r8_source_inventory', HERE.parent / 'f01-r8-combined-result-guard/build.py')
    inv = importlib.util.module_from_spec(spec); spec.loader.exec_module(inv)
    decl = inv.declarations(result)
    names = ['Submission.'+n for n in ['add','add_spec','mul','mul_spec','sum','sum_spec','bmm','bmm_spec']]
    assert all(len(decl.get(n, [])) == 1 for n in names)
    assert result.endswith(old[end:])
    assert old[:begin] == result[:begin]
    gate = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/upstream/gate-4b7e838.py'
    assert sha(gate.read_bytes()) == '1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194'
    tree = ast.parse(gate.read_text())
    def val(name): return next(n for n in tree.body if isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id == name for t in n.targets)).value
    assert not re.compile(ast.literal_eval(val('BANNED').args[0])).search(result)
    env = {'re': re, 'OPTIONS': ast.literal_eval(val('OPTIONS'))}
    fn = next(n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name == 'options')
    exec(compile(ast.Module(body=[fn], type_ignores=[]), str(gate), 'exec'), env)
    assert env['options'](result) is None
    assert [ln for ln in result.splitlines() if re.search(r'\bimport\b', ln)] == ['import ContractTensor']
    allowed = ast.literal_eval(val('ATTRIBUTES'))
    for group in re.findall(r'@\[([^\]]*)\]', result):
        for attr in group.split(','): assert attr.split()[-1] in allowed
    now = datetime.now(timezone.utc).isoformat()
    manifest = {'candidate': HERE.name, 'candidate_file': 'Kernel.lean', 'candidate_sha256': sha(data), 'candidate_bytes': len(data), 'created_at_utc': now, 'parent': PARENT.parent.name, 'parent_sha256': sha(raw), 'validation_mode': 'full-gate', 'proof_status': 'NOT_RUN_EXACT_NATIVE_EVENT_REPLAY', 'mechanism': 'Keep all existing normalBMM passes/layout. Only rejectedNaN endpoint fallback uses native accumulator prefix, one exactraw repair at firstNaN, then unconditionalquiet absorption provedby actualW05. No perstep software wrapping in successful prefix.', 'difference_from_old_a9_draft': 'Use exactaccepted41 and its acceptedW05 quiet-event theorem; remove oldruntimequietcheck/exactsuffixfallback. Explicit foldcongruence avoids historical815 accumulatorrewrite mismatch. Never measured thismechanism before.', 'preserved': 'All bytes outside R7NaNReplay unchanged, including scalar41, singlepasssum, Nat/USize proofs, nativehotBMM andpacked/direct layouts. Existing exact quiet rawloop retained as unused alternative definition.', 'source_before_namespace_sha256': sha(old[:begin].encode()), 'source_after_namespace_sha256': sha(old[end:].encode()), 'original_namespace_sha256': sha(block.encode()), 'new_namespace_sha256': sha(source.encode()), 'increment_sha256': sha(addition.encode()), 'full_gate': 'NOT_RUN', 'performance': 'UNKNOWN', 'formal_submission': 'NOT_SUBMITTED', 'licences': 'All original notices and proof dependencies preserved; no source minification.'}
    previous = json.loads(REPORT.read_text()) if REPORT.exists() else {}
    report = {**previous, 'state': 'SINGLE_CANDIDATE_READY_STATIC_ONLY', 'candidate_ready_at_utc': now, 'candidate': manifest, 'inverse_parent_bytes_verified': True, 'changed_region': {'old_start_byte': len(old[:begin].encode()), 'old_bytes': len(block.encode()), 'new_bytes': len(source.encode()), 'untouched_prefix_bytes': len(old[:begin].encode()), 'untouched_suffix_bytes': len(old[end:].encode())}, 'original_policy_static': 'PASS_IMPORT_SIZE_OPTIONS_ATTRIBUTES_BANNED', 'namespace_balance': True, 'exports_and_specs': {n: decl[n] for n in names}, 'not_run': ['exact newLean statement','kernel replay/axioms','fullsuite checksums and25pairedrounds','newC/object/performance'], 'coordinator': 'D only; noR Git,CI,web,agent ormessages'}
    if args.write:
        assert not (HERE/'Kernel.lean').exists() and not (HERE/'manifest.json').exists()
        (HERE/'Kernel.lean').write_bytes(data)
        (HERE/'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
        REPORT.write_text(json.dumps(report, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    else:
        assert (HERE/'Kernel.lean').read_bytes() == data
        assert json.loads((HERE/'manifest.json').read_text())['candidate_sha256'] == sha(data)
    print(json.dumps({'sha256': sha(data), 'bytes': len(data), 'static': 'PASS', 'exact_Lean': 'NOT_RUN', 'parent_inverse': True}))

if __name__ == '__main__': main()
