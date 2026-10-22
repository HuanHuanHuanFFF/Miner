"""Update the four-operation view only from exact discovery and frozen confirmation."""
from pathlib import Path
import argparse,datetime,hashlib,json,statistics

ap=argparse.ArgumentParser()
ap.add_argument('--candidate',required=True)
ap.add_argument('--discovery',type=int,required=True)
ap.add_argument('--confirmation',type=int,required=True)
ap.add_argument('--previous',required=True)
a=ap.parse_args()
root=Path.cwd();own=Path(__file__).resolve().parent
def read(p): return json.loads(p.read_bytes())
def write(p,v): p.write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
def digest(p): return hashlib.sha256(p.read_bytes()).hexdigest()
now=datetime.datetime.now(datetime.timezone.utc).isoformat()
results=read(own/'public-suite-results.json')
source=root/'competitions/floatlib/candidates'/a.candidate/'Kernel.lean'
h=digest(source);records=[];comparisons=[]
for rid in [a.discovery,a.confirmation]:
    r=next(r for r in results['records'] if r['run']==rid and r['candidate']==a.candidate)
    assert r['full_gate'] and r['kernel_sha256']==h and r['official_commit']=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
    records.append(r)
    comparisons.append(next(r for r in results['comparisons'] if r['run']==rid and r['candidate']==a.candidate and r['baseline_candidate']==a.previous))
assert records[0]['seed']!=records[1]['seed'] and a.discovery!=a.confirmation
frozen=read(root/comparisons[1]['requested_plan'])
assert any(r['candidate']==a.candidate and r['sha256']==h and r['prior_discovery_run']==a.discovery for r in frozen['confirmation_candidates'])
assert not any(r.get('capture_codegen',False) for r in frozen['candidates']), 'Confirmation cannot use any optional observer'
snapshot=read(own/'current-official-snapshot.json');official=own/snapshot['directory']
assert snapshot['official_commit']==records[0]['official_commit'], 'Upstream changed: review the new protocol before a current adoption'
receipt=read(official/'receipts.json')
for info in receipt['responses'].values():
    if 'file' in info:
        assert digest(official/info['file'])==info['sha256']
        assert (official/info['file']).stat().st_size==info['bytes']
champ=next(r for r in read(official/'champions.raw') if r['current'])
detail=read(official/'champion-detail.raw');competition=read(official/'competition.raw')
assert detail['id']==champ['submission']==snapshot['champion'] and detail['verification_current'] and len(detail['classes'])==26
ops=['add','mul','sum','bmm']
ratios=[{op:r['operation_total_ns'][op]/r['operation_reference_total_ns'][op] for op in ops} for r in records]
speed={op:{'speedup_range':sorted(1/r[op] for r in ratios),'time_share_median_percent':statistics.median(r['time_share_percent'][op] for r in records)} for op in ops}
whole=sorted(1/r['ratio'] for r in records)
view={'as_of_utc':now,'candidate':a.candidate,'kernel_sha256':h,'full_gate_runs':[a.discovery,a.confirmation],'public_results':(own/'public-suite-results.json').relative_to(root).as_posix(),'champion':{'submission':champ['submission'],'digest':detail['digest'],'official_normalized_self_time':1.0,'candidate_over_champion_time':'UNKNOWN','official_cumulative_speedup_vs_shipped':champ['speedup_vs_shipped'],'cumulative_scope':'Cross-suite historical chain; not a matched public-v2 speedup','snapshot':competition['current_snapshot_id'],'receipts':(official/'receipts.json').relative_to(root).as_posix()},'public_speedup':{'whole_range':whole,'operations':speed},'previous_package':{'candidate':a.previous,'whole_normalized_ratios':[r['whole_entry_headline_ratio_normalized_candidate_over_parent'] for r in comparisons],'bmm_normalized_ratios':[r['operations_reference_normalized_candidate_over_parent']['bmm'] for r in comparisons]},'formal_submission':'NOT_SUBMITTED'}
write(own/'multiplier-comparison.json',view)
sp=root/'competitions/floatlib/coordination/development-status.json';s=read(sp)
old={'candidate':s['candidate'],'kernel_sha256':s['kernel_sha256'],'performance':s['performance']}
if s['kernel_sha256']!=h:s.setdefault('r7_adoptions',[]).append({'adopted_at_utc':now,'previous':old,'new_candidate':a.candidate,'new_sha256':h,'discovery':a.discovery,'confirmation':a.confirmation})
s.update(updated_at_utc=now,candidate=str(source.parent.relative_to(root)).replace('\\','/'),kernel=source.relative_to(root).as_posix(),kernel_sha256=h,kernel_bytes=source.stat().st_size,manifest=source.with_name('manifest.json').relative_to(root).as_posix(),proof_status='PASS_FULL_CURRENT_PUBLIC_SUITE_DISCOVERY_AND_FROZEN_NEW_SEED_RUNNER_CONFIRMATION')
s['performance']={'protocol':results['protocol']+'; public shipped reference','full_gate_runs':[a.discovery,a.confirmation],'seeds':[r['seed'] for r in records],'ratio_vs_shipped':[r['ratio'] for r in records],'kernels_vs_shipped':ratios,'confirmation_phase':['discovery','frozen_new_seed_new_runner'],'previous_package':a.previous,'time_over_previous_package_reference_normalized':[r['whole_entry_headline_ratio_normalized_candidate_over_parent'] for r in comparisons],'evidence':view['public_results']}
s['current_champion_comparison'].update(submission=champ['submission'],source_digest=detail['digest'],policy_snapshot=competition['current_snapshot_id'],queried_at_utc=snapshot['queried_at_utc'],candidate=a.candidate,direct_paired_ratio='UNKNOWN')
s['current_multiplier_view'].update(official_champion=champ['submission'],snapshot=competition['current_snapshot_id'],candidate=a.candidate,candidate_current_public_suite_speedup_range=whole,champion_official_historical_speedup_vs_shipped=champ['speedup_vs_shipped'])
s['optimization_priority'].update(basis_applicability='Exact '+a.candidate+' discovery and frozen new-seed/new-runner complete gates',current_public_suite_share_percent={op:speed[op]['time_share_median_percent'] for op in ops},research_authorization='R7 ten-hour collaboration '+s['collaboration']['start_utc']+' through '+s['collaboration']['deadline_utc'])
s['selection_scope']='Retain exact '+h+' after discovery and frozen confirmation; ten-hour champion research remains active'
s['research_resources']='R7 Astra research active; latest CI state is in active_jobs; local analysis and evidence recovery continue'
s['remaining']=['Current-champion replacement unachieved','Continue authorized ten-hour research through '+s['collaboration']['deadline_utc'],'Formal submission, registration and funds outside scope']
s['current_protocol']['scope']='Current original paid private suite; current champion'+str(champ['submission'])+' verification_current=true and26cell report verified; public-v2 SHA unchanged'
write(sp,s)
labels={'add':'加法 add','mul':'乘法 mul','sum':'求和 sum','bmm':'矩阵乘法 bmm'}
t=datetime.datetime.fromisoformat(snapshot['queried_at_utc']).astimezone(datetime.timezone(datetime.timedelta(hours=8))).strftime('%Y-%m-%d %H:%M')
lines=['# FloatLib 冲冠看板','',f"冠军 [#{champ['submission']}](https://conjectures.io/v1/competitions/floatlib/submissions/{champ['submission']})｜{t}核对。**我方/冠军耗时越低越好；公开原版/我方加速越高越好。**",'',f'当前保留[直接点积＋非NaN完整包]({source.relative_to(root).as_posix()})，两轮新版公开套件完整通过。','','| 运算 | 冠军耗时基准 | 我方 / 冠军耗时 | 我方对公开原版加速 | 我方耗时占比 |','| --- | ---: | ---: | ---: | ---: |']
for op in ops:
    lo,hi=speed[op]['speedup_range'];share=speed[op]['time_share_median_percent'];lines.append(f'| {labels[op]} | 1.00× | 待正式评测 | {lo:.2f}–{hi:.2f}× | {share:.1f}% |')
g=sorted((1-r['whole_entry_headline_ratio_normalized_candidate_over_parent'])*100 for r in comparisons)
lines+=['',f"整包我方 **{whole[0]:.2f}–{whole[1]:.2f}×**；冠军官方累计 **{champ['speedup_vs_shipped']:.2f}×** 含跨套件历史，不能相除算差距。[数据](competitions/floatlib/candidates/f01-d7-research/multiplier-comparison.json)",'',f"**结论：尚无取代#{champ['submission']}的已验方案；组合包相对上一保留版本再降耗{g[0]:.0f}%–{g[1]:.0f}%，继续冲冠。**",'']
(root/'dashboard.md').write_text('\n'.join(lines),encoding='utf-8')
print(json.dumps({'candidate':a.candidate,'sha256':h,'whole_public_speedup':whole,'shares':s['optimization_priority']['current_public_suite_share_percent']}))
