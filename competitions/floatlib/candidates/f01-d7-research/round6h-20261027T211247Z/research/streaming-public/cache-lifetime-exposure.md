# 已曝光R15的batch局部缓存覆盖补充

`cache_lifetime_exposure.py`重新核对原plan/work/verdict SHA，只用早已曝光R15 D/A/B，未读取R22确认组；原始来源绑定在JSON。

| 旧run | B2形状 / 多batch | 触及类whole上界 | 单次最大全局packet+slot请求 / 逐batch最大请求 | 一份plan新增外Array header请求 |
|---|---:|---:|---:|---:|
|40168687803|9 / 9|14.7685%|470016 / 4248 B|232344 B|
|40169957447|12 / 11|17.1490%|548400 / 23616 B|156528 B|
|40171180249|14 / 14|19.0579%|604800 / 44832 B|167520 B|

所以“当前样本几乎无多batch”不成立；同时，这只是条件请求量/类总时间上界。逐batch不减B转换、packet总数、输出finish；新增外header及准备边界，原始输入/全输出仍存活。实际underflow命中率、缓存寿命成本、allocator/RSS和可得速度均UNKNOWN。即使把触及类全算为目标，10%whole仍需删其中约67.71%/58.31%/52.47%时间；不能把peak请求下降比例换成时间收益。当前不据此新造候选；参照闭合情况见`cache-layout-closeout.md`。
