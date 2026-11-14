# R24 scalar：二次幂舍入边界，旧ContractTensor数学helper

**任意纯word提案**：arbitrary-proposal1 **e634d0ed578edf3172b0d4b95491003e87933d2f57665cbaa30f7fcc8586ae3e／69184B／29roots**。`ArbitraryProposal.lean.inc`新增1根check_sound，依赖下面normalized interval。hint仅UInt64 mask/add/shift→UInt32 subtract，不调用opaque Float.toFloat32，不证明guess准确；cert看独立exact normalized interval，sign由精确表达式给定，失败由caller保留完整fallback。121579模型；`3ff0000010000000→proposal3f800001≠RN3f800000`正确拒绝；普通even tie正确guess仍strict拒；跨binade power carry midpoint正确闭接受。所有typing/replay/AX/native/cost NOT_RUN，`READY-arbitrary-proposal.json`已交D，可后续统一island；不要求另CI、不声称真实机器收益。

**新区间端口待依赖typing**：interval-word1281 **b0bb8f5854632ee885fa5cdff06bbad5184243c86008ff4c85c45e8e0260a979／66946B／28roots**。`IntervalWord128.lean.inc`、`READY-interval-word128.json`。官方33KB四端点逐字前缀＋精确旧scope组件，strict interior或closed power/minnormal两端wordguard＋独立N enclosure inequalities→actual roundRatScaled/mkBits，runtime不构造actualN。350880区间、295203接受区间内点检查、4坏guard反例及policy/hash PASS；Lean/replay/AX/native/cost全NOT_RUN。**只接normalized N/D且D64**，P=(2^94+1)、D=(2^29+1)在目标scale42需D<<42成72bit，不能截断P丢sticky；反例在预检JSON。broad拥有singlepoint logicalscale，本组件不声称raw norm覆盖/外部scale完成。已交D可后续统一island，未要求单独CI。

**新独立fixed-word包待关键复核**：power-gap1281 **21489f2dbbc99628f27d0adc66237a1395580b4d5fd7fed9cb30eadb76b3d361／244750B／16roots**。`READY-power-gap128.json`，`PowerGap128.lean.inc`与`preflight-power-gap128.json`。输入UInt128 N、UInt64 D、UInt32 exponent；full128 gap高位必须0，先g<D且g≤D−g，再在lower/E≥2安全加倍并比较t≤D−t。真实powerCell→roundRatScaled/mkBits；E1半距、E≥2下侧四分之一距，闭even ties。精确提取broad冻结6a7e25…的gap与gap_toNat_cases，提取字节区间/hash在manifest。203968有限模型/源policy/hash预检PASS，5类反例；Lean/replay/AX/native/cost全部NOT_RUN。已交D复核，等待math2依赖实际typing，不改2960或对方文件。

**v2当前待gate**：power-cell2 **2960b3b79b1b2e4dda279878f4d610915893c8cc40633620b7190ad86951f344／236365B／11roots**。`READY-v2.json`与manifest；精确依赖broad `ClosedEven-v2.lean.inc`（6891bf…1533B），自己的normal两支改阶段式rounder→scale0/1→rw q→carry→field，E1独立subnormal。178232模型及policy/hash预检PASS，所有Lean/replay/AX仍NOT_RUN；已交D统一batch，旧e8不覆盖。

早期模型`GAP-BOUNDARY.md`：broad WordGap128 strict内部与本方power边界去重；153246完整word/rational样例及4个坏guard反例通过。现已另包写出原生边界版本，仍不从模型宣称机器收益。

**依赖停等，e8自身仍NOT_RUN**：CI40779515020的broad e1d2包在closed-even原体相同的`succ_eq_add_one` simp处失败，另有其内部word末端残留rounder目标。broad负责cell2，不重复修或把它当数学反例；e8冻结不覆盖，收到新精确body/hash后组power-cell2。本方power/carry/minnormal分支继续独立核；其qRNE结论是闭常量M或2M，且已显式展开scale/shift，与broad可变mant末端目标分开。

**首版准备快照**：`f01-r24-dev-scalar-power-cell1/Kernel.lean` **e8ca5e51bb5f5816e373b9576a6ab2897a4db614b3b3e4be841803417fd37129／235502B**。manifest列11根：4原B2规格、1复用broad闭区间even quotient、6新bounds/log22/log23/power/minnormal/checker真实桥。`READY.json`及`model-preflight.json`：178232有限rational模型（含全部254正规目标指数/符号/ties）、原policyregex、源/组件hash检查PASS；**Lean statement/replay/AX均NOT_RUN**。边界反例：N33554430/D4在E1给00800000且正确接受，在E2给00ffffff而目标01000000，错误uniform half-cell会误接受；本checker正确拒绝。未做任何native cost或性能声明。

共同截止2026-10-29T03:38:56Z，03:15后不请求长CI；D唯一Git/CI。仅本目录和`f01-r24-dev-scalar-*`可写。Sol/xhigh，无子agent、本机Lean/native、正式提交、资金。实际起点22:16Z；token/cache/CI占用UNKNOWN。

去重：broad已提供`development-broad/CellPrimitive.lean.inc`（a34107b6…/7767B），candidate `f01-r24-dev-broad-cell-primitive1` e1d2b23e…/234597B，11根NOT_RUN。其strict normal bridge只覆盖`2^23<mant<2^24`。本方只补`mant=2^23`，不重写内部桥。

固定FloatLib0d918257…，实际`NativeBinary32.roundRatScaled`在`Backends/Word/Narrow/Base/Runtime.lean`（blob dc080c68…）；Nat rational scale在`Numerics/Exact/RationalBinary.lean`（493364e2…），positive1用Nat.shiftLeft num1，zero有已证明simp。

目标：对任意num、den>0，e+150在1..254，若中点证书通过，则actual roundRatScaled sign num den e = mkBits sign (e+150).toNat 0，不引入抽象hcell或native猜值准确性假设。只复用broad exact `quotient_even_closed_midpoint` 原证明体作为依赖。

- 常量M=8388608恒even。E≥2时下界`D*(4M−1)≤4N`，上界`2N≤D*(2M+1)`；ratio可能落在binade22或23。上半段使用RNE(N/D)=M；下半段使用RNE(2N/D)=2M=2^24，真实roundercarry进入目标E。
- E=1（e=−149）下界改`D*(2M−1)≤2N`，同上界。ratio上半段走normal；下半段实际走subnormal分支，RNE(N/D)=M触发minnormal输出。不能把一般power2下界1/4沿用到这里。
- num=0/den=0/非normal目标拒绝，由未来caller原fallback处理；符号由精确原表达式提供，不能凭任意猜word符号省去检查。

下一：有限falsifier先覆盖两个边界和ties；写独立CellPower.lean.inc和旧B2前缀单数学候选，列精确根、源hash及未编译状态交D。依赖提取保留broad来源，不修改其文件。无新ContractExact Kernels或新赛道运行。

请求D：关键数学复核后可按原helper-audit-v8走statement＋两模块replay＋11root AX，不派性能/25轮；本agent不自行CI。若broad闭区间原证明体有typing修复，仅按其新精确版本重新提取本依赖，保留本轮源与失败，不手改对方冻结组件。
