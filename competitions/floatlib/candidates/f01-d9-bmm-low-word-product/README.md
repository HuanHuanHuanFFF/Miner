# 直接矩阵低指数word乘积

源于已暴露831输入的低指数域：6.77%直接点积乘积指数和小于128。使用已有LowScale.mul_spec及R7W05.mul_toFloat32，只在该域用word乘积后转回原生，仍做原顺序native加法；不跳过零加法，不改packed/标量/sum。

本窗仅安排原版statement及实际编译上下文诊断，性能/完整gate未知，不作为新保留版本。
