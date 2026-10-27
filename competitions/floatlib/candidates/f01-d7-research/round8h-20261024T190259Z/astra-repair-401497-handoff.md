# R14：真实编译反馈的首份数学修复已备

时间：2026-10-25T01:29Z，回复012100。原5556/a234/3934与原始compiler_output不变；以下只写astra新版本，均 **NOT_RUN**，由开发合入下一精确源。

1. `astra-biased-rne3.lean`，2457B，SHA **fd3df0d744f52f15ba697b1f742f56d77c0ee58ea082b3f5872afbaa970f8326**。从e9ab去掉norm_num之后已无作用的`simp only [beq_iff_eq]`，对应5556:3421两次真实no-progress。
2. `astra-integer-core-model2.lean`，2722B，SHA **c201150eb693447adbec8c58a7e877f6f21ea336d00508582ac717680d2bd3bf**。只替换R14ExponentShift.core_model声明，不可并排追加重名。两处dx/dy非零前提明确show尾数Nat≠0；hm先change成具体sign/p/exponent记录，再做heOrig和model_round_normal重写；末尾明确展开p/s/storedFraction。原定理陈述不变，运行体不改。
3. `astra-small-shift-bias3.lean`，3163B，SHA **ec6a8e65cb608d094049682549e3e9213ac81e13125ca57d2a89943b2c2c2a94**。去掉8个分支norm_num之后同一条无进展simp。
4. `astra-word-add-alignment4.lean`，4000B，SHA **c8bd8475394f3161f412309476226edb724e961852e08ebce5d866aff8f69e50**。alignLeftOffset直接exact原定理，避免此前部分转换把Int.ofNat150留下↑150；same-sign记录显式`↓reduceIte`消掉残留if True。中间3版仍有offset转换，已保留；**下一源用4版**。
5. `astra-word-add-rounding2.lean`，2092B，SHA **b358c5a11e524af35fc476a5d373c84714b3e570de543a0b9a5dd4dcfb6a846b**。真实失败是在rounded_bounds末尾：norm_num后的quotient写成n/2^k，而后来hrlo/hrhi仍是Nat.shiftRight n k，omega没有把二者关联。新稿先change成shift notation再rw shiftRight_eq_div_pow，使上下界与RNE界同式；masked_fraction/carry陈述不变。

完整收据 `astra-repair-40149766137.json`。已读实际raw output，不能把这些修复称为编译通过；下一真实结果再收敛。ADD runtime/word字段/core_spec和ef5冗余dsimp仍按你的分工由开发修。913d仍延期，不扩队列。

组合graph审阅暂未发现明确缺引用：41项无primed声明、无环境搜索tactic、无export/notation等额外命令；但该图并非Lean elaborator，仍以实际3934错误为准。现在先推进标量数学修复，再完成图逐片回放与引用审计。没有独立Git/CI动作。
