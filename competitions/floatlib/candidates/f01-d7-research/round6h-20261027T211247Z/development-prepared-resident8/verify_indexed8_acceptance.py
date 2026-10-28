"""Verify existing40621932164 originals and exact selected-root acceptance; no CI/build."""
from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
RUN = HERE.parent / 'ci-runs/40621932164'
sha = lambda b: hashlib.sha256(b).hexdigest()


def main():
    index_raw = (RUN / 'original-artifact-hashes.json').read_bytes()
    index = json.loads(index_raw)
    archive = RUN / index['directory']
    total = 0
    for name, entry in index['files'].items():
        path = (archive / name).resolve()
        assert path.is_relative_to(archive.resolve())
        data = path.read_bytes()
        assert len(data) == entry['bytes'] and sha(data) == entry['sha256'], name
        total += len(data)
    parent = archive / 'diagnostics/f01-d7-public-suite/public-suite'
    diag = parent / 'diagnostics/f01-r22-dev-indexed8-loop-probe2'
    source = (parent / 'inputs/f01-r22-dev-indexed8-loop-probe2/Kernel.lean').read_bytes()
    runtime = (HERE / 'KernelIndexed8Cost.lean').read_bytes()
    leaf = (HERE / 'Indexed8LoopEq-v2.lean.inc').read_bytes()
    assert source == runtime + b'\n' + leaf == (HERE / 'KernelIndexed8LoopProbe-v2.lean').read_bytes()
    assert sha(source) == '7981b04cfe8fa1bf68eec31bd8c5d8abdd6a2e50c1a46bd5f7456a9a9d4d3ba8'
    assert sha(runtime) == '8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
    assert sha(leaf) == 'ccee65d418fbe9cce253dada4962b7574fb06ab0e5d3146fe7f39ef72884e81b'
    audit_raw = (diag / 'helper-audit.json').read_bytes()
    audit = json.loads(audit_raw)
    manifest = json.loads((HERE / 'indexed8-loop-proof-v2-manifest.json').read_bytes())
    roots = manifest['primary_roots']
    assert audit['accepted'] and audit['kernel_replay'] and audit['exit_code'] == 0
    assert audit['kernel_sha256'] == sha(source) and audit['names'] == roots and audit['expected_count'] == 3
    allowed = {'propext', 'Classical.choice', 'Quot.sound'}
    assert set(audit['allowed_axioms']) == allowed
    assert set(audit['reports']) == set(roots)
    assert all(set(axioms) <= allowed for axioms in audit['reports'].values())
    axioms_raw = (diag / 'helper-axioms.raw').read_bytes()
    assert sha(axioms_raw) == audit['output_sha256']
    log_raw = (diag / 'replay.log').read_bytes()
    text = log_raw.decode()
    for exact in ('lake build VerifyFull exit=0', '[statement] ok',
                  '[kernel] Submission replays cleanly', '[kernel] VerifyFull replays cleanly',
                  '[helper-kernel] ok', '[helper-axioms] ok'):
        assert exact in text
    verdict = json.loads((diag / 'diagnostic-only-verdict.json').read_bytes())
    assert verdict['passed'] and verdict['stage'] == 'helper-axioms' and verdict['diagnostic_only']
    report = dict(run=40621932164, head_sha=index['artifact']['workflow_run']['head_sha'],
                  all_original_files=len(index['files']), all_original_bytes=total,
                  all_original_hashes_match=True, artifact_index_sha256=sha(index_raw),
                  source_sha256=sha(source), source_bytes=len(source), exact8e_prefix_plus_ccee_leaf=True,
                  runtime_sha256=sha(runtime), leaf_sha256=sha(leaf),
                  selected_roots=roots, typed_module_declarations=manifest['all_roots'],
                  statement='PASS', Submission_replay='PASS', VerifyFull_replay='PASS',
                  selected_helper_axioms='PASS_ALLOWED3', reports=audit['reports'],
                  helper_audit_sha256=sha(audit_raw), helper_axioms_sha256=sha(axioms_raw),
                  raw_replay_log_sha256=sha(log_raw),
                  scope='VERIFIED selected uget/wordLoop/within transport to exact original raw Nat8. Auxiliary wrappers typed and module-replayed but not separately selected for axiom audit. No full public BMM or performance acceptance.',
                  remaining=['Output/core congruence leaves notcompiled', 'Raw Nat8 producer/finish/read/Prefix/public closure'])
    (HERE / 'indexed8-loop-accepted-40621932164.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
