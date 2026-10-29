"""Finite model of actual native32 roundRatScaled and power-cell boundaries."""
from pathlib import Path
import ast,hashlib,json,random,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
PUB=ROOT/'competitions/floatlib/candidates'
TARGET=PUB/'f01-r24-dev-scalar-power-cell2'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
M=1<<23
def rne(n,d):
    q,r=divmod(n,d);return q+int(2*r>d or 2*r==d and q%2==1)
def scaled(n,d,k):return (n<<k,d) if k>=0 else (n,d<<(-k))
def flog(n,d):
    k=n.bit_length()-d.bit_length()
    if k>=0:return k-1 if n<d<<k else k
    return k-1 if n<<(-k)<d else k
def actual_word(sign,n,d,e):
    s=0x80000000 if sign else 0
    if d==0:return 0x7fc00000
    if n==0:return s
    l=flog(n,d);t=l+e
    if t>127:return s|0x7f800000
    if t< -150:return s
    if t< -126:
        a,b=scaled(n,d,e+149);f=rne(a,b)
        return s|(min(f,M))
    a,b=scaled(n,d,23-l);m=rne(a,b)
    if m==1<<24:m=M;t+=1
    if t>127:return s|0x7f800000
    return s|((t+127)<<23)|(m-M)
def check(n,d,e):
    E=e+150
    return d>0 and 1<=E<=254 and (d*(2*M-1)<=2*n if E==1 else d*(4*M-1)<=4*n) and 2*n<=d*(2*M+1)
def main():
    for p in HERE.glob('*.py'):ast.parse(p.read_bytes())
    manifest=json.loads((TARGET/'manifest.json').read_bytes());assert sha(TARGET/'Kernel.lean')==manifest['candidate_sha256']
    assert (TARGET/'Kernel.lean').read_bytes().startswith((PUB/'f01-r15-dev-packed-b2-1/Kernel.lean').read_bytes())
    for item in manifest['components']:
        p=ROOT/item['path'];assert sha(p)==item['sha256'] and p.stat().st_size==item['bytes']
    trace=hashlib.sha256();count=accept=0
    for E in range(1,255):
        for d in (1,2,3,4,5,7,16,31,257,65537,(1<<24)-1):
            offsets=sorted(set([-d-2,-d,-d//2-1,-d//2,-d//2+1,-d//4-1,-d//4,-d//4+1,-1,0,1,d//4-1,d//4,d//4+1,d//2-1,d//2,d//2+1,d,d+2]))
            for delta in offsets:
                n=M*d+delta
                for sign in (False,True):
                    accepted=check(n,d,E-150);word=actual_word(sign,n,d,E-150);target=(0x80000000 if sign else 0)|(E<<23)
                    assert accepted==(word==target),(E,n,d,sign,hex(word),accepted)
                    count+=1;accept+=int(accepted);trace.update(f'{E},{n},{d},{int(sign)},{int(accepted)},{word}\n'.encode())
    rng=random.Random(24270327)
    for _ in range(100000):
        E=rng.randrange(1,255);d=rng.randrange(1,1<<32);n=M*d+rng.randrange(-d,d+1);sign=bool(rng.getrandbits(1))
        a=check(n,d,E-150);w=actual_word(sign,n,d,E-150);t=(0x80000000 if sign else 0)|(E<<23)
        assert a==(w==t);count+=1;accept+=int(a);trace.update(f'{E},{n},{d},{int(sign)},{int(a)},{w}\n'.encode())
    examples=[]
    for E,delta,d in ((1,-2,4),(1,-3,4),(2,-2,4),(2,-1,4),(2,2,4),(2,3,4),(254,-1,4)):
        n=M*d+delta;w=actual_word(False,n,d,E-150)
        wrong_symmetric=d*(2*M-1)<=2*n<=d*(2*M+1)
        examples.append({'E':E,'num':n,'den':d,'accepted':check(n,d,E-150),'actual_word':hex(w),'power_word':hex(E<<23),'wrong_uniform_half_cell':wrong_symmetric})
    assert examples[0]['accepted'] and examples[0]['actual_word']=='0x800000'
    assert not examples[2]['accepted'] and examples[2]['wrong_uniform_half_cell'] and examples[2]['actual_word']=='0xffffff'
    assert examples[3]['accepted'] and examples[3]['actual_word']=='0x1000000'
    for E in (0,1,2,254,255):
        assert not check(0,1,E-150) and not check(M,0,E-150)
    # The exact original source policy is checked without importing/running the gate.
    gate=(PUB/'f01-d7-research/official-policy/gate-4b7e838.raw').read_text();tree=ast.parse(gate)
    node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id=='BANNED' for t in n.targets))
    assert re.compile(ast.literal_eval(node.value.args[0])).search((TARGET/'Kernel.lean').read_text()) is None
    report={'status':'FINITE_POWER_CELL_MODEL_AND_LOCAL_PACKAGE_PASS_LEAN_NOT_RUN','source_sha256':manifest['candidate_sha256'],
        'cases':count,'accepted':accept,'trace_sha256':trace.hexdigest(),'examples':examples,
        'scope':'All254 normal target exponents with directed/random rational cells, minnormal and binade ties; numerical/source model only, not a universal Lean proof or actual native execution.',
        'Lean':'NOT_RUN','kernel_replay':'NOT_RUN','helper_AXIOM_audit':'NOT_RUN','performance':'NOT_RUN'}
    (HERE/'model-preflight-v2.json').write_bytes((json.dumps(report,indent=2)+'\n').encode())
    ready=json.loads((HERE/'READY-v2.json').read_bytes());ready['status']='READY_FOR_PARENT_MATH_REVIEW_AND_ORIGINAL_STATEMENT_REPLAY_AXIOMS';ready['model']='model-preflight-v2.json'
    (HERE/'READY-v2.json').write_bytes((json.dumps(ready,indent=2)+'\n').encode())
    print(json.dumps({'status':report['status'],'cases':count,'accepted':accept,'source':manifest['candidate_sha256'],'counterexample_wrong_half_at_E2':examples[2]}))
if __name__=='__main__':main()
