# 完整公共 BMM 的成本前提与证明界面

起点是 R21 `4e36c931`，19 根声明 / 两模块回放 / 允许公理已有原回执；该通过范围止于任意 p 的完整两行调用。本轮公共 `059f0401` 复用其运行体，新增 batch 内 pair / 奇尾 writer 及公开 root。新组合未编译，速度 UNKNOWN。

## 先决证据

固定 Lean 源位于 `round45m-20261027T074758Z/research/source-intake/lean-runtime-293d5d0c/Array.Basic.lean`，commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`。公开一手源：https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Array/Basic.lean 。作者与 Apache 2.0 头保留在原件。

`mapIdx` 经 `mapIdxM` 进入原库 `mapFinIdxM`；后者的后端先取元素、清槽，再执行回调并写回。候选没有新增 unsafe / implemented_by，也不改变库属性。这个事实不保证实际生成 C 会复用 Cell：还要查专化是否保留、旧 state 是否捕获、元素别名和输出阶段的引用计数。

`advance` 回调不捕获 state，只使用传入 Cell 与 a0 / a1 / B / rowB。首次 replicate 是 p 个指针共享同一个零 Cell。首 k 分配、稳态 Cell 更新、闭包捕获 / Float32 装箱、两个 slot store、最终两遍 finish、NaN raw replay 和 state 释放均计入实际调用。

## 应决定下一步的结果

1. 若实际 caller 每 k 整表 COW，或每槽持续 Cell / closure 分配吞掉 raw codec 删除的收益，暂停这份表示；不以宽度阈值或换 seed 挽救。
2. 若可看到复用，完整双行计时也必须包含输出分配、replicate、所有 k、两行 finish 与释放；controlPair 是逐点 DirectContinuous 类参照，不能代替保留 B2 路由的整包比较。
3. 成本有信号才推进当前公开稿的完整 gate / public-v2 与新 runner 确认。当前 v1 无阈值，窄 p 和零尺寸路径的成本可能不同；语义桥先对所有尺寸成立，策略应另留精确版本。

## 证明审查

每个 pair 的局部行 i=2g，g<m/2，推出 i+1<m。因此两行 `floor(r/m)` 均为当前 bi；B 基址必须 `bi*n*p`。奇尾只在 m%2=1 时写 m-1；m=0 无 pair 与尾，p=0 每行 emit 空，n=0 保留原 +0 初态。`streamedRows_eq_control` 保留精确 k 序、两遍 finish 和 NaN 原始回放。

4000 形状的有限符号检查覆盖布局与序列，并抓住已知跨批变异；浮点语义与 Lean 接口仍由实际 pinned runner 的声明、回放和公理审计验收。整合原稿 c3c3 含旧未编译 writer，不称其为已证明。
