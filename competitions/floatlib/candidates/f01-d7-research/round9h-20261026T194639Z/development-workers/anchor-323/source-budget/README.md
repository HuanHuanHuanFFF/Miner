# Jam17注释/空行预算：保留原始notice时不足12,000 B

UTC 2026-10-26 21:58:58接手，预算20分钟。只新增本子目录的脚本、草稿与回执；未改估算器、源候选或既有补丁，没有Git/CI/Lean执行，未读取40407333869的输入或性能。

原件：`competitions/floatlib/candidates/f01-r19-dev-jam17-public1/Kernel.lean`，254,877 B，SHA `b2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff`。完整D仍与原件绑定，本草稿不替换它。

| 仅删注释/纯空行的策略 | 剩余B | 省下B | 再加任务给定11,068 B | ≤256,000 B |
|---|---:|---:|---:|---|
| 保留两份原始notice | 251,410 | 3,467 | 262,478 | 否，超6,478 |
| 保留每份不同notice，仅去掉完全相同的重复副本 | 246,806 | 8,071 | 257,874 | 否，超1,874 |
| 删除全部注释的机械上界，包含最后一份notice | 242,202 | 12,675 | 253,270 | 是 |

**结论：** 全删注释在纯字节层面可超过12,000 B；但该上界会删除最后一份原始MIT/第三方notice，未将它作为保留intake头的可用草稿。保留一份完整原始notice后只能省8,071 B，离12,000 B目标还差3,929 B；即使只要求容纳11,068 B增量，也还差1,874 B。本任务据此交付有保留头约束的负结果，不扩大到定义/定理裁剪。

源中有16个block comment，共10,969 B；其中两份100行notice原字节完全相同，每份4,603 B，SHA `5e94218c8d2ec02ec51bb564393399e9cea00a51e9ba4322f81e5a3a4e372965`，原位置695—794及998—1097行。其余14份注释合计1,763 B。原件有1,738个纯空行；这与注释内部空行有重叠，不能把两项直接相加。表中为实际删除后重数的UTF-8字节。

已读取现有`astra-workers/exact-arithmetic/source-budget-pruning.patch`（SHA `90591e63deeaf6971987ca2362ce16038a452e1487bd929dd657e4c9eae3650c`）。它包含31条定义/定理删除行、20个diff hunk，属于另一类裁剪；本任务没有重放它，也没有重复删声明。

## 本地检查与精确逆映射

[脚本](analyze-comment-budget.py)是针对本原件的保守lexer：支持嵌套block comment、line comment、转义字符串、raw字符串和引号标识符；未支持的插值字符串明确拒绝。会保留删除后可能导致token粘连或改变行首token列的inline comment，不插入字符、不改非空行缩进或尾部空白。当前原件的字符串/raw/引号标识符/字符literal数量均为0，相关保护由独立小fixture覆盖。

[草稿](Jam17-comments-emptylines-draft.lean.txt)只采用第二行策略，SHA `60ca7de974c96947c2594416d425fe9eb70eaaef39088b15493e489b49da0382`。它保留原始`import ContractTensor\n`、一份完整notice，以及全部code token。文件位于worker子目录且后缀为`.lean.txt`，不是参赛候选。

[独立复验](verify-source-budget.py)从original byte ranges重放删除，再仅用草稿+[逆映射](inverse-deletions.json)恢复原件并逐字节相等；映射包含原始起止byte、草稿byte偏移、删除原字节base64。没有替换/新增字节。58,153个保守token分区一致；5,141个非空token行的相对缩进/原前缀一致，进一步核对所有token的起始列均相同。`def=149`、`theorem=399`、`abbrev=12`、namespace/end/import/open等计数全保留，未添加options。namespace文本篡改和缩进篡改的负测均被检测。草稿剩余非notice注释及notice外纯空行均为0，8,071 B是该原始notice完整保留策略下的实测删除上限。

这些是本地字节/词法/layout检查，不是Lean官方前端token结果或kernel gate。所有草稿的Lean编译、完整gate、实际性能及正式提交状态均为**NOT_RUN**。原件与既有patch哈希在复验后保持不变；删除内容可完整恢复。

复验（仓库根）：

```powershell
$p = 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-workers/anchor-323/source-budget'
python -B "$p/analyze-comment-budget.py"
python -B "$p/verify-source-budget.py"
```

完整注释盘点、三种策略及行映射见[budget-receipt.json](budget-receipt.json)；独立正向/逆向回放与布局结果见[verification-receipt.json](verification-receipt.json)。本目录产物哈希见`MANIFEST.json`。
