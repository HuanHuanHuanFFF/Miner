# DirectBias 公共接线接口表（只读审查，未生成公共源）

**00:15更新：此表保留为组装前历史。新的完整79e8及proof-only review1/fa6529已出现，缺口已在源码层补，实际余量689B；当前结论请读`PUBLIC-REVIEW1.md`，不要把本表缺口/预算当作新源现状。**

2026-10-27 00:11Z。**数学前提未发现与7489实际caller冲突，但现有四段尚不构成公共证明。** 原seed/PostBias/WordBias/FastMulBoundary组合仍NOT_RUN；7489只证明三个运行定义可编译及旧public规格，不能替代下表缺口。以下`p`为实际24位尾数UInt64乘积，`S`为两UInt32指数之和，`B`为偏置后的UInt64；`q_old`是原RNE商。

| 实际运行边界 | 已有精确接口及前提 | 公共桥仍须关闭 |
|---|---|---|
| `eu/ev=(raw>>>23)&255`；`eu-1≤253 ∧ ev-1≤253`，继而`S-128≤252` | B2 `FastMul.expField_toNat`；原guard是UInt32模减 | 推出`1≤eu,ev≤254`、`S.toNat=eu.toNat+ev.toNat`和`128≤S.toNat≤380`。不能在下界未得前把word减法当Nat减法。B2没有`R14ExponentShift.eligible_conditions/sum_nat`。 |
| `a/b=(raw&0x7fffff)|0x800000`，`p=a.toUInt64*b.toUInt64` | 顶层`R2W01c.mantissa_bounds`对任意raw给`2^23≤a,b<2^24` | 证明实际word乘法不回卷，`2^46≤p.toNat≤(2^24−1)^2=281474943156225`。B2没有Jam额外的`R14ExponentShift.product_bounds`。无需旧`NormalBand`的指数≥24条件。 |
| 按`p<2^47`选择literal23/24及0x3fffff/0x7fffff，得到B | `Submission.R19DirectBiasWord.biasedWord_nat p hp`；只需上述上界；依赖`biased_sum_nat` | 实际literal表达式与`biasedWord p`展开后吻合；应在证明中fold/unfold，保持已编译runtime定义原样。该层不能只用seed的“舍入后商相等”代替未右移B的等式。 |
| `h=B>>>47`；`q=(B>>>(23+h)).toUInt32` | Word的`highWord_nat/highWord_le_one/shiftWord_nat/mantissaWord_nat`，需P上下界；PostBias `normalized_quotient` | 得`h∈{0,1}`、shift23/24且小于64、narrow不丢值；再用Shape `literal_shift_eq`将literal shift接到`log2(p)−23`。`h=(log2(p)−46)+carry`，`q=旧normalizedMantissa`仍须在实际字段等式中组合。 |
| 旧normal `FastMul.roundP sign p (S.toUInt64−2)` | Shape `roundP_normal`需P上下界及`128≤S≤380`；其`normalized_position_le`给≤425 | 该定理只化简旧函数；它没有断言新`normalCore`等于旧函数。还需将Word high/mantissa和旧`rounded_word_nat`连接。h=1后的carry排除依赖精确产品上界，不可放宽到任意`p<2^48`。 |
| 新`e=S−127+h.toUInt32`、`f=q−0x800000`；直接OR打包 | Shape `mantissa_bounds`加literal-shift桥可给`2^23≤q<2^24`；S/h可给`1≤e≤254` | 证明e/f的word减法无回卷；e等于旧`normalizedPosition−171`，f等于旧`fracW`；消去`mkW`额外的8bit/23bit mask。当前四段没有新encoded-exponent/最终word打包等式。 |
| 旧`FastMul.core rawu rawv`实际有限字段 | 固定FloatLib `NativeBinary32.finiteMantissa_toNat`需fraction<2^23；B2 `UnderflowZero.finiteScale_toNat`；`FastMul.sm1_eq` | 正常输入下finiteMantissa等于上述a/b，finiteScale之和等于`S.toUInt64−2`；`((u xor v)&signMask)`等于旧Bool.xor(signBit)符号字。新normalCore对任意raw及S范围即可证明word层，normal前提只在连接旧输入字段/排special时使用。 |
| `R7W02.fromRaw`返回新word；域外原fallback | 两载体定义均为`ExecFloat.ofRaw`相同UInt32及界证明；B2 `FastMul.mul_spec` | 以普通展开/证明无关性检查载体等式（新Lean验收仍未跑），经旧FastMul规格得域内结果，再用fallback规格覆盖所有miss。不要加入native cast语义桥；±0/subnormal/Inf/所有NaN payload均仍由原guard/fallback承担。 |

**字节预算（UTF-8原字节；只在内存组合，没有写Kernel）：**

| 组合 | 字节 | 距256000余量，尚未计新桥/公共包装 |
|---|---:|---:|
| B2 226829 + seed4307 + PostBias2839 + WordBias5228 + Boundary7039 + 精确runtime1358 | 247600 | 8400 |
| 上项整体按既有方式`Submission→R19Base` | 247342 | 8658 |
| seed仅保留当前Nat依赖闭包2018B，其余不变 | 245311 | 10689 |
| 上项再作同样命名空间替换 | 245065 | 10935 |

seed可不纳入的2289B为`grouped`定义、`word_grouped`、`grouped_eq_existing_rse`：当前PostBias只引用`nat_grouped_bias`，WordBias自己有未右移sum证明，Shape无这三项依赖。原4307B文件未改；此值是**当前依赖闭包的省略方案，不是最终公共证明的全局最小值**。private `quotient_bias`仍保留，故字节节省不构成历史OOM的修复证据。不要整段带入8609B Jam支持后仍沿用表中余量；若复用guard/product证明，应计其实际依赖及新字节。

**命名空间与根：** 顶层`BranchlessRNESeed`四个公开theorem、顶层`R19PostBias`三个，`Submission.R19DirectBiasWord`六个，`Submission.R19BiasShape`十二个；另有三个`Submission.R19DirectBias`运行定义及四public规格，共32个当前具名根。旧14根清单漏了Word6+Shape12；依赖闭包省略两seed theorem后为30根。`HelperAudit-current32.lean.inc`给现状原名，`helper-roots.json`给公共适配名。整体改名时Word/Shape/DirectBias及其`Submission.FastMul`引用一并变为R19Base，seed/PostBias名保持顶层；`R2W01c.*`也保持顶层。private quotient只由Nat根传递审计，不猜私有mangled名。新字段桥、core规格、guarded规格及真正public mul_spec仍须按**未来实际声明**加入，不以这32根宣称闭合。

公共包装由D负责：fallback必须绑定原B2，例如整体改名后的`R19Base.mul`，避免新`Submission.mul`自引用；新规格名称与类型仍满足原四义务。仅改命名空间的源也须重新核实际MainFull，不能直接继承7489的diagnostic机器码。若公共源新增/改动证明，重新绑定SHA后再审，本表不许可偷偷改已冻结runtime。

证据：`audit.json` SHA54659d2748fce61d7ffb9f4a477d92c3f5de32c0bf8655c7357f6666bea9d19b；四片段原SHA、运行1358B后缀SHA、全部当前声明和固定FloatLib0d918 primary源均在其中。原始256000 gate限制按官方4b7源码核定；本方无Lean/CI/Git，无第二runtime/公共wrapper。
