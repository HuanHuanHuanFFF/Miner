"""Exact total-median parser/encoder/paired-denominator decomposition for one frozen A candidate."""
from pathlib import Path
import argparse
import hashlib
import importlib
import json
import statistics as st

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/route-a'
MED=importlib.import_module('r26-measure-audit').median

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('folder');ap.add_argument('--name',required=True);ap.add_argument('--prefix',required=True);args=ap.parse_args()
    folder=Path(args.folder);folder=folder if folder.is_absolute()else ROOT/folder
    state=json.loads((folder/'state.json').read_bytes());ci=json.loads((folder/'ci-run.json').read_bytes())
    assert ci['status']=='completed'and ci['conclusion']=='success'
    inventory=json.loads((folder/'raw-artifact-files.json').read_bytes());entries={e['name']:e for e in state['spec']['entries']}
    names=['public641','public641-shadow',args.name,args.name+'-shadow'];assert all(n in entries for n in names)
    assert entries[names[0]]['hashes']==entries[names[1]]['hashes'];assert entries[names[2]]['hashes']==entries[names[3]]['hashes']
    measured={};files_bound={}
    for name in names:
        for block in [1,2]:
            p=folder/f'round{block}-{name}.jsonl';check=inventory['files'][p.name];assert digest(p)==check['sha256']and p.stat().st_size==check['bytes']
            records=[json.loads(line)for line in p.read_text().splitlines()if line.strip()];meta=records[0]
            assert meta['measured_rounds']==11 and meta['warmup_rounds']==1
            assert meta['methods'][name]['source_sha256']==entries[name]['hashes']['parse.rs']
            rows={x['file']:x for x in records if x['kind']=='file'};assert len(rows)==28 and sum(x['raw_bytes']for x in rows.values())==15930000
            for x in rows.values():x['chosen']={n:MED(x['methods'][n])for n in [name,'incumbent']}
            axis=st.mean(x['chosen'][name]['total_s']/x['chosen']['incumbent']['total_s']for x in rows.values())
            metric=next(m for m in state['metrics']if m['candidate']==name and m['round']==block);assert abs(axis-metric['time'])<1e-12
            measured[name,block]={'meta':meta,'rows':rows,'axis':axis};files_bound[p.relative_to(ROOT).as_posix()]=check
    pairs=[(names[0],names[1]),(names[2],names[3])]+[(a,b)for a in names[:2]for b in names[2:]];result=[]
    for a,b in pairs:
        for block in [1,2]:
            aa=measured[a,block];bb=measured[b,block];same=entries[a]['hashes']==entries[b]['hashes']
            assert aa['meta']['methods']['incumbent']['lib_sha256']==bb['meta']['methods']['incumbent']['lib_sha256']
            if same:assert aa['meta']['methods'][a]['lib_sha256']==bb['meta']['methods'][b]['lib_sha256']
            rows=[]
            for f,ar in aa['rows'].items():
                br=bb['rows'][f];assert ar['sha256']==br['sha256']and ar['raw_bytes']==br['raw_bytes']
                for key in ['tokens_sha256','output_sha256','output_bytes']:assert ar['methods']['incumbent'][key]==br['methods']['incumbent'][key]
                equal=all(ar['methods'][a][k]==br['methods'][b][k]for k in ['tokens_sha256','output_sha256','output_bytes'])
                if same:assert equal
                ac,ai=ar['chosen'][a],ar['chosen']['incumbent'];bc,bi=br['chosen'][b],br['chosen']['incumbent'];w=.5*(1/ai['total_s']+1/bi['total_s'])/28
                parse=(bc['parse_s']-ac['parse_s'])*w;encode=(bc['encode_s']-ac['encode_s'])*w
                denom=.5*(bc['total_s']+ac['total_s'])*(1/bi['total_s']-1/ai['total_s'])/28
                delta=(bc['total_s']/bi['total_s']-ac['total_s']/ai['total_s'])/28;assert abs(parse+encode+denom-delta)<1e-12
                rows.append({'file':f,'same_tokens_output':equal,'parse_pct_contribution':100*parse/aa['axis'],'encode_pct_contribution':100*encode/aa['axis'],
                  'denominator_pct_contribution':100*denom/aa['axis'],'raw_parse_change_pct':100*(bc['parse_s']/ac['parse_s']-1),
                  'raw_encode_change_pct':100*(bc['encode_s']/ac['encode_s']-1),
                  'parent_chosen':{k:ac[k]for k in ['parse_s','encode_s','total_s','order_index']},
                  'candidate_chosen':{k:bc[k]for k in ['parse_s','encode_s','total_s','order_index']}})
            components={k:sum(x[k]for x in rows)for k in ['parse_pct_contribution','encode_pct_contribution','denominator_pct_contribution']}
            total=100*(bb['axis']/aa['axis']-1);assert abs(sum(components.values())-total)<1e-10
            changed=[x for x in rows if not x['same_tokens_output']]
            result.append({'A':a,'B':b,'block':block,'same_source_binary':same,'A_axis':aa['axis'],'B_axis':bb['axis'],'relative_total_axis_pct':total,
              'components':components,'changed_token_files':len(changed),'changed_file_components':{k:sum(x[k]for x in changed)for k in components},'files':rows})
    report={'status':'VERIFIED_FROZEN_PAIRED_TOTAL_MEDIAN_COMPONENTS_NO_CURRENT_SCORE','folder':folder.relative_to(ROOT).as_posix(),'source_commit':state['git_sha'],
      'candidate':args.name,'hashes':entries[args.name]['hashes'],'input_files':files_bound,'comparisons':result,
      'limits':['Exact decomposition is descriptive, not causal attribution or corrected timing.','Two blocks and same-source shadows are one runner, not independent confirmation.','No public/formal pool share computed; latestofficial replay is separate.']}
    (OUT/(args.prefix+'-paired-cost.json')).write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps([{k:x[k]for k in ['A','B','block','same_source_binary','relative_total_axis_pct','components','changed_token_files','changed_file_components']}for x in result],indent=2))

if __name__=='__main__':main()
