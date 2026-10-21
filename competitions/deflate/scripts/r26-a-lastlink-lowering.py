"""A17: official-shim last-link lowering plus unchanged public658 trajectory coverage."""
from pathlib import Path
import hashlib
import importlib
import json
import os
import re
import subprocess
import tomllib

ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'references/round26-public-658/parse.rs'
RUST='1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad'
RELEASE={'opt-level':3,'lto':'fat','codegen-units':1,'debug-assertions':False,'overflow-checks':True,'panic':'unwind'}
FIELDS=['walk_calls','walk_iterations','valid_candidates','common_calls','better_matches','length_stop_events','next_link_loads','final_next_link_loads','depth1_calls','depth6_calls','depth12_calls','other_depth_calls']
HELP=importlib.import_module('r26-a-rep-shadow')
UTIL=importlib.import_module('research-round25-len3-price')

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,obj):p.write_bytes((json.dumps(obj,indent=2)+'\n').encode())

def alternative(raw):
 assert sha(raw)==RUST
 def edit(b):
  old='''            let nx = prev[c % W] as usize;
            if nx < c {
                c = nx;
                k -= 1;
            } else {
                k = 0;
            }'''
  new='''            if k <= 1 { k = 0; }
            else {
                let nx = prev[c % W] as usize;
                if nx < c { c = nx; k -= 1; } else { k = 0; }
            }'''
  return HELP.once(b,old,new)
 return HELP.edit_fn(raw.decode(),'u118_walk<',edit).encode()

EXTRA=r'''
use std::sync::atomic::{AtomicU64,Ordering};
static A17_COUNTS:[AtomicU64;12]=[const{AtomicU64::new(0)};12];
pub fn a17_take()->[u64;12]{std::array::from_fn(|i|A17_COUNTS[i].swap(0,Ordering::Relaxed))}
'''
def instrument(raw):
 assert sha(raw)==RUST
 def edit(b):
  b=HELP.once(b,'    let n = s.len();','    let mut cnt=[0u64;12];cnt[0]=1;cnt[if depth==1{8}else if depth==6{9}else if depth==12{10}else{11}]=1;\n    let n = s.len();')
  b=HELP.once(b,'    while k > 0 {','    while k > 0 {\n        cnt[1]+=1;')
  b=HELP.once(b,'        if d.wrapping_sub(1) < 32768 && c + best < n {','        if d.wrapping_sub(1) < 32768 && c + best < n {\n            cnt[2]+=1;')
  b=HELP.once(b,'                let l = u118_common(s, c, p, cap);','                cnt[3]+=1;\n                let l = u118_common(s, c, p, cap);')
  b=HELP.once(b,'                if take == 1 {','                if take == 1 {\n                    cnt[4]+=1;')
  b=HELP.once(b,'                    if l >= stop || p + l >= n {','                    if l >= stop || p + l >= n {\n                        cnt[5]+=1;')
  b=HELP.once(b,'            let nx = prev[c % W] as usize;','            cnt[6]+=1;cnt[7]+=(k<=1)as u64;\n            let nx = prev[c % W] as usize;')
  return HELP.once(b,'    (best, bd)','    for i in 0..12{A17_COUNTS[i].fetch_add(cnt[i],Ordering::Relaxed);}\n    (best, bd)')
 return (HELP.edit_fn(raw.decode(),'u118_walk<',edit)+EXTRA).encode()

def harness(observed):
 s=HELP.HARNESS.replace('A15_CORPUS','A17_CORPUS').replace('observed::a15_take','observed::a17_take')
 for key,path in [('FROZEN',BASE),('OBSERVED',observed)]:s=HELP.once(s,'#[path='+key+']','#[path='+json.dumps(str(path))+']')
 return s

def preflight(spec):
 assert spec['r26_mode']=='native'and spec['native_encoder']is True and spec['r26_a_lastlink_lowering']is True
 assert all(e['control']for e in spec['entries'])and spec['r26_expected_candidates']==0
 e=next(e for e in spec['entries']if e['name']=='public658');raw=(ROOT/e['path']/'parse.rs').read_bytes();assert sha(raw)==e['hashes']['parse.rs']==RUST
 assert 'public658'in spec['native_encoder_references']and'public641'in spec['native_encoder_references']
 template=ROOT/'evidence/round26/route-b/b25-official-template';assert tomllib.loads((template/'Cargo.toml').read_text())['profile']['release']==RELEASE
 return {'status':'VERIFIED_ORIGINAL658_OFFICIAL_FLAGS_TEMPLATE_AND_OBSERVER_NOT_NATIVE','rust_sha256':RUST,'scratch_variant_sha256':sha(alternative(raw)),
  'observer_sha256':sha(instrument(raw)),'harness_sha256':sha(harness(Path('observed.rs')).encode()),'release':RELEASE,
  'template_canonical_sha256':{f:sha((template/f).read_bytes().replace(b'\r\n',b'\n'))for f in ['Cargo.toml','lib.rs']}}

def body_ir(text,name):
 starts=list(re.finditer(r'(?m)^define[^\n]*'+re.escape(name)+r'[^\n]*\{\n',text))
 return [text[m.start():text.index('\n}',m.end())+2]for m in starts]
def body_asm(text,name):
 starts=list(re.finditer(r'(?m)^\s*\.section\s+\.text\.[^\n]*'+re.escape(name)+r'[^\n]*\n',text));out=[]
 for m in starts:
  end=text.find('\n\t.section',m.end());out.append(text[m.start():end if end>=0 else len(text)])
 return out

def run():
 assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
 from round4 import validate
 spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec);raw=BASE.read_bytes()
 build=Path(os.environ['RUNNER_TEMP'])/'r26-a-lastlink-build';build.mkdir();spool=build/'spool';spool.mkdir()
 out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-lastlink';out.mkdir(parents=True)
 original_template=Path(os.environ['DEFLATE_ROOT'])/'validator/measure/candidate';cargo=(original_template/'Cargo.toml').read_bytes();shim=(original_template/'lib.rs').read_bytes()
 assert tomllib.loads(cargo.decode())['profile']['release']==RELEASE
 assert {f:sha(v.replace(b'\r\n',b'\n'))for f,v in [('Cargo.toml',cargo),('lib.rs',shim)]}==checked['template_canonical_sha256']
 (out/'official-Cargo.toml').write_bytes(cargo);(out/'official-shim.rs').write_bytes(shim)
 r={'status':'STARTED_OFFICIAL_FLAGS_LASTLINK_LOWERING_AND_COVERAGE','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],
  'preflight':checked,'variants':{},'scope':'Original658 and one scratch final-link control under official release/shim; no production candidate, timing or proof. Untimed original658 observer bound to originalencoder.'}
 report=out/'receipt.json';dump(report,r)
 try:
  for label,src in [('original',raw),('lastlink_control',alternative(raw))]:
   folder=build/label;folder.mkdir();(folder/'parse.rs').write_bytes(src);(folder/'lib.rs').write_bytes(shim);asmfolder=folder/'lowering';asmfolder.mkdir()
   cmd=['rustc','+nightly-2026-08-18','--edition=2021','--crate-type=cdylib','--crate-name=candidate','-O','-C','lto=fat','-C','codegen-units=1','-C','debug-assertions=no','-C','overflow-checks=yes','-C','panic=unwind','--emit=asm,llvm-ir','--out-dir',str(asmfolder),str(folder/'lib.rs')]
   UTIL.captured(cmd,out/(label+'-compile.log'),300);ir=(asmfolder/'candidate.ll').read_text();asm=(asmfolder/'candidate.s').read_text();bodies={}
   for fn in ['p125_row2','p125_row9','u118_walk','bulk_parse']:
    i='\n\n'.join(body_ir(ir,fn));a='\n\n'.join(body_asm(asm,fn));(out/(label+'-'+fn+'.ll')).write_text(i);(out/(label+'-'+fn+'.s')).write_text(a)
    bodies[fn]={'IR_bodies':len(body_ir(ir,fn)),'ASM_bodies':len(body_asm(asm,fn)),'IR_sha256':sha(i.encode()),'ASM_sha256':sha(a.encode()),'IR_load_i32_count':len(re.findall(r'\bload i32\b',i))}
   assert bodies['p125_row9']['IR_bodies'] and bodies['p125_row9']['ASM_bodies']
   (out/(label+'-parse.rs')).write_bytes(src);r['variants'][label]={'rust_sha256':sha(src),'compiler_command':cmd,'full_IR_sha256':sha((asmfolder/'candidate.ll').read_bytes()),'full_ASM_sha256':sha((asmfolder/'candidate.s').read_bytes()),'functions':bodies};dump(report,r)
  observed=build/'observed.rs';obs=instrument(raw);observed.write_bytes(obs);(out/'observer.rs').write_bytes(obs)
  h=harness(observed);driver=build/'observer-driver.rs';driver.write_text(h);(out/'harness.rs').write_text(h);binary=build/'observe'
  UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'observer-compile.log',300)
  corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';process=UTIL.captured([str(binary),str(corpus),str(spool)],out/'observer-run.log',300)
  encpath=out.parent/'r13-encoder/encoder.json';native=json.loads(encpath.read_bytes());expected={e['file']:e for e in native['rows']if e['candidate']=='public658'};rows=[]
  for line in process.stdout.splitlines():
   if not line.startswith('A17_CORPUS '):continue
   _,file,n,nt,*vs=line.split();assert len(vs)==len(FIELDS);c=dict(zip(FIELDS,map(int,vs)));e=expected[file];data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes()
   assert len(data)==int(n)==e['raw_bytes']and len(ts)==4*int(nt)and int(nt)==e['tokens']and sha(data)==e['input_sha256']and sha(ts)==e['tokens_sha256']
   assert c['walk_calls']==c['depth1_calls']+c['depth6_calls']+c['depth12_calls']+c['other_depth_calls']and c['final_next_link_loads']<=c['next_link_loads']
   rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'counts':c})
  assert len(rows)==28 and len({e['file']for e in rows})==28
  r.update(status='VERIFIED_OFFICIAL_FLAGS_LASTLINK_LOWERING_AND_ORIGINAL_COVERAGE',rows=rows,totals={f:sum(e['counts'][f]for e in rows)for f in FIELDS},encoder_sha256=sha(encpath.read_bytes()),compiler_version=subprocess.run(['rustc','+nightly-2026-08-18','-vV'],capture_output=True,text=True,check=True).stdout,
   limits=['Official shim/release flags copied; no original repository or flags modified. Exact Cargo library identity not claimed.','Load instruction counts require exact loop inspection; they do not prove deadload elimination or speed.','Scratch variant not executed as candidate; no fullgate or pairedtime.','Observer counts are original source execution semantics; compiled original may already remove some loads.'])
 except Exception as exc:r.update(status='FAILED_OR_INCOMPLETE_LASTLINK_DIAGNOSTIC',error_type=type(exc).__name__,error=str(exc));dump(report,r);raise
 dump(report,r);print(json.dumps({'status':r['status'],'totals':r['totals']},indent=2))

if __name__=='__main__':run()
