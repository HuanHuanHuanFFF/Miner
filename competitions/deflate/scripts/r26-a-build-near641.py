"""Isolate the three public641 near-distance rejection guards."""
from pathlib import Path
import hashlib
import json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round26-public-641'
OUT=ROOT/'evidence/round26/route-a'
NAME='r26-a-641-allow-near'
RUST='97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181'
LEAN='7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e'


def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())


def main():
    rust=(BASE/'parse.rs').read_bytes();proof=(BASE/'Parse.lean').read_bytes()
    assert sha(rust)==RUST and sha(proof)==LEAN
    source=rust.decode();text=source
    guard='    if d>=2 && d<=8 && s.len()!=500000 {return (0,0);}\n'
    chain='    if d2>=2 && d2<=8 && s.len()!=500000 {return (l,d);}\n'
    assert text.count(guard)==2 and text.count(chain)==1
    changed=text.replace(guard,'').replace(chain,'')
    # Locate each edit inside its named function rather than matching filenames/routes.
    targets={'pc_probe_m':guard,'pc_probe_lazy':guard,'pc_f_try':chain}
    reversed_source=changed
    for name,line in targets.items():
        a=reversed_source.index('pub fn '+name+'(');b=reversed_source.index('\n}',a)
        body=reversed_source[a:b]
        marker='    let d2 = p.wrapping_sub(c2);\n' if name=='pc_f_try' else ('    let d = q.wrapping_sub(c);\n' if name=='pc_probe_lazy' else '    let d = p.wrapping_sub(c);\n')
        assert body.count(marker)==1
        body=body.replace(marker,marker+line)
        reversed_source=reversed_source[:a]+body+reversed_source[b:]
    assert reversed_source==source
    dest=ROOT/'candidates'/NAME;assert not dest.exists();dest.mkdir()
    (dest/'parse.rs').write_bytes(changed.encode());(dest/'Parse.lean').write_bytes(proof)
    hashes={'parse.rs':sha(changed.encode()),'Parse.lean':sha(proof)}
    manifest={'candidate':NAME,'parent':'references/round26-public-641','hashes':hashes,
              'attribution':{'source_receipt':'references/round26-public-641/source-receipt.json','author_hotkey':'5FYhJSAu4q86E2Yn8UjNvpbUQVZGzq5wB7W7YFqnmvz288yo','ownership':'Derivative of public641; original author/source preserved. Guard-free helper precedent is public631.'},
              'mechanism':'Remove only the three d2..8 early-rejection guards in PC primary/lazy/predecessor probes. Restored hints still pass the original range, key and byte-match checks. Do not add a new route or distance threshold.',
              'difference_from_old_work':'This is a specific public641 guard ablation; olderR25len3 far-distance economics do not cover this min4+ nearby-distance policy. Existing631 helpers provide the guard-free code precedent, but its other routing/search differences are not transferred.',
              'preserved':'All H values, hash functions, route/classifier, insertion/search depth, lazy settings, folding, emission and proof text; no trimhead/hash17/boundary combination.',
              'proof_interface':'PC.probe_m_spec, probe_lazy_spec and f_try_spec already establish FoundAt/MatchAt from the retained checks. Removal changes local extraction branches; copied641 Lean is unverified until exact original gate.',
              'quality_status':'UNKNOWN; more accepted matches can change later parsing and Huffman alphabets, so improvement is not assumed.',
              'time_status':'UNKNOWN','gate_status':'NOT_RUN','formal_submission_sent':False}
    dump(dest/'manifest.json',manifest)
    entry={'name':NAME,'path':dest.relative_to(ROOT).as_posix(),'control':False,'hashes':hashes,'anchor':'public641','comparison_baseline':'public641','native_decode_reference':'public641'}
    dump(OUT/'near641-entry.json',entry)
    dump(OUT/'near641-build-audit.json',{'status':'VERIFIED_THREE_GUARD_REMOVALS_AND_EXACT_REVERSAL_NOT_NATIVE','parent_hashes':{'parse.rs':RUST,'Parse.lean':LEAN},'hashes':hashes,'changed_functions':list(targets),'removed_guard_count':3,'source_reversal':True,'unchanged_proof':True,'native':'NOT_RUN','time':'NOT_RUN','gate':'NOT_RUN'})
    print(json.dumps({'candidate':NAME,'hashes':hashes},indent=2))


if __name__=='__main__':main()
