# R3 最终研究交接：当前成果冻结，D继续最终CI

本轮授权已核对至用户原话“开始新一轮 协作推进1h”。共同窗口为2026-10-22 04:36:27—05:36:27Z（北京时间12:36:27—13:36:27）。按D在状态中要求，R于05:30前冻结交接；这不是整个一小时任务提前结束。D继续收齐已启动的完整验收和独立确认，必要回收可自然越过研究截止，不取消作业。

## 已落实的核心成果

R的首稿 `f01-r3-packed4-usize` / `4d37c26cde7b2119162dd030f1ec48335e044f459db89832192069e4668cc67b` 已于04:44前交出。原稿在run403仅剩一处uget/get定义等式未收尾，原错误与源保留；D补最终rfl并完成标量组合后，4路精确源 `e54f091df8f0b42e375c3fe0456f1cc0446be7bf8a93db53b8632df4a181472a` 已在run405完整gate通过。D的8路适配 `9a4b1ddab0da0b2c798440eca62a2039096a0669d2fa638b6a6bc041a534cc54` 同批完整通过。

实际生成C确认 count/base/k 为机器字；热循环没有Nat add/mul、USize转Nat或Array.size读取，A/B各一次uget；4/8个原生float累加器，结果结构只在终点构造。不能从C直接宣称SIMD或确切机器加载次数，汇编尚未核对。

run405三类完整bmm归一化耗时的算术平均：4路USize **1.2509746667 ns/MAC**；8路Nat **1.3236953333**；8路USize **1.187918**。整包随附参考ratio分别 **0.2708161492 / 0.2696848850 / 0.2666215210**。这是同批每份候选各自对随附参考的发现结果，最终独立确认仍归D；部分参考慢样本明显，均保留，不据小幅整包差异宣告稳定排序或冠军晋升。

完整精确路径、receipt/C哈希、逐类数据与限制在 `matrix405-codegen-and-results.json`，解释见 `checkpoint-04.md`。新R原稿没有被覆盖成D修复稿。

## 网页资源与新增原件

已恢复旧W03b的超时任务，并复用现有6 Pro会话完成一项窄的全局边界证明；直接研究、候选冻结与实际CI反馈同步进行。两项现在都已完成下载，不再有本轮待回收网页。

| 原件 | SHA-256 | 当前验证范围 |
|---|---|---|
| `E:\Download\FloatLib-R2-W03b.zip` | `654bdd25517ed97367e1eb26777b4607cabb9f8bd0e304ae71144421a9df1525` | CRC及16项清单PASS；D另核17个解压文件。转换证明18558 bytes，独立policy PASS，Lean NOT_RUN。 |
| `E:\Download\R2-W03b-report.md` | `86bb36e0b8b0d4137e32e11a0ba92bdb131f924db87a6608cb265b6ddd1c16d4` | ZIP报告成员逐字保存。 |
| `E:\Download\FloatLib_R3-W01_WholeCallBounds.zip` | `3afc5d2d28e4077e507df0148ebf390a85cd5ca20d67ae422c194a5628747805` | CRC及18项清单PASS；辅助片段9758 bytes，Lean NOT_RUN。 |
| `E:\Download\FloatLib_R3-W01_Report_zh.md` | `b29d39bf3a2ef8c166f625206e9f397994ca62eb10bdd4d9506ed508ab71fa6f` | ZIP报告成员逐字保存。 |

原件和许可均保留在R3的 `web/`，下载包脚本未执行；旧R2文件/原始回执/当时pending观察没有改写。当前完整E盘文件清单见 `download-index-final.json`，包含旧索引与本轮新增原件的重读核对。网页交付截图只留本地忽略目录。

W03b是unpacked-rounding转换证明的另一完整尝试；D正在采用的W01c Model路线已实际编译到无条件convert_eq，因此本窗不再重复编译这份替代稿。不能把网页“证明写齐”升级成通过。

## 保留的下一起点

`f01-r3-packed4-global-guard/Kernel.lean`，88944 bytes，SHA `abb650a68efb5e1c70f6bfa746670594d7d9c2ce62386da2370bbd744c1c043d`。从D的e54父本接入网页地址界证明，类型与接口已适配，官方纯intake/policy PASS；Lean、完整gate、性能均NOT_RUN。原始源码与适配片段分开保留。

机制是由矩阵形状与nativeA长度推出每行的n/base/末地址界，叶子直接调用同一机器字within，将每tile四条件改成一次全局长度检查。该数学边界不依赖lane宽度，后续可供D适配8路；当前按D决定停放，保留最终确认时间。不能把检查次数减少直接当收益。

## 尚由D完成的验收

- 冻结8路USize独立完整确认：run408 `39727625634`。
- 修复命名空间后的真实求和/最终整合包已在run409 `39727658622` statement通过；最终包精确源为 `6744be2bd784bea7a7e347d68f813bc865d2d18abab87f19fa37aec8a8c2c1f7`。其完整gate、实际公理依赖、速度与独立确认应以D随后实际回执为准，不以statement通过代替。
- 正式提交和线上冠军晋升均未由这些公共参考结果建立，原目标仍未完成。

R未进行Git/CI操作。D保留唯一Git/CI协调权和最终版本选择权；R状态入口 `research-status.json` 已引用各检查点与精确工件。R停止新增方向，既有源、失败和负例均可继续使用。
