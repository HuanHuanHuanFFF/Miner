"""Generate a small public-profile C fixture; this does not compile or time it.

Run in this directory, then compile integer_cost_probe.c on a public runner.
The C probe compares identical finite input/output cases and has both prepared
and preparation-inclusive boundaries. These fixtures are exploration data.
"""
from pathlib import Path
import hashlib
import json
import model_span_probe as m

HERE=Path(__file__).resolve().parent


def c_array(name, xs):
    rows=[', '.join(f'0x{x:08x}u' for x in xs[i:i+12]) for i in range(0,len(xs),12)]
    return f'static uint32_t {name}[{len(xs)}] = {{\n  '+',\n  '.join(rows)+'\n};\n'


def run():
    seed=42;r=m.lcg(8,seed^0x5bd1e995)
    ni=(32+r[0]%67)*8;no=(8+r[1]%25)*8
    text=['/* Generated public typical seed42 fixture; finite-model exploration. */',
          f'#define INPUT_N {ni}',f'#define OUTPUT_N {no}','#define DATA_CASES 2']
    fixtures=[]
    for index,kind in enumerate(('normal','sparse')):
        x=m.gen(kind,ni,seed+999)
        w=m.weights(kind,seed,0,ni,ni*no)
        b=m.biases(seed,1,no)
        expected=[m.span_probe(x+[m.ONE],w[j*ni:(j+1)*ni]+[b[j]])[1]
                  for j in range(no)]
        for name,values in (('input',x),('weight',w),('bias',b),('expected',expected)):
            text.append(c_array(f'{name}_{index}',values))
        fixtures.append({'kind':kind,'n':ni,'m':no,'expected_words':expected})
    text.extend(['static uint32_t *inputs[DATA_CASES] = {input_0, input_1};',
                 'static uint32_t *weights[DATA_CASES] = {weight_0, weight_1};',
                 'static uint32_t *biases[DATA_CASES] = {bias_0, bias_1};',
                 'static uint32_t *expecteds[DATA_CASES] = {expected_0, expected_1};',
                 'static const char *case_names[DATA_CASES] = {"normal", "sparse"};'])
    header=HERE/'integer_cost_fixture.h'
    header.write_text('\n'.join(text)+'\n',encoding='utf-8',newline='\n')
    receipt={'status':'GENERATED_NOT_COMPILED_OR_TIMED',
             'profile':'typical','seed':seed,'fixture_header_bytes':header.stat().st_size,
             'fixture_header_sha256':hashlib.sha256(header.read_bytes()).hexdigest(),
             'generator_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
             'model_mirror_sha256':hashlib.sha256((HERE/'model_span_probe.py').read_bytes()).hexdigest(),
             'fixtures':fixtures,
             'excludes':['Wide path is a proven guard rejection in typical-first-layer-probe.json; no fake wide fallback cost.',
                         'No machine or Lean result; C candidate is a cost discriminator, not an accepted implementation.']}
    (HERE/'cost-fixture-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({k:receipt[k] for k in ('status','fixture_header_bytes','fixture_header_sha256')}))


if __name__=='__main__':run()
