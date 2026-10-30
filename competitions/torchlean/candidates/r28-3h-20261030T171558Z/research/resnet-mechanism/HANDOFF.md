# R28 ResNet A · 已到共同截止，交付入口

实际开始 UTC17:22:10；共同截止20:15:58已到，A窗内2h53m48s。最后新增研究工件20:14:27；20:16后仅最终字节核验/交付。Droot唯一Git/CI；全树仅文件。A当前源码都**未编译、无原生计时**。旧过程在history；当前状态status.json。

| 当前精确源 | 状态与入口 |
|---|---|
| 零跳过 c6a4da97 /252334B | 完整义务声明源，未编译；源码未变。build_zero_pair.py，recipe97fa0af4。 |
| support v3 **00928141 /252238B** | NativeOnly，无新correct。已修奇数通道未用bias/BW越界及v!=词法错误。build_lexical_repair.py，recipe0f109d9e；lexical-repair-receipt.json。 |
| 空间 preferred **ce1a8c2b /255987B** | NativeOnly，无新correct。build_spatial_mixed_zero.py，recipe**0c7333b2**；PREFERRED-SPATIAL.md、spatial-mixed-native-receipt.json列全依赖。入口Submission.rV；full_gate=false/declares_correct=false。 |

父1854/1911已落实：恢复真正Lean参数空白，用无捕获短名腾体积；只要求每个BW.min!=511，允许单项零权重，全零行回原Ybp。其它原finite/narrow/size、偶数3×3、cin≤8、cout≥4、B0≥2/旧bias shift≤76保留。每tile小Nat输入cache、共享权重cache、128逆变换、B0−2重建bias、原raw zW回放和CHW输出。旧11全部runtime/proof保留为R8K/R8P，不移作新kernel证明。

spatial-mixed-model-receipt.json：旧seed42三profile的25个准入卷积、45244输出/舍入前整数匹配，其中9调用含零权重；另有mixed-zero局部−0、全零行和Inf拒绝检查。仍是Python同一证据家族，不是Lean/native。原模型重复读生成器的慢脚本已停止并归档，缓存后8.79s复核；不是算法计时。

成本风险仍明确：少55.6%源乘法，但每coordinate循环6.67–8倍、partial数组分配、Nat getElem!；见spatial-cost-structure.json（旧窄域，核心结构未变）。仅余13B，完整新证明能否装入UNKNOWN；不在成本反馈前扩变体。旧8e5/f59有已确认语法缺陷，5a43是修复但较窄旧域，均保留、不并排队。当前只推荐ce1a。

数学/接口入口ROUTES.md、PACKED-PROOF-INTERFACE.md、SpatialWinograd/WordBounds/Rebase.lean，全为未编译草稿。精确576系数核验；block8有限字模型；父14安全/15溢出raw反例已独立复现。更宽字流水线54708整数/输出和−0/抵消/上下溢/奇数tile另保留。早期v1 JSON的重建明确非原始字节，current v2原件/依赖见spatial-word-pipeline-provenance.json。

收尾新增：sparse-mask-coverage.json完整1024低位状态显示最长零段7，固定CNN权重行≥27不被行非零guard排除；overlap-transfer-review.json给当前空间guard内85bit单乘反例，不能截64位后套overlap32。NEXT-SHARED-SUPPORT.md区分“两输入共享weight”与A“一输入共享两output”的缓存语义、真实payload项数及60/63bit前提。均无新Kernel/CI，不用CI6数据。

raw profile确认分类器另调1×1，3×3占所测入口互斥时间约75.65–78.85%，不是整模份额。18:15原件Res64的19.015%只为跨配置/报告规划推断；current-target-snapshot-review.json。接受D的Mobile/Mixer优先级，不擅派CI；未读确认数据。本地无Lean/native构建，token/cache用量UNKNOWN。持续至20:15:58，之后只收既有作业/交付。

最终记录FINAL.json；源码/范围final-source-scope-check.json；20:09干净目录重建portability-preflight-receipt.json；自有公开文件清单public-manifest.json。当前无A在途作业，不请求新CI；后续需新授权窗口。
