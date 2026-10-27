from pathlib import Path
import json,hashlib,datetime
D=Path(__file__).resolve().parent
H=lambda b:hashlib.sha256(b).hexdigest()
m=json.loads((D/'public-v1-manifest.json').read_text(encoding='utf8'))
s='import Submission\n\n'+'\n\n'.join((D/p['path']).read_text(encoding='utf8') for p in m['parts'])
p=D/'MathOutlet-interface-v1.lean';p.write_text(s,encoding='utf8',newline='\n')
roots=[r.replace('R19BiasBase','Submission') for r in m['roots']]
(D/'HelperAudit-math-outlet.lean.inc').write_text('\n'.join('#print axioms '+r for r in roots)+'\n',encoding='utf8',newline='\n')
im={'file':p.name,'bytes':len(p.read_bytes()),'sha256':H(p.read_bytes()),'roots':roots,'roots_count':len(roots),
 'dependency':'Exact compiled B2 Submission; no added assumptions; public four ops still B2',
 'outlet':'Submission.R19DirectBias.guardedMul_spec over exact frozen runtime and arbitrary correct fallback',
 'status':'NOT_RUN_HOLD_ORIGINAL_QUOTIENT_RESOURCE_DIAGNOSTIC','not_a_full_kernel':True}
(D/'math-outlet-manifest.json').write_text(json.dumps(im,indent=2)+'\n',encoding='utf8',newline='\n')
old=D/'HANDOFF.md'
archive=D/'HANDOFF-before-public-outlet.md'
if not archive.exists():archive.write_bytes(old.read_bytes())
text=f'''# DirectBias：完整公共出口尝试，先等 quotient 独立诊断

当前 R 授权窗口至 2026-10-27 02:28:21Z；旧 04:46:39 窗口为历史，不修改 D 窗口。无本机 Lean、Git、CI、第二运行体。

- **已实现但 NOT_RUN**：`Kernel-direct-bias-public-v1.lean`，{m['bytes']} B，SHA `{m['sha256']}`。实际 public MUL 已接冻结 DirectBias guardedMul，域外原 B2；四个完整规格根齐备。新增 typed high/q/exp → FastMul.roundP/core → FastMul.mul_spec，未假设全输入条件、未移入 R14 Model 支持。
- **最小模块接口**：`MathOutlet-interface-v1.lean`，{im['bytes']} B，SHA `{im['sha256']}`；导入已编译精确 B2 Submission，出口 `Submission.R19DirectBias.guardedMul_spec`。`HelperAudit-math-outlet.lean.inc` 自动生成 {len(roots)} 根，含 WordBias 六根。它只验证新数学模块，四个 public 操作仍 B2，不是性能候选。
- **预算与冻结**：seed 仅保留原始 Nat 依赖闭包 2018 B（未改原 quotient）；剔除未用 word 尾段。完整源只删 9 个无引用 B2 普通定理叶共 4814 B，155 个非证明声明逐字相同；逆补丁 `public-source-budget.patch`。原 1359 B 文件未改，嵌入只去最终 CR 并改 namespace。原静态 intake/policy/options PASS；Lean/axioms/replay/fullgate/timing 全 NOT_RUN。
- **必要次序仍 HOLD**：CI7 40415182202 的 scope OOM 已核实；旧 1180 原因保持 UNKNOWN。`#eval` markers 被固定 Lean 的 isolated streams 捕获，flush 是 no-op，不能定位首个定理。先 ImportOnly→QuotientOnly 独立进程；7b03 仍 HOLD、未并入本源。只有新证据定位 quotient 后才决定换 private proof。参见 `MARKER-HANDOFF.md`。
- **投入依据**：R/runtime sibling 已核 CI9 7489 完整诊断接受路径一 imul、无 FP/表读/call，bias 分支消除；仍有 shared frame。该代码生成证据支持验证公共出口，不是新 MUL 计时或采用。Jam b271 whole .998885/p05 −.010815 精确负结果继续停放。

完整清单 `public-v1-manifest.json`、`math-outlet-manifest.json`；生成器 `build_full_public.py`。新源码后续修复须另存副本，保留本版/hash。只做实际反馈所需修复，不改运行域/NaN 回退/资源上限。GRS 旁支推导已保存 `../grs-jam-lemma-paused.md` 并暂停。
'''
old.write_text(text,encoding='utf8',newline='\n')
status={'updated_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'PUBLIC_OUTLET_WRITTEN_NOT_RUN_HOLD_QUOTIENT_DIAGNOSTIC',
 'overall_deadline_utc':'2026-10-27T02:28:21Z','old_deadline_historical':'2026-10-27T04:46:39Z',
 'public':{k:m[k] for k in ['file','bytes','sha256','roots_count','static_gate']},'math_interface':im,
 'resource1':'7b03 HOLD, not incorporated','runtime':'Frozen f3e86842 unchanged; CI9 positive codegen per R, no full timing',
 'statement':'NOT_RUN','kernel_replay':'NOT_RUN','axioms':'NOT_RUN','performance':'NOT_RUN','tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN','direct_CI_seconds':0}
(D/'status.json').write_text(json.dumps(status,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({k:im[k] for k in ['file','bytes','sha256','roots_count']},indent=2))
