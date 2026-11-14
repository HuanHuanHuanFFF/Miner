# R22 A：native BEq 只读前提筛

阶段 **02:28:00—02:38:00 UTC**；共同截止03:12:47。未新增运行体、Kernel、Lean证明、CI；f59d及所有旧源不改，不读当前确认输入/结果。

**本轮关闭实现推进：没有找到现成的两变量native BEq→word等价根。** 限定源码调查没有推翻“source非零且非NaN时可等价”的数学前提，但不能用nativeBEq当propositional Eq，也不能用FloatLib的EReal比较定理直接替代这个缺口。

固定Lean293d `Float32.beq`165–168经Model.beq到UnpackedFloat.beq，后者定义为`a.compare b == some .eq`。本次取回的Unpacked/Operations/Compare.lean逐分支表明：NaN任一侧都是none；两个zero不看sign直接eq；infinity仅相同sign可能eq，±Inf与finite/zero不等；同sign finite按exponent再mantissa字典序比较（negative再swap），异sign finite不等。这是全构造器的源码事实，不只测试normal finite。

可复用的最小未闭接口是：对Unpacked source排除notANumber/zero后，`source.beq back=true → source=back`。same-sign finite只需Int/Nat compare和Ordering.then的等号反演；infinity分两sign，back其余kind均排除。这里不需要从相同实数重新证明编码唯一性。随后借已在B2 `R7W05.native_eq_nan_of_isNaN`中使用的`Model.toFloat32Model_ofFloat32Model m`（即`pack m.unpack=m`）运输回Float32 Eq。**该两变量helper未找到现成声明，也未编写/编译。**

另一个未闭接线是raw source的`0<absraw≤Inf`到native unpack非zero/非NaN。非NaN已有R7W12 classifier；非zero可望用37cd import word及两种packed-zero闭值关闭，但本筛没有把这个希望升级成证明。反向Eq→BEq true已有R7W04.self_beq_eq_not_isNaN；word检查→native Eq可复用fb7d.checked_native。主缺口仍是上述forward和raw非zero运输。

反例边界明确：`+0 == -0`为true而word不同；canonical NaN与自身word相等但BEq为false。因此这两类必须继续旧word检查。source +Inf/back +Inf、source -Inf/back -Inf同号成立；异号Inf、Inf与任意finite/zero/NaN都不成立，不能把±Inf悄悄排除或当作finite处理。

固定FloatLib0d918 `Operations/Compare/Proof`的`compare_eq_some_eq_iff_toReal_eq`仅finite decoded model；`compare_eq_some_eq_iff_toEReal_eq`含Inf但仍是Model数值比较，不是nativeFloat32 BEq或raw-word反演。已读取的Native目录及Native.Model未给这条现成桥；这是有界检索，不宣称全库不存在。primary/保存固定源码和来源，manifest保存SHA。

即使未来证明闭合，source值为零/NaN的字段仍有backcast.toBits；普通字段会以native比较换该表达式，并增加源域分派。准备成功率、真实FFI/CSE、额外分支/寄存器和整包收益均UNKNOWN。当前不造新比较器，不扩确认队列。
