"""One existing predecessor recovers primary misses; primary depth unchanged."""
from pathlib import Path
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1];BASE=ROOT/'references/round13-public-514'
HELPER='''/// Preserve original primary deepening; recover one valid predecessor only after a live primary miss.
#[inline(always)]
pub fn r13_pc_find_rescue(s: &[u8], prev: &[u32;32768], c: usize, cw: u64, p: usize, km: u32, dp: usize, minl: usize) -> (usize,usize) {
    let f=pc_probe_m(s,c,cw,p,km);
    if f.0>=3 {
        let cl=prev[c%32768]as usize;
        pc_f_deepen(s,prev,c,cl,p,f.0,f.1,dp,minl)
    } else if c<p && p-c<=32768 {
        let cl=prev[c%32768]as usize;
        if cl<c && p-cl<=32768 {
            let w=pc_be8(s,cl);
            let g=pc_probe_m(s,cl,w,p,km);
            if CONDITION {g}else{(0,0)}
        }else{(0,0)}
    }else{f}
}

'''

def sha(b):return hashlib.sha256(b).hexdigest()

def generate(kind):
    assert kind in('one','gain');raw={f:(BASE/f).read_bytes()for f in('parse.rs','Parse.lean')};origin=json.loads((BASE/'receipt.json').read_bytes());assert {f:sha(b)for f,b in raw.items()}==origin['files']
    original=raw['parse.rs'].decode();a=original.index('pub fn pc_run1c<const H: usize>');b=original.index('/// Structured binaries (class 3)',a);old=original[a:b];body=old
    x='            let f = pc_probe_m(input, c, cw, p, km);';y='            let f = r13_pc_find_rescue(input,&prev,c,cw,p,km,dp,minl);';assert body.count(x)==1;body=body.replace(x,y,1)
    x='''                let cl = prev[c % 32768] as usize;
                let g = pc_f_deepen(input, &prev, c, cl, p, f.0, f.1, dp, minl);
                let mut l = g.0;
                let mut d = g.1;'''
    y='''                let mut l = f.0;
                let mut d = f.1;''';assert body.count(x)==1;body=body.replace(x,y,1)
    condition='g.0>=3 && g.0>=minl'+(' && pc_gain(g.0,g.1)>0'if kind=='gain'else'');helper=HELPER.replace('CONDITION',condition)
    rust=original[:a]+body+original[b:];marker='/// `pc_run1` with chain links and `pc_f_deepen` at every match of at least `minl` bytes.';assert rust.count(marker)==1;rust=rust.replace(marker,helper+marker,1)
    assert rust.replace(helper,'',1).replace(body,old,1).encode()==raw['parse.rs']
    n='r13-514-rescue-'+kind;files={'parse.rs':rust.encode(),'Parse.lean':raw['Parse.lean']};assert all(len(x)<=524288 for x in files.values())
    manifest={'candidate':n,'parent':'public514','formal_anchor_id':'514','comparison_baseline':'public514','native_relation':'decode_only','hashes':{f:sha(x)for f,x in files.items()},'parent_original_hashes':origin['files'],
        'mechanism':'Preserve original first-hit deeper search. After a live primary failure, inspect one valid predecessor with original masked byte probe; require original minimum length'+(' and positive existing length/distance gain proxy.'if kind=='gain'else'.'),
        'evidence_basis':'Original observer824975 misses,232705 live-head misses,107435 older-live candidates; one predecessor recovered28382 matches/181442 covered bytes, full original depth29428/187955. Covered bytes not encoded savings.',
        'difference_from_previous':'Changes which failed-primary positions can recover a match, not blind maximum-depth widening. One step captures most observed recovery; expired/future predecessor words never loaded. Primary matched behavior unchanged.',
        'attribution':{'source':'Official public514; original headers retained','author_hotkey':origin['author_hotkey'],'reference':'references/round13-public-514/PROVENANCE.md'},
        'source_reversal':'Remove one helper and reverse isolated main probe/deepen block to restore exact parent bytes; all routes and other engines unchanged.',
        'proof_status':'PARENT_PROOF_UNADAPTED_FOR_NEW_FIND_HELPER; proof bridge can reuse coherent-word primary probe and original matched deepening, plus guarded predecessor probe',
        'semantic_status':'Token/search positions intentionally change. All selected matches pass original pc_probe_m bytes and window checks; longer recovery is not monotone encoded improvement.',
        'performance_status':'UNKNOWN; native original-encoder first before paired time/proof spending','formal_submission_sent':False,
        'stop_condition':'Any decode/panic error stops source; insufficient final two-axis change closes it. Fresh extraction/original gate and independent confirmation mandatory before promotion.'}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode();return n,files

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    for kind in('one','gain'):
        n,files=generate(kind);p=ROOT/'candidates'/n
        if args.check:assert all((p/f).read_bytes()==x for f,x in files.items())
        else:
            assert not p.exists();p.mkdir()
            for f,x in files.items():(p/f).write_bytes(x)
        print(json.dumps({'candidate':n,'hashes':{f:sha(x)for f,x in files.items()},'status':'DRAFT_NOT_RUN'}))

if __name__=='__main__':main()
