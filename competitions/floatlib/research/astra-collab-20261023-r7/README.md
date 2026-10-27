# R7研究材料索引

本目录属于Miner优化/FloatLib十小时协作的R文件范围。**当前状态唯一入口为[research-status.json](research-status.json)**；时间、ready候选、已接受组件和下一检查点以该文件为准。D拥有Git、CI、公共看板与最终采用；这里的原始证据不扩大权限。

## 路线及验收

- 非NaN终点桥：真实Model/Configured/ExecFloat全输入非NaN等价，含Inf。`nonnan-first-full-805.json`为首轮完整验证的独立读取结果。
- quiet-NaN矩阵后缀：乘法先quiet，再相加，真实后缀吸收；`nan-first-full-806.json`为首轮完整验证的独立读取结果。
- 精确组件组合、矩阵native前缀修复、求和native前缀加raw signaling后缀：各精确源和NOT_RUN/后续实际结果由当前状态链接，不能继承组件PASS或相加组件收益。
- 求和最后sNaN规则：网页证明/实际集成分开记录。求和不得误用dot的无条件quiet后缀吸收，必须保留sign/payload和后来的sNaN替换。
- canonical image强闭包与单遍sum：`canonical-image-compiled-equivalence.json`连接最小公开集成实际编译；`singlepass-proof1-lineage.json`记录唯一新单遍循环及未验收边界。
- 低normal精确缩放解码：先按`sum-decoder-low-screen.json`调查实际输入曝光，网页数学/C证据未返回前不增加完整候选。

## 可交接文件

- [web-deliveries.json](web-deliveries.json)：E盘原ZIP/报告的当前存在性、SHA256、对应完整提取目录和顶层Lean源码。原始成功与失败证据都保留。
- `web/<job>/receipt.json`：下载时的CRC、manifest逐条校验和回收时间；`original-extracted/`原字节不编辑。
- `checkpoint-*.md`：每个自然阶段的可复核交接，按编号保留历史，后续状态不回写历史判断。
- `policy-precheck.json`：候选哈希/大小/单一导入/官方禁词静态检查；不是Lean编译或完整gate。
- `public-nonfinite-opportunity-805.json`：公开发现计划的源码转录机会计数，既不是计时，也不用于未见过的冻结确认样本。
- `nonfinite-oracle.json`、`native-repair-oracle.json`、`sum-repair-oracle.json`：有限原始字整数模型诊断；不代替Lean/硬件验收。
- `w11-codegen-audit.json`：完整原ZIP及实际MainFull C/asm边界的独立复核，链接轻量精选原件；完整110MB文本保留在本地忽略提取目录及E盘ZIP。
- `handoff-materials-preview.json`：当前待验源码与网页原ZIP/报告的精确文件清单；窗口仍在进行，数量及状态以research-status为准。
- `codegen-subject-audit-807-w11.json`：807的8eb诊断重放与W11的60f独立代码生成对象分列，不能冒充同一计时对象。
- `source-budget-inventory.json`：组合接线与256000bytes上限的只读规划，未生成或验证新的组合源码。

完整计时采用原版current public-v2、25配对轮和实际cell_work，不把ns/work直接求和。公共shipped参照提升、私有suite、评测时现任冠军、正式准入与收益各自独立；没有正式冠军结果就不宣称达标。
