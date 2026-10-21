"""Read-only audit of same-endpoint plan selection against a rebound public299 profile.

Prints JSON to stdout; creates no files and invokes no compiler/network/CI.
Exit 0: no mechanism stop condition (still only public performance review).
Exit 1: missing/inconsistent evidence. Exit 2: boundary/size/no-gain stop.
"""
from __future__ import annotations
import argparse
import hashlib
import json
import re
import statistics
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_BASE = ROOT / 'evidence/round4/37535056448/gate'
HASH_RE = re.compile(r'[0-9a-f]{64}')
NAME_RE = re.compile(r'[a-zA-Z0-9_-]+')


class EvidenceError(ValueError):
    pass


def require(condition, message):
    if not condition:
        raise EvidenceError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def sha_value(value, label):
    require(isinstance(value, str) and HASH_RE.fullmatch(value), f'{label}: invalid SHA256')
    return value


class Audit:
    def __init__(self):
        self.receipts = {}

    def read(self, path, jsonl=False):
        path = Path(path).resolve()
        data = path.read_bytes()
        self.receipts[str(path)] = digest(data)
        text = data.decode('utf-8-sig')
        return ([json.loads(line) for line in text.splitlines() if line.strip()]
                if jsonl else json.loads(text))

    def entry(self, gate, name):
        state = self.read(gate / 'state.json')
        entries = [e for e in state['spec']['entries'] if e['name'] == name]
        require(len(entries) == 1, f'{gate}: expected one spec entry for {name}')
        entry = entries[0]
        for key in ('parse.rs', 'Parse.lean'):
            sha_value(entry['hashes'][key], f'{name}/{key}')
        source = (ROOT / entry['path'] / 'parse.rs').resolve()
        require(source.is_relative_to(ROOT), f'{name}: source path escapes repository')
        data = source.read_bytes()
        self.receipts[str(source)] = digest(data)
        require(digest(data) == entry['hashes']['parse.rs'], f'{name}: local source differs from frozen run')
        return entry

    def native(self, gate, name, entry):
        paths = sorted(gate.glob(f'round*-{name}.jsonl'), key=lambda p: int(p.name.split('-', 1)[0][5:]))
        require(paths and paths[0].name == f'round1-{name}.jsonl', f'{gate}: round1-{name} absent')
        runs = []
        for path in paths:
            records = self.read(path, True)
            metas = [r for r in records if r.get('kind') == 'meta']
            require(len(metas) == 1, f'{path}: expected one meta record')
            meta = metas[0]
            require(meta['corpus'] == 'corpus-stage1', f'{path}: wrong corpus')
            require(meta['methods'][name]['source_sha256'] == entry['hashes']['parse.rs'], f'{path}: source hash mismatch')
            rows = [r for r in records if r.get('kind') == 'file']
            files = {r['file']: r for r in rows}
            require(len(files) == len(rows) == 28, f'{path}: stage1 file coverage/duplicate mismatch')
            require(sum(r['raw_bytes'] for r in rows) == 15930000, f'{path}: stage1 input byte total mismatch')
            ratios = []
            for file, row in files.items():
                sha_value(row['sha256'], f'{path}/{file}/input')
                times = {}
                for method in (name, 'incumbent'):
                    result = row['methods'][method]
                    require(result['deterministic'] is True and not result['errors'], f'{path}/{file}/{method}: runtime/determinism failure')
                    for field in ('tokens_sha256', 'output_sha256'):
                        sha_value(result[field], f'{path}/{file}/{method}/{field}')
                    reps = [r for r in result['reps'] if r['phase'] == 'measured']
                    require(len(reps) == meta['measured_rounds'] == 11, f'{path}/{file}: repetition coverage mismatch')
                    require(all(r['total_s'] > 0 for r in reps), f'{path}/{file}: invalid time')
                    times[method] = statistics.median(r['total_s'] for r in reps)
                ratios.append(times[name] / times['incumbent'])
            run = {'round': int(path.name.split('-', 1)[0][5:]), 'meta': meta,
                   'files': files, 'time_axis': statistics.mean(ratios)}
            if runs:
                reference = runs[0]
                require(files.keys() == reference['files'].keys(), f'{path}: repeated file coverage mismatch')
                for file, row in files.items():
                    before = reference['files'][file]
                    require((row['sha256'], row['raw_bytes']) == (before['sha256'], before['raw_bytes']), f'{path}/{file}: repeated input drift')
                    for method in (name, 'incumbent'):
                        for field in ('tokens', 'tokens_sha256', 'output_bytes', 'output_sha256'):
                            require(row['methods'][method][field] == before['methods'][method][field], f'{path}/{file}/{method}: repeated {field} drift')
            runs.append(run)
        return runs

    def profile(self, gate, name, entry, native):
        summary = self.read(gate / 'token-profile.json')
        records_path = gate / 'token-profile.jsonl'
        records = self.read(records_path, True)
        require(summary['status'] == 'DIAGNOSTIC_OK' and not summary['failures'], f'{gate}: profile diagnostic failed')
        require(summary['records_sha256'] == self.receipts[str(records_path.resolve())], f'{gate}: profile JSONL hash mismatch')
        require(summary['block_tokens'] == 16384, f'{gate}: wrong token-block size')
        require(name in summary['candidate_sources'], f'{gate}: no profile for {name}')
        require(summary['candidate_sources'][name]['hashes'] == entry['hashes'], f'{name}: profile source/proof binding mismatch')
        provenance = [r for r in records if r['kind'] == 'provenance']
        require(len(provenance) == 1, f'{gate}: profile provenance absent/duplicate')
        for key in ('official_revision', 'block_tokens', 'inputs'):
            require(provenance[0][key] == summary[key], f'{gate}: profile {key} mismatch')
        selected = [r for r in records if r.get('candidate') == name and r['kind'] == 'file']
        files = {r['file']: r for r in selected}
        native_files = native[0]['files']
        require(len(selected) == len(files) == 28 and files.keys() == native_files.keys() == summary['inputs'].keys(), f'{name}: profile/native/input coverage mismatch')
        aggregates = {r['file']: r for r in summary['files'] if r.get('candidate') == name}
        require(files == aggregates, f'{name}: summary/file-record mismatch')
        all_blocks = [r for r in records if r.get('candidate') == name and r['kind'] == 'block']
        require(all(r['file'] in files for r in all_blocks), f'{name}: unexpected block file')
        for file, profile in files.items():
            row = native_files[file]; result = row['methods'][name]; pin = summary['inputs'][file]
            require(profile['source_sha256'] == entry['hashes']['parse.rs'] and profile['proof_sha256'] == entry['hashes']['Parse.lean'], f'{name}/{file}: source/proof mismatch')
            require(profile['input_sha256'] == row['sha256'] == pin['sha256'], f'{name}/{file}: input hash mismatch')
            require(profile['raw_bytes'] == row['raw_bytes'] == pin['bytes'], f'{name}/{file}: input length mismatch')
            require(profile['tokens_sha256'] == result['tokens_sha256'] and profile['total_token_count'] == result['tokens'], f'{name}/{file}: token hash/count mismatch')
            require(profile['decode_checked'] is True, f'{name}/{file}: independent decode failed')
            blocks = sorted((b for b in all_blocks if b['file'] == file), key=lambda b: b['block_index'])
            require(len(blocks) == profile['block_count'], f'{name}/{file}: block-count mismatch')
            token_end = raw_end = 0
            for index, block in enumerate(blocks):
                require(block['source_sha256'] == entry['hashes']['parse.rs'] and block['proof_sha256'] == entry['hashes']['Parse.lean'], f'{name}/{file}: block source/proof mismatch')
                require(block['block_index'] == index, f'{name}/{file}: block index duplicate/gap')
                require(block['token_start'] == token_end and block['raw_start'] == raw_end, f'{name}/{file}: block discontinuity')
                token_end, raw_end = block['token_end'], block['raw_end']
                require(block['token_count'] == token_end - block['token_start'], f'{name}/{file}: token span mismatch')
                require(0 < block['token_count'] <= 16384, f'{name}/{file}: invalid nonempty block size')
                require(index == len(blocks) - 1 or block['token_count'] == 16384, f'{name}/{file}: incomplete nonfinal block')
                require(raw_end - block['raw_start'] == block['literal_bytes'] + block['match_bytes'], f'{name}/{file}: byte coverage mismatch')
                lf, df = block['litlen_frequencies'], block['distance_frequencies']
                require(len(lf) == 288 and len(df) == 30 and all(isinstance(x, int) and x >= 0 for x in lf + df), f'{name}/{file}: malformed histogram')
                require(lf[256] == block['end_of_block_frequency'] == 1, f'{name}/{file}: EOB mismatch')
                require(sum(lf) == block['token_count'] + 1 and sum(df) == sum(lf[257:286]) == block['match_tokens'], f'{name}/{file}: histogram token totals mismatch')
                require(sum(lf[:256]) == block['literal_bytes'], f'{name}/{file}: literal histogram mismatch')
            require(token_end == profile['total_token_count'] and raw_end == profile['raw_bytes'], f'{name}/{file}: incomplete stream')
            profile = dict(profile)
            profile['raw_ends'] = [b['raw_end'] for b in blocks]
            profile['block_token_counts'] = [b['token_count'] for b in blocks]
            files[file] = profile
        return summary, files


def analyze(gate, candidate='r5-opt-a-sameend299', baseline_gate=DEFAULT_BASE,
            baseline_candidate='r4-alt299-tinydepth32'):
    gate, baseline_gate = Path(gate).resolve(), Path(baseline_gate).resolve()
    for name in (candidate, baseline_candidate):
        require(NAME_RE.fullmatch(name), 'invalid candidate identifier')
    audit = Audit()
    control = 'public299'
    entry = audit.entry(gate, candidate)
    base_entry = audit.entry(gate, control)
    old_entry = audit.entry(baseline_gate, baseline_candidate)
    old_control_entry = audit.entry(baseline_gate, control)
    require(base_entry['hashes'] == old_control_entry['hashes'], 'public299 source/proof drift between runs')
    new = audit.native(gate, candidate, entry)
    base = audit.native(gate, control, base_entry)
    old = audit.native(baseline_gate, baseline_candidate, old_entry)
    old_base = audit.native(baseline_gate, control, old_control_entry)
    new_summary, new_profile = audit.profile(gate, candidate, entry, new)
    old_summary, old_profile = audit.profile(baseline_gate, baseline_candidate, old_entry, old)
    for key in ('official_revision', 'block_tokens'):
        require(new_summary[key] == old_summary[key], f'profile {key} drift between runs')
    for key in ('deflate.rs', 'token.rs', 'record.rs'):
        require(new_summary['official_source'][key]['sha256'] == old_summary['official_source'][key]['sha256'], f'official {key} hash drift')
    engine = base[0]['meta']['benchmark_provenance']['engine_sha256']
    for runs in (new, base, old, old_base):
        for run in runs:
            require(run['meta']['benchmark_provenance']['engine_sha256'] == engine, 'official benchmark engine hash drift')
    require({r['round'] for r in new} == {r['round'] for r in base}, 'new/control repetition-block mismatch')
    rows = []
    for file in sorted(base[0]['files']):
        current = base[0]['files'][file]; b = current['methods'][control]
        history = old[0]['files'][file]; h = history['methods'][baseline_candidate]
        historical_control = old_base[0]['files'][file]
        for record, method in ((history, h), (historical_control, historical_control['methods'][control])):
            require((record['sha256'], record['raw_bytes']) == (current['sha256'], current['raw_bytes']), f'{file}: historical input mismatch')
            for key in ('tokens', 'tokens_sha256', 'output_bytes', 'output_sha256'):
                require(method[key] == b[key], f'{file}: historical baseline {key} not bound to current public299')
        r = new[0]['files'][file]; c = r['methods'][candidate]
        require((r['sha256'], r['raw_bytes']) == (current['sha256'], current['raw_bytes']), f'{file}: new/control input mismatch')
        if c['tokens_sha256'] == b['tokens_sha256']:
            require((c['output_bytes'], c['output_sha256']) == (b['output_bytes'], b['output_sha256']), f'{file}: equal tokens have differing official output')
        bp, cp = old_profile[file], new_profile[file]
        rows.append({'file': file, 'raw_bytes': current['raw_bytes'], 'input_sha256': current['sha256'],
                     'baseline_tokens_sha256': b['tokens_sha256'], 'candidate_tokens_sha256': c['tokens_sha256'],
                     'baseline_output_sha256': b['output_sha256'], 'candidate_output_sha256': c['output_sha256'],
                     'baseline_blocks': bp['block_count'], 'candidate_blocks': cp['block_count'],
                     'block_count_equal': bp['block_count'] == cp['block_count'],
                     'baseline_raw_ends': bp['raw_ends'], 'candidate_raw_ends': cp['raw_ends'],
                     'raw_ends_equal': bp['raw_ends'] == cp['raw_ends'],
                     'baseline_block_token_counts': bp['block_token_counts'], 'candidate_block_token_counts': cp['block_token_counts'],
                     'baseline_bytes': b['output_bytes'], 'candidate_bytes': c['output_bytes'],
                     'bytes_delta': c['output_bytes'] - b['output_bytes'], 'tokens_delta': c['tokens'] - b['tokens'],
                     'tokens_equal': c['tokens_sha256'] == b['tokens_sha256'],
                     'output_equal': c['output_sha256'] == b['output_sha256'],
                     'size_axis_delta_pp': 100 * (c['output_bytes'] - b['output_bytes']) / current['raw_bytes'] / 28})
    boundary = [r['file'] for r in rows if not r['block_count_equal'] or not r['raw_ends_equal']]
    larger = [r['file'] for r in rows if r['bytes_delta'] > 0]
    gain = sum(r['size_axis_delta_pp'] for r in rows)
    stops = []
    if boundary: stops.append('encoder block count or raw endpoints moved')
    if larger: stops.append('at least one file has more encoded bytes')
    if gain >= 0: stops.append('no improvement in the public size axis')
    bt = statistics.mean(r['time_axis'] for r in base)
    ct = statistics.mean(r['time_axis'] for r in new)
    baseline_size = statistics.mean(100 * r['baseline_bytes'] / r['raw_bytes'] for r in rows)
    candidate_size = statistics.mean(100 * r['candidate_bytes'] / r['raw_bytes'] for r in rows)
    state = audit.read(gate / 'state.json')
    return {'scope': 'Read-only receipt audit; public finite observations, not proof, admission or rewards',
            'status': 'STOP' if stops else 'PUBLIC_PERFORMANCE_REVIEW',
            'run_id': state.get('run_id'), 'git_sha': state.get('git_sha'),
            'candidate': candidate, 'source_sha256': entry['hashes']['parse.rs'],
            'baseline': {'candidate': control, 'source_sha256': base_entry['hashes']['parse.rs'],
                         'profile_proxy': baseline_candidate, 'profile_proxy_gate': str(baseline_gate),
                         'rebound_files': len(rows), 'binding': 'current public299 input/token/output hashes and counts equal both historical public299 and historical proxy native records'},
            'hash_checks': {'profile_jsonl_digest': 'recomputed from saved bytes',
                            'parser_sources': 'recomputed from frozen local source bytes and bound to run spec/profile/native meta',
                            'input_token_output': 'cross-checked across native rounds, profile records and historical baseline receipts',
                            'limit': 'Raw corpus/token/compressed streams are absent here; their content SHA256 values cannot be independently recomputed from histograms. Output hashes are verified for receipt consistency, not regenerated.'},
            'summary': {'files': len(rows), 'boundary_changed_files': boundary, 'larger_files': larger,
                        'smaller_files': [r['file'] for r in rows if r['bytes_delta'] < 0],
                        'total_bytes_delta': sum(r['bytes_delta'] for r in rows), 'size_axis_delta_pp': gain,
                        'baseline_size_pct': baseline_size, 'candidate_size_pct': candidate_size,
                        'baseline_time_axis': bt, 'candidate_time_axis': ct,
                        'time_axis_change_pct': 100 * (ct / bt - 1),
                        'timing_rounds': [r['round'] for r in new], 'stop_conditions': stops,
                        'remaining': 'Fresh frontier scoring at the measured time coordinate is required; no earlier fixed threshold is assumed. Small byte savings alone do not establish useful frontier margin. Formal proof/axioms still required; a non-STOP status is not a gate verdict.'},
            'files': rows, 'receipt_sha256': audit.receipts}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('gate', type=Path)
    ap.add_argument('--candidate', default='r5-opt-a-sameend299')
    ap.add_argument('--baseline-gate', type=Path, default=DEFAULT_BASE)
    ap.add_argument('--baseline-candidate', default='r4-alt299-tinydepth32')
    args = ap.parse_args()
    try:
        result = analyze(args.gate, args.candidate, args.baseline_gate, args.baseline_candidate)
    except (EvidenceError, OSError, ValueError, KeyError, TypeError) as error:
        print(json.dumps({'status': 'EVIDENCE_ERROR', 'error': str(error)}, ensure_ascii=False))
        return 1
    print(json.dumps(result, ensure_ascii=False, indent=2))
    return 2 if result['status'] == 'STOP' else 0


if __name__ == '__main__':
    sys.exit(main())
