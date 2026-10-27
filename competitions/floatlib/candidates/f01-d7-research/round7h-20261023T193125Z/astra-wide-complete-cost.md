# 四行路径的完整成本判别

当前来源为 43aaf31f / 252421 B 真实入口候选；尚未编译或计时。921 的同对象证据只确认 eb9e 独立 wordLoop：每 k 十个 4-lane mulps/addps、无热调用或热栈访问；入口有四十参数 ABI，退出需分配 168 B 的 F40。旧 Packed10Index.loop 同次 C 的定义在 38790 行，38798 行为 lean_alloc_ctor(0,0,40)，即 F10 的 40 B payload；不能从“结果记录数变少”推导整次分配减少。

令 G=ceil(p/10)、t=floor(m/4)、r=m%4。以下均为源路径逻辑次数，不是计时权重，也没有假设每个动作成本相同。只在最外层 underflow miss 且实际 wide guard 命中时适用。

| 项目 | 旧 RowStream | 当前四行路径 |
| --- | --- | --- |
| global A 转换 / B 打包 | 各一次 | 各一次，同样的布局 |
| 完整 dot 调用 | batch*m*G | batch*(t+r)*G |
| 每个有效矩阵元素的 k 顺序 | 原 mul 后 add | 相同，无横向归约/FMA |
| A 对象/浮点读取 | batch*m*G*n | 同数量；四行 gather 每次共同组装 |
| B 的 F10 包读取 | batch*m*G*n | batch*(t+r)*G*n |
| 输出 finish | batch*m*p | 相同；只对有效列调用 |
| 新结果缓存 | 每次单 F10 后立即输出 | 当前四行块 G 个 F40，再按四行输出 |

每完整四行列组，旧四个 F10 请求约 4*48=192 B；新 F40 为 168 B，只省 24 B 的结果对象请求。新路径同时新增当前块的 Array F40 指针槽（约 8G B）、数组头和 ofFn 闭包；这些必须另计。假设指针数组只占恰好 G 槽，结果对象与槽的差额仅为每组 16 B，尚未扣数组头/闭包；G 很小时，新增缓存可能反而增加分配字节。实际容量、分配次数和存活期要看真实 caller C，不能把此公式当作 allocator 测量。

新 emitRow 的 j/10 和 j%10 使用常量 10，可能编译成乘法/移位，但仍有逐输出地址选择；旧按组 emit 直接消费当前 F10。新增四行 lane 选择与四十参数入口初始化也要由 whole-call 测试计费。为避免再付通用函数回调成本，当前候选显式 inline Layout.emitBlock/writeBatch/output 和 Actual.buildTiles/output；这只是实现意图，是否消除 lean_apply 仍 UNKNOWN。

逐输出高阶回调还有装箱风险，不只是间接跳转。921 原 C 的 Packed10_lane___boxed（38261行）先调用返回 float 的 lane，再 lean_box_float32。当前真实入口若把 lane40 保留成通用函数值，必须检查其 boxed ABI 是否也在输出热路径出现；不能仅看独立 lane40 的 float 返回签名。相反，发现 standalone ___boxed 定义也不证明实际调用了它：必须沿实际 bmm/fold 调用及函数指针引用核对。现阶段未观察到 28b819 的该问题。

判别顺序：先让完整具体证明通过；随后看同对象真实 bmm → wide core → buildTiles → run → wordLoop 的可达调用链，以及输出是否复用已经算好的块缓存。捕获应区分 wordLoop 热区、ABI 入口和结果分配阶段。第一次完整 suite 记录发现样本，随后冻结精确源码并关闭 observer 在新 runner 上确认。若主要成本落在准备、输出或 NaN 回放，热循环 SIMD 改善不能自动成为整次调用收益。

没有据此改 guard 阈值、创建第二宽度或预报收益。n>4、p>2、m≥4 的边界来自既有直接路径分工；本轮只评估这个单一路径。
