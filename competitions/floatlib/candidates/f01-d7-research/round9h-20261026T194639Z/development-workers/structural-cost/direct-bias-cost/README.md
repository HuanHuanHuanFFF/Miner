# DirectBias：成本前提已实现，支持有界数学继续

**明确建议：继续一次有界数学闭合尝试。** 精确74899988…运行草稿的实际diagnosticEntry成功路径已删除FP往返及相关工作，P只算一次；没有发现helper虽简洁、完整caller仍偷偷走旧转换的事故。此结论只关成本机制，不报速度或新public MUL正确性。

UTC23:46:50开始，首决定23:51落盘，20分钟上限次日00:06:50。全部83原件/3955261B逐项重算大小和SHA，并核实际文件集合无差项。local/CI input/producer三处均为`74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc`、228187B；首226829B逐字等于622d。

原Submission C为`c991847178387cfd2eccaa65e7162b17f9b565c7b8dd1094e6e8242a16e536d4`，对象索引登记`0000a5aa27fb6babc8e0503d9e3fe12cbf4d7c7e9828f2e0647d38399fa7d36c`。对象二进制未保存，不能独立重算该object SHA。所有C/ASM均为statement诊断构建，非timed ELF。

## 真正完整成功路径

检查`diagnosticEntry`本体C43280–48355及native-loop-6对象，不以standalone normalCore代替caller。正常输入且S128..380实际路径为：

`0x0–0x2d → 0x74–0x86 → 0x266–0x272 → 0x45b–0x4bd → 0xb47–0xb53(ret)`。

共**58条指令**，包括5次save/restore、16B共享frame及全部输入guard。内部成功路径无call、FP、table/codec访存或spill。三个unsigned条件跳转分别核u正常、v正常和S128..380；未追加post-result nonNaN/codec guard。r14在成功路径仅push/pop，没有实际值用途；其他保存寄存器仍承担输入或guard值，不能把五个save都当可直接删除。

## literal选择、P复用与carry

| 项目 | 完整caller中的实际指令 |
|---|---|
| P | 0x475单次`imul rcx,rax`，RCX保留P；没有重复乘积 |
| 23/24选择 | **无branch，也无cmov。** 0x479–0x485取h0=P>>47，将h0<<22与0x3fffff合成bias |
| parity | 0x48b形成23+h0，0x48e `bt ecx,edx`取相应bit，0x491 `adc rax,rcx`得到biased P |
| postbias carry | 0x494–0x497对biased值再取>>47。它是不同输入的h1，不是多算P |
| quotient | 0x49b–0x49e形成23+h1并执行`shr rax,cl`；变量shift保留 |
| pack | 原符号/指数/尾数字位操作直接返回UInt32，无FP cast/外部codec |

standalone normalCore为28条含ret，无save/frame，但这是另一个上下文，仅作核对。完整caller的整数依赖链仍是IMUL→h0→BT/ADC→h1→变量SHR，并非消除了所有舍入成本。

## Jam17有限机制对照与冷臂

按b271原MainFull ASM/index重新认证实际62条成功路径及5save/16B。Jam17成功路径中的`cvtsi2ss`、浮点常量load/`ucomiss`、`cvttss2si`在DirectBias成功路径均不存在。**Jam17成功路径原本也没有table/codec/foreigncall；相对Jam17真正删的是FP往返和相关夹位工作。** 58与62属于不同符号、包装、对象，不能作同binary timing或周期比。未来public caller的寄存器分配/frame可再次变化。

完整diagnosticEntry C/ASM和83原件保留，成功路径外还有727条指令和9个call站点，含原native/table/codec/software慢路；静态站点不代表频次或耗时，没有丢弃这些路径。共享prologue/frame仍由全入口承担，没有据standalone leaf预测未来ABI。

原普通声明、Submission/VerifyFull重放和7根依赖审计PASS；其中normalCore等是runtime定义，**没有新增MUL等价证明**。MainFull C仍逐字为B2的`94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb`，没有DirectBias引用。全run failure与该子项PASS分列，不猜其他失败原因，不修1180。

因此有真实工作可删，成本前提不构成停止数学路线的理由；长证明预算及是否达整包目标仍需另有覆盖/完整成本证据。证明闭合后还必须核新public caller及原完整验收，当前probe不授予它们PASS。`audit.json`保存原件清单、全部路径和比较绑定，`audit.py`约0.3秒可复核；无Git/CI/Lean/新agent，旧route/prefix包未改。
