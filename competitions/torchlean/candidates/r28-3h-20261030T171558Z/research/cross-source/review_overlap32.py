"""Independent review of parent1939 overlap32 arithmetic and proof interface.

No candidate, CI or frozen source changes. Uses direct Python integer sums,
the old signed128 carry update, and separately reconstructed overlap words.
"""
from pathlib import Path
from datetime import datetime,timezone
import hashlib
import importlib.util
import json
import random
import sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
B=1<<32;M=1<<64;MASK=M-1;MASK128=(1<<128)-1


def signed(word):return word-M if word>>63 else word
def ash32(word):return (signed(word)//B)&MASK


def overlap(values,unsigned=False):
    low=qsum=0
    for value in values:
        word=value&MASK
        low=(low+word)&MASK
        qsum=(qsum+((word>>32)if unsigned else ash32(word)))&MASK
    a=(qsum<<32)&MASK
    high=((qsum>>32)if unsigned else ash32(qsum))+int(low<a)
    return high&MASK,low


def old_signed(values):
    high=low=0
    for value in values:
        p=value&MASK;next_low=(low+p)&MASK
        high=(high-(p>>63)+int(next_low<low))&MASK;low=next_low
    return high,low


def repeated_closed(n,p,unsigned=False):
    word=p&MASK
    q=(word>>32)if unsigned else signed(word)//B
    low=(n*word)&MASK;qsum=(n*q)&MASK;a=(qsum<<32)&MASK
    high=(((qsum>>32)if unsigned else ash32(qsum))+int(low<a))&MASK
    return (high<<64)|low


def main():
    rng=random.Random(28003239);checked=0
    edges=[-(1<<63),-(1<<63)+1,-B-1,-B,-B+1,-1,0,1,B-1,B,B+1,(1<<63)-1]
    for n in [0,1,2,3,7,16,31,32,33,127,1024]:
        for _ in range(32):
            a=[rng.choice(edges)if rng.randrange(2)else signed(rng.getrandbits(64))for _ in range(n)]
            h,l=overlap(a)
            assert (h,l)==old_signed(a)
            assert (h<<64)|l==sum(a)&MASK128
            u=[rng.getrandbits(64)for _ in range(n)];h,l=overlap(u,True)
            assert (h<<64)|l==sum(u)&MASK128
            checked+=2
    # The parent's <B guard is sufficient, not a maximal length theorem.
    signed_boundary=repeated_closed(B,-(1<<63))
    assert signed_boundary==(B*(-(1<<63)))&MASK128
    signed_bad=repeated_closed(B+1,-(1<<63))
    assert signed_bad!=((B+1)*(-(1<<63)))&MASK128
    unsigned_boundary=repeated_closed(B+1,M-1,True)
    assert unsigned_boundary==((B+1)*(M-1))&MASK128
    unsigned_bad=repeated_closed(B+2,B-1,True)
    assert unsigned_bad!=((B+2)*(B-1))&MASK128
    # Lift the arithmetic/logical mixup to source36's real finite Float32 domain.
    util=HERE.parents[2]/'r27-5h-20261029T194443Z/research/fp-proof/census/formula_snapshot.py'
    spec=importlib.util.spec_from_file_location('overlap_float_words',util);f=importlib.util.module_from_spec(spec);spec.loader.exec_module(f)
    p=f.key(0x80000001)*f.key(0x00000001);assert p==-1
    correct=f.round_ratio(p,1,-298)
    wrong_h,wrong_l=overlap([p],True);wrong_sum=(wrong_h<<64)|wrong_l
    wrong=f.round_ratio(wrong_sum,1,-298)
    assert correct==0x80000000 and wrong==0
    # Naively interpreting an old high-word parameter as Q changes valid old
    # helper states. This is not a counterexample to the zero-start algorithm.
    old_high=2;old_low=0;q=old_high
    reconstructed=(ash32(q)+int(old_low<((q<<32)&MASK)))&MASK
    old_value=(old_high<<64)|old_low;new_value=(reconstructed<<64)|old_low
    assert old_value==1<<65 and new_value==1<<64
    assert old_value<=4*(1<<63)  # old ZMD prefix mass bound at k=n=4
    parent=HERE.parent/'overlap-accumulator/OVERLAP32.md'
    result={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'INDEPENDENT_PAPER_AND_WORD_REVIEW_NOT_LEAN_NATIVE',
      'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'parent_document_sha256':hashlib.sha256(parent.read_bytes()).hexdigest(),
      'array_checks':checked,'verdict':'Parent signed/unsigned formulas and current n<2^32 premise accepted; no counterexample within premise',
      'boundary_refinement':{'signed_n_equals_2pow32':'still universally safe','signed_n_2pow32_plus1_counterexample_p':str(-(1<<63)),
        'unsigned_n_2pow32_plus1':'still universally safe','unsigned_n_2pow32_plus2_counterexample_p':B-1,
        'decision':'No guardchange needed; source36n<2^20 farinside. Call currentbound sufficient, notsharp.'},
      'actual_source36_negative_zero_counterexample':{'linear_shape':[2,1,1],'x':['80000001','80000001'],'w':['00000001'],'bias':['00000000'],
        'lo':0,'d':0,'span':0,'product_signed':-1,'old_prepared_domain':True,
        'correct_outputs':['80000000','80000000'],'wrong_logical_shift_outputs':['00000000','00000000'],
        'scope':'Finite mathematical source36 witness, not execution of a newLeanKernel'},
      'old_helper_invariant_counterexample':{'k':4,'n':4,'h':2,'l':0,'old_P':str(old_value),'reinterpreted_Q_result':str(new_value),
        'explanation':'OldZMD allows a generic prefixstate representedby h*2^64+l. The newsecondregister is Q, so do notinherit that invariant. Actualkernels startzero; this doesnotrefute the algorithm or oldkernel.'},
      'remaining':['Actualp producer equality andsigned/unsigned choice','NewL/Q/R loop invariant, not oldh/l invariant','Exactsource proof/bytebudget','Full nativecost against same source36/norm26 baseline; modernADC mayalreadybeefficient']}
    (HERE/'overlap32-review.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8');print(json.dumps({k:result[k]for k in ['array_checks','verdict','actual_source36_negative_zero_counterexample','old_helper_invariant_counterexample']},indent=2))


if __name__=='__main__':main()
