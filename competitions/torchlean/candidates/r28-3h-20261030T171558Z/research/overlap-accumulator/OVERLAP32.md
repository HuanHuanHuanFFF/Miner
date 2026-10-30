# 两个相互独立的累加器，最后恢复128位

状态：父原创推导/有限字模型/运行草稿，未Lean编译、未完整Kernel、未计时。不新增本轮CI。它与R27按指数Band或每16项合并不同：沿用原缓存及每项已算出的64位积，不新增数组或准备扫描。

令M=2^64、B=2^32，长度n<2^32。对signed64整数p_i作**向负无穷取整**分解

`p_i = B*q_i + r_i, q_i=floor(p_i/B), 0≤r_i<B`。

维护两个寄存器：`L=(Σp_i) mod M`，`Q=Σq_i`。因q_i∈[-2^31,2^31)，n<2^32，Q的每个前缀都在signed64内；R=Σr_i满足0≤R<M。终端设`A=(Q*B) mod M`，则R恰是`(L−A) mod M`，所以

`S = B*Q+R`，

`high64 = floor(Q/2^32) + (L<A ? 1 : 0)`，`low64=L`。

这是完整整数等式，最后只做一次carry判断。循环中更新L和Q各一次，不让Q依赖L的carry。UInt64原始位转Int64后算术右移32即q_i；不能用逻辑右移。固定Lean4.34 `Init/Data/SInt/Basic.lean` blob472c97c9…提供inline UInt64.toInt64和extern-backed Int64.shiftRight，逻辑模型是BitVec.sshiftRight'，RHS32模64安全。实际新C/ASM还没生成，不能仅凭接口断言移位免费。

unsigned64积也有同样分解，q_i是逻辑右移32、Q用UInt64无符号和（n<2^32保证<2^64）；末尾high用Q逻辑右移32。适合父单边正输入表示里可能≥2^63的合法积，不能误用signed版本。若输入p_i只是更宽数学积的低64位且没有原guard保证它就是目标signed/unsigned值，本方法不会恢复丢掉的产品高位；这条producer义务不能省略。

## 与现有路径的桥

source36的MD/MD2已有原span域给每个shifted product signed64精确，n<2^20。可保持同一getter、布局、乘法、bias和原fallback，只把逐项sign+carry更新换成L/Q更新，终端构造同一个128body后复用YL。最终整数和<2^83，signed128唯一；raw零符号仍由原fallback决定。纸面闭合的是累加表示，不是实际Word缓存/loop/all12。

潜在价值是去掉逐项carry的跨寄存器依赖；现代编译器可能已把旧代码降成高效ADC，增加SAR32也可能不值得。因此必须看同源完整成本/新ASM，不按少分支或少乘法宣称更快。pair内两个dot需要各自L/Q，不得混行；不要用每项tuple返回引入新allocation。`OverlapRuntime.lean`仅展示inline寄存器更新与一次终端pair，未编译。

`overlap_model.py`含正负极值、模64回绕、抵消、逻辑/算术移位混淆及n越界的闭式反例。它说明这个准确表示可复用，不构成本轮新性能或形式化验收。若当前Mobile修复/已有norm确认更有价值，先交它们；本路线留作下轮唯一最小实验。
