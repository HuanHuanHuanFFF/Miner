"""Read-only source reproduction/freeze receipt; never rewrites frozen Lean."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
EXPECTED='8e27baf70ce7e3f10b669cc9f59d66d5fffaa17ee3dc6df934f3229139a5b0dd'
sha=lambda b:hashlib.sha256(b).hexdigest()


def main():
    base=(ROOT/'competitions/floatlib/candidates/f01-r22-dev-resident8-cost1/Kernel.lean').read_bytes()
    fragment=(HERE/'IndexedResident8.lean.inc').read_bytes()
    raw=(HERE/'KernelIndexed8Cost.lean').read_bytes()
    start=base.index(b'abbrev State (p : Nat) := Vector Cell (groups p)',base.index(b'namespace Submission.R22Pair8'))
    end=base.index(b'end Submission.R22Pair8',start)
    rebuilt=base[:start]+base[end:]+b'\n'+fragment
    assert rebuilt==raw and sha(raw)==EXPECTED and len(raw)<=256000
    old=(HERE.parent/'development-resident8/Resident8.lean.inc').read_bytes()
    assert old in raw and raw[:226829]==base[:226829]
    m=json.loads((HERE/'indexed8-source-manifest.json').read_bytes())
    checks=json.loads((HERE/'indexed8-address-screen.json').read_bytes())
    assert m['sha256']==checks['kernel_sha256']==EXPECTED
    assert m['fragment_sha256']==checks['fragment_sha256']==sha(fragment)
    for name in ('build_indexed8.py','check_indexed8.py','freeze_indexed8.py'):
        ast.parse((HERE/name).read_bytes(),filename=name)
    carrier=(HERE/'R22Indexed8CostMain.lean').read_bytes()
    assert sha(carrier)==m['caller_sha256'] and carrier.count(b'Bench.Suite.run ')==3
    assert all(('@[noinline] def '+n).encode() in carrier for n in ('runControl','runRaw8','runIndexed8'))
    prior=json.loads((HERE.parent/'development-resident8-actual-loop-machine.json').read_bytes())['rows'][0]
    asm_raw=(HERE.parent/prior['file']).read_bytes()
    assert sha(asm_raw)==prior['assembly_sha256']=='254fb41144b21961503328313a27c9b543a117389c35d3dd44430b08d946a86a'
    body=asm_raw.decode().split('<'+prior['symbol']+'>:',1)[1]
    instructions=[]
    for line in body.splitlines():
        match=re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)',line)
        if match and 0x570<=int(match[1],16)<=0x638:instructions.append(line)
    snippet='\n'.join(instructions)+'\n'
    assert 'movaps XMMWORD PTR [rsp],xmm0' in snippet
    assert 'movaps XMMWORD PTR [rsp+0x20],xmm0' in snippet
    (HERE/'old-raw8-hot-acc-stack.asm.txt').write_text(snippet,encoding='utf-8')
    report={'frozen_at_utc':datetime.now(timezone.utc).isoformat(),
        'kernel_sha256':EXPECTED,'bytes':len(raw),'fragment_sha256':sha(fragment),
        'caller_sha256':sha(carrier),'read_only_rebuild_exact':True,
        'retained_B2_prefix_exact':True,'raw8_entire_fragment_exact':True,
        'dead_unused_Pair8_variant_bytes':end-start,
        'finite_source_address_check_sha256':sha((HERE/'indexed8-address-screen.json').read_bytes()),
        'old_native_source':prior,'old_hot_stack_snippet_sha256':sha(snippet.encode()),
        'change_scope':'Word-fit guard once per call, erased address bounds, USize k/A addresses/stride cursor; old raw8 arithmetic/prep/codec/finish/tail unchanged.',
        'Lean':'NOT_RUN','new_BMM_all_input_proof':'NOT_RUN','actual_new_C_ASM':'NOT_RUN','cost':'NOT_RUN',
        'cold_R2_codec_calls_and_new_spill':'UNKNOWN; a word-index loop does not guarantee register residency.',
        'freeze_rule':'Preserve this exact8e source. Any necessary repair must be a separately named version with fresh hash/receipt.'}
    (HERE/'indexed8-freeze-receipt.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:v for k,v in report.items() if k!='old_native_source'}))


if __name__=='__main__':main()
