"""Current552 real A range widths and original compiler lowering, runner-only."""
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

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
EXPECTED = '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
FIELDS = ['dp_calls', 'positions', 'variable_queries', 'variable_terms', 'width1_3',
          'width4_7', 'width8_15', 'width16_31', 'width32_63', 'width64_127', 'width128_plus',
          'terms_width4_plus', 'terms_width8_plus', 'terms_width16_plus', 'fixed_single_terms', 'empty_ranges']
EXTRA = '''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_DP_COUNTS:[AtomicU64;16]=[const{AtomicU64::new(0)};16];
pub fn r26_dp_take()->[u64;16]{std::array::from_fn(|i|R26_DP_COUNTS[i].swap(0,Ordering::Relaxed))}
'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw) == EXPECTED
    source = raw.decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    old = fn(source, 'a_dp_pass')
    part = old.replace('    let cl = cost.len();', '    let cl = cost.len();let mut cnt=[0u64;16];cnt[0]=1;', 1)
    part = part.replace('            i -= 1;', '            i -= 1;cnt[1]+=1;', 1)
    marker = '                    let mut at = prev + 1;'
    assert part.count(marker) == 2
    count = '''                    if stop>prev {
                        let width=stop-prev;cnt[2]+=1;cnt[3]+=width as u64;
                        let bin=if width<4{4}else if width<8{5}else if width<16{6}else if width<32{7}else if width<64{8}else if width<128{9}else{10};
                        cnt[bin]+=1;if width>=4{cnt[11]+=width as u64;}if width>=8{cnt[12]+=width as u64;}if width>=16{cnt[13]+=width as u64;}
                    }else{cnt[15]+=1;}
'''
    part = part.replace(marker, count + marker)
    marker = '                    let l = stop.wrapping_sub(i) as u32;'
    assert part.count(marker) == 1
    part = part.replace(marker, '                    cnt[14]+=1;\n' + marker, 1)
    assert part.endswith('}\n')
    part = part[:-2] + '    let mut zc=0usize;while zc<16{R26_DP_COUNTS[zc].fetch_add(cnt[zc],Ordering::Relaxed);zc+=1;}\n}\n'
    source = source.replace(old, part, 1) + EXTRA
    importlib.import_module('r26-b-fix-shared-cache').spans(source)
    return source.encode()


def preflight(spec):
    assert spec.get('r26_b_a_compiler_counts') is True and spec.get('native_encoder') is False
    assert spec['native_only'] and all(e['control'] for e in spec['entries'])
    entry = next(e for e in spec['entries'] if e['name'] == 'public552')
    raw = (ROOT/entry['path']/'parse.rs').read_bytes()
    assert sha(raw) == entry['hashes']['parse.rs'] == EXPECTED
    observed = instrument(raw)
    return {'status': 'VERIFIED_CURRENT_A_RANGE_OBSERVER_STRUCTURE_ONLY', 'computed_utc': datetime.now(timezone.utc).isoformat(),
            'source_sha256': sha(raw), 'observer_sha256': sha(observed),
            'limits': ['No native coverage, machine-code or performance claim. Original O3/default-target compiler diagnostic differs from benchmark engine until flags/identity are verified.']}


def function_ir(text):
    match = re.search(r'(?m)^define[^\n]*a_dp_pass[^\n]*\{\n', text)
    assert match, 'a_dp_pass IR missing'
    end = text.index('\n}', match.end()) + 2
    return text[match.start():end]


def function_asm(text):
    starts = list(re.finditer(r'(?m)^\s*\.section\s+\.text\.[^\n]*a_dp_pass[^\n]*\n', text))
    assert len(starts) == 1, 'a_dp_pass assembly missing/ambiguous'
    start = starts[0].start()
    end = text.find('\n\t.section', starts[0].end())
    return text[start:end if end >= 0 else len(text)]


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
    preflight(spec)
    entry = next(e for e in spec['entries'] if e['name'] == 'public552')
    frozen = ROOT/entry['path']/'parse.rs'
    raw = frozen.read_bytes()
    build = Path(os.environ['RUNNER_TEMP'])/'r26-b-a-compiler'
    build.mkdir()
    out = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-a-compiler'
    out.mkdir(parents=True)
    compiler_dir = build/'lowering'
    compiler_dir.mkdir()
    compiler_cmd = ['rustc', '+nightly-2026-08-18', '--edition=2021', '--crate-type=lib', '--crate-name=r26_a_original',
                    '-O', '--emit=asm,llvm-ir', '--out-dir', str(compiler_dir), str(frozen)]
    c = subprocess.run(compiler_cmd, capture_output=True, text=True, timeout=240)
    (out/'original-lowering-compile.log').write_text(c.stdout+c.stderr)
    assert c.returncode == 0
    irfile, asmfile = compiler_dir/'r26_a_original.ll', compiler_dir/'r26_a_original.s'
    ir, asm = irfile.read_text(), asmfile.read_text()
    ir_body, asm_body = function_ir(ir), function_asm(asm)
    (out/'original-a-dp-pass.ll').write_text(ir_body+'\n')
    (out/'original-a-dp-pass.s').write_text(asm_body+'\n')
    (out/'original-all.ll').write_text(ir)
    (out/'original-all.s').write_text(asm)
    observed = build/'observed.rs'
    observed.write_bytes(instrument(raw))
    harness = importlib.import_module('research-round13-counts').HARNESS.replace('FROZEN', str(frozen)).replace('OBSERVED', str(observed)).replace('observed::r13_take()', 'observed::r26_dp_take()').replace('R13_COUNT', 'R26_DP_RANGE')
    driver = build/'check.rs'
    driver.write_text(harness)
    binary = build/'check'
    cc = subprocess.run(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], capture_output=True, text=True, timeout=240)
    (out/'observer-compile.log').write_text(cc.stdout+cc.stderr)
    assert cc.returncode == 0
    corpus = Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    rr = subprocess.run([str(binary), str(corpus)], capture_output=True, text=True, timeout=480)
    (out/'run.log').write_text(rr.stdout+rr.stderr)
    assert rr.returncode == 0
    rows = []
    for line in rr.stdout.splitlines():
        if line.startswith('R26_DP_RANGE '):
            _, name, size, *values = line.split()
            assert len(values) == 16
            data = (corpus/name).read_bytes()
            assert len(data) == int(size)
            rows.append({'file': name, 'raw_bytes': len(data), 'input_sha256': sha(data), 'counts': dict(zip(FIELDS, map(int, values)))})
    assert len(rows) == 28 and sum(r['raw_bytes'] for r in rows) == 15930000
    totals = {f: sum(r['counts'][f] for r in rows) for f in FIELDS}
    assert sum(totals[f] for f in FIELDS[4:11]) == totals['variable_queries']
    result = {'status': 'VERIFIED_ORIGINAL_CURRENT_A_RANGE_TOKEN_DECODE_PARITY_AND_COMPILER_ARTIFACTS',
              'run_id': os.environ['GITHUB_RUN_ID'], 'git_sha': os.environ['GITHUB_SHA'], 'source_hashes': entry['hashes'],
              'observer_sha256': sha(observed.read_bytes()), 'harness_sha256': sha(driver.read_bytes()),
              'compiler_command': compiler_cmd, 'compiler_version': subprocess.run(['rustc', '+nightly-2026-08-18', '-vV'], capture_output=True, text=True, check=True).stdout,
              'totals': totals, 'rows': rows,
              'compiler_hints_not_conclusions': {'IR_vector_u32_mentions': len(re.findall(r'<\d+ x i32>', ir_body)),
                                                'IR_vector_reduce_umin': len(re.findall(r'@llvm\.vector\.reduce\.umin', ir_body)),
                                                'ASM_vector_register_mentions': len(re.findall(r'%[xy]mm\d+', asm_body))},
              'artifact_hashes': {p.name: sha(p.read_bytes()) for p in out.iterdir() if p.is_file()},
              'limits': ['Original unmodified source library O3/default target lowering is diagnostic, not a claim of benchmark-engine machine-code identity.',
                         'Vector registers may belong to initialization or unrelated blocks; inspect exact reduction loops before claiming automatic vectorization.',
                         'Width counts are real original DP calls, no added query state/price/candidate or changed original writes; all28tokens/decode match.',
                         'Counts and compiler lowering do not establish whole encoder speed, current share, proof or stable target success.']}
    (out/'receipt.json').write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({'status': result['status'], 'totals': totals, 'hints': result['compiler_hints_not_conclusions']}))


if __name__ == '__main__':
    main()
