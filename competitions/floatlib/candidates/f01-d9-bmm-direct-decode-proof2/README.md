# 直接点积解码证明修复

831暴露Packed10.dot10_lane也会展开NativeFinal.dotLoop；需要在归纳结论处运输directDecode_eq。仅改这一处proof，运行定义与548保持原字节；原失败版本保留。新完整gate和性能NOT_RUN。
