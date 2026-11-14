"""Independent universal envelope and actual-word overflow witness.

Paper bounds plus finite endpoint evaluation. No Lean/native execution.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
from datetime import datetime, timezone

M=(1<<24)-1
MASK=(1<<64)-1

def main():
    here=Path(__file__).resolve().parent
    root=next(p for p in here.parents if (p/'AGENTS.md').is_file())
    helper=root/'competitions/torchlean/candidates/r27-5h-20261029T194443Z/research/board-frontier/norm_frontier.py'
    spec=importlib.util.spec_from_file_location('r28_exact_round',helper)
    f=importlib.util.module_from_spec(spec);spec.loader.exec_module(f)
    endpoints=[]
    for sw in range(7):
      for sx in range(32-sw):
        vcap=4*(M<<sx);ucap=9*(M<<sw)
        # floor of a negative V may have the extra unit: use ceil(abs(V)/2^25).
        hcap=(vcap+(1<<25)-1)//(1<<25)
        max_high=hcap*ucap
        low_bound=((1<<25)-1)*ucap
        assert 14*max_high<(1<<63)
        assert 14*low_bound<(1<<62)
        endpoints.append({'sx':sx,'sw':sw,'high_abs_bound':max_high,'low_abs_bound':low_bound})
    h=max(x['high_abs_bound'] for x in endpoints)
    assert h==9*M*M*(1<<8)
    assert ((1<<63)-1)//h==14
    # Fifteen channels, all high entries in a 4x4 tile; one low entry elsewhere
    # in each 5x5 channel fixes xm. All weights use the same nonzero base index.
    base_x=120;base_w=120;sx=31;cin=15
    raw_hi=((base_x+sx+1)<<23)|0x7fffff
    raw_low=((base_x+1)<<23)|0x7fffff
    raw_w=((base_w+1)<<23)|0x7fffff
    x=M<<31;w=M;v=4*x;u=9*w
    lo_sum=cin*(v% (1<<25))*u
    hi_sum=cin*(v//(1<<25))*u
    signed_hi=((hi_sum+(1<<63))&MASK)-(1<<63)
    exact_scaled=cin*v*u
    naive_scaled=lo_sum+(signed_hi<<25)
    assert lo_sum==0 and hi_sum>=(1<<63)
    assert exact_scaled%4==naive_scaled%4==0
    direct=cin*9*x*w
    wrong=naive_scaled//4
    assert exact_scaled==4*direct and wrong==direct-(1<<87)
    direct_word=f.round_ratio(direct,1,base_x+base_w-298)
    wrong_word=f.round_ratio(wrong,1,base_x+base_w-298)
    assert direct>0 and wrong<0 and direct_word!=wrong_word
    assert (raw_hi>>23)&255!=255 and (raw_w>>23)&255!=255
    out={'state':'PAPER_UNIVERSAL_BOUND_PLUS_FINITE_ENDPOINTS_AND_EXACT_WORD_COUNTEREXAMPLE',
      'at_utc':datetime.now(timezone.utc).isoformat(),
      'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
      'round_helper_sha256':hashlib.sha256(helper.read_bytes()).hexdigest(),
      'envelope_exponent_pairs':len(endpoints),'max_high_term_abs':str(h),
      'largest_uniform_signed64_block':14,'block8_conservative_safe':True,
      'block15_witness':{'shape':{'cin':15,'h':5,'w':5,'cout':1,'kh':3,'kw':3,'stride':1,'pad':1},
        'K':135,'input_xm':120,'weight_wm':120,'sx':31,'sw':0,
        'tile_description':'Each channel 5x5 is raw_hi except bottom-right raw_low; inner4x4 tile is constant raw_hi.',
        'raw_input_hi':hex(raw_hi),'raw_input_low':hex(raw_low),'raw_all_weights':hex(raw_w),'bias':'0x00000000','relu':False,
        'transformed_V':str(v),'transformed_U':str(u),'high_sum':str(hi_sum),'signed64_limit':str(1<<63),
        'exact_aligned_body':str(direct),'wrong_naive_aligned_body':str(wrong),
        'exact_output_word':f'{direct_word:08x}','naive_unblocked_output_word':f'{wrong_word:08x}'},
      'scope':'Refutes naive unblocked transformed signed64 reuse, NOT original source11. Actual source11 guard acceptance is source-derived, not executed. Exact integer/F32 oracle is Python, not Lean/native.',
      'missing':['actual guarded-array producer Lean proof','native new runtime','original all12 gate','full model cost'],
      'universal_argument':'Coordinate L1 norms<=4/9; for each fixed sw, ceil(4*M*2^sx/2^25)*9*M*2^sw increases with sx. Max sx=31-sw>=25 gives9*M^2*2^8. Fourteen terms fit signed63; fifteen same-sign terms attain overflow.'}
    (here/'block-bounds-result.json').write_text(json.dumps(out,indent=2)+'\n')
    print(json.dumps(out,indent=2))

if __name__=='__main__':main()
