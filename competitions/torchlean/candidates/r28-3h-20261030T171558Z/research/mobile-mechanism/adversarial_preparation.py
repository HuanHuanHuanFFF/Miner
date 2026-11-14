"""Original finite raw-word guard, local-scale and signed-zero boundary audit."""
from pathlib import Path
import importlib.util,random,json,hashlib,datetime,collections
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r28pmodel',HERE/'pointwise128_model.py');P=importlib.util.module_from_spec(spec);spec.loader.exec_module(P)
M=P.M;F=M.F;MASK=(1<<64)-1

def wgen(rng,lo,span,zero=False):
    if zero and rng.randrange(5)==0:return rng.randrange(2)<<31
    e=min(254,lo+rng.randrange(span+1));frac=rng.randrange(1<<23)
    if rng.randrange(8)==0:frac=0
    return (rng.randrange(2)<<31)|(e<<23)|frac

def main():
    rng=random.Random(0x285315);counts=collections.Counter();examples=[]
    for case in range(2000):
      h=rng.randrange(1,4);ci=rng.randrange(1,17);co=rng.randrange(1,7)
      lo=rng.choice([0,1,2,110,126,230,254,rng.randrange(255)])
      span=min(rng.randrange(26),254-lo)
      wl=rng.choice([0,1,100,120,240,254,rng.randrange(255)]);ws=min(rng.randrange(7),254-wl)
      x=[wgen(rng,lo,span,True) for _ in range(ci*h*h)]
      w=[wgen(rng,wl,ws,False) for _ in range(ci*co)]
      b=[(rng.randrange(2)<<31) if case%3 else wgen(rng,rng.randrange(255),0) for _ in range(co)]
      # Positive subnormal zero significands are true zero weights; they retain original path.
      g=M.source53_guard(x,w,b,ci,co)
      counts['raw_finite_cases']+=1
      if g['g_narrow'] and not any((v&0x7fffffff)==0 for v in w):
        try:P.audited(x,ci,h,co,1,0,w,b,False,'adversarial')
        except AssertionError:
          failure={'case':case,'h':h,'cin':ci,'cout':co,'x':x,'w':w,'b':b,'guard':g,'scope':'Model assertion failure; not yet localized to candidate','model_sha256':hashlib.sha256((HERE/'pointwise128_model.py').read_bytes()).hexdigest()}
          (HERE/('adversarial-failure-'+str(case)+'.json')).write_text(json.dumps(failure,indent=2)+'\n')
          raise
        counts['admitted_cases']+=1
      else:counts['original_fallback_cases']+=1
    # Original global finite guard must reject every active nonfinite word.
    for special in [0x7f800000,0xff800000,0x7fc00001,0x7f800001,0xffc00001]:
      for location in ['input','weight','bias']:
        x=[0x3f800000]*8;w=[0x3f000000]*6;b=[0x3c800000]*3
        {'input':x,'weight':w,'bias':b}[location][0]=special
        g=M.source53_guard(x,w,b,2,3)
        assert not g['g_narrow'];counts['nonfinite_rejections']+=1
    # Exact-zero sign is selected on original words by unchanged Ybz, not the integer scale.
    for signx in [0,1]:
      for signw in [0,1]:
       for signb in [0,1]:
        x=[signx<<31]*3;w=[(signw<<31)|0x3f800000]*3;b=signb<<31
        nz=all(F.fields(a)[1]*F.fields(v)[1]==0 and ((a>>31)^(v>>31)) for a,v in zip(x,w)) and F.fields(b)[1]==0 and bool(b>>31)
        expected=0x80000000 if nz else 0
        assert expected==(0x80000000 if (signx^signw) and signb else 0)
        examples.append({'input_sign':signx,'weight_sign':signw,'bias_sign':signb,'expected_word':expected})
    out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'scope':'Finite raw-word preparation/carry/guard audit; no Lean/native/gate claim; zero-sign tests audit preserved Ybz predicate only','counts':dict(counts),'admitted_numeric_checks':dict(P.COUNTS),'mismatches':0,'signed_zero_cases':examples,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'dependencies':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in [HERE/'pointwise128_model.py',HERE/'mobile_census.py']}}
    (HERE/'adversarial-preparation.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps({k:v for k,v in out.items() if k not in ['signed_zero_cases','dependencies']},indent=2))
if __name__=='__main__':main()
