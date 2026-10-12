"""Reuse exact B31 full-state observer for owner-free consumer, small real lookup counts."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import sys

sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[1]
BASE=importlib.import_module('r26-b-a-flatten-counts')
ORIGINAL=BASE.instrument
NAME='r26-b-552-a-no-owner'
EXPECTED='8012a8320f07228f01f383d0946d52f1000d3256d71ea6f1a121a2501ea276eb'
BASE.NAME=NAME;BASE.EXPECTED=EXPECTED
BASE.FIELDS=list(BASE.FIELDS)
BASE.FIELDS[7]='fill_written_base_slots'
BASE.FIELDS[13]='owner_helper_calls'
BASE.FIELDS+=['winning_cached_records_read','direct_inherited_owner_calls']


def instrument(raw):
    text=ORIGINAL(raw).decode()
    text=text.replace('[AtomicU64;16]','[AtomicU64;18]').replace('[const{AtomicU64::new(0)};16]','[const{AtomicU64::new(0)};18]').replace('r26_flat_take()->[u64;16]','r26_flat_take()->[u64;18]')
    text=text.replace('pub fn a_fill(bl:&mut[u32;1024],dl:&mut[u32;1024],from:usize,to:usize,base:u32,d:u32)',
                      'pub fn a_fill(bl:&mut[u32;1024],from:usize,to:usize,base:u32)')
    text=text.replace('r26_a_fill_core(bl,dl,from,to,base,d);','r26_a_fill_core(bl,from,to,base);')
    fn=importlib.import_module('prepare-round24-extract-repro').fn
    old=fn(text,'a_dp_owner');part=old
    part=part.replace(' if ext&&len>prev_len{return xd.wrapping_sub(1)as u32;}',
                      ' r26_flat_hit(13,1);let mut reads=0u64;\n if ext&&len>prev_len{r26_flat_hit(17,1);return xd.wrapping_sub(1)as u32;}',1)
    part=part.replace('  let m=mb[j];','  let m=mb[j];reads+=1;',1)
    part=part.replace('if stop>=len{return m&32767;}','if stop>=len{r26_flat_hit(16,reads);return m&32767;}',1)
    part=part.replace(' 0\n}',' r26_flat_hit(16,reads);0\n}',1)
    assert part!=old;text=text.replace(old,part,1)
    importlib.import_module('r26-b-fix-shared-cache').spans(text)
    return text.encode()


BASE.instrument=instrument


def preflight(spec):
    assert spec.get('r26_b_a_flatten_module')=='r26-b-a-no-owner-counts'
    return BASE.preflight(spec)


def main():
    BASE.main()
    path=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-a-flatten/receipt.json'
    raw=path.read_bytes();path.with_name('full-state-driver-receipt.json').write_bytes(raw)
    data=json.loads(raw)
    data['consumer_mode']='B36_NO_OWNER_SCRATCH_EXACT_ACTUAL_DP_FULL_STATE_CHECK'
    data['no_owner_script_sha256']=hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    data['limits']=[s for s in data['limits'] if not s.startswith('Scratch pair slots')]
    data['limits'].append('fill_written_base_slots now counts one real bl store; no dl allocation/initialization/store. Owner helper/cached-record/direct inherited counts are real observer-only counts; their production work remains in separate pure profile.')
    path.write_text(json.dumps(data,indent=2)+'\n')


if __name__=='__main__':main()
