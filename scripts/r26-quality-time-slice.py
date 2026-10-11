"""Map measured native quality to hypothetical time; never fabricate time observations."""
import argparse
import hashlib
import importlib
import json
from pathlib import Path

M = importlib.import_module('r26-score-map')
intervals = importlib.import_module('r26-target-slices').intervals


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--quality', required=True, type=Path)
    ap.add_argument('--capture', required=True, type=Path)
    ap.add_argument('--formal-id', required=True)
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args()
    assert not a.output.exists()
    q = json.loads(a.quality.read_bytes())
    assert q['status'] == 'VERIFIED_ORIGINAL_ENCODER_BYTES_ONLY'
    r = M.Replay(a.capture, M.ROOT/'evidence/round26/official-rules-start-live')
    M.audit(r)
    fm = r.byid[a.formal_id]['metrics']
    parent = next(x for x in q['summary'] if x['candidate'] == q['parent'])
    output = {'status': 'INFERRED_QUALITY_CONDITIONED_TIME_GRID_NOT_PERFORMANCE',
        'snapshot': r.context, 'native_quality_receipt_sha256': hashlib.sha256(a.quality.read_bytes()).hexdigest(),
        'native_quality_receipt': str(a.quality), 'formal_id': a.formal_id,
        'mapping': 'formal parent quality * native candidate quality / native parent quality',
        'time_grid': {'relative_parent_min': .80, 'relative_parent_max': 1.15, 'step': .0001},
        'candidates': [], 'limits': ['Quality mapping to hidden corpus is conditional.',
        'No candidate timing has been measured by this script.',
        'Sampled intervals are not continuous thresholds or stability evidence.',
        'No shadow-noise model or success probability is asserted.']}
    for row in q['summary']:
        if row['candidate'] == q['parent'] or not row['candidate'].startswith('r26-'):
            continue
        y = fm['mean_file_compression_pct']*row['public_size_pct']/parent['public_size_pct']
        xs = []
        for i in range(3501):
            f = .8 + i*.0001
            score = r.describe([('candidate', fm['balanced_time_ratio']*f, y)])['points']['candidate']['share_pct']
            xs.append({'factor': f, 'minimum_share_pct': score, 'maximum_share_pct': score})
        output['candidates'].append({'candidate': row['candidate'], 'source_hashes': q['candidate_hashes'][row['candidate']],
            'conditional_quality_pct': y,
            'share_at_unmeasured_equal_parent_time_pct': r.describe([('candidate', fm['balanced_time_ratio'], y)])['points']['candidate']['share_pct'],
            'targets': {str(t): intervals(xs, t, 'factor') for t in (5, 10)}})
    a.output.write_text(json.dumps(output, indent=2)+'\n', encoding='utf-8')
    print(json.dumps(output['candidates'], indent=2))


if __name__ == '__main__':
    main()
