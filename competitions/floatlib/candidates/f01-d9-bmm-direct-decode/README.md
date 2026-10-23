# DirectSmall 输入数值解码

将已有全输入等价的R2W01b.convert接入直接矩阵内积，测试能否减少反复Float32.ofBits调用的完整成本。两条输入转换改为helper，沿用decode_eq证明模式；不改变原序乘法后加法及NaN精确重放。标量、求和和packed矩阵原样保留。

候选与证明尚未运行原版gate；预期收益UNKNOWN。逆变换逐字节恢复41父本，许可证全部保留。
