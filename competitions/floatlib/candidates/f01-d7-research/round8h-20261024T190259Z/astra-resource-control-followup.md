# R14：两个最小版本均终止，下一层只切Nat/word并加父源正控

时间：2026-10-25T02:26Z。已读40153361143四份原replay.log：old最小29.2s、new最小26.6s、M5 20.3s、combined3 22.6s，VerifyFull均exit=-15，均无Lean错误文本。q/r替换在这批**没有使构建通过**；当前不能归因于原大模数omega、OOM或任何数学反例。

更小触发片段已于02:05放在 `astra-biased-rne3-nat-only.lean`，495B，SHA **0bf6eabde75e359e47b962dd80eb5532fd0d90e60e13d21580a9a385a957ee6d**。它从fd3仅截取namespace/open/nat_bias证明并正确闭合，完全没有UInt64 word_bias/biased运行函数。`astra-mul-termination-isolation.json`给出compact3c6a+该片段的内存预览：228153B、SHA44e56491...，未创建候选/CI。若与现有最小对照比较，请保持相同maxRecDepth设置/位置，另绑定精确source SHA。

建议下一已有槽内诊断顺序：保留你安排的精确M4复现；同时把未改compact3c6a作为当前runner正控（官方shipped pin不能替代较重DF父源的正控）；若仍需切分，再用这个Nat-only片段。若Nat-only通过而wholeBias终止，才把范围收敛到word lift/二者组合；若连父源也终止，优先环境。所有结果分别记录，不能从某个控制通过推整包接受。

若加只读观察，最有区分力的是失败层在cleanup前的Submission/VerifyFull `.trace/.olean/.c`是否生成及SHA，以及相应进程/资源事件。当前ci-diagnostics只在reason为空时复制生成文件，失败无C索引不能证明未进入代码生成。保持原gate/cap，不增加计时observer到确认组。

另外核对了固定Lean kernel/type_checker.cpp：Nat.ble、位运算/移位等有数值原语归约，因此不能仅从Prelude的递归源码就断言“decide比较百万数必然线性/OOM”。目前没有据此改word_bias。R不新增运行表示、不独立派发，也不把新的q/r草稿称为已修复。
