"""Build role-separated delivery from audited raw analysis; never invent missing gates."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, itertools, json, statistics as st
import importlib

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/extension90m'
CONFIG = [
 ('C2', 'r26-c-658-fold-tail-proof1', '末尾必要过滤', '补测旧Rust'),
 ('C3', 'r26-c-658-deferred-extension-proof3', '延迟完整扩展', '补测旧Rust'),
 ('D1', 'r26-d-658-selective-depth-proof1', '两起点分配深搜', '新增Rust'),
 ('D2', 'r26-d-658-once-budget-proof1', '深搜预算只转交一次', '新增Rust'),
 ('E1', 'r26-e-658-short-same-proof3', '短匹配直接比较', '新增Rust'),
 ('E2', 'r26-e-658-short-tail-proof2', 'C2与E1受控组合', '新增Rust组合'),
]

def read(p): return json.loads(p.read_bytes())
def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
def save(p, obj): p.write_bytes((json.dumps(obj, ensure_ascii=False, indent=2)+'\n').encode())

def span(values, suffix=''):
    lo,hi=values
    return f'{lo:.9f}{suffix}' if lo==hi else f'{lo:.9f}–{hi:.9f}{suffix}'

def render(result, target):
    cs=result['candidates'];ct=result['counts'];snap=result['snapshot']
    lines=['# 第26轮追加90分钟：所有选中机制先实测，再判断晋升','',
      '固定北京时间窗口：**2026-10-12 22:55:17–2026-10-13 00:25:17**。准备、排队、运行、修补、复测和报告都计入本窗；旧窗口不改写。执行规则见 [AGENTS.md](../../AGENTS.md)。','',
      '**稳定份额目标未完成；没有推荐正式提交的新候选。** 公共预测为条件估算，未正式上传、注册、签名或支出。', '',
      f'本窗测试 **6个不同Rust版本**：2个旧版本补原协议计时、4个新版本（含1个受控组合）。每种都至少一次有效原协议测试后才决定晋升或暂停。共{ct["ci"]}个手动作业：{ct["ci_success"]}成功、{ct["ci_failure"]}失败、{ct["ci_cancelled"]}到既定超时取消；{ct["paired_processes"]}个原协议配对进程。', '',
      '[固定预算](../../evidence/round26/extension90m/budget.json) · [逐圈记录](../../evidence/round26/extension90m/state.md) · [完整机器交付](../../evidence/round26/extension90m/delivery.json) · [独立评分审计](../../evidence/round26/extension90m/score-audit/)','',
      '## 最新快照下的条件份额与两轴','',
      f'快照 **{snap["snapshot_id"]}**，官方计算UTC {snap.get("computed_at","UNKNOWN")}，API freshness={snap.get("freshness","UNKNOWN")}。查询时间、原始响应及SHA见本窗最终捕获回执。主/副本、校准和runner分开统计。主校准为同runner #658；两轴越低越好。','',
      '| 候选 | 测量范围 | 份额最低／中位／最高 | 零份额 | 时间轴X范围（倍） | 大小轴Y |',
      '|---|---|---:|---:|---:|---:|']
    for c in cs:
        z=c['main']['primary'];stage=f'{z["runner_count"]} runner／{z["n"]}主块'
        lines.append(f'| {c["label"]} {c["mechanism"]} | {stage} | {z["minimum_pct"]:.6f}／{z["median_pct"]:.6f}／{z["maximum_pct"]:.6f}% | {z["zero_count"]}/{z["n"]} | {span(z["projected_x_range"])} | {span(z["projected_y_range"],"%")} |')
    lines += ['', 'C2/C3/E1/E2使用冻结后的独立Rust复测，D1/D2仅发现块。独立性的范围绑定实际Lean哈希，见下表。以上未将副本或影子校准并入主样本；样本达标次数不是正式成功概率。所有候选的5%／10%达标次数详见机器交付。', '',
      '| 候选 | 影子参照份额最低／中位／最高 | 零次数 | 影子校准X范围 | 影子校准Y |', '|---|---:|---:|---:|---:|']
    for c in cs:
        z=c['main']['shadow']
        lines.append(f'| {c["label"]} | {z["minimum_pct"]:.6f}／{z["median_pct"]:.6f}／{z["maximum_pct"]:.6f}% | {z["zero_count"]}/{z["n"]} | {span(z["projected_x_range"])} | {span(z["projected_y_range"],"%")} |')
    lines += ['', '同源码副本的逐块结果、零次数及相对时间差完整保存在机器交付和原始分析中，不能因它们推翻主测量而删除。以下是公共实测坐标，未直接当作正式榜单坐标使用：', '',
      '| 候选 | 公共时间轴X范围 | 公共大小轴Y | 正式可支付份额 |', '|---|---:|---:|---|']
    for c in cs:
        z=c['main']['primary'];lines.append(f'| {c["label"]} | {span(z["public_x_range"])} | {span(z["public_y_range"],"%")} | UNKNOWN，未提交 |')
    lines += ['', '## 精确文件与验收','', '| 候选 | 最终保存目录 | 完整gate | 此精确pair的新独立主块 |', '|---|---|---|---:|']
    for c in cs:
        lines.append(f'| {c["label"]} | [{c["name"]}](../../{c["path"]}) | {c["gate_status"]} | {c["final_pair_independent_main_blocks"]} |')
    lines += ['', 'C3/E1的性能反例来自同Rust的旧证明配对；修补Lean后的新pair若没有独立计时，不能把旧计时重标为最终确认。D1/D2证明草稿只作下一轮起点。目录带proof不代表验收通过。', '', '| 候选 | Rust SHA-256 | Lean SHA-256 |', '|---|---|---|']
    for c in cs:lines.append(f'| {c["label"]} | {c["hashes"]["parse.rs"]} | {c["hashes"]["Parse.lean"]} |')
    lines += ['', '## 反馈与保留边界','',
      '- C2/C3补实测后出现过小份额；冻结复测保留归零，未仅凭计数覆盖或单次峰值作结论。C2完整gate提供一个已验证的同字节改动起点。',
      '- D1把深搜放到浅比较之后；D2限制预算只转交一次。D2未恢复速度，实际慢主要集中在改动域，暂停此具体改法；不宣布两起点搜索永久无效。',
      '- E1首发现四种主/副本及参照视图均为正，但独立确认回落。真实提取产生12个额外循环副本，原证明不自动覆盖；随后按原版日志逐次修补。',
      '- E2在同runner同时测量组合、C2及E1组件，未相加组件收益。正式结论以冻结确认和独立gate为准。', '',
      '## 联合加入','',
      'C2/C3/E1/E2的校准大小轴相同；同一组合中较快者会支配较慢者，独立份额不能直接相加。以下将实际主校准坐标做交叉组合后重新计算前沿和归一化，保留全部情况；它是条件情景，不是配对的联合确认，也不是概率。', '',
      '| 组合 | 已观测坐标组合数 | 联合总份额范围 |', '|---|---:|---:|']
    for j in result['joint']:lines.append(f'| {" + ".join(j["labels"])} | {j["scenario_count"]} | {span(j["total_range_pct"],"%")} |')
    lines += ['', '逐情景的各候选单独／联合份额及实际两轴见机器交付joint字段。未将假设的中心坐标份额当作期望收益。', '',
      '## 消耗、验证与后续','',
      f'19个作业按既定结束规则收齐，已记录runner job wall合计 **{ct["job_seconds"]:.0f}秒（{ct["job_seconds"]/60:.2f}分钟）**；这不是GitHub计费。账户真实用量见usage-start/mid/close，变化属于共享账户，不能全归于本轮。精确模型tokens、模型费用和CI账单UNKNOWN。重置卡兑换0，购买0。', '',
      '**VERIFIED**：原始逐文件11次总时间、输入/输出身份、精确文件哈希、已收齐的CI回执以及通过的完整gate。**INFERRED**：基于当前快照和同族参照的公共两轴投影。**UNKNOWN**：私有集表现、正式准入与可支付份额、钱包到账、未完成的新pair确认。', '',
      '最高价值后续见[有界路线评审](../../evidence/round26/extension90m/route-d/final-search-review.md)：先区分同源码跨进程波动与真实收益，再检查实际token/encoder工作量；不以微参数重试或挑选峰值宣称成功。', '']
    target.write_bytes(('\n'.join(lines)).encode())

def stats(rows):
    if not rows: return None
    vs = [r['single_pool_share_pct'] for r in rows]
    return dict(n=len(rows), runner_count=len({r['run_id'] for r in rows}),
        minimum_pct=min(vs), median_pct=st.median(vs), maximum_pct=max(vs),
        zero_count=sum(v == 0 for v in vs), at_least_5_count=sum(v >= 5 for v in vs),
        at_least_10_count=sum(v >= 10 for v in vs),
        projected_x_range=[min(r['projected_time'] for r in rows),max(r['projected_time'] for r in rows)],
        projected_y_range=[min(r['projected_size_pct'] for r in rows),max(r['projected_size_pct'] for r in rows)],
        public_x_range=[min(r['public_time'] for r in rows),max(r['public_time'] for r in rows)],
        public_y_range=[min(r['public_size_pct'] for r in rows),max(r['public_size_pct'] for r in rows)])

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--analysis',type=Path,required=True)
    ap.add_argument('--capture',type=Path,required=True);ap.add_argument('--rules',type=Path,required=True)
    ap.add_argument('--stem',default='delivery');a=ap.parse_args()
    analysis=read(a.analysis); by={g['rust_sha256']:g for g in analysis['candidates']}
    candidates=[]; selected={}
    for label,name,mechanism,origin in CONFIG:
        folder=ROOT/'candidates'/name
        hashes={f:sha(folder/f) for f in ['parse.rs','Parse.lean']}
        g=by[hashes['parse.rs']]
        mainrows=[o for o in g['observations'] if o['entry_role']=='candidate']
        fresh=[o for o in mainrows if o['role']=='independent_confirmation']
        rows=fresh or mainrows; runids={o['run_id'] for o in rows}
        cert=read(folder/'VERIFICATION.json') if (folder/'VERIFICATION.json').exists() else None
        if cert: assert cert['files']==hashes and cert['status']=='VERIFIED_EXACT_ORIGINAL_PUBLIC_GATE_PASSED'
        copies=[o for o in g['observations'] if o['run_id'] in runids and o['entry_role']=='control' and o['entry_name'].endswith('-shadow')]
        pairrows=[o for o in fresh if o['proof_sha256']==hashes['Parse.lean']]
        selected[label]=[o for o in rows if o['calibration']=='primary']
        candidates.append(dict(label=label,name=name,mechanism=mechanism,origin=origin,
            path=folder.relative_to(ROOT).as_posix(),hashes=hashes,
            gate_status=cert['status'] if cert else read(folder/'manifest.json').get('proof_status','UNKNOWN'),
            gate_certificate=cert,measurement_scope='independent Rust measurements' if fresh else 'one discovery runner',
            final_pair_independent_main_blocks=len([o for o in pairrows if o['calibration']=='primary']),
            final_pair_gate_passed=bool(cert),
            main={cal:stats([o for o in rows if o['calibration']==cal]) for cal in ['primary','shadow']},
            copies={cal:stats([o for o in copies if o['calibration']==cal]) for cal in ['primary','shadow']},
            observations=[{k:o[k] for k in ['run_id','block','role','entry_name','entry_role','calibration','proof_sha256','projected_time','projected_size_pct','public_time','public_size_pct','single_pool_share_pct']} for o in rows],
            exact_pair_scope='Older-proof same-Rust observations are not final-pair confirmation.' if fresh and len(pairrows)!=len(fresh) else 'Selected independent measurements bind this exact pair.' if fresh else 'No frozen independent confirmation.'))
    replay=importlib.import_module('r26-score-map').Replay(a.capture,a.rules)
    joint=[]
    for left,right in itertools.combinations(['C2','C3','E1','E2'],2):
        scenarios=[]
        for x,y in itertools.product(selected[left],selected[right]):
            scored=replay.score([(left,x['projected_time'],x['projected_size_pct']),(right,y['projected_time'],y['projected_size_pct'])])
            shares={n:scored.get(n,{}).get('share_pct',0.0) for n in [left,right]}
            scenarios.append(dict(left_run=x['run_id'],left_block=x['block'],right_run=y['run_id'],right_block=y['block'],
                points={left:[x['projected_time'],x['projected_size_pct']],right:[y['projected_time'],y['projected_size_pct']]},
                single={left:x['single_pool_share_pct'],right:y['single_pool_share_pct']},joint=shares,total_pct=sum(shares.values())))
        joint.append(dict(labels=[left,right],scenario_count=len(scenarios),total_range_pct=[min(s['total_pct'] for s in scenarios),max(s['total_pct'] for s in scenarios)],
            scope='Cartesian combinations of observed primary coordinates; not paired joint confirmation, probabilities, or a sum of independent shares.',scenarios=scenarios))
    jobs=[]
    for p in sorted((ROOT/'evidence/round26').glob('dispatch-*.json')):
        d=read(p)
        if d.get('budget_path')!='evidence/round26/extension90m/budget.json':continue
        rid=str(d['run']['databaseId']);phase='exact-gate' if d['mode']=='gate' else 'gate'
        folder=ROOT/f'evidence/round26/{rid}/{d["batch"]}/{phase}';ci=read(folder/'ci-run.json')
        assert ci['status']=='completed' and ci['headSha']==d['git_sha']
        sec=sum((datetime.fromisoformat(j['completedAt'].replace('Z','+00:00'))-datetime.fromisoformat(j['startedAt'].replace('Z','+00:00'))).total_seconds() for j in ci['jobs'] if j.get('startedAt') and j.get('completedAt') and j.get('conclusion')!='skipped')
        jobs.append(dict(run_id=rid,batch=d['batch'],mode=d['mode'],conclusion=ci['conclusion'],job_seconds=sec,receipt=folder.relative_to(ROOT).as_posix(),dispatch_utc=d['dispatch_utc']))
    stable_positive = [c['label'] for c in candidates if c['final_pair_gate_passed'] and c['final_pair_independent_main_blocks'] >= 4
        and all(c[role][cal] and c[role][cal]['minimum_pct'] > 0 for role in ['main','copies'] for cal in ['primary','shadow'])]
    result=dict(status='VERIFIED_OBSERVATIONS_CONDITIONAL_SHARES_NOT_FORMAL_PAYMENT',generated_utc=datetime.now(timezone.utc).isoformat(),
        budget=read(OUT/'budget.json'),snapshot=analysis['snapshot'],analysis_path=str(a.analysis),analysis_sha256=sha(a.analysis),
        candidates=candidates,joint=joint,same_source_controls=analysis['same_source_controls'],jobs=jobs,
        counts=dict(distinct_rust_versions=len(candidates),new_rust_versions=4,retested_rust_versions=2,ci=len(jobs),ci_success=sum(j['conclusion']=='success' for j in jobs),ci_failure=sum(j['conclusion']=='failure' for j in jobs),ci_cancelled=sum(j['conclusion']=='cancelled' for j in jobs),paired_processes=analysis['paired_processes'],job_seconds=sum(j['job_seconds'] for j in jobs)),
        observed_stable_positive_candidates=stable_positive,formal_target_met=False,formal_submission_sent=False,formal_admission='UNKNOWN',formal_payable_share='UNKNOWN',
        cost_scope='Completed job wall seconds are not billed runner minutes. Account allowance is shared; token/model/GitHub billing costs UNKNOWN.')
    save(OUT/(a.stem+'.json'),result)
    if a.stem=='delivery':render(result,ROOT/'docs/rounds/round26-extension90m.md')
    print(json.dumps({'snapshot':result['snapshot'],'counts':result['counts'],'rows':[{'label':c['label'],'main':c['main'],'gate':c['gate_status'],'final_pair_confirmation_blocks':c['final_pair_independent_main_blocks']}for c in candidates]},ensure_ascii=False,indent=2))

if __name__=='__main__':main()
