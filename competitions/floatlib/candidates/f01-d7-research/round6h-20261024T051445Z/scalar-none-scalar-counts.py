"""Bounded input-only None/invalid counts for exposed007/009 scalar public cases.

No hardware floating arithmetic, timing, Lean, CI or hidden/future plan is used.
Only already inspected generator/partner AST functions are loaded, never mains.
"""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,time

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
sha=lambda raw:hashlib.sha256(raw).hexdigest()


def functions(path,wanted,constants):
    raw=path.read_bytes();tree=ast.parse(raw)
    nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef)and n.name in wanted or isinstance(n,ast.Assign)and any(isinstance(t,ast.Name)and t.id in constants for t in n.targets)]
    assert {n.name for n in nodes if isinstance(n,ast.FunctionDef)}==set(wanted)
    env={};exec(compile(ast.Module(body=nodes,type_ignores=[]),str(path),'exec'),env)
    return raw,env


def main():
    started=time.monotonic();deadline=started+120
    generator_path=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
    partner_path=HERE.parent/'scalar-opportunity.py'
    gen_raw,gen=functions(generator_path,('word','ctz','element'),('M64','M32'))
    partner_raw,part=functions(partner_path,('partner',),('M32',))
    rows=[]
    for run_id in (40072436647,40073100983):
        run=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run_id}'
        idx=json.loads((run/'original-artifact-hashes.json').read_bytes());base=run/idx['directory']
        relative='diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
        plan_raw=(base/relative).read_bytes();assert sha(plan_raw)==idx['files'][relative]['sha256']
        plan=json.loads(plan_raw);cases=[]
        for c in plan['cases']:
            if not c['timed'] or c['kernel'] not in ('add','mul'):
                continue
            if not c['name'].split(':')[1]=='specials':
                assert c['mag']!=2 and c['specRate']==0
                cases.append({'name':c['name'],'work':c['work'],'source_raw_choose_some':0,'source_None_invalid':0,
                    'scope':'No raw/NaN/Inf input generator; source finite-input classification skips enumeration'})
                continue
            count={'name':c['name'],'work':c['work'],'source_raw_choose_some':0,'source_None_invalid':0}
            fixed=gen['element'](c,0,1,31)if c['relation']==4 else None
            inputs=hashlib.sha256();witness=[]
            for i in range(c['work']):
                if i%8192==0 and time.monotonic()>deadline:
                    raise TimeoutError('120second scalar input counting budget')
                a=gen['element'](c,i,0,31);b=part['partner'](c,i,a,gen['element'],gen['word'],fixed)
                ma,mb=a&0x7fffffff,b&0x7fffffff
                na,nb=ma>0x7f800000,mb>0x7f800000
                some=na or nb
                invalid=(ma==0x7f800000 and mb==0x7f800000 and bool((a^b)&0x80000000))if c['kernel']=='add' else ((ma==0x7f800000 and mb==0)or(mb==0x7f800000 and ma==0))
                none_invalid=bool(invalid and not some)
                count['source_raw_choose_some']+=some;count['source_None_invalid']+=none_invalid
                inputs.update(a.to_bytes(4,'little')+b.to_bytes(4,'little'))
                if none_invalid and len(witness)<3:
                    witness.append({'index':i,'a':hex(a),'b':hex(b)})
            count.update(input_pairs_le_sha256=inputs.hexdigest(),None_invalid_witnesses=witness)
            cases.append(count)
        totals={op:{key:sum(c[key]for c in cases if c['name'].startswith(op+':'))for key in ('work','source_raw_choose_some','source_None_invalid')}for op in ('add','mul')}
        for op,total in totals.items():
            denominator=total['source_raw_choose_some']+total['source_None_invalid']
            total['None_share_of_predicted_native_NaN_cold']=total['source_None_invalid']/denominator if denominator else None
            total['None_share_all_timed_scalar_inputs']=total['source_None_invalid']/total['work']
        rows.append({'run':run_id,'plan_sha256':sha(plan_raw),'totals':totals,'cases':cases})
    assert sha(generator_path.read_bytes())==sha(gen_raw) and sha(partner_path.read_bytes())==sha(partner_raw)
    report={'state':'COMPLETE_SOURCE_INPUT_CLASSIFICATION_ONLY','recorded_at_utc':datetime.now(timezone.utc).isoformat(),
        'seconds':time.monotonic()-started,'budget_seconds':120,'generator_ast_source_sha256':sha(gen_raw),'partner_ast_source_sha256':sha(partner_raw),
        'runs':rows,'classification':'Input rawChoose=None plus IEEE invalid pattern: opposite infinities for add; infinity-times-zero for mul. All selectedSome rawNaN operands separate. No operation cycles/stages or post-gate instrumentation measured.',
        'scope':'Finite exposed input reconstruction, not full-input proof, hardware frequency or exact compiled call counts. NativeNaN/input-invalid equivalence belongs to the accepted model bridges and proposed proof, not validated by these counts.',
        'BMM_replay_None_frequency':'UNKNOWN_NOT_ENUMERATED','sum_repair_None_frequency':'Known rawNaN q implies Some, so this None optimization does not target the sum firstrawNaN repair',
        'performance':'UNKNOWN'}
    (HERE/'scalar-none-scalar-counts.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':report['state'],'seconds':report['seconds'],'runs':[{'run':r['run'],'totals':r['totals']}for r in rows]},indent=2))


if __name__=='__main__':
    main()
