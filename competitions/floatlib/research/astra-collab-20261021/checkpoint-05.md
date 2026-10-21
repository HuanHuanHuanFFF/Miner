# R 检查点 05：直接循环已验收，归因收紧；native guard 可去重

2026-10-21 10:55 UTC。

## 已核对 R-01 实际回执

D 的 run 39586444651 对冻结 `cb09e9c6...` 完整 gate 通过：四义务、kernel replay、仅三项允许公理、12类25轮。整体／起始参考0.973328，bmm／起始参考0.933632。独立核验原始输入、verdict、log及C的SHA见 `direct-loop-audit.json`，可运行 `audit-direct-loop.py` 重算。

**关键归因修正**：R-01最初观察的是旧 WordTensor+inline 版本残留通用回调。进一步核对实际 parent `f01-index-hoist-proof2` 的成功 C，发现 parent 已有特化 uint32_t 循环。parent 与R-01的内层都没有 lean_apply/lean_alloc，都有3次Nat加、1次Nat乘、2次数组读取与原有1次add/1次mul。因此不能把本次相对起始参考6.64%的bmm改善称为“消除闭包的净收益”；它包含已有基址外提，未对parent同机配对。直接循环作为已证的后续native状态改写骨架保留，不再把它当成巨大差距解释。

## native 位 guard 的证明草稿

`native-roundtrip-bridge-draft.lean` 给出：

```lean
finiteRoundtrip (x : Binary32)
  (hx : (ExecFloat.Binary.toFloat32 x).isFinite = true) :
  ExecFloat.Binary.ofFloat32 (ExecFloat.Binary.toFloat32 x) = x
```

证明利用真实 pinned Model.toFloat32Model/ofFloat32Model 往返=canonicalizeModel，finite 排除唯一有损的NaN编码，再用canonicalizeModel_eq_self和toModel_injective。NOT_COMPILED，没进入新候选。若R-03的完整gate通过，可用它删除native-add中额外的两次raw等式检查；保留两操作数native finite guard。若具体`tactic change`/命名不合，D用对应原始source修复，不能视为已通过。

与R-04乘法草稿可共用；先等待当前native-add结果，再一次集成精确版本验证，不堆并行变体。
