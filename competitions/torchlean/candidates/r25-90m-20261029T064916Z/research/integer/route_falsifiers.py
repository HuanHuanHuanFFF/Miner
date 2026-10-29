"""Small fixed counterexamples to unsafe relaxations of the integer routes."""
from pathlib import Path
from fractions import Fraction
import datetime
import hashlib
import json
import model_span_probe as m
from bucket64_discriminator import checked

HERE=Path(__file__).resolve().parent
M=1<<64


def signed64(w):return w if w<1<<63 else w-M


def aligned_terms(x,y):
    dx=[m.decode(w) for w in x];dy=[m.decode(w) for w in y]
    lowx=min(e for _,v,e in dx if v);lowy=min(e for _,v,e in dy if v)
    base=lowx+lowy
    terms=[sx*sy*(mx*my << (ix+iy-base)) if mx and my else 0
           for (sx,mx,ix),(sy,my,iy) in zip(dx,dy)]
    return base,terms


def run():
    records=[]
    lo=(121<<23)|0x7fffff;hi=(127<<23)|0x7fffff
    x=[lo]+[hi]*16;y=x[:];base,terms=aligned_terms(x,y)
    wrong=sum(signed64(sum(terms[i:i+16])%M) for i in range(0,len(terms),16))
    true=sum(terms)
    assert wrong!=true
    true_word=m.round_rat(Fraction(true)*Fraction(2)**(base-298))
    wrong_word=m.round_rat(Fraction(wrong)*Fraction(2)**(base-298))
    assert true_word!=wrong_word
    records.append({'name':'block16_requires_term59_not_term60','x':x,'y':y,
                    'span_sum':12,'unsafe_block':16,'safe_block':8,
                    'true_total':str(true),'unsafe_total':str(wrong),
                    'true_word':true_word,'unsafe_word':wrong_word})

    mag=((1<<24)-1)**2<<11
    terms=[(False,mag)]*33+[(True,mag)]*32
    r=checked(terms)
    assert r['state']=='bucket_overflow' and r['index']==32
    assert sum(-v if neg else v for neg,v in terms)==mag
    records.append({'name':'bucket_overflow_despite_small_final','repeat_positive':33,
                    'repeat_negative':32,'magnitude':str(mag),'final_total':str(mag),'checked':r})

    x=[0x80000000];y=[m.ONE]
    # ExactToolkit.dallNZ and incumbent.dotFn: nonempty && all zero negative terms.
    negzero=len(x)>0 and all(m.decode(a)[1]*m.decode(b)[1]==0 and
                            bool((a^b)>>31) for a,b in zip(x,y))
    spec_zero=0x80000000 if negzero else 0
    assert spec_zero!=0
    records.append({'name':'dropping_negative_zero_needs_fallback_or_flags',
                    'x':x,'y':y,'spec_zero_word':spec_zero,'naive_skip_word':0})

    x=[121<<23,127<<23];y=[m.ONE,m.ONE]
    base,terms=aligned_terms(x,y)
    true=sum(terms);wrong=2*(1<<46)
    assert true!=wrong
    records.append({'name':'per_band_shift_back_is_required','x':x,'y':y,
                    'band_delta':[0,6],'true_word':m.round_rat(Fraction(true)*Fraction(2)**(base-298)),
                    'missing_shift_word':m.round_rat(Fraction(wrong)*Fraction(2)**(base-298))})

    x=[0xbf800000];y=[m.ONE];base,terms=aligned_terms(x,y)
    word=sum(terms)%M
    assert signed64(word)==-(1<<46)
    records.append({'name':'unsigned_extension_changes_negative_block','x':x,'y':y,
                    'true_word':m.round_rat(Fraction(signed64(word))*Fraction(2)**(base-298)),
                    'wrong_word':m.round_rat(Fraction(word)*Fraction(2)**(base-298))})

    x=[1,0x7f7fffff];y=x[:];base,terms=aligned_terms(x,y)
    assert max(abs(t).bit_length() for t in terms)>128
    records.append({'name':'band_local_fit_does_not_imply_global128_fit','x':x,'y':y,
                    'global_base':base,'max_exact_term_bits':max(abs(t).bit_length() for t in terms),
                    'band_delta':[0,506],'requires':'Guard total global range and shift count before UInt128 reconstruction.'})
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
         'status':'EXACT_FIXED_COUNTEREXAMPLES_NOT_FORMAL_PROOF',
         'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
         'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest()
                          for p in (HERE/'model_span_probe.py',HERE/'bucket64_discriminator.py')},
         'records':records,
         'scope':'Finite integer/word and explicitly quoted zero-sign policy. No official gate or timing.'}
    (HERE/'route-falsifiers.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'cases':len(records),'names':[r['name'] for r in records]},indent=2))


if __name__=='__main__':run()
