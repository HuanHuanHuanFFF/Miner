# Public outlet：单行 proof-only 静态修订

只把 exponentWord_nat 第一处 Nat.mod_eq_of_lt 明确限定到 highWord.toNat，避免嵌套模数的 rw 先命中外层。不是实际 Lean 错误反馈，也不宣称修复通过。原 v1 完整源/接口/片段保留；逆补丁精确恢复。

运行体、guard、假设、48 根和全输入公共规格均不变；7b03 仍 HOLD，旧 quotient proof 未修改。此副本为后续编译优先源，原 prefix 诊断先行；manifest 给完整文件名/哈希/大小。没有编译、重放或计时证据。
