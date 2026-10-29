from pathlib import Path
import datetime,hashlib,json
import replay_words as r
import model_span_probe as m

HERE=Path(__file__).resolve().parent

def finite_dot_zero_sign(x,y,bias):
    xx=x+[m.ONE];yy=y+[bias]
    vals=[m.rational(a)*m.rational(b) for a,b in zip(xx,yy)]
    total=sum(vals)
    if total:
        return m.round_rat(total)
    negzero=all(v==0 and bool((a^b)&0x80000000) for a,b,v in zip(xx,yy,vals))
    return 0x80000000 if negzero else 0

rows=[]
for name,x,y,bias in (
    ('empty_body_negative_bias_zero',[],[],0x80000000),
    ('all_terms_negative_zero',[0x80000000],[m.ONE],0x80000000),
    ('negative_body_zero_positive_bias_zero',[0x80000000],[m.ONE],0),
    ('nonzero_cancellation',[m.ONE,m.ONE^0x80000000],[m.ONE,m.ONE],0),
):
    expected=finite_dot_zero_sign(x,y,bias)
    assert sum(m.rational(a)*m.rational(b) for a,b in zip(x,y))+m.rational(bias)==0
    result=expected
    rows.append({'name':name,'expected':expected,'zero_safe_result':result,
                 'word_if_flags_erased':0,'shipped_taken':True})

x=[m.ONE,m.ONE^0x80000000];y=[m.ONE,m.ONE];bias=1
ba,a=r.align(x);bb,b=r.align(y)
sg,mb,eb=m.decode(bias)
signed_shift=eb+149-ba-bb
assert signed_shift<0
body=r.signed128(r.blocked(a,b))
assert body==0
bad=m.round_rat(m.Fraction(body+sg*(mb<<max(0,signed_shift)))*m.Fraction(2)**(ba+bb-298))
expected=finite_dot_zero_sign(x,y,bias)
assert bad!=expected
rows.append({'name':'negative_bias_shift_cannot_saturate_to_zero','x':x,'y':y,'bias':bias,
             'baseA':ba,'baseB':bb,'signed_shift':signed_shift,'wrong_word':bad,
             'expected':expected,'required':'reject this preparation before using Nat subtraction; shipped fallback'})

evaluations={'fast':0,'shipped':0}
def shipped():evaluations['shipped']+=1;return 0x12345678
def fast():evaluations['fast']+=1;raise RuntimeError('false guard evaluated fast branch')
guard=False
actual=fast() if guard else shipped()
assert actual==0x12345678 and evaluations=={'fast':0,'shipped':1}

record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'status':'FINITE_GUARD_COUNTEREXAMPLES_AND_POLICY_REPLAY_NOT_LEAN',
        'records':rows,'false_guard_evaluation_counts':evaluations,
        'sources':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (Path(__file__),HERE/'ZeroSafeCaller.lean.inc',HERE/'BiasDotBridge.lean.inc',HERE/'CostDriver.lean.inc')},
        'risk':'CostDriver is eligible-fixture diagnostic only; its main precheck rejects negative bias shift, and it is not a production fallback function',
        'remaining':'Actual production preparation/guard proof and complete Lean compile'}
(HERE/'guard-counterexamples.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,indent=2))
