# A19 精确源码的低成本证明接口预审

Rust固定`10b2e02e230df8a2225e94db15a50eadf2d5d2abaabfa193936e885dd97a8e64`。原658 Lean505143B，剩19145B。当前目录只复制父Lean，没有运行或继承新完整gate；等待本批精确提取与净成本结果。

实际接入点是`U118_MAIN.common_loop0_spec`（原Lean约3397行），不是整个matcher/main/lazy循环。其参数、loop状态(k,run)、返回值、终止度量和规格均不改变。前提已经分别给出`a+cap<=s.length`和`b+cap<=s.length`，所以证明这个helper无需重新推导链来源关系。`common_loop1_spec`字节尾和所有下游`walk/find/run`规格可保持。

父版用共享宏`C12546!`展开字循环证明；宏内部`Matches.word_zero`／`Matches.word_lz`目前靠`by assumption`取得`pa.val=a+k`。新提取的wrapping_add可能只给`pa=wrapping_add a k`，不能假定原宏直接通过。父Lean的PC namespace已有真实`wadd_val`／`wadd_le`以及wrapping word-loop模式（约4777、4832、4852行），可在U118_MAIN局部复用同样论证，不能全局修改共享宏影响FX0等旧证明。

若计时值得完整验收，最小适配是：

1. 在U118_MAIN.common_loop0_spec前加局部wrapping值/范围引理，沿现有`core.num.Usize.wrapping_add_val_eq`、`Nat.mod_eq_of_lt`和`Slice.length_ineq`证明无回绕。
2. 为原`Matches.word_zero`和`Matches.word_lz`加两个局部包装，在已有`a+k+8<=len`、`b+k+8<=len`前提下把wrapping返回位置改写成自然数和。
3. 只展开并适配这一份common_loop0_spec的宏，增加be8范围goal的`wadd_le`分支，并把两个Matches构造换为局部包装。其余shared宏、字节尾、kernel和顶层obligation保持原样。

预计增加量是少量引理和一份短loop证明，19KB不是静态阻断；没有以此预审宣称一定能编译或证明时间足够。必须先读该Rust的真实`slot.u118_common_loop0.body`确认wrap调用的bind形状，再用原提取、原obligation、公理白名单、原roundtrip做精确pair gate。若净收益薄/回退，则不执行这些完整证明步骤。
