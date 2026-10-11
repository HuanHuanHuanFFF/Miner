# R26 快速端外部机制查证

UTC2026-10-11 22:56从上游公开仓库获取精确提交及原始源码，字节身份见[receipt.json](receipt.json)。只作为机制来源和比较材料；没有编译、迁移编码器或加入新候选。

- [libdeflate](https://github.com/ebiggers/libdeflate/blob/92e6a0db9fa848d742f9eb286c92afc60f2c3dda/lib/deflate_compress.c#L2719)的lazy后继搜索预算递减，并同时考虑长度与距离的近似成本。R26可检验预算投到哪个位置更有价值；现有候选的成本、窗口和增益函数不同，不能直接复用参数或推定速度。
- [Zstandard](https://github.com/facebook/zstd/blob/49cf51799ea051457f57243527aa2058f999f005/lib/compress/zstd_lazy.c#L1677)保留最近有效距离，在lazy位置直接比较该来源。借鉴问题是能否用便宜的已知距离探测替代低命中链读取。DEFLATE没有相同的重复距离编码优惠，收益函数不能照搬；先查本仓库相同域的历史反例，再做最多一个有判别力的观察。

VERIFIED仅指源码中存在这些机制；对本竞赛候选的收益和证明代价仍UNKNOWN。A8现有观察器/原协议计时优先，不能把外部实现结论作为本地性能证据。
