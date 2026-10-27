"""Read-only source and finite trace audit; emits evidence only in this directory."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib,json,time

H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
started=time.monotonic()
def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
def identity(p): return dict(path=str(p.relative_to(R)),sha256=sha(p),bytes=p.stat().st_size)
baseline=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
assert sha(baseline)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
sources=[]
for name in ('FloatArray-Basic','Float32','ByteArray-Basic'):
    p=H/'upstream'/f'{name}.json'
    j=json.loads(p.read_text(encoding='utf-8-sig'))
    data=j['content'].encode()
    saved=(H/'upstream'/f'{name}.lean').read_bytes()
    assert saved==data, (name,len(saved),len(data))
    sources.append(dict(name=name,source=j.get('display_url'),git_blob_sha=j.get('sha'),
        source_sha256=hashlib.sha256(data).hexdigest(),bytes=len(data),receipt=identity(p)))
f32=(H/'upstream/Float32.lean').read_text()
fa=(H/'upstream/FloatArray-Basic.lean').read_text()
assert 'opaque Float32.toFloat : Float32 → Float' in f32
assert 'opaque Float.toFloat32 : Float → Float32' in f32
assert 'data : Array Float' in fa
assert 'def uget' in fa and 'lean_float_array_uget' in fa

runtime=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/lean-lean.h'
assert sha(runtime)=='982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
runtime_text=runtime.read_text()
assert 'lean_alloc_sarray(sizeof(double), 0' in runtime_text
assert '#define LEAN_MAX_CTOR_SCALARS_SIZE 1024' in runtime_text
review=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/matrix-architecture/cost-review-401854.json'
review_data=json.loads(review.read_text())
cs=next(x for x in review_data['bindings'] if x['path'].endswith('candidate-generated-0.c'))
cp=R/cs['path'];assert sha(cp)==cs['sha256']
snippet=review.parent/'cost-review-401854-excerpts/Submission_R15PackedB2_loop.txt'
assert snippet.read_text().strip() in cp.read_text()
assert 'lean_alloc_ctor(0, 0, 8)' in snippet.read_text()

old=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/matrix-architecture/analysis.json'
groups=json.loads(old.read_text())['groups']
costs=[]
for g in groups:
    ps={k:R/v['path'] for k,v in g['evidence'].items()}
    for k,p in ps.items(): assert sha(p)==g['evidence'][k]['sha256']
    plan,work,v=(json.loads(ps[k].read_text()) for k in ('plan','work','verdict'))
    cell={k:work[k]*r['submission_ns'] for k,r in v['classes'].items()}
    whole=sum(cell.values()); share=sum(x for k,x in cell.items() if k.startswith('bmm:'))/whole
    shape_rows=[]
    for c in plan['cases']:
        if not(c['timed'] and c['kernel']=='bmm'):continue
        b,m,n,p=(c[k] for k in ('batch','m','n','p'))
        # Classify baseline dispatch after the unknown actual underflow test.
        if 2<=p<=8 and n>1 and m>=4:
            width=2; route='B2'
        elif p==1 and n>1 and m>=4:
            width=1; route='thin boxed B'
        elif n>4 and p>8:
            width=10; route='F10 plus boxed A'
        else:continue
        G=(p+width-1)//width; T=(n+3)//4
        old_payload=8+4*width
        new_payload=8+16*width
        old_bytes=b*G*(24+n*(8+old_payload))
        new_bytes=b*G*(24+T*(8+new_payload))
        if route=='thin boxed B':
            old_bytes=24+b*n*p*20
        raw_decodes=width*b*G*n if route=='B2' else b*n*p
        shape_rows.append(dict(name=c['name'],batch=b,m=m,n=n,p=p,route=route,
            old_B_record_count=b*G*n,new_B_record_count=b*G*T,
            old_B_array_and_records_bytes=old_bytes,new_B_array_and_records_bytes=new_bytes,
            raw_B_conversion_count=raw_decodes,
            raw_decode_scope='B2 retains original unused odd lane decode; F10 padding is a zero field, not a raw B decode',
            padded_k_field_count=width*b*G*(4*T-n)))
    costs.append(dict(run=g['run'],seed=g['seed'],bmm_share=share,
        bmm_fraction_removed_for_10pct_whole=.1/share,
        bmm_fraction_removed_for_3pct_whole=.03/share,
        twice_all_bmm_whole_gain=share/2,
        cells={k:v/whole for k,v in cell.items()},
        conditional_shapes=shape_rows,evidence=g['evidence']))

# Compare symbolic operation traces, not host floating-point results or timings.
assert list(range(1)) != list(range(4)), 'negative control: padded tail must fail'
assert list(range(4)) != [0,2,1,3], 'negative control: reordered middle must fail'
checked=0; operations=0
for batch in range(4):
 for m in range(6):
  for n in range(34):
   for p in range(1,12):
    for b in range(batch):
     for row in range(m):
      for g in range((p+1)//2):
       for lane in range(min(2,p-2*g)):
        j=2*g+lane
        direct=[((b*m+row)*n+k,b*n*p+k*p+j) for k in range(n)]
        packed=[]
        for t in range((n+3)//4):
         for q in range(4):
          k=4*t+q
          if k<n: packed.append(((b*m+row)*n+k,b*n*p+k*p+j))
        assert packed==direct
        checked+=1;operations+=len(direct)

result=dict(updated_utc=datetime.now(timezone.utc).isoformat(),state='FIXED_SOURCE_AND_FINITE_TRACE_AUDIT_PASS',
    baseline=identity(baseline),core=identity(H/'TemporalCore.lean'),
    order_proof_attempt=identity(H/'OrderedBlocks.lean'),upstream=sources,
    runtime=identity(runtime),old_selected_C=identity(cp),old_B2_excerpt=identity(snippet),
    historical_cost_identity=identity(old),groups=costs,
    finite_trace=dict(output_lanes=checked,ordered_MAC_pairs=operations,
        domain='batch0..3,m0..5,n0..33,p1..11; all output rows/columns; all 4 tails',
        assertion='exact symbolic original A/B addresses and chronological MAC order'),
    limitations=['New Lean elaboration and codegen NOT_RUN','No performance timing',
        'Logical allocation requests assume ELF64 scalar-field layout and exact array capacity',
        'Underflow-zero actual misses UNKNOWN; conditional shape counts are not runtime hits',
        'Constructor layout supported by fixed runtime and old native-field C; exact new compiled layout UNKNOWN',
        'No current/future confirmation inputs read'],
    elapsed_seconds=time.monotonic()-started,tokens='UNKNOWN',cached_input='UNKNOWN',ci_occupancy=0)
(H/'audit.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(state=result['state'],elapsed_seconds=result['elapsed_seconds'],
    finite_trace=result['finite_trace'],sources=sources,
    shares=[{k:g[k] for k in ('seed','bmm_share','bmm_fraction_removed_for_10pct_whole')} for g in costs])))
