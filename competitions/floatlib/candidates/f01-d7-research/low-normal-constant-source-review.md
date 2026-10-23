# W14b/W14c 常量来源修订独立审查

审查开始：2026-10-23 00:24:51 UTC；只读原件、轻量静态核对。结论绑定同名 JSON 中逐文件重新计算的 SHA-256。未修改 R、候选、官方文件，未运行 Lean/Linux 工具链、CI、目标对象或微基准。上一份 `low-normal-history-review` 的 W14 原始负面结论不变。

**W14b 确实消除了独立探针低 normal 小 Nat 暖循环的 once 分流及 FP spill；W14c 真实重新编译关闭了8192资源上限问题。未发现新确定证明错误。完整接线候选的 Lean、完整 gate、计时与收益仍为 NOT_RUN / UNKNOWN。**

## 精确来源与命题

下列文件位于 `competitions/floatlib/research/astra-collab-20261023-r7/web/<包>/original-extracted/<包>/`。原件在本地可定位；本审查没有将其重新发布。完整 SHA 和原日志路径见 JSON。

| 原件 | bytes | SHA-256 |
|---|---:|---|
| W13 `R7W13Increment.lean` | 14224 | `55ce42724776e218139bd702373829ca55910955c07f8f0821ba2feaf949b620` |
| W13b `R7W13bIncrement.lean` | 5624 | `f7d2cd47627ba56aa1f4d1b41800fdc289355587ed6b466dae8659d557db0e91` |
| W14b `source/ConstantSource.lean` | 786 | `e6a553e98ec595d4c38973d1251b337fb476e98bff2d1b2cc47bbff192218114` |
| W14b `source/R7W14b.lean` | 1436 | `fe9e76106e2030fd1a614073976c079150f20c1d4e2157f4693fbcb8a1bbd5dd` |
| W14c `source/ConstantSource.lean` | 785 | `fdce65a41e155b3009e5c4b10eab6020b37195081b0ca56bc154537274749663` |
| W14c `source/Host.lean` | 155871 | `65a78403229b21528d88964fdd05a381802f9ec2f43859b8e77ecd8249daf806` |

5624字节是 W13b 守卫增量，W14b 常量证明源仅786字节。W14b 原常量源第8、11、16、20行分别是索引恒等式、范围、实际函数和常量相等定理：

```lean
(u - u) + (118 : UInt32) = 118
constantFromTable u = Float32.ofBits 0x2f800000
```

两式均对任意 UInt32，不带指数或非 NaN 前提。`index_eq` 用普通 `simp`；`index_bound` 重写真实512项表大小后 `decide`；常量证明用真实 `scaleTable_entry ⟨118, ...⟩`，最后 `rfl` 计算 `scaleBits 118 = 0x2f800000`。实际表公式为 `(118-23)<<23`，正号、指数95，恰为2^-32。没有用浮点结合律或 native 证明计算代替舍入桥。

`Proof.lean` 的 `lowNormalDecode_eq_old` 比较实际新旧两个模块，**对全部 u 证明新旧 helper 相等**。它不把 helper 扩成全域正确解码器。独立核对：除 import、命名空间改名和右乘数 `Float32.ofBits 0x2f800000 → constantFromTable u` 外，原 W14 与 W14b 源逐字相同。

原成功日志 `proof-constant-03`、`proof-prototype-01`、`proof-helper-01`、`proof-axioms-01` 均显式 exit0；四条 axiom 原行只出现允许的 `propext / Classical.choice / Quot.sound`。默认深度首稿 exit1、第二稿多余 tactic 的 exit1 仍保留，未改成成功。

## 实际 C / 对象 / 暖循环

W14b 两份实际生成 C 的本地 SHA：`generated/ConstantSource.c` 为 `6ac827fe2e84a44517ff1ee7bc9081a3af72d4e07c407df99642096e8c5150a0`；`generated/R7W14b.c` 为 `982122f33474500c9ef705780a6553cfb53b59e86d1fd38419c77e53f006989f`。四个 Lean-C / clang 命令均 exit0。原 clang 参数含 `-O3 -ffp-contract=off -fPIC`，未补写没执行过的参数。

C 仍显式执行 `lean_uint32_sub(u,u)`、加118、转Nat、借用数组读与unbox：常量 C 第27–34行；内联 direct 第190–197行；loop 第393–402行。固定头文件 `lean_uint32_sub` 是无符号 `a1-a2`，`lean_float32_mul` 是 `a*b`。**消除整数恒等式是实际 clang 对象的事实，不能归给 Lean-C。**

保存的真实汇编中：

- `constantFromTable` 23字节，读取已有表指针，`+0xa mov 0x3c8(%rax),%rax`，`+0x11 movss 8(%rax),%xmm0`，返回。`0x3c8=24+118*8`。无输入寄存器计算、call、条件分支或栈帧。
- native helper 在 `+0x28/+0x34` 两次 `mulss`；新增常量是固定表项读取，不再是 once getter。
- research 小Nat loop 低normal路线 `+0xa2…+0xcd → +0x111 mulss → +0x41 addss`：第一次 `mulss` 在 `+0xc8`，常量表项在 `+0xcd`；该路径无call或 FP 栈读写。旧 W14 `+0x7d` 保存 / `+0xf1` 恢复与 once 分流不再位于新路径。
- fallback 仍在 `+0x30/+0x3b` 保存/恢复 acc，并于 `+0x36` call `lean_float32_of_bits`。慢 Nat、超小整数索引边界及冷 RC 路径仍有 call/spill。boxed adapters 和模块初始化不等于消失。

两个新对象的 C、符号及重定位均无新增 `once`，但仍依赖既有 scaleTable 初始化。对象未收入包，本地重新核的是 C、原 `objdump`、命令和对象元数据；原记录对象分别为10280字节/`4c53d6d6b16b71503d68b20bafafefbbe89bfeaf49ec9d225009191e5290fd8d`与3064字节/`b90047583d1ed969dbca8e245943bcd5339ec09c31c39e3a39b7b8bb00eb73f1`，未声称本机重算远程二进制哈希。

本审查独立解析保存的原 `objdump` 指令字节，复现：原对照 `originalConvert` 78字节、`originalLoop` 395字节与 W14 完全相同；research direct 普通表算术块 W14 `[0x66,0x8e)` 与 W14b `[0x5f,0x87)` 的40字节相同。**research loop 上端块43字节不相同**：寄存器、跳转方向和共享末次乘法布局改变。算术仍是原一次转换/读表/乘法，primitive语义保持；不能宣称整条 ordinary 机器路径或成本保持。

新增低normal仍需两次有依赖乘法、整数转浮点和表读取，ordinary另有守卫布局代价；完整 USize/Vector 求和代码未由这个 Nat/Array 探针证明。低normal出现次数不是耗时份额。没有微基准或完整计时，gain UNKNOWN。

## 8192实际编译与接入边界

W14c 于00:28:40回收。本审查逐字核对：新常量源唯一替换 `10000→8192`；Host 精确为原60f全部155103字节 + 换行 + 新常量源删除唯一 `import Submission` 行。Host中唯一资源选项为 `maxRecDepth 8192`；保留 `R7W14b` 命名空间，没有覆盖四entry。

`compile-ConstantSource` 与 `compile-Host` 为本轮新编译，均 exit0；Host从00:21:00.744690至00:21:19.196189。新 `LEAN_PATH` 首项 `/tmp/r7w14c-build`，不含旧 `/tmp/r7w14b-build`。`audit-standalone-01`、`audit-host-01` 均 exit0，Host有四spec的完整量词/输出函数等式 example，并检查原 VerifyFull 同一四义务合取。原始 axiom 输出分别4条/8条，只有允许三公理的子集；Host也审计了常量**定义**。

原全 gate import 因缺 `loguru` 的 policy-01 exit1 是加载失败。policy-02 从同一原 gate 的未改 AST 加载静态 policy/options，exit0。此处又以固定4b7原函数对确切 Host 字节重新静态执行，PASS；将原10000常量块附到公开60f会明确 FAIL：允许1..8192。**10000原成功源不能作为当前可用源；8192成功不再只是推测。**

W14c没有重生成C、重链、内核replay或完整gate。它仅追加常量块；**没有** W13/W13b 或新decoder运行接线。因此不得把上述四spec检查写成新decoder候选已通过。

## 声明依赖、映射与剩余判别

W13完整源63410字节精确以14224字节 Increment结尾；前49186字节与公开60f、准备稿父c760相同。W13b完整源精确以 W13 为前缀、以5624字节 Increment为后缀。数学前置接口已有真实同字节来源，不需借用旧有限native桥或额外 W05/W12 包。

终端依赖链为：`R7LowTableDecode.convert_eq` → `convert_eq_wrapper` → W13b `wrapper_eq_ofBits`；新helper通过 `constantFromTable_eq` 接 W13 `lowNormalDecode_eq`；后者使用真实 `R2W01c.native_mul_eq_of_decoded_raw_model_mul_eq`、`R2W01cModel.mul_eq_of_finite_value` 与已存在codec/分类/范围/舍入证明。W13b的 `low_false_minNormal_lowNormal` 将真实wrapped减法假分支和minNormal下界送入 E1..23域；不是仅用“小于Inf”的弱前提。

当前准备builder读取36条W13声明、14条W13b声明、常量块4条声明，再加tail5条声明；这是最少**来源族**的接线，尚未逐定理裁剪为最小闭包。只改新常量namespace为 `R7LowTableDecode`，保留W13/W13b命名空间与原父prefix；tail两桥仅按定义重写，静态未见前向名字或作用域错误。新数学reference helper可能仍生成旧常量once符号，不能从独立probe外推整个接线模块无once。

只读重现00:28所见builder的内存组合：174914字节，SHA `353d9816425d92fbc6d0cc14c9d30e17fb64d6d4fb7ebdf594700ef02c417c2a`，逆变换精确恢复c760、现行静态policy PASS；**未写候选、未执行builder、未编译该组合**。此记录只绑定当时读取的builder和tail，不能替代R稍后冻结文件。

三个数学边界必须分列：

1. helper精确复原原word仅在 E1..23（全符号/全fraction）；E0排除，原±0反例保留。
2. W13b全UInt32 wrapper等于旧convert及 `Float32.ofBits u`；±0仍原表路径，次正规仍ofBits，Inf/NaN仍原高端fallback。
3. 全域 `toBits` 只等于旧convert的bits，不等于任意原始u。原成功witness明确有 `0xffc12345/0x7f800001 → 0x7fc00000`。这些见证驱动使用32768深度，未进入Increment映射，也不能作为gate可用源码。没有据native NaN值等式修改raw NaN fallback或宣称payload保留。

最有价值下一检查：绑定R冻结接线候选，先按8192上限实际编译四spec及公理，再核原实际求和C/汇编中低normal live路径是否仍无once/call/spill、普通上端布局代价是否扩大；由D按授权决定完整配对public suite。精确候选的上述编译/完整gate/性能均待独立证据。未发现应阻止这一步的新增静态错误。
