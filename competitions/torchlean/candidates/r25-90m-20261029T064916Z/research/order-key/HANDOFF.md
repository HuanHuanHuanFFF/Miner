# R25 order-key 当前入口

08:04新薄接口已交，待阶段读取：`target-bridge/ContractWordBridge.lean` 4295 B／SHA `9a79cd70b8c33dd28cf15e97850264aa5892fc8bd9e75b42412ab754c6811d9a`，仅ContractExact、12审计根。它用固定FloatLib `ofUInt32_roundDyadic/roundRatScaled` 接到真正 `ExactRuntime.toWord`；再用官方 `finishWord_of_ne` 接非零精确总和，并独立处理零符号；`dotOf_of_native_nonzero`直接使用实际输入的官方dotState.exact。API／条件／仍缺producer同值及零旗标见 `target-bridge/API-BOUNDARY.md`，原字节blob/源hash/原policy AST PASS见该目录receipt.json。可选den1薄组合737 B另需旧R24DyadicAgreement，未并入core。所有新Lean仍NOT_RUN；未建新Kernel/CI，policy1冻结原字节未改。许可未知官方全文在已核Git忽略的source-private；MIT Agreement另存公开源。续段首tool07:56:17 UTC，目标08:08前交付已达到，但不宣称项目或1.5h窗口完成。

08:07薄接口最终核对：core补显式destination State Fmt后的身份以以上9a79cd70为准；`DotZeroBridge.lean.inc`另补actual dotState零分支，1451 B／b7d892cb461fb30bb4656c61f8ab4042bb6d39e3b0df9f09a867b45e575867ee，精确保留sawFiniteTerm与allTermsNegativeZero。新增MIT Reduction/Proof原字节blob已核，receipt含4份固定源；零后缀与den1后缀各自NOT_RUN，未并入冻结policy1或任何大Kernel。下一步优先实CI错误；无错误则源码整理至共同截止。

08:13本阶段保存：`phase-status.json`记录三段实际执行窗口和其间空档；target-bridge最新08:11:29静态核对保持core9a79cd70／12roots／4fixed-source-blobs／原policy AST PASS，Lean仍NOT_RUN。policy1仍82399ee3，尚未收到本方可读取的第二CI原错；按真实错误可再次续修，共同08:19:16不延，不把等待空档计作持续执行或宣称整轮完成。

07:38 当前待验版本改为 **`policy1/Kernel.lean`，64728 B，SHA-256 `82399ee3da291a1ad82dbb0432bc2c5bd2a4097db9dcc37bdbca111ff4867111`**；29个审计根与v2完全相同，清单及原规则回执在 `policy1/receipt.json`。真实run40834710293/source823aa68b在policy拒绝v2，未进入Lean。仅替换1166行的一句注释，去掉触发词法检查的文字；所有证明／执行正文及规范化代码不变，v2原字节保留。用D保存的固定官方sandbox.py SHA ba8e1a0f23692928f080ad278c35b36493199fb90e3768f90710b85ffef84126、duplicates.py SHA e1859b11011797b5012795d067383ef619a291769ea40dd0cd017791f127f4f8原AST函数重现v2拒绝，并验证policy1 intake/policy PASS。Lean／重放／公理审计仍NOT_RUN。没有修改预测的mixedcast、gate或资源。本次续修首tool07:37:24，回执07:38:10 UTC；此前空档不记持续执行。

此前07:24阶段源 `v2/ActualCheckerContractOnly.lean`（26259 B，SHA-256 `c57a8c1ef5579753e31911f7c98305737a43d0c73d2c2890c9389c2a9114e995`）及分离的 `v2/OrderKeyContractOnly.lean`（15770 B，`1359292082474997b2a3ce7292abcbd84648ddba5ce1eb84d267db47d590b1fd`）保持不变。仅 import ContractExact；固定 Lean/FloatLib 见上级 controller/pinned-source-receipt.json。原 v1 多 import 探针及单 import 首稿保留。

- 新义务：实际 UInt64 sign-XOR key 的有限字严格比较运输，包含 raw binary64 正规、次正规、正负零解码，不借用旧 Float.lt 草稿。`orderKey_lt_real` 的“至少一端非零”必要；actual checker 组合已在源码内部由 q 正规指数守卫导出中点有限且非零。
- 实际表达式：`ActualRuntime.lean.inc` 从旧 `PortableF64Dot.lean.inc` SHA `dd775683cade6e575dc6f0684f9216742e1c772c3cf7460b0c53c54e4e3eff04` 逐字截取。`certify_eq_runtime := rfl` 绑定实际 checker。最终根 `Submission.R25Checker.actual_acceptance_bounds` 给实际 `sum±radius` 端点落入实际 raw 中点字。
- 候选载体：`v2/Kernel.lean` 64745 B，`ba634fe6af6bcf84c07ad248457ac120941da40bc601f893e07f356f0297c967`，保留官方 incumbent 38506 B 精确前缀，未换正式 kernel。`v2/manifest.json` 合并29个审计根；carrier 构建通过不代表证明接受。
- 已执行：精确 Fraction 小模型，7-bit 全112有限字6216有序对及 binary64 224字24976有序对，唯一 key 严格而实值相等对为 -0/+0。`small-model.json` 记录范围，不是全输入证明。新增6份固定公开源逐字 Git blob 验证见 `source-receipt.json`。
- **全部新 Lean、重放和公理审计 NOT_RUN。** Droot 统一 Git/CI；本方不运行本机 Lean、不改 gate/官方源、不正式提交。v2只修静态脚本问题；等待真实编译日志决定下次修订。实际 producer enclosure、midpoint→rounder cell、完整 kernel/model 验证仍未闭合。
- 接合后续：`ProducerInterface.lean.inc` 仅3个薄包装根（NOT_RUN），将明确的实际 `sum±radius` enclosure 前提与 checker 接受组合为精确 S 的严格 cell bounds。暂不追加进 v2 冻结待验源。
- first tool `2026-10-29T06:52:57Z`；共享窗 `06:49:16—08:19:16 UTC`，不延长；本方未发CI。tokens/cache/CPU UNKNOWN。阶段：固定源→07:01首稿→07:03单import→07:07checker→07:10 v2静修；当前等待实错并处理相互独立的接口整理。

07:24阶段回执：`stage-verification.json` 新鲜核对6份v2文件哈希、单import、原incumbent前缀、dd775 runtime逐字抽取、6份固定源Git blob及5脚本AST，静态PASS，Lean/gate/replay/axioms仍NOT_RUN。`checker-boundaries.json` 2540个精确有理数边界样本PASS；`RounderInterface.lean.inc` 保存可选actual checker→旧R24RawMidpoint roundRatScaled组合，未纳入v2且其旧证明闭包未验。当前只待D的v2实错，阶段执行窗06:52:57—07:24:23，后续空档不记持续执行；共享截止不变。重点看magnitudeReal混合Nat/Int指数是否需要显式cast，实际日志确认后再修。

