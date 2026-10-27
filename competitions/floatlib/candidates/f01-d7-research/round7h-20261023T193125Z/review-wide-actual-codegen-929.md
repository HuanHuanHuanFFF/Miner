# 929 实际wide调用者审查

**实际40lane路径与无热spill内核已核实；调用者仍有可见、未量化的结构开销。** 每四行块只计算一次F40 tiles，实际输出C已内联lane40，没有每输出lean_apply、闭包或F10构造。这里确认真实编译入口的条件调用链，未收动态逐case/block调用计数或PC追踪。重复边界检查及base重算确实在每个列组发生，但不能据此把相对6c2d慢6.19%归因于wide。完整原件hash、函数区间、实际指令及重算成本在[JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-wide-actual-codegen-929.json)。

run40044330511的73/73原件长度/hash一致；精确源码与保存的compiled-Submission.lean均为253315 B / `28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b`。三个原verdict均full/score/passed=true、seed929；官方4b7/public-v2、25round、500000pairs。此次是实际wide接线通过完整公共gate，区别于921/927未接入探针；不等于正式准入、clean独立确认或未来改稿通过。

原对象634672 B / `3ba1c392b59d3b6301046a400c76c0cb9875bd71c2397bd0b2677b0b45ace341`，临时副本SHA相同、已删除。C/trace/nm/asm来自同一个原gate statement对象旁路捕获，未另外重编译。捕获器为eab84afe…e53ce1。Lean4.34.0 commit293d5d0c…，clang `-O3 -ffp-contract=off`，其余实际参数/完整命令见JSON。原件在[capture-5954…](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40044330511/download-097aa2e598ee42309b19b69ae92e1ed0/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-r11-wide4-inline-proof3/capture-5954e29df0d84ab5b25ada80c60043c0)。observer扰动UNKNOWN，最终链接binary未保留。

## 实际调用和生命周期

原C `Submission.bmm` 在39115/39173的underflow scan miss调用 `bmmBeforeUnderflowZero`。该函数38838起检查 `4≤m,4<n,2<p,n<USize.size,A.size<USize.size`，满足时实际进入 `R11WideActual.core`；非满足形状走旧路径，不能声称所有BMM均执行wide。

`core` C38773–38799只做一次全局nativeA map及一次全局packedB准备，再进入实际 `core_spec__3` batch fold。后者调用 `core_spec__2` 四行块循环。每块在38680创建一个列组closure，38693一次Array.ofFn构造所有F40 tiles；38696才调用 `core_spec__1` 循环四行，每行通过 `core_spec__0` 循环p列。38697在四行全部输出之后 `lean_dec_ref(tiles)`，随后进入下一块。因此没有把buildTiles放入每个输出的求值函数中重跑。

F40是内核结束时的160 B标量payload；每g一次构造，tiles数组每四行块一次。C释放tiles引用发生在四行后，实际active输出/销毁机器码未被选中；最后引用的运行时递归释放遵循原数组/constructor机制，不宣称已观察全部allocator free指令。原raw A/B及全局nativeA/packedB仍跨块存活，未采用Panel4表示。

实际输出路径是C `core_spec__0`，38012–38595。row/lane选择已内联成Nat相等测试和F40标量字段读取，再调用 `Packed10.finish` 和array push；函数内lean_apply、closure allocation、constructor、Float32 box均为0。仍有j/10 groupFor、j%10 laneFor、row/lane分支与finish/toBits或原字NaN回放，其成本未知。

**不要把standalone generic helper当真实输出。** 捕获到的 `asm-0-15` 是泛型 `R11WideLayout.emitRow___redArg___lam__0`，其中确有lean_apply_3；实际core C已专门化并消掉该间接调用。20符号预算没有选中 `R11WideActual_core_spec__0..3`，因此active输出最终机器布局、分支优化与销毁汇编仍UNKNOWN。

## 每列组重复的已证开销

实际列callback `core_spec__2___lam__0` C37978–37993每次g都重算 `(b*m+4*h)*n`（37982–37987），读取该B包，然后37991调用通用 `R11WideRows4.run`。这些base运算不依赖g。standalone buildTiles callback的asm-0-13也保留对run的真实relocation，但这里以实际core callback的C绑定为准。

run C36851–36895再次检查 `n<USize.size`、`base+3*n+(n-1)<nativeA.size`、`nativeA.size<USize.size`，然后36891进入within。当前active route为n>4，末地址等于base+4*n-1；不能把该简写推广到n=0。若检查失败，run仍保留四条旧dot及joinRows后备，巨大Nat语义不能被随意删掉。

外层wide guard已检查n和raw A size的机器上限，但当前core API未把typed span/上限证明传入within，因此这些检查没有被证明擦除。重复次数是每块G=ceil(p/10)，不是每MAC。其ns和整包影响UNKNOWN，也没有证据说明它主导了本轮负差。

## 热内核与成本边界

真实 `R11WideRows4_wordLoop___redArg` 为951 B，asm-0-8的0x200–0x2df仍是十组mulps/addps，四个独立行lane，回边内call=0、rsp访问=0、分配=0。四个A对象指针、四个Float32字段和两次unpack/一次merge仍在。MAC段十acc+A+B共十二向量寄存器，A gather暂用第十三个XMM。入口40参数ABI栈加载及退出后十acc保存/F40分配不算热spill。

从原cell_work/classes重新计算same-run reference-normalized比值：

| wide28b相对 | whole | BMM |
| --- | ---: | ---: |
| 41控制 | 0.906115022 | 0.743421787 |
| 6c2d强组合 | 1.015091848 | 1.061851076 |

929缺同run“underflow+direct、无Cross、无Wide”的底座，6c2d包含另一条Cross组合路径，不能把1.061851的差额单独分配给wide或上述重复检查。Root提供的930 clean6c2d/41 whole0.916224、BMM0.718057、p05+0.064674仅作上下文；本审查未重新读取930原件，不把跨run差额当因果收益。

最小后续判别若由Root选择：在保持完整fallback的前提下，把g无关base和机器/span检查提升为每块一次，快路传既有typed span进入within；未支持的巨大Nat仍保留原run/旧路径。先核精确新证明/fullgate及真实调用者C，再以同run无Cross底座作关闭observer的完整成本对照。当前没有修改任何源码/helper，也未Git/CI或启动agent。
