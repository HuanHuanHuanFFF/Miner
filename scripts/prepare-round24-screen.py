"""Turn a successful immutable native-byte batch into two original timing blocks."""
from pathlib import Path
import argparse, json
ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'

def main():
    ap=argparse.ArgumentParser();ap.add_argument('native_batch');ap.add_argument('run');ap.add_argument('screen_batch');ap.add_argument('--drop-control',action='append',default=[]);a=ap.parse_args()
    native=ROOT/f'evidence/round24/{a.run}/{a.native_batch}/diagnostics/r13-encoder/encoder.json'
    n=json.loads(native.read_bytes());assert n['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    s=json.loads((E/(a.native_batch+'.json')).read_bytes())
    s['entries']=[e for e in s['entries'] if e['name']!='public514']
    by={e['name']:e for e in s['entries']}
    assert all(n in by and by[n]['control'] for n in a.drop_control)
    for e in s['entries']:
        if e['name'] in a.drop_control:continue
        assert not set(a.drop_control).intersection(e.get(k) for k in ['anchor','comparison_baseline','native_decode_reference','expected_equivalent_to'])
    s['entries']=[e for e in s['entries'] if e['name'] not in a.drop_control]
    for e in s['entries']:
        if not e['control']: assert n['source_hashes'][e['name']]==e['hashes']
    s.update(r24_mode='standard',native_only=False,native_encoder=False,native_encoder_references=[],synthetic_validation=False,r18_role='discovery',description=f'Original paired total-compression timing of actual-byte-screened {a.native_batch}; both reversed blocks and all declared actual parents and same-source anchors. Exact Lean acceptance remains separate.')
    ns=[e['name'] for e in s['entries']];s['screen_orders']=[ns,ns[::-1]]
    dest=E/(a.screen_batch+'.json');assert not dest.exists();dest.write_bytes((json.dumps(s,indent=2)+'\n').encode())
    plan={'gap':'Native quality is real; token changes and parser/encoder interaction leave total speed and current share UNKNOWN.',
        'change':'First original-protocol total-time measurement on the same exact Rust after byte screening.',
        'minimum':'Two reversed original1warmup11measured blocks, complete28-file corpus and per-file paired incumbent, actual parent and same-source formal anchor.',
        'decisions':'Recompute every block with latest official capture; retain positives and failures. Control discrepancies that change promotion trigger a discriminating diagnosis, not peak promotion. Full gate follows only useful evidence or blocking proof feasibility.',
        'native_receipt':native.relative_to(ROOT).as_posix(),'cost_cap_runner_minutes':25,'evidence':f'evidence/round24/<run>/{a.screen_batch}/gate','status':'PREDECLARED'}
    (E/f'preflight-{a.screen_batch}.json').write_bytes((json.dumps(plan,indent=2)+'\n').encode())
    print(a.screen_batch, len(ns), 'methods x2blocks')
if __name__=='__main__':main()
