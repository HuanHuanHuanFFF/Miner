# R14开发恢复入口

本轮仍在推进，不能将阶段结果当作8小时完成。窗口UTC2026-10-24 19:02:59至2026-10-25 03:02:59（北京时间03:03—11:03）；02:02:59目标源码冻结，已启动CI收齐终态后交付。准备、等待、修复都计入，不补时、不另启窗口。

唯一总状态是`../../../coordination/development-status.json`，本文件只供恢复定位，实际Git/CI先刷新。工作分支`huan/codex-gpt`；main本地及远端71eb78ce。本轮只推实验分支，不合并、不正式参赛、不碰钱包。本机不运行Lean/重型工具链，不追加模型额度重置，不加第4个agent。

研究会话01a15e06已按用户要求改为6.1Sol/xhigh并收到一次启动消息；普通交流只走D:/CodingProject/Bitget-Collab。开发侧唯一维护codex/status.md和本worktree Git/CI；研究写astra-*、f01-r14-math-*及分主题消息；DeepSeek独立worktree、huan/dhs-deepseek、用户另行启动。旧子agent均completed。本方1个在途、DeepSeek1个，合计2，不借槽。

当前已知作业：

- 40124283357，source5f422bf3，seed1425001：45min上限cancelled，46份artifact及日志已全部回收并入Git。Nested完整：DF/41 full25通过；398d因helper定理类型漏改add名字而statement失败，无性能。失败原件未修改；dc8a只修证明类型、运行定义相同。
- 40128099563，sourcebff841a0，seed1425005：六项statement批次终态failure，107份artifact全部SHA验证并入Git。206f舍入边界、2bd8行NaN/Thunk、3c6a精简基底、dc8a修复通过编译。4c52 shape1深度和字面值简化失败，14bc native-product1的Dyadic歧义/不存在定理失败。分项真实错误在`development-proof-batch-40128099563.json`及单项JSON，已在公共区交研究侧修复；不是数学反例。额外helper公理审计/kernel replay仍未做。
- 40129155932，source273c32c8，seed1425006：本方当前full25运行，候选DF/dc8a/2bd8/41，先等终态再collect、summarize。准确状态先读API。发现组低于等于0.97且p05>0才冻结两组新输入；负结果不换有利seed。已准备但未派发1425002/3/4，因编译请求陆续合批而被1425005替代，原文件保留。
- DeepSeek40126911323（sourcea4161b10，seed1425002）已完成，报告169f/p2cont8整包0.9584、BMM0.8319；尚在做独立取证/统计复核，不直接采用。开发侧collect读取该既有run，未新增CI。DeepSeek40128718577（seed1425003）隔离p2cont等路由，实际状态从对方文件/API刷新。对方已接受后续改用1525xxx；本方用1425xxx，候选冻结后才生成确认组。

复用现有工具：本目录`development-ci.py`（明确--branch huan/codex-gpt）、`prepare-plan.py`、`development-collect-run.py`、`development-job-state.py`、`summarize-run.py`、`freeze-cohort.py`与三组验收/采用脚本。所有原artifact统一在`f01-mul-log2-proof1/ci-runs`，保持原字节。原始日志有CRLF和尾随空格，Git检查仅针对源码/自有元数据；提交前仍逐字节核对暂存原件，绝不为格式检查改写raw。

冠军已刷新#309：`official-20261024T191026Z`。只替换冠军分母，我方旧冻结分子、6个配对样本和work不变；看板DF整包约1.25、BMM2.73。当前模型SHA8e681261，旧5d946原字节保留；新anchor/retained-estimate-freeze在本目录。相同源码/冠军后续control不重算数字。当前firstD暴露输入份额add32.91%、mul38.38%、sum9.81%、BMM18.90%；scalar specials总成本上限4.48%、BMM specials1.69%。所以NaN组件只作小组件，后续主要投入普通乘法/矩阵主路径。

较大后续路线：

- 研究侧native同宽缩放融合：已有包含Nat/模型/原字/UInt32运行表达的草稿，仍NOT_RUN；优先拿真实编译错误修复两个关键namespace，不由开发覆盖研究未完成源。最新请求/状态读astra-status及公共区消息。
- 开发侧正常结果专门整数乘法：读`development-word-normal-design.md`及30800项有限模型。仅normal输入且指数和128..379；用48位乘积、偏置ties-even和直接打包，删旧M19通用rounder分支。关键缺口是无回卷bias-RNE、正常域/packing/spec证明，尚无候选性能。SoftFloat固定公开源与完整BSD许可证在development-sources，来源回执已保存。不是复测旧M19。
- 2bd8只针对RowStream按A行rawNaN走原replayEarly，普通行同Packed10，Thunk延迟并共享准备。正确性不依赖NaN payload猜测。研究已核对历史无同机制负例，但类别覆盖有限，不夸大收益。
- 3c6a压缩基底227657B，199段独占行非归属注释被移除，非注释文本与行数保持，statement已通过；余量28343B可组合数学证明，最终完整源码仍须原full gate。原DF没改。

接下来先回收当前full结果/复核DeepSeek原始证据，检查研究新修复请求，再投入下一有意义的候选。每阶段提交精确自己的文件、公共区逐主题交接；不要暂存astra-status等研究侧未冻结文件，不改对方worktree或共享协议。
