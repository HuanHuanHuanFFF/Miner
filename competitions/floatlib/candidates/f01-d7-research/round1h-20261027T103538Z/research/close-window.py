"""R21 deadline bookkeeping only. Never starts research, CI, Git or submissions."""
from pathlib import Path
import datetime, hashlib, json
H=Path(__file__).resolve().parent
now=datetime.datetime.now(datetime.timezone.utc)
deadline=datetime.datetime(2026,10,27,11,35,38,tzinfo=datetime.timezone.utc)
if now<deadline: raise SystemExit('Common window still active; no early close.')
s=json.loads((H/'research-status.json').read_bytes())
s.update(state='TIME_WINDOW_COMPLETE_RESEARCH_STOPPED',updated_utc=now.isoformat(),research_end_utc=deadline.isoformat(),closure_observed_utc=now.isoformat(),controller_active_seconds=3517,common_window_seconds=3600,late_join_seconds=83)
jobs=json.loads((H.parent/'development-jobs.json').read_bytes()).get('jobs',[])
s['D_jobs_snapshot_at_close']=jobs
s['new_adoption_receipt_received']=False
s['close_scope']='R research window only. D owns pending full-cost CI and final adoption/publication; no new R task or CI after deadline.'
(H/'research-status.json').write_text(json.dumps(s,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
text='''# R21研究最终交接

共同UTC2026-10-27 **11:35:38**（北京19:35:38）已到，R停止新增研究。实际10:37:01接入，持续至共同截止，**58分37秒**；晚接入未延期。三Astra实际开始A10:38:49／B10:39:21／C10:39:17，各自闭合记录以本方HANDOFF/manifest为准。

**已严验的新完整源**：public终端BMM `f01-r21-dev-terminal-dc4`／**7de57a41…／238168B**，CI40492989029、head a9a4053f，声明、Submission/VerifyFull原内核回放及9根三允许公理PASS。root独立逐字节核47原件／2737532B，见originals-verified-40492989029-f01-r21-dev-terminal-dc4.json。三个先前失败分别是ifFalse、dependent count、List/Array末桥；运行体未因此改变。b66另一proof稿未运行，不能继承7de结果。

**完整成本已实测，不采用**：原public D **40493865047**，head492b047f、seed2120101，B2＋control41＋7de，原25轮/152timed及156case全部通过，capture/profile=false。7de相对B2 whole=**0.9915165699**、BMM=**0.9431702670**、gain p05=**−0.0248642808**；即BMM快约5.68%、整包约0.85%，未达原3%且p05未正。精确运行体停放，不A/B、不换seed，保留证明/真实caller。56原件2109857B由D收齐，原始结果development-result-40493865047-f01-r21-dev-terminal-dc4.json；不将公共比值换算新私有官方成绩。保留B2。

**末段批6**已启动streaming4e36（19根）、scaled运行29d（8根）、同宽数学组合56cdb（15根）。截止后只收证据，不修源；确切终态回执由D更新，未收前仍NOT_RUN/UNKNOWN。

**新矩阵机制已成完整可测调用**：streaming-state/v2/Kernel.lean，**4e36c931…／237212B／19根**。安全mapIdx整列consume、专用k loop、完整两行任意p与原finish/replay/输出，callback不捕获旧state。v1/5bbf的实际唯一错误是emit_size的apply/motive；v2仅修该proof、运行149个非证明声明相同。**v2 Lean／C／性能尚未确认**，不是新fullbatch publicBMM。单槽余量不替代验收。后继首轮融合ae1b片段仅符号顺序/负零边界，保留`+0+product`；首k共享Cell、两slot写、RC/COW、closure、spill、最终释放均不得忽略。

**独立标量机制**：`f01-r21-r-scaled-u32-probe1`，**29d09f90…／228050B／8根**（4旧spec＋4定义），public仍B2，完整guard与原fallback。复续R18未测储备，P→Float32→精确2^-23→U32，新增FP乘/常量读取并期望删U64 reverse补偿；**无新MULspec／速度确认**。root独立23431合法输入零差异并抓3类mutant，只有有限证据。scalar-frontier/ScaledBridge.lean.inc **a4432cb1…／5568B**及helper提供7根实质同宽桥尝试，NOT_RUN，原P decode/字段/guard到public连接仍缺。

**已止损/反例**：幂次因子分支10794旧位置仅1命中；大high16值表覆盖多为原已优化零，重表/守卫未支撑收益，均不造完整候选。跨宽Double旧opaque桥无新前提。pair-batch-boundary-counterexample.json给batch2,m3,n2,p3精确反例：全局跨批配对将应44误算28，必须localbatch与奇尾fallback；它不反驳冻结pair诊断。A另留6根writer/same-batch运输，NOT_RUN。

**交付/资源**：root的`python -B scripts/project.py check`于11:27:56—11:28:14完整PASS，含两赛道本地检查，见final-local-check.json；无本机Lean、注册、资金或新正式提交。网页Pro新DOM明确disabled/Usage limit reached，三Astra替代研究，未送新网页请求；三条官方fresh读同403，失败字节先落E后核入official-public，最新rank UNKNOWN，保留10:28原#336回执。#336只绑定B2/622d。

D唯一Git／push／CI／总状态协调者；R只写research/及授权独立候选，技术成果由D按持续授权统一推送。真实token／cache／分路线共享CI秒数UNKNOWN，未宣称初配比例达成。delivery-inventory.json为精确快照；动态收尾状态若更新须按新时间再核，不混淆冻结源。
'''
(H/'HANDOFF.md').write_text(text,encoding='utf-8')
files=[]
for p in sorted(H.rglob('*')):
    if p.is_file() and p.name!='delivery-inventory.json':
        raw=p.read_bytes();files.append({'path':p.relative_to(H).as_posix(),'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest()})
(H/'delivery-inventory.json').write_text(json.dumps({'at_utc':now.isoformat(),'files':files,'scope':'Identity snapshot; D owns publication selection and Git. New independent29d candidate is separately frozen at its own manifest.'},ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'state':s['state'],'closure_observed_utc':now.isoformat(),'controller_seconds':3517,'files':len(files),'handoff_sha256':hashlib.sha256((H/'HANDOFF.md').read_bytes()).hexdigest()}))
