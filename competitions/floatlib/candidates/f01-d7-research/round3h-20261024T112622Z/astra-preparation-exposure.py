"""Bounded source reconstruction on completed df5c inputs, not a timing probe."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import sys
import time

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
ROOT = CS.parents[2]
OLD = HERE.parent / 'round6h-20261024T051445Z'
sha = lambda b: hashlib.sha256(b).hexdigest()


def main():
    started = time.monotonic()
    deadline = started + 180
    prior_path = OLD / 'astra-lowexp-integer-dot-memo.json'
    prior = json.loads(prior_path.read_bytes())
    parent = CS / 'f01-d12-scalar-combined/Kernel.lean'
    assert sha(parent.read_bytes()) == prior['candidate_sha256']
    for binding in prior['source_bindings']:
        assert sha((ROOT / binding['path']).read_bytes()) == binding['sha256']
    ex_path = HERE.parent / 'round7h-20261023T193125Z/review-output-underflow-exposure.py'
    spec = importlib.util.spec_from_file_location('source_reconstruction_only', ex_path)
    ex = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(ex)
    element = ex.load_generator(ex.RESEARCH / 'public-nonfinite-opportunity.py')['element']
    totals = dict(cases=0, valid_A_words=0, valid_B_words=0, warm_A_words=0,
                  warm_B_words=0, padded_B_slots=0, original_underflow_cases=0)
    runs = []
    for run in prior['runs']:
        for evidence in run['evidence'].values():
            assert sha((ROOT / evidence['canonical_path']).read_bytes()) == evidence['sha256']
        local = {k: 0 for k in totals}
        cases = []
        for item in run['cases']:
            c = item['generator_case']
            batch, m, n, p = item['shape']
            assert c['timed'] and c['kernel'] == 'bmm'
            underflow = item['already_UnderflowZero_reconstructed']
            if underflow:
                local['original_underflow_cases'] += 1
            # Current complete dispatch: underflow, cross p=2, direct n<=4/p<=2,
            # then RowStream when output and n are nonzero.
            if underflow or n <= 4 or p <= 2 or batch*m*p == 0:
                continue
            local['cases'] += 1
            row = dict(name=c['name'], shape=[batch,m,n,p], roles={})
            for role, label, length, width in [(0,'A',batch*m*n,n),(1,'B',batch*n*p,p)]:
                warm = zeros = nonfinite = 0
                digest = hashlib.sha256()
                for i in range(length):
                    if i % 4096 == 0:
                        assert time.monotonic() < deadline
                    u = element(c, i, role, width)
                    digest.update(u.to_bytes(4,'little'))
                    a = u & 0x7fffffff
                    fast = a == 0 or 0x0c000000 <= a < 0x7f800000
                    warm += fast
                    zeros += a == 0
                    nonfinite += a >= 0x7f800000
                row['roles'][label] = dict(words=length, warm=warm, zero=zeros,
                    fallback=length-warm, nonfinite=nonfinite, little_endian_sha256=digest.hexdigest())
                local[f'valid_{label}_words'] += length
                local[f'warm_{label}_words'] += warm
            row['padded_B_slots'] = batch*n*((p+9)//10*10-p)
            local['padded_B_slots'] += row['padded_B_slots']
            cases.append(row)
        for k in totals:
            totals[k] += local[k]
        runs.append(dict(seed=run['seed'], run=run['run'], counts=local, cases=cases,
            recorded_whole_ns=run['whole_recorded_scored_ns'],
            recorded_BMM_whole_fraction=run['BMM_whole_fraction']))
    out = dict(state='INFERRED_PINNED_SOURCE_INPUT_COUNTS_ONLY',
        at_utc=datetime.now(timezone.utc).isoformat(), elapsed_seconds=time.monotonic()-started,
        script_sha256=sha(Path(__file__).read_bytes()), parent_sha256=prior['candidate_sha256'],
        source_record=dict(path=str(prior_path.relative_to(ROOT)).replace('\\','/'), sha256=sha(prior_path.read_bytes())),
        source_bindings=prior['source_bindings'], totals=totals, runs=runs,
        conversion_frequency='One conversion per valid A/B input in current RowStream; padded B slots already use zero and are not foreign-call savings.',
        boundaries='Counts reconstruct the pinned source, not measured runtime events. Original source tiny/empty/cross/underflow dispatch excluded. No timing allocated by counts; preparation cost and achievable whole gain UNKNOWN.')
    (HERE/'astra-preparation-exposure.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(dict(seconds=out['elapsed_seconds'],totals=totals,runs=[dict(seed=r['seed'],counts=r['counts']) for r in runs]),indent=2))


if __name__ == '__main__':
    main()
