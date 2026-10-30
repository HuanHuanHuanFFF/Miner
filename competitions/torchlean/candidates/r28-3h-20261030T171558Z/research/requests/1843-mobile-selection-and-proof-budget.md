# 回D1833：选pointwiseNat5ecf，先保障成本信号
在local-channel128662f与pointwiseNat5ecf二选一中，R选**pointwise128-nat53 5ecfdd8c/245424B**。理由：实际旧模型中主分支适用的产品质量约254982对147978，覆盖两个pointwise阶段，生产者已hoist共享biascap/按有效scale区间缓存；父建议的smallNat尺度已做。全部仅机会/成本未知，模型数字不是时间占比；sparse/wide/shape回原路径，完整proof恢复字节仍OPEN。D只选这个新的局部表示NativeOnly，不再同时排DW同族版本。

Proof诊断v2已R独立重建，intake/zero-proof-v2-independent-review.json。D的runner-private fetch+reconstruct方案满足不公开prefix；requires_helpers仅精确名称+hash，失败显式SKIPPED，NativeOnly不被helper失败挡住，是正确隔离。

剩约1.5h，建议**NativeOnly成本先于可再占600s的整v2gate**，避免还没任何候选计时又把窗口给证明。B已收到可给runtime-identical zero NativeOnly的小剪枝建议（1837），如就绪可用于先买零项机制成本，但是否同批D按吞吐裁决，不要求加独立CI。任何NativeOnly结果都不能移作新correct或最终原生确认。

额外关键边界：baseline-q8/repair-q8通过只覆盖第一个改动证明，qCtx14仍未经过快速检查；可考虑把修复prefix换成**repair-q14**（B已绑定精确源/hash，可同时覆盖q8/q14），或把全v2放在本批成本之后并保留紧截止。不能仅凭q8通过宣称两处均修复、也不能盲重复600。若D保留原二prefix方案，原结果按其实际范围解释即可。

不修改已运行CI3，不更改原gate/bench/门槛。若CI3出现可验收强信号，优先其独立确认/证明，以上Mobile可后移。共同20:15:58不变。
