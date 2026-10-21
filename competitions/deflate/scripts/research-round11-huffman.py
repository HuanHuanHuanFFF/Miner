"""Runner-only read-only D Huffman-table diagnostic; no candidate is generated."""
from pathlib import Path
import argparse, hashlib, json, os, subprocess

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'candidates/r10-finder-pipeline-proof/parse.rs'
BASE_SHA='b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf'
MANIFEST=ROOT/'evidence/round11/37722786008/probe-a/gate/round1-r10-finder-pipeline-proof.jsonl'

CAPTURE=r'''
pub fn r11_huff_capture(freq: &[u32;288], m:usize, len:&mut [u8;288], ck:usize, role:usize)->u32 {
    crate::hdiag::reset_depth();
    let result=d_huff(freq,m,len);
    crate::hdiag::record(freq,m,len,result,ck,role);
    result
}
'''

HARNESS=r'''
#![allow(dead_code,unused_variables)]
#[path="frozen.rs"] mod frozen;
#[path="observed.rs"] mod observed;
#[path="official_pm.rs"] mod official_pm;
mod hdiag {
    use std::sync::atomic::{AtomicUsize,Ordering};
    static CASE:AtomicUsize=AtomicUsize::new(0);
    static TABLE:AtomicUsize=AtomicUsize::new(0);
    static DEPTH:AtomicUsize=AtomicUsize::new(0);
    pub fn begin(c:usize){CASE.store(c,Ordering::Relaxed);TABLE.store(0,Ordering::Relaxed);}
    pub fn reset_depth(){DEPTH.store(0,Ordering::Relaxed);}
    pub fn note_depth(d:usize){DEPTH.fetch_max(d,Ordering::Relaxed);}
    pub fn record(freq:&[u32;288],m:usize,len:&[u8;288],mx:u32,ck:usize,role:usize){
        let n=m.min(288);if role==0{TABLE.fetch_add(1,Ordering::Relaxed);}
        let pm=crate::official_pm::lengths(&freq[..n]);
        let live=(0..n).filter(|&i|freq[i]>0).count();
        let depth=if live==1{1}else{DEPTH.load(Ordering::Relaxed)};
        let dif=(0..n).filter(|&i|freq[i]>0&&len[i]!=pm[i]).count();
        let old_bits:u64=(0..n).map(|i|freq[i]as u64*len[i]as u64).sum();
        let pm_bits:u64=(0..n).map(|i|freq[i]as u64*pm[i]as u64).sum();
        let pmax=pm.iter().copied().max().unwrap_or(0).max(1)as u32;
        let ou=if mx<15{mx+1}else{15};let pu=if pmax<15{pmax+1}else{15};
        println!("HUFF_TABLE {{\"case\":{},\"table\":{},\"role\":{},\"cost_kind\":{},\"symbols\":{},\"live\":{},\"unclamped_max_depth\":{},\"length_limited\":{},\"active_length_differences\":{},\"old_weighted_bits\":{},\"pm_weighted_bits\":{},\"old_max_length\":{},\"pm_max_length\":{},\"old_unseen_bits\":{},\"pm_unseen_bits\":{},\"pure_unseen_difference\":{},\"freq\":{:?},\"old_lengths\":{:?},\"pm_lengths\":{:?}}}",CASE.load(Ordering::Relaxed),TABLE.load(Ordering::Relaxed),role,ck,n,live,depth,depth>15,dif,old_bits,pm_bits,mx,pmax,ou,pu,dif==0&&ou!=pu,&freq[..n],&len[..n],pm);
    }
}
type Parser=fn(&[u8],&mut[u32])->usize;
fn tokens(s:&[u8],f:Parser)->Vec<u32>{let mut o=vec![0;s.len()+16];let n=f(s,&mut o);assert!(n<=s.len());o.truncate(n);o}
fn decode(s:&[u8],t:&[u32])->bool{let mut o=Vec::new();for &x in t{if x<256{o.push(x as u8)}else{if !(16777216..25165824).contains(&x){return false}let v=x-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>o.len()||l>258||o.len()+l>s.len(){return false}for _ in 0..l{let b=o[o.len()-d];o.push(b)}}}o==s}
fn main(){let dir=std::env::args().nth(1).unwrap();let mut paths:Vec<_>=std::fs::read_dir(dir).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();paths.sort();assert_eq!(paths.len(),28);for(i,p)in paths.iter().enumerate(){let s=std::fs::read(p).unwrap();let base=tokens(&s,frozen::parse);assert!(decode(&s,&base));hdiag::begin(i);let measured=tokens(&s,observed::parse);let eq=base==measured;let dec=decode(&s,&measured);println!("HUFF_FILE {{\"case\":{},\"bytes\":{},\"tokens\":{},\"tokens_equal\":{},\"decode\":{}}}",i,s.len(),measured.len(),eq,dec);assert!(eq&&dec);}}
'''


def sha(b):return hashlib.sha256(b).hexdigest()


def function(text,name):
    a=text.index('fn '+name+'(');b=text.index('{',a);level=1;i=b+1
    while level:
        level+=(text[i]=='{')-(text[i]=='}');i+=1
    return text[a:i]


def observe(raw):
    original=raw.decode();text=original
    edits=[('let mxl = d_huff(lf, 286, &mut ll);','let mxl = r11_huff_capture(lf, 286, &mut ll, ck, 0);'),('let mxd = d_huff(df, 30, &mut dl);','let mxd = r11_huff_capture(df, 30, &mut dl, ck, 1);'),('        let l = d_clamp_len(depth[k % 576]);','        crate::hdiag::note_depth(depth[k % 576] as usize);\n        let l = d_clamp_len(depth[k % 576]);')]
    for old,new in edits:assert text.count(old)==1; text=text.replace(old,new,1)
    back=text
    for old,new in reversed(edits):back=back.replace(new,old,1)
    assert back==original
    return (text+CAPTURE).encode()


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--corpus',type=Path)
    ap.add_argument('--output',type=Path)
    ap.add_argument('--official-source',type=Path)
    ap.add_argument('--corpus-manifest',type=Path,default=MANIFEST)
    ap.add_argument('--toolchain',default='nightly-2026-08-18')
    ap.add_argument('--self-check',action='store_true');a=ap.parse_args()
    raw=BASE.read_bytes();assert sha(raw)==BASE_SHA
    official=a.official_source or (Path(os.environ['DEFLATE_ROOT'])/'validator/measure/src/deflate.rs' if os.environ.get('DEFLATE_ROOT') else ROOT/'sources/conjectures-optimisation-deflate/validator/measure/src/deflate.rs')
    official_raw=official.read_bytes();pm=function(official_raw.decode(),'package_merge')
    module=(pm+'\npub fn lengths(f:&[u32])->Vec<u8>{package_merge(f,15)}\n').encode()
    observed=observe(raw)
    expected={r['file']:(r['raw_bytes'],r['sha256'])for r in map(json.loads,a.corpus_manifest.read_text().splitlines())if r['kind']=='file'}
    assert len(expected)==28 and sum(v[0]for v in expected.values())==15930000
    if a.self_check:
        print(json.dumps({'status':'SOURCE_ONLY_SELF_CHECK','frozen_sha256':sha(raw),'observed_sha256':sha(observed),'official_source_sha256':sha(official_raw),'package_merge_function_sha256':sha(pm.encode()),'public_manifest_sha256':sha(a.corpus_manifest.read_bytes()),'expected_inputs':len(expected)}));return
    assert os.environ.get('GITHUB_ACTIONS')=='true' and os.environ.get('RUNNER_OS')=='Linux'
    assert os.environ.get('GITHUB_REPOSITORY')=='HuanHuanHuanFFF/Miner'
    temp=Path(os.environ['RUNNER_TEMP']);out=a.output or temp/'round11-huffman-receipts';out.mkdir(parents=True,exist_ok=True)
    corpus=a.corpus or Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
    files=sorted(p for p in corpus.iterdir()if p.is_file());actual={p.name:(p.stat().st_size,sha(p.read_bytes()))for p in files};assert actual==expected,'public input names/size/SHA differ from probe-a'
    build=temp/'round11-huffman-build';build.mkdir(parents=True,exist_ok=True)
    for n,b in [('frozen.rs',raw),('observed.rs',observed),('official_pm.rs',module),('main.rs',HARNESS.encode())]:(build/n).write_bytes(b)
    result={'status':'PENDING','run_id':os.environ.get('GITHUB_RUN_ID'),'git_sha':os.environ.get('GITHUB_SHA'),'batch':os.environ.get('ROUND4_SPEC','huffman-1'),'frozen_sha256':sha(raw),'observed_sha256':sha(observed),'harness_sha256':sha(HARNESS.encode()),'diagnostic_script_sha256':sha(Path(__file__).read_bytes()),'official_source_path':str(official),'official_source_sha256':sha(official_raw),'package_merge_function_sha256':sha(pm.encode()),'official_wrapper_sha256':sha(module),'corpus_manifest_path':str(a.corpus_manifest),'corpus_manifest_sha256':sha(a.corpus_manifest.read_bytes()),'corpus':[{'file':p.name,'bytes':actual[p.name][0],'sha256':actual[p.name][1]}for p in files],'tables':[],'files':[],'limits':['Read-only observed parser returns original Huffman lengths/costs; PM is diagnostic only.','Exact copied official PM function, fixed max_bits15; no new parser or Lean evidence.','Unclamped depths and weighted symbol bits are model observations, not complete DEFLATE bytes or performance.'],'compile_timeout_s':180,'runtime_timeout_s':300}
    def save(): (out/'huffman.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    save()
    try:
        cp=subprocess.run(['rustc','+'+a.toolchain,'--edition=2021','-O','-C','overflow-checks=yes',str(build/'main.rs'),'-o',str(build/'huffman')],capture_output=True,text=True,timeout=180)
        (out/'compile.log').write_text(cp.stdout+cp.stderr,encoding='utf-8');result['compile_exit']=cp.returncode
        if cp.returncode:raise RuntimeError('diagnostic compile failed')
        rp=subprocess.run([str(build/'huffman'),str(corpus)],capture_output=True,text=True,timeout=300)
        (out/'runtime.log').write_text(rp.stdout+rp.stderr,encoding='utf-8');result['runtime_exit']=rp.returncode
        for line in rp.stdout.splitlines():
            if line.startswith('HUFF_TABLE '):result['tables'].append(json.loads(line[11:]))
            elif line.startswith('HUFF_FILE '):result['files'].append(json.loads(line[10:]))
        for row in result['tables']+result['files']:
            item=result['corpus'][row['case']];row.update(file=item['file'],input_sha256=item['sha256'])
        tables=result['tables'];assert tables, 'No actual D cost tables were observed'
        different=[r for r in tables if r['active_length_differences'] or r['old_unseen_bits']!=r['pm_unseen_bits']]
        result['summary']={'cost_blocks':sum(r['role']==0 for r in tables),'huffman_tables':len(tables),'different_huffman_tables':len(different),'different_cost_blocks':len({(r['case'],r['table'])for r in different}),'different_files':sorted({r['file']for r in different}),'active_symbols_differ':sum(r['active_length_differences']for r in tables),'length_limited_tables':sum(r['length_limited']for r in tables),'pure_unseen_difference_tables':sum(r['pure_unseen_difference']for r in tables),'weighted_bit_delta_pm_minus_old':sum(r['pm_weighted_bits']-r['old_weighted_bits']for r in tables),'public_inputs_completed':len(result['files'])}
        assert rp.returncode==0 and len(result['files'])==28 and len({r['case']for r in result['files']})==28
        assert all(r['tokens_equal']and r['decode']for r in result['files'])
        result['status']='VERIFIED_FINITE_READ_ONLY_HUFFMAN_DIAGNOSTIC';save()
    except subprocess.TimeoutExpired as exc:
        result['status']='DIAGNOSTIC_TIMEOUT';result['error']=str(exc)
        for n,data in [('stdout',exc.stdout),('stderr',exc.stderr)]:
            if data is not None:(out/('timeout-'+n+'.log')).write_bytes(data if isinstance(data,bytes)else data.encode())
        save();raise
    except Exception as exc:
        result['status']='DIAGNOSTIC_FAILED';result['error']=repr(exc);save();raise
    print(json.dumps({'status':result['status'],'summary':result['summary']},ensure_ascii=False),flush=True)


if __name__=='__main__':main()
