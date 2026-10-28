from pathlib import Path
from datetime import datetime, timezone
import hashlib, json, re

HERE=Path(__file__).resolve().parent
ROUND=HERE.parents[1]
RAW=ROUND/'ci-runs/40586463637/download-9432e902177f4d09aae48d670123a126/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-runtime-cost1/runtime-cost'
result=json.loads((RAW/'result.json').read_text())
assert result['complete'] and result['measurement_complete']
data=[]
for pair in result['pairs']:
    seed=pair['seed']
    for block,(control_i,variant_i) in enumerate([(4,5),(7,6)]):
        control=json.loads((RAW/f'{seed}-{control_i}-control-rows.json').read_text())
        variant=json.loads((RAW/f'{seed}-{variant_i}-scaled-rows.json').read_text())
        keys=[k for k,v in control.items() if k.startswith('mul:') and v['timed']]
        groups={}
        for category in sorted({k.split(':')[1] for k in keys}):
            selected=[k for k in keys if k.split(':')[1]==category]
            c=sum(control[k]['best_ns'] for k in selected)
            v=sum(variant[k]['best_ns'] for k in selected)
            assert all(control[k]['checksum']==variant[k]['checksum'] for k in selected)
            groups[category]={'cases':len(selected),'control_ns':c,'scaled_ns':v,'ratio':v/c}
        all_ratio=sum(variant[k]['best_ns'] for k in keys)/sum(control[k]['best_ns'] for k in keys)
        assert all_ratio==pair[f'scaled_block_{block}']['mul']['variant_over_control']
        data.append({'seed':seed,'block':block,'all_mul_ratio':all_ratio,'groups':groups})
asm=(RAW/'own-object-0-asm.txt').read_bytes()
capture=next(x for x in result['post_timing_existing_capture_tools'] if x['artifact']=='own-object-0-asm.txt')
assert hashlib.sha256(asm).hexdigest()==capture['sha256'] and capture['ok']
text=asm.decode()
symbol_start=text.index('0000000000000000 <lp_competition_main___lam__1>:')
body_start=text.index('\n',symbol_start)+1
symbol_end=re.search(r'(?m)^0[0-9a-f]+ <[^>]+>:',text[body_start:])
symbol=text[symbol_start:body_start+symbol_end.start()] if symbol_end else text[symbol_start:]
lines=symbol.splitlines()
fast='\n'.join(line for line in lines if re.match(r'\s*(?:3[5-9][0-9a-f]):',line))+'\n'
assert 'cvtsi2ss' in fast and 'cvttss2si' in fast and 'mulss' in fast
# The complete raw disassembly remains the authority; this excerpt is navigation only.
(HERE/'timed-scaled-fast-arm.asm.txt').write_text(fast,encoding='utf-8')
out={'checked_utc':datetime.now(timezone.utc).isoformat(),'decision':'PARK_CURRENT_SCALED_RUNTIME_NO_FULL_PROOF_QUEUE',
 'run_id':40586463637,'kernel_sha256':result['source_sha256'],
 'result_sha256':hashlib.sha256((RAW/'result.json').read_bytes()).hexdigest(),
 'timed_object_sha256':result['build_identities'][next(k for k in result['build_identities'] if k.endswith('/R22RuntimeCostMain.c.o.export'))],
 'timed_asm_sha256':capture['sha256'],'pairs':data,
 'observation':'All four complete-call MUL blocks regress. Actual timed callback main___lam__1, selected through main___lam__1___boxed, includes the product/cast/scale/reverse/clamp chain at357..38b.',
 'actual_callback_symbol':'lp_competition_main___lam__1',
 'auxiliary_symbol':'lp_competition_r22CostScaledMul is a separately emitted helper, not the timed callback.',
 'mechanism_correction':'Parent traced _lean_main callback binding and corrected the earlier helper-only475..4ae label. Original derived note preserved as cost-decision-helper-location-original.json; raw artifacts unchanged.',
 'excerpt_correction':'The earlier navigation extractor matched the remaining zeros of its own header and emitted an empty excerpt. Current extraction begins after the header newline and asserts the three conversion/multiply mnemonics. This never affected raw artifact bytes or paired times.',
 'scope':'Fixed two-seed discovery diagnostic, not original25-round gate or a new random confirmation.',
 'causal_limit':'Category labels do not establish guard-hit rates or isolate a single instruction cost. No profile or omission experiment identifies the causal share of scale versus clamp versus dispatch.',
 'next_condition':'Reopen only with a changed arithmetic/data representation or independently justified caller-cost change; no seed retry.'}
(HERE/'cost-decision.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'decision':out['decision'],'pairs':[{'seed':r['seed'],'block':r['block'],'all':r['all_mul_ratio'],'groups':{k:round(v['ratio'],6) for k,v in r['groups'].items()}} for r in data]},indent=2))
