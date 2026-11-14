from pathlib import Path
import datetime,hashlib,json
import replay_words as r
import model_span_probe as m

HERE=Path(__file__).resolve().parent

def rawdecode(w):
    exponent=(w>>23)&255
    return (-1 if w>>31 else 1),(w&0x7fffff)+(0 if exponent==0 else 1<<23),(0 if exponent==0 else exponent-1)

def scan(words):
    low=high=0;seen=False;finite=True
    for w in words:
        _,mant,idx=rawdecode(w)
        active=mant!=0
        if active and (not seen or idx<low):low=idx
        if active and (not seen or high<idx):high=idx
        seen=seen or active
        finite=finite and ((w>>23)&255)!=255
    return low,high,seen,finite

def prepare(words):
    low,high,seen,finite=scan(words)
    if not finite or high-low>7:return None
    values=[]
    for w in words:
        s,mant,idx=rawdecode(w)
        mag=mant*(1<<max(0,idx-low))
        values.append((s*mag)&0xffffffff)
    return {'values':values,'base':low,'maximum':max(map(r.magn32,values),default=0)}

records=[]
for kind in ('normal','sparse'):
    file=HERE/f'word-fixture-{kind}.txt'
    lines=file.read_text(encoding='utf-8').splitlines()
    n,outputs=map(int,lines[:2])
    x,w,bias,expected=([int(v) for v in line.split(',')] for line in lines[2:6])
    assert len(x)==n and len(w)==n*outputs and len(bias)==len(expected)==outputs
    a=prepare(x);assert a
    for j in range(outputs):
        b=prepare(w[j*n:(j+1)*n]);assert b
        assert r.canblock(a['values'],b['values'])
        sg,mb,idx=m.decode(bias[j]);delta=idx+149-a['base']-b['base'];assert delta>=0
        actual=[]
        for blocked in (False,True):
            pair=r.blocked(a['values'],b['values']) if blocked else r.each(a['values'],b['values'])
            total=r.signed128(pair)+sg*(mb<<delta)
            word=m.round_rat(m.Fraction(total)*m.Fraction(2)**(a['base']+b['base']-298))
            relu=0 if word&0x80000000 else word
            assert relu==expected[j]
            actual.append(relu)
        records.append({'kind':kind,'row':j,'expected_relu':expected[j],'each':actual[0],
                        'block':actual[1],'baseA':a['base'],'baseB':b['base'],
                        'maxA':a['maximum'],'maxB':b['maximum']})
special=[]
for words in ([],[0],[0x80000000],[0x7f800000],[0xff800000],[0x7fc00001],
              [0x3f800000,0x43800000],[1,0x3f800000]):
    p=prepare(words)
    special.append({'words':words,'accepted':p is not None})
    if any(((w>>23)&255)==255 for w in words): assert p is None
receipt={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
         'status':'COST_DRIVER_PREPARE_AND_OUTPUT_FINITE_REPLAY_ONLY',
         'records':records,'special_prepare_cases':special,
         'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (Path(__file__),HERE/'WordBlockCostMain.lean',HERE/'CostDriver.lean.inc',HERE/'word-fixture-normal.txt',HERE/'word-fixture-sparse.txt')},
         'limits':['Not actual Lean execution','Fixed first-layer ReLU domain','Rejected preparation returns sentinel only in diagnostic driver','Full all-input guard/zero obligation remains separate']}
(HERE/'cost-preflight.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'matching_rows':len(records),'special_prepare_cases':special},indent=2))
