"""Reject a new match only when it cannot improve its existing distance-code slot."""
from pathlib import Path
import importlib.util
import json

ROOT = Path(__file__).resolve().parents[1]


def main():
    sp = importlib.util.spec_from_file_location('writer', ROOT / 'scripts/build-round18-start.py')
    w = importlib.util.module_from_spec(sp)
    sp.loader.exec_module(w)
    parent = ROOT / 'candidates/r18-rf-sf-content-proof1'
    rust, lean = [(parent / f).read_text() for f in ('parse.rs', 'Parse.lean')]
    helper = '''pub fn SFbound(best:&[u32;8],count:usize,d:usize)->usize {
 let dc=q9_dslot(d) as u32;let mut bound=2usize;
 if count>0&&best[4]==dc {bound=q9_umax(bound,SFlen(best[0]));}
 if count>1&&best[5]==dc {bound=q9_umax(bound,SFlen(best[1]));}
 if count>2&&best[6]==dc {bound=q9_umax(bound,SFlen(best[2]));}
 if count>3&&best[7]==dc {bound=q9_umax(bound,SFlen(best[3]));}
 bound
}

'''
    rust = rust.replace('pub fn SFsmallmatches(', helper + 'pub fn SFsmallmatches(', 1)
    old = 'let known=SFknown(ot,d,cap);let l=SFmatchlen(input,j,p,cap,known);if l>=3{count=SFsmalladd(&mut best,count,SFmt(d,l));}'
    new = 'let bound=SFbound(&best,count,d);if bound<cap&&q9_byte_at(input,j.wrapping_add(bound))==q9_byte_at(input,p.wrapping_add(bound)){let known=SFknown(ot,d,cap);let l=SFmatchlen(input,j,p,cap,known);if l>=3{count=SFsmalladd(&mut best,count,SFmt(d,l));}}'
    assert rust.count(old) == 1
    rust = rust.replace(old, new)
    proof = '''@[local step]
theorem SFbound_spec (best : Array Std.U32 8#usize) (count d : Std.Usize) :
 slot.SFbound best count d ⦃ fun _ => True ⦄ := by
 rw [slot.SFbound]
 step*
 repeat' (split <;> step*)
 all_goals scalar_tac

'''
    marker = '@[local step]\ntheorem SFsmallmatches_loop0_loop0_spec'
    assert lean.count(marker) == 1
    lean = lean.replace(marker, proof + marker)
    entry = w.write_candidate('r19-sf-endprobe', parent.name, rust, lean,
        'Before scanning a predecessor, use the best retained match in the same DEFLATE distance-code bucket as a lower bound; skip when the match cannot exceed it, including one end-byte rejection test.',
        'R19 profile shows SFsmallmatches is the largest SF stage. Unlike quality-reducing depth or stride changes, this seeks identical retained matches and output. Equality remains a hypothesis until real differential checks.',
        {'parent': 'candidates/r18-rf-sf-content-proof1/manifest.json', 'profile': 'evidence/round19/38042741551/profile-b-native/diagnostics/r18-functions/functions.json'})
    entry.update(anchor='base603', comparison_baseline='base603', native_decode_reference='base603', expected_equivalent_to='base603')
    spec = json.loads((ROOT / 'evidence/round19/probe-c-native.json').read_bytes())
    spec['entries'] = [e for e in spec['entries'] if e['control']] + [entry]
    names = [e['name'] for e in spec['entries']]
    spec['screen_orders'] = [names, list(reversed(names))]
    spec['description'] = 'E preflight: same-code end-probe avoids hopeless match scans. One actual-source28-file encoder/decode against603; token hashes must match before spending on original paired timing, and540 native cases plus exact full proof follow if worthwhile.20minute cap. New helper proof is only a draft.'
    (ROOT / 'evidence/round19/probe-e-native.json').write_bytes((json.dumps(spec, indent=2) + '\n').encode())
    print(entry['hashes'])


if __name__ == '__main__':
    main()
