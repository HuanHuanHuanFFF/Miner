"""Small predecessor representation on newly published compression-side542."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-542';NAME='r13-542-abs15'

def sha(b):return hashlib.sha256(b).hexdigest()

def function_end(s,name):
    a=s.index('pub fn '+name);i=s.index('{',a)+1;depth=1
    while depth:
        depth+=(s[i]=='{')-(s[i]=='}');i+=1
    return a,i

def generate():
    raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};receipt=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(b)for f,b in raw.items()}==receipt['files']
    original=raw['parse.rs'].decode();start=original.index('pub fn pc_f_link<const H: usize>');_,end=function_end(original,'pc_run1c');old=original[start:end]
    prior=(ROOT/'references/round13-public-514/parse.rs').read_text()
    for n in('pc_f_link','pc_f_try','pc_f_deepen','pc_f_record3'):
        a,b=function_end(original,n);x,y=function_end(prior,n);assert original[a:b]==prior[x:y]
    body=old;edits=[('[u32; 32768]','[u16; 32768]',3),('prev[i % 32768] = head[a];','prev[i % 32768] = (head[a] as u16) & 32767;',1),('let c3 = prev[c2 % 32768] as usize;','let c3 = r13_542_unwrap(c2,prev[c2 % 32768]);',1),('let mut prev = [0u32; 32768];','let mut prev = [0u16; 32768];',1),('let cl = prev[c % 32768] as usize;','let cl = r13_542_unwrap(c,prev[c % 32768]);',1)]
    for x,y,n in edits:assert body.count(x)==n;body=body.replace(x,y)
    back=body
    for x,y,n in reversed(edits):assert back.count(y)==n;back=back.replace(y,x)
    assert back==old
    helper='''/// R13 modular PC predecessor hint; original byte/window validator decides emitted matches.
#[inline(always)]
pub fn r13_542_unwrap(c: usize, low: u16) -> usize {
    c.wrapping_sub(c.wrapping_sub(low as usize)&32767)
}

'''
    attr=original.rfind('#[inline(always)]',0,start);rust=(original[:attr]+helper+original[attr:start]+body+original[end:]).encode();assert rust.decode().replace(helper,'',1).replace(body,old,1)==original
    lean=raw['Parse.lean'].decode();ls=lean.index('theorem f_link_spec',lean.index('namespace PC'));le=lean.index('end PC',ls);section=lean[ls:le];assert section.count('Array Std.U32 32768#usize')==9;changed=section.replace('Array Std.U32 32768#usize','Array Std.U16 32768#usize');lat=lean.rfind('@[local step]',0,ls)
    lemma='''/-- Coordinate recovery is total; original match validator owns validity. -/
@[local step]
theorem r13_542_unwrap_spec (c : Std.Usize) (low : Std.U16) :
    slot.r13_542_unwrap c low ⦃ fun _ => True ⦄ := by
  rw [slot.r13_542_unwrap]
  step*
  all_goals first | trivial | scalar_tac

'''
    proof=(lean[:lat]+lemma+lean[lat:ls]+changed+lean[le:]).encode();files={'parse.rs':rust,'Parse.lean':proof};assert all(len(b)<=524288 for b in files.values())
    m={'candidate':NAME,'parent':'public542','comparison_baseline':'public542','formal_anchor_id':'542','native_relation':'decode_only','hashes':{f:sha(b)for f,b in files.items()},'parent_original_hashes':receipt['files'],
        'mechanism':'Only original PC predecessor ring changes U32→U16 modulo32768; reads reconstruct hints and retain original byte/window checks. PIM/O_A engines, rows and routes remain original542.',
        'difference_from_previous':'New legal published compression-side parent after546 dominates542. Four PC functions exact514, main uses equivalent explicit return and different allocation/routes; not reusing a514 performance coefficient or proof certificate.',
        'attribution':{'source':'Official public542; original source retained','author_hotkey':receipt['author_hotkey'],'reference':'references/round13-public-542/PROVENANCE.md'},
        'source_reversal':'Exact isolated PC region reversed and helper removed; every unrelated engine/route original. Nine PC proof parameter types adapted only; PIM U32 types untouched.',
        'proof_status':'DRAFT_UNCOMPILED; no derivative certificate; exact original gate mandatory','performance_status':'UNKNOWN; own542 anchor plus same-source shadow and direct total-compression time required',
        'semantic_status':'Token changes possible for expired modular hints; finite decode and original obligation required. No private compression/time guarantee.','formal_submission_sent':False,
        'stop_condition':'Any decode/panic error stops. A ~0.816% time gap at542 size to546 motivates one bounded screen; lack of actual viable geometry closes this fixed source.'}
    files['manifest.json']=(json.dumps(m,indent=2)+'\n').encode();return files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();files=generate();p=ROOT/'candidates'/NAME
    if args.check:assert all((p/f).read_bytes()==b for f,b in files.items())
    else:
        assert not p.exists();p.mkdir()
        for f,b in files.items():(p/f).write_bytes(b)
    print(json.dumps({'candidate':NAME,'hashes':{f:sha(b)for f,b in files.items()},'status':'DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
