from pathlib import Path
import datetime, hashlib, json

HERE = Path(__file__).resolve().parent
OLD = HERE.parents[2] / 'r26-1h-20261029T085515Z' / 'research' / 'fallback'


def decode(w):
    e = (w >> 23) & 255
    f = w & ((1 << 23) - 1)
    return (-1 if w >> 31 else 1), (f if e == 0 else f + (1 << 23)), max(0, e - 1), e != 255


def align(words):
    ds = list(map(decode, words))
    base = min((e for _, m, e, _ in ds if m), default=0)
    vals = [s * (m << (e-base)) if m else 0 for s, m, e, _ in ds]
    return dict(base=base, values=vals, maximum=max(map(abs, vals), default=0),
                mass=sum(map(abs, vals)), finite=all(f for _, _, _, f in ds))


def main():
    rows, inputs = [], []
    for kind in ['normal', 'sparse']:
        p = OLD / f'word-fixture-{kind}.txt'
        lines = p.read_text().splitlines()
        n, out = map(int, lines[:2])
        x, w, bias = [list(map(int, x.split(','))) for x in lines[2:5]]
        assert len(x) == n and len(w) == n*out and len(bias) == out
        ax = align(x)
        for j in range(out):
            aw = align(w[j*n:(j+1)*n])
            products = [a*b for a,b in zip(ax['values'], aw['values'])]
            positive, negative = sum(max(0, p) for p in products), sum(max(0, -p) for p in products)
            _, bm, be, bf = decode(bias[j])
            shift = be+149-ax['base']-aw['base']
            uniform = n*ax['maximum']*aw['maximum']
            l1bound = min(ax['mass']*aw['maximum'], aw['mass']*ax['maximum'])
            assert positive+negative <= l1bound <= uniform
            rows.append(dict(kind=kind, output=j, n=n, baseA=ax['base'], baseB=aw['base'],
                             maxA=ax['maximum'], maxB=aw['maximum'], massA=ax['mass'], massB=aw['mass'],
                             body_factor32=all(-(1<<31)<=v<(1<<31) for v in ax['values']+aw['values']),
                             block16=ax['maximum']*aw['maximum']<(1<<59),
                             uniform_global64=uniform<(1<<63), l1_global64=l1bound<(1<<63),
                             actual_mass_global64=positive+negative<(1<<63),
                             actual_bucket63=max(positive,negative)<(1<<63),
                             uniform_bits=uniform.bit_length(), l1_bits=l1bound.bit_length(),
                             actual_mass_bits=(positive+negative).bit_length(),
                             positive_bits=positive.bit_length(), negative_bits=negative.bit_length(),
                             signed_total_bits=abs(positive-negative).bit_length(),
                             all_finite=ax['finite'] and aw['finite'] and bf,
                             bias_shift=shift, bias_shift_eligible=(bm==0 or shift>=0)))
        inputs.append(dict(file=str(p), bytes=p.stat().st_size, sha256=hashlib.sha256(p.read_bytes()).hexdigest()))
    metrics = ['body_factor32','block16','uniform_global64','l1_global64','actual_mass_global64','actual_bucket63','all_finite','bias_shift_eligible']
    report = dict(at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                  classification='FINITE_FIXED_PUBLIC_R26_FIRST_LAYER_CENSUS_NOT_LEAN_OR_TIMING',
                  scope='R26 already-seen public typical seed42 normal/sparse first layer only; no final confirmation inputs',
                  inputs=inputs, rows=rows,
                  counts={kind:{k:sum(r[k] for r in rows if r['kind']==kind) for k in metrics} for kind in ['normal','sparse']},
                  conclusions=['L1-max bound is a valid cheap sufficient global64 guard but coverage must be measured, not assumed.',
                               'Actual mass/bucket eligibility requires reading products and cannot be used as cached metadata for free.',
                               'Bias and finite guard must hold independently; these body-only counts cannot authorize a finish path.'],
                  missing=['Other models/layers/seeds','Actual native route usage','Current champion comparison'])
    (HERE/'guard-coverage.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'count':len(rows),'counts':report['counts']},indent=2))


if __name__ == '__main__':
    main()
