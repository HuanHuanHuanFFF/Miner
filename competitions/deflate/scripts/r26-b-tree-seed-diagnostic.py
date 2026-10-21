"""Extend frozen B19 with exact active edge-prefix seeds on its fallback probes."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib
import json
import os
import sys

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
BASE = importlib.import_module('r26-b-tree-edge-diagnostic')
ORIGINAL_INSTRUMENT = BASE.instrument
FIELDS = BASE.FIELDS + ['seed_raise_calls', 'seed_raise_bytes', 'seed_saved_word_pairs', 'seed_258_direction_difference']


def instrument(raw):
    text = ORIGINAL_INSTRUMENT(raw).decode()
    text = text.replace('[AtomicU64;16]', '[AtomicU64;20]').replace('[const{AtomicU64::new(0)};16]', '[const{AtomicU64::new(0)};20]')
    text = text.replace('pub fn r26_edge_take()->[u64;16]', 'pub fn r26_edge_take()->[u64;20]')
    text = text.replace('let mut cnt=[0u64;16]', 'let mut cnt=[0u64;20]').replace('while ci<16', 'while ci<20')
    needle = '        let l = r.0;'
    assert text.count(needle) == 1
    extra = '''        if linked {
            let t=(incoming&511)as usize;
            let shortcut=((incoming&512)!=0&&t<last_l)||t>last_l;
            let low=if t<last_l{t}else{last_l};let raised=if low>seed{low}else{seed};
            if !shortcut&&raised>seed {
                let newer=a_probe(s,p,pos,raised);
                assert_eq!(newer.0,r.0,"seed length old={} new={} pos={} p={} tag={}",seed,raised,pos,p,incoming);
                if r.0<258{assert_eq!(newer.1,r.1,"seed direction old={} new={} pos={} p={} tag={}",seed,raised,pos,p,incoming);}
                let newpairs=if newer.0<258{1+(newer.0-raised)/8}else{1+if raised<250{(250-raised+7)/8}else{0}};
                assert!(newpairs<=pairs);cnt[16]+=1;cnt[17]+=(raised-seed)as u64;cnt[18]+=(pairs-newpairs)as u64;
                cnt[19]+=((r.0==258)&&(r.1!=newer.1))as u64;
            }
        }
'''
    text = text.replace(needle, extra + needle, 1)
    importlib.import_module('r26-b-fix-shared-cache').spans(text)
    return text.encode()


BASE.instrument = instrument
BASE.FIELDS = FIELDS


def preflight(spec):
    assert spec.get('r26_b_tree_edge_module') == 'r26-b-tree-seed-diagnostic'
    result = BASE.preflight(spec)
    result['observer_mode'] = 'B20_EXACT_FALLBACK_PREFIX_SEED_AFTER_B19_SHORTCUTS'
    return result


def main():
    # The unchanged base driver preserves exact original token/decode checks,
    # build/run limits and source binding; only observer construction differs.
    BASE.main()
    if '--check' not in sys.argv:
        path = Path(os.environ['RUNNER_TEMP']) / 'round4-receipts/r26-b-tree-edge/receipt.json'
        raw = path.read_bytes()
        assert not path.with_name('driver-receipt.json').exists()
        path.with_name('driver-receipt.json').write_bytes(raw)
        result = json.loads(raw)
        result['status'] = 'VERIFIED_ORIGINAL_A_EDGE_SHORTCUT_AND_RAISED_SEED_TOKEN_DECODE_PARITY'
        result['observer_mode'] = 'B20_EXACT_FALLBACK_PREFIX_SEED_AFTER_B19_SHORTCUTS'
        result['seed_script_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
        result['driver_receipt_sha256'] = hashlib.sha256(raw).hexdigest()
        result['recorded_utc'] = datetime.now(timezone.utc).isoformat()
        result['combined_saved_word_pairs'] = result['totals']['shortcut_word_pairs'] + result['totals']['seed_saved_word_pairs']
        result['limits'].append('Fallback seed changes require the same lower-bound invariant, and compare length plus direction below258; at capped258 direction is unused by original NICE copy.')
        path.write_text(json.dumps(result, indent=2) + '\n')
        print(json.dumps({'status': result['status'], 'totals': result['totals'], 'combined_saved_word_pairs': result['combined_saved_word_pairs']}))


if __name__ == '__main__':
    main()
