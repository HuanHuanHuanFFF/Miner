"""Fixed Lean header + actual old generated C; no new compiler or timing."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json,re,time
OUT=Path(__file__).resolve().parent
ROOT=next(p for p in OUT.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic(); sha=lambda b:hashlib.sha256(b).hexdigest()
h=(OUT/'public-source/lean-293d5d0c.h').read_bytes(); hs=h.decode()
assert sha(h)=='982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
def cbody(text,name):
    m=list(re.finditer(r'^.*\b'+re.escape(name)+r'\([^\n]*\)\s*\{',text,re.M)); assert len(m)==1,(name,len(m))
    i=m[0].start();j=m[0].end();depth=1
    while depth:
        if text[j]=='{':depth+=1
        elif text[j]=='}':depth-=1
        j+=1
    return text[i:j],text[:i].count('\n')+1
header=[]
for name in ['lean_box_float32','lean_unbox_float32','lean_alloc_ctor','lean_ctor_get_float32','lean_ctor_set_float32']:
    body,line=cbody(hs,name);header.append({'name':name,'line':line,'body':body,'sha256':sha(body.encode())})
cpath='competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40136215532/download-b5ee18c29caa44b7ac3cfe73f422b8c7/diagnostics/f01-r14-dev-p2-n1-cache/candidate-generated-0.c'
cb=(ROOT/cpath).read_bytes(); assert sha(cb)=='6b2a3d7073ad77a4b2b3580e1c20853c80f8036011f14b2a79d99a00f59ff37b'
name='lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowStream_output_spec__0'
body,line=cbody(cb.decode(),name);assert body.count('lean_box_float32(')==1
(OUT/'Float32-map-prior-C.txt').write_text(body+'\n',encoding='utf-8')
pcpath='competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40045868764/download-da97e7bfcfbf48eb9307e69f0ab13faf/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-panel4-codegen-probe/capture-9e612642fbdc469b8c576f8f05da3612/file-0-Submission.c'
pcb=(ROOT/pcpath).read_bytes();assert sha(pcb)=='2c196b4f00a97930a41c33fd09d88caac9c159640b39ede9d8c7cf1e510a62dc'
pn='lp_competition_Submission_Panel4_packA___lam__0'
pb,pl=cbody(pcb.decode(),pn)
assert 'lean_alloc_ctor(0, 0, 16)' in pb and pb.count('lean_ctor_set_float32(')==4 and 'lean_box_float32(' not in pb
(OUT/'F4-pack-prior-C.txt').write_text(pb+'\n',encoding='utf-8')
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'REPRESENTATION_OPPORTUNITY_VERIFIED_OLD_PATTERNS_NEW_B2_NOT_BUILT',
 'lean_commit':'293d5d0c0c3f3dded4688b3ccd6a33939ac5102b','lean_header_sha256':sha(h),'header':header,
 'mapped_Float32_C':{'path':cpath,'file_sha256':sha(cb),'kernel_sha256':'83a981273988f07ce89d4a18c1dbef475adb6ed2fefce381138c5d165bf2a806','symbol':name,'line':line,'body_sha256':sha(body.encode()),'box_site_per_element_loop':1},
 'inline_F4_C':{'path':pcpath,'file_sha256':sha(pcb),'kernel_sha256':'9a40118eae28c92c1abeca7f6a141fb0fbfe963cbf40321681b8013782f9f7ac','symbol':pn,'line':pl,'body_sha256':sha(pb.encode()),'record_constructor_sites':1,'scalar_payload_bytes':16,'Float32_set_sites':4,'individual_float_box_sites':0},
 'B2_inference':'A two-Float32 record should use one8B scalar-payload object rather than two individual4B scalar-payload boxes; new exact generatedC remains UNKNOWN. Each inner preparedVector read could load one record pointer and two native fields.',
 'cost_limits':'For even p, B2 element-object source count halves; allocator request bytes need not halve and physical allocator buckets/RSS/time are unknown. Nested batch/group arrays, closures, packing order/index arithmetic, extra odd-tail decodes and destruction remain inside timed BMM.',
 'no_speed_claim':True,'elapsed_seconds':time.monotonic()-start}
assert receipt['elapsed_seconds']<5
(OUT/'b2-representation-evidence.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'status':receipt['status'],'header_bytes':len(h),'map_line':line,'F4_line':pl,'elapsed_seconds':receipt['elapsed_seconds']}))
