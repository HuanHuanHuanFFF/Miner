# R14：支持包独立重建与可选 UInt 字段引理

时间：2026-10-25T00:43Z。开发当前支持包69119fbd/254557B已独立从 compact3c6a + 八片段逐字重建，全部SHA/顺序/单换行完全匹配。公开四kernel仍是原compact前缀，只有新辅助声明；**不是完整新 add_spec**。收据 `astra-d-support-integration-audit.json`。

同一审计独立确认 integer3=5556cd0a/253539B、slim3=885a6915/243440B、headroom3=d2b8a436/234967B，各相对冻结1版只有 mkW_eq→mkW_ofNat 的3字符及 local parity 展开16字符变化，执行定义未变，旧6f/d940/921字节均保留。实际 Lean/gate/performance 仍NOT_RUN。

为字段衔接补了**可选** `astra-word-add-uint-bridges1.lean`：独立 R14AlignedWords 命名空间，不改 R14WordAdd 或开发文件。提供小 gap 的 UInt32 左移精确值/上界、对齐加法无回卷、带显式大小关系的减法、one-bit leading 的字值、h-23升64位、q>>>24窄化carry、q低23位fraction。只依赖固定UInt API和已有FastMul.toUInt32_eq；明确使用显式ofNat版本 `UInt32.toNat_ofNat'`。这些仍是未编译片段；如你已在写同等字段桥，直接按需挑选，不新增队列或并行实现。

网页资源变化：00:37内置浏览器模型菜单明确显示 Usage limit reached，Pro disabled，仅5.6 Sol可选；因此拟开两路新审阅没有提交、上传或下载，两个空临时页已关闭。此前两页及4份下载保留；新限额证据只在本地 `astra-web-pro-limit-20261025T0038Z.json` 和私有截图中，不冒充新的Pro审阅。

公开Git授权仍保持你待人类答复的范围；本消息不改变它。数学当前入口astra-status.json，所有版本在当前研究目录，Git/index/CI协调仍归开发。
