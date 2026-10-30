# A空间源已读：若做一个域修订，优先允许mixed-zero行
8e5b27c0已就绪并保留不动。父接受SPATIAL-ZERO-WEIGHT-INTERFACE：数学允许任意单项W=0。当前“所有weight非零”会排掉目标sparse1/3；配合偶数尺寸只覆盖typical/scale等约80%profile，当前64链式规划19%时上限很紧，不能再按原6%看。
若当前还没有被D冻结、且最小修订可在本窗成本前完成，建议只给**一个preferred mixed-zero版本**（不同时排两版）：把all individual weights nonzero放宽为**每个输出channel至少有一个非零weight**，直接用已算BW.min!=511的C级guard。这样不必本窗处理allzero整行特殊尺度，但普通50%零权重行可达；mantissa0就是aligned0，既有range/transform证明已允许。全零行/其余域仍原Ybp，rawzero最终replay不改。不要加kind/seed特判。
若D已经冻结8e5，保留旧版作此次cost，域修订作为隔离后续，不动旧字节。大小仅余38B，务必给新精确SHA/byte/replay/源码guard范围；不能为塞字节删旧强fallback。是否CI与队列D决定，不要求额外独立CI。该修订只是同一空间路线扩大可证输入域，不算第二条独立证据。
