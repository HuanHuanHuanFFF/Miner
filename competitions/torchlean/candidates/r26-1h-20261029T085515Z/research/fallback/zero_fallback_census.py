from pathlib import Path
import datetime,hashlib,json
import replay_words as r
import model_span_probe as m

HERE=Path(__file__).resolve().parent
records=[]
summaries=[]
for kind in ('normal','sparse'):
    lines=(HERE/f'word-fixture-{kind}.txt').read_text(encoding='utf-8').splitlines()
    n,outputs=map(int,lines[:2]);x,w,bias,expected=([int(v) for v in row.split(',')] for row in lines[2:6])
    ba,a=r.align(x)
    for j in range(outputs):
        bb,b=r.align(w[j*n:(j+1)*n])
        sg,mb,idx=m.decode(bias[j]);shift=idx+149-ba-bb
        assert shift>=0 and n<=1048576 and r.canblock(a,b)
        total=r.signed128(r.blocked(a,b))+sg*(mb<<shift)
        word=m.round_rat(m.Fraction(total)*m.Fraction(2)**(ba+bb-298))
        records.append({'kind':kind,'row':j,'exact_zero_fallback':total==0,
                        'rounded_zero':word&0x7fffffff==0,'relu_zero':expected[j]==0,
                        'body_integer_bits':abs(r.signed128(r.blocked(a,b))).bit_length(),
                        'bias_integer_bits':mb.bit_length()+shift if mb else 0,
                        'terminal_integer_bits':abs(total).bit_length()})
    rows=[q for q in records if q['kind']==kind]
    summaries.append({'kind':kind,'rows':len(rows),
                       'exact_zero_fallbacks':sum(q['exact_zero_fallback'] for q in rows),
                       'rounded_zeros':sum(q['rounded_zero'] for q in rows),
                       'relu_zeros':sum(q['relu_zero'] for q in rows),
                       'terminal_integer_bits_max':max(q['terminal_integer_bits'] for q in rows),
                       'bias_integer_bits_max':max(q['bias_integer_bits'] for q in rows)})
record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'status':'EXISTING_SEEN_FIXTURE_ZERO_GUARD_CENSUS_NOT_NEW_PERFORMANCE_EXPERIMENT',
        'scope':'Public typical seed42 first layer only; same frozen fixtures, no new confirmation data',
        'summaries':summaries,'records':records,
        'source_hashes':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in (Path(__file__),HERE/'ZeroSafeCaller.lean.inc',HERE/'word-fixture-normal.txt',HERE/'word-fixture-sparse.txt')},
        'limits':['Observed count is not a deployment probability','No elapsed cost','Does not relax original finite/zero guards']}
(HERE/'zero-fallback-census.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(summaries,indent=2))
