# n=1 native product + raw -0 normalize

已生成 [f01-d7-singleton-native-normalize/Kernel.lean](../f01-d7-singleton-native-normalize/Kernel.lean)：**188335 字节，SHA `47d429fe3a351a5e002f98c1f4cb95dfdc04368c268275508be758d176f3a347`**。仅 singleton 的乘积入口改为先做原生乘法；非 NaN 结果直接导入，NaN 结果保留原始 `Submission.mul` 回退。随后使用完全未改的 raw `-0` normalizer。新 Lean、原版完整 gate、实际 C/asm 和性能均 **NOT_RUN**，收益 UNKNOWN。

父本为冻结 53d：`53d1c2c40642060c970189250ea1aee88c37ba3eb1309b2bcfed1f0fcf9a3fa7` / 187374 字节；接手时本地 ref 为用户指定 `b088889e55f6ba1990f1101145d45dd0bb0bfa03`。97f 和 c44c seed block 未改。不与 D 的 BMM cold-scan 或 R 的 sum/canonical 工作混合，也未执行 Git 修改、CI、推送或上传。

## 运行时与证明

新 [helper 片段](singleton-native-product-block.lean) 为 900 字节，SHA `acbdd0a61024056d4764abb7ce3fed5c217639de7f4b44691e7c6195c73e3442`。全局 `D7SingletonNative` 插入在 frozen seed block 之后、singleton 的 `namespace Submission` 之前，两个声明均标 NOT_RUN：

```lean
@[inline] def nativeProduct (x y : Binary32) : Binary32 :=
  let r := ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y
  if hr : r.isNaN = false then ExecFloat.Binary.ofFloat32 r
  else Submission.mul x y
```

每个输出只调用 helper 一次，helper 的源式只有一个原生乘法，normalizer 消费其结果一次。NaN 冷路仍会先付这次原生试算，再执行原精确 scalar 回退；不能把它表述成所有路径只有一次算术成本。实际机器码是否保留该形状尚未检查。

`nativeProduct_eq` 只使用父本中真实存在的接口：

| 接口／父本行 | 作用 |
|---|---|
| `Submission.NotNaNProbe.mul_inputs` L2847 | 非 NaN native 乘积推出两个 native 输入均非 NaN。 |
| `Submission.R7Native.ofFloat32Mul` L3064 | 非 NaN 输入（允许 Inf）的真实 native／ExecFloat mul 方形等式；没有误用 finite-only 的 NativeBridge 版本。 |
| `Submission.NotNaNProbe.roundtrip` L2817 | 上述两项条件分别恢复原始 carrier，包含 ±0、Inf。 |
| `Submission.mul_eq` L2720 | 将最终 ExecFloat.mul 等式转为实际 Submission.mul。 |

false 分支是原 scalar 调用，等式直接自反；因此 raw qNaN/sNaN 的 sign、payload 和优先级继续由原精确乘法处理。新 singleton 证明只在原 normalize 桥之前增加 `rw [D7SingletonNative.nativeProduct_eq]`，之后沿用 `normalize_submission_mul_eq_add` 和原 Fin.foldl/Fin.val_zero 化简。未引用 R 的新 canonical 定理。

## 精确变化边界

独立逐行差异只有三处：

1. 53d L4403 前插入新 helper 全局块（child L4403–4432）。
2. 原 singletonCore L4413／child L4443，仅把 `Submission.mul` 改为 `D7SingletonNative.nativeProduct`；A/B 的 getD 地址、默认 +0、decode 和输出构造完全相同。
3. child L4455 插入上述一条 proof rewrite；其余 singleton／最终 bmm 证明及 dispatcher 原样保留。

父本前 **185782 字节**逐字节不变。builder 删除新增块并逆转两处单点变化后，恢复完整原 187374 字节；`n!=1` 仍调用原 `bmmBeforeSingleton`。c44c seed block 的 **10793 字节**在父／子中都仅出现一次，原字节 SHA 保持 `c44c4afbbe117e97b857ac3541638f3cbee370ba86f837fc76be16c41d08ed26`。

[builder](build-singleton-native-normalize.py) 绑定父本、97f、seed、原 gate 和模型哈希，重建此唯一候选及 manifest／JSON 回执。没有生成参数或路线近邻变体。

## 本地检查及首次真实验证

原版 `4b7e838` gate 的 **intake/options/policy 原函数**按固定源 SHA `1eb74ef7…4d27194` 提取执行，静态检查通过；完整源码逆变换、seed 不变、原地址／dispatcher、一次 helper 调用／一次乘法源式检查也通过。这些不是 Lean 或原版完整 gate。

16 个定向整数转录用例均匹配显式预期的乘积及 `+0 + product` 结果，详见 [JSON](singleton-native-normalize-design.json)：

- 11 例走 native 非 NaN，包含普通正负数、±0、负下溢为 -0、最小次正规数、normal→subnormal、有限溢出与 Inf。
- 5 例走精确回退：两种 0×Inf invalid、qNaN payload、负 sNaN payload、右 sNaN 优先于左 qNaN。
- 其中 7 个非 NaN 用例原先会触发 scalar 低指数守卫，现在源式直接走 native。转录模型的“native”是 canonical 投影，不是 Lean 或真实硬件执行，不能替代全域证明。

该修正消除了 53d 在 native 非 NaN singleton 上重新进入 scalar low guard 的源级偏离。相对 97f 的完整原生乘加路径，仍有新 n=1 分派、NaN guard、raw -0 比较及 carrier 包装等成本；去掉一个 add 不能直接推断整体收益。

下一步由 D 在授权范围内冻结精确候选：先编译新 helper、singleton 原规格并核原公理日志，再看真实 C/asm 是否只有一次正常乘法、是否绕开 low guard、NaN 回退和 raw -0 处理是否保留、有无额外 closure／间接调用。完整配对成本需分别对照精确 53d 与 97f，不由 helper 或模型计数推算成绩。

