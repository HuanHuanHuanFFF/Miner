"""Small reuse of the existing exact special-word model; never hardware/Lean evidence."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
ORACLE=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
spec=importlib.util.spec_from_file_location('r22_old_word_model',ORACLE)
O=importlib.util.module_from_spec(spec);spec.loader.exec_module(O)
one=0x3f800000; inf=0x7f800000; ninf=0xff800000; qnan=0xffc01234; snan=0xff800011
cases=[
 ('inf_times_zero',[inf],[0]),
 ('opposite_infinity_products',[inf,ninf],[one,one]),
 ('overflow_then_opposite_overflow',[0x7f7fffff,0xff7fffff],[0x7f7fffff,0x7f7fffff]),
 ('signed_zero_initial_add',[0x80000000],[one]),
 ('empty',[],[]),
 ('qnan_payload_first',[qnan],[one]),
 ('snan_payload_first',[snan],[one]),
 ('invalid_then_later_snan',[0,snan],[inf,one]),
 ('payload_then_invalid',[qnan,0],[one,inf]),
 ('canonical_qnan_input',[0x7fc00000],[one]),
]
rows=[]
for name,a,b in cases:
    raw=O.dot(a,b)
    native=O.dot(a,b,lambda x,y:O.native_model(O.add,x,y),lambda x,y:O.native_model(O.mul,x,y))
    safeA=all(not O.nan(x) for x in a);safeB=all(not O.nan(x) for x in b)
    if safeA and safeB:assert raw==native
    rows.append({'name':name,'A':[f'{x:08x}' for x in a],'B':[f'{x:08x}' for x in b],
                 'A_safe':safeA,'B_safe':safeB,'raw_dot':f'{raw:08x}','native_import_model':f'{native:08x}',
                 'equal':raw==native})
assert rows[0]['raw_dot']==rows[1]['raw_dot']==rows[2]['raw_dot']=='7fc00000'
assert rows[3]['raw_dot']=='00000000'
assert not rows[5]['equal'] and not rows[6]['equal'] and not rows[8]['equal']
assert rows[7]['equal'] and not rows[7]['A_safe']
stop_counterexample={'raw_B':[f'{x:08x}' for x in [snan,one,0x40000000]],
 'required_prepared_values':[f'{O.canon(x):08x}' for x in [snan,one,0x40000000]],
 'required_summary':False,'wrong_early_stop_size':1,'required_size':3}
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'state':'TEN_DIRECTED_OLD_MODEL_WITNESSES_CHECKED',
 'oracle_path':str(ORACLE.relative_to(ROOT)).replace('\\','/'),'oracle_sha256':hashlib.sha256(ORACLE.read_bytes()).hexdigest(),
 'rows':rows,'arbitrary_raw_seed_counterexample':{'empty_raw_seed':'ffc01234','raw_empty_result':'ffc01234','native_import':'7fc00000'},
 'summary_does_not_stop_conversion':stop_counterexample,
 'scope':'Ten exact source-model cases plus exact empty-seed/array-length counterexamples. No new native execution, Lean result, timing, full-domain empirical claim or changed T19 proof.'}
(HERE/'witnesses.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,indent=2))
