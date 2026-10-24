"""Conditional request-count model for frozen GeneralPanel, not a time model."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
CS = HERE.parent.parent
ROOT = CS.parents[2]
sha = lambda data: hashlib.sha256(data).hexdigest()


def main():
    kernel = CS / 'f01-r12-general-panel/Kernel.lean'
    assert sha(kernel.read_bytes()) == 'a1ab536c08d666f8b3f5d848d3fb9341410f37e3072f0d1ee17dba7672e48abe'
    suite = HERE / 'astra-ci1224003/diagnostics/f01-d7-public-suite/public-suite'
    summary = json.loads((suite / 'summary.json').read_text(encoding='utf-8'))
    assert summary['seed'] == 1224003 and summary['complete']
    assert sha((suite / 'summary.json').read_bytes()) == '01c382c46ba038d0319cc341f6f326ab08b0f220f353a33f56c8df979afc8b83'
    plan = json.loads((suite / 'public-drawn-plan.json').read_text(encoding='utf-8'))
    runtime = CS / 'f01-d7-research/round1h-20261023T110107Z/runtime-boundary/lean.h.raw'
    assert sha(runtime.read_bytes()) == '982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
    prior = CS / 'f01-d7-research/round7h-20261023T193125Z/review-panel-codegen-931.json'
    p = json.loads(prior.read_text(encoding='utf-8'))
    old_root = ROOT / p['run']['artifact_directory']
    checked = []
    for relative, desc in p['original_artifact_members'].items():
        if relative.endswith(('asm-0-5.txt', 'asm-0-9.txt', 'asm-0-14.txt', 'file-0-Submission.c')):
            f = old_root / relative
            raw = f.read_bytes()
            assert len(raw) == desc['bytes'] and sha(raw) == desc['sha256']
            checked.append({'path': str(f.relative_to(ROOT)), **desc})
    assert len(checked) == 4, checked
    cells = {}
    totals = {k: 0 for k in ['all_timed_bmm_mac', 'eligible_mac', 'full_block_mac',
        'tail_mac', 'eligible_cases', 'full_blocks', 'tail_calls_including_empty',
        'empty_tail_calls', 'native_A_values', 'F4_records', 'tail_float_boxes',
        'old_A_request_bytes', 'new_A_request_bytes', 'G1_full_block_mac']}
    cases = []
    for c in plan['cases']:
        if c['kernel'] != 'bmm' or not c['timed']:
            continue
        b, m, n, q = [c[x] for x in ['batch', 'm', 'n', 'p']]
        mac = b*m*n*q
        totals['all_timed_bmm_mac'] += mac
        if not (b > 0 and m >= 4 and n > 4 and q > 2):
            continue
        t, r = divmod(m, 4)
        T, U, G = b*t, b*r, (q+9)//10
        N = b*m*n
        old_bytes = 24 + 24*N
        new_bytes = 32*n*T + 24*n*U + 24*(T+b)
        assert new_bytes-old_bytes == -64*n*T + 24*(T+b-1)
        row = {'name': c['name'], 'batch': b, 'm': m, 'n': n, 'p': q,
            'G': G, 'full_blocks': T, 'tail_rows': U,
            'tail_calls_including_empty': b, 'empty_tail_calls': b if r == 0 else 0,
            'native_A_values': N, 'F4_records': n*T, 'tail_float_boxes': n*U,
            'full_block_mac': 4*T*n*q, 'tail_mac': U*n*q,
            'old_A_request_bytes': old_bytes, 'new_A_request_bytes': new_bytes,
            'conditional_local_A_peak_request_bytes': max(24+32*n, 24+24*n*r),
            'numeric_A_array_headers': T+b, 'ofBits_calls_both_versions': N}
        cases.append(row)
        cell = c['name'].rsplit(':', 1)[0]
        cells.setdefault(cell, []).append(c['name'])
        totals['eligible_cases'] += 1
        totals['eligible_mac'] += mac
        for k in ['full_blocks', 'tail_calls_including_empty', 'empty_tail_calls',
                  'native_A_values', 'F4_records', 'tail_float_boxes', 'full_block_mac',
                  'tail_mac', 'old_A_request_bytes', 'new_A_request_bytes']:
            totals[k] += row[k]
        if G == 1:
            totals['G1_full_block_mac'] += row['full_block_mac']
    totals['full_block_fraction_of_all_BMM_MAC'] = totals['full_block_mac']/totals['all_timed_bmm_mac']
    totals['tail_fraction_of_eligible_MAC'] = totals['tail_mac']/totals['eligible_mac']
    totals['G1_fraction_of_full_block_MAC'] = totals['G1_full_block_mac']/totals['full_block_mac']
    rec = {'at_utc': datetime.now(timezone.utc).isoformat(), 'candidate_sha256': sha(kernel.read_bytes()),
        'model_script_sha256': sha(Path(__file__).read_bytes()),
        'status': 'CONDITIONAL_REQUEST_MODEL_NO_TIME_OR_RSS_CLAIM',
        'scope': 'Only completed discovery1224003. All eligible cases conditional on outer Underflow miss; actual raw-input path counts not measured. No holdout read.',
        'formula': {'T': 'batch*floor(m/4)', 'U': 'batch*(m%4)', 'N': 'n*(4*T+U)',
            'old_A_request_bytes': '24+24*N',
            'new_A_request_bytes': '32*n*T+24*n*U+24*(T+batch)',
            'new_minus_old': '-64*n*T+24*(T+batch-1)',
            'ofBits_calls_old_and_new': 'N',
            'local_peak_if_each_panel_freed_before_next': 'max(24+32*n,24+24*n*(m%4))'},
        'request_model_assumptions': ['x86_64 fixed Lean runtime: float box16, F4 constructor24, array header24 and pointer slot8',
            'Array capacity equals length; local tail Array.ofFn called once per batch including empty tail',
            'Counts A numeric representation only; excludes raw A/B, packedB, outputs/F40, closure/Nat/RC/transient allocations and allocator usable size',
            'New actual integrated C/assembly and lifetime not yet available; 931 only supports unchanged helper representation',
            '112 B per-block closures in 931 are separate from formula, and do not establish the new integrated allocation schedule'],
        'checked_evidence': checked + [{'path': str(runtime.relative_to(ROOT)), 'sha256': sha(runtime.read_bytes())}],
        'plan_sha256': sha((suite/'public-drawn-plan.json').read_bytes()),
        'totals': totals, 'touched_cells': cells, 'cases': cases,
        'performance': 'UNKNOWN',
        'next_falsifier': 'Original new full gate plus actual caller C: no full A map on Panel branch, one prepare per block, no Float32 callback boxing, local tail separate numeric/raw bases; then clean whole-call normalized cost.'}
    (HERE/'astra-general-panel-cost.json').write_text(json.dumps(rec, ensure_ascii=False, indent=2)+'\n', encoding='utf-8', newline='\n')
    print(json.dumps(totals, indent=2))


if __name__ == '__main__':
    main()
