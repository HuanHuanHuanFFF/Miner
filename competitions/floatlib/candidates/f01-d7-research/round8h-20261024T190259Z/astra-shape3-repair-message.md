# R14研究回复：shape3仅修命令位置，native2原件独立核验

时间：2026-10-24T22:00:47.649183+00:00
关联：20261024T215213521Z-r14-development-repair2-feedback-and-authority-check.md
类型：CI反馈修复／回复

已从Git207与当前Kernel逐字节比对，再重验两份原始verdict和shape2编译输出SHA，记录astra-proof-feedback-40135440097.json。native2(32be572b)statement确实通过；仍无新helper公理审计、独立replay或运行候选完整验收。shape2失败点与原件一致，旧版冻结保留。

shape3已在独立新目录准备：D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r14-math-scale-shape3/Kernel.lean，252706B，SHA-256 17632bb80c068bc57f2ab85987b6be273e1b1f45035e7aa9c769c3e70e8da62a。只把set_option前的doc-comment改普通block comment，并为first_product_form也加scoped maxRecDepth8192；原命题、运行体和df5c父本字节未变。NOT_RUN，不宣称修复已通过。

请求位置：D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-ci-request-scale-shape3.json。保持本地READY／新批公开权限待确认；不重复跑已通过native2，不派独立CI，不改你在途作业。完整56773d4d仍是主线优先编译对象。

另备两条没有建候选或追加CI的数学草稿：astra-uint32-native-bits-draft.lean把已验任意UInt32转换模型直接接到真实toBits；astra-raw-exponent-shift-general.lean把300常量推广到受限k，供加法150和乘法300共享。均NOT_RUN，不替换已冻结主线。signed64转换的原字已有符号，需要补“保留原符号位的加法平移”版本，不能直接把为正mid后置符号写的运行表达式当同一条源式；我继续核对这个代数连接及toInt范围。

结论状态：原CI与字节核验VERIFIED；shape3及两条复用草稿未编译；无性能结果。
