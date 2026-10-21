"""Normalize only expired nonzero hints, retaining coherent-word cache invariants."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-514';NAME='r13-514-expired0'
HELPER='''/// A nonzero position already outside the window cannot become valid as the query advances.
#[inline(always)]
pub fn r13_pc_window_hint(i: usize, c: usize) -> usize {
    if c != 0 && c < i && i-c > 32768 { 0 } else { c }
}

'''
LEMMA='''/-- The normalized position never exceeds the original head bound. -/
@[local step]
theorem r13_pc_window_hint_spec (i c : Std.Usize) :
    slot.r13_pc_window_hint i c ⦃ fun r => r.val ≤ c.val ⦄ := by
  rw [slot.r13_pc_window_hint]
  step*
  repeat' (split <;> step*)
  all_goals scalar_tac

'''

def sha(b):return hashlib.sha256(b).hexdigest()

def generate():
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};origin=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(b)for f,b in raw.items()}==origin['files']
    original=raw['parse.rs'].decode();a=original.index('pub fn pc_ahead_m<const H: usize>');b=original.index('/// `pc_ahead_if`',a);old=original[a:b]
    before='    let c = head[a] as usize;';after='    let raw_c = head[a] as usize;\n    let c = r13_pc_window_hint(i,raw_c);';assert old.count(before)==1;changed=old.replace(before,after,1)
    rust=original[:a]+changed+original[b:];marker='/// `pc_ahead` with keys under `km`.';assert rust.count(marker)==1;rust=rust.replace(marker,HELPER+marker,1)
    assert rust.replace(HELPER,'',1).replace(changed,old,1).encode()==raw['parse.rs']
    lean=raw['Parse.lean'].decode();a=lean.index('namespace PC');b=lean.index('end PC',a);section=lean[a:b];marker='@[local step]\ntheorem ahead_m_spec';assert section.count(marker)==1;section=section.replace(marker,LEMMA+marker,1);proof=(lean[:a]+section+lean[b:]).encode();assert proof.decode().replace(LEMMA,'',1).encode()==raw['Parse.lean']
    files={'parse.rs':rust.encode(),'Parse.lean':proof};assert all(len(x)<=524288 for x in files.values())
    m={'candidate':NAME,'parent':'public514','formal_anchor_id':'514','comparison_baseline':'public514','native_relation':'token_equality','hashes':{f:sha(x)for f,x in files.items()},'parent_original_hashes':origin['files'],
        'mechanism':'Only PC ahead query positions already more than32768 after a nonzero head normalize that hint to0. Still load actual word at resulting position, retaining original coherent-word and head-bound invariants. Original table stores, query order, valid candidates, insertion keys and routes unchanged.',
        'evidence_basis':'Original observer:3700174 ahead calls,689313 expired nonzero candidates (18.63%). Excludes already-hot zero sentinel. Logical opportunity count is not measured cold loads or saved time.',
        'difference_from_previous':'Matched-path skip lost1.299% despite preserved bytes. This keeps valid-word prefetch/order and only replaces window-invalid hints, with a simpler monotone bound proof bridge.',
        'attribution':{'source':'Official public514; original headers retained','author_hotkey':origin['author_hotkey'],'reference':'references/round13-public-514/PROVENANCE.md'},
        'source_reversal':'Remove one helper and reverse one PC ahead statement; original bytes restored. Lean adds only monotone hint lemma.',
        'equality_status':'INFERRED: old hint invalid at queryi, zero also invalid sincei>32768; cache refreshes for earlier actual endpoints. Strict finite/public equality required, no all-input certificate.',
        'proof_status':'DRAFT_UNCOMPILED; monotone bound bridge should feed original ahead macro; original full obligation mandatory',
        'performance_status':'UNKNOWN; extra branch and reduced cache-fix reuse may outweigh eliminated old-word work','formal_submission_sent':False,
        'stop_condition':'Any finite/public token or decode mismatch stops source. No worthwhile repeated paired time improvement closes this fixed implementation; full exact gate mandatory for promotion.'}
    files['manifest.json']=(json.dumps(m,indent=2)+'\n').encode();return files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();p=ROOT/'candidates'/NAME
    if args.check:assert all((p/f).read_bytes()==x for f,x in files.items())
    else:
        assert not p.exists();p.mkdir()
        for f,x in files.items():(p/f).write_bytes(x)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(x)for f,x in files.items()},'status':'DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
