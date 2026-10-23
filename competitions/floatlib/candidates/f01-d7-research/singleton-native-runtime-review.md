# 47d singleton native-product 运行接线审查

开始2026-10-23 01:05:25 UTC，最多35分钟，只写本报告及同名JSON。**本审查者未参与47d的helper、builder或运行集成；曾编写其继承的c44c seed-normalize证明块。因此新增运行接线为独立审查，自作继承块不称独立复证。** 未改候选/R文件，未运行Lean、CI、Git、上传、工具链或目标二进制。

**未发现确定静态bug。native非NaN产品包含Inf/次正规/负零的接受范围，与实际引用桥匹配；NaN路径调用原始raw输入的精确scalar乘法，原n≠1路线保持。新Lean、完整gate、C/asm与性能仍NOT_RUN，gain UNKNOWN。**

## 身份、差异和逆变换

| 源 | bytes | SHA-256 |
|---|---:|---|
| [47d候选](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-singleton-native-normalize/Kernel.lean) | 188335 | `47d429fe3a351a5e002f98c1f4cb95dfdc04368c268275508be758d176f3a347` |
| [53d父本](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-singleton-normalize/Kernel.lean) | 187374 | `53d1c2c40642060c970189250ea1aee88c37ba3eb1309b2bcfed1f0fcf9a3fa7` |
| [97f基座](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-nonfinite/Kernel.lean) | 174925 | `97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26` |

本审查未执行writing builder。独立逐行对齐只发现三处差异：53d第4403行前插入900字节helper及两个换行（47d第4403–4432行）；第4443行把`Submission.mul`换成`D7SingletonNative.nativeProduct`；第4455行插入一条`rw [D7SingletonNative.nativeProduct_eq]`。逆向逐hunk操作恢复完整53d字节与哈希。builder的两处新接线恰对应后一运行行和证明行，没有隐含其他替换。

父本前185782字节与候选相同。10793字节c44c seed块在父/子中均恰一次、原字节不变；900字节helper恰一次，SHA `acbdd0a61024056d4764abb7ce3fed5c217639de7f4b44691e7c6195c73e3442`。去掉seed/helper/singleton后，反向改回旧bmm/spec名字得到97f完整源，额外仅两个拼接换行。旧add/mul/sum和矩阵基座没有其他源级变更。

最终dispatcher及`bmm_spec`块654字节与53d相同，SHA `3be0ef4ae367caf5986772875bb043d06be85b2ffc69842b2fb197a70d9411b5`；`bmmBeforeSingleton`及spec块691字节同父，SHA `3e7599259caf9a2135b2b98cd27511f46bcb3043f85e72853fd2d15043e0b382`。这证明源保持，不能外推C/机器布局或计时保持。

## n=1地址、空输出和其他n

实际`bmm`第4459–4462行仍只按`n=1`选择singleton，否则调用原`bmmBeforeSingleton`。n=0和所有其他n保留97f的DirectSmall/packed决策及原证明。没有seed、值分布或工作量派发。

第4440–4444行与referenceBmm第2736–2742行采用同一`Vector.ofFn`、同一`bmmDecodeC m p q.val`，读取：

```text
A[(b*m+i)*n+0], B[(b*n+0)*p+j], 默认值均posZero
```

这是reference的唯一k=0项，未重排batch/row/column地址或改用unchecked读取。batch/m/p任意；空输出没有q，因而不增加m/p正值前提。n=1证明仍先`subst n`，逐输出将新helper重写成原`Submission.mul`，再将normalizer重写成`Submission.add posZero`，最后用原`Fin.foldl_succ / foldl_zero / val_zero`闭合一个元素的fold。新增加的只有第一条重写；类型匹配和simp最终闭合仍需实际Lean。

## native-product接受范围与NaN修复

实际helper第4409–4412行只有一个绑定的native乘法表达式：

```lean
let r := ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y
if hr : r.isNaN = false then ExecFloat.Binary.ofFloat32 r
else Submission.mul x y
```

singletonCore只有一次helper调用；normalizer接收这个选定产品。源层不重复计算r，未保留53d在非NaN产品上进入scalar低指数守卫的偏离。NaN分支仍先付native试算，再执行scalar，不能称所有路径只有一次算术；实际编译后的指令数量/包装/分配未观察。

新增等式第4415行使用父本的真实接口：

- 第2847行`Submission.NotNaNProbe.mul_inputs`：非NaN产品推出两native输入非NaN。
- 第3064行`Submission.R7Native.ofFloat32Mul`：前提是两输入**非NaN**，没有finite前提。其第3023行model桥明确分finite与Inf，覆盖双Inf、Inf×finite及zero分类。
- 第2817行`Submission.NotNaNProbe.roundtrip`：同一非NaN前提恢复原完整Binary32，包括Inf、±0、次正规。
- 第2720行`Submission.mul_eq`：最后将ExecFloat乘法恢复为实际scalar操作。

没有误用第2671行较早的`Submission.NativeBridge.ofFloat32Mul`（它才要求finite）。`hi.1/hi.2`与新桥、两个roundtrip逐项匹配；真分支得到`ofFloat32 r = ExecFloat.mul x y`，`simpa only [Submission.mul_eq]`与目标同形；假分支是原scalar调用，自反。此为静态目标核对，**nativeProduct_eq尚未编译**。

| 产品/输入情况 | 实际选择 | 必须保留的语义 |
|---|---|---|
| 普通finite、次正规、下溢±0 | r非NaN，直接native carrier | 保留已单独舍入的乘积；-0随后归一化 |
| finite溢出Inf、Inf×非零、Inf×Inf | r非NaN，直接native carrier | 没有误用isFinite拒绝Inf |
| 0×Inf invalid | r为NaN，原scalar | 原invalid位型由原乘法负责 |
| 任意qNaN/sNaN输入 | native NaN进入原scalar | 用原始x/y，而非native canonical投影；保留quieting、sign/payload、双方NaN优先级 |

## raw -0归一化与初始+0加法

第4176–4178行仍是W10b Core的运行形式：先选UInt32，仅`0x80000000→0`，再`ExecFloat.ofRaw`；没有native转换或NaN canonicalization。原W10b Core427字节/`270c698a2dd2b96d21766d35339e090ca1455f71404145b3323cd1862301b67f`已重新读原件核对；W10b Proofs3636字节/`90a6e0461690f8220d7ecc1710d52a267eb6239ec18d50de9f164952eff6bcbd`仍保留完整条件和产品命题。

一般q的恒等式要求`Model.isSNaN (toModel q)=false`，不是对任意raw字成立。唯一新增定向负见证：在原精确整数转录中，q=`0x7f800011`，raw normalizer仍为`0x7f800011`，但`add(+0,q)=0x7fc00011`。这验证该前提不可删除；不是Lean或真实硬件验证。模型源SHA为`3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72`，读取前后不变。没有重跑原作者16例作为新的独立测试。

候选没有放宽上述前提。第4361行经既有`R7W01.mul32_not_snan`证明实际ExecFloat产品不sNaN，再给出第4367行全输入`add_posZero_mul`、第4388行Submission桥。新`nativeProduct_eq`先恢复完整scalar产品，随后才应用该桥。因此native负零/负下溢改成+0、Inf保留、scalar修复后的quietNaN sign/payload保留，正对应Spec的单独乘法后初始+0加法。

上述继承c44c端口仍是NOT_RUN。已收W10/W10b普通Lean成功/公理原件支持其来源命题；原包中的gate禁用声明与c44c适配的区别见[既有zero-seed审查](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/zero-seed-proof-review.md)，本轮不重做旧全包审查或把公共原件成功升级为47d接受。

## 新检查结果与实际缺项

对精确47d再次执行固定4b7原policy/options：PASS_STATIC_ONLY；唯一import仍为ContractTensor，无set_option。新helper在闭合seed namespace之后、singleton namespace之前，所有依赖先声明；未见export冲突、前向名字或新增不满足的证明前提。188335字节在256000上限内。

47d源级上解决53d非NaN singleton重新进入`ex+ey<128`软件乘法的偏离。相对97f原native dot，仍有n=1分派、isNaN判断、carrier包装、raw -0选择；NaN路径还付native试算加scalar修复。去掉+0 add/loop不能据此推出整体提速。既有807 n=1曝光与模型路径计数都不是时间份额，本轮不重新分配整cell时间。

最先有判别力的是精确47d statement：新`nativeProduct_eq`、继承c44c端口、singleton两次rewrite和四spec一起编译/审计。通过后才有实际C可确认正常路径是否只有一次产品、确实绕过low guard及有没有额外包装/间接调用，再由D安排完整配对计时与确认。当前没有新Lean、完整gate、C/asm或性能成功结论。
