"""Read-only scope/proof/size/exposure review. Does not produce a Kernel candidate."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,re,sys,time
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent;CS=HERE.parent.parent;ROOT=CS.parents[2]
sha=lambda b:hashlib.sha256(b).hexdigest()
started=time.monotonic();deadline=started+180
raw=(CS/'f01-r13-preparation-convert/Kernel.lean').read_bytes()
assert sha(raw)=='7086031b8164647e199f52c6b44fc7f54233ec4e75e2221fa95d30a676270d57'
s=raw.decode();a=s.index('namespace Submission.R11CrossRows\n');b=s.index('end Submission.R11CrossRows',a);scope=s[a:b]
changes=[];delta=0
for name,stop,count in [('packGeneral','packGeneral_a',12),('packShared','packShared_eq',6)]:
    start=scope.index('def '+name+' (');end=scope.index('\ntheorem '+stop,start);body=scope[start:end]
    assert body.count('ExecFloat.Binary.toFloat32')==count
    new=body.replace('ExecFloat.Binary.toFloat32','R13NativePrep.toNative')
    diff=len(new.encode())-len(body.encode());delta+=diff
    changes.append(dict(definition=name,line=s.count('\n',0,a+start)+1,sites=count,byte_delta=diff,
        original_definition_sha256=sha(body.encode()),replacement='ExecFloat.Binary.toFloat32 -> R13NativePrep.toNative inside this definition only'))
for lane in ['inputA','inputB']:
    before=f'simp [packGeneral, Packed10.vector_get_ofFn, {lane}, select4]'
    after=f'simp [packGeneral, Packed10.vector_get_ofFn, {lane}, select4, R13NativePrep.toNative_eq]'
    assert scope.count(before)==1
    diff=len(after.encode())-len(before.encode());delta+=diff
    changes.append(dict(proof=lane,before=before,after=after,byte_delta=diff))
history=[];pack_hashes={};source_candidates=0
for file in CS.glob('*/Kernel.lean'):
    text=file.read_text(encoding='utf-8')
    if 'namespace Submission.R11CrossRows\n' not in text:continue
    source_candidates+=1
    ns=text.index('namespace Submission.R11CrossRows\n');end=text.index('end Submission.R11CrossRows',ns);part=text[ns:end]
    for name,stop in [('packGeneral','packGeneral_a'),('packShared','packShared_eq')]:
        st=part.index('def '+name+' (');en=part.index('\ntheorem '+stop,st);body=part[st:en]
        h=sha(body.encode());pack_hashes.setdefault(name,{}).setdefault(h,[]).append(file.parent.name)
        if 'R2W01b.convert' in body or 'R13NativePrep.toNative' in body or 'directDecode' in body:
            history.append(dict(candidate=file.parent.name,definition=name,sha256=h))
prior_path=HERE.parent/'round6h-20261024T051445Z/astra-lowexp-integer-dot-memo.json'
prior=json.loads(prior_path.read_bytes())
for e in prior['source_bindings']:assert sha((ROOT/e['path']).read_bytes())==e['sha256']
ep=HERE.parent/'round7h-20261023T193125Z/review-output-underflow-exposure.py'
sp=importlib.util.spec_from_file_location('cross_input_transcription',ep);ex=importlib.util.module_from_spec(sp);sp.loader.exec_module(ex)
element=ex.load_generator(ex.RESEARCH/'public-nonfinite-opportunity.py')['element']
totals=dict(cases=0,conversion_calls=0,valid_reads=0,default_zero_reads=0,warm=0,fallback=0,shared_calls=0,general_calls=0)
runs=[]
for run in prior['runs']:
    for ev in run['evidence'].values():assert sha((ROOT/ev['canonical_path']).read_bytes())==ev['sha256']
    rows=[];local={k:0 for k in totals}
    for case in run['cases']:
        batch,m,n,p=case['shape'];c=case['generator_case']
        if case['already_UnderflowZero_reconstructed'] or p!=2 or batch*m<4 or n==0:continue
        counts={k:0 for k in totals};counts['cases']=1
        groups=(batch*m+3)//4
        for g in range(groups):
            assert time.monotonic()<deadline
            rr=[4*g+i for i in range(4)];bb=[r//m for r in rr];shared=all(v==bb[0] for v in bb)
            for k in range(n):
                addresses=[(0,r*n+k,batch*m*n,n) for r in rr]
                # Shared branch computes just two B values; general computes8,
                # including duplicate addresses. Default getD zero is converted too.
                if shared:addresses += [(1,(bb[0]*n+k)*p+j,batch*n*p,p) for j in range(2)]
                else:addresses += [(1,(v*n+k)*p+j,batch*n*p,p) for j in range(2) for v in bb]
                for role,i,length,width in addresses:
                    valid=i<length;u=element(c,i,role,width) if valid else 0;mag=u&0x7fffffff
                    fast=mag==0 or 0x0c000000<=mag<0x7f800000
                    counts['conversion_calls']+=1;counts['valid_reads']+=valid;counts['default_zero_reads']+=not valid
                    counts['warm']+=fast;counts['fallback']+=not fast
                    counts['shared_calls' if shared else 'general_calls']+=1
        for key in totals:local[key]+=counts[key]
        rows.append(dict(name=c['name'],shape=case['shape'],counts=counts))
    for key in totals:totals[key]+=local[key]
    runs.append(dict(seed=run['seed'],run=run['run'],counts=local,cases=rows))
rec=dict(at_utc=datetime.now(timezone.utc).isoformat(),elapsed_seconds=time.monotonic()-started,
    state='READ_ONLY_CROSS_PREPARATION_CONVERTER_REVIEW_NO_NEW_KERNEL',parent708_sha256=sha(raw),changes=changes,
    projected_byte_delta=delta,projected_total_bytes=len(raw)+delta,source_budget_limit=256000,
    size_scope='Exact textual delta for these four bounded edits only; no new declaration and no new Kernel file written. Later proof repairs or other combinations may change size.',
    proof_bridge=['Existing unconditional R13NativePrep.toNative_eq applies to every Binary32, including getD default posZero. No finite/nonNaN or bounds premise added.',
      'packGeneral_a and packGeneral_b keep the original toFloat32 conclusions and gain one local rewrite lemma in their simp lists.',
      'packShared_eq remains definitionally equal after applying the same decoder substitution to both pack definitions; its rfl structure is unchanged. New exact-source Lean elaboration remains NOT_RUN.',
      'pack_a/pack_b, Nat/USize recurrence proofs, finish8, tails, dispatcher and four public specs retain their source statements; intended composition through old lemmas, not inherited acceptance.'],
    history=dict(direct_candidate_Kernel_files_with_CrossRows=source_candidates,pack_definition_hash_groups=pack_hashes,matched_existing_converter_spellings=history,
      boundary='Bounded direct candidate-file search, not a global novelty proof. No matching converter spellings in the actual pack bodies is only evidence for this repository scope.',
      R9_negative='d5e3512f run39961709177 fullPASS but BMM1.17313/whole1.04035 versus41. Its original548 manifest explicitly changes direct dot per-MAC decoding only and leaves packed pipeline unchanged.'),
    exposure=dict(state='INFERRED_PINNED_SOURCE_COUNTS_NOT_RUNTIME_EVENTS_OR_TIMES',totals=totals,runs=runs,
      boundary='Conversions are once per selected group and k field, not globally once per unique matrix element. B can be reconverted in later row groups. Cross getD tail zeros are actually converted; unlike Packed10 j>=p padding, these are included explicitly.'),
    first_falsifier='If708 misses whole gate and exact current Cross preparation is appreciable, one integrated candidate may be worth original statement/full comparison. Require actual C/machine warm branches, fallback spills, unchanged packShared two-B reuse and output semantics; reject if total branch/table/FP cost or register pressure cancels foreign-call reduction. Do not add separate gains or use exposure as time.',
    risk='R9 shows numeric conversion can regress when moved into a MAC path. This proposal changes only P12 preparation, but pack lifetimes are short and some n=1 cases can still pay dominant predicate/setup cost. Whole gain UNKNOWN.',
    next_action='D decides after profile and708 cleanD; no candidate or CI generated by this script.',
    source_record_sha256=sha(prior_path.read_bytes()),script_sha256=sha(Path(__file__).read_bytes()))
(HERE/'astra-cross-converter-review.json').write_text(json.dumps(rec,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps(dict(delta=delta,projected_bytes=rec['projected_total_bytes'],history_candidates=source_candidates,history_hits=history,totals=totals,seconds=rec['elapsed_seconds']),indent=2))
