"""Two modular-position probes: cheaper stores, intentional search changes possible."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round12-public-507'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate(kind):
    assert kind in ('abs16','abs15')
    raw={f:(BASE/f).read_bytes()for f in ('parse.rs','Parse.lean')}
    receipt=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(v)for f,v in raw.items()}==receipt['files']
    original=raw['parse.rs'].decode();start=original.index('pub fn pc_f_link<const H: usize>');end=original.index('/// Structured binaries (class 3)',start)
    body=original[start:end]
    if kind=='abs16':
        unwrap='''    let q = (c & !65535usize) | low as usize;
    if q < c { q } else { q.wrapping_sub(65536) }'''
        store='head[a] as u16'
    else:
        unwrap='''    let delta = c.wrapping_sub(low as usize) & 32767;
    c.wrapping_sub(delta)'''
        store='(head[a] as u16) & 32767'
    helper='''/// R12: modular candidate reconstruction. The existing pc_f_try checks every
/// recovered candidate's decreasing order, window and actual input bytes.
#[inline(always)]
pub fn r12_prev_unwrap(c: usize, low: u16) -> usize {
BODY
}

'''.replace('BODY',unwrap)
    edits=[('[u32; 32768]','[u16; 32768]',3),
        ('prev[i % 32768] = head[a];',f'prev[i % 32768] = {store};',1),
        ('let c3 = prev[c2 % 32768] as usize;','let c3 = r12_prev_unwrap(c2, prev[c2 % 32768]);',1),
        ('let mut prev = [0u32; 32768];','let mut prev = [0u16; 32768];',1),
        ('let cl = prev[c % 32768] as usize;','let cl = r12_prev_unwrap(c, prev[c % 32768]);',1)]
    changed=body
    for a,b,n in edits:
        assert changed.count(a)==n,(a,changed.count(a),n);changed=changed.replace(a,b)
    back=changed
    for a,b,n in reversed(edits):assert back.count(b)==n;back=back.replace(b,a)
    assert back==body
    # Keep the original attribute on pc_f_link; helper has its own attribute.
    insert=original.rfind('#[inline(always)]',0,start)
    source=original[:insert]+helper+original[insert:start]+changed+original[end:]
    assert source.replace(helper,'',1).replace(changed,body,1)==original
    lean=raw['Parse.lean'].decode();ls=lean.index('theorem f_link_spec');le=lean.index('end PC',ls)
    section=lean[ls:le];assert section.count('Array Std.U32 32768#usize')==9
    adapted=section.replace('Array Std.U32 32768#usize','Array Std.U16 32768#usize')
    lemma='''/-- Arbitrary reconstructed positions remain search-only; pc_f_try validates actual matches. -/
@[local step]
theorem r12_prev_unwrap_spec (c : Std.Usize) (low : Std.U16) :
    slot.r12_prev_unwrap c low ⦃ fun _ => True ⦄ := by
  rw [slot.r12_prev_unwrap]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

'''
    attr=lean.rfind('@[local step]',0,ls)
    proof=lean[:attr]+lemma+lean[attr:ls]+adapted+lean[le:]
    assert proof[proof.index('end PC',proof.index('theorem f_link_spec')):]==lean[le:]
    name='r12-fast-pc507-'+kind
    files={'parse.rs':source.encode(),'Parse.lean':proof.encode()}
    assert all(len(b)<=524288 for b in files.values())
    manifest={'candidate':name,'parent':BASE.relative_to(ROOT).as_posix(),'parent_hashes':receipt['files'],
        'hashes':{f:sha(b)for f,b in files.items()},'formal_anchor_id':'507','comparison_baseline':'public507',
        'native_relation':'decode_only','attribution':{'source':'Officially public #507, existing #435/#436/#488/#503 lineage retained',
            'author_hotkey':receipt['author_hotkey'],'reference':(BASE/'PROVENANCE.md').relative_to(ROOT).as_posix()},
        'mechanism':f'Store predecessor position modulo{65536 if kind=="abs16" else 32768} inU16 without per-insertion distance encode/invalid-link branch. Reconstruct an older candidate at reads; all distance and byte checks remain in pc_f_try.',
        'difference_from_previous':'The failed distance-coded version paid subtraction and cap handling at every link store. This changes where work is paid and may search a reconstructed nearby position when the original predecessor was too old; it is not a same-token optimization claim.',
        'semantic_status':'Intentional token/search differences permitted. Reconstructed positions are only hints: pc_f_try requires strict decrease, valid window, input bounds and actual matching bytes; original obligation still mandatory.',
        'proof_status':'DRAFT_UNCOMPILED; nine U16 predecessor types plus search-helper totality bridge; real extraction and full original gate not yet run',
        'fixed_predecessor_bytes_before':131072,'fixed_predecessor_bytes_after':65536,
        'source_reversal':'Exact isolated PC link region reverses; every route, row, search depth, original byte validator and other engine unchanged.',
        'limits':'Original #507 exact-length routes retained, no new ones introduced. Public-to-formal transfer is a hypothesis. No compression monotonicity, all-input token equality or private guarantee.',
        'stop_condition':'Any decode/panic failure stops. No worthwhile paired two-axis gain versus current geometry closes this fixed source. Confirmation and exact full gate required before formal submission.',
        'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode()
    return name,files

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    for kind in ('abs16','abs15'):
        name,files=generate(kind);dest=ROOT/'candidates'/name
        if args.check:assert all((dest/f).read_bytes()==b for f,b in files.items())
        else:
            assert not dest.exists();dest.mkdir()
            for f,b in files.items():(dest/f).write_bytes(b)
        print(json.dumps({'candidate':name,'hashes':{f:sha(b)for f,b in files.items()},'relation':'decode-only; token changes permitted'}))

if __name__=='__main__':main()
