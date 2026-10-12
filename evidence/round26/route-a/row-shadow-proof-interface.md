# PC row：正确性接口与性能接口分开

此笔记只读原 public641 Rust/Lean；A11 是观察器，没有新候选或 Lean 验收。父 Lean SHA `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e`，487015 字节，在 524288 字节限制下余 37273 字节。新主循环若保留旧证明并另加一套，尺寸是实质约束。

原 `PC.probe_lazy_spec`（2434）要求 c≤q、cw=word8(c)、q+8≤n、q+l≤n+1，返回 FoundAt、长度≤258、距离≤32768。row 同位置查询可以复用这些前提；A10 的第二位置尾界问题不在这里重复。`PC.f_try_spec`（2776）只要求 c≤p 和当前 MatchAt，不要求 candidate 是旧链节点；传 c=p 并对位置做窗口守卫后，可为 row 的后续 offer 复用它。原 `probe_m` 的 FoundAt/MatchAt转换、fold、flush、raw emitter 的字节证据也仍可复用。

正确性不要求“行里一定是最近八个真同键来源”。只要任意解码位置经过范围守卫并由原字节验证返回 MatchAt，错误标签、驱逐和陈旧位置只影响质量/工作量。因而 tag 等价和 FIFO 证明不必成为合法 token 的逻辑前提；不能据此省掉性能实验中的 false positive 和保留损失计数。原 `f_deepen_spec` 同样没有对 prev 的匹配历史不变量作要求，这一宽接口已存在。

一份完整替换仍需新的实际提取 obligation：row<4096、slot<8、row*8+slot<32768，移位量<64，游标更新范围，非零位置解码减一，掩码扫描 fuel/预算单调，运行循环新增数组捕获，以及旧 token Dec 不变量从 normal/lazy 接回。预取字缓存还需 word8等式；若 coarse row 插入后缓存重用不正确，可以损失质量，也可能令未来未验证的字缓存与所选位置错配。仅缓存 row/tag 元信息与缓存完整 offer/source word 的要求不同。

性能上，即使 row 内存较小，也必须实际支付标签/游标 RMW、位置写入、键信息准备和候选验证。旧 `pc_ahead_fix_m` 可以在 end 位置旧 head 不变时直接使用先前 cw；coarse row 中任意其他 tag 插入都可能改变“最近顺序”的查询结果。A11 的版本计数专门记录这种更大的失效域，未来不能把原流水的预取优势免费视为保留。候选若采用直接查询或其他缓存方式，需要真实总压缩时间，不由源级读取计数决定。

VERIFIED：上述原接口、父文件尺寸与明确前提。INFERRED：合法性证明可不依赖哈希/FIFO正确性，但主循环和数组操作仍需新证明。UNKNOWN：提取后的函数签名、字节余量能否容纳完整证明、Lean实际接受、质量和时间。
