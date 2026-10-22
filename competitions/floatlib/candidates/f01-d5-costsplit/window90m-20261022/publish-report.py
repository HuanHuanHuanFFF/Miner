"""Publish the final concise user index and detailed research evidence links."""
from pathlib import Path
import datetime,json,os

ROOT=Path.cwd();OWN=Path(__file__).resolve().parent
state=json.loads((ROOT/'competitions/floatlib/coordination/development-status.json').read_bytes())
done=json.loads((OWN/'completion.json').read_bytes());summary=json.loads((OWN/'summary.json').read_bytes())
assert done['all_started_jobs_collected']
def atomic(p,s):
    t=p.with_name(p.name+'.update-tmp');t.write_bytes(s.encode());os.replace(t,p)
text=f'''# R5 九十分钟协作

共同窗口：2026-10-22 18:05:04—19:35:04 北京时间。实际收齐于 {done['closed_at_utc']}；用时 {done['elapsed_minutes']:.1f} 分钟，其中窗口后回收 {done['drain_minutes']:.1f} 分钟。新方向搜索11:02:48Z停止，最后数学桥修复后的完整源11:14:35Z冻结。

最终包：[{done['candidate']}](../{done['candidate']}/Kernel.lean)。SHA-256 `{done['kernel_sha256']}`；当前仍不能取代现任冠军。四项用户看板见[dashboard.md](../../../../../dashboard.md)。

本轮 {done['jobs']} 项已启动CI全部终态回收，{done['payloads_verified']} 份原始payload盘面和Git字节核验。选中同源码完整gate：{', '.join(map(str,done['full_gate_runs']))}；独立确认：{done['confirmation_run']}。每次完整gate均包含原四义务、内核重放、3允许公理、12计分类25配对轮及当前官方fingerprint。正式上传未执行。

| 方向 | 验证及决定 |
| --- | --- |
| 矩阵数值解码 | 完整通过；602同机约慢2.3%，停放 |
| B打包地址外提 | 完整通过；603同解码对照三类约少7%，继续合并原始解码 |
| 证明B读取边界 | 原稿证明失败保留；501a修复稿完整通过，同机约少4.7% |
| 两层按行输出 | 首稿97cb完整通过，604同机约少12.3% |
| 单层流式输出 | 首稿b5ae完整通过，605同机约少15.2%；两种布局最终同机比较 |
| 字节通道选择 | 完整通过，约0.13%无实质收益，停放 |
| 延迟回退地址 | 完整通过，约0.38%无实质收益，停放 |
| 单次位转换 | 原稿及proof1失败保留；最终整包修复版本的实际结果见下方精确回执 |

以上是各自同批发现结果，不能相加。最后选择依据完整组合及新runner确认，保留所有CPU、慢样本、失败源和原始测量。

证据：[完整审计](summary.json)、[同批逐项对照](same-batch-comparisons.json)、[现任冠军逐类比较](operation-comparisons.json)、[完成回执](completion.json)、[网页原件独立校验](web-independent-audit.json)、[研究交接](../../../research/astra-collab-20261022-r5/checkpoint-06-stream-pass.md)。

阶段诊断已修复提取、固定sysroot头文件、构建/运行内存上限和BENCH_PAIRS导致的空batch问题。最终609三次13个实际bmm调用且checksum一致；包含未计分raw的聚合计时，不能把raw主导的输出占比当作正式计分瓶颈。timed-only阶段占比仍UNKNOWN；原始零工作量数据保留并标INVALID_ZERO_WORKLOAD。
'''
# Candidate folders are siblings of f01-d5-costsplit, two levels above this report.
text=text.replace(f'../{done["candidate"]}/Kernel.lean',f'../../{done["candidate"]}/Kernel.lean')
atomic(OWN/'README.md',text)
old='competitions/floatlib/candidates/f01-d4-global8/window2h-20261022/README.md'
p=ROOT/'README.md';s=p.read_text();s=s.replace('[当前两小时协作]('+old+')','[当前九十分钟协作]('+str((OWN/'README.md').relative_to(ROOT)).replace('\\','/')+')');atomic(p,s)
p=ROOT/'competitions/floatlib/README.md';s=p.read_text();s=s.replace('[当前两小时协作](candidates/f01-d4-global8/window2h-20261022/README.md)','[当前九十分钟协作](candidates/f01-d5-costsplit/window90m-20261022/README.md)');atomic(p,s)
p=ROOT/'competitions/floatlib/docs/first-candidate.md';s=p.read_text()
if '## R5：2026-10-22 九十分钟协作' not in s:
    s+='''\n\n## R5：2026-10-22 九十分钟协作

研究与精确终态见[本轮报告](../candidates/f01-d5-costsplit/window90m-20261022/README.md)。先移除完整调用中的重复坐标/打包工作，再考虑继续扩大微块。两层按行与单层流式均首次全输入证明通过且有完整调用收益；跨CPU发现百分比不能直接排序，最终组合同机比较。UInt8选择与延迟地址虽C更简洁却没有足够收益，不机械合并。泛型BitVec的全1字面量可能值相等而不定义相等；先对齐原模型条件，保留真实失败。候选局部诊断的构建和运行沿用各自官方内存帽，BENCH_PAIRS决定矩阵batch，必须断言非空；计分与未计分raw的阶段成本分开。所有已启动CI自然终态回收，不因窗口到期取消。
'''
    atomic(p,s)
print(json.dumps({'report':str(OWN/'README.md'),'candidate':done['candidate']}))
