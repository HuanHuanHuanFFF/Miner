"""Actual online A9 emitter and pinned original-encoder work; untimed only."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import sys
import zlib

ROOT = Path(__file__).resolve().parents[1]
BUILD = importlib.import_module('r26-a-build-distance12')
HELP = importlib.import_module('research-round25-tiny-encoder')
RUN = importlib.import_module('r26-a-replay')
NAME = BUILD.NAME
RUST = 'a20208d62cdb8c487a2041bc0d41445081caeaa0aefb1d8ddab620c6e4dd8ab3'
FIELDS = ['calls', 'accepted_known', 'accepted_new', 'rejected_matches', 'rejected_bytes', 'ever_used_mask']


def sha(raw): return hashlib.sha256(raw).hexdigest()
def dump(path, value): path.write_bytes((json.dumps(value, indent=2) + '\n').encode())
def once(text, old, new): return HELP.once(text, old, new)


def instrument_parser(raw):
    assert sha(raw) == RUST
    helper = BUILD.HELPER
    altered = once(helper, '    if et_take(l, 4, used, d) {', '    r26_d12_hit(0, 1);\n    if et_take(l, 4, used, d) {\n        let known = ((used >> (et_dcode(d) % 32)) & 1) != 0;\n        r26_d12_hit(if known { 1 } else { 2 }, 1);')
    altered = once(altered, '        (r.0, r.1, mask)', '        R26_D12_COUNTS[5].fetch_or(mask as u64, Ordering::Relaxed);\n        (r.0, r.1, mask)')
    altered = once(altered, '        let end = p + l;', '        r26_d12_hit(3, 1); r26_d12_hit(4, l as u64);\n        let end = p + l;')
    text = once(raw.decode(), helper, altered)
    text += '''
use std::sync::atomic::{AtomicU64, Ordering};
static R26_D12_COUNTS: [AtomicU64; 6] = [const { AtomicU64::new(0) }; 6];
fn r26_d12_hit(i: usize, n: u64) { R26_D12_COUNTS[i].fetch_add(n, Ordering::Relaxed); }
pub fn r26_d12_take() -> [u64; 6] { std::array::from_fn(|i| R26_D12_COUNTS[i].swap(0, Ordering::Relaxed)) }
'''
    return text.encode()


def preflight(spec):
    assert spec['r26_mode'] == 'native' and spec['native_encoder'] is True
    by = {e['name']: e for e in spec['entries']}
    for name in ['strong', 'combo', 'public595', 'public514', NAME]:
        e = by[name]
        for file, expected in e['hashes'].items(): assert sha((ROOT / e['path'] / file).read_bytes()) == expected
    assert by[NAME]['hashes']['parse.rs'] == RUST and by['strong']['hashes']['parse.rs'] == BUILD.RUST
    raw = (ROOT / by[NAME]['path'] / 'parse.rs').read_bytes(); assert BUILD.generate()[0] == raw
    observed = instrument_parser(raw)
    return {'status': 'VERIFIED_ONLINE_SOURCE_REVERSAL_AND_OBSERVER_GENERATION_NOT_NATIVE',
            'candidate_rust_sha256': RUST, 'parser_observer_sha256': sha(observed),
            'strong_rust_sha256': BUILD.RUST, 'codec_sha256': HELP.CODEC_SHA, 'token_sha256': HELP.TOKEN_SHA}


def run():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    from round4 import validate
    spec = validate(os.environ['ROUND4_SPEC']); checked = preflight(spec); by = {e['name']: e for e in spec['entries']}
    upstream = Path(os.environ['DEFLATE_ROOT']); codec = upstream / 'validator/measure/src/deflate.rs'; token = codec.with_name('token.rs')
    codec_raw = codec.read_bytes(); token_raw = token.read_bytes()
    assert sha(codec_raw) == HELP.CODEC_SHA and sha(token_raw) == HELP.TOKEN_SHA
    build = Path(os.environ['RUNNER_TEMP']) / 'r26-a-distance12-build'; build.mkdir()
    out = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r26-a-distance12'; out.mkdir(parents=True)
    spool = out / 'tokens-and-output'; spool.mkdir()
    codec_observer = build / 'codec-observer.rs'; codec_observer_raw = HELP.instrument(codec_raw); codec_observer.write_bytes(codec_observer_raw)
    (out / 'codec-observer.rs').write_bytes(codec_observer_raw)
    parser_observer = build / 'parser-observer.rs'; parser_raw = instrument_parser((ROOT / by[NAME]['path'] / 'parse.rs').read_bytes()); parser_observer.write_bytes(parser_raw)
    (out / 'parser-observer.rs').write_bytes(parser_raw)
    aliases = [('combo', 'combo'), ('strong', 'strong'), ('distance12', NAME)]
    modules = '\n'.join('#[path=' + json.dumps(str(ROOT / by[name]['path'] / 'parse.rs')) + '] mod parser_' + label + ';' for label, name in aliases)
    modules += '\n#[path=' + json.dumps(str(parser_observer)) + '] mod parsed_observer;'
    cases = ','.join('(' + json.dumps(label) + ',parser_' + label + '::parse)' for label, _ in aliases)
    harness = HELP.HARNESS.replace('MODULES', modules).replace('CASES', cases)
    before = 'let ts=tokens(&s,f);assert!(decode(&s,&ts));'
    after = before + '''
if label=="distance12" { let other=tokens(&s,parsed_observer::parse);assert_eq!(ts,other);assert!(decode(&s,&other));let events=parsed_observer::r26_d12_take();print!("R26_D12_COUNT {}",name);for x in events{print!(" {}",x);}println!();}
'''
    harness = once(harness, before, after)
    harness = harness.replace('TOKEN', json.dumps(str(token))).replace('CODEC', json.dumps(str(codec))).replace('OBSERVER', json.dumps(str(codec_observer)))
    driver = build / 'main.rs'; driver.write_text(harness); (out / 'harness.rs').write_text(harness)
    result = {'status': 'STARTED_ONLINE_DISTANCE12_ORIGINAL_ENCODER_WORK', 'run_id': os.environ['GITHUB_RUN_ID'],
              'git_sha': os.environ['GITHUB_SHA'], 'batch': os.environ['ROUND4_SPEC'], **checked,
              'codec_observer_sha256': sha(codec_observer_raw), 'harness_sha256': sha(harness.encode()),
              'scope': 'Actual online parse/fold outputs, original codec and byte-identical observer. Logical work counts are not elapsed costs or private guarantees.'}
    result['status'] = 'STARTED_ONLINE_DISTANCE12_ORIGINAL_ENCODER_WORK'; report = out / 'receipt.json'; dump(report, result)
    try:
        binary = build / 'check'
        RUN.captured(['rustc', '+nightly-2026-08-18', '--edition=2021', '-O', '-C', 'overflow-checks=yes', str(driver), '-o', str(binary)], out / 'compile.log', 180)
        corpus = upstream / 'data/benchmark/corpus-stage1'
        log = RUN.captured([str(binary), str(corpus), str(spool)], out / 'run.log', 180)
        native_path = out.parent / 'r13-encoder/encoder.json'; native = json.loads(native_path.read_bytes())
        expected = {(r['candidate'], r['file']): r for r in native['rows']}
        traces = {}; events = {}; current = None
        for line in log.splitlines():
            if line.startswith('R25_CONTEXT '):
                _, label, file = line.split(); current = (label, file); assert current not in traces
                traces[current] = {'trees': [], 'blocks': [], 'choices': []}
            elif line.startswith('R25_TREE '):
                _, n, bits, arrays = line.split(' ', 3); freq, lengths, work = HELP.read_arrays(arrays)
                assert len(freq) == len(lengths) == int(n) and len(work) == len(HELP.TREE_FIELDS)
                traces[current]['trees'].append({'alphabet_size': int(n), 'max_bits': int(bits), 'frequency': freq,
                                                'code_lengths': lengths, 'work': dict(zip(HELP.TREE_FIELDS, work))})
            elif line.startswith('R25_BLOCK '):
                values = list(map(int, line.split()[1:])); assert len(values) == 8
                traces[current]['blocks'].append(dict(zip(['items', 'raw_bytes', 'hlit', 'hdist', 'hclen', 'dynamic_bits', 'fixed_bits', 'stored_bits'], values)))
            elif line.startswith('R25_CHOICE '): traces[current]['choices'].append(line.split()[1])
            elif line.startswith('R26_D12_COUNT '):
                _, file, *values = line.split(); assert len(values) == len(FIELDS)
                events[file] = dict(zip(FIELDS, map(int, values)))
        rows = []
        for label, name in aliases:
            assert native['source_hashes'][name] == by[name]['hashes']
            for file in HELP.FILES:
                data = (corpus / file).read_bytes(); raw = (spool / (label + '-' + file + '.tokens')).read_bytes()
                encoded = (spool / (label + '-' + file + '.deflate')).read_bytes(); measured = (spool / (label + '-' + file + '.observed.deflate')).read_bytes()
                prior = expected[name, file]
                assert sha(data) == prior['input_sha256'] and sha(raw) == prior['tokens_sha256']
                assert encoded == measured and sha(encoded) == prior['output_sha256'] and zlib.decompress(encoded, -15) == data
                summary = HELP.token_summary(raw, codec_raw.decode()); trace = traces[label, file]
                assert summary['produced_bytes'] == len(data) and summary['tokens'] == prior['tokens']
                assert len(trace['trees']) == 3 and len(trace['blocks']) == len(trace['choices']) == 1
                assert trace['trees'][0]['frequency'] == summary['litlen_frequency_including_eob']
                assert trace['trees'][1]['frequency'] == summary['distance_frequency']
                rows.append({'label': label, 'candidate': name, 'file': file, 'input_sha256': sha(data), 'tokens_sha256': sha(raw),
                             'output_sha256': sha(encoded), 'output_bytes': len(encoded), 'tokens': prior['tokens'], 'token_summary': summary, **trace})
        assert len(events) == 2
        for file, e in events.items():
            assert e['calls'] == e['accepted_known'] + e['accepted_new'] + e['rejected_matches']
            assert e['ever_used_mask'].bit_count() == e['accepted_new']
            final = next(r for r in rows if r['label'] == 'distance12' and r['file'] == file)
            if file == 'tiny-config.json.txt':
                assert e['calls'] > 0
                freq = final['token_summary']['distance_frequency']
                assert all(n == 0 or e['ever_used_mask'] & (1 << code) for code, n in enumerate(freq))
            else:
                assert e['calls'] == 0
                before = next(r for r in rows if r['label'] == 'strong' and r['file'] == file)
                assert final['tokens_sha256'] == before['tokens_sha256'] and final['output_sha256'] == before['output_sha256']
        assert codec.read_bytes() == codec_raw and token.read_bytes() == token_raw
        result.update(status='VERIFIED_ONLINE_NATIVE_IDENTITIES_EMITTER_COUNTS_AND_ORIGINAL_ENCODER_WORK',
                      native_encoder_sha256=sha(native_path.read_bytes()), rows=rows, emitter_events=events)
    except Exception as exc:
        result.update(status='FAILED_OR_INCOMPLETE_ONLINE_DISTANCE12_WORK', error_type=type(exc).__name__, error=str(exc)); dump(report, result); raise
    dump(report, result)
    print(json.dumps({'status': result['status'], 'rows': [{'label': r['label'], 'file': r['file'], 'bytes': r['output_bytes'], 'symbols': [t['work']['live_symbols'] for t in r['trees']]} for r in rows], 'emitter_events': events}, indent=2))


if __name__ == '__main__': run()
