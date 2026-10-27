# RNE偏置公式：历史复用种子，不是新性能路线

**同式已有。** R14的astra-biased-rne3、Nat-only和f30f16a7 quotient版已含k23/24的同一ties-to-even偏置公式及UInt64桥。30c5b4d8最小探针在40153361143实际未通过；原记录是exit−15、空Lean文本，原因UNKNOWN。不能把今天的整理当新发现或已解决当年的终止原因。

本轮只保留4307B的BranchlessRNE-seed.lean.inc，SHA5a06c12700e015d3aecbfdbcd2abe879d2bbd68f0d7ed8d75f29289806652279：逐段复用原Nat quotient证明尝试，再写括号明确的N+(half−1)+parity与产品上界专用word桥，最后连接B2已验FastMul.rseAny_eq及k23/24时rseAny=rse。所有正文有证明尝试，没有加入占位证明；**NOT_COMPILED**，Nat历史缺口仍在依赖链内。

完整整数界：half为2^22或2^23，故half−1不下溢；parity∈{0,1}。当N≤(2^24−1)^2=281474943156225时，biased_sum≤281474951544833<2^48<2^64，两次UInt64加法均不回卷。实际移位k为23/24，half移位k−1为22/23，均小于64，无shift-count模64别名。该种子不假设q永远小于2^24；primitive等价覆盖其完整受限域，后续乘法归一化另证。

三个最小判别已做：偶平局必须保留−1；奇平局必须加商最低位；最大产品的biased_sum仍安全。另给N=2^64−1的域外反例：同UInt64表达式回卷后为0，而正确RNE为2199023255552，说明上界不可删除。见boundaries.json；仅三项定向整数检查，不是形式化验收或计时。

固定API来自FloatLib0d918257（FloatLib Team/MIT）的roundShiftRightEven_eq_roundQuotientEven及FixedWord.roundShiftRightEven_toNat；Lean293d5d0c的Nat.add_mul_div_left、UInt64.toNat_add/sub/shiftRight与Nat低位mask恒等式支持无回卷桥。原源码路径和哈希在status.json。建议下轮只先检查这个Nat证明及word桥，并保留正控与完整stderr；若再无诊断终止，应调查执行原因，不继续换同义proof。

9038完整正常域整数核MUL1.29080、whole1.04714负结果保留；本轮00ab全gate正确但whole1.01402/MUL1.03257、p05<0同样固定。偏置写法少显式分支不证明更快：旧rse可能已被编译成cmov，实际指令、寄存器与完整guard/fallback成本仍UNKNOWN。本轮不建完整候选、不CI、不占ADD93cc队列，不改00ab/93cc，11:20前停止此研究块。
