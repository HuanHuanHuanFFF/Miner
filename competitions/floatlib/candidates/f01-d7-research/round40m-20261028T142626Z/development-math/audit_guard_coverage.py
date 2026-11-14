"""Lightweight exact-source/guard table audit; never claims multiplication proof."""
from pathlib import Path
from collections import Counter
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
old=ROOT/'competitions/floatlib/candidates/f01-r22-dev-outline-public1/Kernel.lean'
new=ROOT/'competitions/floatlib/candidates/f01-r23-dev-outline-public1/Kernel.lean'
oldraw,newraw=old.read_bytes(),new.read_bytes()
sha=lambda b:hashlib.sha256(b).hexdigest()
assert sha(oldraw)=='88cdf318d952d74df95ecabed5e2bbadeab76d4827af1c4e5fd88e43d9d8f054'
assert sha(newraw)=='f90d42e346a1634ffeb537ea7e9980e0a91baea8499dc6c2235da5ab8fe0e85f'
a,b=oldraw.decode(),newraw.decode()
next_decl=re.compile(r'(?m)^(?:@\[[^\n]*\] )?(?:private )?(?:def|theorem) |^end |^namespace ')
def block(text,name,kind):
    match=re.search(r'(?m)^(?:@\[[^\n]*\] )?'+kind+' '+re.escape(name)+r'\b',text)
    assert match
    end=next_decl.search(text,match.end())
    return text[match.start():end.start() if end else len(text)].rstrip()
checks={}
for name,kind in [('normalCore','def'),('guardedMul','def'),('diagnosticEntry','def'),('retainedMul','def'),
                  ('normal_guard','theorem'),('sum_guard','theorem'),('guardedMul_spec','theorem')]:
    aa,bb=block(a,name,kind),block(b,name,kind)
    assert aa==bb,name
    checks[name]={'byte_identical':True,'sha256':sha(bb.encode())}
old_footer=a[a.rindex('\nnamespace Submission\n'):]
new_footer=b[b.rindex('\nnamespace Submission\n'):]
assert old_footer==new_footer
assert 'R19BiasBase.R19DirectBias.guardedMul R19BiasBase.R19DirectBias.retainedMul x y' in new_footer
assert 'R19BiasBase.R19DirectBias.guardedMul_spec R19BiasBase.R19DirectBias.retainedMul R19BiasBase.mul_spec x y' in new_footer
checks['whole_public_Submission_footer']={'byte_identical':True,'sha256':sha(new_footer.encode())}

MASK=(1<<32)-1
classifications=Counter()
accepted=Counter()
for eu in range(256):
    for ev in range(256):
        input_guard=((eu-1)&MASK)<=253 and ((ev-1)&MASK)<=253
        s=(eu+ev)&MASK
        sum_guard=((s-128)&MASK)<=252
        take=input_guard and sum_guard
        domain=1<=eu<=254 and 1<=ev<=254 and 128<=eu+ev<=380
        assert take==domain
        if take:
            classifications['normal_inputs_and_proved_normal_output_domain']+=1
            accepted[s]+=1
        elif not input_guard:
            classifications['fallback_zero_subnormal_or_nonfinite_input']+=1
        elif s<128:
            classifications['fallback_normal_inputs_low_exponent_sum']+=1
        else:
            assert s>380
            classifications['fallback_normal_inputs_high_exponent_sum']+=1
assert sum(classifications.values())==65536
assert set(accepted)==set(range(128,381))
assert (1<<23)**2==70368744177664
assert ((1<<24)-1)**2==281474943156225

record={'state':'STATIC_SOURCE_AND_EXHAUSTIVE_EXPONENT_GUARD_TABLE_PASS',
    'old_sha256':sha(oldraw),'new_sha256':sha(newraw),'exact_identity':checks,
    'enumerated_exponent_pairs':65536,'guard_matches_original_math_domain_for_all_pairs':True,
    'domain':'1<=eu,ev<=254 and 128<=eu+ev<=380; sign/fraction do not appear in guard',
    'classes':dict(classifications),'accepted_sum_pair_counts':dict(sorted(accepted.items())),
    'product_bounds':[70368744177664,281474943156225],
    'normal_position_bounds':[172,425],
    'range_reason':'46<=log2(product)<=47; s-2 in126..378; existing no_carry_at_47 controls normalized upper endpoint.',
    'fallback':'All other exponent cases use original retainedMul -> R19BiasBase.mul, unchanged generic hf specialization.',
    'sum_bmm_scope':'Public sum and bmm remain exact R19BiasBase aliases. This public experiment changes only the exposed mul wrapper.',
    'boundary_pairs':{str(s):accepted[s] for s in [128,129,379,380]},
    'typing':'NOT_RUN','axiom_audit':'NOT_RUN','kernel_replay':'NOT_RUN',
    'limitation':'Host guard arithmetic table and source identity only. No enumeration of mantissas/signs, no all-input MUL or official gate acceptance.'}
(HERE/'guard-coverage.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'state':record['state'],'enumerated_exponent_pairs':65536,'classes':record['classes'],
    'identical_source_blocks':list(checks),'boundary_pairs':record['boundary_pairs']}))
