"""Report only collected observations, explicit failed gates and actual budget limits."""
from pathlib import Path
import argparse,hashlib,json,statistics as st
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round21'
def read(p):return json.loads(p.read_bytes())
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--analysis',type=Path,required=True);ap.add_argument('--audit',type=Path,required=True);ap.add_argument('--capture',type=Path,required=True);a=ap.parse_args();a.analysis=a.analysis.resolve();a.audit=a.audit.resolve();a.capture=a.capture.resolve();d=read(a.analysis);audit=read(a.audit);budget=read(E/'budget.json');comp=read(a.capture/'competition.json');assert not audit['uncollected_run_ids']
 assert d['snapshot']['snapshot_id']==comp['current_snapshot_id'];candidates=[]
 # Recompute exact local-parent comparisons, separate from the formal anchor.
 parent_obs={}
 for run in d['runs']:
  folder=E/run['run_id']/run['batch']/'gate';state=read(folder/'state.json');by={e['name']:e for e in state['spec']['entries']};metric={(m['candidate'],m['round']):m for m in state['metrics']}
  for name,en in by.items():
   if en.get('control'):continue
   manifest=read(ROOT/en['path']/'manifest.json');parent=manifest['parent'];match=[n for n,e in by.items()if Path(e['path']).name==parent and e.get('control') and not n.endswith('-shadow')]
   if not match:continue
   ref=match[0]
   for block in range(1,state['spec']['screen_blocks']+1):
    if (name,block) not in metric or (ref,block)not in metric:continue
    delta=100*(metric[name,block]['time']/metric[ref,block]['time']-1)
    parent_obs.setdefault(en['hashes']['parse.rs'],[]).append({'run_id':run['run_id'],'block':block,'role':run['role'],'reference':ref,'delta_pct':delta})
 for c in d['candidates']:
  obs=c['observations'];co={'candidate':c['candidate'],'files':c['source_versions'][0]['files'],'summary':c['summary'],'independent_confirmation':c['independent_confirmation_summary'],'exact_parent_observations':parent_obs.get(c['rust_sha256'],[]),'full_gate':'NOT_PASSED'}
  candidates.append(co)
 best=max((o['single_pool_share_pct']for c in d['candidates']for o in c['observations']),default=0)
 result={'status':'BUDGET_DELIVERY_OBJECTIVE_NOT_ACHIEVED','budget':budget,'snapshot':d['snapshot'],'candidates':candidates,'best_observed_conditional_pool_pct':best,'current_10pct_count':sum(o['single_pool_share_pct']>=10 for c in d['candidates']for o in c['observations']if o['calibration']=='primary'),'formal_submission_sent':False,'full_gate_passed_count':sum(g['status']=='EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED'for g in audit['full_gates']),'analysis':str(a.analysis.relative_to(ROOT)),'audit':str(a.audit.relative_to(ROOT)),'limits':['Independent runs confirm only frozen public protocol/environment, not hidden corpus.','Main/shadow views of same blocks are not additional independent samples.','No formal payment or submission readiness is established.','I CIcancelled after raw26processes/stategate collected; complete timing is distinguished from overallCI success.']}
 (E/'final-summary.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
 lines=['# 第二十一轮：两小时冲击10%竞赛池份额','','固定窗口：北京时间 **2026-10-10 21:49:49–23:49:49**，中断、排队、修复与交付均计入原窗口。执行规则见[AGENTS.md](../../AGENTS.md)。','','**10%目标未完成。** 未进行正式上传、注册或签名；所有已测候选在最终快照下的单独投影均为0%。无新候选通过完整公共gate，不能标成可正式提交成功的成果。',f'','最终完整快照 **'+str(d['snapshot']['snapshot_id'])+'**，评分时间`'+d['snapshot']['computed_at']+'`，freshness=`unknown`。以下份额为 **INFERRED 公共条件估算**，沿用同块正式参照迁移并重放官方两轴公式。原始计时、源码和环境为 **VERIFIED**；私有集、未来准入和实际支付为 **UNKNOWN**。','','## 全部已计时候选','','|候选|主校准中位／范围|零份额次数|相对精确本地父版本时间变化|新独立复现|','|---|---:|---:|---:|---|']
 for c in candidates:
  v=c['summary']['primary'];ps=c['exact_parent_observations'];delta=('UNKNOWN'if not ps else f"{st.median(x['delta_pct']for x in ps):+.4f}%（{min(x['delta_pct']for x in ps):+.4f}至{max(x['delta_pct']for x in ps):+.4f}%）")
  independent=c['independent_confirmation'].get('primary');ic='未安排'if not independent else f"{independent['n']}块／{independent['runner_count']}runner；份额{independent['median_pct']:.6f}%"
  lines.append(f"|{c['candidate']}|{v['median_pct']:.6f}%／{v['range_pct'][0]:.6f}–{v['range_pct'][1]:.6f}%|{v['zero_count']}/{v['n']}|{delta}|{ic}|")
 lines+=['','速度负号表示更快；原分析`comparison_baseline`对部分SF候选指向正式603参照，不能冒称精确本地父版本。上表改由manifest父目录匹配同块对照；原JSON保留。主／影子为同一块的两种视图，全部观测范围、逐runner统计和同源码分歧见[全量分析](../../'+result['analysis']+')。达到10%的主视图次数为'+str(result['current_10pct_count'])+'；样本次数不表示正式成功概率。','','## 本轮机制与反馈','','- 辅助搜索消费者分配：只撤掉三条既有路线之一；在起始快照仅head16短暂最高约0.025%，前沿更新后全部归零。主表16位表示保住公共输出，却比父版本慢0.85%–1.39%。','- 精确逐块接受与边界价格：603派生版少136B，608派生版少59B，但原协议时间明显增加，未得到新前沿；608accept版多32B，仅编码筛选后暂停。质量小收益不当作总收益。','- SF显式16位后向距离／单次构造：两个父版本的28文件token／编码字节完全相同；精确父版本比较没有确认速度收益。两次完整gate发现并修补了循环长度不变量，第二次仍缺`with_capacity`空向量长度初始化，尚未通过。','- 辅助字级比较与A价格打包：28文件保持精确token／输出。字级比较将8／16字节前缀处理移到已有primitive，A版本将固定9bit打包移出逐长度循环；新的速度复现单列。A版本还改变了函数内联边界，其贡献未分离，不能把全部差异归因于价格表示。','','## 完整验收与冻结字节','','|对象|Rust SHA-256|Lean SHA-256|验收|','|---|---|---|---|']
 for name in ['r21-539-secondary-word16','r21-a-packed-cost','r21-sf-prevdist16','r21-sf-prevdist16-proof1']:
  files=audit['candidate_pairs'][name];g=next((g for g in audit['full_gates']if g['candidate']==name),None);state='NOT_RUN'if not g else g['status'];lines.append(f"|[ {name} ](../../candidates/{name})|`{files['parse.rs']}`|`{files['Parse.lean']}`|{state}|")
 lines+=['','SFproof1是相同Rust的证明迁移，不计第二个机制。原始输入、重新提取、Lean错误、公理与官方树检查保持原字节。有限等价、同字节和时间复现均不替代完整gate。','','## 竞争与证据边界','','本轮起始快照29560仍由595领先；中段29575已有612以约24.41%领先并支配595。新公开595通过普通无认证API取得，归属与原始哈希保存于[来源回执](../../references/round21-public-595/source-receipt.json)。607仍返回403，未绕过限制。595复用脚本仅作为未运行草稿保存，没有编造其收益或CI。','', '同块联合重放见全量分析`joint`；最终所有已测点单独均被现有前沿支配，同时插入仍为0，不能相加独立估算。跨独立runner没有伪造配对联合数据。','', 'I整体CI触及25分钟上限后显示cancelled，已保留完整两块／26个配对进程及gate阶段状态，不能称整体CI通过。最后复现作业按其实际结论列入审计，失败或超时不隐藏。','','## 实际消耗与后续起点','',f"共{audit['dispatched_runs']}个手动作业，{audit['original_paired_processes']}个原协议配对进程（含对照），{audit['distinct_candidate_rust_count']}份不同新Rust。原始artifact文件{audit['raw_file_count']}份／{audit['raw_bytes']:,}字节逐一SHA-256通过；已收齐，见[审计](../../{result['audit']})。runner累计{audit['runner_minutes']:.2f}分钟，是并发作业之和；金额和模型可归因费用UNKNOWN。账户观察剩余70%，0重置、0购买。",'','下一轮最高价值动作：从新公开595实际编码和原协议配对基线开始，先修正其只有一条辅助环的输入结构假设，再比较少量机制迁移；对保留的价格打包微收益分离内联边界贡献。若继续SF距离表示，先补齐空容量向量长度初始化并完整gate；旧的同字节结果不授权直接提交。','','[提交收益看板](../../DASHBOARD.md)已刷新；累计α采用官方API，非钱包余额或净利润。用户没有授权本轮正式提交。','']
 (ROOT/'docs/rounds/round21.md').write_bytes(('\n'.join(lines)).encode());print(json.dumps({'best_conditional_pct':best,'candidate_count':len(candidates),'gate_passed':result['full_gate_passed_count'],'report':'docs/rounds/round21.md'}))
if __name__=='__main__':main()
