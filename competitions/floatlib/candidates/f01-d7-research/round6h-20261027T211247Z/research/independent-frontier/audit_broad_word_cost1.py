"""Single selected-caller and negative discovery-cost audit; no timing rerun."""
from pathlib import Path
from datetime import datetime, timezone
import re, json, hashlib
D = Path(__file__).resolve().parent
R = next(p for p in D.parents if (p/'AGENTS.md').exists())
B = R/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/ci-runs/40602369221'
index = json.loads((B/'original-artifact-hashes.json').read_bytes()); A = B/index['directory']
pre = 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-broadword-cost1/runtime-cost/'
checked = []
def read(name):
    key = pre+name; p = A/key; b = p.read_bytes(); sha = hashlib.sha256(b).hexdigest()
    assert sha == index['files'][key]['sha256'], key
    checked.append({'path':str(p.relative_to(R)), 'sha256':sha, 'bytes':len(b)})
    return b
result = json.loads(read('result.json'))
assert result['source_sha256'] == '0274763264d760775e6a447848e873db418adc2e6fb651d117c5fc04b4b5d4a5'
assert result['measurement_complete'] and result['official_originals_unchanged']
input_key='diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r22-dev-broadword-cost1/Kernel.lean'
input_bytes=(A/input_key).read_bytes(); input_sha=hashlib.sha256(input_bytes).hexdigest()
assert input_sha == index['files'][input_key]['sha256'] == result['source_sha256']
assert input_bytes == (D/'Kernel-broad-word-add-probe.lean').read_bytes()
checked.append({'path':str((A/input_key).relative_to(R)),'sha256':input_sha,'bytes':len(input_bytes)})
C = read('build-product-0-R22BroadWordCostMain.c').decode()
ASM = read('own-object-0-asm.txt').decode(); NM = read('own-object-0-nm.txt').decode()
caller = read('caller.lean').decode(); flags = json.loads(read('flags-and-link.json'))
cpu = read('cpuinfo.txt').decode()
for name in ['prepare.json', 'stage-receipt.json', 'build-product-1-R22BroadWordCostMain.c.o.export.trace',
             'build-product-2-r22BroadWordCost.trace', 'build-product-3-r22BroadWordCost.rsp']:
    read(name)
assert all(flags[k]['equal_after_only_root_target_path_mapping'] for k in ['compile','link','link_response'])
assert 'Bench.Suite.run r22CostBroadWordAdd Submission.mul Submission.sum Submission.bmm' in caller
assert '@[inline] def r22CostBroadWordAdd' in caller
assert '.m_fun = (void*)lp_competition_main___lam__0___boxed' in C
assert 'v___f_1757_ = ((lean_object*)(lp_competition_main___closed__7));' in C
assert 'lp_competition_Bench_Suite_run(v___f_1757_,' in C
assert '.m_fun = (void*)lp_competition_main___lam__2___boxed' in C
assert 'v___f_1763_ = ((lean_object*)(lp_competition_main___closed__10));' in C

def cbody(sym):
    m = re.search(r'LEAN_EXPORT [^;\n]*\b'+re.escape(sym)+r'\([^\n]*\)\{',C); assert m
    depth = 1; j = m.end()
    while depth:
        if C[j] == '{': depth += 1
        elif C[j] == '}': depth -= 1
        j += 1
    return C[m.start():j]+'\n'
def asmfn(sym):
    m = re.search(r'^0+ <'+re.escape(sym)+r'>:\n',ASM,re.M); assert m
    end = ASM.find('\nDisassembly of section ',m.end())
    return ASM[m.start():end if end != -1 else len(ASM)]
new = cbody('lp_competition_main___lam__0'); old = cbody('lp_competition_main___lam__2')
newasm = asmfn('lp_competition_main___lam__0'); oldasm = asmfn('lp_competition_main___lam__2')
newbox = asmfn('lp_competition_main___lam__0___boxed'); oldbox = asmfn('lp_competition_main___lam__2___boxed')
canon = lambda x:re.sub(r'lp_competition_main___lam__[02]','ADD_CALLBACK',x)
assert canon(newbox) == canon(oldbox), 'Wrapper differs beyond callback name'
for name,s in [('broadword-selected.c',new),('broadword-control-selected.c',old),
               ('broadword-selected.asm.txt',newasm),('broadword-control-selected.asm.txt',oldasm),
               ('broadword-selected-wrapper.asm.txt',newbox)]:
    (D/name).write_text(s)

blocks = []; pure_cases=[]
bench_path=R/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/BenchSuite.lean'
bench_bytes=bench_path.read_bytes()
assert hashlib.sha256(bench_bytes).hexdigest() == '2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f'
checked.append({'path':str(bench_path.relative_to(R)),'sha256':hashlib.sha256(bench_bytes).hexdigest(),'bytes':len(bench_bytes),'source':'Pinned official4b7e838 BenchSuite; source classification only'})
for seed in [2220001,2220003]:
    plan=json.loads(read(f'plan-{seed}.json'))
    for block,ni,ci in [(0,1,0),(1,2,3)]:
        vals = {}
        for variant,order in [('broadword',ni),('control',ci)]:
            name = f'{seed}-{order}-{variant}'
            log = read(name+'.log').decode(); saved = json.loads(read(name+'-rows.json')); rows = {}
            for line in log.splitlines():
                m = re.fullmatch(r'(\S+) (true|false) ([0-9]+) ([0-9]+)',line)
                if m: rows[m[1]] = {'timed':m[2]=='true','best_ns':int(m[3]),'checksum':int(m[4])}
            assert rows == saved and len(rows) == 156
            vals[variant] = rows
        assert all(vals['broadword'][k]['checksum'] == vals['control'][k]['checksum'] for k in vals['control'])
        for case in plan['cases']:
            if case['kernel']!='add' or not case['timed']: continue
            cls=None
            if case['relation'] in [2,3]: cls='ALL_MISS_OPPOSITE_SIGNS_BY_RELATION'
            elif (case['relation']==0 and case['mag']==1 and case['positive']==100 and
                  all(case[k]==0 for k in ['zeroPct','subPct','specRate','scaleBlock']) and case['spread']<=24):
                cls='ALL_HIT_GRS_NORMAL_SAME_SIGN_GAP_LE24'
            if cls:
                name=case['name']; nr=vals['broadword'][name]; cr=vals['control'][name]
                pure_cases.append({'seed':seed,'block':block,'name':name,'classification':cls,
                                   'ratio':nr['best_ns']/cr['best_ns'],'normal_spread_bound':case['spread'],
                                   'scope':'Generator source and full case parameters, no additional input sampling or causal cycle attribution'})
        def sums(v):
            groups={}; ops={}; whole=0
            for k,r in v.items():
                if not r['timed']: continue
                cell=':'.join(k.split(':')[:2]); op=k.split(':')[0]; ns=r['best_ns']
                groups[cell]=groups.get(cell,0)+ns; ops[op]=ops.get(op,0)+ns; whole+=ns
            return groups,ops,whole
        ng,no,nw=sums(vals['broadword']); cg,co,cw=sums(vals['control'])
        blocks.append({'seed':seed,'block':block,'whole_ratio':nw/cw,'add_ratio':no['add']/co['add'],
                       'add_cells':{k:ng[k]/cg[k] for k in cg if k.startswith('add:')},
                       'rows_per_process':156,'checksum_match':True})
assert all(b['add_ratio'] > 1.41 and b['whole_ratio'] > 1.16 for b in blocks)
sizes={}
for sym in ['lp_competition_main___lam__0','lp_competition_main___lam__2',
            'lp_competition_main___lam__0___boxed','lp_competition_main___lam__2___boxed']:
    m=re.search(r'^\S+ ([0-9a-f]+) \S '+re.escape(sym)+r'$',NM,re.M); assert m
    sizes[sym]=int(m[1],16)
out={'verified_at_utc':datetime.now(timezone.utc).isoformat(),'run':40602369221,
     'source_sha256':result['source_sha256'],
     'selected_chain':'BENCH_VARIANT=broadword -> closed4/closed3 string -> closed7 -> main.lam0.boxed -> main.lam0; control -> closed10 -> main.lam2.boxed -> main.lam2',
     'selected_symbols':sizes,'boxed_wrapper_equal_after_name_mapping':True,
     'blocks':blocks,'CPU':re.search(r'model name\s*:\s*(.+)',cpu).group(1),
     'pure_domain_case_evidence':pure_cases,
     'flags_equal_except_owned_target_paths':True,'execution_config':result['execution_config'],
     'build_identities_producer_record_not_local_binary_rehash':result['build_identities'],
     'checked_files':checked,'scope':'Owned object linked into complete guarded discovery diagnostic. Object/binary not retained locally; their digests are producer records. Not original25-round gate, new public ADD proof or independent confirmation.',
     'decision':'PARK frozen5655/0274; no further proof/seed. Selected-code observations in BROAD-WORD-COST-DECISION.md.'}
(D/'broadword-cost1-audit.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({'checked_files':len(checked),'blocks':blocks,'sizes':sizes,'boxed_wrapper_equal':True}))
