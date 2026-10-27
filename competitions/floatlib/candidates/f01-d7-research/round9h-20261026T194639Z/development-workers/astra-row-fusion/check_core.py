"""Small source-lineage/control audit; not a Lean or numerical verifier."""
from pathlib import Path
import hashlib
import json
import re
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[6]
PREFIX = 'competitions/floatlib/candidates/'
def digest(data):
    return hashlib.sha256(data).hexdigest()
def read(rel):
    return (ROOT / rel).read_bytes()
def receipt(rel):
    data = read(rel)
    return {'path': rel, 'bytes': len(data), 'sha256': digest(data)}

parent_rel = PREFIX + 'f01-r19-dev-dual-temporal-a4-5/Kernel.lean'
parent = read(parent_rel)
source = (HERE/'Kernel-core-probe.lean').read_bytes()
fragment = (HERE/'Column4Temporal.lean.inc').read_bytes()
manifest = json.loads((HERE/'manifest.json').read_text(encoding='utf-8'))
assert digest(parent) == manifest['parent_sha256']
assert source == parent + b'\n' + fragment
assert digest(source) == manifest['source_sha256']
assert len(source) <= 256000
clean = re.sub(r'/\-.*?\-/', '', fragment.decode(), flags=re.S)
for banned in ['sorry', 'axiom', 'unsafe', 'extern', 'implemented_by', 'set_option', 'import']:
    assert not re.search(r'\b'+banned+r'\b', clean), banned

def body(text, namespace):
    start = text.index('namespace '+namespace)
    start = text.index('\ndef loop (', start)
    end = text.index('\ntheorem loop_eq ', start)
    return text[start:end]
old_body = body(parent.decode(), 'Submission.R19DualTemporal')
new_body = body(fragment.decode(), 'Submission.R19Column4Temporal')
mac = re.compile(r's(\d)\s*\+\s*a\.a(\d)\s*\*\s*b\.k(\d)c(\d)')

def stages(text, width):
    full, tail = text.split('  else if h0 : k<n then', 1)
    assert 'if h3 : k+3<n then' in full
    assert 'if k+1<n then' in tail and 'if k+2<n then' in tail
    assert 'loop n basePacket A B hA (t+1)' in full
    seqs = []
    for section, count in [(full, 4), (tail, 3)]:
        found = [tuple(map(int, m)) for m in mac.findall(section)]
        assert len(found) == count*width, (width, count, found)
        for lane in range(width):
            ops = [x for x in found if x[0] == lane]
            assert ops == [(lane,k,k,lane) for k in range(count)], ops
        seqs.append(found)
    return seqs
old_stages = stages(old_body,2)
new_stages = stages(new_body,4)

def trace(st, n, start, width):
    out = [[] for _ in range(width)]
    t = start
    while 4*t < n:
        full = 4*t+3 < n
        for lane, ai, bi, col in st[0 if full else 1]:
            if 4*t+ai < n:
                out[lane].append((4*t+ai,4*t+bi,col))
        if not full:
            break
        t += 1
    return out
checked = 0
for n in range(65):
    for t in range((n+3)//4+3):
        old = trace(old_stages,n,t,2)
        expected = old + [[(a,b,c+2) for a,b,c in lane] for lane in old]
        actual = trace(new_stages,n,t,4)
        assert actual == expected, (n,t,actual,expected)
        checked += 1

widths=[]
for p in range(1,9):
    pairs=(p+1)//2
    quads=(p+3)//4
    widths.append({'p':p,'old_computed_lanes':2*pairs,'new_computed_lanes':4*quads,
                   'intended_domain':3<=p<=8 and 2*pairs==4*quads})
assert [x['p'] for x in widths if x['intended_domain']]==[3,4,7,8]

# Extract old selected native evidence. This is a completed historical discovery,
# never a D17 or subsequent confirmation source.
old_capture = PREFIX+'f01-mul-log2-proof1/ci-runs/40080782614/download-3c198121366d4014aff9ec685d7af9ed/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-r12-column4-narrow/capture-6cd6a140f1db4f6a85d4c8b6d4584c6d/'
old_c = read(old_capture+'file-3-Submission.c').decode()
signature = 'LEAN_EXPORT lean_object* lp_competition_Submission_Packed4Index_loop___redArg('
start = old_c.index(signature)
if old_c[old_c.index(')',start)+1]==';':
    start=old_c.index(signature,start+len(signature))
end=old_c.index('\nLEAN_EXPORT ',start+len(signature))
old_c_body=old_c[start:end]
assert 'lean_array_uget_borrowed(v_A_' in old_c_body
assert 'lean_unbox_float32(v_a_' in old_c_body
(HERE/'old-r12-selected-loop.c.txt').write_text(old_c_body,encoding='utf-8')
old_asm=read(old_capture+'asm-1-2.txt').decode()
label='0000000000000000 <lp_competition_Submission_Packed4Index_loop___redArg>:'
start=old_asm.index(label)
end=old_asm.index('\nDisassembly of section ',start)
old_asm_body=old_asm[start:end]
assert 'movups xmm2,XMMWORD PTR' in old_asm_body and 'mulps' in old_asm_body
hot=old_asm_body[:old_asm_body.index('  a3:')]
assert '\tcall ' not in hot and '[rsp' not in hot
(HERE/'old-r12-selected-loop.asm.txt').write_text(old_asm_body,encoding='utf-8')

paths=[parent_rel,
       PREFIX+'f01-r15-dev-packed-b2-1/Kernel.lean',
       PREFIX+'f01-r16-dev-a4b2-entry3/Kernel.lean',
       PREFIX+'f01-r12-column4-narrow/Kernel.lean',
       PREFIX+'f01-d7-width4-proof2/Kernel.lean',
       PREFIX+'f01-d7-research/round3h-20261025T091810Z/astra-workers/matrix-architecture/cost-review-401854.md',
       PREFIX+'f01-d7-research/round6h-20261024T051445Z/astra-r12-conclusions.json',
       PREFIX+'f01-d7-research/round6h-20261024T051445Z/review-f4-historical-width4-counterexample.json',
       PREFIX+'f01-d7-research/round9h-20261026T194639Z/development-workers/anchor-323/dual-ci15-review/selected-chain.c.txt',
       PREFIX+'f01-d7-research/round9h-20261026T194639Z/development-workers/anchor-323/dual-ci15-review/native-paths.json',
       PREFIX+'f01-d7-research/round9h-20261026T194639Z/development-workers/structural-cost/indexed-b2.lean.inc',
       'competitions/floatlib/research/materials/20261024-r11/originals/W01/original-extracted/R11-W01/Kernel.conditional.lean',
       old_capture+'file-3-Submission.c',old_capture+'asm-1-2.txt']
result={
 'checked_at_utc':datetime.now(timezone.utc).isoformat(),
 'status':'STATIC_SOURCE_SCREEN_PASS_ONLY',
 'source_sha256':digest(source),'source_bytes':len(source),'parent_prefix_exact':True,
 'fragment_no_forbidden_tokens':True,
 'operation_graph_cases':checked,
 'operation_graph_scope':'Source-extracted per-lane MAC order and k-tail boundaries n=0..64; not an IEEE evaluation or Lean proof.',
 'widths':widths,
 'old_r12_actual_loop':'Full four-lane packed load/mulps/addps; compiler two-k unroll; hot no call/stack access. This is old, not a B16 novelty.',
 'conditional_runtime_request_model':{
   'assumptions':'64-bit 8B ctor header, 24B Array header, exact capacity; excludes allocator size classes, RC, closure/callback objects, temporaries and RSS.',
   'per_fused_four_column_group_per_k4':{'old_two_B8_with_array_slots':96,'new_B16_with_array_slot':80,'difference_new_minus_old':-16},
   'per_finished_four_columns':{'old_two_F2_cumulative':32,'new_F4_cumulative':24,'difference_new_minus_old':-8,
                              'old_one_live_F2':16,'new_one_live_F4':24,'live_difference_new_minus_old':8},
   'B_array_skeleton_per_group_pair':'Old two inner array headers plus two outer slots 64B; new one header plus one outer slot 32B; conditional -32B per pair of column groups.',
   'A_lifecycle':'Exactly existing global A4 cache remains; no new A cache or records.',
   'B_lifecycle':'A future complete packB must replace, not coexist with, old B8 cache on selected calls; not implemented in this probe.',
   'output':'Same p finish/replay/import/UInt32 boxes/push per row; no output cache or random writes intended.',
   'dynamic_time':'UNKNOWN',
 },
 'evidence':[receipt(p) for p in paths],
 'original_core_lean':'FAIL_STATEMENT_TWO_PACK_BRIDGE_GOALS_IN_40440668379',
 'repair1_lean':'NOT_RUN_BY_WORKER_PARENT_CI_FEEDBACK_PENDING',
 'new_C':'NOT_RUN_BY_WORKER','timing':'NOT_RUN','D17_or_confirmation_access':False,
}
(HERE/'static-check.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:result[k] for k in ['status','source_sha256','source_bytes','parent_prefix_exact','operation_graph_cases','original_core_lean','repair1_lean','new_C','timing']},indent=2))
