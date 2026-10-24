from pathlib import Path
from datetime import datetime, timezone
import json, os, subprocess, stat

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
STATE = ROOT/'competitions/floatlib/coordination/development-status.json'
OWN = Path('D:/CodingProject/Bitget-Collab/codex')
for p in (OWN.parent, OWN, OWN/'messages', OWN/'status.md'):
    assert not p.lstat().st_file_attributes & stat.FILE_ATTRIBUTE_REPARSE_POINT
old = STATE.read_bytes()
state = json.loads(old)
assert state['state'].startswith('R13_WINDOW_COMPLETE')
prior = OUT/'development-pre-round-state.json'
with prior.open('xb') as f: f.write(old)
plan = json.loads((OUT/'round-plan.json').read_bytes())
now = datetime.now(timezone.utc)
state.update(state='R14_ACTIVE_THREE_AGENT_RESEARCH', updated_at_utc=now.isoformat(), branch='huan/codex-gpt')
state['research_round'] = {'id': plan['round'], 'state': 'ACTIVE', 'start_utc': plan['start_utc'], 'deadline_utc': plan['deadline_utc'], 'budget_minutes': 480,
                          'plan': (OUT/'round-plan.json').relative_to(ROOT).as_posix(), 'started_ci': [], 'active_ci': [], 'completed_ci': [],
                          'previous_round_state': prior.relative_to(ROOT).as_posix()}
tmp = STATE.with_name('development-status.r14-init.tmp')
assert not tmp.exists()
tmp.write_bytes((json.dumps(state, ensure_ascii=False, indent=2)+'\n').encode())
assert STATE.read_bytes() == old
os.replace(tmp, STATE)
head = subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT).decode().strip()
stamp = now.strftime('%Y%m%dT%H%M%S%f')[:-3]+'Z'
message_id = stamp+'-r14-development-startup.md'
message = f'''# R14三方八小时协作启动

时间：{now.isoformat()}
关联：R14-20261024T190259Z；用户本轮明确授权8h协作与CI验证。
类型：协作请求
摘要：窗口UTC2026-10-24T19:02:59Z至2026-10-25T03:02:59Z（北京时间03:03–11:03）。开发协调者负责本worktree的Git/CI及codex/status.md；研究agent已按用户要求改为6.1Sol/xhigh并收到一次启动消息，专攻数学与Lean；DeepSeek由用户另行启动、独立探索。三方总数固定，不另加子agent。本机不跑Lean/重型编译；CI每方一个在途、合计两个，不借槽。
需要对方：DeepSeek启动后请独立选择有较大收益的方向，先在自己的状态说明文件范围和首个机制，避免与研究侧同宽缩放融合/Lean桥接及开发侧主要算术路径重构重复。研究侧使用本轮astra-status.json，公共区逐议题独立 *-r14-research-*.md；普通交接不追加会话消息。双方在阶段检查点读对方状态与未处理留言，难点单独发主题留言并附最小可执行请求。
证据：D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/round-plan.json（未提交初始化，随后由开发协调者提交）；分支huan/codex-gpt，起点{head}。
结论状态：VERIFIED（窗口/分工/启动）；新候选与性能尚未取得。
下一步：修复实验分支CI绑定、核查官方当前状态，并优先比较有实测覆盖的大收益机制。UTC02:02:59目标冻结，最后一小时完整确认与回收，已启动CI收齐终态。
'''
with (OWN/'messages'/message_id).open('xb') as f: f.write(message.encode())
old_status = (OWN/'status.md').read_bytes()
status = f'''# Codex当前状态

更新时间（UTC）：{now.isoformat()}
状态：R14_ACTIVE
所属会话：Bitget开发协调01a15ce7-bf54-74b2-8a2b-4a1e2f3828d7
工作区：D:/CodingProject/Bitget
实际分支：huan/codex-gpt
HEAD：{head}
当前任务：R14八小时三方协作冲冠；开发集成与CI。
授权：实验分支必要公开push、手动公共标准runner；无本机Lean/重型编译，无付费私有runner、正式提交、资金或新额度重置。
预算／截止：480分钟；UTC2026-10-24T19:02:59Z至2026-10-25T03:02:59Z。源码冻结目标02:02:59Z。
候选：保留df5c；新实验待冻结。
文件范围：开发f01-r14-dev-*及本轮development-*、脚本与集成状态；研究f01-r14-math-*及本轮astra-*。共享codex/status.md由开发侧唯一维护，研究追加逐议题消息。
在途CI：无；本方最多1个，DeepSeek最多1个，合计最多2个。
阻塞：旧CI辅助脚本绑定旧分支，修复中。
下一步：完成CI绑定、首个有覆盖的大收益候选/诊断；检查研究与DeepSeek交接。
需要对方：登记独立方向和精确文件范围；难点逐议题交接并附源码/哈希/最小请求。
项目状态入口：D:/CodingProject/Bitget/competitions/floatlib/coordination/development-status.json
本轮计划：D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/round-plan.json
最近交接消息：codex/messages/{message_id}
已处理对方消息：无（初始化时deepseek/messages为空）。
'''
tmp = OWN/'status-r14-init.tmp'
assert not tmp.exists()
tmp.write_bytes(status.encode())
assert (OWN/'status.md').read_bytes() == old_status
os.replace(tmp, OWN/'status.md')
print(json.dumps({'round':plan['round'],'state':'ACTIVE','message':message_id},ensure_ascii=False))
