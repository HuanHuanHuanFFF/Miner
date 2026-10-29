"""Recompute historical public shares only; never reads private/holdout inputs."""
from pathlib import Path
import collections
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/pins.json').is_file())
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z'
RAW = OLD / 'ci-runs/40611570030/download-032e40387a464ca39810735e751bed51/diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r22-dev-indexed8-cost1/runtime-cost'

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def shape(c):
    if c['kernel'] != 'bmm':
        return 'scalar' if c['kernel'] in ('add','mul') else 'sum'
    m,n,p = (c[k] for k in ('m','n','p'))
    if n == 0 or p == 0 or m == 0: return 'empty'
    if n == 1: return 'n1'
    if m < 4: return 'm_lt4_n_gt1'
    if p == 1: return 'm_ge4_p1_n_gt1'
    if p <= 8: return 'm_ge4_p2to8_n_gt1'
    return 'm_ge4_p_gt8_n_gt1'

def main():
    out = {'scope':'Historical public discovery only. No private-suite measurement or unseen confirmation. Dimensional exposure is not actual runtime branch attribution.', 'private':'UNKNOWN', 'raw':{}, 'groups':[]}
    for seed in (2220001,2220003):
        pp=RAW/f'plan-{seed}.json'; plan=json.loads(pp.read_bytes()); out['raw'][str(pp.relative_to(ROOT))]=sha(pp)
        cases=[c for c in plan['cases'] if c['timed']]
        for block,index in enumerate((4,7)):
            p=RAW/f'{seed}-{index}-control-rows.json'; rows=json.loads(p.read_bytes()); out['raw'][str(p.relative_to(ROOT))]=sha(p)
            whole=sum(rows[c['name']]['best_ns'] for c in cases)
            grouped={kind:collections.defaultdict(lambda:[0,0]) for kind in ('operation','category','shape','bmm_column','bmm_rows')}
            for c in cases:
                value=rows[c['name']]['best_ns']
                keys={'operation':c['kernel'],'category':':'.join(c['name'].split(':')[:2]),'shape':shape(c)}
                if c['kernel']=='bmm':
                    keys['bmm_column']='p1' if c['p']==1 else ('p2' if c['p']==2 else 'p3to8' if c['p']<=8 else 'p_gt8')
                    keys['bmm_rows']='m1' if c['m']==1 else 'm2to3' if c['m']<4 else 'm_ge4'
                for kind,key in keys.items():
                    grouped[kind][key][0]+=value;grouped[kind][key][1]+=1
            route_ns=sum(rows[c['name']]['best_ns'] for c in cases if c['kernel']=='bmm' and c['n']>1)
            out['groups'].append({'seed':seed,'block':block,'whole_ns':whole,'broad_n_gt1_ns':route_ns,'broad_n_gt1_whole_share':route_ns/whole,'shares':{kind:{key:{'ns':v[0],'cases':v[1],'whole_share':v[0]/whole} for key,v in group.items()} for kind,group in grouped.items()}})
    out['broad_n_gt1_share_range']=[min(g['broad_n_gt1_whole_share'] for g in out['groups']),max(g['broad_n_gt1_whole_share'] for g in out['groups'])]
    (HERE/'cost-frontier.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
    print(json.dumps([{'seed':g['seed'],'block':g['block'],'operation':g['shares']['operation'],'shape':g['shares']['shape']} for g in out['groups']],indent=2))

if __name__=='__main__':main()
