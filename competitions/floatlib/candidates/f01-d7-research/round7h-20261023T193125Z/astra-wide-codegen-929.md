# 929 真实四行入口：完整 gate 与实际调用链

精确源码 **28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b，253315 B**。原完整 gate 在 run40044330511 / seed929 通过 statement、kernel replay、axiom audit、checksum 和25轮计时；verdict SHA **3557dd6f1084947281c67a7496556d1bc30f6ddf8eedb961bf75dbf075c8ff36**。这是实际 wide 入口首次完整公共验证，不是正式准入、当前冠军胜出或独立确认。

同组3源均完整通过。完整成本归一比值：wide/6c2d 为整体 **1.015091848**、BMM **1.061851076**；wide/41 为整体 **0.906115022**、BMM **0.743421787**。BMM按各cell的真实work加权求submission/reference总成本，再比较两份gate；不是cell比值的简单几何平均，也不是candidate/baseline直接成对计时。wide 此组仍落后于已含 Cross 的6c2d；由于缺少同组749b-only底座，不能把差距全归因于40链循环。此轮带 observer，为发现数据。只继续一个保留 p=2 Cross 与 p>2 Wide 的互补组合；不声称新组合已更快。

原件位于 `ci-runs/40044330511/download-097aa2e598ee42309b19b69ae92e1ed0/diagnostics/f01-d7-public-suite/public-suite`，capture为 `codegen/f01-r11-wide4-inline-proof3/capture-5954e29df0d84ab5b25ada80c60043c0`。R重新检查了保存源码逐字相同、snapshot成员与所有已选汇编的字节/哈希。

| 绑定项 | SHA-256 |
| --- | --- |
| 原生成 C | c81cec69de9fd00b7b4c2c43f759e8a39df3dcc48545b202f36f95a758e871ff |
| 原对象收据 | 3ba1c392b59d3b6301046a400c76c0cb9875bd71c2397bd0b2677b0b45ace341 |
| capture record | f4e9856b07e9b5b8675962bd1c65c2af423ca8a8b98717e60117474aa7686d6b |
| 标准化wordLoop汇编片段 | 4ef365e15c1e8d9132267ca933d45136d47528880ff074afdf93d4abd5906d09 |

## 已确认的实际路径

实际 bmm 经 bmmBeforeUnderflowZero → R11WideActual.core → core_spec__3（batch）→ core_spec__2（四行块）→ core_spec__1（四行）→ core_spec__0（有效列）。此为C静态调用/函数指针关系，非采样热度；具体相关函数原文与片段在 `astra-wide-codegen-929.json`。

- **全局准备一次。** C38773起的 actual core 只调用一次原 A map 与 Packed10.packB，再进入batch循环。原始输入与两份准备值跨行块共用。
- **每块缓存一次。** C38655起的 core_spec__2 分配一次7捕获值闭包，以 Array.ofFn 计算 G 个F40，再调用四行输出循环；C38697的 dec_ref 在输出后释放当前 tiles，没有把前块缓存放入下一循环状态。闭包依旧是每块准备成本，不能称整次入口零分配。
- **没有逐输出 lane40 回调或浮点装箱。** 真正 core_spec__0（C38012起）直接选择F40 float字段，再直接调用 Packed10.finish；其C调用表没有 lean_apply、lean_alloc_closure、lean_box_float32 或 F10构造。随后 lean_box_uint32 在本64位目标为立即值表示，再push最终数组。39个Nat相等比较是源C的静态分支位置数，不能当成每输出执行39次，也不能推断其实际机器指令数。
- **不能误用generic emitRow的汇编。** 独立 R11WideLayout.emitRow 仍有通用回调ABI，但实际专用输出链没有调用它。此次捕获选中了generic emitRow，却未选中实际 core_spec__0/1/2。因此逐输出机器分支/栈布局仍未获得对应汇编，C已内联这一结论与汇编缺口分开记录。
- **热循环确实沿用已审机器码。** 实际可达 wordLoop___redArg 为951 B，其标准化汇编与921逐字一致：0x200–0x2df十组4-lane mulps/addps，无call/rsp/heap分配；MAC段12个活跃XMM、gather另用xmm2，实际共13个名字。入口ABI加载与退出168 B结果分配的保存发生在热区外。此次有真实within调用，已不再是未接入探针。

## 已确认而未量化的剩余开销

actual core_spec__2___lam__0（C37978起）每个列组重新计算 `(b*m+4*h)*n`（三次Nat乘、一加），再取packedB[b][g]并调用 R11WideRows4.run。run 每g重复检查n界、最后A跨度与A.size界；within随后转换count与四个基址。C确有这些重复计算，但尚无其占比，不能从3个guard预报倍率。

后续可把已经由外层guard与nativeA_span证明的事实作为Prop参数传给具体producer，并把块基址/批B选择放到列组闭包之外；应验证生成C确实消除检查和重复准备。不能假设多加inline就自动消除Nat/Array事实。该变化会影响泛型buildTiles/output的证明接口，**本轮不改已于00:35冻结的e5b279组合**，也不改28b819。此项留作下轮最小实验。

对象本体按捕获器策略未保留，仅原对象哈希、实际工具调用与原asm输出可复核。20symbol预算状态PARTIAL，不可把有限片段说成全部caller机器码。没有重新编译来替代原完整gate对象，observer扰动与最终链接布局仍UNKNOWN。
