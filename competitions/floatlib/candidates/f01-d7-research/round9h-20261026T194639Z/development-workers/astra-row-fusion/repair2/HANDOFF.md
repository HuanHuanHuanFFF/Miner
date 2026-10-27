# repair2：显式统一长度类型，仅两proof，NOT_RUN

| 用途 | 本目录源码 | SHA-256 | 字节/余量 |
|---|---|---|---|
| core3 | `Kernel-core-repair2.lean` | `036372fd3fdca079ef36e6ee2773c9ce27d8aeddc3f29d01257772f29c931e20` | 249691 / 6309 |
| 保留B2的广域版 | `Kernel-column4-broad-retained-repair2.lean` | `386b5fec7a2595b1fa7e47b283abb3bdbd75066a4591ab3a5740e1cf0106741d` | 255721 / 279 |

**实际原因已由CI19原日志定位。** run40442288468 / source118d8efc 的 `pack_low/high` 在重写之前，目标就不满足implicit transparency的类型检查：`t : Fin (blocks n)` 被送给要求 `Fin ((n+3)/4)` 的旧pack.get。旧方案只更换getter重写，未消除这层类型别名差异，因而仍失败。

**本次变化** 两个proof先执行 `dsimp only [R19DualTemporal.blocks, pack, R19Temporal.pack] at *`，显式正规化t的类型及两边ofFn producer，再用同一个 `Packed10.vector_get_ofFn` 与low/high_packet。不改 theorem 语句、运行定义、透明度设置或编译选项。原CI是已复现的红反馈；本机不跑Lean，修复是否闭合必须由D的真实typed批判定。

**差分验收** core基于118d8efc / 249625B；广域基于D的7f1d4ec3f724526b83b17c28a6b392c7d4acb31e830fd141fae5ba5ea7429084 / 255655B，仅在本worker目录写副本。两份各自的 `*-proof-only.patch`、`*-inverse.patch` 与 `receipt.json` 已核正逆还原、原文件未改、除这两proof外全字节相同。原8ad/118d失败源和日志保留。核心审计8根，完整广域审计15新根+原4spec，分别见两个Audit文件。

**状态/边界** 两新源的编译、两模块重放、公理、C与计时均NOT_RUN；不能因其余新声明未报错称全包通过。广域保留B2回退及原UnderflowZero的性质来自未改D母本，不由这个proof patch重新证明。新DC域奇p=3/7相对旧逐列DC会增加phantom MAC；ceil等式只保证相对B2双lane分组不再额外扩宽，不能称对所有旧route无新增MAC。新A4/B16完整生命周期仍计入。

D拟同批验core3与完整广域源；本worker只修实际typed错误，不读D17/后续确认输入结果，不Git/CI/本机Lean。追加窗03:17:16接手，03:31截止；排队/反馈都计时。原日志SHA `a9e26a3026195ff66d980715104d3790c5c1221a3445459eec51d00058c1599e`。
