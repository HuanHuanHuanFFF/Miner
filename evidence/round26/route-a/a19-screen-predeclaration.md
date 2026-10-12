# A19：已执行安全索引源码的一次原协议净成本判别

精确Rust：`10b2e02e230df8a2225e94db15a50eadf2d5d2abaabfa193936e885dd97a8e64`，来自A19 native已执行scratch，原字节固化到`r26-a-658-safe-word-offsets`。只改u118_common字循环两处安全地址加法，无其他组合。原658 Lean复制，未声明新gate。

已知与缺口：1548实际helper、28完整parse token/decode同父658。官方shim/release下row2汇编只变panic定位数据标签；row9主word-loop保持同28条opcode，两版均已64bit movq/bswapq。可核实的窄变化是row9 lazy word-loop少一个cmp/jbe，剩余be8溢出guard仍在，伴随寄存器/栈布局变化。实际总时间UNKNOWN，不预计这一个变更直接达到5%/10%。取得658同源码原协议基线也能改变后续投入判断。

最小动作：前置精确Rust提取，随后两块反序的原28文件、1 warmup/11 measured协议。public658主/同源码shadow、精确候选主/同源码shadow全部保留；另有原框架必需控制。全部token/output身份须保持。完整gate不在本批。

决策：回退或只得到薄弱/被控制分歧覆盖的信号则停止新gate投入；正的小组件可保留，但没有目标接近的声明。只有可用的真实净收益才考虑完整gate与新runner冻结确认，且不挤占固定最后90分钟。若没有足以投入的候选，原5%/10%目标保持未完成。

本次只这一批，不因单块控制有利而继续扫源码写法、改be8或组合其他失败组件。建议35分钟外层cap，历史同规模实际通常更短，排队UNKNOWN。原官方encoder/pins/时限不变。
