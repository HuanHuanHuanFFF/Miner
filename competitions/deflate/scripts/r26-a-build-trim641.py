"""Remove unreachable head-table tails in public641; no route/search changes."""
from pathlib import Path
import hashlib
import json
import re

ROOT=Path(__file__).resolve().parents[1]
PARENT=ROOT/'references/round26-public-641'
NAME='r26-a-641-trimhead'
OUT=ROOT/'evidence/round26/route-a'
RS='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
LEAN='7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e'


def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())


def main():
    raw=(PARENT/'parse.rs').read_bytes();lean=(PARENT/'Parse.lean').read_bytes()
    assert sha(raw)==RS and sha(lean)==LEAN
    text=raw.decode()
    expression='(k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> (if H == 262144 {46u32} else if H == 131072 {47u32} else if H == 65536 {48u32} else {49u32})) as usize % H'
    assert text.count(expression)==1
    assert 'if H%2==1 {pc_put_match_checked' in text and 'else if H%4==2{pc_put_match_wrapped' in text
    assert 131100%2==32768%2==0 and 131100%4==32768%4==0
    # For every possible 15-bit pre-modulo index, the two head tables agree.
    for index in range(1<<15):assert index%131100==index%32768==index
    matches=list(re.finditer(r'pc_run1c::<131100>\([^\n]*?\)',text))
    assert len(matches)==text.count('::<131100>')==6
    changed=text.replace('pc_run1c::<131100>','pc_run1c::<32768>')
    # Verify by exact spans rather than global reverse replacing existing32768 calls.
    rebuilt=text
    for m in reversed(list(re.finditer('pc_run1c::<131100>',text))):
        rebuilt=rebuilt[:m.start()]+'pc_run1c::<32768>'+rebuilt[m.end():]
    assert rebuilt==changed
    rows=[line for line in text.splitlines() if 'pc_run1c::<131100>' in line]
    changed_rows=[line for line in changed.splitlines()if any('pub fn '+name+'(' in line for name in ['p135_row10','p135_row16','p135_row18'])]
    # Existing source proof is generic inH; no hard-coded131100 premise exists.
    assert b'131100' not in lean
    directory=ROOT/'candidates'/NAME
    assert not directory.exists(),'Frozen candidates are immutable'
    directory.mkdir()
    (directory/'parse.rs').write_bytes(changed.encode());(directory/'Parse.lean').write_bytes(lean)
    hashes={'parse.rs':sha(changed.encode()),'Parse.lean':sha(lean)}
    manifest={'candidate':NAME,'parent':'references/round26-public-641','hashes':hashes,
              'attribution':{'source_receipt':'references/round26-public-641/source-receipt.json','source_submission':'641','author_hotkey':'5FYhJSAu4q86E2Yn8UjNvpbUQVZGzq5wB7W7YFqnmvz288yo','ownership':'Derivative of public641; original author/source attribution retained.'},
              'mechanism':'Replace only six pc_run1c::<131100> instantiations with pc_run1c::<32768>. Both H choices use shift49 before modulo, so every address is below32768; both use the raw emitterH%4==0. Remove393328 bytes of unreachable head-table capacity per activated parse.',
              'difference_from_old_work':'R22halfhead changed one older595 table from65536 to32768 with weak total-time signals. This exact new641 parent already has35.95827 formal historical quality and six4x-sized head instances across three rows, with different lazy/search/routing. This is a bounded transfer and source-specific unreachable-capacity correction, not a new mechanism class or a size sweep.',
              'preserved':'All route/classifier branches, search/skip/lazy/depth, hash multiplier and shifts, insertion policy, folding and emission functions; all other H values including odd32769/32781/32785 remain exact.',
              'proof_status':'ORIGINAL_PUBLIC641_LEAN_COPIED_UNMODIFIED; genericH interfaces inspected, fresh exact extraction and full original gate NOT_RUN',
              'performance_status':'UNKNOWN; capacity/init reduction does not imply elapsed-time gain, compiler may already optimize dead storage.',
              'expected_token_equivalence':'INFERRED for valid execution via address-range and state projection; finite native/all-public equality and new original gate required.',
              'formal_submission_sent':False}
    dump(directory/'manifest.json',manifest)
    entry={'name':NAME,'path':directory.relative_to(ROOT).as_posix(),'control':False,'hashes':hashes,'anchor':'public641','comparison_baseline':'public641','native_decode_reference':'public641','expected_equivalent_to':'public641'}
    dump(OUT/'trim641-entry.json',entry)
    audit={'status':'VERIFIED_EXACT_SOURCE_PATCH_AND_ALL15BIT_INDEX_MODEL_NOT_NATIVE','parent_hashes':{'parse.rs':RS,'Parse.lean':LEAN},'hashes':hashes,
           'changed_call_sites':len(matches),'changed_original_rows':rows,'changed_rows':changed_rows,'finite_index_cases':32768,
           'head_bytes_before':131100*4,'head_bytes_after':32768*4,'unreachable_bytes_removed_per_active_parse':(131100-32768)*4,
           'lean_byte_identical':True,'original_proof_has_literal131100':False,'native':'NOT_RUN','performance':'NOT_RUN','gate':'NOT_RUN'}
    dump(OUT/'trim641-build-audit.json',audit)
    print(json.dumps({'candidate':NAME,'hashes':hashes,'changed_call_sites':len(matches)},indent=2))


if __name__=='__main__':main()
