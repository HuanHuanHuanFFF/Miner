"""Price-aware auxiliary choice; useful original short fallback always retained."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'candidates/r13-514-ef32-aux4'

def sha(b):return hashlib.sha256(b).hexdigest()

def generate(kind):
    assert kind in('gain','seven');m=json.loads((BASE/'manifest.json').read_bytes());raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};assert {f:sha(b)for f,b in raw.items()}==m['hashes']
    old='if l4>l { (l4,c4) } else { (l,c) }'
    condition='l4>=3 && l4>l && (l<3 || pc_gain(l4,p-c4)>pc_gain(l,p-c))'if kind=='gain'else'l4>=7 && l4>l'
    new='if '+condition+' { (l4,c4) } else { (l,c) }';text=raw['parse.rs'].decode();assert text.count(old)==1;changed=text.replace(old,new,1);assert changed.replace(new,old,1)==text
    n='r13-514-ef32-aux4-'+kind;files={'parse.rs':changed.encode(),'Parse.lean':raw['Parse.lean']}
    manifest={**m,'candidate':n,'parent':'r13-514-ef32-aux4','comparison_baseline':'r13-514-ef32-aux4','hashes':{f:sha(b)for f,b in files.items()},'parent_variant_hashes':m['hashes'],
        'mechanism':'Keep primary3-byte match unless strictly longer fourth-key match also wins existing PC estimated literal/length/distance score.'if kind=='gain'else'Keep primary3-byte fallback; auxiliary match must cover at least7 bytes (one extra aligned element) and be strictly longer.',
        'evidence_basis':'Aux4 recovered longer matches and lowered11215 tokens, but real output grew3485B. Original3-byte price replay showed almost all short matches profitable. Added-byte coverage alone did not price longer/farther matches.',
        'difference_from_previous':'One choice predicate changes; all primary useful3-byte matches, original routing and auxiliary maintenance stay fixed. Seven is a complete-element control, not raising the primary minimum length.',
        'score_assumptions':'Gain uses existing pc_HLIT/16=5bit literal and pc_GBASE/16=10.5bit base; proxy does not include learned block code lengths/header shifts. Exact unchanged encoder replay decides whether to allocate paired timing.',
        'source_reversal':'Reverse the single auxiliary choice predicate to recover exact aux4 parent; no other bytes change.',
        'proof_status':'PARENT_PROOF_UNADAPTED; gain arithmetic is short-circuit guarded by original validated lengths/candidates; original full obligation remains mandatory',
        'performance_status':'UNKNOWN; finite exact encoder first, then total-time and independent confirmation only if sufficient gain'}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return n,files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    for kind in('gain','seven'):
        n,files=generate(kind);p=ROOT/'candidates'/n
        if args.check:assert all((p/f).read_bytes()==b for f,b in files.items())
        else:
            assert not p.exists();p.mkdir()
            for f,b in files.items():(p/f).write_bytes(b)
        print(json.dumps({'candidate':n,'hashes':{f:sha(b)for f,b in files.items()},'status':'DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
