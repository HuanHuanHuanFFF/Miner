R25独立关键审查：请只由你本人完成，不派任何子agent，不启动benchmark/CI或写新候选实现。控制为一次约10分钟的短审，输出最多两页，并附可下载Markdown，不要zip。附件Kernel.lean是我们自己的TorchLean候选，约52849B、SHA256 f1b3f6ca5fc0a3e8d25e2f3db53e613687decd0941b0017b7cf177ae91ca5914；它保留官方12算子原算术，只尝试共享dense/conv解码缓存、空间patch，以及归一化的精确Rat缓存。官方规范固定 https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/accb82b6e2adeda1b41a57a260d68fb3879c427e/lean/contract/ContractExact.lean ，Lean4.34/FloatLib0d918257。新目标现已授权，但当前冠军/生产策略未知；竞赛API先前被Cloudflare1010明确拒绝，不再请求它、换UA或绕过；无需旧冠军源。

请读附件中新增部分和最终Submission.correct：优先找一个实质的语义/量词/缓存索引漏洞，覆盖任意Nat尺寸、零维、stride=0、padding、shape不匹配、NaN/Inf、±0、domain外fallback。不要把只支持正常benchmark形状的论证当全输入证明。区分数学反例、具体Lean elaboration风险、只凭源码不能判断的问题。

再检查成本前提：conv patch缓存消除cout次重复坐标/解码，是否被patch数组、复制、引用计数/释放抵消；norm共享decode是否真的消掉每output重复工作、而非原编译器本已hoist。若数学上成立，给两个最小、能改变继续/停路线的具体测量或反例；所有整模型收益UNKNOWN，不把旧合成bank0.27–0.29×自建integer当新赛道成绩。官方CI正独立验证完整源，你的判断只作一次关键审查，不要宣称Lean/gate或任何性能已通过。标附件具体声明/行或最短引用，别泛列清单。
