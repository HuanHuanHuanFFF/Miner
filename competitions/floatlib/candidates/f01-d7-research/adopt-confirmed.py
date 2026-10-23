"""Update the four-operation view only from exact discovery and frozen confirmation."""
from pathlib import Path
import argparse,datetime,hashlib,json,statistics,importlib.util

ap=argparse.ArgumentParser()
ap.add_argument('--candidate',required=True)
ap.add_argument('--discovery',type=int,required=True)
ap.add_argument('--confirmation',type=int,required=True)
ap.add_argument('--previous',required=True)
a=ap.parse_args()
if not __debug__: raise RuntimeError('Optimized Python disables legacy assertions; adoption refused')
root=Path.cwd();own=Path(__file__).resolve().parent
def read(p): return json.loads(p.read_bytes())
def write(p,v): p.write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
def digest(p): return hashlib.sha256(p.read_bytes()).hexdigest()
# Re-read original indexed artifacts before any persistent output is written.
spec=importlib.util.spec_from_file_location('adoption_guard',own/'adoption-guard.py')
guard=importlib.util.module_from_spec(spec);spec.loader.exec_module(guard)
selection,verified_packets=guard.verify_adoption(root,own,a.candidate,a.discovery,a.confirmation,a.previous)
status_before=read(root/'competitions/floatlib/coordination/development-status.json')
assert status_before['kernel_sha256']==guard.digest(root/'competitions/floatlib/candidates'/a.previous/'Kernel.lean'), 'Previous must be the currently retained exact source'
now=datetime.datetime.now(datetime.timezone.utc).isoformat()
results=read(own/'public-suite-results.json')
source=root/'competitions/floatlib/candidates'/a.candidate/'Kernel.lean'
h=digest(source);records=[];comparisons=[]
for rid in [a.discovery,a.confirmation]:
    r=next(r for r in results['records'] if r['run']==rid and r['candidate']==a.candidate)
    assert r['full_gate'] and r['kernel_sha256']==h and r['official_commit']=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
    records.append(r)
    comparisons.append(next(r for r in results['comparisons'] if r['run']==rid and r['candidate']==a.candidate and r['baseline_candidate']==a.previous))
# The convenient aggregate must agree with the freshly authenticated raw evidence.
for i,(r,c,p) in enumerate(zip(records,comparisons,verified_packets)):
    v=p['verdicts'][a.candidate]; b=p['verdicts'][a.previous]
    assert r['seed']==p['seed'] and r['suite_sha256']==guard.SUITE_SHA
    assert r['verdict_sha256']==p['evidence']['verdict_sha256'][a.candidate]
    assert r['cell_work']==p['cell_work']
    assert abs(r['ratio']-v['ratio'])<1e-10 and c['parent_sha256']==p['kernel_hashes'][a.previous]
    assert c['kernel_sha256']==h and c['seed']==p['seed']
    assert abs(c['whole_entry_headline_ratio_normalized_candidate_over_parent']-v['ratio']/b['ratio'])<1e-10
    assert read(root/c['requested_plan'])==p['plan']
    for op in ['add','mul','sum','bmm']:
        st=sum(x['submission_ns']*r['cell_work'][n] for n,x in v['classes'].items() if n.startswith(op+':'))
        rt=sum(x['incumbent_ns']*r['cell_work'][n] for n,x in v['classes'].items() if n.startswith(op+':'))
        bt=sum(x['submission_ns']*r['cell_work'][n] for n,x in b['classes'].items() if n.startswith(op+':'))
        br=sum(x['incumbent_ns']*r['cell_work'][n] for n,x in b['classes'].items() if n.startswith(op+':'))
        assert r['cell_work']==b.get('cell_work',r['cell_work'])
        assert r['operation_total_ns'][op]==st and r['operation_reference_total_ns'][op]==rt
        assert c['operations_reference_normalized_candidate_over_parent'][op]==(st/rt)/(bt/br)
    assert r['classes']==v['classes'] and r['verifier_fingerprint']==v['verifier_fingerprint']
    assert r['time_share_percent']=={op:t/sum(r['operation_total_ns'].values())*100 for op,t in r['operation_total_ns'].items()}
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
view={'as_of_utc':now,'candidate':a.candidate,'kernel_sha256':h,'full_gate_runs':[a.discovery,a.confirmation],'public_results':(own/'public-suite-results.json').relative_to(root).as_posix(),'champion':{'submission':champ['submission'],'digest':detail['digest'],'official_normalized_self_time':1.0,'candidate_over_champion_time':'UNKNOWN','official_cumulative_speedup_vs_shipped':champ['speedup_vs_shipped'],'official_speedup_basis':champ.get('speedup_basis'),'cumulative_scope':'Official API hash-linked estimate on its declared benchmark basis; a changed benchmark requires a measured anchor. Not a matched comparison to our public-v2 candidate.','snapshot':competition['current_snapshot_id'],'receipts':(official/'receipts.json').relative_to(root).as_posix()},'public_speedup':{'whole_range':whole,'operations':speed},'previous_package':{'candidate':a.previous,'whole_normalized_ratios':[r['whole_entry_headline_ratio_normalized_candidate_over_parent'] for r in comparisons],'bmm_normalized_ratios':[r['operations_reference_normalized_candidate_over_parent']['bmm'] for r in comparisons]},'formal_submission':'NOT_SUBMITTED'}
view['local_selection_guard']=selection
write(own/'multiplier-comparison.json',view)
sp=root/'competitions/floatlib/coordination/development-status.json';s=read(sp)
old={'candidate':s['candidate'],'kernel_sha256':s['kernel_sha256'],'performance':s['performance']}
if s['kernel_sha256']!=h:s.setdefault('r7_adoptions',[]).append({'adopted_at_utc':now,'previous':old,'new_candidate':a.candidate,'new_sha256':h,'discovery':a.discovery,'confirmation':a.confirmation})
s.update(updated_at_utc=now,candidate=str(source.parent.relative_to(root)).replace('\\','/'),kernel=source.relative_to(root).as_posix(),kernel_sha256=h,kernel_bytes=source.stat().st_size,manifest=source.with_name('manifest.json').relative_to(root).as_posix(),proof_status='PASS_FULL_CURRENT_PUBLIC_SUITE_DISCOVERY_AND_FROZEN_NEW_SEED_RUNNER_CONFIRMATION')
s['performance']={'local_selection_guard':selection,'protocol':results['protocol']+'; public shipped reference','full_gate_runs':[a.discovery,a.confirmation],'seeds':[r['seed'] for r in records],'ratio_vs_shipped':[r['ratio'] for r in records],'kernels_vs_shipped':ratios,'confirmation_phase':['discovery','frozen_new_seed_new_runner'],'previous_package':a.previous,'time_over_previous_package_reference_normalized':[r['whole_entry_headline_ratio_normalized_candidate_over_parent'] for r in comparisons],'evidence':view['public_results']}
s['current_champion_comparison'].update(submission=champ['submission'],source_digest=detail['digest'],policy_snapshot=competition['current_snapshot_id'],queried_at_utc=snapshot['queried_at_utc'],candidate=a.candidate,direct_paired_ratio='UNKNOWN')
s['current_multiplier_view'].update(official_champion=champ['submission'],snapshot=competition['current_snapshot_id'],candidate=a.candidate,candidate_current_public_suite_speedup_range=whole,champion_official_historical_speedup_vs_shipped=champ['speedup_vs_shipped'],champion_official_speedup_basis=champ.get('speedup_basis'))
s['optimization_priority'].update(basis_applicability='Exact '+a.candidate+' discovery and frozen new-seed/new-runner complete gates',current_public_suite_share_percent={op:speed[op]['time_share_median_percent'] for op in ops},research_authorization='R7 ten-hour collaboration '+s['collaboration']['start_utc']+' through '+s['collaboration']['deadline_utc'])
continuation=s.get('authorized_validation_continuation')
if continuation:
    s['optimization_priority']['research_authorization']='Explicitly authorized validation continuation '+continuation['started_at_utc']
window_finished=bool(s['collaboration'].get('window_completed_at_utc'))
s['selection_scope']='Retain exact '+h+' after discovery and frozen confirmation; '+('ten-hour research window ended' if window_finished else 'ten-hour champion research remains active')
if continuation:
    s['selection_scope']='Retain exact '+h+' after local guarded discovery and frozen confirmation; authorized validation continuation'
    s['research_resources']='Authorized validation continuation: '+continuation['state']+'; '+('recorded CI is active' if continuation.get('active_ci') else 'no active CI recorded')
elif window_finished:
    s['research_resources']=('R7 research window ended; already-started CI is collecting terminal results' if s.get('active_jobs') else 'R7 research window ended; all prior CI terminal and collected, no new CI queued or running. Frozen new integrations still await their own authorized verification.')
elif s.get('active_jobs'):
    s['research_resources']='R7 Astra research active; already-started CI continues to terminal results; local analysis and evidence recovery continue'
elif s['collaboration'].get('publication',{}).get('state')=='AWAITING_EXPLICIT_PUBLIC_PUSH_AUTHORIZATION':
    s['research_resources']='R7 local/source research active; all prior CI terminal and collected, no new CI queued or running. Explicit public-push authorization remains pending after automatic approval rejection.'
else:
    s['research_resources']='R7 local/source research active; no CI queued or running'
s['remaining']=['Current-champion replacement unachieved',('Continue explicitly authorized bounded verification' if continuation else 'Frozen new integrations await separately authorized original gates' if window_finished else 'Continue authorized ten-hour research through '+s['collaboration']['deadline_utc']),'Formal submission, registration and funds outside scope']
s['current_protocol']['scope']='Current original paid private suite; current champion'+str(champ['submission'])+' verification_current=true and26cell report verified; public-v2 SHA unchanged'
write(sp,s)
labels={'add':'加法 add','mul':'乘法 mul','sum':'求和 sum','bmm':'矩阵乘法 bmm'}
official_multiplier=champ.get('speedup_vs_shipped')
official_basis=champ.get('speedup_basis')
official_label=(f'{official_multiplier:.2f}×（{official_basis or "基准未知"}）'
                if isinstance(official_multiplier,(int,float)) else '待官方校准')
t=datetime.datetime.fromisoformat(snapshot['queried_at_utc']).astimezone(datetime.timezone(datetime.timedelta(hours=8))).strftime('%Y-%m-%d %H:%M')
lines=['# FloatLib 冲冠看板','',f"冠军 [#{champ['submission']}](https://conjectures.io/v1/competitions/floatlib/submissions/{champ['submission']})｜官方倍率 **{official_label}**｜{t}核对。",'',f'当前保留[{a.candidate}]({source.relative_to(root).as_posix()})，整包对公开原版 **{whole[0]:.2f}–{whole[1]:.2f}×**。','','| 运算 | 冠军耗时基准 | 我方 / 冠军耗时 | 我方对公开原版加速 | 我方耗时占比 |','| --- | ---: | ---: | ---: | ---: |']
for op in ops:
    lo,hi=speed[op]['speedup_range'];share=speed[op]['time_share_median_percent'];lines.append(f'| {labels[op]} | 1.00× | 待正式评测 | {lo:.2f}–{hi:.2f}× | {share:.1f}% |')
g=sorted((1-r['whole_entry_headline_ratio_normalized_candidate_over_parent'])*100 for r in comparisons)
lines+=['',f"**结论：尚无取代#{champ['submission']}的已验方案；组合包相对上一保留版本再降耗{g[0]:.0f}%–{g[1]:.0f}%。** [数据](competitions/floatlib/candidates/f01-d7-research/multiplier-comparison.json)",'']
(root/'dashboard.md').write_text('\n'.join(lines),encoding='utf-8')
print(json.dumps({'candidate':a.candidate,'sha256':h,'whole_public_speedup':whole,'shares':s['optimization_priority']['current_public_suite_share_percent']}))
