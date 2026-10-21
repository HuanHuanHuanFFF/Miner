"""Audit where paired total-time differences enter the original equal-file axis."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,statistics as st

ROOT=Path(__file__).resolve().parents[1]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def read_measurement(folder,name,block):
    p=(folder/f'round{block}-{name}.jsonl').resolve();assert p.is_relative_to(folder.resolve());rows=[json.loads(x)for x in p.read_text().splitlines()];meta=rows[0];files={}
    assert meta['measured_rounds']==11 and meta['warmup_rounds']==1
    for row in rows:
        if row.get('kind')!='file':continue
        stats={}
        for n in(name,'incumbent'):
            m=row['methods'][n];assert m['deterministic']and not m['errors'];reps=sorted([r for r in m['reps']if r['phase']=='measured'],key=lambda r:r['total_s']);assert len(reps)==11;rep=reps[5]
            assert abs(rep['time_s']+rep['encode_s']-rep['total_s'])<1e-12
            stats[n]={'total':rep['total_s'],'parse':rep['time_s'],'encode':rep['encode_s']}
        v=stats[name];inc=stats['incumbent']['total'];assert inc>0;files[row['file']]={'input_sha256':row['sha256'],'output_sha256':row['methods'][name]['output_sha256'],'tokens_sha256':row['methods'][name]['tokens_sha256'],'raw_total':v['total'],'incumbent_total':inc,'ratio':v['total']/inc,'parse_ratio':v['parse']/inc,'encode_ratio':v['encode']/inc}
    assert len(files)==28;return {'file':str(p.relative_to(ROOT)),'sha256':sha(p),'source_sha256':meta['methods'][name]['source_sha256'],'library_sha256':meta['methods'][name]['lib_sha256'],'files':files,'axis':st.mean(v['ratio']for v in files.values())}

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('receipts',type=Path,nargs='+');ap.add_argument('--candidate-sha',required=True);ap.add_argument('--anchor-id',required=True);ap.add_argument('--output',type=Path,required=True);args=ap.parse_args();result=[];audits={}
    for folder in args.receipts:
        folder=folder.resolve();state=json.loads((folder/'state.json').read_bytes());inv=json.loads((folder/'raw-artifact-files.json').read_bytes())
        for name,v in inv['files'].items():
            p=(folder/name).resolve();assert p.is_relative_to(folder)and p.stat().st_size==v['bytes']and sha(p)==v['sha256']
        entries=state['spec']['entries'];candidates=[e['name']for e in entries if e['hashes']['parse.rs']==args.candidate_sha];anchors=[e['name']for e in entries if e.get('formal_id')==args.anchor_id];assert len(candidates)==1 and anchors
        primary=next(n for n in anchors if not n.endswith('-shadow'));shadow=primary+'-shadow';names={e['name']for e in entries};candidate=candidates[0];pairs=[(candidate,primary)]+([(candidate,shadow),(shadow,primary)]if shadow in names else[])
        for block in sorted({m['round']for m in state['metrics']}):
            cache={}
            for n in{n for pair in pairs for n in pair}:cache[n]=read_measurement(folder,n,block);audits[cache[n]['file']]=cache[n]['sha256']
            for cn,pn in pairs:
                c,p=cache[cn],cache[pn];rows=[]
                for file,cv in c['files'].items():
                    pv=p['files'][file];assert cv['input_sha256']==pv['input_sha256'];unit=100/(28*p['axis']);total=(cv['ratio']-pv['ratio'])*unit
                    prog=.5*(1/cv['incumbent_total']+1/pv['incumbent_total'])*(cv['raw_total']-pv['raw_total'])*unit
                    denom=.5*(cv['raw_total']+pv['raw_total'])*(1/cv['incumbent_total']-1/pv['incumbent_total'])*unit;assert abs(prog+denom-total)<1e-10
                    rows.append({'file':file,'input_sha256':cv['input_sha256'],'output_and_tokens_unchanged':cv['output_sha256']==pv['output_sha256']and cv['tokens_sha256']==pv['tokens_sha256'],'axis_change_contribution_pct':total,'parse_component_contribution_pct':(cv['parse_ratio']-pv['parse_ratio'])*unit,'encode_component_contribution_pct':(cv['encode_ratio']-pv['encode_ratio'])*unit,'symmetric_raw_program_allocation_pct':prog,'symmetric_incumbent_allocation_pct':denom,'raw_program_time_delta_pct':100*(cv['raw_total']/pv['raw_total']-1),'incumbent_time_delta_pct':100*(cv['incumbent_total']/pv['incumbent_total']-1)})
                total=100*(c['axis']/p['axis']-1);assert abs(total-sum(r['axis_change_contribution_pct']for r in rows))<1e-10
                result.append({'run_id':state['run_id'],'block':block,'candidate_name':cn,'anchor_name':pn,'same_rust':c['source_sha256']==p['source_sha256'],'same_library':c['library_sha256']==p['library_sha256'],'total_axis_delta_pct':total,'candidate_parse_fraction_of_axis':sum(r['parse_ratio']for r in c['files'].values())/(28*c['axis']),'anchor_parse_fraction_of_axis':sum(r['parse_ratio']for r in p['files'].values())/(28*p['axis']),'changed_output_contribution_pct':sum(r['axis_change_contribution_pct']for r in rows if not r['output_and_tokens_unchanged']),'unchanged_output_contribution_pct':sum(r['axis_change_contribution_pct']for r in rows if r['output_and_tokens_unchanged']),'largest_absolute_observed_contributions':sorted(rows,key=lambda r:abs(r['axis_change_contribution_pct']),reverse=True)[:5],'per_file':rows})
    output={'status':'VERIFIED_RAW_ORIGINAL_AXIS_COMPONENT_RECOMPUTATION','created_at_utc':datetime.now(timezone.utc).isoformat(),'candidate_rust_sha256':args.candidate_sha,'anchor_formal_id':args.anchor_id,'comparisons':result,'input_sha256':audits,'scope':'Parser/encoder components use the same actual rep that supplies the odd11-rep total median; they sum to the measured original axis. The symmetric program/incumbent allocation is algebra on observed measurements, not a controlled causal experiment or an adjusted score. Unchanged output does not prove unchanged runtime or code path. No diagnostic timing is mixed in.'};args.output.write_bytes((json.dumps(output,indent=2)+'\n').encode())
    for row in result:
        print(json.dumps({k:v for k,v in row.items()if k not in('per_file','largest_absolute_observed_contributions')},ensure_ascii=False))

if __name__=='__main__':main()
