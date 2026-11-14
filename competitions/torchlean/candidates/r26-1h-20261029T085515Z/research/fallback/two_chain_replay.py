from pathlib import Path
import datetime,hashlib,json,random
import replay_words as r

HERE=Path(__file__).resolve().parent

def pairs(a,b,n,i):
    even=odd=0
    for j in range(n):
        even=(even+r.extend32(a[i+2*j])*r.extend32(b[i+2*j]))&r.MASK
        odd=(odd+r.extend32(a[i+2*j+1])*r.extend32(b[i+2*j+1]))&r.MASK
    return (even+odd)&r.MASK

def run(a,b,two):
    lo=hi=0
    n=len(a)
    for j in range(n//16):
        q=pairs(a,b,8,j*16) if two else r.block(a,b,16,j*16)
        lo,hi=r.merge(lo,hi,q)
    if n%16:
        lo,hi=r.merge(lo,hi,r.block(a,b,n%16,n//16*16))
    return lo,hi

rows=[]
for kind in ('normal','sparse'):
    lines=(HERE/f'word-fixture-{kind}.txt').read_text(encoding='utf-8').splitlines()
    n,count=map(int,lines[:2]);x,w=([int(v) for v in line.split(',')] for line in lines[2:4])
    _,a=r.align(x)
    for j in range(count):
        _,b=r.align(w[j*n:(j+1)*n])
        single=run(a,b,False);two=run(a,b,True)
        assert single==two==r.blocked(a,b)
        rows.append({'kind':kind,'row':j,'word128':list(two)})
randomizer=random.Random(202610290938)
for n in (0,1,2,15,16,17,31,32,33,63,64,65):
    a=[randomizer.randrange(-(1<<29)+1,1<<29)&0xffffffff for _ in range(n)]
    b=[randomizer.randrange(-(1<<29)+1,1<<29)&0xffffffff for _ in range(n)]
    assert r.canblock(a,b)
    assert run(a,b,False)==run(a,b,True)==r.blocked(a,b)
out=HERE/'WordBlockTwoChains.lean'
out.write_text((HERE/'WordBlockCarrier.lean').read_text(encoding='utf-8')+'\n'+(HERE/'BlockTwoChains.lean.inc').read_text(encoding='utf-8'),encoding='utf-8',newline='\n')
receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
         'status':'FOLLOW_ON_FINITE_REPLAY_NOT_NEW_CI_REQUEST',
         'records':rows,'tail_lengths':[0,1,2,15,16,17,31,32,33,63,64,65],
         'source_sha256':hashlib.sha256(out.read_bytes()).hexdigest(),
         'scope':'Same cached factors; pairs use two independent UInt64 accumulation arguments; one-chain and two-chain controls both omit empty tail merge',
         'source_changes':'No existing primary runtime/carrier/cost source modified',
         'missing':['Compile','codegen allocation','cycle/ILP evidence','paired native measurement'],
         'warning':'This is a continuation of block16 mechanism, not a second independent high-ceiling route; wide bands are the distinct route.'}
(HERE/'two-chain-replay.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'matching_public_dots':len(rows),'tail_lengths':receipt['tail_lengths'],'sha256':receipt['source_sha256']},indent=2))
