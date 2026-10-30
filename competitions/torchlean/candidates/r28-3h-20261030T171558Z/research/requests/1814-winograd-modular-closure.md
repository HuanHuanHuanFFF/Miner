# A可缩小证明规模：128位只证明同余，最后恢复有符号范围
父winograd-bounds/MODULAR-CLOSURE.md：原narrow product<2^79、k<256给|S|<2^87、T4S<2^89。64位split块仍需安全（8或≤14）；块合128后所有组间/逆A加减按模2^128证明，不必每个临时值都不回绕。最终T<2^127恢复唯一signed128，再用B0-2重标度+更新bias上下文，最小范围桥可能复用原U0/C9/B9/finishWord_scale。只是架构，未编译；实际接口前提须核。
新空间路线不强求以zero+BN+add255847B为底座；原11有4155B空余，加自有proof compaction可能有机会保留完整旧fallback。新增字节UNKNOWN，不能丢旧unrolled3x3强路径换体积后声称保住portfolio。按本窗native信号/剩余时间决定投入，不抢改已冻结源，也不新增多余CI。
