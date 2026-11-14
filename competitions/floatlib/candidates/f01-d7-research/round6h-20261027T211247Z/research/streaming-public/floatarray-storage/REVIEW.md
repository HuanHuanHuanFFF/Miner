# FloatArray 作为 B2 的连续 binary64 存储：成本前提审核

阶段首工具2026-10-28 **00:56:40 UTC**，20分钟上限01:16:40；共同截止03:12:47不变。只读历史/固定源，无新Kernel、运行片段、公共证明或CI。B另负责“校验回原nativeB”的最小语义桥。

**结论：没有每k外部宽转换FFI这个关闭理由；当前B-only、每组两列连续存储仍是未测的精确成本条件。不能无校验采用opaque往返；也不能把全A/B旧布局或DoubleScale算术表的结果继承给它。** 新路线有合法旧检查接口可复用，但目前没有packet/header成本占主导的测量，不宣称整包收益或立即排队。

## 固定 API 与真实代价

已重哈希Lean293d的`lean.h`，SHA982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13。3274–3275的`lean_float_to_float32(double)`/`lean_float32_to_float(float)`均为`static inline`单个C cast；1243–1248的uget/fget直接读double。这里没有必须调用的外部转换函数，实际新caller的机器指令/SLP仍UNKNOWN。

标准`FloatArray/Basic` SHA80f3eff556a5316357ceff025f8b094f9c47915abdb61d4bbb843b92bc8075de：`emptyWithCapacity`、`push`、`get (i:Nat)(h:i<size)`、`uget (i:USize)(h:i.toNat<size)`全部公开合法；没有名为getUSize的API。get/uget的界证擦除，运行读取不通过`.data`。USize偏移2*k+1仍要有不回卷的界；现B2本来用Nat，不能为了引用uget就默加机器尺寸假设。可先保留Nat get的真实界证，随后由D实际C判别地址计算成本。

FloatArray是double连续payload，每标量8B；不是Float32Array。`push`在header中是LEAN_EXPORT，在固定object.cpp2692–2698检查容量、独占性并写入double，属于**准备阶段的实际调用和所有权成本**。预分配2*n消除正常扩容意图，不自动证明无共享复制。`FloatArray.mk`从Array Float逐个拆箱，`.data`反向逐个装箱；新的单遍准备不得走这两条路径。

两个跨宽函数在逻辑源中仍opaque（Float32.lean548/555）；C中的精确提升不能直接充作Lean等式。所需动态条件只在准备时检查，热循环不加位检查。

## 旧实现与原采样范围

| 旧精确源 | 已有机制 | 原证据/边界 |
|---|---|---|
| 5be0735a/64087B，f01-d2-checked-floatarray | 全A/B先all(checkOne)，每输入一次raw往返校验；再map encode及FloatArray.mk；单输出dot热读两次narrow，保持F32乘加；旧final-isFinite失败原dot回放 | 39663131701 seed309原full gate PASS/25轮。与同job Array Float32 preconverted的dense/relu/wide BMM，原ns比1.002048/1.000033/1.002053，各自参照归一化比1.003047/1.004409/1.002657，基本持平。独立候选/reference gate，非逐轮直接A/B。 |
| 98cef0f2/68415B，DeepSeek R2-W04，f01-d3-fused-floatarray | `let d:=encode x; if checkOne x d then out.push d`单遍；检查和存储同一d，无中间Array Float；热dot与5be相同 | 39724650290 seed403原full gate PASS/25轮，whole/shipped .309663。不同seed，不能用它与5be .322128的比值解释融合收益；更不是相对当前B2性能。 |
| R17 structural-frontier | 重新核fixed API/opaque，已明确旧checked方案存在；转temporal字段包 | 未做新的B-only FloatArray完整成本。R20 postfreeze同样关闭“免费F32状态容器”，因为每MAC变化的acc若动态校验会增加热成本；本次只准备只读B不同。 |
| R19 CompactScales/DoubleScale相关 | FloatArray存512个静态scale或以Double参与算术/codec | 这些不是B2-only两列B缓存，不继承其负面归因。CompactScales完整旧负面仍保留在原报告。 |

5be旧生成C审计`codegen-audit-39661096034.json`记录选中dot有2个FloatArray fget、2个inline narrowing、0个raw conversion、0个`.data`；输入验证和final回放并非每MAC检查。本次重读了这个hash-bound审计，但它引用的原`candidate-generated-0.c`路径当前缺失，**未声称本次重新核过其原C字节/ASM**。固定header/API、旧Kernel和原verdict字节已重新核。R9–R20/材料的限定文本检索未找到当前“保rawA、两列B组、只替换B2内部储存”的精确完整成本；这是有界调查，不是穷尽新颖性证明。

## 唯一新运行差异与投影

固定当前B2的underflow分派、p2..8/n>1/m>=4入口和原fallback。外层仍按`(batch,group)`选只读tile。每tile预分配2*n个double，按k顺序push左右两字段；读地址为2*k、2*k+1。原A读取/解码、两个F32 accumulator、每k先乘后加、原k次序、group/row输出都保持。不得在double中累积，也不得在double做乘法后只最终narrow。

准备时绑定原native值`f := ExecFloat.Binary.toFloat32 rawB`和存储值`d := f.toFloat`，检查`ofFloat32(d.toFloat32)`与`ofFloat32(f)`的raw相同。**不是要求等于原rawB**：现B2没有allfinite guard，非canonical rawNaN可能已经由原codec变成nativeNaN。旧rawB检查仍正确但会收窄快路覆盖；新的native目标检查由B给语义桥。若检查失败，释放已构造prefix/tile并回现B2完整原始调用。成功时loop只有get/narrow/F32 arithmetic，不重复检查。

每有效lane目标为`stored[t][2*k+c].toFloat32 = toFloat32(Braw.getD(base+k*p+c) posZero)`。旧`CheckedFloatArray.checkOne_eq`给ofFloat32等式，`congrArg toFloat32`和现成`ExecFloat.Binary.toFloat32_ofFloat32`给native值等式；检查目标改为原native时按B接口同理。不需要新Float64数值理论。投影成功即可逐步回现R15PackedB2两条原序链，再复用Packed10.finish/原NaN replay和group/row/output运输。仍需新tile的成功Prefix、2*k+c边界及outer成功传播；不复制旧final-isFinite回放到现nonNaN finish。

奇p最后右字段无有效输出；原B2会额外读下一行/批或default。若保留该物理读/检查就计入其成本；若改成固定padding，证明只承诺有效lane且不能假设它与旧无效字段相等。每batch的base独立，不允许平铺后跨batch配对输出。原rawA/B始终保留用于原finish回放。

## 无计时成本账与最小判别

G=ceil(p/2)，N=batch*G*n，假定准备成功且与旧B2相同字段数。条件64位请求模型：旧每F2为8B header+8B scalar+8B指针槽=24B；新两个double=16B。N个F2对象及其槽位被取消，outer/inner容器仍在；payload本身从8N增至16N。每k从“槽指针+两个F32字段”变成“两double连续读+两narrow”，消除一次依赖指针取数，但不能仅从载入条数预测速度。已有temporal B8的4k请求48B还小于FloatArray的64B；旧temporal负面不自动否定不同读取链。

新增准备工作含每字段widen、narrow、位校验、FloatArray.push、prefix失败释放。以native两边toBits直接检查计，**每字段2个toBits**；若B能给原codec canonical raw的廉价等式才可另行减少，当前不能偷算成0或1。旧F2标量没有逐字段Float32 box，不能把不存在的两份box再次算作节省。新热循环保留A codec；若两narrow或live值跨codec新增spill，可能抵销删除packet指针的收益。

最小D判别只需一个实际B-only pair caller：先检查成功准备没有Array Float中间体、`.data`、每步Option/字段box；hot loop没有外部转换/回调、校验或分配，cast确实先于F32 mul/add，原finish仍用raw。随后完整cost必须含全部prepare/check/push、失败prefix/fallback、原输出与释放。保留所有旧慢样本；不先开宽度、阈值、seed网格。当前没有该精确运行体或成本，是否值得本窗口一个槽由D现有队列决定。
