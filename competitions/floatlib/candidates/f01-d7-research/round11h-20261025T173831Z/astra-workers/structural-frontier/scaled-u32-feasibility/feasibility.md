# R→精确2^-23缩放→UInt32：接口可达，性能未知

**CONTINUE作为下一代窄接口储备；没有opaque阻断，不改当前23ad/176、不排新CI。** 当前R=u64_product.toFloat32的已验decode是positive m·2^e，m∈[2^23,2^24)，e∈{23,24}。因此Z=R·2^-23=m·2^(e−23)，是[2^23,2^25)中的整数：e23时Z=m，e24时Z=2m且必为偶数。两者都精确可表示为Float32，UInt32无夹断。b=[Z≥2^24]、q=Z>>b恢复同一m，E=S−127+b不变。

## 固定可用接口与最小证明链

当前B2源622d中的R2W01cModel.mul_eq_of_finite_value已经把有限、非零、精确乘积的toReal等式提升为**原Model.mul相等**，不是只提供实数近似。R2W01c.native_mul_eq_of_decoded_raw_model_mul_eq再连接实际Float32乘法；两者当前MUL候选仍可用。所需底层语义来自固定FloatLib0d918257及Lean293d5d0c，不用Float64/scaleB，也不增加primitive假设。

选择一个合法常量定义：

```lean
def powNeg23 : Float32 := Float32.ofBits (0x34000000 : UInt32)
```

原字指数104、fraction0，R2W01c.fields32_toDyadic给出decode ⟨false,8388608,-46⟩，即2^-23。通过nativeModel_ofBits_decode取得实际Float32常量的同一decode。目标z取normal字段E=e+127（150或151）、fraction=m−8388608；同一个已验fields32_toDyadic给出⟨false,m,e−23⟩。z非零且有限，因此mul_eq_of_finite_value适用；toReal乘积只需e=23/24两个分支的二次幂等式，不能把任意实数乘积当浮点精确。

最小明确lemma目标如下，`Model`指FloatLib.Floats.Formats.BinaryInterchange.Model，Dyadic均为FloatLib.Numerics.Dyadic：

```lean
theorem scaled_decode (x : Float32) (m e : Nat)
  (hm0 : 8388608 ≤ m) (hm : m < 16777216)
  (he : e = 23 ∨ e = 24)
  (hx : Model.toDyadic? (R2W01c.nativeModel x) =
    some ⟨false,m,(e : Int)⟩) :
  Model.toDyadic? (R2W01c.nativeModel (x * powNeg23)) =
    some ⟨false,m,((e-23 : Nat) : Int)⟩
```

这是待证明声明形状，未写占位证明或假设其成立。其后直接应用40296747927已验的UInt32 conditional lemma：toUInt32_of_nonnegative_integral_decode，m·2^(e−23)<2^25<2^32。若MUL源未带该UInt32 lemma，复制它约1KB的已验修复版即可；不能误用UInt64数值转位型。最终实例用已验native_uint64_decode与rounded_shift_cases提供hx/he，无新一般缩放理论。

## 常量与完整成本

选择显式top-level闭常量，最好在快臂计算P/R之前取出它。固定旧实际C的NativeFinal/Packed10 zero32先经lean_float32_once，在init函数中调用of_bits；固定lean.h的once热路读取缓存，冷路调用once_cold。**这是已观察的相同闭常量模式，不是新powNeg23的实际C证据。** 新实现仍须核：不能每次热调用都执行external of_bits；首次初始化、once状态检查、常量加载均计入完整调用，不能当成免费的硬编码寄存器值。没有借用已有512项表而隐藏其准备/访存成本。

期望交换：保留整数乘积与一次前向转换，增加一次Float32乘2^-23和常量访问，将unsigned64 reverse换成UInt32 reverse。真实876诊断观察的双cvttss2si、subss、AND/OR补偿及上界选择为动机；新UInt32目标按范围不需要2^63补偿，但其实际指令、0/2^32夹断以及常量路径仍待新C/ASM，**不能宣称一定一次转换或更快**。缩放增加FP依赖链，可能抵销收益。

## 首个证伪与预算

已用八个定向整数例检查min/max、46→47进位及两种平局附近；Z整数、Float32可表示、阈值/尾数恢复均匹配，见directed-check.json。这不是Lean证明或计时。P=(2^23)*(2^23+1)给Z=8388609：常量若错用2^-24则变4194304.5并被截断，直接反驳错误缩放；未经缩放把R转UInt32会饱和，另有显式反例。

首个形式化判别只需上述常量decode＋scaled_decode＋现成UInt32 cast实例，禁止先铺通用缩放框架。预计新增约3–5KB源码（常量、两分支精确乘法、cast接线；不是已生成精确长度），可删除替换部分旧U64 reverse桥但净增量UNKNOWN。当前实际23ad为255704B、余296B，不能直接追加；只有本窄接口和实际成本都值得继续时，再做精确替换容量计划。

截至记录：scaled lemma/新C/性能NOT_RUN，当前主候选保持不变，无新队列。当前public候选真实错误一到优先处理；本判别09:55前停止。
