# CI12 OOM后的两份不重叠共享块（未排队）

原2177导入B2后仍单scope4GiB OOM/24.132s，无typed goal。新诊断仅逐字切出已失败源共享证明，**不修改任何证明/运行体/输入假设，不是第3proof版本**。

- NatPostClosure.lean：4877 B，SHA cbdb2fb8e83908a6c6179c286b1648891c0186727db53b6d635a5af2689b8f31；原Nat闭包＋PostBias，5新具名根。
- NoWrapOnly.lean：1821 B，SHA 8d49e866e3ea7257af5d78709dea54b8b805a7a7f66f7e39ed74e98e8050fe39；原biased_sum_nat完整定理，1新具名根；包含旧word_grouped移来的1338 B证明块。

两者均已有import Submission，无#eval/options。若R/D选用：精确B2原carrier审计先过，再同原g.own/caps/read模式独立运行两进程并抓live资源；这两段逻辑独立，第一段失败不应自动跳过第二段，除非base失败或原预算不足。现有stage上限内执行，不扩额，不跑B2计时。原quotient-only已完成，不重开；7b03/70d4仍HOLD。

manifest列结果分歧的下一决定。两个小helper的process成功、其新根axioms/replay、完整fa652验收分别记录，未测NOT_RUN。当前只是准备件，不自行排队；root/D决定后继。
