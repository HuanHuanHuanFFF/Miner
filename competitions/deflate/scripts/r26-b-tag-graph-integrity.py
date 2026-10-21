"""Cloud-only actual B15 finder argument/stripped-graph/full-tag-prefix integrity."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import subprocess

ROOT=Path(__file__).resolve().parents[1]
PARENT='5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9'
CANDIDATE='8974acb8e1c1087d1b4560fd2dc451d8d19c6e3e6f81905b81e9df9a3be4ecdf'
FIELDS=['finder_calls','raw_finder_bytes','preserved_original_records','tagged_records','tagged_bytevalid_records',
        'tagged_prefix_check_bytes','original_graph_logical_bytes','new_graph_logical_bytes','new_graph_capacity_bytes']
CHECK='''
    // This observer changes no candidate state; recompute the exact parent graph under actual args.
    let mut oldmp=Vec::<u32>::new();let mut oldmb=Vec::<u32>::new();
    crate::parent::a_find_all(s,&mut oldmp,&mut oldmb,depth,skip);
    assert_eq!(mp.len(),oldmp.len());assert_eq!(mp.len(),s.len()+1);
    let mut counts=[0u64;9];counts[0]=1;counts[1]=s.len()as u64;
    counts[6]=(oldmp.len()*4+oldmb.len()*4)as u64;
    counts[7]=(mp.len()*4+mb.len()*4)as u64;counts[8]=(mp.capacity()*4+mb.capacity()*4)as u64;
    let mut p=0usize;
    while p<s.len(){
        let mut j=mp[p]as usize;let end=mp[p+1]as usize;
        let mut oldj=oldmp[p]as usize;let oldend=oldmp[p+1]as usize;let oldstart=oldj;
        let maxlen=if oldj<oldend{(((oldmb[oldend-1]>>15)&255)+3)as usize}else{2};
        let mut seenextra=false;
        while j<end{
            let m=mb[j];
            if (m&R26_A_EXTRA)!=0{
                seenextra=true;counts[3]+=1;
                let len=(((m>>15)&255)+3)as usize;let dist=((m&32767)+1)as usize;
                assert!(len<=maxlen);assert!(check(s,p,len,dist));counts[4]+=1;counts[5]+=len as u64;
                let code=(m>>23)%32;let mut k=oldstart;let mut oldprefix=2usize;
                while k<oldend{let om=oldmb[k];assert_eq!(om&R26_A_EXTRA,0);if (om>>23)%32==code{let l=(((om>>15)&255)+3)as usize;if l>oldprefix{oldprefix=l;}}k+=1;}
                assert!(len>oldprefix);
            }else{
                assert!(!seenextra);assert!(oldj<oldend);assert_eq!(m,oldmb[oldj]);assert_eq!(m&R26_A_EXTRA,0);
                counts[2]+=1;oldj+=1;
            }
            j+=1;
        }
        assert_eq!(oldj,oldend);p+=1;
    }
    println!("R26_TAG_CONTEXT {} {} {} {} {} {}",s.len(),depth,skip,oldmp.len(),oldmb.len(),mb.len());
    for k in 0..9{R26_TAG_GRAPH[k].fetch_add(counts[k],Ordering::Relaxed);}
'''
EXTRA='''
use std::sync::atomic::{AtomicU64,Ordering};
static R26_TAG_GRAPH:[AtomicU64;9]=[const{AtomicU64::new(0)};9];
pub fn r26_tag_graph_take()->[u64;9]{std::array::from_fn(|i|R26_TAG_GRAPH[i].swap(0,Ordering::Relaxed))}
'''


def sha(raw):return hashlib.sha256(raw).hexdigest()


def instrument(raw):
    assert sha(raw)==CANDIDATE
    source=raw.decode();fn=importlib.import_module('prepare-round24-extract-repro').fn
    old=fn(source,'a_find_all');close=old.rfind('}')
    new=old[:close]+CHECK+old[close:]
    observed=(source.replace(old,new,1)+'\n'+EXTRA).encode()
    importlib.import_module('r26-b-fix-shared-cache').spans(observed.decode())
    return observed


def preflight(spec):
    assert spec.get('r26_b_tag_graph_integrity') is True and spec.get('native_encoder') is True
    candidate=next(row for row in spec['entries'] if row['name']=='r26-b-552-discarded')
    parent=next(row for row in spec['entries'] if row['name']=='public552')
    assert candidate['hashes']['parse.rs']==CANDIDATE and parent['hashes']['parse.rs']==PARENT
    assert sha((ROOT/parent['path']/'parse.rs').read_bytes())==PARENT
    observed=instrument((ROOT/candidate['path']/'parse.rs').read_bytes())
    return {'status':'VERIFIED_GRAPH_INTEGRITY_OBSERVER_STRUCTURE_ONLY','source_hashes':candidate['hashes'],
            'parent_hashes':parent['hashes'],'observer_sha256':sha(observed),'fields':FIELDS,
            'scope':'Actualcandidate finder arguments versusparent, per-position untaggedgraph byte identity/newtag suffix/fullprefixcheck; candidateplain vsobserver token/decode equality. No native/fullgate result yet.'}


def main():
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    spec=importlib.import_module('round4').validate(os.environ['ROUND4_SPEC']);preflight(spec)
    candidate=next(row for row in spec['entries'] if row['name']=='r26-b-552-discarded')
    parent=next(row for row in spec['entries'] if row['name']=='public552')
    build=Path(os.environ['RUNNER_TEMP'])/'r26-b-tag-graph';build.mkdir()
    out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-b-tag-graph';out.mkdir(parents=True)
    observed=build/'observed.rs';observed.write_bytes(instrument((ROOT/candidate['path']/'parse.rs').read_bytes()))
    harness=importlib.import_module('research-round13-counts').HARNESS
    harness=harness.replace('#[path="FROZEN"] mod frozen;', '#[path="PARENT"] mod parent;\n#[path="FROZEN"] mod frozen;')
    harness=harness.replace('PARENT',str(ROOT/parent['path']/'parse.rs')).replace('FROZEN',str(ROOT/candidate['path']/'parse.rs')).replace('OBSERVED',str(observed))
    harness=harness.replace('observed::r13_take()','observed::r26_tag_graph_take()').replace('R13_COUNT','R26_TAG_GRAPH')
    driver=build/'driver.rs';driver.write_text(harness);binary=build/'check'
    compile=subprocess.run(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],capture_output=True,text=True,timeout=240)
    (out/'compile.log').write_text(compile.stdout+compile.stderr);assert compile.returncode==0
    corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    run=subprocess.run([str(binary),str(corpus)],capture_output=True,text=True,timeout=480)
    (out/'run.log').write_text(run.stdout+run.stderr);assert run.returncode==0
    rows=[];contexts=[]
    for line in run.stdout.splitlines():
        if line.startswith('R26_TAG_CONTEXT '):
            values=list(map(int,line.split()[1:]));assert len(values)==6
            contexts.append(dict(zip(['raw_bytes','depth','skip','original_offset_words','original_record_words','new_record_words'],values)))
            continue
        if not line.startswith('R26_TAG_GRAPH '):continue
        _,name,size,*values=line.split();assert len(values)==len(FIELDS);data=(corpus/name).read_bytes();assert len(data)==int(size)
        counts=dict(zip(FIELDS,map(int,values)));assert counts['finder_calls']==len(contexts)
        assert all(context['raw_bytes']==len(data) for context in contexts)
        assert sum(context['new_record_words']-context['original_record_words'] for context in contexts)==counts['tagged_records']
        rows.append({'file':name,'raw_bytes':len(data),'input_sha256':sha(data),'counts':counts,'actual_finder_contexts':contexts});contexts=[]
    assert not contexts
    assert len(rows)==28 and sum(row['raw_bytes'] for row in rows)==15930000
    totals={field:sum(row['counts'][field] for row in rows) for field in FIELDS}
    assert totals['tagged_records']==totals['tagged_bytevalid_records']
    result={'status':'VERIFIED_NATIVE_UNTAGGED_PARENT_GRAPH_IDENTITY_AND_ALL_TAGGED_PREFIXES_VALID',
            'run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
            'source_hashes':candidate['hashes'],'parent_hashes':parent['hashes'],'observer_sha256':sha(observed.read_bytes()),'driver_sha256':sha(driver.read_bytes()),
            'rows':rows,'totals':totals,'max_perfile_new_graph_capacity_bytes':max(row['counts']['new_graph_capacity_bytes'] for row in rows),
            'scope':'Actualcandidate allfinder args: every originalperposition record retained identical/inorder; extras are suffix/tagbit30, <=oldmaxlength, strictlynovel samecode prefix and fullybytevalid. Plaincandidate vsobserver28tokens/decode equal.',
            'limits':['Finitepublic graph/prefix identity is not a universal proof or originalobligation/gate acceptance.',
                      'Observer parent-recomputation/prefixcheck costs are separate from productioncandidate fullA profile; no speed claim.',
                      'Logical/capacity graph bytes notprocessRSS; perfilemax and sum separate. No formal/admission/reward.']}
    (out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(totals))


if __name__=='__main__':main()
