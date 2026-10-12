"""Recheck archived R7 paired totals and replay each block against one current capture."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json
import statistics as st

M = importlib.import_module('r26-score-map')
ROOT = M.ROOT
RUNS = [('37636716596', 'middle-a'), ('37636990183', 'middle-cpu'),
        ('37641161339', 'middle-block'), ('37642665812', 'middle-seed')]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', required=True, type=Path)
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args(); assert not a.output.exists()
    manifest = ROOT/'evidence/round7/final-receipt-manifest.json'
    recorded = json.loads(manifest.read_bytes())['files']; checked = {}
    def read(path):
        raw = path.read_bytes(); name = path.relative_to(ROOT).as_posix()
        identity = {'bytes': len(raw), 'sha256': hashlib.sha256(raw).hexdigest()}
        assert identity == recorded[name], name
        checked[name] = identity
        return raw
    r = M.Replay(a.capture, ROOT/'evidence/round26/official-rules-start-live'); M.audit(r)
    fm = r.byid['361']['metrics']; groups = {}; controls = []; inputs = {}; outputs = {}
    processes = 0
    for rid, batch in RUNS:
        folder = ROOT/'evidence/round7'/rid/batch/'gate'
        state = json.loads(read(folder/'state.json')); ci = json.loads(read(folder/'ci-run.json'))
        assert ci['conclusion'] == 'success' and ci['headSha'] == state['git_sha']
        assert str(ci['databaseId']) == state['run_id'] == rid and not state['failures']
        entries = {e['name']: e for e in state['spec']['entries']}; by = {}
        for m in state['metrics']:
            name, block = m['candidate'], m['round']; entry = entries[name]
            data = [json.loads(line) for line in read(folder/f'round{block}-{name}.jsonl').splitlines()]
            meta = data[0]; fs = [f for f in data if f['kind'] == 'file']
            assert meta['warmup_rounds'] == 1 and meta['measured_rounds'] == 11
            assert len(fs) == 28 and sum(f['raw_bytes'] for f in fs) == 15930000
            assert meta['methods'][name]['source_sha256'] == entry['hashes']['parse.rs']
            times, sizes = [], []
            for f in fs:
                assert inputs.setdefault(f['file'], f['sha256']) == f['sha256']
                meds = {}
                for method in (name, 'incumbent'):
                    value = f['methods'][method]; assert value['deterministic'] and not value['errors']
                    reps = [v['total_s'] for v in value['reps'] if v['phase'] == 'measured']
                    assert len(reps) == 11 and min(reps) > 0
                    meds[method] = st.median(reps)
                value = f['methods'][name]
                key = (entry['hashes']['parse.rs'], f['file'])
                output = (value['tokens_sha256'], value['output_sha256'], value['output_bytes'])
                assert outputs.setdefault(key, output) == output
                times.append(meds[name]/meds['incumbent']); sizes.append(100*value['output_bytes']/f['raw_bytes'])
            x, y = st.mean(times), st.mean(sizes)
            assert abs(x-m['time']) < 1e-12 and abs(y-m['size_pct']) < 1e-12
            by[name, block] = (x, y, meta['methods'][name]['lib_sha256']); processes += 1
        for (name, block), (x, y, binary) in by.items():
            if name == 'mid-shadow':
                assert entries[name]['hashes'] == entries['public361']['hashes']
                assert binary == by['public361', block][2]
                controls.append({'run': rid, 'block': block,
                    'parent_shadow_relative_time_pct': 100*(x/by['public361', block][0]-1)})
            if not name.startswith('r7-mid361-'): continue
            e = entries[name]
            g = groups.setdefault(name, {'candidate': name, 'source_pair': e['hashes'], 'observations': []})
            assert g['source_pair'] == e['hashes']
            for label, ref in [('primary', 'public361'), ('shadow', 'mid-shadow')]:
                if (ref, block) not in by: continue
                px, py = fm['balanced_time_ratio']*x/by[ref, block][0], fm['mean_file_compression_pct']*y/by[ref, block][1]
                score = r.describe([(name, px, py)])['points'][name]
                g['observations'].append({'run': rid, 'block': block, 'calibration': label,
                    'projected_x': px, 'projected_y': py, 'conditional_share_pct': score['share_pct'],
                    'dominator_ids': score['dominator_ids'], 'role': 'historical_selection_not_new_confirmation'})
    out = {'status': 'VERIFIED_ARCHIVED_RAW_REPLAY_CONDITIONAL_CURRENT_GEOMETRY', 'snapshot': r.context,
        'manifest_sha256': hashlib.sha256(manifest.read_bytes()).hexdigest(), 'input_hashes': checked,
        'paired_processes': processes, 'source_runner_count': len(RUNS), 'candidates': list(groups.values()),
        'same_source_controls': controls, 'limits': ['Historical discovery and old confirmation are selection evidence here.',
        'No new measurements, gates, formal admission or realized rewards.', 'Calibration views do not add samples.']}
    a.output.write_bytes((json.dumps(out, indent=2)+'\n').encode())
    print(json.dumps({'candidates': len(groups), 'original_processes': processes,
        'best_individual_block_pct': max(o['conditional_share_pct'] for g in groups.values() for o in g['observations'])}))


if __name__ == '__main__': main()
