# R8 一小时组合优化

窗口：2026-10-23 北京时间19:01:07—20:01:07。完整结束时间见[窗口回执](window-end.json)；冠军目标仍未达成。

当前保留[41组合](../../f01-r8-combined-result-guard/Kernel.lean)，235169字节：将已验bee6标量结果守卫接入a84，原sum/BMM及七项证明修复保持字节一致。821发现、822新runner/新seed反序确认，四份原版完整gate均通过。相对a84整包降耗**7.7%–12.4%**，对公开原版**4.15–4.55×**；822的sum退步5.4%也保留。

- [精确选择及本地bootstrap](independent-selection.json)：两样本归一化ratio0.8764126571/0.9225086344，gain p05均>0；不是正式冠军准入。
- [三次CI及原始证据](round-results.json)：821/822完整验证；825独立编译上下文诊断，未混入计时。
- [独立源码复核](source-review.md)、[真实编译上下文](compiled-context-review.md)：self-BEq已内联，常规tensor循环独立；诊断对象不冒充计时对象。
- [更新后的残余机会](post-discovery-residual-note.md)：specials合计20.923%是完整cell曝光，NaN/invalid时间UNKNOWN。939投影仅余636B，未生成新候选；353d未接入当前循环。
- [有限标量输入盘点](scalar-cold-domain-821.json)：86类输入模型完成，timed scalar6230/11178909触发原生NaN回退；未计tensor/replay，也不是观测时间。旧807校准与新模型边界保留。
- [固定Lean运行时边界](runtime-boundary/receipt.json)：加/乘/selfBEq为header inline，bit转换为外部声明且执行NaN规范化；诊断clang参数无LTO。最终机器码与每次成本仍需测量，不能直接改成任意raw bitcast。

下一次先量高频转换边界与tensor冷路实际成本，再决定大证明集成。939备选可比较“补拒绝域桥”与“冷路显式重查特殊域后复用原证明”两种取舍；后者新增检查与字节/收益均UNKNOWN。不开无新机制的numeric-mul或低零值重试网格。
