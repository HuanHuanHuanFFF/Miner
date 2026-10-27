# repair3：修长度别名的可约性；只改一个关键字

| 用途 | 本目录文件 | SHA-256 | 字节 / 余量 |
|---|---|---|---|
| core4 | `Kernel-core-repair3.lean` | `c7e7ad380238b3a7e848b460c28fd6bbe6d4aa5c354b57483ef1243b91eb844a` | 249694 / 6306 |
| retained broad2 | `Kernel-column4-broad-retained-repair3.lean` | `bb058c75f59ca36b4952cffae0c943fd296de02cb3e83d164409736b0252c061` | 255724 / 276 |

**唯一改动** `Submission.R19DualTemporal.blocks` 的 `@[inline] def` → `@[inline] abbrev`。其RHS仍为 `(n+3)/4`，原inline属性、全部repair2证明体和其它字节逐字不变；各增加3B，不加option/axiom/编译标志。两份输入原件未改，正逆差分与完整SHA见 `receipt.json`。没有声称生成机器代码已相同。

**为何改接口** CI20/40443955689原core3和broad1日志均显示 `implicit` transparency下的同一别名问题：pack_low/high的ofFn.get期待 `Fin ((n+3)/4)`，t仍是 `Fin (blocks n)`；broad finish_select的B8 Vector参数也在同两种长度间不匹配。repair2的局部dsimp并未真正改变这些参数在implicit级的可匹配性。将纯定义长度别名标为可约，作用于三处接口；保留原proof脚本作为固定判别，避免继续换rw/simp规则掩盖问题。

**验收状态** 仅单关键词差分、源字节、逆还原及原日志身份已经检查。新编译、两模块重放、公理、实际C和计时均 **NOT_RUN**。核心仍8新根；广域15新根+原4spec；审计文件原样复制。D安排固定的一次typed/C反馈后再决定，不由“其余声明未报错”升级失败源码为通过。

**范围不变** 保留B2回退、UnderflowZero、路线guard及全部运行表达式。新DC奇p=3/7的phantom MAC相对旧DC确实新增，A4/B16准备/驻留/析构继续完整计入；此可约性修复没有消除任何成本。D17与确认输入/结果未读，无Git/CI/本机Lean。追加10分钟窗自03:34:35至03:44:35，首次交付03:35:54，未自行续期。
