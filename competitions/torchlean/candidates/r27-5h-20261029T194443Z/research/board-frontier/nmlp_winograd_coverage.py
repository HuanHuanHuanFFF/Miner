"""Actual-context factor coverage for source12's complete normalized MLP.
This is a finite formula census, not native measurement or a correctness proof.
"""
from datetime import datetime, timezone
import hashlib, json
from pathlib import Path
import norm_frontier as nf
from winograd_word_check import prep

def coverage(x, w, rows, k, out_width):
    a = [prep(x[r*k:(r+1)*k]) for r in range(rows)]
    b = [prep(w[j*k:(j+1)*k]) for j in range(out_width)]
    eligible = sum(aa is not None and bb is not None and aa[1]+bb[1] < (1 << 32)
                   for aa in a for bb in b)
    return {'shape': [rows, k, out_width], 'valid_input_rows': sum(v is not None for v in a),
            'valid_weight_rows': sum(v is not None for v in b), 'eligible_outputs': eligible,
            'outputs': rows*out_width, 'no_input_row_admitted': all(v is None for v in a)}

def main():
    start = datetime.now(timezone.utc).isoformat()
    cells = []
    for seed in [27051001, 27151004, 27251007]:
        for profile in ['typical', 'scale', 'boundary']:
            i, h, h2 = nf.dimensions(seed, profile)
            for kind in ['normal', 'wide', 'sparse']:
                rows = 8
                x = nf.gen(kind, rows*i, seed+999)
                w = nf.weights(kind, seed, 1, i, h*i)
                c1 = coverage(x, w, rows, i, h)
                x = nf.linear(x, rows, i, h, w, nf.bias(seed, 2, h), True)
                x = nf.norm(x, rows, h, nf.scale(seed+3, h))
                w = nf.weights(kind, seed, 4, h, h2*h)
                c2 = coverage(x, w, rows, h, h2)
                x = nf.linear(x, rows, h, h2, w, nf.bias(seed, 5, h2), True)
                x = nf.norm(x, rows, h2, nf.scale(seed+6, h2), nf.bias(seed, 7, h2))
                w = nf.weights(kind, seed, 8, h2, 10*h2)
                c3 = coverage(x, w, rows, h2, 10)
                cells.append({'seed': seed, 'profile': profile, 'kind': kind,
                              'linear1': c1, 'linear2': c2, 'linear3': c3})
    summary = {stage: {'eligible_outputs': sum(c[stage]['eligible_outputs'] for c in cells),
                      'outputs': sum(c[stage]['outputs'] for c in cells),
                      'no_input_row_cells': sum(c[stage]['no_input_row_admitted'] for c in cells)}
               for stage in ['linear1', 'linear2', 'linear3']}
    out = {'status': 'FINITE_CONTEXT_COVERAGE_ONLY', 'start_utc': start,
           'end_utc': datetime.now(timezone.utc).isoformat(),
           'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
           'cells': cells, 'summary': summary,
           'decision': 'If no input cache is admitted, retain whole original linear before building all weight factors; avoid paying scalar per-output fallback and losing four-row fusion.',
           'limits': ['No runtime timing', 'No current champion result', 'Observed cells only, not universal coverage probabilities']}
    Path(__file__).with_name('nmlp-winograd-coverage.json').write_text(json.dumps(out, indent=2), encoding='utf-8')
    print(json.dumps({'cells': len(cells), 'summary': summary}))

if __name__ == '__main__':
    main()
