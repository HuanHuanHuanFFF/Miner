# E1 proof2：真实抽取的 fallback clone 配对

真实发现作业 `38268487485/screen90-e1` 已提供新 Rust 的 Funs。其前置短路 guard 使原 generic fallback 被 Aeneas 复制为15个循环：word loops 0/3/6/9/12，byte loops 1/2/4/5/7/8/10/11/13/14。proof1 只显式覆盖原loop0/1/2；它不能据父宏自动覆盖所有这些新增名字。原 proof1 已启动 gate，由主线程保留其完整结果，不改写该 pair。

[proof2-entry](e1-proof2-entry.json) Rust 保持 `bc1b3fec788a0d58d220efb84505e26f83a7045129c724f43095704c6097adc0`；Lean 为 `b0d67036601c00bd7cb9831f26693e70d08ab9d529a0b2c5ac5a7562b60c8275`，509162B，余15126B，**UNCOMPILED**。

本修补有两层：

1. 静态检查实际抽取的loop3…14，每个loop的`.body`与外层函数共24份定义，仅正规化对应函数名字后，与loop0/1/2逐字相等。原始抽取SHA和各定义SHA保存在 [clone-preflight](e1-real-clone-preflight.json)。这只是文本检查，尚未 kernel 验证。
2. 新 proof2 增加12个 `by rfl` 程序等式，在 same_spec 展开后用 simp only 将新clone归一化至原loop0/1/2。原完整循环规格、循环不变量及masked-tail证明直接复用，没有新增公理或占位。每份 alias 的实际 definitional equality 将由原版 Lean gate 检查。

新短路径 `e1_mask_match` 与原 proof1 相同，仍从 word8_prefix 支持len≤8；guard、cast、shift与writer的实际 tactic 匹配尚未通过真实构建。消除clone名字缺口不证明所有义务已经完成。真实发现速度与份额来自主线程按同一快照复算，属于筛选信号；proof2 的新精确 pair 仍需完整 gate 与冻结后新runner确认，不能继承成已确认成绩。

旧Rust、父Lean、proof1以及原native/计时/抽取证据均保持字节。准备脚本 `scripts/r26-e-build-short-same-proof2.py` 只做轻量源码检查和文件构建，没有Git、CI启动、上传或资金操作。

VERIFIED：实际clone命名、正文正规化相等、精确新pair字节和来源。INFERRED：程序等式可将clone接到原规格。UNKNOWN：内核等式与新short分支验收、完整 gate、稳定公共份额及正式成绩。
