"""C2 untimed original-trajectory oracle; C1 same-distance is counted, not implemented."""
from pathlib import Path
import hashlib
import importlib
import json
import os

ROOT = Path(__file__).resolve().parents[1]
BUILD = importlib.import_module('r26-c-build-fold-tail')
HELP = importlib.import_module('r26-a-rep-shadow')
UTIL = importlib.import_module('research-round25-len3-price')
BASE = BUILD.BASE/'parse.rs'
FIELDS = ['original_same_calls', 'original_span_bytes', 'tail_reject_calls',
          'tail_reject_span_bytes', 'tail_reject_original_word_pairs',
          'tail_reject_original_byte_pairs', 'tail_pass_calls', 'original_same_success',
          'original_same_failure', 'same_distance_calls', 'same_distance_span_bytes',
          'original_word_pairs', 'original_byte_pairs']

def sha(b): return hashlib.sha256(b).hexdigest()
def dump(p, x): p.write_bytes((json.dumps(x, indent=2)+'\n').encode())

EXTRA = r'''
use std::sync::atomic::{AtomicU64,Ordering};
static C2_COUNTS:[AtomicU64;13]=[const {AtomicU64::new(0)};13];
pub fn c2_take()->[u64;13]{std::array::from_fn(|i|C2_COUNTS[i].swap(0,Ordering::Relaxed))}
// Shadow the exact source-level original same loads, not cycles or assembly operations.
fn c2_same_model(s:&[u8],a:usize,b:usize,len:usize)->(usize,u64,u64){
 let n=s.len();let mut k=0usize;let mut ok=1usize;let mut words=0u64;let mut bytes=0u64;
 while ok==1&&k+8<=len{words+=1;if u118_be8(s,a+k)==u118_be8(s,b+k){k+=8;}else{ok=0;}}
 if ok==1&&k<len{
  if a+k+8<=n&&b+k+8<=n{words+=1;let x=u118_be8(s,a+k)^u118_be8(s,b+k);if(x>>(64-8*(len-k)as u32))!=0{ok=0;}}
  else{while ok==1&&k<len{bytes+=1;if s[a+k]==s[b+k]{k+=1;}else{ok=0;}}}
 }
 (ok,words,bytes)
}
fn c2_observe_same(s:&[u8],p:usize,w:usize,d:usize,t:u32)->usize{
 let original=u118_same(s,p-w-d,p-w,w);
 let (model,words,bytes)=c2_same_model(s,p-w-d,p-w,w);assert_eq!(original,model);
 let pass=s[p-1]==s[p-1-d];assert!(original==0||pass,"Necessary endpoint condition failed");
 let same_distance=((t-16777216)/256+1)as usize==d;
 if same_distance{assert_eq!(original,1,"Already emitted same-distance token must match");}
 let mut c=[0u64;13];c[0]=1;c[1]=w as u64;c[7]=(original==1)as u64;c[8]=(original==0)as u64;
 c[9]=same_distance as u64;c[10]=if same_distance{w as u64}else{0};c[11]=words;c[12]=bytes;
 if pass{c[6]=1;}else{c[2]=1;c[3]=w as u64;c[4]=words;c[5]=bytes;}
 for i in 0..13{C2_COUNTS[i].fetch_add(c[i],Ordering::Relaxed);}original
}
'''

def instrument(raw):
    assert sha(raw) == BUILD.RUST
    old = 'u118_same(input, p - w - d, p - w, w) == 1'
    text = raw.decode(); assert text.count(old) == 1
    return (text.replace(old, 'c2_observe_same(input, p, w, d, t) == 1', 1)+EXTRA).encode()

def harness(observed):
    s = HELP.HARNESS.replace('A15_CORPUS', 'C2_CORPUS').replace('observed::a15_take', 'observed::c2_take')
    s = HELP.once(s, '#[path=FROZEN]', '#[path='+json.dumps(str(BASE))+']')
    s = HELP.once(s, '#[path=OBSERVED]', '#[path='+json.dumps(str(observed))+']')
    return s

def preflight(spec):
    assert spec['r26_mode'] == 'native' and spec['native_encoder'] is True
    assert spec['r26_c_fold_tail_counts'] is True and spec['r26_finite_equivalence'] is True
    by = {e['name']: e for e in spec['entries']}
    p = by['public658']; e = by[BUILD.NAME]
    assert p['hashes']['parse.rs'] == BUILD.RUST == sha(BASE.read_bytes())
    assert e['hashes']['parse.rs'] == sha(BUILD.source()) == sha((ROOT/e['path']/'parse.rs').read_bytes())
    assert e['expected_equivalent_to'] == 'public658'
    return {'status': 'VERIFIED_SOURCE_AND_OBSERVER_HASH_BINDING_NOT_COMPILED',
            'parent_rust_sha256': BUILD.RUST, 'candidate_hashes': e['hashes'],
            'observer_sha256': sha(instrument(BASE.read_bytes())),
            'harness_template_sha256': sha(harness(Path('observed.rs')).encode())}

def run():
    assert os.environ.get('GITHUB_ACTIONS') == 'true' and os.environ.get('RUNNER_OS') == 'Linux'
    from round4 import validate
    spec = validate(os.environ['ROUND4_SPEC']); checked = preflight(spec)
    build = Path(os.environ['RUNNER_TEMP'])/'r26-c-fold-tail-build'; build.mkdir()
    spool = build/'spool'; spool.mkdir()
    out = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r26-c-fold-tail'; out.mkdir(parents=True)
    observed = build/'observed.rs'; raw = instrument(BASE.read_bytes()); observed.write_bytes(raw)
    (out/'observer.rs').write_bytes(raw)
    h = harness(observed); driver = build/'main.rs'; driver.write_bytes(h.encode()); (out/'harness.rs').write_bytes(h.encode())
    r = {'status': 'STARTED_ORIGINAL_TRAJECTORY_FOLD_TAIL_ORACLE', 'run_id': os.environ['GITHUB_RUN_ID'],
         'git_sha': os.environ['GITHUB_SHA'], 'batch': os.environ['ROUND4_SPEC'], 'preflight': checked,
         'observer_sha256': sha(raw), 'harness_sha256': sha(h.encode()),
         'scope': 'Original658 trajectory; no instrumentation in candidate timing. Source-level original word/byte pairs, not machine instructions or cycles. C1 only observed. Counts do not establish speed or gate.'}
    report = out/'receipt.json'; dump(report, r)
    try:
        binary = build/'check'
        UTIL.captured(['rustc','+nightly-2026-08-18','--edition=2021','-O','-C','overflow-checks=yes',str(driver),'-o',str(binary)],out/'compile.log',240)
        corpus = Path(os.environ['DEFLATE_ROOT'])/'data/benchmark/corpus-stage1'
        process = UTIL.captured([str(binary),str(corpus),str(spool)],out/'run.log',240)
        native_path = Path(os.environ['RUNNER_TEMP'])/'round4-receipts/r13-encoder/encoder.json'
        native = json.loads(native_path.read_bytes()); assert native['status'] == 'VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
        expected = {e['file']: e for e in native['rows'] if e['candidate'] == 'public658'}
        candidate = {e['file']: e for e in native['rows'] if e['candidate'] == BUILD.NAME}
        assert len(expected) == len(candidate) == 28
        rows = []
        for line in process.stdout.splitlines():
            if not line.startswith('C2_CORPUS '): continue
            _, file, n, nt, *vs = line.split(); assert len(vs) == len(FIELDS)
            c = dict(zip(FIELDS, map(int,vs))); e = expected[file]; new = candidate[file]
            data = (corpus/file).read_bytes(); ts = (spool/(file+'.tokens')).read_bytes()
            assert len(data) == int(n) == e['raw_bytes'] and len(ts) == 4*int(nt) and int(nt) == e['tokens']
            assert sha(data) == e['input_sha256'] and sha(ts) == e['tokens_sha256']
            assert all(new[k] == e[k] for k in ('tokens_sha256','output_sha256','tokens','output_bytes'))
            assert c['original_same_calls'] == c['tail_pass_calls'] + c['tail_reject_calls']
            assert c['original_same_calls'] == c['original_same_success'] + c['original_same_failure']
            rows.append({'file':file,'input_sha256':sha(data),'tokens_sha256':sha(ts),'counts':c})
        assert len(rows) == 28 and len({e['file'] for e in rows}) == 28
        r.update(status='VERIFIED_28_ORIGINAL_TRAJECTORY_AND_CANDIDATE_TOKENS_ENCODER_DECODE',
                 encoder_receipt_sha256=sha(native_path.read_bytes()), rows=rows,
                 totals={f:sum(e['counts'][f] for e in rows) for f in FIELDS},
                 performance='NOT_MEASURED',full_gate='NOT_RUN')
    except Exception as exc:
        r.update(status='FAILED_OR_INCOMPLETE_FOLD_TAIL_ORACLE',error_type=type(exc).__name__,error=str(exc)); dump(report,r); raise
    dump(report,r); print(json.dumps({'status':r['status'],'totals':r['totals']},indent=2))

if __name__ == '__main__': run()
