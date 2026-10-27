# 7489：实际偏置入口消掉 Jam 转换链，回退帧仍在

2026-10-26 23:57Z。**决定：成本前提没有被这次真实编译否定，值得继续当前已选的公共等式证明；不增加运行变体或自动排 CI。** 这只关闭代码机制未知。新诊断入口没有接到公开 MUL，原完整性能未测，不能宣称整包提速或已证明新乘法。

精确输入 `74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc`，228187B；其前226829B逐字等于保留 B2/622d。run40420540388、开发提交ce3e26f9c6efaf3a7435570d46a13db93cf8c463、官方4b7e83841cc0c32c6529f533923c73d33b5ecf97。真实构建为 Lean4.34.0 / 293d5d0c0c3f3dded4688b3ccd6a33939ac5102b，固定clang单独`-c -O3`，trace无LTO。`audit_codegen.py`复核32份相关证据绑定及5份f529历史绑定；原始对象二进制未提供，对象SHA仅是索引记录，未冒充重哈希对象。

## 已接受的接口范围

原verdict是`diagnostic-statement-only`、passed=true、ratio=null。VerifyFull和bench构建成功，Submission/VerifyFull两模块重放成功；7根为四个旧public规格及`R19DirectBias.normalCore/guardedMul/diagnosticEntry`三个**定义**，仅三允许公理。这里没有新定义等于乘法规范的定理。

实际BENCH_PLAN闭包仍是ADD closed1→lam0、MUL closed5→lam3；两条选中C经局部变量和lambda编号规范化后均与B2逐体相同。故本批不存在公开DirectBias MUL性能。候选内遗留的NOT_COMPILED注释不再代表这三个定义的当前编译状态，但源保持冻结，不为改注释生成版本。

## 成功路径及残余依赖

真正带完整B2回退的`Submission.R19DirectBias.diagnosticEntry`来自Submission实际对象，不是以独立normalCore代替入口。接受路径按原ASM地址为：

`0..2d → 74..86 → 266..272 → 45b..4bd → b47..b53`。

- 三道守卫正好对应两个输入指数1..254及指数和128..380；与b271真实MainFull lam3的接受守卫/前导指令完全相同。这里没有新增输入覆盖。
- `45b..4bd`实际只有一次`imul rcx,rax`。原P保留到偏置；P的bit47给0/1，构造0x3fffff/0x7fffff，`bt ecx,edx`读取P第23/24位，经`adc rax,rcx`加进偏置。源中的偏置if没有变成条件跳转。
- 偏置后重新取bit47，再`shr rax,cl`完成23/24位可变右移；这是串行整数依赖链，仍有可变bit-test和一次可变shift。不能把branchless等同无成本。
- 成功路径无浮点转换、浮点运算、表/常量数据读、call、heap/RC或显式数据spill。它仍执行五组push/pop和16B栈帧调整，所以“无数据读”不包括这些栈保存操作。
- 独立normalCore也是同一偏置机制，0..6b的叶函数没有call/栈帧/条件跳转。但其形状只作交叉核对；结论以上述完整diagnosticEntry为依据。

完整入口仍把旧B2回退内联，并非miss后尾跳到隔离的冷函数。五个callee-saved寄存器为rbp/r15/r14/r12/rbx；r14在成功路径没有语义用途，rbp只在前门提取y的指数后不再使用，r15/r12供指数判别与和，rbx供y的尾数和符号。共享帧与回退有明确联系，但不能把所有保存都归因于冷路径。全函数9个call和6个`[rsp+0xc]`浮点存取都位于回退，成功路径不经过它们。此次没有测试冷包装，也不重开1d15变体。

## 与已有负结果的差异和不能越过的边界

| 对照 | 真实已知 | 对当前决定的约束 |
|---|---|---|
| b271/Jam17，40404258098真实MainFull lam3 | 同一三道guard、五保存和16B帧；核心1imul后还有sticky压缩、cvtsi2ss、movss常量、ucomiss、cvttss2si、cmova上界选择 | 7489确实移除了这组工作，替为整数偏置链。没有移除公共guard或fallback ABI。 |
| b271首完整D40407333869 | 已记录whole/B2=0.9988850281、MUL/B2=1.0171211598、p05=-0.0108148042，停放 | “快臂无call/spill”此前已存在且并未带来合格收益。此次必须依靠被移除的具体残余工作，不以叶函数名义重置负结果。 |
| f529/R15，40166656717 | 全gate/25轮通过但whole/df5c=1.24480320596、MUL/df5c=1.70257769469；保留拒绝。真实选中C有remainder mask、两比较及flag组合 | 同normal/S128..380域的软件整数RNE不是新发现。旧优化标量ASM未捕获，不能断言旧机器多做第二次乘法或与当前bt/adc同价。该旧基准是df5c，不是当前B2。 |

当前可证的差异是**新完整诊断入口实际保留一个乘积，并且没有Jam转换/clamp**；不是“整数比浮点快”的经验断言。静态路径58条指令只用于复核路径，不是周期估计。编译布局、guard、fallback、寄存器保存及数据分布可能吃掉全部收益。

冻结分配模型中MUL占整包38.724%，单靠MUL带来整包10%改善需该操作全部成本约降低25.82%；本次只改变其中被guard接受的部分，其时间占比与可实现降耗仍UNKNOWN。不要由normal域宽度、指令数或模型命中频率换算收益。

## 下一项可证伪验收

1. 公共证明完成后用**相同运行体和guard/fallback**接入真正public MUL，重验四spec、全部辅助根及模块，不把本批7定义根当等式桥。
2. 下一必要编译追BENCH_PLAN到真实MainFull选中callback，检查仍一产品、无floatcast/table/call热臂及相同域，记录新增闭包/调用/save/spill；不能用本次独立诊断入口替代未来caller。此项是代码假设检验，不新加采用门槛。
3. 原完整D按所有初始化、guard miss和fallback成本对保留B2测量；只有原门槛通过才原A+B。旧f529、b271及9c4e负结果原样保留。当前暂无新性能、checksum或采用结论。

产物：`audit.json` SHA bf0522cc34baeec23d8441ad5429058b1b2246a9a7239bc9549a0f9d7b511256；`accepted-diagnostic-path.asm.txt` SHA e92807f660ccba0b4687ddba1f8c9a0b1896a94541049b7800c58844d1e20b2f。原ASM6/7及C0/1哈希在audit逐项绑定。只读原件、只写本方证据；无本机Lean/编译、Git/index、CI或新源码。约9分钟关闭本阶段关键未知，token/cache UNKNOWN。
