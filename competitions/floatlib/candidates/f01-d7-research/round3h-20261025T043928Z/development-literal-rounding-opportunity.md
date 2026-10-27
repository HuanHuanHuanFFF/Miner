# R15 可证伪的标量结构机会：字面量舍入与共享中间量

开发已接入 b962 为 `f01-r15-dev-column-pairs1`（源码未改），也已把cutoff84完整片段与短n/内联A组合成 `f01-r15-dev-shortn-decode-cutoff1` cb7f1099。seed1526002仅编译这两份新证明，待首CI40163383779终态后启动；不把statement当full D。

另请研究在自然检查点评估一个有具体结构差异的方向，第三条Astra有空闲时可复用：R14已完整正确但MUL慢29.1%的9038，`R14DIntegerNormal.roundedWord` 调通用 `FastMul.rseAny product (23 + (product >>>47))`；实际rseAny对shift==0、<64、==64分支，rse内部还有变量移位、mask、half和奇偶判断。所有入口已有inline，单纯加inline没有意义。

可尝试的实质变化：显式共享一次 product/high/rounded/carry，并按high=0/1分别调用字面量shift23/24的已有rseAny，让通用shift边界与mask在编译阶段成为常数。原 `shiftWord_values` 对任意u/v已有23或24的证明；通过split与rewrite可证明字面量rounder等于旧roundedWord，无需新bias/RNE恒等式或重型Nat证明。随后证明新pack core等于原core，复用完整core_spec，保持旧eligible/fallback和所有边界。先核对旧C是否已消掉这些检查或共享中间量，若已等价就不占full runner；若实际C缺失，明确UNKNOWN，提出最小精确代码生成检查。

这是待评估机制，不是收益断言；9038首D失败继续保留，旧59de/M16/R9/prep负结果不能换名抹去。若新runtime没有实际不同成本，则停；若进入候选，必须独立精确源、自己的首D。尚未由开发创建此候选，避免与研究文件冲突。数学组件在 `f01-r14-dev-mul-cache-rse2/Kernel.lean` 3321–3429附近，旧proof已完整验证；不得重开未验biased整数路线。

三小时窗口、单在途CI、06:19:28UTC冻结、07:39:28UTC截止不变。R14完整研究导出仍HOLD。
