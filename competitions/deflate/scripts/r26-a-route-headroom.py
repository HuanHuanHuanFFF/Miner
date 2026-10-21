"""Read-only planning from actual641 route costs and historical OA evidence."""
from pathlib import Path
import hashlib
import importlib
import json
import statistics

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/route-a'


def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def dump(p,v):p.write_bytes((json.dumps(v,indent=2)+'\n').encode())


def main():
    route_path=ROOT/'evidence/round26/38176596170/boundary-a4-native/diagnostics/r26-a-boundary641/receipt.json'
    routes=json.loads(route_path.read_bytes());assert routes['status'].startswith('VERIFIED_')
    native_path=ROOT/'evidence/round26/38176193246/quality-a3-native/diagnostics/r13-encoder/encoder.json'
    native=json.loads(native_path.read_bytes());current={r['file']:r for r in native['rows']if r['candidate']=='public641'}
    actual={r['file']:r for r in routes['pairs']}
    groups={}
    for file,r in actual.items():
        if r['route_row']==13 or (r['route_row']==16 and current[file]['raw_bytes']==1100000):g='DX1'
        elif r['route_row']==15:g='OA'
        elif r['active_pc']:
            g='PC_chain' if r['route_row']in [0,7,10,16,18,19]else'PC_head'
        elif r['route_row']==6:g='PI1'
        else:g='other'
        groups[file]=g
    source=(ROOT/'references/round26-public-641/parse.rs').read_text()
    assert 'pub fn p135_row13(input:&[u8],out:&mut[u32])->usize{dx1_u118_run' in source
    assert 'else if n==1100000{dx1_u118_run' in source
    assert 'pub fn p135_row15(input:&[u8],out:&mut[u32])->usize{o_a_main_part' in source
    folder=ROOT/'evidence/round26/38176445754/screen-a3/gate'
    inventory=json.loads((folder/'raw-artifact-files.json').read_bytes())
    models=[]
    for block in [1,2]:
        path=folder/f'round{block}-public641.jsonl';assert sha(path)==inventory['files'][path.name]['sha256']
        data=[json.loads(s)for s in path.read_text().splitlines()];rows=[r for r in data if r['kind']=='file'];assert len(rows)==28
        def axis(selected,factor):
            total=0
            for row in rows:
                m=row['methods']['public641'];inc=row['methods']['incumbent'];assert m['deterministic']and not m['errors']
                samples=[(rep['time_s']*(factor if groups[row['file']]in selected else 1))+rep['encode_s']for rep in m['reps']if rep['phase']=='measured']
                denominator=statistics.median(rep['total_s']for rep in inc['reps']if rep['phase']=='measured')
                assert len(samples)==11
                total+=statistics.median(samples)/denominator/28
            return total
        baseline=axis(set(),1)
        scenarios=[]
        for selected in [['OA'],['DX1'],['OA','DX1'],['PC_chain'],['PC_chain','PC_head'],['OA','DX1','PC_chain','PC_head']]:
            for factor in [0,.5,.8]:
                value=axis(set(selected),factor)
                scenarios.append({'groups':selected,'assumed_parser_multiplier':factor,'hypothetical_axis':value,'relative_change_pct':100*(value/baseline-1)})
        models.append({'block':block,'raw':path.relative_to(ROOT).as_posix(),'raw_sha256':sha(path),'baseline_axis':baseline,'scenarios':scenarios})
    old=[]
    for name in ['round3-size385-dense4','round3-size385-dense3']:
        path=ROOT/f'evidence/round3/37488526325/round1-{name}.jsonl';data=[json.loads(s)for s in path.read_text().splitlines()];rows=[r for r in data if r['kind']=='file'];assert len(rows)==28
        changes=[]
        for r in rows:
            assert r['sha256']==current[r['file']]['input_sha256']
            if actual[r['file']]['active_pc']:
                delta=r['methods'][name]['output_bytes']-current[r['file']]['output_bytes']
                changes.append({'file':r['file'],'old_output_bytes':r['methods'][name]['output_bytes'],'current641_output_bytes':current[r['file']]['output_bytes'],'quality_delta_pp':100*delta/r['raw_bytes']/28})
        old.append({'candidate':name,'raw':path.relative_to(ROOT).as_posix(),'raw_sha256':sha(path),'parser_sha256':data[0]['methods'][name]['source_sha256'],'same_public_inputs':28,'old_benchmark_engine_sha256':data[0]['benchmark_provenance']['engine_sha256'],'hypothetical_replacement_of_current17PC_files_quality_delta_pp':sum(r['quality_delta_pp']for r in changes),'rows':changes,'scope':'Historical fixed-encoder measurements only. Not a newly implemented mixture, not current timing, and no file-specific replacement proposed.'})
    helper=importlib.import_module('make-round3-size385')
    old_functions=helper.function_bodies((ROOT/'references/round3-public-385/parse.rs').read_text())
    new_functions=helper.function_bodies(source)
    normalize=lambda s:''.join(s.split())
    oa=[n for n in old_functions if n.startswith('o_a_')and n in new_functions]
    same=[n for n in oa if normalize(old_functions[n])==normalize(new_functions[n])]
    result={'status':'VERIFIED_READING_AND_HYPOTHETICAL_MEDIAN_RECOMPUTATION_NOT_NEW_PERFORMANCE','route_receipt_sha256':sha(route_path),'native_receipt_sha256':sha(native_path),'groups':groups,'cost_models':models,'historical_oa_comparisons':old,'OA_385_to641_function_text':{'common':len(oa),'identical_whitespace_normalized':len(same),'changed':[n for n in oa if n not in same]},'limits':['Scaling selected parser times holds original encoder repetitions and paired incumbent measurements fixed, then reselects per-file medians. This is an opportunity model, not a realizable bound or observed speedup.','Historical OA dense3/4 used IH258/IT258/TS1/ACC63/LZT258 and LZN4 on every input; current641 OA uses10/256/8/5/32 and LZN1 on its existing route. Worse historical mixture does not prove every less-dense OA transfer impossible.','No new rank/share calculation here. All output claims remain scoped to exact sources and fixed public inputs.']}
    dump(OUT/'larger-route-headroom.json',result)
    print(json.dumps({'cost_models':[{'block':r['block'],'selected':[s for s in r['scenarios']if s['groups']in [['OA','DX1'],['PC_chain']]and s['assumed_parser_multiplier']in [0,.8]]}for r in models],'OA_text':result['OA_385_to641_function_text'],'old_OA_PC_replacement_quality_delta_pp':[r['hypothetical_replacement_of_current17PC_files_quality_delta_pp']for r in old]},indent=2))


if __name__=='__main__':main()
