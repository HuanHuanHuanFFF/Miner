"""A19: only U118 word-loop offset sums, official shim/flags lowering and finite equality."""
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
HELP=importlib.import_module('r26-a-rep-shadow')
UTIL=importlib.import_module('research-round25-len3-price')
LOW=importlib.import_module('r26-a-lastlink-lowering')

def sha(raw):return hashlib.sha256(raw).hexdigest()
def dump(p,obj):p.write_bytes((json.dumps(obj,indent=2)+'\n').encode())
def variant(raw):
 assert sha(raw)==RUST
 def edit(b):
  a='u118_be8(s, a + k) ^ u118_be8(s, b + k)';z='u118_be8(s, a.wrapping_add(k)) ^ u118_be8(s, b.wrapping_add(k))'
  out=HELP.once(b,a,z);assert out.replace(z,a)==b;assert 'if s[a + k] == s[b + k]'in out;return out
 return HELP.edit_fn(raw.decode(),'u118_common(',edit).encode()

def arithmetic_model():
 cases=0
 for bits in [32,64]:
  mx=(1<<bits)-1
  for n in [0,7,8,16,258,65536,mx-258,mx-1,mx]:
   for cap in [0,1,7,8,15,16,257,258]:
    if cap>n:continue
    for b in sorted({0,n-cap,(n-cap)//2}):
     for a in sorted({0,b,b//2}):
      for k in range(0,cap+1,8):
       if k+8>cap:continue
       assert a+k+8<=b+cap<=n<=mx
       assert (a+k)&mx==a+k and (b+k)&mx==b+k;cases+=1
 return cases

HARNESS=r'''
#![allow(dead_code)]
#[path=PARENT]mod parent;
#[path=VARIANT]mod changed;
fn tokens(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut v=vec![0;s.len()];let n=f(s,&mut v);assert!(n<=s.len());v.truncate(n);v}
fn decode(s:&[u8],ts:&[u32])->bool{let mut out=Vec::with_capacity(s.len());for&t in ts{if t<256{out.push(t as u8)}else{if !(16777216..25165824).contains(&t){return false}let v=t-16777216;let d=(v/256+1)as usize;let l=(v%256+3)as usize;if d>out.len()||out.len()+l>s.len(){return false}for _ in 0..l{let b=out[out.len()-d];out.push(b)}}}out==s}
fn main(){let mut cases=0;for n in [0,1,7,8,9,16,17,257,258,259,512]{for period in [1,3,7,17]{let s:Vec<u8>=(0..n).map(|i|(i%period)as u8).collect();for b in [0,n/2,n]{for a in [0,b/2,b]{for cap in [0,1,7,8,9,15,16,31,257,258]{if b+cap<=n{let x=parent::u118_common(&s,a,b,cap);let y=changed::u118_common(&s,a,b,cap);assert_eq!(x,y);cases+=1;}}}}}}println!("A19_HELPERS {}",cases);
 let args:Vec<_>=std::env::args().collect();let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|p|p.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for p in files{let s=std::fs::read(&p).unwrap();let a=tokens(&s,parent::parse);let b=tokens(&s,changed::parse);assert_eq!(a,b,"{}",p.display());assert!(decode(&s,&b));let name=p.file_name().unwrap().to_str().unwrap();let raw:Vec<u8>=b.iter().flat_map(|t|t.to_le_bytes()).collect();std::fs::write(std::path::Path::new(&args[2]).join(format!("{}.tokens",name)),raw).unwrap();println!("A19_CORPUS {} {} {}",name,s.len(),b.len());}}
'''
def harness(changed):
 s=HARNESS
 for key,p in [('PARENT',BASE),('VARIANT',changed)]:s=HELP.once(s,'#[path='+key+']','#[path='+json.dumps(str(p))+']')
 return s

def preflight(spec):
 assert spec['r26_mode']=='native'and spec['native_encoder']is False and spec['r26_a_common_lowering']is True
 assert all(e['control']for e in spec['entries'])and spec['r26_expected_candidates']==0
 raw=BASE.read_bytes();e=next(e for e in spec['entries']if e['name']=='public658');assert sha(raw)==e['hashes']['parse.rs']==RUST
 t=ROOT/'evidence/round26/route-b/b25-official-template';assert tomllib.loads((t/'Cargo.toml').read_text())['profile']['release']==LOW.RELEASE
 baseline=ROOT/spec['r26_a_common_baseline'];j=json.loads(baseline.read_bytes());assert j['source_hashes']['public658']['parse.rs']==RUST and j['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
 return {'status':'VERIFIED_TWO_SAFE_WORD_SUM_PATCH_AND_OFFICIAL_TEMPLATE_NOT_NATIVE','source_sha256':RUST,'variant_sha256':sha(variant(raw)),
  'arithmetic_model_cases':arithmetic_model(),'baseline_sha256':sha(baseline.read_bytes()),'harness_sha256':sha(harness(Path('changed.rs')).encode()),
  'template_canonical_sha256':{f:sha((t/f).read_bytes().replace(b'\r\n',b'\n'))for f in ['Cargo.toml','lib.rs']},
  'derivation':'u118_common hasone caller u118_walk; walk invariant c<=p+2 plus accepted wrapped distance gives a<=b, and find fixes b+cap<=n. Wordloop k+8<=cap yields a+k+8<=b+cap<=n<=usize::MAX, so a+k and b+k equal wrapping sums. Byte-tail, be8, masks, filtering, search and routes unchanged.'}

def run():
 assert os.environ.get('GITHUB_ACTIONS')=='true'and os.environ.get('RUNNER_OS')=='Linux'
 from round4 import validate
 spec=validate(os.environ['ROUND4_SPEC']);checked=preflight(spec);raw=BASE.read_bytes()
 build=Path(os.environ['RUNNER_TEMP'])/'r26-a-common-lowering-build';build.mkdir();spool=build/'spool';spool.mkdir()
 out=Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-a-common-lowering';out.mkdir(parents=True)
 t=Path(os.environ['DEFLATE_ROOT'])/'validator/measure/candidate';cargo=(t/'Cargo.toml').read_bytes();shim=(t/'lib.rs').read_bytes()
 assert tomllib.loads(cargo.decode())['profile']['release']==LOW.RELEASE
 assert {f:sha(v.replace(b'\r\n',b'\n'))for f,v in [('Cargo.toml',cargo),('lib.rs',shim)]}==checked['template_canonical_sha256']
 (out/'official-Cargo.toml').write_bytes(cargo);(out/'official-shim.rs').write_bytes(shim)
 r={'status':'STARTED_SAFE_WORD_SUM_LOWERING','run_id':os.environ['GITHUB_RUN_ID'],'git_sha':os.environ['GITHUB_SHA'],'batch':os.environ['ROUND4_SPEC'],'preflight':checked,'variants':{}};report=out/'receipt.json';dump(report,r);changed=None
 try:
  for label,src in [('original_checked',raw),('safe_wrapping_words',variant(raw))]:
   folder=build/label;folder.mkdir();(folder/'parse.rs').write_bytes(src);(folder/'lib.rs').write_bytes(shim);asmfolder=folder/'lowering';asmfolder.mkdir()
   cmd=['rustc','+nightly-2026-08-18','--edition=2021','--crate-type=cdylib','--crate-name=candidate','-O','-C','lto=fat','-C','codegen-units=1','-C','debug-assertions=no','-C','overflow-checks=yes','-C','panic=unwind','--emit=asm,llvm-ir','--out-dir',str(asmfolder),str(folder/'lib.rs')]
   UTIL.captured(cmd,out/(label+'-compile.log'),300);ir=(asmfolder/'candidate.ll').read_text();asm=(asmfolder/'candidate.s').read_text();bodies={}
   for name in ['p125_row2','p125_row9','u118_common']:
    i='\n\n'.join(LOW.body_ir(ir,name));a='\n\n'.join(LOW.body_asm(asm,name));(out/(label+'-'+name+'.ll')).write_text(i);(out/(label+'-'+name+'.s')).write_text(a)
    bodies[name]={'IR_bodies':len(LOW.body_ir(ir,name)),'ASM_bodies':len(LOW.body_asm(asm,name)),'IR_sha256':sha(i.encode()),'ASM_sha256':sha(a.encode()),'IR_add_overflow_panic_calls':len(re.findall('call.*panic_const_add_overflow',i)),'IR_u64_loads':len(re.findall(r'\bload i64\b',i))}
   assert bodies['p125_row9']['IR_bodies']and bodies['p125_row9']['ASM_bodies']
   (out/(label+'-parse.rs')).write_bytes(src);r['variants'][label]={'rust_sha256':sha(src),'compiler_command':cmd,'functions':bodies,'full_IR_sha256':sha((asmfolder/'candidate.ll').read_bytes()),'full_ASM_sha256':sha((asmfolder/'candidate.s').read_bytes())};dump(report,r)
   if label=='safe_wrapping_words':changed=folder/'parse.rs'
  assert changed is not None;h=harness(changed);driver=build/'check.rs';driver.write_text(h);(out/'harness.rs').write_text(h);binary=build/'check'
  UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'native-compile.log',300)
  corpus=Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1';proc=UTIL.captured([str(binary),str(corpus),str(spool)],out/'native-run.log',300)
  baseline=json.loads((ROOT/spec['r26_a_common_baseline']).read_bytes());expected={e['file']:e for e in baseline['rows']if e['candidate']=='public658'};rows=[];helpers=0
  for line in proc.stdout.splitlines():
   if line.startswith('A19_HELPERS '):helpers=int(line.split()[1])
   if not line.startswith('A19_CORPUS '):continue
   _,file,n,nt=line.split();e=expected[file];data=(corpus/file).read_bytes();ts=(spool/(file+'.tokens')).read_bytes()
   assert len(data)==int(n)==e['raw_bytes']and len(ts)==4*int(nt)and int(nt)==e['tokens']and sha(data)==e['input_sha256']and sha(ts)==e['tokens_sha256']
   rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts)})
  assert len(rows)==28 and len({e['file']for e in rows})==28 and helpers>1000
  r.update(status='VERIFIED_OFFICIAL_FLAGS_SAFE_WORD_SUM_LOWERING_AND_FINITE_EQUALITY',rows=rows,helper_cases=helpers,compiler_version=subprocess.run(['rustc','+nightly-2026-08-18','-vV'],capture_output=True,text=True,check=True).stdout,
   limits=['Original official release/shim settings copied, not altered. Exact Cargo binaryidentity notclaimed.','Instruction/branch counts need loopinspection; no speedclaim.','Onlytwo wordsum additions changed; no be8/tail/final-link/window-filter combination.','No production candidate, fullgate, original pairedtiming or formal result.'])
 except Exception as exc:r.update(status='FAILED_OR_INCOMPLETE_SAFE_WORD_SUM_DIAGNOSTIC',error_type=type(exc).__name__,error=str(exc));dump(report,r);raise
 dump(report,r);print(json.dumps({'status':r['status'],'helper_cases':helpers,'variants':r['variants']},indent=2))

if __name__=='__main__':run()
