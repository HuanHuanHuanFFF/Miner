# R11 gap-groups 只读反方审查

审查对象 Rust SHA-256 `6ef07be874052d23fbe3cdca8de7e311e82a306338a93f70389fe35006e99992`。本次只读源码／生成器／既有 harness，并做 0..511 的区间算术核对；没有修改候选、运行 Rust／Lean 或新增 CI。groups-d 的原生与提取结果当时仍在运行，不预填成功。

**未发现当前源码的阻断性反例。** 两处测试范围口径应收紧；元数据语义仍须与将来的总性 gate 分开。

**元数据来源。** `d_load_groups` 先调用原 `d_load`，再读取实际 256 项 literal 价格和实际 lc 区间。任一 literal 为零、最大值大于 4095、或没有平坦组时编码为零禁用。否则最大值占低 12 位，20 个组标志占高 20 位，最高组落 bit31，互不覆盖。平坦组由每个实际 lc 项相等得到，并非假定任意 tabs 都符合长度码的默认平台。计算完成后只覆写 lc[511]；后续消费者只读价格，实际块切换重新生成。

源级逐字比较确认原 `d_load/d_block/d_gap/d_bcost/d_best_len_scalar/d_best_len_old/d_best_len/d_push/d_cand/d_back` 均未改。d_dp 仅有一处 load、两处 block、一处 gap 名称替换，反转恢复父函数。slot511 的安全性仍依赖调用链：实际 gap 的 stop≥node+1，长度字段最高511，所以消费 rem≤510；候选／push 另有≤258约束。该论证不把其他 padding 槽都视为空闲，也不把保留的 generic helper 限制为合法 producer 输入。

**20 区间与 seed 后 count。** 起止数组均为半开区间 `[start,end)`；源级算术核对 rem=0..511，所有 11..257 都落在恰当的组，其他值返回无组。258 单独保留标量。原 scalar seed 已将 q 减一并写出 q；后续 `count=min(q-stop, group_end-1-rem)` 恰好排除 seed，且最后 rem 不超过该组最后一个下标。最大 count 为31，没有跨平台多写一格的迹象。

**严格胜出与包装。** seed 必须 `vc<vl`。实际 metadata 保证所有 literal 正价，`C+max<2^32` 排除下一 literal 的打包回绕；相同 lc 平台使 continuation 高位保持 C，下一 literal 高位则严格大于 C，不需要借助 choice tie。`chd<=0xfffffefd` 与 rem≤258 保证 choice 不侵入高32位；dlit 也显式限制为低32位。失败守卫进入原通用 helper 或逐字标量步。任意伪造 mask／max 都不满足这个论证，尤其低估 max 可重现先前的 wrap 反例；未来 totality 通过不能补出元数据来源不变量。

**升序填充、ring 和返回值。** count≤31<1024，所写物理 ring 槽互不重复，最多跨一次 ring 末端。`lower%1024` 和剩余 room 正确划出最多两块。该段不读取 pending push 的 ring min；kc 在填充前已缓存，各 cell 只由固定高位和 `chd+end-p` 决定，所以改为升序不改变最终数组。seed 后 q 已小于 input/out 长度，填充位置都比 q 小，各 helper guard 在实际调用中不会提前截断。最后 `nxt` 重构 lower 的 cell，正是原逆序循环最后处理的位置，而非升序存储的最后位置。

**两处有限检查覆盖缺口，非已发现错误。**

- harness 的“14 loader”实际是7次 `d_load_groups` 与原 loader 比较，另7次在 usize::MAX 调用的是未改的 `new::d_load`。不能写成14次新元数据 loader 边界检查。
- 2156 个固定 DP fixture 没有显式把批量区间放在物理 ring 边界：node0 的 end≤511；node600 的有效 end=858；node1100 的 len511 超出 room，不进入续接。仅出现 n=1025 不等于已经覆盖 bulk 跨1024。公共整体等价可能经过该分支，但目前没有对应分支计数证明覆盖。

可手算的边界轨迹是：`hi=1027, stop=1020, end=1045`，literal价全1、lc[19..23)全2、endpoint高位10、kcd0、chd512、nxt0高位13、lo2000。首个 seed 在 q1026/rem19，count3、lower1023，源码应写 `[1023,1024)` 到 ring1023，再写 `[1024,1026)` 到 ring0/1；**第一轮 bulk 后**恢复 q1023、nxt 高位12／choice534。函数随后还会处理至 stop1020，534 不是该调用的最终返回；若后续长度价也为2，最终 choice 为537。当前源码与此轨迹吻合。该例是审查中的手工推导，未执行，不属于本批 native 已通过用例。

按主线程追加授权，另存 [native-cross-ring-check.rs](../../candidates/r11-gap-groups/native-cross-ring-check.rs)，冻结原 tests／Rust／Lean 未改。它通过真实 `d_load_groups` 构造 metadata，准备9例：stop1023隔离一次跨 ring bulk、stop1020继续执行对照、平移后的非跨界对照、metadata bit31 对应 [227,258) 的跨界与非跨界、零 literal／max4096／无平坦组禁用，以及真实最大价格触发的成本回绕回退。全部比较完整 ring／out／nxt，常价启用输入还逐 cell 核对预期值。状态为 **UNCOMPILED / UNRUN**；只有后续确认 CI 真正运行后才可追加执行结论，不能因暂缺专项用例宣称源码有 bug。

当前可以保留的结论仅是没有找到源级反例，及上述局部保持条件。性能仍由同场总时间决定；正式正确性仍需精确新 pair 的原始义务、公理白名单、真实提取和公共 roundtrip。完整逐项审查和哈希见 [groups-review.json](groups-review.json)。
