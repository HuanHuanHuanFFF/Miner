# Broad-word ADD：最小数学接口映射

对象是 C 冻结运行片5655df5c、诊断02747632；A不改它们。15分钟阶段23:30:40—23:45:40 UTC，共同截止不变。这里只查现成根并补三个小稿，不铺公共ADD/全部GRS/候选或CI。

## 已有资产的真实范围

- **已验 jam**：C已独立绑定 R19 b372/40435830288/15根；`R19JamVariableProbe.rne_jam`仅最终k=2/3/4，覆盖任意p,d。`lowJam_ge`与`lowJam_lt_even`可在H=2^27的偶边界复用首carry判别。它们不直接证明d>=25同号normal吸收，也不是UInt32字段桥。
- **SameSignGRS/T0 名称未定位**：本轮A/C在当前源码、报告、helper审计及CI源检索未找到这个已验精确根。不能据语义标签宣布已证明；若有另一原件指针可替代以下小稿。T=0相关旧GRS分支也不可代替同号normal的大gap吸收。
- **旧bias**：`BranchlessRNESeed.quotient_bias`是private泛half Nat公式；014acd/40425497337有完整typecheck进程exit0/5.905s，但该证据不等于整个新helper重放/审计。公开`nat_bias`/`nat_grouped_bias`仅t=23或24；`word_grouped`是UInt64、48-bit乘积界。不能直接拿来充当新UInt32/k3定理。原巨大DirectBias模块失败/部分OOM与当时UNKNOWN都保留。
- **旧负面不重置**：6bef纯word GRS旧UInt64/排序/tuple/d>27/overflow fallback bench-only whole/旧参照1.09609；R19带cast GRS仍有toFloat32/toBits/postE等不同运行路径。新5655为同号normal、全gap UInt32、d>=25直返、bias RNE和加法pack；这些差异只说明需要实际完整成本，不是收益。

## 三个真实小缺口

`MinimalRounding.lean.inc`仅三根，全部NOT_RUN：

1. `nat_bias3`：`(n+3+(n/8)%2)/8 = RSE n 3`。固定8余数/商奇偶的线性证明，借旧商分解思路，不搬23/24位大证明。
2. `u32_bias3_correct`：n.toNat<2^28时，**显式给出两次UInt32加法总和无回卷**及源码`(n+3+((n>>3)&1))>>3`的toNat=RSE(n,3)。不增加原运行guard。
3. `far_round_absorb`：lo<2^24、d>=25 ⇒ `RSE(hi*2^d+lo,d)=hi`；hi为任意Nat。此时2*lo<2^d严格小于half，不存在tie。**这里只闭Nat舍入；到同号normal Model.add/原raw hi仍须原dyadic、leading/scale及字段接线。**

## 接线不能丢的边界

C的R19 jam图已给 no-carry用`rne_jam P d 3`；carry1先`rne_jam T 1 3`再`rne_jam P d 4`，无需新jam-composition。未验`jam_add_even`仍是一个独立小缺口，不在本稿偷补。

新RNE后可有**第二次carry**：T=2^27−4时第一carry=0，但RSE3(T)=2^24。e=127的hi=0x3fffffff、lo=0x33800000应经加法pack得0x40000000；掩掉隐藏位再OR旧e会错成0x3f800000。e=254同形边界应得到signedInf。5655的`((e−1)<<23)+m`正用于保留这一carry，不能回写旧OR-fraction式。

n<2^28只足够证明bias无回卷；若要m<=2^24，还必须另证源码首carry/jam归一后的n界。完整工程还缺UInt32 jam/guard/排序无wrap、normalized范围、normal signed Model.add、overflow与fallback接线。成本先决定是否继续，不把这些小稿或有限模型当公共add_spec。

原始指针：R19 `bias-frontier/Retained-BranchlessRNE-seed.lean.inc`、`prefix-review-40425497337.json`；C `BROAD-WORD-PROOF-INTERFACE.md`及`broad-word-history-verified.json`。精确源码/有限反例与hash见本目录manifest及检查脚本。
