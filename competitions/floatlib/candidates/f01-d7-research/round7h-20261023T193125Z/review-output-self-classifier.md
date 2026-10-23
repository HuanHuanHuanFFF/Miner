# BMM 终点 self-BEq：旧机制的当前父本迁移

状态：**READY_FOR_STATEMENT**。唯一新源是 `f01-d11-bmm-self-classifier/Kernel.lean`，SHA256 `6457ed8f64714c116d8e861e612c53a9019446e8a282964611c794ccba29f482`，237208 B。父本严格为 a066 `a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78`，237142 B；增加66 B，余18792 B。源已冻结，Root负责实际语句及完整gate。

仅把 `NativeFinal.dot` 与 `Packed10.finish` 的终点 `result.isNaN = false` 改成已有 `R7W04.nonNaN result = true`。`dot_eq` 通过已有 `nonNaN_eq_true_iff` 把新前提转回原 `dotLoop_eq` 前提。两处守卫同步改动，因此 `finish_eq_dot` 原来的 `rw [hs] <;> rfl` 保持原字节，后续证明也不变。

三处精确替换之外，所有原字节保留：原生乘加循环及顺序、getD地址、packing、终点toBits、原始A/B字NaN回放、空维数/巨大Nat回退、scalar、全部sum及作者说明。`exact-inverse.json` 保存每步旧/新文本、偏移、片段hash和前后完整源hash；逆变换逐字节恢复a066。`build.py --verify` 重新构建并核对冻结源，未调用Lean、Git或CI。

历史核查未找到已完成的同一路径负面计时：旧6b00候选确实同时改过四个终点，但基于失败b169；proof1/proof2的最终交接仍明确标为NOT_RUN。当前结果索引三者均“无匹配回执/0”。另在678份本地保留的`*verdict*.json`中搜三份精确source hash及候选名，均无匹配。这个结论只覆盖本地保留证据。R8的scalar self-BEq已进入a066，但这两个BMM终点仍使用isNaN，因此本次是旧机制的当前精确父本接线实验。Astra另有基于short7cad的未写Kernel补丁，不是本候选或已验收结果。

固定R7-W06 `lean.h` 第2948行把`lean_float32_isnan`声明为外部函数；第3260行的`lean_float32_beq`已经是static inline。本次动机是替换BMM终点外部isNaN分类，不能声称额外去掉foreign beq。新候选的实际C、汇编、内联和收益均尚未观测。

本地原版policy、256000 B上限、唯一导入、namespace/八个export及spec库存、资源选项不变、注释保留、三段唯一替换和完整逆变换均PASS。**新Lean语句、leanchecker、axiom审核、checksum、完整gate及生成代码均NOT_RUN，性能UNKNOWN；没有正式提交。** 证据来源各自的hash/字节、检查边界和后续步骤见 `review-output-self-classifier-status.json` 及候选manifest。
