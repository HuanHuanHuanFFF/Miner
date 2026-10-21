"""Reuse a denser short-input PC mechanism without changing shared large-input engines."""
from pathlib import Path
import hashlib,json

ROOT=Path(__file__).resolve().parents[1]


def function(text,name):
    start=text.index('pub fn '+name+'<')
    opening=text.index('{',start);end=opening+1;depth=1
    while depth:
        depth+=(text[end]=='{')-(text[end]=='}');end+=1
    return text[start:end]


def main():
    parent=ROOT/'candidates/r22-595-chain-halfhead';raw=(parent/'parse.rs').read_bytes()
    assert hashlib.sha256(raw).hexdigest()=='57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275'
    reference=ROOT/'references/round18-public-584/parse.rs'
    assert hashlib.sha256(reference.read_bytes()).hexdigest()=='82297feee16db3fe6af50fe07f034b81d73d7189a40a829b78b44db167410cf2'
    text=raw.decode();record=function(text,'pc_record3_m');run=function(text,'pc_run1')
    assert record.count('pc_INS_MAX')==2 and run.count('pc_record3_m::<H>')==1
    record_new=record.replace('pub fn pc_record3_m','pub fn r25_tiny_pc_record8').replace('pc_INS_MAX','8usize')
    run_new=run.replace('pub fn pc_run1','pub fn r25_tiny_pc_run1').replace('pc_record3_m::<H>','r25_tiny_pc_record8::<H>')
    before='pub fn p125_row12(input:&[u8],out:&mut[u32])->usize{et_tiny(input,out,302256384)}'
    after='pub fn p125_row12(input:&[u8],out:&mut[u32])->usize{r25_tiny_pc_run1::<32768>(input,out,6,16,1000000,4294967295)}'
    assert text.count(before)==1
    suffix='\n// R25 short-input PC mechanism: fixed8 head inserts, existingverified emitter.\n#[inline(always)]\n'+record_new+'\n\n#[inline(always)]\n'+run_new+'\n'
    changed=text.replace(before,after)+suffix
    assert changed.removesuffix(suffix).replace(after,before).encode()==raw
    out=ROOT/'candidates/r25-root-tiny-pc8';assert not out.exists();out.mkdir()
    (out/'parse.rs').write_bytes(changed.encode());(out/'Parse.lean').write_bytes((parent/'Parse.lean').read_bytes())
    manifest={'candidate':out.name,'parent':parent.name,'hashes':{f:hashlib.sha256((out/f).read_bytes()).hexdigest()for f in ['parse.rs','Parse.lean']},
        'mechanism':'Replace only the inherited tiny row12 ETINY engine with a dedicatedPC run1 using unrestricted validatedmatch lengths, lazy16 and8headinsertions. Clone the record/main functions so otherPC paths remain byte-identical. Existing routing is preserved; no new file identifiers or length conditions.',
        'difference_from_old_work':'The prior tiny-tail only repaired fragmentation of existingETINY allowed lengths and saved8B. This tests a different existingmatcher/emitter strategy motivated by an actual332B public584 advantage. It is not a length-mask or density sweep.',
        'reference_differences':'Public584 used H32769 and its parity-selected checkedemitter. This variant uses the currentparent H32768 and alreadyverified pc_put_match; no extra redundant validation or oddtable chosen for a timingwindow. Exactpublic584 bytes/time are not assumed.',
        'attribution':{'source':'references/round21-public-595/source-receipt.json','mechanism_reference':'references/round18-public-584/source-receipt.json','evidence':'evidence/round25/luna/tiny-alternatives.json'},
        'proof_status':'DRAFT_PARENT_PROOF_NOT_ADAPTED_FOR_NEW_LOCAL_FUNCTIONS','performance_status':'NOT_RUN','formal_submission_sent':False}
    (out/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps(manifest,indent=2))


if __name__=='__main__':main()
