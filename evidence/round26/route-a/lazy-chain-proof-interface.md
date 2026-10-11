# A8 证明接口静态检查

冻结 Rust `29eeab8a83b7c22d56d5c28986198b735ced2ee3199aebf71164b5198eb71ec4`。原 Lean `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` 尚未适配。以下只是源接口审阅；没有生成新 Parse.lean、运行提取或完整 gate。

新 helper 不需要证明 hash/prev 内容正确，也不需要证明 pc_gain 给出最优压缩。它只从三个已经验证的 offer 中选一个。应保持原 `probe_lazy_spec` 的完整后置条件，而非只留下 FoundAt：后续两次 `pc_gain` 还需要长度、距离上界。

预期的局部定理形状（参数顺序必须以未来实际 Funs 为准）：

```lean
theorem r26_lc_probe_spec (s : Slice Std.U8)
    (prev : Array Std.U32 32768#usize)
    (c : Std.Usize) (cw : Std.U64) (q l dp : Std.Usize)
    (hc : c.val ≤ q.val) (hcw : cw.val = word8 s c.val)
    (hq : q.val + 8 ≤ s.length) (hl : q.val + l.val ≤ s.length + 1) :
    slot.r26_lc_probe s prev c cw q l dp ⦃ fun r =>
      FoundAt s q.val r.1.val r.2.val ∧
      r.1.val ≤ 258 ∧ r.2.val ≤ 32768 ⦄
```

已有接口在 `references/round26-public-641/Parse.lean`：

- `PC.be8_spec`（1485）需要 `i+8≤length`，并非任意索引的无条件 word 对应。新 `c2<c≤q` 和 `q+8≤length` 足以给出该前提；c3 同理。不要遗漏这个读取边界。
- `PC.gain_spec`（1765）需要 length≤258、distance≤32768，保证运算安全，后置条件是 True。它不能用来声称比较保持任何真实编码最优性。
- `PC.probe_lazy_spec`（2434）接受 c≤q、源 word 一致、q+8≤length、q+l≤length+1，产出上述 FoundAt 和两个上界。
- `PC.f_deepen_spec`（2791）给出“可信 MatchAt 与不可信 prev 提示”组合的同族先例，但 A8 用 FoundAt offer 选择，不能直接把它当新 helper 的证明。

新 helper 没有循环或写入。两次 prev 索引的余数都小于 32768；u32 转 usize 保留值由既有平台界支持。每条严格下降分支单独建立 `c2≤q` / `c3≤q`，读取 word 后调用原 probe。每次严格 gain 选择保留被选 offer 的三个后置条件；score 的数值正确性无需成为解码前提。若 proof automation 无法自动拆 tuple，按原 `f_deepen_spec` 的 tuple 解构方式分开结果和后置条件即可，不能提高顶层假设或修改 obligation。

唯一既有循环接口变化是 `pc_run1c` 的内层 lazy 循环新增对外层 dp 的读取。当前 `lazy1c_loop_inv` / `lazy1c_loop_spec`（2841、2871）调用形状里没有 dp；未来实际提取可能改变参数排列。必须检查该 inner loop、其 body、父 main loop body 和调用点的真实 Funs，不能只按源码猜“在 km 后插一个参数”。原循环状态 tuple 的运行状态未新增，prev/head/预取缓存的读写位置未变；新 helper 的候选一旦被接受，仍使用原 `LazyInv1.accept`，否则仍使用原 reject。

主循环的燃料、p 每次 lazy 接受前进一字节、Dec/fold/emitter/输出容量接口保持原结构。没有把“比 head 更好”作为安全性要求；只需每个有效 offer 的 MatchAt 成立。潜在未来预算重分配若改变 normal 搜索，其证明应另行绑定新 Rust；A8 的有限解码和这份静态审阅不能继承过去。

原 Lean 大小 487015 B，距离 524288 B 还有 37273 B。这说明有文本容量，不说明提取或证明耗时一定可接受。性能出现足够信号后，再执行实际提取、局部迁移与原完整 gate；当前这些仍是 UNKNOWN。
