"""One full-source discarded-prefix A candidate; isolate tagged records from old state."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round24-public-552'
TARGET=ROOT/'candidates/r26-b-552-discarded'
PAIR={'parse.rs':'5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9',
      'Parse.lean':'51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592'}
EXTRA='''
pub const R26_A_EXTRA:u32=0x40000000;
// Epochs and touched codes avoid a full per-position 32-slot reset/scan.
pub fn r26_a_discard_offer(pos:usize,l:usize,d:usize,epochs:&mut[usize;32],lengths:&mut[usize;32],distances:&mut[usize;32],codes:&mut[usize;32],count:usize)->usize{
    let code=(a_slot_of((d.wrapping_sub(1))as u32)%32)as usize;
    if epochs[code]!=pos+1{
        epochs[code]=pos+1;lengths[code]=l;distances[code]=d;
        if count<32{codes[count]=code;count+1}else{count}
    }else{
        if l>lengths[code]||(l==lengths[code]&&d<distances[code]){lengths[code]=l;distances[code]=d;}
        count
    }
}
pub fn r26_a_discard_finish(mb:&Vec<u32>,start:usize,lengths:&[usize;32],distances:&[usize;32],codes:&[usize;32],count:usize,pending:&mut[u32;32])->usize{
    let mut n=0usize;let mut k=0usize;
    while k<count&&k<32{
        let code=codes[k]%32;let mut old=2usize;let mut j=start;
        while j<mb.len(){let m=mb[j];if ((m>>23)%32)as usize==code{let l=(((m>>15)&255)+3)as usize;if l>old{old=l;}}j+=1;}
        let l=lengths[code];let d=distances[code];
        if l>old&&l>=3&&l<=258&&d>=1&&d<=32768&&n<32{
            pending[n]=R26_A_EXTRA|((d-1)as u32)|(((l-3)as u32)<<15)|((code as u32)<<23);n+=1;
        }
        k+=1;
    }
    n
}
// Only genuine new same-code prefix lengths may affect the cost/choice.
pub fn r26_a_discard_best(cost:&Vec<u32>,lc:&[u32;512],dc:&[u32;32],mb:&Vec<u32>,i:usize,start:usize,end:usize,top:usize,bias:u32,il:usize,id:usize)->(u32,u32){
    let mut best=4294967295u32;let mut bd=0u32;let mut x=end;
    while x<top&&x<mb.len(){
        let item=mb[x];let code=((item>>23)%32)as usize;let len=(((item>>15)&255)+3)as usize;
        let mut oldprefix=2usize;let mut j=start;
        while j<end&&j<mb.len(){let m=mb[j];if ((m>>23)%32)as usize==code{let l=(((m>>15)&255)+3)as usize;if l>oldprefix{oldprefix=l;}}j+=1;}
        if il>=3&&id>=1&&(a_slot_of((id-1)as u32)%32)as usize==code&&il>oldprefix{oldprefix=il;}
        let price=dc[code];let base=price.wrapping_add(bias);let mut prev=i+2;j=start;
        while j<end&&j<mb.len(){
            let m=mb[j];let stop=i+(((m>>15)&255)+3)as usize;
            if stop<cost.len()&&m<0x80000000&&price<dc[((m>>23)%32)as usize]{
                let mut lo=prev+1-i;if lo<=oldprefix{lo=oldprefix+1;}
                let hi=if len<stop-i{len}else{stop-i};let mut l=lo;
                while l<=hi&&l<=258{
                    let v=(cost[i+l].wrapping_add(lc[l%512]).wrapping_add(base)<<9)|(l as u32);
                    if v<best{best=v;bd=item&32767;}l+=1;
                }
            }
            if stop>prev{prev=stop;}j+=1;
        }
        x+=1;
    }
    (best,bd)
}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()


def generate():
    raw={name:(BASE/name).read_bytes() for name in PAIR}
    assert {name:sha(data) for name,data in raw.items()}==PAIR
    source=raw['parse.rs'].decode()
    fn=importlib.import_module('prepare-round24-extract-repro').fn
    edits={}
    tree=fn(source,'a_tree_insert')
    anchor='    mb: &mut Vec<u32>,\n) -> usize {'
    assert tree.count(anchor)==1
    tree=tree.replace(anchor,'''    mb: &mut Vec<u32>,
    r26_epochs:&mut[usize;32],r26_lengths:&mut[usize;32],r26_distances:&mut[usize;32],r26_codes:&mut[usize;32],r26_pending:&mut[u32;32],
) -> (usize,usize) {''',1)
    anchor='    let oldest = if pos > 32767'
    tree=tree.replace(anchor,'    let r26_start=mb.len();let mut r26_count=0usize;\n'+anchor,1)
    anchor='        let lr = a_probe(s, cr - 1, pos, 0).0;'
    tree=tree.replace(anchor,anchor+'\n        if lr>=3&&lr<=best{r26_count=r26_a_discard_offer(pos,lr,pos-cr+1,r26_epochs,r26_lengths,r26_distances,r26_codes,r26_count);}',1)
    anchor='        let l = r.0;'
    tree=tree.replace(anchor,anchor+'\n        if l>=3&&l<=best{r26_count=r26_a_discard_offer(pos,l,pos-p,r26_epochs,r26_lengths,r26_distances,r26_codes,r26_count);}',1)
    anchor='    best\n}'
    assert tree.count(anchor)==1
    tree=tree.replace(anchor,'    let r26_n=r26_a_discard_finish(mb,r26_start,r26_lengths,r26_distances,r26_codes,r26_count,r26_pending);\n    (best,r26_n)\n}',1)
    edits['a_tree_insert']=tree
    finder=fn(source,'a_find_all')
    anchor='    let n = s.len();'
    finder=finder.replace(anchor,anchor+'\n    let mut r26_epochs=[0usize;32];let mut r26_lengths=[0usize;32];let mut r26_distances=[0usize;32];let mut r26_codes=[0usize;32];let mut r26_pending=[0u32;32];',1)
    anchor='                let best = a_tree_insert(s, &mut head, &mut kid, &mut h3, &mut rct, i, pre, depth, mb);'
    assert finder.count(anchor)==1
    finder=finder.replace(anchor,'''                let r26_pair=a_tree_insert(s,&mut head,&mut kid,&mut h3,&mut rct,i,pre,depth,mb,&mut r26_epochs,&mut r26_lengths,&mut r26_distances,&mut r26_codes,&mut r26_pending);
                let best=r26_pair.0;''',1)
    anchor='''                if nh == pre.2 {
                    nr = i + 1;
                    nc = i + 1;
                }'''
    assert finder.count(anchor)==1
    finder=finder.replace(anchor,anchor+'''
                // Original CD read and all finder state updates finish before extras append.
                let mut r26_k=0usize;
                while r26_k<r26_pair.1&&r26_k<32{if mb.len()<mb.len().saturating_add(1){mb.push(r26_pending[r26_k]);}r26_k+=1;}''',1)
    edits['a_find_all']=finder
    dp=fn(source,'a_dp_pass')
    anchor='            let j0 = mp[i] as usize;'
    dp=dp.replace(anchor,'''            let r26_el=if xl+1>258{258}else{xl+1};
            let r26_il=if xl>=3&&xd>=1&&xd<=i&&s[i]==s[i-xd]{r26_el}else{0};let r26_id=xd;
''' + anchor,1)
    anchor='            let top = if e < mb.len() { e } else { mb.len() };'
    dp=dp.replace(anchor,anchor+'''
            // Tagged suffixes never enter original lo/prev/pd/XL/XD recurrence.
            let mut r26_end=top;
            while r26_end>j0&&(mb[r26_end-1]&R26_A_EXTRA)!=0{r26_end-=1;}''',1)
    anchor='            while j < top {'
    assert dp.count(anchor)==1
    dp=dp.replace(anchor,'            while j < r26_end {',1)
    anchor='            a_store_choice(cost, ch, i, best, bd, nxt);'
    dp=dp.replace(anchor,'''            if r26_end<top{
                let r26_pair=r26_a_discard_best(cost,lc,dc,mb,i,j0,r26_end,top,bias,r26_il,r26_id);
                if r26_pair.0<best{best=r26_pair.0;bd=r26_pair.1;}
            }
''' + anchor,1)
    edits['a_dp_pass']=dp
    observed=source
    for name,new in edits.items():
        old=fn(source,name)
        assert new!=old and observed.count(old)==1
        observed=observed.replace(old,new,1)
    rust=(observed+'\n'+EXTRA).encode()
    reverse=observed
    for name,new in edits.items():reverse=reverse.replace(new,fn(source,name),1)
    assert reverse.encode()==raw['parse.rs']
    spans=importlib.import_module('r26-b-fix-shared-cache').spans(rust.decode())
    assert all(name in spans for name in ['r26_a_discard_offer','r26_a_discard_finish','r26_a_discard_best'])
    assert finder.index('cd = ((mb[mb.len() - 1]') < finder.index('mb.push(r26_pending')
    assert all(statement in dp for statement in ['xl = el;','xl = prev - i;','xd = pd;','a_store_choice(cost, ch, i, best, bd, nxt);'])
    files={'parse.rs':rust,'Parse.lean':raw['Parse.lean']}
    receipt=json.loads((BASE/'source-receipt.json').read_bytes())
    manifest={'candidate':TARGET.name,'parent':BASE.relative_to(ROOT).as_posix(),'formal_parent_id':'552',
        'parent_hashes':PAIR,'hashes':{name:sha(data) for name,data in files.items()},'bytes':{name:len(data) for name,data in files.items()},
        'source_author_hotkey':receipt['author_hotkey'],'source_receipt':'references/round24-public-552/source-receipt.json',
        'source_receipt_sha256':sha((BASE/'source-receipt.json').read_bytes()),
        'mechanism':'Retain one longest already-probed discarded prefix per distancecode only beyond existing cachedsamecode max length. Fullsource, no extra search depth. Tagged suffix records enter only controlled novel-length lower-dcprice wrappedpacked consumer after oldfinalbest.',
        'producer_cost':'Epoch/touched-code32scratch reused withinfinder, scan only touchedcodes. Pending32array appended to primarymb after originalCD/skip state updates. Full additional record storage and all maintenance paid.',
        'consumer_cost':'Tagged suffix stripped from originalrecordloop. Newhelper scans realoriginalrecords for samecode availability, removes inheritedsamecode source, then queries genuine newlength ranges only if lowerdcprice. No raw-argmin or nonwrap assumption.',
        'tag_boundary':'bit30 cannot enter originalCD-lastrecord read, original lo/prev/pd/XL/XD or plain emittedtoken. Only a_find_all and a_dp_pass directly index A mb; otherA users pass it onward; a_walk reads untaggedch.',
        'scope':'a_tree_insert returnpair/internalscratch, a_find_all append boundary, a_dp_pass boundedextra consumer plus threehelpers. Routes/price/passes/a_walk/fixedrecords/emitter and all otherengines retained.',
        'predecessor_evidence':'evidence/round26/route-b/b14-discarded-feedback.json','source_reversal':'Restore exactthreeoriginalfunctions and remove appendedhelpers -> pinned552 byte exact, checked locally.',
        'quality_status':'UNKNOWN_UNTIL_FULL28ORIGINALENCODER; no sample×32 extrapolation',
        'proof_status':'UNADAPTED_PARENT_DRAFT; actualre-extraction/helper-loop proofs/fulloriginalgate required if valuable',
        'performance_status':'NOT_RUN; complete lowfrequency A cost first; no originalpaired result',
        'formal_status':'NOT_SUBMITTED; formal/private/reward UNKNOWN'}
    files['manifest.json']=(json.dumps(manifest,indent=2)+'\n').encode()
    assert all(0<len(value)<=524288 for name,value in files.items() if name!='manifest.json')
    return files,manifest


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--check',action='store_true');args=parser.parse_args()
    files,manifest=generate();TARGET.mkdir(exist_ok=True)
    for name,raw in files.items():
        path=TARGET/name
        if args.check:assert path.read_bytes()==raw
        else:assert not path.exists() or path.read_bytes()==raw;path.write_bytes(raw)
    print(json.dumps({'candidate':TARGET.name,'hashes':manifest['hashes'],'bytes':manifest['bytes']}))


if __name__=='__main__':main()
