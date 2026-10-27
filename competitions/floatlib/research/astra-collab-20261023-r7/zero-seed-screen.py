from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib.util,json,random
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[3]
sp=importlib.util.spec_from_file_location('word_oracle',HERE/'nonfinite-oracle.py');O=importlib.util.module_from_spec(sp);sp.loader.exec_module(O)
norm=lambda q: 0 if q==0x80000000 else q
r=random.Random(2026102305)
edge=[0,0x80000000,1,0x80000001,0x7fffff,0x800000,0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc12345,0xffc23456,0x7f800001,0xff800002]
pairs=[(x,y) for x in edge for y in edge]+[(r.getrandbits(32),r.getrandbits(32)) for _ in range(50000)]
h=hashlib.sha256();negativezero=0
for x,y in pairs:
    p=O.mul(x,y);expected=O.add(0,p);assert not O.snan(p) and expected==norm(p)
    negativezero+=int(p==0x80000000);h.update(x.to_bytes(4,'little')+y.to_bytes(4,'little')+expected.to_bytes(4,'little'))
qwords=edge+[r.getrandbits(32) for _ in range(50000)];checked=0
for q in qwords:
    if not O.snan(q):assert O.add(0,q)==norm(q);checked+=1
bad=0xff800011
out={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'status':'PASS_FINITE_ZERO_SEED_WORD_MODEL','seed':2026102305,'product_pairs':len(pairs),'non_signaling_q_cases':checked,'negativezero_products_requiring_correction':negativezero,'trace_sha256':h.hexdigest(),'witnesses':{'bare_mul_wrong_negativezero':{'x':'80000000','y':'3f800000','mul':f'{O.mul(0x80000000,0x3f800000):08x}','seeded':f'{O.add(0,O.mul(0x80000000,0x3f800000)):08x}'},'arbitrary_q_without_non_signaling_premise_is_false':{'q':f'{bad:08x}','normalize':f'{norm(bad):08x}','actual_add_poszero':f'{O.add(0,bad):08x}'}},'scope':'Own source-derived exact integer oracle only, not Lean/hardware proof or timing. Generalq needs non-signaling premise; product version closes it in actual Lean only after W10.'}
(HERE/'zero-seed-oracle.json').write_text(json.dumps(out,indent=2)+'\n')
base=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39840672791/download-81e3479e9e2b47249bf76c8d44eb2e62/diagnostics/f01-d7-public-suite/public-suite'
profile=json.loads((base/'parent-stage-profile/profile-current-public-plan.json').read_text());full=json.loads((base/'public-drawn-plan.json').read_text());same=profile==full
audit=json.loads((HERE/'nonnan-composition-807.json').read_text());candidate=next(x for x in audit['results'] if x['candidate']=='f01-d7-direct-nonnan')
rows=[]
for kernel,dim in [('sum','length'),('bmm','n')]:
    allcases=[c for c in profile['cases'] if c['timed'] and c['kernel']==kernel];cs=[c for c in allcases if c[dim]==1]
    outputs=lambda c:c['batch'] if kernel=='sum' else c['batch']*c['m']*c['p']
    cells=sorted(set(c['name'].rsplit(':',1)[0] for c in cs))
    rows.append({'kernel':kernel,'singleton_cases':len(cs),'timed_cases':len(allcases),'singleton_outputs':sum(outputs(c) for c in cs),'all_outputs':sum(outputs(c) for c in allcases),'case_names':[c['name'] for c in cs],'containing_cells':cells,'whole_cell_exposure_upper_not_expected_gain':sum(candidate['cells'][c]['sub'] for c in cells)/candidate['sub_total_ns'] if same else None})
exp={'checked_at_utc':datetime.now(timezone.utc).isoformat(),'profile_equals_actual_fullgate_drawn_plan':same,'source_plan_sha256':hashlib.sha256((base/'parent-stage-profile/profile-current-public-plan.json').read_bytes()).hexdigest(),'candidate_for_cell_bound':'60f74aa4 exact807 FULLPASS','rows':rows,'scope':'Observed general singleton shape exposure only. Output fraction is NOT time fraction. Whole containing-cell cost is a loose upper bound including unrelatedcases/preparation and cannot be treated as recoverabletime/gain/privateprevalence. No newruntime candidate queued.'}
(HERE/'singleton-exposure-807.json').write_text(json.dumps(exp,indent=2)+'\n');print(json.dumps(out,indent=2));print(json.dumps(exp,indent=2))
