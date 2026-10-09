"""Recompute R17 public paired evidence and declared-family frontier projections."""
from pathlib import Path
import argparse
import hashlib
import json
import statistics
from round3 import load_scorer
from round10_payability import analyze_payability, load_flat_rows, validate_policy_for_replay

ROOT=Path(__file__).resolve().parents[1]

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('receipts',type=Path,nargs='+')
    ap.add_argument('--capture',type=Path,default=ROOT/'evidence/round17/official-start')
    ap.add_argument('--output',type=Path,required=True)
    ap.add_argument('--final',action='store_true')
    args=ap.parse_args()
    competition,context,rows=load_flat_rows(args.capture)
    scorer=load_scorer(ROOT/'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py')
    policy=competition['policy'];policy_check=validate_policy_for_replay(policy,rows,scorer)
    bounds=scorer.Boundaries(policy['max_balanced_time_ratio'],policy['max_mean_file_compression_pct'])
    formal={r['id']:r for r in rows};groups={};runs=[];identities={};input_ids={};timing_owners={};shadows=[];pipeline_shadows=[];pc507_shadows=[];family_shadows=[];verified_controls=[]
    # A candidate's later control role must not discard its actual standard measurements.
    # Determine declared families first so receipt argument order cannot affect inclusion.
    declarations={}
    for folder in args.receipts:
        state=json.loads((folder/'state.json').read_bytes());entries={e['name']:e for e in state['spec']['entries']}
        for n,e in entries.items():
            if e.get('control') or not n.startswith(('r12-','r13-','r14-','r15-','r16-','chat-20261008-')):continue
            value=(entries[e['anchor']]['formal_id'],e['comparison_baseline'])
            assert declarations.setdefault(e['hashes']['parse.rs'],value)==value
    for folder in args.receipts:
        state=json.loads((folder/'state.json').read_bytes());ci=json.loads((folder/'ci-run.json').read_bytes())
        assert str(ci['databaseId'])==state['run_id'] and ci['headSha']==state['git_sha']
        if args.final: assert ci['status']=='completed'
        inv=json.loads((folder/'raw-artifact-files.json').read_bytes())
        if args.final:
            namespace=folder.resolve().relative_to((ROOT/'evidence').resolve()).parts[0]
            assert namespace in ('round13','round14','round15','round16','round17'), 'Only compatible R13/R14/R15/R16/R17 original protocol receipts are supported'
            artifact_round=namespace.removeprefix('round')
            assert inv['artifact_name']==f"r{artifact_round}-{state['run_id']}-{state['batch']}-gate", 'Use the final artifact, not an early screen snapshot'
        for name,record in inv['files'].items():
            p=(folder/name).resolve();assert p.is_relative_to(folder.resolve())
            assert p.stat().st_size==record['bytes'] and sha(p)==record['sha256']
        entries={e['name']:e for e in state['spec']['entries']};by={};file_id={};environment=None
        for metric in state['metrics']:
            n,b=metric['candidate'],metric['round'];e=entries[n]
            raw=[json.loads(v) for v in (folder/f'round{b}-{n}.jsonl').read_text().splitlines()]
            meta,files=raw[0],[v for v in raw if v['kind']=='file']
            assert meta['corpus']=='corpus-stage1' and len(files)==28 and sum(f['raw_bytes'] for f in files)==15930000
            assert meta['measured_rounds']==11 and meta['warmup_rounds']==1
            env={k:meta[k] for k in ('os','arch','rustc_version','cpu_model','cpu_governor','benchmark_provenance')}
            if environment is None:environment=env
            assert environment==env
            assert meta['methods'][n]['source_sha256']==e['hashes']['parse.rs']==metric['source_sha256']
            axis=[];fid={};timing_signature=[]
            for f in files:
                assert input_ids.setdefault(f['file'],f['sha256'])==f['sha256']
                times={}
                for method in (n,'incumbent'):
                    item=f['methods'][method];reps=[r for r in item['reps'] if r['phase']=='measured']
                    assert item['deterministic'] and not item['errors'] and len(reps)==11 and all(r['total_s']>0 for r in reps)
                    times[method]=statistics.median(r['total_s'] for r in reps)
                axis.append(times[n]/times['incumbent'])
                timing_signature.append((f['sha256'],[(method==n,[r['total_s'] for r in f['methods'][method]['reps']]) for method in (n,'incumbent')]))
                item=f['methods'][n];value=(f['sha256'],item['tokens_sha256'],item['output_sha256'],item['output_bytes'])
                assert identities.setdefault((metric['source_sha256'],f['file']),value)==value
                fid[f['file']]=value
            assert abs(statistics.mean(axis)-metric['time'])<1e-12
            timing_digest=hashlib.sha256(json.dumps(timing_signature,sort_keys=True).encode()).hexdigest()
            owner=timing_owners.setdefault((metric['source_sha256'],timing_digest),state['run_id'])
            assert owner==state['run_id'], 'Identical measured timing vectors cannot be counted as independent CI evidence'
            assert abs(statistics.mean(100*f['methods'][n]['output_bytes']/f['raw_bytes'] for f in files)-metric['size_pct'])<1e-12
            assert (n,b) not in by
            by[n,b]=metric;file_id[n,b]=fid
        for e in entries.values():
            for name,digest in e['hashes'].items():assert sha(ROOT/e['path']/name)==digest
        runs.append({'run_id':state['run_id'],'batch':state['batch'],'commit':ci['headSha'],'status':ci['status'],
            'conclusion':ci['conclusion'],'paired_processes':len(by),'failures':state['failures'],'gates':state['gates'],
            'environment':environment})
        blocks=sorted(b for n,b in by if n=='fast-shadow')
        if blocks:shadows.append({'run_id':state['run_id'],'changes_pct':[100*(by['fast-shadow',b]['time']/by['r3-432-fast3',b]['time']-1) for b in blocks],
            'identical_public_tokens_and_output':all(file_id['fast-shadow',b]==file_id['r3-432-fast3',b] for b in blocks)})
        pcblocks=sorted(b for n,b in by if n=='pc507-shadow')
        if pcblocks:
            assert entries['pc507-shadow']['hashes']==entries['public507']['hashes']
            pc507_shadows.append({'run_id':state['run_id'],'blocks':pcblocks,
                'changes_pct':[100*(by['pc507-shadow',b]['time']/by['public507',b]['time']-1)for b in pcblocks],
                'identical_public_tokens_and_output':all(file_id['pc507-shadow',b]==file_id['public507',b]for b in pcblocks),
                'scope':'Observed identical-source control movement; not a confidence bound or noise correction.'})
        pipeline_blocks=sorted(b for n,b in by if n=='pipeline-shadow')
        if pipeline_blocks:
            assert entries['pipeline-shadow']['hashes']==entries['r10-finder-pipeline-proof']['hashes']
            pipeline_shadows.append({'run_id':state['run_id'],'blocks':pipeline_blocks,
                'changes_pct':[100*(by['pipeline-shadow',b]['time']/by['r10-finder-pipeline-proof',b]['time']-1) for b in pipeline_blocks],
                'identical_public_tokens_and_output':all(file_id['pipeline-shadow',b]==file_id['r10-finder-pipeline-proof',b] for b in pipeline_blocks),
                'scope':'Identical-source D-family control, observed variation only; not a confidence interval or correction factor.'})
        for n,e in entries.items():
            if n.endswith('-shadow') and n[:-7] in entries:
                parent=n[:-7];bb=sorted(b for name,b in by if name==n)
                assert e['hashes']==entries[parent]['hashes']
                family_shadows.append({'run_id':state['run_id'],'shadow':n,'parent':parent,'blocks':bb,
                    'changes_pct':[100*(by[n,b]['time']/by[parent,b]['time']-1)for b in bb],
                    'public_equal':all(file_id[n,b]==file_id[parent,b]for b in bb),
                    'scope':'Identical-source observed drift; not a confidence bound or noise correction'})
            gate=state.get('gates',{}).get(n)
            if e.get('control') and gate and gate.get('accepted'):
                assert gate==json.loads((folder/(n+'-gate.json')).read_bytes())
                assert gate['corpora']==['corpus-stage1']
                assert all(sha(folder/('input-'+n)/f)==v for f,v in e['hashes'].items())
                verified_controls.append({'name':n,'run_id':state['run_id'],'files':e['hashes']})
        for n,e in entries.items():
            if not n.startswith(('r12-', 'r13-','r14-','r15-', 'r16-', 'chat-20261008-')) or e['hashes']['parse.rs'] not in declarations:continue
            blocks=sorted(b for name,b in by if name==n)
            if not blocks:continue
            fid,parent=declarations[e['hashes']['parse.rs']]
            anchor=next(name for name,entry in entries.items() if entry.get('formal_id')==fid)
            assert parent in entries
            fm=formal[fid]['metrics']
            rel=[by[n,b]['time']/by[anchor,b]['time'] for b in blocks]
            sizes=[fm['mean_file_compression_pct']*by[n,b]['size_pct']/by[anchor,b]['size_pct'] for b in blocks]
            assert max(sizes)-min(sizes)<1e-12
            g=groups.setdefault(e['hashes']['parse.rs'],{'candidate':n,'source_sha256':e['hashes']['parse.rs'],
                'formal_anchor_id':fid,'comparison_baseline':parent,'runs':[],'verified_pairs':[]})
            assert g['formal_anchor_id']==fid and g['comparison_baseline']==parent
            g['runs'].append({'run_id':state['run_id'],'name':n,'role_in_batch':'control' if e.get('control') else 'candidate','proof_sha256':e['hashes']['Parse.lean'],'blocks':blocks,
                'relative_to_anchor':rel,'relative_to_parent':[by[n,b]['time']/by[parent,b]['time'] for b in blocks],
                'public_size_pct':by[n,blocks[0]]['size_pct'],'public_size_change_pp':by[n,blocks[0]]['size_pct']-by[parent,blocks[0]]['size_pct'],
                'projected_size_pct':sizes[0], 'public_equal_to_parent':all(file_id[n,b]==file_id[parent,b] for b in blocks)})
            gate=state.get('gates',{}).get(n)
            if gate and gate.get('accepted'):
                assert gate==json.loads((folder/(n+'-gate.json')).read_bytes())
                assert gate['corpora']==['corpus-stage1']
                assert all(sha(folder/('input-'+n)/f)==v for f,v in e['hashes'].items())
                g['verified_pairs'].append({'name':n,'run_id':state['run_id'],'files':e['hashes']})
    assert len(runs)==len({r['run_id'] for r in runs}), 'A CI run may only be counted once'
    candidates=[]
    for g in groups.values():
        rr=g['runs'];assert len(rr)==len({r['run_id'] for r in rr})
        fm=formal[g['formal_anchor_id']]['metrics'];x=fm['balanced_time_ratio']*statistics.mean(statistics.mean(r['relative_to_anchor']) for r in rr);y=rr[0]['projected_size_pct']
        assert all(abs(r['projected_size_pct']-y)<1e-12 for r in rr)
        def scenario(tx,sy):
            return analyze_payability(rows,tx,sy,'453',scorer,pareto_share=policy['pareto_share'],improvement_share=policy['improvement_share'],bounds=bounds)
        g.update(independent_runs=len(rr),blocks=sum(len(r['blocks']) for r in rr),
            relative_time_change_pct_vs_parent=100*(statistics.mean(statistics.mean(r['relative_to_parent']) for r in rr)-1),
            public_size_pct=rr[0]['public_size_pct'],public_size_change_pp=rr[0]['public_size_change_pp'],
            same_family=scenario(x,y),stress=scenario(fm['balanced_time_ratio']*max(v for r in rr for v in r['relative_to_anchor'])*1.01,y+0.01),
            public_equal_to_parent=all(r['public_equal_to_parent'] for r in rr),full_gate_accepted=bool(g['verified_pairs']))
        candidates.append(g)
    result={'status':'COMPLETED_FINAL_ARTIFACTS_RECOMPUTED' if args.final else 'SCREEN_OR_COMPLETED_RECEIPTS_RECOMPUTED',
        'snapshot':context,'capture':str(args.capture),'policy_validation':policy_check,'runs':runs,'candidates':candidates,'fast_shadows':shadows,
        'pipeline_shadows':pipeline_shadows,'pc507_shadows':pc507_shadows,'family_shadows':family_shadows,'verified_controls':verified_controls,
        'paired_processes':sum(r['paired_processes'] for r in runs),
        'field_definitions':{'full_gate_accepted':'At least one exact pair in verified_pairs passed; it does not certify other proof variants with the same Rust.',
                             'candidate_measurements':'A declared exact Rust source retains later standard measurements even when used as a control. These remain fixed-public-data observations, not unseen-data confirmation.',
                             'final_mode':'Final artifacts from completed CI; failed CI is retained as negative evidence and is not labeled successful.'},
        'limits':['Same-family transfer and stress (worst block relative time plus1%, size plus0.01pp) are declared hypotheses, not private guarantees.',
                  'Full public gate is bound to exact source/proof pairs; neither projected geometry nor same-hotkey conditional share is formal admission or realized reward.']}
    args.output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'runs':len(runs),'paired_processes':result['paired_processes'],'candidates':[{'name':g['candidate'],
        'time_change_pct_vs_parent':g['relative_time_change_pct_vs_parent'],'size_change_pp':g['public_size_change_pp'],
        'family_point':g['same_family']['candidate'],'stress_point':g['stress']['candidate'],'gate':g['full_gate_accepted']} for g in candidates]},indent=2))

if __name__=='__main__':main()
