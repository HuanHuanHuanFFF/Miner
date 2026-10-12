"""One A ordinary-domain inherited-distance reselect; preserve the original recurrence."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT/'references/round24-public-552'
TARGET = ROOT/'candidates/r26-b-552-overlap-select'
PAIR = {'parse.rs': '5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9',
        'Parse.lean': '51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'}

HELPER = '''
// Original offers and new inherited-distance offers share each ordinary-range load.
// Keep both wrapped packed minima; a whole-range raw-cost minimum is insufficient.
pub fn r26_a_overlap_interval(cost:&Vec<u32>,lc:&[u32;512],i:usize,lo:usize,stop:usize,cut:usize,base:u32,delta:u32)->(u32,u32) {
    let mut old=4294967295u32;let mut extra=4294967295u32;
    let mut at=lo;let mut l=at.wrapping_sub(i) as u32;
    while at<=stop&&at<cost.len() {
        let v=(cost[at].wrapping_add(lc[(l%512)as usize]).wrapping_add(base)<<9)|l;
        if v<old{old=v;}
        if at<=cut&&l<512 {
            let x=v.wrapping_sub(delta);
            if x<extra{extra=x;}
        }
        at+=1;l=l.wrapping_add(1);
    }
    (old,extra)
}
'''

ORDINARY = '''                    let mut at = prev + 1;
                    let mut l = at.wrapping_sub(i) as u32;
                    while at <= stop {
                        let c = (cost[at].wrapping_add(lc[(l % 512) as usize]).wrapping_add(base) << 9) | l;
                        mbest = if c < mbest { c } else { mbest };
                        at += 1;
                        l = l.wrapping_add(1);
                    }'''


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def generate():
    raw = {name: (BASE/name).read_bytes() for name in PAIR}
    assert {name: sha(value) for name, value in raw.items()} == PAIR
    source = raw['parse.rs'].decode()
    fn = importlib.import_module('prepare-round24-extract-repro').fn
    old = fn(source, 'a_dp_pass')
    new = old
    edits = []

    def change(before, after):
        nonlocal new
        assert new.count(before) == 1, before
        new = new.replace(before, after, 1)
        edits.append((before, after))

    change('        let mut xd = 0usize;', '        let mut xd = 0usize;\n        let mut r26_xprice=0u32;')
    change('            let j0 = mp[i] as usize;', '''            // The old XL/XD pair remains the sole inherited-match source.
            let r26_el=if xl+1>258{258}else{xl+1};
            let r26_valid=xl>=3&&xd>=1&&xd<=i&&s[i]==s[i-xd];
            let r26_newbd=((xd.wrapping_sub(1))as u32)&32767;
            let mut r26_extra=4294967295u32;
            let j0 = mp[i] as usize;''')
    change('            let mut pd = 0usize;', '            let mut pd = 0usize;\n            let mut r26_pprice=0u32;')
    change('                let base = dc[((m >> 23) % 32) as usize].wrapping_add(bias);', '''                let r26_oldprice=dc[((m>>23)%32)as usize];
                let base = r26_oldprice.wrapping_add(bias);''')
    replacement = '''                    if r26_valid&&r26_oldprice>r26_xprice&&prev+1<=i+r26_el {
                        let r26_delta=r26_oldprice.wrapping_sub(r26_xprice)<<9;
                        let r26_pair=r26_a_overlap_interval(cost,lc,i,prev+1,stop,i+r26_el,base,r26_delta);
                        mbest=r26_pair.0;
                        if r26_pair.1<r26_extra{r26_extra=r26_pair.1;}
                    }else{
''' + ORDINARY + '\n                    }'
    assert new.count(ORDINARY) == 2
    # Replace only ordinary records. The uncovered extension below stays exact.
    new = new.replace(ORDINARY, replacement, 1)
    edits.append((ORDINARY, replacement))
    change('                    pd = ((m & 32767) + 1) as usize;', '                    pd = ((m & 32767) + 1) as usize;\n                    r26_pprice=r26_oldprice;')
    change('                xd = pd;', '                xd = pd;\n                r26_xprice=r26_pprice;')
    change('            a_store_choice(cost, ch, i, best, bd, nxt);', '''            // Original record and uncovered-extension choices win exact packed ties.
            if r26_extra<best{best=r26_extra;bd=r26_newbd;}
            a_store_choice(cost, ch, i, best, bd, nxt);''')
    reverse = new
    for before, after in reversed(edits):
        assert reverse.count(after) == 1, after
        reverse = reverse.replace(after, before, 1)
    assert reverse == old
    rust = (source.replace(old, new, 1)+'\n'+HELPER).encode()
    spans = importlib.import_module('r26-b-fix-shared-cache').spans(rust.decode())
    assert 'r26_a_overlap_interval' in spans
    assert source.replace(old, new, 1).replace(new, old, 1).encode() == raw['parse.rs']
    files = {'parse.rs': rust, 'Parse.lean': raw['Parse.lean']}
    manifest = {
        'candidate': TARGET.name, 'parent': BASE.relative_to(ROOT).as_posix(), 'formal_parent_id': '552',
        'parent_hashes': PAIR, 'hashes': {name: sha(value) for name, value in files.items()},
        'bytes': {name: len(value) for name, value in files.items()},
        'attribution': 'Original public552 source and author attribution retained. Existing inherited A candidate supplies the added choice; R8D distance reselect is known negative precedent.',
        'mechanism': 'Only ordinary record-provided lengths may also use the byte-valid inherited distance when its current-pass dc price is strictly smaller. Original and new wrapped packed minima are both retained per term, then original final best wins exact ties.',
        'scope': 'A DP plus one bounded ordinary-range helper. No fixed-only endpoint/prefix additions, extra matcher searches, route/price/passes/encoder changes. Old XL/XD/record maximum/PD and uncovered extension recurrence retained.',
        'price_carry': 'One U32 dc price travels with unchanged XL/XD within a DP invocation. Original largest-record fallback saves the same already loaded record dc; inherited extension leaves both distance and price unchanged. No cross-pass price cache.',
        'consumption': 'Selected ordinary domains load cost/lc once and compute originalpacked plus exact wrapping-sub alternative; inactive domains retain original length loop. No full-prefix check or duplicate ordinary-range scan. All guard/helper/price-state cost is real new work.',
        'evidence': 'evidence/round26/route-b/b12-overlap-feedback.json: all12257237 inherited prefixes bytevalid; opportunities are sparse. Extra fixedgaps excluded due mostlytie/large scan cost.',
        'quality_status': 'UNKNOWN_UNTIL_ORIGINAL28ENCODER; modeledprice gaps do not imply bytes',
        'proof_status': 'UNADAPTED_PARENT_DRAFT; original-emitter checking/finite prefix evidence does not replace exact extraction/obligations/gate',
        'performance_status': 'NOT_RUN; native completecoarsecost first, no pairedspeed claim',
        'formal_status': 'NOT_SUBMITTED; admission/private/reward UNKNOWN',
        'source_reversal': 'Restore exact a_dp_pass edits in reverse and remove appended helper -> byte-exact pinned552; checked locally.',
    }
    files['manifest.json'] = (json.dumps(manifest, indent=2)+'\n').encode()
    assert all(len(value)<=524288 for name,value in files.items() if name!='manifest.json')
    return files, manifest


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    files, manifest = generate()
    TARGET.mkdir(exist_ok=True)
    for name, raw in files.items():
        path = TARGET/name
        if args.check:
            assert path.read_bytes() == raw
        else:
            assert not path.exists() or path.read_bytes() == raw
            path.write_bytes(raw)
    print(json.dumps({'candidate': TARGET.name, 'hashes': manifest['hashes'], 'bytes': manifest['bytes']}))


if __name__ == '__main__':
    main()
