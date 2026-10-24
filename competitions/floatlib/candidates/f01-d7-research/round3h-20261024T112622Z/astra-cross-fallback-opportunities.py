"""At most two read-only next-mechanism hypotheses, on current source and old actual capture."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
CS=HERE.parent.parent
ROOT=CS.parents[2]
sha=lambda b:hashlib.sha256(b).hexdigest()
parent=(CS/'f01-d12-scalar-combined/Kernel.lean').read_bytes()
assert sha(parent)=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
reference=json.loads((HERE/'astra-preparation-reference.json').read_bytes())
cap=ROOT/reference['canonical_capture']
captured=(cap/'compiled-Submission.lean').read_bytes()
def cross(raw):
    text=raw.decode();a=text.index('namespace Submission.R11CrossRows\n');b=text.index('end Submission.R11CrossRows',a)
    return text[a:b].encode()
assert cross(parent)==cross(captured)
parser=HERE.parent/'round6h-20261024T051445Z/astra-audit-column4.py'
spec=importlib.util.spec_from_file_location('cross_readonly_parser',parser);mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
fs={}
for name in ['file-0-MainFull.c','file-3-Submission.c','file-6-BenchSuite.c']:
    fs.update(mod.functions((cap/name).read_text(),name))
paths=mod.paths_from(fs,['_lean_main'])
c=(cap/'file-3-Submission.c').read_text()
selected={}
for suffix in ['R11CrossRows_packShared___lam__0','R11CrossRows_packGeneral___lam__0','R11CrossRows_wordLoop___redArg','R11CrossRows_finish8','R11CrossRows_core___redArg','R11CrossRows_core___redArg___lam__0','R11CrossRows_rowWord___redArg']:
    matches=[n for n in fs if n.endswith(suffix)]
    assert len(matches)==1,(suffix,matches)
    n=matches[0];f=fs[n]
    print(suffix, 'ACTUAL_REACHABLE' if n in paths else 'GENERIC_NOT_REACHABLE')
    lines=c.splitlines();start=f['line']-1
    body='\n'.join(lines[start:])[:f['bytes']]
    selected[n]={**f,'MainFull_path':paths.get(n),
        'allocation_and_field_writes':[line.strip() for line in body.splitlines() if 'lean_alloc_ctor(' in line or 'lean_ctor_set_float32(' in line or 'lean_ctor_set_uint32(' in line]}
selected['actual_CrossRows_reachable_symbols']=[n for n in paths if 'R11CrossRows_' in n]
prior_path=HERE.parent/'round6h-20261024T051445Z/astra-lowexp-integer-dot-memo.json'
prior=json.loads(prior_path.read_bytes())
runs=[];totals=dict(cases=0,groups=0,P12_records=0,shared_P12_records=0,n1_groups=0,W8_records=0)
for run in prior['runs']:
    for ev in run['evidence'].values():assert sha((ROOT/ev['canonical_path']).read_bytes())==ev['sha256']
    cases=[]
    for item in run['cases']:
        batch,m,n,p=item['shape']
        if item['already_UnderflowZero_reconstructed'] or p!=2 or batch*m<4 or n==0:continue
        assert max(n,batch*m*n,batch*n*p,batch*m*p)<2**64
        groups=(batch*m+3)//4
        shared=sum((4*g)//m==(4*g+3)//m for g in range(groups))
        cases.append(dict(name=item['name'],shape=item['shape'],groups=groups,
            shared_groups=shared,P12_records=groups*n,shared_P12_records=shared*n,
            W8_records=groups,n1_groups=groups if n==1 else 0,MAC=item['MAC']))
    local={k:sum(x[k] for x in cases) for k in totals if k!='cases'};local['cases']=len(cases)
    for k in totals:totals[k]+=local[k]
    runs.append(dict(seed=run['seed'],run=run['run'],counts=local,cases=cases))
old_short_path=HERE.parent/'round7h-20261023T193125Z/result-918-f01-r11-crossrow-short-shared-vs-f01-r11-crossrow-p2-pack12-proof2.json'
old_short=json.loads(old_short_path.read_bytes())
assert old_short['full_gate_both'] and old_short['sha256']=='7cad7df494da6004b9e4b202f4d09b838ef8d4b79ba6fe934eea7287784fea28'
out=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='READ_ONLY_TWO_HYPOTHESES_NOT_CANDIDATES',
    current_parent_sha256=sha(parent),matching_CrossRows_namespace=dict(bytes=len(cross(parent)),sha256=sha(cross(parent))),
    actual_old_capture=reference['canonical_capture'],old_capture_source_sha256=sha(captured),actual_C=selected,
    source_counts=dict(scope='INFERRED completed-plan dispatch and representation counts; not events, allocator usable size or time.',totals=totals,runs=runs),
    hypotheses=[
      dict(id='CROSS_SHARED_INPUT_REPRESENTATION',
        problem='packShared computes four A values and two B values, then stores B values four times each in P12. The source has a 48-byte scalar payload; actual old matching C constructs it. This is separate from RowStream A.map/Packed10.packB.',
        proposed_mechanism='For existing same-B four-row groups, represent input with four A fields plus two B fields and broadcast B within the unchanged eight ordered chains. A more involved follow-on is separate per-batch B pairs reused across row blocks, only if repeat-conversion cost is measured. Preserve the general cross-batch packet path.',
        difference='R12 GeneralPanel changes A representation for four-row-by-ten-column F40 loops; this preserves already-adopted p=2/F8 computation and removes duplicated shared B storage. No width or threshold grid.',
        proof_path='Embed six-field packet into original P12; prove inputA/inputB and update projections equal, then ordered Nat/USize loop equality, finish8, blockRows and core. Keep general path and tails; no real-arithmetic reassociation or weakened NaN contract.',
        mathematical_obligations=['expand(a0,a1,a2,a3,c0,c1)=(a0,a1,a2,a3,c0,c0,c0,c0,c1,c1,c1,c1). Prove newUpdate(s,v)=oldUpdate(s,expand(v)) by field equality, without nonNaN/finite assumptions.',
          'Prove expand(pack6[k])=packShared[k] for every valid k; lift by induction through the original sequential recurrence. The eight chains each retain separate mul then add, starting+0.',
          'Select the compact loop outside the MAC loop under the existing equal-B-base condition. A tagged union or callback in each MAC would be a different cost mechanism and requires explicit inspection.'],
        first_falsifier='Use current diagnostic to isolate CrossRows shared pack/loop complete-call cost. If shared packets have little whole contribution, or new broadcasts/dual loads dominate the saved stores/traffic, park. High shared-record counts alone do not support allocation.',
        risk='Same-B subset excludes cross-batch groups; compact representation adds broadcast/shuffle needs. Whole gain UNKNOWN.'),
      dict(id='CROSS_OUTPUT_PRODUCER_CONSUMER_FUSION',
        problem='R11CrossRows.words materializes a Vector W8 for all four-row groups, then core reconstructs the final output with Vector.ofFn and quotient/remainder per output. The general RowStream and DirectContinuous writers already improved, but this CrossRows writer still retains the intermediate representation.',
        proposed_mechanism='Compute one current blockAt, emit its eight words directly in row order into the final preallocated Array, and release the block before proceeding; handle partial final row groups explicitly. Keep the current packed input/Float32 recurrence and NaN finish unchanged. Do not conflate this with removing input packets.',
        difference='Continuous output is an existing proven mechanism in other routes; here it is a new integration into the still-materialized CrossRows path. R12 column4 and F4 panel negatives do not measure this exact writer. Improvement is unverified, not a novel arithmetic claim.',
        proof_path='Reuse blockRows_word/rowWord_eq and RowStream Prefix/foldl invariant; preserve r=4*g+i, column order, valid tail bounds and raw Word8 bits. Complete original core_eq_rows and four-kernel gate still required.',
        mathematical_obligations=['For rows=batch*m and p=2, after g groups the output prefix length is 2*min(4*g,rows); element 2*r+j equals NativeFinal.dot n (r*n) ((r/m)*n*2+j) 2 A B for r<min(4*g,rows), j<2.',
          'For each block, emit row i only if 4*g+i<rows, then j=0 followed by j=1. Last-group tail lengths are2,4,6 when rows mod4 is1,2,3. Never emit padded rows or reorder the two columns.',
          'Keep blockRows computation unchanged initially, including unused tail lanes, and remove only the all-groups W8 Vector/reconstruction. This avoids relying on unproved zero-seed removal, skipping NaN replay, or reassociation.',
          'blockRows_word supplies per-element equality; Prefix induction supplies size/order, and prefix_vector_eq_ofFn closes the exact Vector result. These are a paper-level proof plan, not compiled new declarations.'],
        first_falsifier='Current CrossRows full-call/output phase must contain material intermediate-vector/reconstruction cost. Inspect actual caller: if compiler already scalar-replaces W8 and hoists div/mod, or output residual is too small, park. n=1 groups are especially sensitive to fixed overhead but cannot be assigned time by count.',
        risk='Actual finish8 reuses the F8 object for W8 when exclusive; its lean_alloc_ctor is the reuse-failure fallback. Do not count a fresh W8 allocation per group as confirmed. Word8 storage may remain once per block; safe claim is eliminating the all-groups Vector and second traversal. Additional append/closure/allocation would negate the intended effect.')],
    historical_short_shared_control=dict(path=str(old_short_path.relative_to(ROOT)).replace('\\','/'),sha256=sha(old_short_path.read_bytes()),run=old_short['run'],
      candidate=old_short['sha256'],baseline=old_short['baseline_sha256'],whole_normalized=old_short['relative_normalized_ratio'],BMM_normalized=old_short['per_operation_normalized']['bmm'],gain_p05=old_short['gain_p05'],
      lesson='R11 W03-derived7cad removed Vector P12 only for n1/n2 with all four B bases equal; same-run918 BMM was essentially tied with5c5e and whole failed. Do not repeat that unroll or claim that eliminating packets necessarily helps. Compact shared representation covers all n but needs new measured cost evidence; output fusion removes a distinct all-groups result vector, including nonshared n1 groups.'),
    decision='Wait for df5c diagnostic. Build no additional candidate or CI from this report. D chooses at most one material opportunity;708 remains frozen.',
    script_sha256=sha(Path(__file__).read_bytes()),source_record_sha256=sha(prior_path.read_bytes()))
(HERE/'astra-cross-fallback-opportunities.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
print(json.dumps(dict(totals=totals,source_namespace=out['matching_CrossRows_namespace'],selected_C=list(selected),directions=[x['id'] for x in out['hypotheses']]),indent=2))
