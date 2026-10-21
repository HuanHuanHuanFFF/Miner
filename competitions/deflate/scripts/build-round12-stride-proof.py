"""Prepare an uncompiled strideword proof bridge; original obligation stays intact."""
from pathlib import Path
import hashlib, json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r12-fast-strideword'
DEST=ROOT/'candidates/r12-fast-strideword-proof'

def sha(b):return hashlib.sha256(b).hexdigest()

def main():
    rust=(BASE/'parse.rs').read_bytes()
    parent=(BASE/'Parse.lean').read_bytes()
    assert sha(rust)=='bcbdc69254ece1bbc2a0a25dcc6ff66165595ce09bb754f37e221558711ffcd5'
    assert sha(parent)=='e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04'
    text=parent.decode()
    start=text.rfind('@[local step]',0,text.index('theorem st_find_loop_spec'))
    end=text.index('/-- Three byte comparisons',start)
    removed=text[start:end]
    assert removed.count('theorem ')==1 and 'slot.st_find_loop' in removed
    changed=text[:start]+text[end:]
    start=changed.index('theorem st_find_spec')
    end=changed.index('/-- The leading literals',start)
    body=changed[start:end]
    before='  all_goals first\n    | exact FoundAt.none\' s p.val'
    after='  all_goals first\n    | scalar_tac\n    | exact FoundAt.none\' s p.val'
    assert body.count(before)==1
    body=body.replace(before,after,1)
    changed=changed[:start]+body+changed[end:]
    assert 'slot.st_find_loop' not in changed
    assert 'slot.common_from s a b cap k0' in changed
    assert changed[changed.index('theorem parse_spec'):]==text[text.index('theorem parse_spec'):]
    files={'parse.rs':rust,'Parse.lean':changed.encode()}
    manifest={'candidate':DEST.name,'parent':BASE.relative_to(ROOT).as_posix(),
        'hashes':{f:sha(b)for f,b in files.items()},'rust_same_as_screened_candidate':True,
        'attribution':json.loads((BASE/'manifest.json').read_bytes())['attribution'],
        'proof_status':'DRAFT_UNCOMPILED; no fresh original gate accepted',
        'bridge':'Delete obsolete st_find_loop_spec; existing common_from_spec discharges bounded extension seeded by unchanged Matches.three. Add arithmetic closure to st_find_spec. Original parse_spec and obligation tail byte-identical.',
        'actual_extraction_check':'PENDING; bind actual Funs.lean hash before any full gate claim',
        'formal_submission_sent':False}
    files['manifest.json']=(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n').encode()
    assert not DEST.exists()
    DEST.mkdir()
    for f,b in files.items():(DEST/f).write_bytes(b)
    print(json.dumps({'candidate':DEST.name,'hashes':manifest['hashes'],'proof_status':manifest['proof_status']}))

if __name__=='__main__':main()
