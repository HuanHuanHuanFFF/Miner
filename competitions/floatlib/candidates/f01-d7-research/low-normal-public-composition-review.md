# W13c公共组合与353d差异证据审查

开始2026-10-23 01:25:28 UTC，最多35分钟。只读checkpoint23、W13c原件、353d及W14c对应源；未运行Lean、CI、Git、上传、writing builder或代码生成。本轮只写本报告及同名JSON；此前353d审查MD/JSON保持原字节。

**W13c普通编译/完整spec类型/80声明公理成功证据链真实一致。四次失败没有发现仍留在353d中的相同失败证明正文或选项位置。353d使用另一个已在W14c宿主编译过的常量证明，而不是W13c失败的化简策略。公共组合成功仍不等于353d的Lean/完整gate通过；新运行、C与计时均NOT_RUN。**

## source → snapshot → exit → raw axiom

原件根为 `competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W13c/original-extracted/R7-W13c/`。以下SHA由本机对所读原字节重算，完整本地路径和日志记录见JSON：

| 文件 | bytes | SHA-256 |
|---|---:|---|
| `Kernel.lean` | 177974 | `e8fb1bb6671db553162a4e5fcd44d5bc47c7923df68b32cd7cbb9bd8bf65bf54` |
| `KernelDiagnostics.lean` | 187131 | `4db627a9824f7737aa6c44a0d3ae7cf7ba60c15a31f31314f3690b91ab527453` |
| `R7LowTableDecode.lean` | 3019 | `42abb4cbeea43d9f4109e526de8d7c3651f5ecb2952760004160c1e38d3776ce` |
| `R7W13cIncrement.lean` | 22869 | `11be1f6a80c3b4aea8f2d9ac23eec67652bc53c803bbe2e3dfa22ad7c5461023` |

`Kernel.lean`逐字等于`logs/Kernel-attempt1.lean`，其哈希与命令JSON的source_sha256一致；实际returncode0，开始00:39:34.535782，耗时8.163秒。诊断源同样逐字等于成功snapshot，命令returncode0，开始00:39:42.699738，耗时9.199秒。两个原log均没有error或`declaration uses sorry`警告。`TableDecodeTest-attempt5`亦有独立exit0；最终Kernel恰为该成功snapshot再加一个LF，并已重新编译。

实际命令是固定Lean4.34.0的普通`lean -o ... source`，**未显式带`-DautoImplicit=false/-DrelaxedAutoImplicit=false`**。因此不能把它称为官方statement命令。所存工具/依赖身份记录绑定Lean、libleanshared和固定公开archive；报告注明FloatLib0d918，未在本机下载或重哈希远程二进制。这里确认的是已保存证据链。

完整宿主精确为：原60f全部155103字节 + LF + 22869字节Increment + LF。Increment内W13原14224字节、W13b原5624字节和3019字节新块各恰一次；根目录与proofs下的新块相同。原四entry/spec全部在未变60f前缀中，**没有接线到新decoder**。诊断源完整保留最终Kernel前缀，再添加类型断言和公理打印。

本审查独立解析raw输出：80个唯一声明，与`required-axiom-declarations.json`集合完全相同，无缺项/重复；79条depends行和1条无公理行。只出现`propext`、`Classical.choice.{u}`、`Quot.sound.{u}`，去掉显式universe参数后正好是允许三公理，没有sorryAx或其他公理。覆盖4原spec、36条W13、14条W13b、14条新表helper、4条原spec类型断言与8条全域decoder断言。

四spec断言保留任意Binary32、任意sum长度、全部batch/m/n/p与完整BMM输出get函数等式。8条decoder断言分别核任意u及函数整体的常量、与旧low helper相等、与W13b wrapper相等、最终等于Float32.ofBits；没有finite/非NaN域前提藏入终端类型。它们不是官方VerifyFull/gate执行。

## 四次失败与本地正文逐项比较

| 失败稿 | 原exit/错误 | 与353d的关系 |
|---|---|---|
| attempt1 `a4d6cf68…` | exit1；constantFromTable默认递归深度不足，随后unknown/implicit-variable错误与一条恢复性sorry警告 | 运行表读取式同型，但353d在其前有全局8192；此处不是同一资源上下文。最终成功源/log无这些警告。 |
| attempt2 `90b4a7cb…` | exit1；doc-comment之后插入`set_option … in`产生两处语法错；另有`rw [index_eq]`改变依赖索引证明时motive不合类型 | 353d没有该local-option摆放，也不用这段`rw`证明策略。 |
| attempt3 `45ce3727…` | exit1；动态Fin范围证明的`.toNat`与`.toBitVec.toFin.1`匹配失败 | 353d不构造这个动态Fin证明项，使用固定118表项及另一条trans/rfl证明。 |
| attempt4 `24403376…` | exit1；`simpa only [constantFromTable,index_eq]`后，Nat索引118与`UInt32.toNat 118`不匹配 | 成功attempt5显式加入`hNat : (118:UInt32).toNat=118`。353d未使用失败simpa正文，而非简单漏搬这个hNat。 |

每次失败snapshot的真实SHA与各自命令JSON相同，raw错误保留于JSON，不将先前失败改写成成功。四次失败的constantFromTable_eq正文与353d均不同。

**不能仅因353d没有hNat就判它复现attempt4。** 353d第3818行的实际证明是`unfold`、`simp only [index_eq]`、经`Float32.ofBits (scaleBits (UInt32.ofNat 118))`传递、固定`scaleTable_entry`和`rfl`。这段定理正文与W14c已编译常量源逐字相同；整个常量namespace块仅namespace改名，且同样处于8192限制内。W14c的实际编译还显式关闭autoImplicit。它给出了此另一策略的直接成功证据，不能用W13c另一策略的失败覆盖。

## 与353d实际数学/运行正文的对应

353d仍为174914字节/`353d9816425d92fbc6d0cc14c9d30e17fb64d6d4fb7ebdf594700ef02c417c2a`，本轮未改源。

| 定义 | W13c与353d的比较 |
|---|---|
| constantFromTable | 运行式相同，唯范围证明名`index_lt/index_bound`不同；proof参数不改变选出的UInt32/表项。 |
| lowNormalDecode | 从声明至运行体逐字相同，SHA `e6be66a7f72d88075cceb4b2987e782fd882cd0cfb1bb5ba186a5bc1790b1fea`。 |
| convert | 分支/运算相同；公开稿显式写三处UInt32 numeral casts，353d由magnitude的UInt32类型推断；仅这些casts与空白规范化后文本相同。这个文本检查不是新Lean证明。 |

W13c成功正文用`unfold …; rw`得到helper/wrapper等式，并另给funext版本；353d的三个本地桥采用`simpa only`和传递，名字分别是`lowNormalDecode_eq_proved`、`convert_eq_wrapper`、`convert_eq`。这些**tactic正文没有被W13c原编译执行**。全UInt32数学接口现在有公共组合证据，精确353d的这些证明、`NativeDecodeSum.decode_eq`和完整宿主仍待自身编译。

公开`lowNormalDecode_eq_original`的“全u”是等于旧W13 helper；它不把旧helper扩为全域正确解码器。真正全u的`convert_eq_ofBits`经W13b守卫闭合条件域：E1..23进入helper，E0/±0/Inf/NaN保留旧路线。原NaN的Float32值/toBits canonical边界不变，不声称任意raw payload roundtrip。

## namespace、options与准入边界

W13c新namespace在完整60f之后第4107行打开；8192的两个local options在第4119、4129行，均正确置于doc-comment之前，只作用于常量定义和定理。353d则在第3802行设置全局8192，再打开新namespace；未见失败稿的语法摆放或超限值。两边W13/W13b正文为原精确增量，依赖的前49186字节证明与旧公共/本地父本相同。

W13c包内`static-review.json`明确承认只做自列规则检查、未运行官方checker。本轮另外对**确切e8fb Kernel路径**执行固定4b7原policy/options，PASS_STATIC_ONLY；官方原源SHA `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194`。诊断驱动含打印命令与pp选项，不作为候选。静态policy也不补上普通编译缺少的官方调用边界。

没有发现应当因这四次公共失败而改写353d的确定bug；也没有依据把W13c当作353d的成功回执。最有判别力的下一步仍是精确353d的原statement/四spec/公理检查；C、完整计时与确认属于后续独立证据。本轮不重做W15 primitive codegen审查，不从短callee或低normal曝光推算收益。

此前353d审查保持：MD `a55eae64a3ab84a6e0ecbc48844421a6ef52276ae066de513aca1de092987005`；JSON `5b6f47765f0512ec53d6470a6dec00017d943bc60328a99a6979a483b220ec54`。
