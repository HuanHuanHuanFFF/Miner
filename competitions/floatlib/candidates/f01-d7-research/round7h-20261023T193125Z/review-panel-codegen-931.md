# 931 Panel4 实际机器码审查

**GO，仅限表示/codegen成立。** fd17修复了927的namespace匹配缺口：真实Panel4回边现在使用一个F4指针加一次movups取四行，十组SIMD乘加，无热call、栈访问或分配。准备成本和闭包仍存在；9a未接入实际BMM，没有Panel算法收益。927报告保持原字节。本报告及[JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-panel-codegen-931.json)不改变候选/helper/Git/CI或全局状态。

从sync-ci-state所维护的started_ci seed931定位到run40045868764，HEAD `018c92d60b2780e3b2c3c5a2d1baba8858d16c25`，floatlib job120727337567，均success。下载目录为[download-da97…](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40045868764/download-da97e7bfcfbf48eb9307e69f0ab13faf)，capture为其公共suite `codegen/f01-d11-panel4-codegen-probe/capture-9e612642fbdc469b8c576f8f05da3612`。

**70/70原始成员**长度/SHA全部重核一致，完整逐成员hash映射在JSON。9a Kernel、保存的compiled source与本地冻结源均为229218 B / `9a40118eae28c92c1abeca7f6a141fb0fbfe963cbf40321681b8013782f9f7ac`。helper为 `fd17f35a4ef1bc1b1df2afe5fcfe39691d88e7e605968acbe3c38df09df9078b`，与freeze-931原件一致；plan、request hash及原CI/summary绑定一致。

| 原件 | B | SHA-256 |
| --- | ---: | --- |
| Submission.c | 1215385 | `2c196b4f00a97930a41c33fd09d88caac9c159640b39ede9d8c7cf1e510a62dc` |
| C object trace | 1303 | `fdc9b3d1775abe90a36a40e4aa27586a4067a3538fd7043f634d8cacbc6aebaf` |
| 原对象（收据；私有副本已删除） | 547160 | `4380cf302c94965f44a622f9bba1c11fdc9a6baefea1ebe0897e7af083458613` |
| asm-0-5 wordLoop | 见JSON | `b11a7eb352c5099ecb038295fee64a4d5f2cb470e2fd11c68044d8d47d1b4f0e` |
| asm-0-9 block | 见JSON | `bb450a22ace7519ee65698482e7dbf872c6f53444e185793265f9940c29d6a4e` |
| asm-0-14 packA callback | 见JSON | `04fcb11ef49ff4400e1aea732ae3dc8336859faaf9d7b833c05067a984243f34` |

C与对象SHA均与927相同，但这次新增了正确目标符号的原对象反汇编；不回写当时UNKNOWN。编译为Lean4.34.0 commit293d5d0c…自带clang，x86_64 Linux，`-O3 -ffp-contract=off -fdata-sections -ffunction-sections -fPIC -fvisibility=hidden -DNDEBUG -DLEAN_EXPORTING`，完整trace在JSON。这是原gate statement对象旁路捕获，没有额外诊断重编译；最终链接binary未保存。

## 真正wordLoop回边

实际 `lp_competition_Submission_Panel4_wordLoop___redArg` 为825 B。`asm-0-5:641–686 / 0x1b0–0x262` 是唯一k回边，共46条指令：

- 0x1b0读一个F4对象指针；0x1bd **`movups xmm0,[r8+8]`** 一次读取四个连续Float32字段。
- 0x1b5读一个F10对象指针，十个标量B读取/广播，十个mulps和十个addps。每k四十个独立lane乘法及四十个加法，没有水平k归约/FMA。
- 回边call=0、rsp访问=0、分配=0、新装箱=0。旧921/929的四个A指针、四个标量A读取及两次unpack/一次merge，确实被一个指针加一个向量加载替代。

**实际不是最多十二个XMM。** 十个acc为xmm8、4、6、7、9、10、11、12、13、14；A为xmm0。LLVM提前读取首四个B临时量xmm1、2、3、5，实际出现xmm0…14共十五个名字，但没有热spill。不能把此前“十acc+A+B≈十二个”的布局预测当作本轮最大活跃寄存器数。

入口0x0–0x199将八个XMM浮点参数及三十二个调用者栈浮点参数组装为十个acc，这是每次调用ABI开销。0x268退出后保存十个acc，调用heartbeat及 `mi_malloc_small(168)`，写入160 B F40 payload。它们不是每k spill/分配，也不是被Panel4消掉的成本。

## prepare确切成本与g外共享

`Panel4_packA___lam__0` 的真实1202 B机器码在asm-0-14。四个ofBits调用位于0x96、0xfc、0x15d、0x1c0；0x1d0设置edi=0x18，0x1d5调用mi_malloc_small，**每个k一次24 B F4请求**，写四个内嵌Float32字段。实际C36104–36220也对应四次ofBits、一份16 B标量payload constructor，没有四个临时Float32 box。

四个转换值会暂存在 `[rsp+0x1c/0x18/0x14/0x8]`，跨foreign转换/分配调用再写入F4。这是prepare阶段的真实栈流量，不能说整个方案没有spill或foreign开销。prepare还保留四次Nat地址/getD边界处理、default-zero once暖检查/读取、可能的大Nat慢路和数组callback；本轮没有分阶段ns。

asm-0-9的真实block入口先分配64 B prepare闭包，0x8e调用Array.ofFn(n)完成整个panel；随后分配48 B列闭包并在0xce捕获panel，最后0x116 tailjump到Array.ofFn(G)。因此prepare在g外一次，两个闭包共112 B请求不能忽略，也不能把它们算成每k或每MAC分配。

asm-0-10的23 B非装箱列callback仅取B包并tailjump runDot，无packA/ofBits/malloc；asm-0-11 runDot准备计数/zero40 ABI后调用wordLoop，可能经过zero-once冷路，但不重复转换A。实际generic闭包指向boxed wrapper，C36258–36267还有g、panel、n、packedB引用递减；未捕获该boxed wrapper汇编，因此不能把完整generic callback开销等同23 B叶函数。

## 生命周期与验收边界

panel仅移入列闭包；F4/F40都为标量字段，不把panel指针存入返回结果。C可核列boxed callback的dec_ref(panel)。但block最后tailjump外部Array.ofFn，**其最终闭包销毁/释放指令未在捕获符号中**，当前探针也没有实际连续BMM块调用者。标准所有权约定支持遍历结束释放的推断；“下一块开始前实际最终释放”仍UNKNOWN，不能由一次callback引用递减替代。

9a完整保留749b父本前223584 B，四个实际入口与spec未改。931的Panel9a与41两个原verdict均full/score/passed=true，绑定4b7/public-v2、seed931、25round、500000pairs。它们验证了完整源中的定义、终止及packA_get等现有证明，并对旧入口计时；**没有接入Panel BMM、四十lane矩阵等价、raw NaN finish、尾行/尾列与巨大Nat后备的完整新算法验收或收益。**

snapshot为00:41:18.449070–00:41:18.452984 UTC，observer扰动UNKNOWN；不是clean确认。未来若Root选择接入，须保留原raw A/B用于NaN回放、避免旧global nativeA与panel重复准备，并重新核实际caller的生命周期、完整gate和关闭observer的完整成本。当前unused helper机器码不能保证未来集成后仍使用相同寄存器调度。未改927报告或任何原始回执。
