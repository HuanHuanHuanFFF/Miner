# C4原版gate失败与最小修补草稿

UTC12:40–12:43，按实际日志准备；未修改原候选、proof1或原始回执，未派发新CI。

## 已执行的失败

run38248430871，Git fd5db7c2798152e6c1c0b8fed501adcee7508bdf，精确Rust `ae4602290cc2a0253703ab6e6ac0d2fe098e84429cc4d56314ac9326abbf0f88`、Lean `11426ab441c65b37949eff9de9840310d9192fd797870433d90d5e06463fb105`。

原receipt为`EXACT_ORIGINAL_PUBLIC_GATE_REJECTED_OR_INCOMPLETE`、exit_code=1、accepted=false，未产生official JSON。official tree检查通过，但原obligation、axiom whitelist最终输出及公共roundtrip接受未完成。不得把native有限decode成功写成完整gate通过。

原日志：`evidence/round26/38248430871/gate-c4-proof1/exact-gate/exact-gate/logs/005-lake.log`，唯一error位于Proof/Parse.lean:919:7。失败的`WP.spec_mono (emit_lits_spec...)`试图匹配的实际目标仍是整个do程序，首项为：

`let cap ← if rem < 258 then ok rem else ok 258`。

之后才有cap≥l分支、trusted match_len及writer。首次step*已建立n/pos/d及rem=n-pos-8事实，但停在这项if/bind；通用writer或literal回退证明都无法消耗这层bind。该错误直接证明**提交的proof1脚本不完整**，不是Rust匹配正确性的反例。其他mvcgen重复注册为warning，不能代替这一error或将它们自行归为根因。

## 未执行修补

仅新建`audit/C4-Parse-proof2-UNCOMPILED.lean`，508337B，SHA256 `1182e84949bf7e1003af878ff9253ea39d9238147c9e138c374610f104cf53c1`。它在同一完整父证明中，只为c4_emit_step_spec增加416B的局部bind消费：

1. `Std.WP.spec_bind`的中间谓词给出cap≤258与cap≤rem。
2. 对if两分支分别证明该谓词，rem/258选择均保留原程序。
3. 显式恢复pos+rem+8=n以及pos+cap+8≤n，再step*展开余下cap≥l、match_len、full≥l与writer/回退分支。
4. 保留原c4_write_post及全部完整进度/decode后置条件，没有修改Rust、原obligation、公理白名单或已冻结hash。

草稿没有sorry、admit或新增axiom。它针对已经观察到的绑定失败，但仍**UNCOMPILED**：后续cast、writer和回退匹配可能暴露新错误；没有工具证据证明这份草稿可编译或通过gate。本窗按主线程决定不再派CI，不称“修复成功”。

性能结论亦保持原状：主候选发现份额0/0，未进行冻结后独立确认；即使后续证明通过，也不能据此晋升可靠小份额。原失败pair保留FAILED，proof2仅下一次获授权研究的修补起点。
