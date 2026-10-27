"""Exact-input MainFull comparison; C equality can park, C inequality is not speed."""
from pathlib import Path
from collections import Counter
import argparse,hashlib,json,re,datetime
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
BASE=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168024176/download-97e5567f5b7c4fc2a261a6d6dac40edc/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r15-dev-packed-b2-1'
sha=lambda b:hashlib.sha256(b).hexdigest()
def load(diag,expected):
    idx=json.loads((diag/'candidate-c-index.json').read_text()); sources={};records=[]
    for r in idx:
        p=diag/r['file'];b=p.read_bytes()
        assert sha(b)==r['sha256'] and r['kernel_sha256']==expected,(str(p),expected)
        assert len(b)<8_000_000
        sources[r['module']]=b.decode()
        records.append({'path':str(p),'sha256':sha(b),'module':r['module']})
    return sources,records
def extract(txt,symbol):
    m=re.search(r'^LEAN_EXPORT [^\n]+\b'+re.escape(symbol)+r'\([^\n]*\)\{',txt,re.M);assert m,symbol
    pos=m.end();depth=1
    while depth:
        if txt[pos]=='{':depth+=1
        elif txt[pos]=='}':depth-=1
        pos+=1
    return txt[m.start():pos]
def select(sources):
    text=sources['MainFull'];main=extract(text,'_lean_main')
    m=re.search(r'lp_competition_Bench_Suite_run\(([^;]+)\)',main);assert m
    args=[v.strip() for v in m.group(1).split(',')]
    closures=dict(re.findall(r'static const lean_closure_object (\w+)_value = .*?\.m_fun = \(void\*\)(\w+)',text))
    rows={}
    for op,var in zip(['add','mul'],args[:2]):
        defs=list(re.finditer(re.escape(var)+r' = \(\(lean_object\*\)\((\w+)\)\);',main[:m.start()]));assert defs,var
        closure=defs[-1].group(1);boxed=closures[closure]
        wrapper=extract(text,boxed)
        targets=re.findall(r'= (lp_competition_main___lam__\d+)\(',wrapper);assert len(targets)==1,targets
        symbol=targets[0];body=extract(text,symbol)
        rows[op]={'closure':closure,'boxed':boxed,'unboxed':symbol,'body':body}
    return rows
def normalize(body):
    variables={}
    def v(m):
        x=m.group();variables.setdefault(x,'var'+str(len(variables)));return variables[x]
    b=re.sub(r'\bv_[A-Za-z0-9_]+',v,body)
    b=re.sub(r'lp_competition_main___lam__\d+','SELECTED_MAIN_CALLBACK',b)
    return re.sub(r'\s+',' ',b).strip()
def main():
    p=argparse.ArgumentParser();p.add_argument('--input',type=Path,required=True);p.add_argument('--diag',type=Path,required=True);p.add_argument('--sha',required=True);p.add_argument('--label',required=True);a=p.parse_args()
    assert re.fullmatch(r'[a-zA-Z0-9_-]+',a.label)
    assert sha(a.input.read_bytes())==a.sha
    before,oldrecords=load(BASE,'622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58')
    after,newrecords=load(a.diag,a.sha)
    old=select(before);new=select(after);results={}
    output=HERE/('codegen-'+a.label);output.mkdir(exist_ok=True)
    for op in ['add','mul']:
        x,y=old[op],new[op];xb,yb=x['body'],y['body']
        (output/(op+'-selected.c')).write_text(yb+'\n',encoding='utf-8')
        results[op]={k:v for k,v in y.items() if k!='body'}
        results[op].update(old_raw_sha256=sha(xb.encode()),new_raw_sha256=sha(yb.encode()),
          normalized_body_equal=normalize(xb)==normalize(yb),
          old_C_if_sites=len(re.findall(r'\bif\s*\(',xb)),new_C_if_sites=len(re.findall(r'\bif\s*\(',yb)),
          old_primitive_sites=dict(Counter(re.findall(r'\b(lean_\w+)\(',xb))),
          new_primitive_sites=dict(Counter(re.findall(r'\b(lean_\w+)\(',yb))))
    result={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'candidate_sha256':a.sha,
      'input':str(a.input),'baseline_records':oldrecords,'candidate_records':newrecords,'operations':results,
      'scope':'Original diagnostic C only; selected closures derived from actual BENCH_PLAN branch. Variable names and callback lambda numbers normalized, no arithmetic/control changes normalized away. Static site counts are not dynamic work.',
      'decision':('CONTROL_EXACT_SELECTED_MATCH' if a.sha=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
                  else 'PARK_C_SAME' if all(r['normalized_body_equal'] for r in results.values()) else 'OPTIMIZED_MAINFULL_ASM_REQUIRED'),
      'performance':'UNKNOWN_NOT_MEASURED'}
    (output/'comparison.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'decision':result['decision'],'operations':{k:v['normalized_body_equal'] for k,v in results.items()}}))
if __name__=='__main__':main()
