# R15：下一项紧界／字面量RSE研究已派发，首D独立复核完成

时间：2026-10-25T05:33:59.574780+00:00。回复D052003实际proof反馈：b962的两处dsimp及finish_select零lane三处错误已确认。worker独立核对D b1160671只改三处证明，427两行草稿已被替代；R不重复写开发源。新source仍以真实下一编译为准。cutoff与当前cb7组合声明通过不继承到原8373或新组合的完整gate。

R已从401633原verdict/class-work/归档input独立核对ec82及DF全gate与25轮、指纹起止不变，重建candidate/reference再除DF/reference=0.9760865601918188。D原bootstrap p05=-0.0060468，R未重跑该bootstrap。该源两指标不达，PARK，不同seed确认不能重置。回执astra-first-D-independent-review.json。

根从旧LowScale源码提出、已交scalar Astra推进一条有实质数学边界的新路：旧roundLow_eq对product<2^48且scale<=123保守；非零leading<=47，scale124仍保证position<=171<172。再加两条有严格product界的字面量scale分支：

|scale|必须满足的product界|现有rseAny固定shift|
|---|---|---|
|124|product<2^48|25|
|125|product<2^47|24|
|126|product<2^46|23|

这是沿用原roundLow/RNE/roundP，仅绕过已可静态确定的leading搜索并使移位可折叠；不追R14未验bias公式、不重做整个正常整数MUL。原<=123热路要保留无额外3比较，其余完全回原roundP。root912项exact-dyadic边界模型已过、5秒硬上限实测0.001s，未证Lean或速度。重要反例已保存：scale125若无product界，真实normal mantissas(2^23+2)*(2^24-1)会从正确0x00800001变错0x1；scale126也有真实subnormal/normal反例0x00800003 vs0x3。因此不能单纯把123提高到125/126。模型/纸面范围见astra-tight-rse-boundaries.py/.json。

请D不重复实现该小模块，scalar worker在核旧负结果与真实命中域、写完整proof/片段，约05:50给root，R先独立审阅再交。matrix worker另做prepared B2类型布局的5分钟表示预检，再决定是否交原型：一个对象含两个F32字段，可能减少Bmap boxed元素与指针流量，保持两k链/raw finish。只有真实类型表示证据才继续，不能把对象数当速度，旧Panel4覆盖窄不排队。

旧far-add与low-zero都找到了完整负D，保留为约束；low-zero原路径本就跳过log2/RNE，不再靠错误成本叙述推进。R15当前仍以已验证cb7组合完整结果和b116声明修复为近期优先，新增两个研究不等于要求全部排CI。06:19:28冻结、07:39:28截止与原gate/确认预算不变，190旧资料HOLD。
