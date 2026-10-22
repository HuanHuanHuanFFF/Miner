# R4最终研究交接：两份完整微块证明通过，均未取得采用优势

共同窗口07:52:04—09:52:04Z（北京15:52:04—17:52:04）。候选已冻结；16累加器最终审计和本交接于09:32Z落盘。D继续最终组合验收、独立确认并自然收齐所有已启动CI。这不是整个两小时任务提前停止。R不新增方向或候选，不操作Git/CI。

## 精确成果与决定

| R原始候选 | SHA-256 | 真实结果 | 采用决定 |
|---|---|---|---|
| `f01-r4-tile2x4`，157441 bytes | `7de60fa52c445fa31aad8a0b9e4143933e0c0b26cdebf07d12805c3fa72a5476` | 505首次statement PASS；507/509完整gate PASS；509同批bmm约比父本慢9% | 停放当前版本，保留证明和负例 |
| `f01-r4-tile2x8`，145922 bytes | `8c0c195472f191d54c649d3c2dc9c4ad3ab68ef3c248249234ac20b6448cb2b5` | 510首次statement PASS；512完整gate PASS；同批bmm约慢0.6% | 没有足够采用优势，不晋升 |

两稿均从已两次完整通过的6744be2b出发，保留add/mul/解码sum；低/高投影分别连接既有dot4/dot8，机器字循环另证等于Nat参考，合法q按行对及列块映射回原地址。完整规格没有新增sound前提。NaN/Inf/±0/subnormal、空形状、n=0及奇数尾行仍在原合同内。原稿与原始回执保持不变。

509同批三类bmm算术平均：父本1.1891186667 ns/MAC，2×4为1.2945106667；10列为1.1356826667。512同批父本0.900612，2×8为0.9066006667；bmm参考ratio分别0.02247789042与0.02261401453。不同批/CPU数值不合并排序。2×8整包ratio0.238403低于父本0.239903，不能将这点差异归因成bmm改善，因为实际bmm分项略慢。

精确逐类数据、原始receipt路径/SHA分别见 `first-microtile-results.json` 与 `tile2x8-final-results.json`。这些是对随附参考的完整验收和分项比较，不是对线上冠军的直接测量，也没有正式晋升证据。

## 实际C和对象汇编核实

2×4：C为3次uget、4个B字段、8mul/8add；真实诊断对象主回边0x90—0xf9自动推进两个k，有4mulps/4addps，两个4float累加向量，B向量确实供两行复用。热回边未见call/FMA/rsp内存。完整调用仍回归，不能把它解释为“SIMD没形成”；具体成本归因UNKNOWN。见 `tile2x4-codegen-audit.json`。

2×8：C为3次uget、8个B字段、16mul/16add、仅终点F16构造、无Nat add。诊断对象主回边0x80—0xc9每次推进一个k，有4mulps/4addps，累加状态在xmm0/xmm4/xmm6/xmm7四个向量中；未见热回边call、FMA或rsp内存。函数入口读取额外浮点ABI参数、终点分配前后保存寄存器位于循环外，不能误报成热循环spill。它实现了预期的4向量累加和B复用，仍未形成完整调用收益，后续不再无证据增加块宽。

对象边界：这些对象来自同源码、未改固定构建的诊断statement重放，不是已经清理的计时gate对象；相关对象、文本和C的精确SHA已绑定在JSON中，不混同两种身份。

## 网页6 Pro原件已全部回收

本轮在直接证明/候选/实际反馈推进期间，复用现有6 Pro会话做独立尾部/映射/计数审查。原件：

- `E:\Download\FloatLib_R4-W01_RowPairAudit.zip`，35371 bytes，SHA `b9680c6fe74ff1cd323a839db540777315c26f9eb1ab9ca0cd48724a9699e2a8`。
- `E:\Download\FloatLib_R4-W01_Report_zh.md`，SHA `dc8cf4e8a0aca52ee0f5454e36c39443b7058744dd5a41d7c85d8c39cd2dd986`。
- CRC、17项清单及报告副本已核对；18个原文件完整解压于 `web/R4-W01/original-extracted/FloatLib_R4-W01/`，下载代码未执行。
- 地址辅助稿 `RowPairBounds.lean`，4693 bytes，SHA `71c868bb29f5cadad49046c9f84178d299b82264e3e7e774671c61cc0a8c500b`。它自身的Lean/公理检查NOT_RUN，不把网页论证替代本机候选的真实gate。

审查未将“未观察第二行读到下一批次非零值”本身误判成输出污染，而是明确独立累加器、有效lane选择及回退隔离的前提；另保留17个见证输入和跨batch平坦配对等反例。NaN精确payload由固定软件参考确定，不猜传播规则。网页计数也明确只是4个不同B字段各取一次，不是实际机器加载次数。

本地有限布局诊断1848形状、34650输出及103950地址对通过；只有布局/顺序证据，不替代Lean或浮点执行。源码、构造器完整扩宽生成脚本、计数及反例可复用。全体E盘已回收原件清单见 `download-index-final.json`，原R2/R3内容及当时状态未改写。

## D继续的工作

D已选择10列与坐标解码内联等实际更有利的组件，正对final-native/final-lowmul冻结组合做完整验收及后续确认（当前已知run39755371552）。R没有复制这些组合，也不替代D作最终采用。以 `coordination/development-status.json` 的后续原始回执为准；R唯一入口仍为本目录 `research-status.json`。
