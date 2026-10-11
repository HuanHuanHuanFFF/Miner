"""Review frozen B1 bytes and phase priorities; historical denominators are explicit."""
from pathlib import Path
import datetime as dt
import hashlib
import json
import statistics

ROOT = Path(__file__).resolve().parents[1]
E = ROOT/'evidence/round26/route-b'
NATIVE = ROOT/'evidence/round26/38175512162/quality-b1-native/diagnostics/r13-encoder/encoder.json'
PROFILE = ROOT/'evidence/round26/38175512162/quality-b1-native/diagnostics/r18-functions/functions.json'


def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()


def main():
    enc, prof = [json.loads(p.read_bytes()) for p in (NATIVE,PROFILE)]
    assert enc['status']=='VERIFIED_FINITE_NATIVE_ORIGINAL_ENCODER_BYTES'
    assert prof['status']=='VERIFIED_FUNCTION_OBSERVER_TOKEN_AND_DECODE_EQUAL'
    assert enc['source_hashes']['public628']==prof['source_hashes']
    by = {(r['candidate'],r['file']):r for r in enc['rows']}
    base = {r['file']:r for r in enc['rows'] if r['candidate']=='public628'}
    assert len(base)==28
    pp = {r['file']:r for r in prof['rows']}
    for n,r in pp.items():
        assert (r['input_sha256'],r['raw_bytes'])==(base[n]['input_sha256'],base[n]['raw_bytes'])
    quality = []
    for name in enc['source_hashes']:
        rows=[r for r in enc['rows'] if r['candidate']==name]
        changes=[]
        for r in rows:
            b=base[r['file']]
            if r['tokens_sha256']!=b['tokens_sha256'] or r['output_sha256']!=b['output_sha256']:
                changes.append({'file':r['file'],'bytes_delta':r['output_bytes']-b['output_bytes'],
                                'tokens_delta':r['tokens']-b['tokens'],
                                'size_pp':100*(r['output_bytes']-b['output_bytes'])/r['raw_bytes']})
        quality.append({'candidate':name,'public_quality_pct':statistics.mean(100*r['output_bytes']/r['raw_bytes'] for r in rows),
                        'bytes':sum(r['output_bytes'] for r in rows),
                        'balanced_pp_delta':statistics.mean(100*(r['output_bytes']-base[r['file']]['output_bytes'])/r['raw_bytes'] for r in rows),
                        'changed_files':changes})
    modeled=[]
    for run, folder in [('38135739022','confirm-components-a2'),('38135751559','confirm-components-b2')]:
        for block in (1,2):
            for control in ('public595','public595-shadow'):
                path=ROOT/f'evidence/round25/{run}/{folder}/gate/round{block}-{control}.jsonl'
                records=[json.loads(x) for x in path.read_text().splitlines() if x.strip()]
                assert records[0]['warmup_rounds']==1 and records[0]['measured_rounds']==11
                rows={r['file']:r for r in records if r['kind']=='file'}
                assert rows.keys()==base.keys()
                denominators={}
                for name,r in rows.items():
                    assert (r['sha256'],r['raw_bytes'])==(base[name]['input_sha256'],base[name]['raw_bytes'])
                    values=[v['total_s'] for v in r['methods']['incumbent']['reps'] if v['phase']=='measured']
                    assert len(values)==11 and min(values)>0
                    denominators[name]=statistics.median(values)
                axes={fn:statistics.mean(r['functions'][fn]['inclusive_ns']/1e9/denominators[n] for n,r in pp.items()) for fn in prof['functions']}
                per_file=[]
                for name,r in pp.items():
                    per_file.append({'file':name,'borrowed_incumbent_total_s':denominators[name],
                        'contributions_to_model_parser_axis':{fn:r['functions'][fn]['inclusive_ns']/1e9/denominators[name]/28 for fn in prof['functions']},
                        'observed_inclusive_ns':r['functions']})
                per_file.sort(key=lambda r:r['contributions_to_model_parser_axis']['SFbase'],reverse=True)
                modeled.append({'run_id':run,'block':block,'control':control,
                    'denominator_receipt':path.relative_to(ROOT).as_posix(),'receipt_sha256':sha(path),
                    'model_axes':axes,'model_fractions_of_parser_axis':{fn:axes[fn]/axes['parse'] for fn in prof['functions'] if fn!='parse'},
                    'per_file':per_file})
    result={
        'status':'VERIFIED_FROZEN_NATIVE_BYTES_AND_PROFILE_WITH_INFERRED_BORROWED_DENOMINATOR_MODEL',
        'computed_utc':dt.datetime.now(dt.timezone.utc).isoformat(),
        'receipts':{p.relative_to(ROOT).as_posix():sha(p) for p in (NATIVE,PROFILE)},
        'source_hashes':enc['source_hashes'],'actual_quality':quality,'actual_profile_totals':prof['totals'],
        'models':modeled,
        'model_summary':{fn:{'min':min(m['model_fractions_of_parser_axis'][fn] for m in modeled),
                            'max':max(m['model_fractions_of_parser_axis'][fn] for m in modeled)}
                         for fn in ('SFbase','SFshape','refine','rf_find','rf_dp','rf_exact')},
        'decision':'Pause standalone RF-backward cloud timing/full-proof spend as the primary target route: its complete phase removal is only around1.2% of modeled parser axis under all borrowed denominators. Preserve source/model as a reusable structural DP experiment; reassess only after a different workload or base composition leaves useful target headroom. Prioritize the actual SFbase structure and real cross-stage matching coverage.',
        'limits':[
            'Native bytes and inclusive timings are VERIFIED on B1; official total timing for628 and these ablations is UNKNOWN.',
            'The denominators come from oldR25 runners, not thisB1 runner. Profiles mix code layout and observer overhead. This is an investment model, not a measured bound or current speed score.',
            'Model numerator excludes the628 encoder because it was not timed. Unknown encoder contributes additional nonnegative total time, but no real-world upper bound follows without valid comparable timing.',
            'Nested phase times overlap; never add SFbase/seed_parse/parse or rf_find/rf_dp/refine as separate savings.',
            'Sample range is not future hardware/private-set error bound or reward probability.',
        ],
    }
    (E/'b1-quality-and-priority.json').write_bytes((json.dumps(result,indent=2,ensure_ascii=False)+'\n').encode())
    print(json.dumps({'status':result['status'],'model_summary':result['model_summary'],
                      'quality':[{k:r[k] for k in ('candidate','public_quality_pct','balanced_pp_delta')} for r in quality]},indent=2))


if __name__=='__main__':
    main()
