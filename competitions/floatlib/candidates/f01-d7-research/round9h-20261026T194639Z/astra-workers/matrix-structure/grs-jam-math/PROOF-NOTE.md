# 变量 drop 的 jam-RNE：最小商余分解

结论是纸面闭合与未编译 Lean 草稿。`JamVariable.lean` **3477 B**，SHA **a78a153405a2b4a5fd29ac704d77114a8f650ac6120591700f4d2ad05afe5595**；**Lean / CI / 完整 ADD 规格均 NOT_RUN**。没有创建大 Kernel、没有修改 exact-arithmetic。承接 `../../exact-arithmetic/grs-jam-lemma-paused.md`，已亲读同目录已验 b271 源的固定 drop17 `rne_jam`，不重算原证明。

## 数学分解

对任意自然数 p、正 D、C∈{4,8,16}，写

`p = D*(C*q+v)+r`, `v<C`, `r<D`。

令 `j = v + (if r=0 then 0 else 1-v%2)`。因为 C 为偶数，`(C*q+v)%2=v%2`，所以 `jamDiv p D = C*q+j`。并且 j<C：若 v=C−1，它是奇数，sticky不再增加；其余 v 至多增加1。原余数 `D*v+r<D*C` 由 `D*v+r<D*(v+1)≤D*C` 得到。

先分别用商余 API 把两个 roundQuotientEven 都变成同一个商 q 与余数比较，不让 omega 看原 p 或 D*q。剩下唯一问题是 `2*j` 与 C 的大小关系是否等于 `2*(D*v+r)` 与 D*C 的大小关系。

令 H=C/2，H 为偶数。只有三种位置：

- v<H：若 v=H−1，它为奇数，j=v；再低的位置即使加1也仍低于H。另一方面 r<D，故 D*v+r<D*H。
- v=H：r=0 时两边都是精确中点，使用同一个 q%2；r>0 时 j=H+1，两边均高于中点。
- v>H：j≥v>H，D*v+r>D*H，两边均向上舍入。

这同时保留商的进位与 ties-even；不需要限制 p 大小。令 D=2^d、C=2^k，使用 pow_add 即得所有 d（包括0）及 k∈{2,3,4} 的目标等式。

## 草稿接口与证明成本

代码使用五个小引理：`quotient_block` 消掉商块；`low_states` 只展开4+8+16=28个v值；`quotient_jam_decomposed` 完成变量D商余代入；`quotient_jam` 对任意p恢复分解；`rne_jam` 接回原 FloatLib roundShiftRightEven。

唯一的 omega 出现在 `low_states`：C/v都已经固定，D/r始终线性，q仅以q或q+1和相同奇偶判断出现。商余还原使用 `Nat.div_add_mod` 两次，不用 p 与 D*q 的通用算术自动化；余数上界直接用 `Nat.mul_le_mul_left D (Nat.succ_le_of_lt hv)`。不枚举 d、指数或大p，也不引入额外 Mathlib import。

已核实际 API：

| API | 实际作用与来源 |
|---|---|
| `roundQuotientEven` | 原定义直接显示商、余数、两倍余数、商奇偶，FloatLib pinned 0d918257 的 Quotient.lean:46 |
| `roundShiftRightEven_eq_roundQuotientEven` | 去掉原实现log2快捷分支；同版本 ShiftRight.lean:111 |
| `Nat.mul_add_div (hC:0<C) q r` | `(C*q+r)/C=q+r/C`，Lean4.34 Nat/Lemmas:1563 |
| `Nat.mul_add_mod C q r` | `(C*q+r)%C=r%C`，同文件:1570 |
| `Nat.div_add_mod p D` | `D*(p/D)+p%D=p`，Nat/Div/Basic:241 |
| `Nat.div_eq_of_lt`、`Nat.mod_eq_of_lt`、`Nat.mod_lt` | 使用已给余数界，不创建变量乘积约束 |
| `Nat.pow_add`、`Nat.two_pow_pos` | 把变量D桥回2^d，已见于b271同导入环境 |

FloatLib两文件重新取 pinned commit 原件，并用 Git blob SHA-1 与本地字节比较一致，见 `verified-api.json`。Lean API来源为仓库保留4.34原件与sources.json；b271精确SHA为 b2710197d387bb22c4f0395f24d39543299965867b95cabb6965ce3df48f4bff。`interval_cases`、`norm_num`、`omega` 和所用算术 API 在该已验源/固定依赖中可见。草稿本身仍需要真实 Lean 验证，尤其 low_states 的 tactic 收敛和定向 simp 接线；源阅读不替代编译。

## 最小反证与实际剩余桥

`check_residue_certificate.py` 只检查28个低位系数状态。对于非零余数，令a=2v−C：a是偶数；a≤−2时，`a*D+2r≤−2`；a=0时为正；a≥2时为正。它检查jam后比较的符号逐格相同，**不枚举d/p，也不是Lean证明**。r=0保持精确中点与相同q奇偶。结果保存在 `residue-certificate.json`。

必要边界：p=3,d=1,k=1 时，jam后RNE为0，直接RNE为1；不能把k下界降为1。仅“C偶数”也不够：D=2,C=6,p=17时，jam后为2、直接为1。这里的C均为4的倍数，中点偶性不能丢。

接入真实GRS仍需独立桥，未由此草稿关闭：对偶数X，证明 `jamDiv (X*D+M) D = X+jamDiv M D`；减法需无借位/非负条件，r>0时原正差商为X−q−1、余数D−r，再按q奇偶得到 `X−jamDiv M D`。d≥4下leading L∈25..27才把目标k=L−23限制到2/3/4；d≤3的精确路径与小T、原Model.add指数/符号/normal/overflow桥仍照原任务分别证明。本件不宣称完成公共ADD正确性、生成成本或性能。
