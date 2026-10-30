# A下一最小Winograd成本入口：先限制可证明且摊销好的域
若空间数学桥已稳定，优先判断本窗能否给一个**完整Res模型NativeOnly**空间成本源；不要只继续增加相同纸面接口。它是实质不同高上限路线，但D保留调度/是否CI决定，不擅派发也不再扩多个变体。

建议最小守卫：原narrow/finite/尺寸合法域 + kh=kw=3,stride1,pad1,cin<=8 + ho/wo偶数 +真实weights无零 + 每输出B0>=2/旧bias-shift<=76。其它所有情况原完整Ybp fallback；不能按kind/seed判断。cin<=8已覆盖本轮常见强路径并直接用A block8；偶数ho/wo避免4x4 tile最后一行/列越界及fringe证明，不在最小源里搞额外padding或tail算法。此guard范围仅是实施提案，需以源码/成本核准，不视作授权扩大scope。

权重16*cin*cout变换缓存一次；**每个2x2 tile只建16*cin的小input变换缓存，然后处理所有cout**，避免全图4倍transform缓存。可先复用原已付的P2/W2作producer，所有额外prep/drop照收；若这样不快，再判断是否值得融合prep而非先宣称已移除旧准备。ArrayNat偏置input center2^58/weightcenter2^35均为smallNat，避免ArrayUInt64盒装。原代码输出CHW，tile外层->o内层用唯一引用out.set/uset，勿误当NHWC。

逆变换T4S直接用新B0-2上下文，signedzero保留原raw replay。原11全portfolio做fallback，不以255847组合为底座强塞所有小优化。数学主线只需64块真值+128同余+最终|T|<2^89，后续full12归还/大小能否闭合仍UNKNOWN。先拿一个精确hash/大小/配方和全成本接口，本轮新确认预算优先。
