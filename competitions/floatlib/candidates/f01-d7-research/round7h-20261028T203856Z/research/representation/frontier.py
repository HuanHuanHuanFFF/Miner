"""Recompute historical, exposed whole-case cost limits and bind primary sources."""
from pathlib import Path
from collections import defaultdict
from datetime import datetime, timezone
import hashlib, json, re

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').is_file())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
old = ROOT/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z'
base = old/'ci-runs/40611570030/download-032e40387a464ca39810735e751bed51/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-indexed8-cost1/runtime-cost'
result = json.loads((base/'result.json').read_bytes())
assert sha(base/'result.json') == '126d3162a4dea70630b307e6d50a35d7d2a15615baa7042b8ab763a5334b2340'
archive = json.loads((old/'ci-runs/40611570030/original-artifact-hashes.json').read_bytes())
pre = 'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-indexed8-cost1/runtime-cost/'
rows = []
for seed in (2220001, 2220003):
    run = next(r for r in result['runs'] if r['seed'] == seed and r['order'] == 4)
    plan = json.loads(run['environment']['BENCH_PLAN'])
    cases = {c['name']:c for c in plan['cases']}
    for order in (4,7):
        file = f'{seed}-{order}-control-rows.json'
        assert sha(base/file) == archive['files'][pre+file]['sha256']
        measured = json.loads((base/file).read_bytes())
        total = sum(c['best_ns'] for c in measured.values() if c['timed'])
        groups = defaultdict(lambda: {'cases':0, 'ns':0})
        details = []
        for name,t in measured.items():
            if not t['timed']: continue
            c=cases[name];k=c['kernel']
            groups[k]['cases']+=1;groups[k]['ns']+=t['best_ns']
            lower = c['center']-c['spread']-(c['scaleShift'] if c['scaleBlock'] else 0)
            # Conservative sufficient condition from published generator shape.
            warm = (c['mag'] != 2 and c['specRate']==0 and c['subPct']==0 and lower>=24
                    and (c['zeroPct']==0 or c['zeroKind'] in [0,1,2]))
            if k=='sum':
                if warm:
                    groups['sum_header_guaranteed_warm']['cases']+=1
                    groups['sum_header_guaranteed_warm']['ns']+=t['best_ns']
                details.append(dict(name=name, length=c['length'],batch=c['batch'],ns=t['best_ns'],
                    header_guaranteed_warm=warm,ordinary_exp_lower=lower))
        rows.append(dict(seed=seed,order=order,raw_sha256=sha(base/file),whole_ns=total,
            groups={k:dict(**v,whole_share=v['ns']/total) for k,v in groups.items()}, sum_cases=details))

index=old/'research/independent-frontier/codec-source-index.json'
sources=json.loads(index.read_bytes());verified=[]
for f in sources['files']:
    p=index.parent/f['name'];assert sha(p)==f['sha256']
    verified.append(dict(path=p.relative_to(ROOT).as_posix(),sha256=sha(p),
                         url=f['url'],license='Apache-2.0 per exact source header',header=f['header']))
out=dict(at_utc=datetime.now(timezone.utc).isoformat(),script_sha256=sha(Path(__file__)),
    scope='Only old, exposed R22 diagnostic control rows; whole-case measured shares are ceilings for complete elimination of those cases, not savings. Header guarantee excludes possible NaN/subnormal/low-exponent inputs; false means UNKNOWN. No new confirmation input or result read.',
    source_sha256=result['source_sha256'], original_manifest_sha256=sha(old/'ci-runs/40611570030/original-artifact-hashes.json'),
    rows=rows, primary_source_index_sha256=sha(index), pinned_lean_commit=sources['fixed_commit'],primary_sources=verified,
    selected_mechanism='One warm prefix, then tail-transfer once to original loop before first cold element. Remove the NEED for hot acc to survive decoder calls, NOT numeric decoding or native accumulator codec already absent.',
    first_falsifier='Actual pinned SUM object warm backedge has acc spill/reload or decoder/allocation calls; reject SUM cost premise if no work was removed.',
    machine_old_sum_spill='UNKNOWN; old generated C proves native accumulator but old observer did not save SUM machine body.',
    resource=dict(first_observed_utc='2026-10-28T20:43:06Z',shared_deadline_utc='2026-10-29T03:38:56Z',tokens='UNKNOWN',cache_tokens='UNKNOWN',ci_occupancy_seconds='UNKNOWN',local_lean=False))
(HERE/'frontier.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps([{'seed':r['seed'],'order':r['order'],'groups':r['groups']} for r in rows]))
