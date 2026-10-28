# 冻结 f5a6 的包装、容量和失败回收前提

只读阶段 **2026-10-28 01:32:01—01:47:01 UTC**；只用冻结前原件，无新版本、编译、benchmark、CI或确认组读取。f5a6/303a/91ac字节保留。以下区分固定源码事实、表示推断与未测实际行为。

## 包装不是每字段增加一个 Checked 对象

`checkNative`返回Bool；没有Checked结构、证明运行字段或每MAC检查。`packTileLoop`在完成整tile时只写一个`some ⟨out,sizeProof⟩`；每次k递归直接返回递归结果，不逐k包装。外`packTilesLoop`完成全部tile再写一个`some ⟨outer,sizeProof⟩`；成功tile的Option仅在match中拆开，外数组存FloatArray，不存Option。源码成功构造数为 **T+1个some**，T=batch*ceil(p/2)；失败none没有承载数据的字段。

固定Lean293d的ToLCNF512–514擦除Prop，Irrelevant57–72识别一个构造器且只有一个相关字段的结构，MonoTypes74–76用该字段替换类型；ToImpure106–113、135–138直接替换此类projection/constructor。由这些规则，`Tile n`的Subtype和Vector.size证明包装应消去，只保留FloatArray/Array本体，不能再加一个“长度证明对象/field”。这是编译规则推断，**新callback尚无实际C**。

Option有两个构造器，不属于该单构造器消除。若terminal some未被跨函数优化消去，其一个object字段按64位header8+pointer8请求16B；none的零字段构造在EmitC583–587走lean_box标量，不需要heap对象。故额外Option的条件累计请求为16*(T+1)B，**不是已测分配次数**；实际some消除/复用、参数借用仍待新C确认。

## 24N→16N的准确范围

N=T*n，只比较缓存，64位、精确容量、无共享复制、无allocator级取整：

| 条目 | 原F2缓存 | 冻结FloatArray缓存 |
|---|---:|---:|
| 外Array头与T个槽 |24+8T|24+8T|
| T个内部Array/FloatArray头 |24T|24T|
| 内部payload及F2记录 |24N（8N槽+16N记录）|16N double|
| **持久缓存请求** |**24+32T+24N**|**24+32T+16N**|
| 条件累计terminal Option |0|16(T+1)，若全部按普通some落地|

因此8N是持久缓存请求差，不是总分配、RSS、峰值或时间差。仅加Option而暂不计旧闭包时，新旧累计差为`16+T*(16−8n)`：**n=2没有这个子模型的累计字节收益，反而多16B总返回**；n=3差16−8T；n=4差16−16T。n0/1不进新入口，不能用其结果扩大guard。

但旧闭包也不能漏计。401680精确622d选中packB C原片段（本次重哈希匹配旧body_sha）有一个fixed5外closure及每tile一个fixed4内closure。固定lean_closure_object头在64位为24B，分别请求 **64B和56B/tile**。旧packB/内回调body SHA4656b3a3、b77c4c91；F2构造体acd9e26f确为一个8B scalar payload，不是两个Float32 box。

新producer是直接递归、没有运行函数值参数/Array.ofFn回调；若新actual C确实没有prep闭包，且some全部普通分配，则这个扩展请求子模型旧为`88+88T+24N`，新为`40+48T+16N`，差`−48−40T−8N`。**这不是总成本**：新增每字段宽/窄转换、两次native目标toBits、FloatArray.push、Nat地址、分支、RC均未变成时间单位。旧Array.ofFn内部控制/闭包释放与新直接循环差异必须一起归因，不能只称“payload布局收益”。

## 容量及失败时的数据树

固定header1129–1134按`sizeof(sarray)+elem_size*capacity`分配；emptyWithCapacity(2*n)请求size0、capacity2*n。push源码object.cpp2692–2698先ensure_capacity(size+1)，再ensure_exclusive；2590–2596在所需容量≤capacity时直接返回原对象。成功tile恰push2*n次，容量不会因数量不足增长，**仍每次检查容量/独占性**。若共享，ensure_exclusive通过copy_sarray分配同容量新块、复制已初始化size个double、dec旧块。不能把预分配说成复制不可能。

冻结source每次两次检查都通过后才做`(out.push d0).push d1`；旧out在后续运行体没有第二次使用，size证明是Prop，检查只取f/d标量，不捕获out。这支持唯一所有权预期；新C是否引入inc或保留别名仍UNKNOWN。d0跨第二字段检查存活，可能有准备期spill，不能当不存在。

失败树明确：当前tile的FloatArray是full capacity2*n、已初始化2*k字段；外Array预分配T槽、已存t个完整tile。左检查失败不读取右字段；右失败不push当前任一字段。`none`不返回这些缓存，任何FloatArray都没有指向原B或其它tile的back-reference；只有原A/B被guard保留给完整B2 fallback。失败前尚未分配新输出Array。成功输出则继续保留原rawA/B给原finish/NaN replay。

固定object.cpp389–397：释放普通Array逐个dec其**size**内子对象，再free容器；释放ScalarArray直接free整块，double字段无RC遍历。因此失败前缀的可达数据树可完整回收，不依赖清空未初始化capacity槽。当前tile和已完成tile都无循环引用。**实际decrement位置、是否在原B2 fallback前完成、allocator缓存/RSS是否下降未实测，不能声称已观测零泄漏或立即返还OS。** 新C将来需核每个none出口释放current buffer和outer prefix，且准备返回后没有旧缓存活跃；这不是新增CI请求。

若第t组失败，失败前已请求的缓存容量（不计临时some/闭包/输入）为`24+8T+(t+1)*(24+16n)`，与当前只成功多少k无关。第一字段失败也会浪费完整outer和当前tile容量；随后还要付完整原B2。检查必过定理不存在，真实失败率UNKNOWN。

## odd与最小n

保留原odd右物理读：p2/4/6/8无额外列，p3/5/7每k多1个无效字段，比例分别1/3、1/5、1/7；新方案同样检查、存储、热窄化并计算该lane，最后不emit。它可能读下一行/批或default，绝不能在成本账中抹掉。T=0时builder没有tile，但实际empty A/B通常先走原underflow-zero；n1、m<4、p1及p>8均完整B2路线。

每次成功准备的源级事件：2N原B解码、2N宽化、2N检查窄化、4N toBits表达式、2N push；热循环mN原A解码和原2mN F32链更新不变，新加2mN窄化及2*k/2*k+1索引计算。结果F2对象和原finish输出未删除。上述表达式可能被编译器简化，真实指令/FFI/分配/耗时全部需实际调用证据。当前只作为下轮固定源的审核清单。
