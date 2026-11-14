"""Read-only metadata arithmetic. No LCG draws, tensors, inference or timings."""
from pathlib import Path
from fractions import Fraction as F
from math import isqrt
from datetime import datetime, timezone
import hashlib, json

HERE = Path(__file__).resolve().parent
ROUND = HERE.parents[2]
SOURCE = ROUND / 'development-broad/torchlean-source/lean/bench/ExactSuite.lean'
raw = SOURCE.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '99574dc2925d7db5cba56c4452cc1fc9b6fa27625e9ba81fde9f9b74db147530'
def power(e):
    return F(2**e) if e >= 0 else F(1, 2**(-e))
def log2floor(x):
    e = x.numerator.bit_length() - x.denominator.bit_length()
    return e - (x < power(e))
def round32positive(x):
    # All operands here are normal positive scalar preparation bounds.
    e = log2floor(x)
    assert -126 <= e <= 127
    unit = power(e - 23)
    z = x / unit
    q, r = divmod(z.numerator, z.denominator)
    q += 2*r > z.denominator or (2*r == z.denominator and q % 2 == 1)
    return q * unit
def ceil_log2(n):
    return (n-1).bit_length()
def stepped(lo, count, step=1):
    return {lo + d*step for d in range(count)}
def edges(values):
    return {v+s for v in values for s in [-1,1]}

profiles = {}
for profile in ['legacy','typical','scale','boundary']:
    if profile == 'legacy':
        inp,h,h2 = stepped(256,529),stepped(64,193),stepped(32,97)
        ni,c1,c2,T,C = stepped(128,385),stepped(4,5),stepped(8,9),stepped(8,9),stepped(16,33)
    elif profile == 'typical':
        inp,h,h2 = stepped(256,67,8),stepped(64,25,8),stepped(32,13,8)
        ni,c1,c2,T,C = stepped(128,49,8),stepped(4,5),stepped(8,9),stepped(8,9),stepped(16,9,4)
    elif profile == 'scale':
        inp,h,h2 = stepped(128,57,16),stepped(32,7,16),stepped(16,4,16)
        ni,c1,c2,T,C = stepped(64,45,16),stepped(4,3),stepped(8,5),stepped(20,7,2),stepped(12,9)
    else:
        inp,h,h2 = edges(stepped(256,67,8)),edges(stepped(64,25,8)),edges(stepped(32,13,8))
        ni,c1,c2,T,C = edges(stepped(128,49,8)),stepped(5,2,2),stepped(9,4,2),stepped(9,5,2),stepped(15,10,2)
    profiles[profile] = {'mlp':[('first',inp,True,True),('hidden1',h,True,False),('hidden2',h2,True,False)],
        'nmlp':[('first',ni,True,True),('hidden1',h,True,False),('hidden2',h2,True,False)],
        'cnn':[('first',{27},True,True),('later_conv',{9*c for c in c1},True,False),('classifier',c2,True,False)],
        'mnet':[('first',{27},True,True),('depthwise',{9},True,False),('pointwise1',c1,True,False),
                ('pointwise2',c2,True,False),('classifier',c2,True,False)],
        'mixer':[('token_gemm',T,False,False),('channel1',C,True,False),
                 ('channel2',{2*c for c in C},True,False),('classifier',{t*c for t in T for c in C},True,False)]}
gmax = F(2**24-1,2**24)
rows = []
for profile,families in profiles.items():
    for family,groups in families.items():
        for layer,ks,biased,initial in groups:
            data = []
            for k in sorted(ks):
                scale = round32positive(F(4,max(1,isqrt(k))))
                max_weight = round32positive(gmax*scale)
                weight_field = log2floor(max_weight)+127
                L = ceil_log2(k+int(biased))
                H = max(125+weight_field-1,243 if biased else 0)
                H_finite = max(253+weight_field-1,243 if biased else 0)
                data.append(dict(k=k,n=k+int(biased),L=L,weight_field_upper=weight_field,
                    H_initial_upper=H if initial else None,
                    initial_width_condition_E_sufficient=H+2*L-278 if initial else None,
                    H_finite_upper=H_finite,H_plus_2L_finite_upper=H_finite+2*L,
                    bias_increases_L=biased and ceil_log2(k+1)>ceil_log2(k)))
            def bounds(key):
                vals=[d[key] for d in data if d[key] is not None]
                return [min(vals),max(vals)] if vals else None
            rows.append(dict(profile=profile,family=family,layer=layer,biased=biased,initial=initial,
                k=bounds('k'),n=bounds('n'),L=bounds('L'),weight_field_upper=bounds('weight_field_upper'),
                initial_H_upper=bounds('H_initial_upper'),
                initial_width_condition_E_sufficient=bounds('initial_width_condition_E_sufficient'),
                finite_H_plus_2L_upper=bounds('H_plus_2L_finite_upper'),
                power_of_two_k_affected_by_bias=[d['k'] for d in data if d['bias_increases_L']],
                individual_scalar_metadata=data))
result=dict(observed_at_utc=datetime.now(timezone.utc).isoformat(),phase_first_utc='2026-10-28T23:41:03Z',
    window_start_utc='2026-10-28T20:38:56Z',shared_deadline_utc='2026-10-29T03:38:56Z',
    source=str(SOURCE),source_sha256=hashlib.sha256(raw).hexdigest(),source_git_blob='f78b33ea5ac54b5210bcaa19a03b70e93f5c5f6d',
    official_commit='accb82b6e2adeda1b41a57a260d68fb3879c427e',
    meaning='Support-envelope metadata only. Cartesian token/channel envelopes may include seed-incompatible combinations. No LCG seeds or tensor elements are generated.',
    universal_weighted_dot_bound=dict(fan_in=[4,1024],bias_count_max=1025,L_max=11,
        nonzero_weight_fields=[118,127],bias_fields=[113,118],bias_product_index_max=243,
        finite_activation_index_max=253,H_upper=379,H_plus_2L_upper=401,
        all_normal_q_hard_rejection_threshold=406),
    limitations=['Necessary width condition is not certificate acceptance.',
       'Refined tables use exact positive scalar RNE arithmetic, not a Lean proof or performance measurement.',
       'Nonfinite or nonzero-subnormal activations may fail the current widening guard; no all-layer Domain invariant is asserted.',
       'Norm square-moment operands are not weights and are excluded from this weighted-dot bound.',
       'H from retained nonzero products and conservative all-pair/shared maxima must be measured separately.'],
    tokens='UNKNOWN',cached_input_tokens='UNKNOWN',rows=rows)
(HERE/'native-midpoint-structural-bounds.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'row_count':len(rows),'largest_finite_H_plus_2L':max(r['finite_H_plus_2L_upper'][1] for r in rows),
    'first_layers':[{k:v for k,v in r.items() if k!='individual_scalar_metadata'} for r in rows if r['initial'] and r['profile']!='legacy']},indent=2))
