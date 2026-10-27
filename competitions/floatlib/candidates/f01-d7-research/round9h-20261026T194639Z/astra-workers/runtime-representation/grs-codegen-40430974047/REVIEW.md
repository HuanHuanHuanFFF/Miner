# 7737真实入口：一cast成立，后置失败保活成本也成立

2026-10-27 01:44Z。**决定：7737不直接投入昂贵public ADD桥，也没有实测足以宣告其必慢。** 它消掉了B2解码/表读/FP加乘，但新增非尾codec、六保存与两热栈写；旧三组等成本模型所需28.5%–31.5%eligible降耗仍未被证明。根已另准一个由T硬界导出的前置域成本判别，见`../grs-pre-guard-frontier/HANDOFF.md`；这是唯一下一代码判别备选，不排新CI，不改7737。

精确源77377f8b373988545c557aa6f5cd5edfd82ec772bb643a404a15e26e02d627af，run40430974047/f421185689a8af2d3751e873ef85a2514ba52ade。statement、Submission/VerifyFull两重放、7根允许公理PASS；后3根仍是运行定义，不是新ADD等式。GRS MainFull C与同批622d route-profile2逐字相同，均SHA94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb；真实public ADD仍closed1→lam0→B2。没有新GRS公开计时或公开正确性验收。

实际GRS来自Submission对象的`R19GRS32Add.diagnosticEntry`，C SHA538e0608c7e1798a0e8b9ca985f84b39b527293c4c55c817a0763fbc08aba20a，ASM7 SHA071b5d2f3d681a539f079e3a6515349f4908beb924c3e8eefe5d77c81da3e859。比较B2是同次MainFull真正选中ADD，ASM10 SHAc20a4038dd45779f575119f7f39d42e45fd9b616bd824dd25e13215c0097eb1d。索引中的对象SHA保留，原ELF未提供，未冒充重哈希ELF；均为固定Lean4.34/293d、原-O3诊断构建，不是计时ELF。

| 完整代表路径 | callee保存 / 额外frame | 显式栈数据存取 | 数值cast / native codec transfers | 其他关键工作 |
|---|---|---|---|---|
| GRS正常非零接受，d<32 | 6组 / 24B | 2写、无读 | 1 / 1非尾call | 两次相同magnitude cmp、4cmov；2变量shift、mask/sticky；符号分支；postE判定/打包 |
| GRS正常非零接受，d≥32 | 6组 / 24B | 2写、无读 | 1 / 1非尾call | 省lo选择及jam移位，sticky直接1；其余postcall工作保留 |
| GRS T0 | 6组 / 24B | 1写、无读 | 0 / 0 | 短gap排序/jam/符号减法后直接0，仍付前导保存 |
| GRS早期normal miss，B2两表输入 | 6组 / 24B | 0 | 2 / 1尾跳 | 继续原B2两mulss+addss+self-compare |
| GRS postE miss，B2两表输入 | 6组 / 24B | 2写+2读 | 3 / 1call+1尾跳 | 完整GRS计算后重新做原B2解码/运算 |
| GRS postE miss，两低指数输入 | 6组 / 24B | 3写+3读 | 1 / 3call+1尾跳 | GRS codec后又两次ofBits，B2 add后再toBits |
| B2两表输入且结果nonNaN | 3组 / 16B | 0 | 2 / 1尾跳 | 两表查找链、两mulss、addss、ucomiss |
| B2两低指数输入且nonNaN | 3组 / 16B | 1写+1读 | 0 / 2call+1尾跳 | 两ofBits，add后toBits |

这里“codec transfer”包括尾跳，不把尾跳算零工作；计数不是周期。完整C/ASM原文及11个代表路径片段均保存，NaN冷分支仍在完整入口中，不以表中有限代表替代全输入行为。miss的源调用始终原序`fallback x y`，C使用原始x/y，postE miss在ASM从保留寄存器/栈恢复它们；未调用排序后的hi/lo作为fallback参数。

**热路径精确定位。** 正常前门0..2a→5c..7c→119..153。d<32进入155..184：cmp123在155重复一次以重建flags，低尾数选择和两个cl变量移位随后发生；不是源码“一个swap”就一条比较。186..198形成高尾数和符号，same臂19e..1a0，opposite臂35c..35e；零走47b。非零364..38d包括`mov eax,eax; cvtsi2ss xmm0,rax`和373的`lean_float32_to_bits`，再读指数和postE判断。accepted走3b4..3cf打包和47d..48b返回；没有表、FPadd/mul、Nat/heap/apply热工作。

**两热栈写不是猜测。** 18d把原v写`[rsp+0xc]`，364把abs(v)写`[rsp+0x10]`。它们在成功臂不读，却供postE失败后的3fc/400重载；RBP保留hi供符号，R14保留eBig供E/pack，R15原u、R12原u指数、R13原v指数、RBX abs(u)供可能回退。跨call保活有源码和机器路径双重依据。B2接受臂在d4先恢复三个寄存器/栈后尾跳toBits；GRS373必须返回继续做E/pack。

注意原反汇编没有显示relocation：call373显示的下一地址不是实际callee名字；由对应C可定位toBits。B2 d4与GRS476的jmp是外部codec尾转移，**不能沿显示的下一局部地址误跟进NaN或zero块**。

**旧负结果边界。** R16 f7f/401897实际ADD选择lam2，已一U32 cast+一toBits、无表/FPaddmul；其ADD/B2=1.87392268417完整负不重置。旧优化scalarASM未采，因此不能声称新两cmp比旧八C站点快，更不能把旧same-sign GRS里不可达log2算成此次收益。当前全normal覆盖仍有价值：T0能跳过codec，某些低指数输入能省B2输入ofBits；这两点也说明不能只凭保存数把所有eligible路径判慢。

**最小下一判别已改为有因果依据的pre-guard完整入口代码生成：** 以T硬界保证postE，删call后fallback和字段分解，只让delta跨call。若新完整入口仍有对应两热栈写/多个旧输入跨codec，停止该ABI假设；若消掉，再决定是否值得做包含全部guard、miss、fallback和初始化的完整路径配对成本诊断。不能以leaf/指令条数推进大proof。此阶段无计时，无自动CI，无源码改动。

`audit.json` SHA **8f248d8acb44850b33f9f0ed5d2ce12f8162e0b3bc072073d210e92a43c36a12**绑定新源、同批B2、7根、全部C/ASM及旧f7f C；根排序模型没有升格为新实测。
