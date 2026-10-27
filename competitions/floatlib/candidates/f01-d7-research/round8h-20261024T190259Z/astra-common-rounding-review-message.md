# R14研究回复：913d静态接入核对与共享整数舍入边界

时间：2026-10-24T22:34:08.058419+00:00
关联：20261024T221135428Z-r14-development-native-runtime-and-next-probes.md
类型：静态审阅／数学支持

913d已独立通过字节／位置核对：本地7f312bfe Git blob与当前250296B一致，原四片段各恰好一次、原字节原顺序，父本前缀及add_eq之后完整尾部不变，原mul改名仅四个名字位置，公开新mul/spec放在原mul_eq/referenceBmm之前，无环fallback，Submission重开后恢复了所需open。没有推断Lean已通过。完整回执与引用如下。

0382与compact父本＋LF＋99c2e2f6当前桥精确一致。一处未实跑的静态风险：low_int64_model_eq_roundDyadic里rw后可能已因ofScaledInt自然数系数可定义化简自动rfl闭合，后续have/simp会报No goals；可用先have hm:=int64_model...，再在末尾simpa [cast等式, ofScaledInt,非负] using hm避免依赖rw是否自动结束。原0382保持冻结，是否在新版本采用由你决定，不能称已发生编译失败。

通用带符号word平移已有草稿：直接证明mkBits(sign,em,f)+((s-k)<<23)=mkBits(sign,em+s-k,f)，保留signed64转换原字里的符号位，不误套先正mid再OR符号的运行表达式。它只依赖原packing mkBits_nat和精确模2^32恒等式。

共同整数正常舍入草稿新增：覆盖h<23的精确左移以及h≥23的RSE右移、一般归一化尾数界、低h无carry、原NativeBinary32.roundDyadic正常式，以及真正原rounder的normal指数平移等式native_round_shifted。不是Real代数替代，也没有Float64桥。对齐加法a≥1下，carry=1必h≥24，所以postguard E=h+c+a−23≥1足以推出原未舍入h+a−150≥−126，无需额外排除E1；证明必须显式用这条低h无carry连接。零和仍要先单独处理。

这些是NOT_RUN研究片段，不创建新运行候选或额外CI请求，不改你固定四项顺序。若未来确需编译，可用compact＋当前整数桥＋原packing theorem片段＋新通用word／整数形状，按独立组件相加约245116B（尚无组合候选，分隔符/命令闭合须另计），不把它们直接追加到250296B主线导致超限。先收913d真实编译。signed64乘法替代证明只留纸面比较，不做第三运行表示；其中与开发桥重复的两个前置引理不再单独编译。

原固定Lean SInt/Lemmas额外取得公共短转换API并保留Apache2许可证，Git blob0f7ebdd0、259689B。无需重取或本机安装工具链。

证据（未提交快照；新批发布仍待开发侧人类确认）：
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-development-integration-review-913d.json；SHA-256 28bc98493bed234e5c394e05fa2af1a2121c0d45157c0b4fc872915ce0da306c
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-common-rounding-boundary-review.md；SHA-256 d26d75fbee5e3547ffa36d6fe98b6169ffedc70ca5c1616d9ac2fbfa450ed662
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-general-integer-round-shape-draft.lean；SHA-256 5f2dcfe1c21f447630a70374031cc76804d223457d21a87fa61f4cf9a080311c
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-raw-exponent-shift-general.lean；SHA-256 a1aa12152165572a9f7c5fb742c0f98a468d715145939b2d58b1f1638be9569f
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-int64-source-index.json；SHA-256 01148ddd876b111c1827d71803b12afa8e054571ab033c98736e76bbe0a48b53

结论状态：913d/0382身份及源码放置VERIFIED；通用引理仅纸面/Lean草稿，编译、公理与性能均NOT_RUN。
