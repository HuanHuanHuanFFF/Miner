"""Bounded flat-tile layout, both-lane ordered expression, and source inverse checks."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,time
OUT=Path(__file__).resolve().parent
ROOT=next(p for p in OUT.parents if (p/'competitions/floatlib/pins.json').is_file())
start=time.monotonic();sha=lambda b:hashlib.sha256(b).hexdigest()
meta=json.loads((OUT/'b2-build-receipt.json').read_bytes())
base=(ROOT/meta['parent']).read_bytes();candidate=(OUT/meta['candidate']).read_bytes();frag=(OUT/meta['fragment']).read_bytes()
assert sha(base)==meta['parent_sha256'] and sha(candidate)==meta['candidate_sha256'] and sha(frag)==meta['fragment_sha256']
eol=b'\r\n' if b'\r\n' in base else b'\n'
insert=eol+frag.replace(b'\r\n',b'\n').replace(b'\n',eol)+eol
assert candidate.count(insert)==1
back=candidate.replace(insert,b'',1)
back=back.replace(b'else R15PackedB2.dispatch batch m n p A B',b'else R15ThinPairs.dispatch batch m n p A B')
back=back.replace(b'exact R15PackedB2.dispatch_spec batch m n p A B',b'exact R15ThinPairs.dispatch_spec batch m n p A B')
assert back==base
reads=0;chains=0;shapes=0
def read(size,i):return ('raw',i) if i<size else ('posZero',)
for batch in range(4):
 for n in range(7):
  for p in range(11):
   G=(p+1)//2;N=batch*n*p
   packed=[]
   for t in range(batch*G):
    b,g=divmod(t,G);baseB=b*n*p+2*g
    packed.append([(read(N,baseB+k*p),read(N,baseB+1+k*p)) for k in range(n)])
   for b in range(batch):
    for g in range(G):
     t=b*G+g;assert 0<=t<batch*G
     for k in range(n):
      for lane in range(2):
       assert packed[t][k][lane]==read(N,b*n*p+2*g+lane+k*p);reads+=1
   for m in range(9):
    emitted=[]
    for r in range(batch*m):
     b=r//m
     for g in range(G):
      t=b*G+g;count=min(2,p-2*g)
      for lane in range(2):
       old=new=('zeroSeed',)
       for k in range(n):
        a=('decode',read(batch*m*n,r*n+k))
        old=('add',old,('mul',a,('decode',read(N,b*n*p+2*g+lane+k*p))))
        new=('add',new,('mul',a,('decode',packed[t][k][lane])))
       assert old==new;chains+=1
      emitted.extend(r*p+2*g+l for l in range(count))
    assert emitted==list(range(batch*m*p));shapes+=1
    assert time.monotonic()-start<5

ap='competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-analysis-40099316795.json'
raw=(ROOT/ap).read_bytes();analysis=json.loads(raw);groups=[]
for seed in analysis['seeds']:
 selected=[]
 for c in seed['cases']:
  s=c['shape'];batch,m,n,p=s['batch'],s['m'],s['n'],s['p'];G=(p+1)//2
  if not(c['timed'] and c['kernel']=='bmm' and 2<=p<=8 and n>1 and m>=4 and c['route']['route']!='UnderflowZero'):continue
  selected.append({'name':c['name'],'shape':s,'old_B_scalar_values':batch*n*p,'new_B2_records':batch*G*n,
    'new_B2_native_fields_and_decodes':2*batch*G*n,'extra_odd_tail_decodes':batch*n*(p%2),
    'old_prepared_container_nodes_source':1,'new_prepared_container_nodes_source':1+batch*G,
    'old_hot_B_element_pointer_reads_source':2*batch*m*G*n,'new_hot_B_record_pointer_reads_source':batch*m*G*n,
    'same_active_finish_calls':batch*m*p,'same_terminal_F2_results':batch*m*G})
 groups.append({'seed':seed['seed'],'cases':selected})
receipt={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'STATIC_INVERSE_AND_FINITE_OPAQUE_TRACE_PASS',
 'candidate_sha256':sha(candidate),'candidate_bytes':len(candidate),'exact_inverse_to_b116':True,
 'packed_both_lane_read_checks':reads,'both_lane_ordered_expression_checks':chains,'shape_output_checks':shapes,
 'dimensions':{'batch':'0..3','m':'0..8','n':'0..6','p':'0..10'},
 'trace_limit':'Both active and unobserved odd-tail lanes compared as opaque decode/mul/add expressions in ascendingk. This is a finite source/address model, not Float32 execution or Lean acceptance.',
 'cost_model_source':ap,'cost_model_source_sha256':sha(raw),'source_cost_counts':groups,
 'cost_limit':'Counts are symbolic source evaluations/containers, not physical allocation counts, bytes, cache misses or time. New nested containers partly offset fewer B element records, especially shortn/oddp. Prep div/mod per tile, packing, pointer arrays, field decoding, returnF2, output and destruction all remain timed.',
 'elapsed_seconds':time.monotonic()-start}
assert receipt['elapsed_seconds']<5
(OUT/'b2-validation.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:receipt[k] for k in ['status','candidate_sha256','candidate_bytes','packed_both_lane_read_checks','both_lane_ordered_expression_checks','shape_output_checks','elapsed_seconds']}))
