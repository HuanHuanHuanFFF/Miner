"""Move proven-small PC mechanism to newly published, closer #514 parent.

Exact PC Rust body matches #507; other engines/routes stay #514's original.
Native equality is required only for the subsequent padding representation.
"""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-514'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate(padding=False):
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};origin=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(b)for f,b in raw.items()}==origin['files']
    original=raw['parse.rs'].decode();start=original.index('pub fn pc_f_link<const H: usize>');end=original.index('/// Structured binaries (class 3)',start);body=original[start:end]
    prior=(ROOT/'references/round12-public-507/parse.rs').read_text();a=prior.index('pub fn pc_f_link<const H: usize>');b=prior.index('/// Structured binaries (class 3)',a);assert body==prior[a:b]
    n = 32800 if padding else 32768
    off = ' + 32' if padding else ''
    edits=[('[u32; 32768]',f'[u16; {n}]',3),('prev[i % 32768] = head[a];',f'prev[i % 32768{off}] = (head[a] as u16) & 32767;',1),
        ('let c3 = prev[c2 % 32768] as usize;',f'let c3 = r13_prev_unwrap(c2, prev[c2 % 32768{off}]);',1),
        ('let mut prev = [0u32; 32768];',f'let mut prev = [0u16; {n}];',1),
        ('let cl = prev[c % 32768] as usize;',f'let cl = r13_prev_unwrap(c, prev[c % 32768{off}]);',1)]
    changed=body
    for x,y,k in edits:assert changed.count(x)==k;changed=changed.replace(x,y)
    restored=changed
    for x,y,k in reversed(edits):assert restored.count(y)==k;restored=restored.replace(y,x)
    assert restored==body
    helper='''/// R13 modular predecessor hint. Original pc_f_try validates every emitted match.
#[inline(always)]
pub fn r13_prev_unwrap(c: usize, low: u16) -> usize {
    let delta = c.wrapping_sub(low as usize) & 32767;
    c.wrapping_sub(delta)
}

'''
    attr=original.rfind('#[inline(always)]',0,start);rust=(original[:attr]+helper+original[attr:start]+changed+original[end:]).encode()
    assert rust.decode().replace(helper,'',1).replace(changed,body,1)==original
    lean=raw['Parse.lean'].decode();ls=lean.index('theorem f_link_spec');le=lean.index('end PC',ls);section=lean[ls:le];assert section.count('Array Std.U32 32768#usize')==9
    proofbody=section.replace('Array Std.U32 32768#usize',f'Array Std.U16 {n}#usize');lat=lean.rfind('@[local step]',0,ls)
    lemma='''/-- Reconstructed coordinates are hints; match validity remains with the original byte validator. -/
@[local step]
theorem r13_prev_unwrap_spec (c : Std.Usize) (low : Std.U16) :
    slot.r13_prev_unwrap c low ⦃ fun _ => True ⦄ := by
  rw [slot.r13_prev_unwrap]
  step*
  all_goals first | trivial | scalar_tac

'''
    proof=(lean[:lat]+lemma+lean[lat:ls]+proofbody+lean[le:]).encode()
    name='r13-514-abs15'+('-pad64'if padding else'');files={'parse.rs':rust,'Parse.lean':proof};assert all(len(x)<=524288 for x in files.values())
    baseline='r13-514-abs15'if padding else'public514'
    manifest={'candidate':name,'parent':baseline,'formal_anchor_id':'514','comparison_baseline':baseline,'hashes':{f:sha(v)for f,v in files.items()},'parent_original_hashes':origin['files'],
        'attribution':{'source':'Official published514; original source headers retained','author_hotkey':origin['author_hotkey'],'reference':'references/round13-public-514/PROVENANCE.md','link_encoding':'R12 abs15 mechanism; not an independent whole-parser invention'},
        'native_relation':'token_equality'if padding else'decode_only',
        'mechanism':'Same shallow PC modular-position link encoding on #514, '+('with one64B logical predecessor displacement'if padding else'without per-store distance encoding'),
        'difference_from_old_work':'New official closer parent after539 defeated514; Rust PC region is byte-identical to507 but routes, other engines and formal coordinates differ. Test actual total-time transfer rather than adding old gains.',
        'source_reversal':'Exact original514 restored by reversing isolated PC store/types/reads and removing helper; every route and other engine unchanged.',
        'proof_status':'DRAFT_UNCOMPILED; nine predecessor types and helper totality bridge; no inherited derivative gate certificate',
        'equivalence_status':'Padding requires exact finite/public equality to abs15; plain abs15 intentionally permits modular hint/token changes',
        'performance_status':'UNKNOWN; current same-family projection and repeated paired controls required','formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return name,files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    for padding in(False,True):
        name,files=generate(padding);dest=ROOT/'candidates'/name
        if args.check:assert all((dest/f).read_bytes()==v for f,v in files.items())
        else:
            assert not dest.exists();dest.mkdir()
            for f,v in files.items():(dest/f).write_bytes(v)
        print(json.dumps({'candidate':name,'hashes':{f:sha(v)for f,v in files.items()},'proof_status':'UNCOMPILED'}))

if __name__=='__main__':main()
