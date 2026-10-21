# 冻结后静态影响核查与判别观察器设计

时间：2026-10-11 16:18 北京时间。两份候选目录保持冻结，不对native等待中的源码做修改。

## 路由影响（VERIFIED 静态调用点）

`pc_f_record3` 只有 `pc_run1c` 的一个实际调用点；`pc_run1c` 在入口可达的调用者只有以下三个：

|wrapper|route结果k|参数|两份候选的影响|
|---|---|---|---|
|p125_row0|0、1、10|head32768、skip5、lazy0、km=0xffffff00、dp2、minl3|有影响，三字节key结构化数据路径|
|p125_row1|2、4、5、12、14、15、17、18、19、20|head32768、skip4、lazy0、km=0xffffffff、dp1、minl4|有影响，四字节key多种文本路径|
|p125_row6|9|head32768、skip6、lazy0、km=0xffffffff、dp1、minl4|有影响，R22/R23的旧质量改动所在路径|

其余wrapper及fallback既不调用新helper，也不调用改动后的record函数。两份源的 `route` / `format_id` / `bulk_parse` 与实际combo字节一致；未新增按文件名、输入长度或内容模式的分流。

这是一项有意覆盖三个现有PC链路线的机制实验，并非仅限row6。若native在这些路线之外显示token差异，优先检查实际artifact/候选身份及调用假设。编译器代码布局变化可能影响其他路线计时，静态不受影响不等于其总时间一定相同。

## end4的正确性与质量风险

- `j=end-4<lim=n-8` 保证完整key读取有余量；`j>=ins` 保证它没有与本次原头插入重复，且先于原end-1插入。
- 新head最终可能指向新增位置，浅链第二节点也可能被它取代。这是预期搜索行为变化，不能把“保留旧插入操作”误写成“保留全部旧可见候选”。
- 在同一hash槽上，新增记录顺序为原头位置→end-4→end-1。因此新链仍按递减位置搜索；质量损失可能来自浅链预算被新近却较短的候选占用。
- 原 `ae` 在record前预取end位置的hint；record后的 `pc_ahead_fix_m` 会比较当前head[a]与缓存c，任何槽被改写都会重新读取。新插入不要求增加缓存不变假设。
- 三字节key路径的end-4只覆盖末端前三字节；是否比原head/末端跨界key更有用尚UNKNOWN，不因四字节路径的设计动机推断它也受益。

## gap1的频率判别

最小观察器应先在**冻结父路径**上计数，避免把变体改变的访问位置误记为原本的机会：

1. 所有 `pc_run1c` 原主probe失败次数；每个route单列。
2. `p=ls+1` 的失败次数，以及有效的上一match token、d<=32768/d<=p次数。
3. 一个原probe能恢复的match数、覆盖字节、长度和距离码分布；保留4–7、8–15、16–31、32–257、258长度桶。覆盖字节不是编码节约。
4. 可选但非第一步必需：一般R11 gaprepeat在gap>1的恢复机会，用相同父位置静态对照gap1占比；如果gap1已无有效机会，不继续扩大探测范围。

当前实现没有跨轮cache/rep变量。读取out[nt-1]发生在nt合法时，token只是hint；即使给出任意大于阈值的token，距离guard与原字节验证仍决定能否采用。额外true probe次数在每个inter-match literal run最多一次。所有failed heads仍承担gap条件分支，故这不是“只有命中才付成本”。

若原encoder少字节但token增多，可能发生更多短match切碎或块分布变化；先看逐文件字节/token，再分解原协议parse/encode时间。观察器耗时及counter收益不代替原协议配对总时间。

## 准备证明的最小接口

end4：原 `PC.f_record3_spec` 返回 `HeadBound`，无需证明插入质量或完整hash链不变。已有 `step*` / `split` 自动化可能覆盖新增有限分支，但是否真的通过待实际提取和gate检验。

gap1：在 `PC` 命名空间、`f_deepen_spec` 之后且主循环证明之前新增局部step lemma。输入只需与原 `probe_m_spec` 相同的 c<=p、cw字节一致、p+8<=length；不需要输出Decoded不变量，因为out只提供不可信hint。

```lean
-- Interface sketch only; NOT compiled, NOT an accepted proof.
@[local step]
theorem f_find_gap1_spec
    (s : Slice Std.U8) (out : Slice Std.U32)
    (nt ls : Std.Usize) (prev : Array Std.U32 32768#usize)
    (c : Std.Usize) (cw : Std.U64) (p : Std.Usize) (km : Std.U32)
    (dp minl : Std.Usize)
    (hc : c.val ≤ p.val) (hcw : cw.val = word8 s c.val)
    (hp : p.val + 8 ≤ s.length) :
    slot.pc_f_find_gap1 s out nt ls prev c cw p km dp minl
      ⦃ fun r => FoundAt s p.val r.1.val r.2.val ∧
        r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄ := by
  -- Use actual extraction, not this sketch, for the final argument order/body.
  -- First probe/deepen: FoundAt.real, f_deepen_spec, MatchAt bounds.
  -- Fallback: guarded token read, pc_be8/probe_m; zero result is FoundAt.none'.
  -- Existing main-loop tuple fields remain unchanged.
```

草图故意没有编造完成的tactic正文。它用于识别缺口及安排证明投入，不可复制成声称已验收的候选。
