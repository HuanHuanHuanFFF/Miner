# 来源与许可说明

完整来源地址、提交、Git blob、SHA256 见 `public_sources/source_manifest.json`。

## FloatLib

固定与对比源码均标注 MIT，Copyright (c) 2026 FloatLib / Authors: FloatLib Team。
原始许可证保存在 `public_sources/floatlib_fixed/LICENSE` 与对比目录对应文件中。
本轮候选调用固定库的精确表示定理；没有复制新版七定理块作为候选新依赖。

## 公开父源 Kernel

父源是 Miner commit `46a9f085db7634a22324d25623f715829f7074f9` 的 `f01-d2-final-finite/Kernel.lean`。
其完整 Conjectures.io、FloatLib、TorchLean MIT notices 随摘录的 `NativeProductBridge.lean` 一并保留，也在最终单文件中。
复用父源有限原生乘法桥所依赖的三个既有 targetExponent 引理，保留父源记录的较新 FloatLib 来源归属；这不是本轮新移植或依赖升级。

父源给出的许可通知也说明官方合同、内核片段与其引用项目的归属。官方固定提交的根目录未发现独立 LICENSE 文件；本报告的相关许可依据是给定公开父源内嵌通知，不伪称下载过该固定提交的根许可证。

## Lean 与 Mathlib

Lean4.34 与固定 Mathlib 源码适用各自 Apache 2.0 通知，原始许可证分别随 `public_sources/lean4/LICENSE`、`public_sources/mathlib/LICENSE` 保留。
本轮新证明调用其公开引理，没有改变固定依赖。

## 研究代码与审计

`WordFields.fragment.lean`、Model 组合和整合接口为本轮生成的研究尝试；W01b 基线按字节保留。所有新 Lean 文本未经实际编译。来源源码中的命令、定义或属性不代表允许把它们新增到候选；官方文本政策检查只应用于明确列出的候选文件。
