# R10矩阵检查点

共同窗口17:00:31—19:00:31 UTC，第一JSON检查点17:08:11。选定**n=1原生乘积＋原字负零归一化**，保留所有n≠1的41路径；不接入R9负面的numeric decoder或native NaN重放。

已有821/822各2个n=1案例，输出184440/352867，其中822两个案例落在subnormal。当前通用direct dot仍需Nat循环、初始+0加法及终点/重放；n1专化能用一项乘积和原字负零归一化消掉这些步骤。该输出数和cell时间都不是可省成本，native乘法本身及NaN回退仍在。选择native乘积是保持原n1乘法数据通路，不与D的低指数word路线混合。

备选DirectSmall USize覆盖仍Nat的direct n≤4/longthin p≤2，已暴露longthin工作量约536724/542429；但新stride-B边界、巨大Nat回退及循环等式证明更多。Packed10已经USize，不复制旧宽度网格。

现存47d singleton-native-normalize尚未完整验收，不继承其NOT_RUN之外结论。已有W10/W10b数学证明及其c44c端口、nativeProduct精确桥和singleton地址证明可复用。原4ba的失败是Fin.val_zero证明目标未闭合，后续dab已准备对应修复；不是性能反例。

本次将精确47d追加块机械接到41，并只把c44c内两个重复classifier证明委托给41已验R7W05引理，避免重新引入已知的字面BitVec位宽改写歧义。旧47d实际未编译，不能说它已发生该错误。所有运行体及许可保留，最终新全源仍需D原完整gate。

首稿目标17:25前，三个不同新输入组的原完整验收由D负责；不查看未来种子，不Git/CI/工具链或派发其他执行者。

## 可冻结的单一候选

[f01-r10-bmm-singleton-native](../../f01-r10-bmm-singleton-native/Kernel.lean)：**ff34b1b7e2166b7b22f53d5f3e656b6567fd7487d457343e3599885757ab25ad**，247919B，余8081B。完整Lean/fullgate/C/性能均NOT_RUN。

精确运行父本41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7，235169B；机制来源47d429fe3a351a5e002f98c1f4cb95dfdc04368c268275508be758d176f3a347，188335B。旧47d的全部追加块来自97f基座，本次先反向/正向完整复现47d，再映射到41；不运行会覆盖旧源的原builder。

原41只有最终bmm/spec的616B区作标识符重命名，成为676B的bmmBeforeSingleton/spec，其函数体不改。原区后的9510B（包括完整单遍sum及其已验修复）逐字节保留；其他prefix也原样保留。新增12688B追加块；剥离它并反向重命名即可恢复完整41哈希。独立核对用实际namespace边界重新定位，不依赖builder保存的偏移。

三个关键运行体均与47d逐字节相同：raw负零normalizer、nativeProduct和singletonCore。两个classifier证明的完整前后文本/哈希在JSON：原命题类型不变，直接使用Submission.R7W05.model_toModel_isNaN和toFloat32_isNaN。此举复用当前父本已有证明，不能说旧47d已被编译否决。

## 全输入语义与具体证伪点

- nativeProduct只有一个绑定的原生乘积。结果非NaN时，由mul_inputs、ofFloat32Mul和两次非NaNroundtrip恢复精确原字乘积，覆盖Inf、次正规数和±0；结果NaN时重用原始x/y走Submission.mul，保留payload/sign及sNaN优先级，不能用canonical native NaN冒充raw产品。
- 初始+0加法不能直接删除。单独乘积-0须变成+0；其他乘积原字保留。一般sNaN输入q不满足这个normalizer恒等式，例如q=7f800011时normalizer仍为7f800011，但add(+0,q)=7fc00011。这里先证明产品不sNaN，再接种子等式，没有放宽前提。
- n=1的A/B地址仍是原reference的k=0表达式及getD默认posZero；batch/m/p任意，空输出无需正维度假设。旧4ba残留的Fin零索引归约已通过复制dab的Fin.val_zero修复保留，但这份新组合仍须实际Lean。
- n=0和所有n≠1仍走原41分派，只有一次新增n=1分支判断。源正文不变不保证二进制布局/计时不变，应保留这些控制项。

首个实际证伪是整份新Kernel的statement：检查seed端口的native_posZero_add、native/raw负零对应、quiet NaN加零、nativeProduct_eq及singleton的两个rewrite/Fin.foldl收尾。随后才是原四义务、内核重放、仅三允许公理、全部checksum和25轮。静态检查与16项历史定向模型不替代此验收。

## 完整成本和与D路线的边界

本稿保留原n1的native乘法，主要移除通用dot循环、初始native加法、终点/重放框架。乘法本身可能仍有次正规硬件成本，NaN路径也仍付native试算和精确回退；rawnormalizer、封装、地址和输出构造均计入成本。不能用n1输出数直接分配一个cell耗时，更不能把subnormal完整cell视为可回收时间。

本稿与D的低指数word试验隔离。若将来合成，singleton原生helper会绕开NativeFinal.dotLoop；只叠加D对旧loop的改动不会让n1使用word乘法，需要真实接线与重新验证，不能相加两条收益。

建议D直接对精确新源和41做原完整gate（其本身先验statement），关闭observer。若发现样本值得采用，冻结同源完成另外两个未参与选择的新输入组，三组均保留，任一不达既定门槛不隐去。当前没有选过未来种子，也没有本地计时或工具链动作。

## D的小n展开稿：只读反馈

精确d70ebe881ce9c9cd48e83eb02b71b41f50340746717e8b461c6da65e766ed791，236880B。独立移除42行新增NativeFinal块、逆回DirectSmall的两处运行/证明引用后，恢复完整41字节。未发现确定源码错误；未执行D builder或修改D源。

嵌套Nat分支覆盖0、1、2、3、4和剩余≥5，固定小n的simp目标只展开相应dotLoop方程；最后分支是原dotLoop的定义相等。初始+0、每次mul后add顺序、最终NaN判据和精确raw replay保留。NativeFinal.dot本身及packed共享证明未改，避免R9直接改dotLoop牵动packed等式的问题。仍需实际Lean验证。

成本风险：n≥5的long-thin每个输出仍多经过一次n分类后才调用原loop；“回退源码相同”不等于零开销。它保留初始+0浮点加法，与R的n1归一化方案不同；两者在n1重叠，不能直接相加收益。

## DirectSmall USize：下一份最小可证设计

只覆盖n>4、p≤2的long-thin direct；不扩大n≤4网格或packed宽度。优先把n/p和两数组长度可表示为USize的guard放在整次矩阵入口，利用Packed10.decode_bounds为每个输出证明地址范围，避免每个dot重复做六项guard。循环保持baseA+k、baseB+k*p的机器整数计算和原native乘加顺序。

复用Packed10Index.addNat/stepNat/next_decreases/boundA；新增必要部分是strided-B乘法不回绕、Matrix坐标到首尾地址界、uget=getD及逐步循环等式。n或尺寸超USize范围时走原41，不删巨大Nat域。第一风险是这些全输入地址义务和一次guard是否足够，先闭合最小设计再决定出源；最迟18:15交候选或具体缺口。

## n1已取得的实际反馈

D保存的result-846-f01-r10-bmm-singleton-native.json：run39994377803，ff34及41原完整gate均通过，完整checksum/25轮。整包比0.9904540223，BMM比0.9621232175，局部gain_p05=-0.0013665；未达冻结的整包≤0.97且p05>0门槛，不采纳、不换基准。证明接受与性能采用分列，旧创建时NOT_RUN清单不改写成历史已知。

## long-thin USize完整稿

[f01-r10-bmm-longthin-usize](../../f01-r10-bmm-longthin-usize/Kernel.lean)：**f278796997dc8ca584ec661ea2f253e5174b95fedbd6268e11152040ce29d736**，243876B，余12124B，独立对照仍为精确41。

改动是整矩阵入口一次判断n>4、p≤2以及n/p/A.size/B.size可表示为USize，再构造新core。每输出仍使用原bmmDecodeC和Nat基地址，只把count/base/stride转换一次；每MAC的k推进、baseA+k、baseB+k*p是机器整数。新loop通过实际地址证明使用uget，避免重复getD范围检查。没有修改乘法decoder或浮点算术，也没有使用R9 native NaN重放。所有其他形状/超范围路径调用原41分派。

地址证明的闭合点：

1. row_lt用外坐标和内坐标界推出row-major线性界；Packed10.decode_bounds提供每个实际输出q的b/i/j界。A索引用两次row_lt；B先用原index_address重排为(b*n+k)*p+j，再用两次row_lt。它覆盖任意batch/m/n/p；空输出没有q，无额外非空假设。
2. 活跃k<count时，实际地址<A/B.size<USize.size。由此证明k*stride及baseB+k*stride不回绕，A地址复用Packed10Index.addNat。count后继复用stepNat/next_decreases。
3. 地址只在k<count分支计算，不要求退出后下一B指针仍可表示。所有proof参数为Prop；预期编译后不产生每MAC检查，但实际C尚未观察。
4. raw_uget_eq_getD连接同一输入word，loop_eq保持逐步native乘加；nativeWithin_eq和dotWithin_eq恢复原NativeFinal.dotLoop/dot，最终core和bmm_spec接原全输入义务。终点NaN仍用41原字重放，保留payload/优先级。

独立字节检查：只把原bmm/spec做可逆重命名，再追加8641B；旧NativeFinal.dotLoop、DirectSmall/packed声明、scalar、sum和所有许可均未改。解出实际替换边界并去掉追加块可恢复完整41。没有执行任何写入旧候选的builder。

有限地址筛查覆盖9360组小整数维度、2552组guard接受情形、63233个MAC地址；另检查真实32/64位size边界以及“最后一次后指针本会回绕、但循环已退出”的定向例。结果只支持这些整数模型，没有真实Array/Float32运行或Lean接受。

首个实际可证伪点是新完整源的matrix_bounds、strided_nat、uget重写和循环归纳能否被Lean4.34接受；随后看原完整gate。若通过，检查实际C确实是机器索引而非把Nat转换留在内循环，并在完整成本中保留入口guard、每输出转换、地址解码、旧NaN回放及未改控制组。新核心省的是long-thin索引，不是全部BMM或整cell时间；收益UNKNOWN。

此稿尚未与n1或D的地址/按行输出稿合成。按当前两个R稿简单累计可能接近或超过源大小上限，真正合成需要重新核共享代码、精确接线与完整gate，不能相加收益。R不决定额外CI占位，D根据剩余验证容量选择。
