"""Close this R20 window only at the unchanged common deadline; no research work."""
from pathlib import Path
import datetime, hashlib, json
HERE=Path(__file__).resolve().parent
deadline=datetime.datetime(2026,10,27,8,32,58,tzinfo=datetime.timezone.utc)
now=datetime.datetime.now(datetime.timezone.utc)
if now<deadline: raise SystemExit('Window still active; do not close early.')
status=json.loads((HERE/'research-status.json').read_bytes())
status.update(state='TIME_WINDOW_COMPLETE_RESEARCH_STOPPED',updated_utc=now.isoformat(),actual_controller_end_utc=deadline.isoformat(),closure_observed_utc=now.isoformat(),controller_active_seconds=2335,shared_window_seconds=2700,late_join_seconds=365)
status['processed_messages'] += ['20261027T080621492Z-r20-sum-certificate-low-coverage.md','20261027T082005800Z-r20-row8-nine-roots-pass-terminal-ci-live.md','20261027T082450074Z-r20-two-probes-pass-real-allocation-removed.md','20261027T083019200Z-r20-complete-terminal-next-source-not-run.md']
status['results']={'row8':{'source_sha256':'ec40e88eb85730520a1cd1e6adcbaea3c8161fc5c0f7e4b2f5795e178d24a5a6','run':40471664006,'statement_and_two_module_replay':'PASS','allowed_helper_roots':9,'performance':'NOT_RUN'},'terminal_pair':{'source_sha256':'b6b77553d49e968db27639b84f104783a9cf474ed963ec9cff7753a7adb17962','run':40472418849,'statement_and_two_module_replay':'PASS','allowed_helper_roots':8,'performance':'NOT_RUN'},'new_adoption':False,'remaining_R_CI':[],'new_public_terminal_integration':'39626da4 / NOT_RUN, D owned'}
status['resources']['token_counts']='UNKNOWN; no bill or per-route token totals inferred'
for row in status['routes']: row['state']='WINDOW_CLOSED; see own handoff for exact acceptance and remaining gaps'
(HERE/'research-status.json').write_text(json.dumps(status,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
text='''# R20研究最终交接

共同截止UTC2026-10-27 **08:32:58**（北京16:32:58）已到；R实际07:54:03加入，持续至共同截止，**38分55秒**，不把晚加入补成45分钟。三个Astra分别07:55:13／43／53开始，分工及本方记录见research-status.json与各路线HANDOFF。本方没有新增长CI，两个R请求诊断均终态收齐。

- **八列广播ec40／239638B**：CI40471664006，声明、Submission/VerifyFull原回放及9根三允许公理PASS。无全局A缓存，每k共享A转换；public仍B2，新publicBMM与性能NOT_RUN。
- **终端写出b6b7／230373B**：CI40472418849，同层次8根PASS。真实F2终态分配消失；单框架168→120B，普通steady浮点显式栈由96B变32B，同时向量算术变scalar；指令/字节不是速度。完整成本仍未测。两组77原件共4789601B已独立逐哈希核验，见originals-verified-*.json。
- **下一可证起点**：row-broadcast/postfreeze/WideRowRefinement.lean.inc为任意p／状态view的原序投影；representation/streaming-accumulator/SafeState.lean.inc用原安全Array.modify。后者只可能复用独占Cell，replicate初态共享会有首轮分配，实际CtorReuse／closure／总成本UNKNOWN。两新接口Lean NOT_RUN。
- **数学与淘汰**：mathematical/HANDOFF.md保留严格吸收、一般RNE减法、binade真drop及分配律／幂次缩放反例。scalar_sound原桥未闭；低覆盖SUM扫描与exact raw行列去重本窗NO-GO，不由有限oracle提升全证明。root独立复算结构反例，见semantic-counterexamples-independent-review.json。

开发已形成完整public接入候选f01-r20-dev-terminal-dc1／39626da4／237637B，**尚未编译，不能继承b6b7结果**。下一步先精确9根与完整模块，再核真实public caller和完整调用成本；采用仍需新D+A+B。当前保留B2／622d8394，无新采用、无正式提交。

两份源码和LICENSE共3份、221726B先下载E:/Download/FloatLib/20261027-R20，再逐字节整理至本目录source-intake/lean-runtime-293d5d0c；无ZIP。原网页仅见reduced-capabilities与thinking-effort菜单，Pro可用性UNKNOWN；三Astra承担研究，未等待网页。

根python -B scripts/project.py check于08:29:59—08:30:27完整PASS，包含两赛道本地自检，见final-local-check.json；没有本机Lean或性能测试。D唯一Git／push／CI／总状态协调者，技术文件按既有范围统一提交；browser-pro-observation.json含私有研究页定位，仅留本地。Token／分路线成本UNKNOWN，未宣称60/20/15/5实际达成。
'''
(HERE/'HANDOFF.md').write_text(text,encoding='utf-8')
files=[]
for path in sorted(HERE.rglob('*')):
    if not path.is_file() or path.name=='delivery-inventory.json': continue
    raw=path.read_bytes()
    files.append({'path':path.relative_to(HERE).as_posix(),'bytes':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'publication':'LOCAL_ONLY' if path.name=='browser-pro-observation.json' else 'TECHNICAL_WITHIN_STANDING_SCOPE'})
(HERE/'delivery-inventory.json').write_text(json.dumps({'created_utc':now.isoformat(),'files':files,'note':'Identity index only; D reviews publication selection and owns Git. Do not count local-only browser locator as public material.'},ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'state':status['state'],'closure_observed_utc':now.isoformat(),'controller_active_seconds':2335,'files':len(files),'handoff_sha256':hashlib.sha256((HERE/'HANDOFF.md').read_bytes()).hexdigest()}))
