"""One natural full-capacity hash endpoint on public641, not an H sweep."""
from pathlib import Path
import hashlib
import json
import re

ROOT=Path(__file__).resolve().parents[1]
PARENT=ROOT/'references/round26-public-641'
OUT=ROOT/'evidence/round26/route-a'
NAME='r26-a-641-hash17'
RS='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
LEAN='7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e'


def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())


def main():
    raw=(PARENT/'parse.rs').read_bytes();proof=(PARENT/'Parse.lean').read_bytes()
    assert sha(raw)==RS and sha(proof)==LEAN
    source=raw.decode();needle='pc_run1c::<131100>'
    assert source.count(needle)==6 and source.count('::<131100>')==6
    assert 'else if H == 131072 {47u32}' in source and 'else {49u32}' in source
    changed=source.replace(needle,'pc_run1c::<131072>')
    assert 'pc_run1c::<131072>' not in source
    assert changed.replace('pc_run1c::<131072>',needle)==source
    assert 131100%4==131072%4==0
    # All possible17-bit values; old15-bit index is the top15bits of newindex.
    assert all((v>>2)<32768 and v<131072 for v in range(131072))
    calls=[line for line in source.splitlines()if needle in line]
    dest=ROOT/'candidates'/NAME;assert not dest.exists(),'Frozen candidate exists';dest.mkdir()
    (dest/'parse.rs').write_bytes(changed.encode());(dest/'Parse.lean').write_bytes(proof)
    hashes={'parse.rs':sha(changed.encode()),'Parse.lean':sha(proof)}
    manifest={'candidate':NAME,'parent':'references/round26-public-641','hashes':hashes,
              'attribution':{'source_receipt':'references/round26-public-641/source-receipt.json','author_hotkey':'5FYhJSAu4q86E2Yn8UjNvpbUQVZGzq5wB7W7YFqnmvz288yo','ownership':'Derivative of public641 with original source and author attribution retained.'},
              'mechanism':'Replace exactly six H131100 PC chain instantiations with H131072. This activates the existing shift47 hash branch, covering17bits of slots instead of15, at almost unchanged allocated capacity. Search, lazy, insertion, routing and raw emitter selection remain as in641.',
              'difference_from_trimhead':'A3 removed an unreachable table tail and expected identical tokens. This source intentionally changes bucket collisions and candidate availability; no token equivalence is claimed. It is the single natural full-capacity endpoint, not a sweep near131100.',
              'history_boundary':'Older R3 expanded tables and R16 hash variants remain prior negative/cost evidence. The new641 parent has independently measured stronger parsing and different workload; those old outcomes neither establish this candidate nor prove it ineffective.',
              'proof_status':'Original641 Lean copied. Existing hash spec is generic inH and already branches on131072, but fresh exact extraction and original full gate are still required.',
              'performance_status':'UNKNOWN; more retained keys can cost cache traffic and change downstream encoding work. Only actual original-encoder bytes justify a paired total-time screen.',
              'formal_submission_sent':False}
    dump(dest/'manifest.json',manifest)
    entry={'name':NAME,'path':dest.relative_to(ROOT).as_posix(),'control':False,'hashes':hashes,'anchor':'public641','comparison_baseline':'public641','native_decode_reference':'public641'}
    dump(OUT/'hash17-entry.json',entry)
    audit={'status':'VERIFIED_STATIC_ONE_ENDPOINT_HASH_AND_SOURCE_PATCH_NOT_NATIVE','parent_hashes':{'parse.rs':RS,'Parse.lean':LEAN},'hashes':hashes,
           'changed_call_sites':6,'original_rows':calls,'old_hash_bits':15,'new_hash_bits':17,'old_allocated_head_bytes':524400,'new_allocated_head_bytes':524288,
           'same_emitter_mod4':0,'index_bound_model_cases':131072,'token_equivalence':'NOT_EXPECTED','native':'NOT_RUN','time':'NOT_RUN','gate':'NOT_RUN'}
    dump(OUT/'hash17-build-audit.json',audit);print(json.dumps({'candidate':NAME,'hashes':hashes,'call_sites':6},indent=2))


if __name__=='__main__':main()
