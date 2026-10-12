"""Exact official candidate shim/flags: checked A increment versus proven-safe wrapping."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib
import json
import os
import re
import subprocess
import sys
import tomllib

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
EXPECTED = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
RELEASE = {'opt-level': 3, 'lto': 'fat', 'codegen-units': 1, 'debug-assertions': False,
           'overflow-checks': True, 'panic': 'unwind'}


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def variants(raw):
    assert sha(raw) == EXPECTED
    text = raw.decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    old = fn(text, 'a_dp_pass')
    loop = '''                    while at <= stop {
                        let c = (cost[at].wrapping_add(lc[(l % 512) as usize]).wrapping_add(base) << 9) | l;
                        mbest = if c < mbest { c } else { mbest };
                        at += 1;
                        l = l.wrapping_add(1);
                    }'''
    assert old.count(loop) == 2
    new = old.replace(loop, loop.replace('at += 1;', 'at = at.wrapping_add(1);'))
    changed = text.replace(old, new, 1).encode()
    assert changed.replace(b'at = at.wrapping_add(1);', b'at += 1;') == raw
    importlib.import_module('r26-b-fix-shared-cache').spans(changed.decode())
    return {'original_checked': raw, 'safe_wrapping_increment': changed}


def preflight(spec):
    assert spec.get('r26_b_a_compiler_counts') is True and spec.get('native_encoder') is False
    assert spec.get('r26_b_a_compiler_module') == 'r26-b-a-checked-lowering'
    assert spec['native_only'] and all(e['control'] for e in spec['entries'])
    entry = next(e for e in spec['entries'] if e['name'] == 'public552')
    raw = (ROOT/entry['path']/'parse.rs').read_bytes()
    assert sha(raw) == entry['hashes']['parse.rs']
    forms = variants(raw)
    template = ROOT/'evidence/round26/route-b/b25-official-template'
    cargo = tomllib.loads((template/'Cargo.toml').read_text())
    assert cargo['profile']['release'] == RELEASE
    result = {'status': 'VERIFIED_TWO_ISOLATED_SAFE_INCREMENT_SOURCE_DIAGNOSTICS_ONLY',
              'computed_utc': datetime.now(timezone.utc).isoformat(),
              'source_variants_sha256': {k: sha(v) for k, v in forms.items()},
              'release_settings': RELEASE,
              'official_local_template_canonical_sha256': {f: sha((template/f).read_bytes().replace(b'\r\n', b'\n')) for f in ('Cargo.toml', 'lib.rs')},
              'increment_proof': 'Both changed loops are dominated by stop<cl and execute only at<=stop. Therefore at<=stop<cl<=usize::MAX implies at<usize::MAX; at+1 is in range and equals wrapping_add(1). Zero-width loops execute no increment. Earlier prev+1, other increments and every packed term unchanged.',
              'limits': ['No native compile or Rust/Lean equivalence/performance established yet; no candidate files created.']}
    return result


def ir_functions(text):
    starts = list(re.finditer(r'(?m)^define[^\n]*a_dp_pass[^\n]*\{\n', text))
    assert starts, 'a_dp_pass IR missing'
    return [text[m.start():text.index('\n}', m.end())+2] for m in starts]


def asm_functions(text):
    starts = list(re.finditer(r'(?m)^\s*\.section\s+\.text\.[^\n]*a_dp_pass[^\n]*\n', text))
    assert starts, 'a_dp_pass assembly missing'
    result = []
    for m in starts:
        end = text.find('\n\t.section', m.end())
        result.append(text[m.start():end if end >= 0 else len(text)])
    return result


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--check', type=Path)
    ap.add_argument('--output', type=Path)
    a = ap.parse_args()
    if a.check:
        result = preflight(json.loads(a.check.read_bytes()))
        if a.output:
            assert not a.output.exists()
            a.output.write_text(json.dumps(result, indent=2)+'\n')
        print(json.dumps(result))
        return
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    spec = importlib.import_module('round4').validate(os.environ['ROUND4_SPEC'])
    check = preflight(spec)
    entry = next(e for e in spec['entries'] if e['name'] == 'public552')
    raw = (ROOT/entry['path']/'parse.rs').read_bytes()
    upstream = Path(os.environ['DEFLATE_ROOT'])/'validator/measure/candidate'
    cargo = (upstream/'Cargo.toml').read_bytes()
    shim = (upstream/'lib.rs').read_bytes()
    assert tomllib.loads(cargo.decode())['profile']['release'] == RELEASE
    assert {f: sha(v.replace(b'\r\n', b'\n')) for f, v in [('Cargo.toml', cargo), ('lib.rs', shim)]} == check['official_local_template_canonical_sha256']
    build = Path(os.environ['RUNNER_TEMP'])/'r26-b-a-checked-lowering'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-a-checked-lowering'
    out.mkdir(parents=True)
    (out/'official-shim.rs').write_bytes(shim)
    (out/'official-candidate-Cargo.toml').write_bytes(cargo)
    result = {'status': 'CHECKED_LOWERING_STARTED_NOT_A_RESULT', 'run_id': os.environ['GITHUB_RUN_ID'],
              'git_sha': os.environ['GITHUB_SHA'], 'source_hashes': entry['hashes'], 'preflight': check,
              'official_template_raw_hashes': {'Cargo.toml': sha(cargo), 'lib.rs': sha(shim)}, 'variants': {}}
    (out/'execution-start.json').write_text(json.dumps(result, indent=2)+'\n')
    for label, rust in variants(raw).items():
        folder = build/label
        folder.mkdir()
        (folder/'parse.rs').write_bytes(rust)
        (folder/'lib.rs').write_bytes(shim)
        assembly = folder/'lowering'
        assembly.mkdir()
        command = ['rustc', '+nightly-2026-08-18', '--edition=2021', '--crate-type=cdylib', '--crate-name=candidate',
                   '-O', '-C', 'lto=fat', '-C', 'codegen-units=1', '-C', 'debug-assertions=no',
                   '-C', 'overflow-checks=yes', '-C', 'panic=unwind', '--emit=asm,llvm-ir',
                   '--out-dir', str(assembly), str(folder/'lib.rs')]
        compiled = subprocess.run(command, capture_output=True, text=True, timeout=300)
        (out/(label+'-compile.log')).write_text(compiled.stdout+compiled.stderr)
        assert compiled.returncode == 0
        irpath, asmpath = assembly/'candidate.ll', assembly/'candidate.s'
        ir, asm = irpath.read_text(), asmpath.read_text()
        bodies, asm_bodies = ir_functions(ir), asm_functions(asm)
        body, asm_body = '\n\n'.join(bodies), '\n\n'.join(asm_bodies)
        (out/(label+'-a-dp-pass.ll')).write_text(body+'\n')
        (out/(label+'-a-dp-pass.s')).write_text(asm_body+'\n')
        (out/(label+'-parse.rs')).write_bytes(rust)
        result['variants'][label] = {'rust_sha256': sha(rust), 'compiler_command': command,
                                     'IR_function_bodies': len(bodies), 'ASM_function_bodies': len(asm_bodies),
                                     'IR_vector_reduce_umin': len(re.findall(r'@llvm\.vector\.reduce\.umin', body)),
                                     'IR_unsigned_add_overflow_calls': len(re.findall(r'call.*@llvm\.uadd\.with\.overflow', body)),
                                     'IR_vector_u32_mentions': len(re.findall(r'<\d+ x i32>', body)),
                                     'ASM_vector_register_mentions': len(re.findall(r'%[xy]mm\d+', asm_body)),
                                     'raw_full_IR_sha256': sha(irpath.read_bytes()), 'raw_full_ASM_sha256': sha(asmpath.read_bytes()),
                                     'body_IR_sha256': sha((out/(label+'-a-dp-pass.ll')).read_bytes()),
                                     'body_ASM_sha256': sha((out/(label+'-a-dp-pass.s')).read_bytes())}
    result['status'] = 'VERIFIED_OFFICIAL_CANDIDATE_FLAGS_SHIM_COMPILE_DIAGNOSTIC_ONLY'
    result['compiler_version'] = subprocess.run(['rustc', '+nightly-2026-08-18', '-vV'], capture_output=True, text=True, check=True).stdout
    result['limits'] = ['Official copied shim and release settings used for both; no official repository/flags changed. Exact Cargo artifact/library identity not claimed.',
                        'Whole-function vector/overflow counts need exact reduction-loop inspection, not automatic performance or root-cause claims.',
                        'Only two dominated at increments differ; no derived parse execution/encoder/gate/performance/frozen confirmation yet.',
                        'Full-library IR/assembly hashes recorded; relevant function bodies and exact generated source retained.']
    (out/'receipt.json').write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({'status': result['status'], 'variants': result['variants']}))


if __name__ == '__main__':
    main()
