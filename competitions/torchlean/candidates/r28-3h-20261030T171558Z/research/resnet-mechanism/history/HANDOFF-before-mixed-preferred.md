# R28 ResNet A · 当前入口

**最新空间源：5a43cf03 / 255990B，recipe 71ae6d94。** 固定 Term.argument 必须有参数空白，旧8e5/f59的空白压缩无效；新 build_spatial_parser_repair.py 恢复原合法空白，仅缩短新 helper 名称保住体积。REQUEST-ROOT-SPATIAL-PARSER-REPAIR.md / spatial-parser-repair-receipt.json 为准，入口 Submission.rV，NativeOnly 无新 correct。与既有模型的算术表达式严格对齐见 spatial-v3-model-link.json；编译/速度仍未测。support009不受参数空白问题影响。

**19:03 词法修复优先：** 固定 Lean4.34 将 `v!=`/`w!=` 读成变量 `v!`/`w!`。旧源未改；新 support **00928141/252238B**、空间 **f59a9b41/255963B** 各只补一个空格，统一 recipe **0f109d9e**。精确依赖/哈希见 lexical-repair-receipt.json、REQUEST-ROOT-LEXICAL-REPAIR.md。仍 NativeOnly，无新 correct；旧已开作业不取消，不并排同族版本。下列历史模型描述算术意图，不代表旧源编译通过。

实际开始 UTC 17:22:10，共同截止 20:15:58 不变。Droot 唯一 Git/CI；全树仅文件。**A 的所有候选目前均未编译、未获得原生计时。** 历次详单已存 history/HANDOFF-before-current-index.md；状态见 status.json。

| 精确产物 | 证据与边界 |
|---|---|
| 零跳过 c6a4da97 / 252334B | 完整义务声明源，未编译；源码未变。recipe 97fa0af4，zero-pair11-receipt.json。 |
| support v2 a498d9b7 / 252237B | NativeOnly，无新 correct。已修奇数通道未用 bias/BW 越界读取；9216 个有限状态、272 个索引检查。v1 保留，不并排队；REQUEST-ROOT-PACKED-V2.md。 |
| 空间 8e5b27c0 / 255962B | 完整模型 NativeOnly，无新 correct，full_gate=false。旧 11 全部 runtime/proof 保留为 R8K/R8P。recipe **ef44083d** + compact8863afd1；旧 756a7799 仅 Windows LF 输出不同，transform 字节完全相同。SPATIAL-NATIVE-READY.md。 |

空间源只覆盖原 narrow/finite/size、偶数 3×3、stride/pad=1、cin≤8、cout≥4、真实权重非零、B0≥2/旧非零 bias shift≤76；其它调用原 Ybp。每 tile 小 Nat 输入缓存、共享权重缓存、128 位逆变换、**B0−2 重建 bias**、原 zW 符号回放。生成表达式模型匹配旧 seed42 的 28584 输出/16 调用及 100 对变换，仍不是 Lean/native。**成本风险：** 源乘法少55.6%，但 fuel 循环6.67–8倍、partial数组分配与 Nat 边界检查增多。仅余38B，完整证明能否装入 UNKNOWN；不在成本反馈前扩变体。

数学入口 ROUTES.md、PACKED-PROOF-INTERFACE.md、SpatialWinograd/WordBounds/Rebase.lean；所有 Lean 草稿未编译。精确576系数核验、block8有限字模型、父14安全/15溢出 raw-word 反例已独立复现。完整字流水线匹配54708个舍入前整数/输出及 −0、抵消、下溢、上溢、奇数 tile。旧 v1 JSON 曾被覆写，其重建明确 NOT_ORIGINAL_BYTES；当前 v2 原件与依赖哈希见 spatial-word-pipeline-provenance.json。

已读原 profile f45ee39d：YlN 分类器另调一次1×1，所以真实3×3为所测入口互斥时间约75.65–78.85%（调用图推断，非整模份额）。18:15官方原件当前 Res64；19.015%为跨配置/报告规划估计，不是同机差距，见 current-target-snapshot-review.json。父已接受 sparse 基线纠正：原11实际36个scalar乘法，18属于理想/已过滤基线；冻结空间源仍保留其保守权重 guard。

已处理至1843请求，接受 D 的 Mobile/Mixer 优先级。READY.json / CI-REQUEST.json 仅列可选择的精确成本源，未擅派发；所有确认数据隔离。Token/cache 用量 UNKNOWN；A 无 CI、无本地 Lean/native 构建。继续关键复核/反馈至共同截止，之后仅既有作业回收与交付。
