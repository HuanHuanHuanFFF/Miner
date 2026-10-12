# C3 proof2：基于真实 cap bind 失败的修补

真实失败 run38267162180 的原日志 SHA256 为 `671fb89273e1cf8a2e40d62b47d1965da07990ee3cec53980699e3ab5f851bf6`；receipt SHA256 为 `1a9f9f9ac96a38fcc1bf36ee52e67ccbfdf0c1b145623a9bba5d06638fbb9a72`。首个 error 为 Proof/Parse.lean:928:7，最后 fallback 无法匹配仍包含 `let cap ← if rem<258 ...` 的整个程序。旧 proof1 的 try 内处理没有留下一步有效的绑定消费。日志没有显示被 try 吞掉的内部错误，因此不能确定是自动局部变量引用、spec_bind 或后续步骤中的哪一个失败。

新 [proof2-entry](c3-proof2-entry.json) Rust 是同一个 C3 实现的逐字副本，SHA `58324f244b6deb669e4a4af523a09e5900a016d027b32cc90c785363a19b8da7`；Lean SHA `e193b0c34200c4177395e7b0502b8ee51a12de2995052ffc457185764f376300`，508530B，余15758B。**UNCOMPILED**；真实 gate 尚未执行。

修补只在 c3 helper 区块：

1. 独立 `c3_cap_spec(rem)` 证明原 if 程序返回 cap≤258 且 cap≤rem，保留 rem/258 两支原语义。
2. 初次 step* 后无条件 `apply Std.WP.spec_bind (c3_cap_spec _)`，显式引入 cap，避免直接依赖自动引入 rem 的名字；不使用 try 包住此处理。若内部仍失败，下次日志应定位直接步骤。
3. 从 cap≤rem 及日志已显示的 i1/rem 算术事实推出 pos+cap+8≤input.length，然后继续 step*。
4. Writer helper 的 full 改为纯 Nat，完整范围、Matches、token值、输出长度和decode后置条件保留。从当前 Matches 假设捕获实际 full 长度，避免按自动 full 名字选择。
5. cap不足的原 emit_step 分支按当前目标推断 hint，而不是依赖 C3 外层 l 在自动简化后仍具有相同语法。

旧 proof1、原失败 receipt、日志与抽取文件保持字节。C2 gate 已由主线程取得真实成功并绑定；这不替代 C3。C3 proof1 正在运行的同 Rust 确认需保持原 pair 身份；若 proof2 gate 通过，仍需按新精确 pair 另做冻结后确认。

C4 proof2 具有相同 try/cap 结构，因此可能受此次问题影响；C4 仍无本窗新 gate，不能将 C3 新修补自动视为 C4 修复成功。没有修改 C4 文件。

VERIFIED：真实失败目标及精确新字节、同Rust、局部修改范围。INFERRED：显式 cap lemma 可避免上一段静默回退，现有writer责任可复用。UNKNOWN：proof2 的实际 Lean/完整gate及新pair确认。
