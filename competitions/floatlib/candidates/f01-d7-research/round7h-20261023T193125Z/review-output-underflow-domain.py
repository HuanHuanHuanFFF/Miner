"""Three mathematical domains only, completed901/902/904; no new Kernel.

Full A/B word reconstructions (not prefixes) provide max exponents/scales and
nonfinite exclusion. Proposed dynamic certificates use one A-then-B scheme with
early rejection. Word counts are work, not scan time or speedup.
"""
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json
import runpy
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
POLICIES = ('fixed43', 'scale_sum84', 'scale_sum100')

def scan_full(c, role, length, row_width, element, limits, deadline):
    digest = sha256()
    max_exp = max_scale = max_magnitude = 0
    nonfinite = nan = inf = 0
    first_nonfinite = None
    violations = {k: None for k in POLICIES}
    for i in range(length):
        if i % 8192 == 0:
            assert time.monotonic() < deadline, '600s source analysis limit reached'
        w = element(c, i, role, row_width)
        digest.update(w.to_bytes(4, 'little'))
        magnitude, exponent, fraction = w & 0x7fffffff, (w >> 23) & 255, w & 0x7fffff
        max_magnitude = max(max_magnitude, magnitude)
        max_exp = max(max_exp, exponent)
        finite = exponent != 255
        scale = max(0, exponent - 1) if finite else None
        if finite:
            max_scale = max(max_scale, scale)
        else:
            nonfinite += 1
            nan += fraction != 0
            inf += fraction == 0
            if first_nonfinite is None:
                first_nonfinite = {'index': i, 'word': f'{w:08x}', 'kind': 'NaN' if fraction else 'Inf'}
        for policy in POLICIES:
            if violations[policy] is not None:
                continue
            limit = limits.get(policy)
            if policy == 'fixed43':
                bad = magnitude >= 0x16000000
            elif limit is None:
                continue
            else:
                bad = not finite or scale > limit
            if bad:
                violations[policy] = {'index': i, 'word': f'{w:08x}',
                                      'exponent': exponent, 'finiteScale': scale,
                                      'reason': 'nonfinite' if not finite else 'domain bound'}
    return {'words': length, 'all_finite': nonfinite == 0,
            'max_raw_exponent': max_exp, 'max_finiteScale_over_finite_words': max_scale,
            'max_magnitude': f'{max_magnitude:08x}', 'nonfinite_words': nonfinite,
            'nan_words': nan, 'inf_words': inf, 'first_nonfinite': first_nonfinite,
            'full_words_le_sha256': digest.hexdigest(), 'first_rejections': violations}

def sequential_certificate(a, b, policy):
    av, bv = a['first_rejections'][policy], b['first_rejections'][policy]
    if av is not None:
        return {'hit': False, 'A_words': av['index'] + 1, 'B_words': 0,
                'total_words': av['index'] + 1, 'reject_operand': 'A', 'reject': av}
    if bv is not None:
        return {'hit': False, 'A_words': a['words'], 'B_words': bv['index'] + 1,
                'total_words': a['words'] + bv['index'] + 1, 'reject_operand': 'B', 'reject': bv}
    return {'hit': True, 'A_words': a['words'], 'B_words': b['words'],
            'total_words': a['words'] + b['words'], 'reject_operand': None, 'reject': None}

def main():
    started = time.monotonic()
    deadline = started + 600
    exposure_py = HERE / 'review-output-underflow-exposure.py'
    exposure_json = HERE / 'review-output-underflow-exposure.json'
    previous = json.loads(exposure_json.read_text(encoding='utf-8'))
    assert previous['only_exposed_seeds'] == [901, 902, 904]
    assert previous['analysis_source_sha256'] == sha256(exposure_py.read_bytes()).hexdigest()
    for src in previous['sources']:
        p = ROOT / src['path']
        assert sha256(p.read_bytes()).hexdigest() == src['sha256'], 'Exposed source evidence changed'
    lib = runpy.run_path(str(exposure_py), run_name='underflow_exposure_definitions_only')
    element = lib['load_generator'](lib['RESEARCH'] / 'public-nonfinite-opportunity.py')['element']
    results = []
    for old_run in previous['runs']:
        assert old_run['seed'] in (901, 902, 904)
        rows = []
        for old in old_run['cases']:
            c = old['generator_case']
            batch, m, n, p = old['shape_batch_m_n_p']
            a = scan_full(c, 0, batch * m * n, n, element,
                          {'scale_sum84': 84, 'scale_sum100': 100}, deadline)
            # B budgets follow the complete A maximum. When A rejects, B is not
            # part of that runtime certificate, but is still fully reconstructed.
            amax = a['max_finiteScale_over_finite_words']
            budgets = {f'scale_sum{limit}': limit - amax
                       if a['all_finite'] and amax <= limit else None for limit in (84, 100)}
            b = scan_full(c, 1, batch * n * p, p, element, budgets, deadline)
            finite = a['all_finite'] and b['all_finite']
            scale_sum = amax + b['max_finiteScale_over_finite_words']
            domains = {
                'fixed43': a['max_raw_exponent'] <= 43 and b['max_raw_exponent'] <= 43,
                'scale_sum84': finite and scale_sum <= 84,
                'scale_sum100': finite and scale_sum <= 100,
            }
            costs = {key: sequential_certificate(a, b, key) for key in POLICIES}
            assert domains['fixed43'] == old['whole_matrix_hit_reconstructed']
            assert costs['fixed43']['total_words'] == old['runtime_total_scan_words_reconstructed']
            assert all(costs[key]['hit'] == domains[key] for key in POLICIES)
            assert not domains['fixed43'] or domains['scale_sum84']
            assert not domains['scale_sum84'] or domains['scale_sum100']
            rows.append({'name': old['name'], 'timed': old['timed'], 'input_seed': old['input_seed'],
                         'shape_batch_m_n_p': old['shape_batch_m_n_p'], 'MAC_work': old['mac_work'],
                         'output_words': old['output_words'], 'A_full': a, 'B_full': b,
                         'max_finiteScale_sum': scale_sum, 'both_arrays_finite': finite,
                         'mathematical_domain_hits': domains,
                         'A_then_B_certificate_word_counts': costs,
                         'a066_case_time': 'UNKNOWN_NOT_RETAINED',
                         'actual_guard_or_certificate_trace': 'UNKNOWN_NO_NEW_CODE_EXECUTED'})
        timed = [r for r in rows if r['timed']]
        total_work = sum(r['MAC_work'] for r in timed)
        policies = {}
        for policy in POLICIES:
            hit = [r for r in timed if r['mathematical_domain_hits'][policy]]
            misses = [r for r in timed if not r['mathematical_domain_hits'][policy]]
            new_fixed = [r for r in hit if not r['mathematical_domain_hits']['fixed43']]
            new_84 = [r for r in hit if not r['mathematical_domain_hits']['scale_sum84']]
            policies[policy] = {
                'hit_cases': [r['name'] for r in hit], 'hit_count': len(hit),
                'hit_MAC_work': sum(r['MAC_work'] for r in hit),
                'fraction_of_BMM_MAC_work': sum(r['MAC_work'] for r in hit) / total_work,
                'new_vs_fixed43_cases': [r['name'] for r in new_fixed],
                'new_vs_fixed43_MAC_work': sum(r['MAC_work'] for r in new_fixed),
                'new_vs_scale_sum84_cases': [r['name'] for r in new_84],
                'new_vs_scale_sum84_MAC_work': sum(r['MAC_work'] for r in new_84),
                'hit_full_scan_words': sum(r['A_full']['words'] + r['B_full']['words'] for r in hit),
                'miss_words_for_A_then_B_early_reject': sum(r['A_then_B_certificate_word_counts'][policy]['total_words'] for r in misses),
                'all_case_words_for_A_then_B_scheme': sum(r['A_then_B_certificate_word_counts'][policy]['total_words'] for r in timed),
                'miss_words_if_naively_scanning_both_arrays_fully': sum(r['A_full']['words'] + r['B_full']['words'] for r in misses),
                'added_time_coverage': 'UNKNOWN',
            }
        results.append({'seed': old_run['seed'], 'run': old_run['run'],
                        'timed_BMM_cases': len(timed), 'total_BMM_MAC_work': total_work,
                        'full_A_B_words_reconstructed': sum(r['A_full']['words'] + r['B_full']['words'] for r in rows),
                        'nonfinite_input_words': sum(r['A_full']['nonfinite_words'] + r['B_full']['nonfinite_words'] for r in rows),
                        'policies': policies, 'cases': rows})
        print(json.dumps({'seed': old_run['seed'], 'policies': {k: {'hits': v['hit_cases'], 'new_vs_fixed': v['new_vs_fixed43_cases'], 'scheme_words': v['all_case_words_for_A_then_B_scheme']} for k, v in policies.items()}}), flush=True)
    additional84 = sum(r['policies']['scale_sum84']['new_vs_fixed43_MAC_work'] for r in results)
    additional100 = sum(r['policies']['scale_sum100']['new_vs_fixed43_MAC_work'] for r in results)
    decision = 'PARK_DYNAMIC_MAX_CERTIFICATE_NO_NEW_HITS' if additional84 == additional100 == 0 else 'REVIEW_INCREMENTAL_DOMAIN_ONLY_NO_RUNTIME_AUTHORIZATION'
    report = {
        'state': 'COMPLETE_THREE_DOMAIN_FULL_INPUT_RECONSTRUCTION',
        'updated_at_utc': datetime.now(timezone.utc).isoformat(), 'analysis_seconds': time.monotonic() - started,
        'analysis_source_sha256': sha256(Path(__file__).read_bytes()).hexdigest(),
        'exposure_report_sha256': sha256(exposure_json.read_bytes()).hexdigest(),
        'only_exposed_seeds': [901, 902, 904], 'future_inputs_read': False, 'new_Kernel_written': False,
        'input_status': previous['input_status'],
        'source_identity': previous['source_identity'],
        'source_hashes': previous['sources'],
        'domains': {
            'fixed43': 'Actual6a69 guard: all raw magnitudes<0x16000000; equivalently both full max raw exponents<=43.',
            'scale_sum84': 'Reject any raw exponent255. Both full max finiteScale values (e0->0,e>0->e-1) sum<=84. Existing generic64bit rounding lemma arithmetic domain; new scan-max bridge/runtime absent.',
            'scale_sum100': 'Reject any raw exponent255; max finiteScale sum<=100. Would additionally require formal24bit mantissa/product<2^48 and RNE shift>=49 result0 proof; absent from6a69.',
        },
        'word_count_model': 'One scheme only: scan A for finite max, early reject at nonfinite or scale>limit; after complete A, scan B with residual limit-maxA and early reject. Counts include first rejecting word. Full stats reconstruction always scans both arrays independently; those analysis reads are not runtime costs.',
        'timing': 'All individual a066 case time weights and scan/max/fill ns UNKNOWN. MAC shares and read counts are not timing or recoverable benefit.',
        'decision': decision, 'runs': results,
    }
    (HERE / 'review-output-underflow-domain.json').write_text(json.dumps(report, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    lines = ['# 三个下溢数学域：完整输入扫描判别', '',
             '只读重建已执行901/902/904的完整A/B字，使用此前与官方4b7 Git blob一致的原生成器与精确复现计划。逐数组完整max exponent、finiteScale、NaN/Inf计数与全字节SHA均在JSON；不是prefix最大值。实际Lean数组dump/运行轨迹仍未保存，结果为源重建推断。', '',
             '|seed|域|命中case数|比当前固定域新增case|命中MAC份额|命中全scan词|miss早拒词|先A后B总读词|',
             '|---|---|---:|---|---:|---:|---:|---:|']
    for run in results:
        for policy, p in run['policies'].items():
            lines.append(f"|{run['seed']}|{policy}|{p['hit_count']}|{', '.join(p['new_vs_fixed43_cases']) or '无'}|{p['fraction_of_BMM_MAC_work']:.2%}|{p['hit_full_scan_words']}|{p['miss_words_for_A_then_B_early_reject']}|{p['all_case_words_for_A_then_B_scheme']}|")
    lines += ['', f'决定：**{decision}**。']
    if decision.startswith('PARK'):
        lines.append('这三组输入中扩大两次数学域均没有新增整矩阵命中，既无新增MAC覆盖，也无已知新增耗时覆盖；不值得仅为动态max证书增加完整扫描、max维护和新scan证明。保持6a69固定短路guard，后续只在出现实际不对称低指数输入的新证据时重访。')
    else:
        lines.append('存在新增数学域命中；JSON列全case与MAC，实际逐case时间仍UNKNOWN。新增证明/扫描是否值得需根据这些精确新增对象单独判断，不能由MAC份额直接采用。没有生成新Kernel。')
    lines += ['', '三个域均按实际raw exponent255拒绝任意NaN/Inf。scale空数组最大值按0处理；normal/subnormal/zero由实际word字段判定，不看family标签。mag1严格center−min(ctz,spread)。', '',
              '≤84域可复用现有任意UInt64 product的算术结论，但仍缺动态max扫描→每个读取scale界的证明和实际运行版本；≤100另缺24bit×24bit乘积界及round-to-even归零桥。', '',
              '表中miss读词数来自唯一的先A后B早拒方案：A有限max扫描中见非finite或scale>上限即拒绝；A完成后B按剩余额度拒绝。当前fixed用原Array.all。完整max统计所做的分析扫描与提案运行时扫描分列，不能混记。所有逐case时间、scan/max/fill耗时及收益均UNKNOWN。']
    (HERE / 'review-output-underflow-domain.md').write_text('\n'.join(lines) + '\n', encoding='utf-8')
    print(json.dumps({'state': report['state'], 'seconds': report['analysis_seconds'], 'decision': decision, 'extra84_MAC': additional84, 'extra100_MAC': additional100}), flush=True)

if __name__ == '__main__':
    main()
