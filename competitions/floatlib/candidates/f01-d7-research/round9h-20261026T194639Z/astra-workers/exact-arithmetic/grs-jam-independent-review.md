# GRS JamVariable 一次独立关键审查

被审精确源：matrix-structure/grs-jam-math/JamVariable.lean，3477 B，SHA a78a153405a2b4a5fd29ac704d77114a8f650ac6120591700f4d2ad05afe5595。只读，未改源、未另造版本/runtime/CI；没有本机Lean。结论：关键数学/量词/定向接口未发现反例或缺条件；Lean编译、资源与公共ADD接线仍 NOT_RUN。

- **商块剥离正确**。quotient_block 在 hr<C、C>0 下分别化简 (C*q+r)/C=q、(C*q+r)%C=r；决策中的商奇偶确为同一q%2。quotient_jam_decomposed 先把p除D、余D和(C*q+v)%2消去，再使用两次quotient_block；传入后者的余数界是 D*v+r<D*(v+1)<=D*C，未把它当假设。
- **实际Lean API签名一致**。独立从固定Lean commit293d5d0c0c3f3dded4688b3ccd6a33939ac5102b读取 src/Init/Data/Nat/Lemmas.lean:1563–1570（Git blob64350aa666a6f9ac4c7a05fcb571671dbf75a0e3）：Nat.mul_add_div {m} (m_pos:m>0) (x y)；Nat.mul_add_mod (m x y)。所以源中的 Nat.mul_add_div hC q r、部分应用 Nat.mul_add_div hD 和 Nat.mul_add_mod 均匹配。Nat.div_add_mod(p,D)给D*(p/D)+p%D=p，与恢复p的两次rw方向匹配。固定Div/Basic:241再次核对。
- **28态确无线性域外项**。low_states进入omega前已将C固定为4/8/16并interval_cases v，因此D*v与D*C的一个因子是常数；q只出现q、q+1、q%2，未携带原p、p/D或D*q。r<D和D>0保留。符号比较及bound目标的分支数有限；这只是源码结构判断，不能报实际内存/编译耗时。
- **任意D和tie没有漏层**。D只要求>0，允许奇D及D=1；r=0时jam不动且两边tie同用q奇偶。r>0时H=C/2为偶数：v<H无法jam到H（H-1为奇数）；v=H上推到H+1；v>H仍在其上。故局部比较相同，并可由pow_add涵盖任意d含0。不能推广k=1或仅C偶数；已列p3,d1,k1及D2,C6,p17反例均合法。

尚未关闭：真实加/减T到jamDiv的桥、bitwise sticky实现、d>=4 leading25/26/27选择k、d<=3与小T、字段/Model.add及真正public规格。该数学probe四公共操作仍B2，不产生ADD正确性/性能结论。此审查不增加新版本或排队建议，DirectBias实际反馈优先。
