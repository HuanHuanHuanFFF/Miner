"""Bounded diagnostic on exposed R15 plans. No Lean, timing or future holdout reads."""
import ast, hashlib, json, time
from pathlib import Path
from datetime import datetime, timezone

D = Path(__file__).resolve().parent
R = next(p for p in D.parents if (p / 'AGENTS.md').exists())
G = R / 'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
tree = ast.parse(G.read_bytes())
env = {}
nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in {'word','ctz','element'} or isinstance(n, ast.Assign) and any(isinstance(z, ast.Name) and z.id in {'M32','M64'} for z in n.targets)]
exec(compile(ast.Module(body=nodes, type_ignores=[]), str(G), 'exec'), env)

def checked(base, idx, name):
    p = base / idx['directory'] / name
    b = p.read_bytes()
    assert hashlib.sha256(b).hexdigest() == idx['files'][name]['sha256'], name
    return p, json.loads(b), hashlib.sha256(b).hexdigest()

def main():
    start = time.monotonic()
    runs = []
    reads = 0
    for run in [40168687803,40169957447,40171180249]:
        base = R / f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
        idx = json.loads((base / 'original-artifact-hashes.json').read_bytes())
        prefix = 'diagnostics/f01-d7-public-suite/public-suite/'
        pp, plan, ph = checked(base, idx, prefix+'public-drawn-plan.json')
        vp, verdict, vh = checked(base, idx, prefix+'f01-r15-dev-packed-b2-1-verdict.json')
        rows = []
        for c in plan['cases']:
            if not c['timed'] or c['kernel'] != 'sum': continue
            n = c['length']
            bs = sorted(set([0, c['batch']//2, c['batch']-1]))
            samples = []
            for b in bs:
                if reads + n > 180000 or time.monotonic()-start > 4.0: break
                ws = [env['element'](c,b*n+k,0,n) for k in range(n)]
                reads += n
                es = [(w>>23)&255 for w in ws]
                samples.append({'batch_index':b,'max_exp':max(es,default=0),'all_exp_le_8':all(e<=8 for e in es),'all_exp_le_24':all(e<=24 for e in es),'all_exp_le_31':all(e<=31 for e in es),'all_true_subnormal_or_zero':all(e==0 for e in es)})
            rows.append({'name':c['name'],'length':n,'batch':c['batch'],'center':c['center'],'spread':c['spread'],'subPct':c['subPct'],'samples':samples})
        runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'plan_path':str(pp.relative_to(R)),'verdict_path':str(vp.relative_to(R)),'classes':verdict['classes'],'rows':rows})
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'BOUNDED_SOURCE_TRANSCRIPTION_ONLY','scope':'Three exposed R15 plans; candidate source B2; class timing belongs only to archived runs. Sample counts are not removable time. Generator has not been crosschecked with actual Lean output.','reads':reads,'elapsed_seconds':time.monotonic()-start,'generator_translation_sha256':hashlib.sha256(G.read_bytes()).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'runs':runs}
    (D/'low-sum-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
    for r in runs:
        hits=[x['name'] for x in r['rows'] if x['samples'] and all(s['all_exp_le_24'] for s in x['samples'])]
        print(json.dumps({'run':r['run'],'sampled_low24_cases':hits,'sampled_rows':sum(len(x['samples']) for x in r['rows'])}))
    print(json.dumps({'reads':reads,'elapsed_seconds':out['elapsed_seconds']}))

if __name__=='__main__': main()
