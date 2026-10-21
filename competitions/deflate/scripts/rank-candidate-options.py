"""Rank recent candidates by best observed block, retaining observed variability."""
from pathlib import Path
import argparse,hashlib,json,statistics
from round10_payability import load_flat_rows,load_official_scorer,validate_policy_for_replay

ROOT=Path(__file__).resolve().parents[1]
def read(p):return json.loads(p.read_bytes())
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--capture',type=Path,required=True);ap.add_argument('--output',type=Path,required=True);args=ap.parse_args()
    comp,ctx,rows=load_flat_rows(args.capture);sc=load_official_scorer();policy=validate_policy_for_replay(comp['policy'],rows,sc);formal={r['id']:r for r in rows}
    front=[sc.Point(r['id'],r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])for r in rows if(r.get('score')or{}).get('on_frontier')]
    def share(x,y):
        if x>comp['policy']['max_balanced_time_ratio'] or y>comp['policy']['max_mean_file_compression_pct']:return 0.0
        return 100*sc.local_global_improvement_space_log_weights(sc.pareto_front(front+[sc.Point('__option__',x,y)])).get('__option__',0)
    groups={};skipped=[];seen=set();hashcache={};input_ids={}
    def digest(p):
        k=str(p)
        if k not in hashcache:hashcache[k]=sha(p)
        return hashcache[k]
    for round_no in range(10,17):
        for path in sorted((ROOT/f'evidence/round{round_no}').glob('*/*/gate/state.json')):
            folder=path.parent
            if not(folder/'ci-run.json').exists()or not(folder/'raw-artifact-files.json').exists():continue
            ci=read(folder/'ci-run.json');state=read(path)
            if ci['status']!='completed':continue
            rid=state['run_id'];assert str(ci['databaseId'])==rid and ci['headSha']==state['git_sha']
            inv=read(folder/'raw-artifact-files.json')['files'];assert digest(path)==inv['state.json']['sha256']
            entries={e['name']:e for e in state['spec']['entries']};metrics={(m['candidate'],m['round']):m for m in state['metrics']}
            valid={}
            def checked(n,b):
                if(n,b)in valid:return valid[n,b]
                p=folder/f'round{b}-{n}.jsonl';assert digest(p)==inv[p.name]['sha256'];raw=[json.loads(s)for s in p.read_text().splitlines()];fs=[r for r in raw if r['kind']=='file'];meta=raw[0]
                assert len(fs)==28 and sum(f['raw_bytes']for f in fs)==15930000 and meta['measured_rounds']==11
                assert meta['methods'][n]['source_sha256']==entries[n]['hashes']['parse.rs']
                ratios=[]
                for f in fs:
                    assert input_ids.setdefault(f['file'],f['sha256'])==f['sha256'], 'Public corpus changed across compared runs'
                    times=[]
                    for k in(n,'incumbent'):
                        m=f['methods'][k];assert m['deterministic']and not m['errors'];v=[r['total_s']for r in m['reps']if r['phase']=='measured'];assert len(v)==11 and min(v)>0;times.append(statistics.median(v))
                    ratios.append(times[0]/times[1])
                x=statistics.mean(ratios);y=statistics.mean(100*f['methods'][n]['output_bytes']/f['raw_bytes']for f in fs)
                assert abs(x-metrics[n,b]['time'])<1e-12 and abs(y-metrics[n,b]['size_pct'])<1e-12
                valid[n,b]=(x,y);return x,y
            for n,e in entries.items():
                source=ROOT/e['path'];name=source.name
                if not str(e['path']).startswith('candidates/r') or not any(name.startswith(f'r{i}-')for i in range(10,17)):continue
                anchor=e.get('anchor');fid=entries.get(anchor,{}).get('formal_id')
                if not fid or str(fid)not in formal:
                    skipped.append({'run':rid,'candidate':n,'reason':'No explicit available formal anchor'});continue
                h=e['hashes']['parse.rs'];assert digest(source/'parse.rs')==h
                key=(h,str(fid));g=groups.setdefault(key,{'candidate':name,'aliases':set(),'source_sha256':h,'anchor_id':str(fid),'observations':[],'verified_pairs':[]});g['aliases'].add(name)
                cert=source/'VERIFICATION.json'
                if cert.exists():
                    v=read(cert)
                    if v.get('status') in ('VERIFIED_EXACT_PUBLIC_FULL_GATE','VERIFIED_FULL_PUBLIC_STAGE1_GATE') and v['files']['parse.rs']==h and all(digest(source/f)==z for f,z in v['files'].items()):
                        gate=ROOT/v['receipt']/v.get('gate_verdict',name+'-gate.json')
                        assert read(gate)['accepted'] is True, 'Certificate must agree with original gate verdict'
                        if name not in g['verified_pairs']:g['verified_pairs'].append(name)
                for nn,b in metrics:
                    if nn!=n or(anchor,b)not in metrics:continue
                    identity=(rid,b,h,str(fid))
                    if identity in seen:continue
                    seen.add(identity);x,y=checked(n,b);ax,ay=checked(anchor,b);fm=formal[str(fid)]['metrics'];tx=fm['balanced_time_ratio']*x/ax;sy=fm['mean_file_compression_pct']*y/ay
                    g['observations'].append({'run_id':rid,'batch':state['batch'],'block':b,'time':tx,'size_pct':sy,'share_pct':share(tx,sy),'receipt':folder.relative_to(ROOT).as_posix(),'role':'control'if e.get('control')else'candidate'})
    result=[]
    for g in groups.values():
        obs=g['observations']
        if not obs:continue
        g['aliases']=sorted(g['aliases']);g['verified_pairs']=sorted(g['verified_pairs'])
        if g['verified_pairs']:g['candidate']=g['verified_pairs'][0]
        v=sorted(o['share_pct']for o in obs);ys=[o['size_pct']for o in obs];assert max(ys)-min(ys)<1e-10
        run_ids=sorted(set(o['run_id']for o in obs));means=[statistics.mean(o['time']for o in obs if o['run_id']==rid)for rid in run_ids]
        g.update(best_pct=max(v),median_block_pct=statistics.median(v),min_pct=min(v),p25_pct=statistics.quantiles(v,n=4,method='inclusive')[0]if len(v)>1 else v[0],p75_pct=statistics.quantiles(v,n=4,method='inclusive')[2]if len(v)>1 else v[0],pooled_center_pct=share(statistics.mean(means),ys[0]),runs=len(run_ids),blocks=len(v),positive_blocks=sum(z>0 for z in v),blocks_ge1pct=sum(z>=1 for z in v),blocks_ge1_7pct=sum(z>=1.7 for z in v),best_observation=max(obs,key=lambda o:o['share_pct']))
        g['already_submitted_as_573']=(g['source_sha256']=='80a7c705d113694eea83f325b8387efb9d97110fba95fdd12b47f0d4eccc33cb')
        result.append(g)
    result.sort(key=lambda g:g['best_pct'],reverse=True)
    output={'snapshot':ctx,'policy_validation':policy,'scope':'Collected final standard R10-R16 receipts with explicit same-family formal anchors. All raw reps verified; later control roles retained; exact Rust aliases deduplicated per run/block. Peaks are observed-block conditional projections on current frontier, not formal scores or expected income. Quartiles summarize observed blocks, not probabilities. No stress adjustment applied. Existing573 would be a duplicate point; shown separately as actual submitted result.','candidates':result,'skipped':skipped,'formal573':formal.get('573')}
    args.output.write_bytes((json.dumps(output,indent=2)+'\n').encode())
    options=[g for g in result if not g['already_submitted_as_573']]
    lines=[f"候选最高已测块投影排序；官方快照{ctx['snapshot_id']}，计算时间{ctx['computed_at']}，freshness={ctx['freshness']}。",
           '覆盖R10-R16标准测量；不添加压力偏移。最高/范围/中位数均来自已收齐块的条件投影，不是正式分红。',
           '排名\t候选\t最高%\t最低%\t块中位数%\t达到1%的块\t运行/块\t完整公开gate']
    for i,g in enumerate(options,1):
        lines.append(f"{i}\t{g['candidate']}\t{g['best_pct']:.6f}\t{g['min_pct']:.6f}\t{g['median_block_pct']:.6f}\t{g['blocks_ge1pct']}/{g['blocks']}\t{g['runs']}/{g['blocks']}\t{'已通过'if g['verified_pairs']else'未核实通过'}")
    lines+=['','少量块的中位数不代表稳定水平；达标块比例不是未来上榜概率。完整原始回执定位及逐块结果见同名JSON。',
            '已有#573实际可支付份额：'+str(formal['573']['score']['payable_weight']*100)+'%；已提交版本不按新增候选重复计算。']
    args.output.with_suffix('.txt').write_bytes(('\n'.join(lines)+'\n').encode())
    print(json.dumps({'snapshot':ctx,'candidates':len(result),'skipped':len(skipped),'ranking':[{k:g[k]for k in('candidate','best_pct','median_block_pct','p25_pct','p75_pct','min_pct','pooled_center_pct','runs','blocks','positive_blocks','blocks_ge1pct','blocks_ge1_7pct','verified_pairs')}for g in result if g['best_pct']>0]},indent=2))

if __name__=='__main__':main()
