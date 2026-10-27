# 首10分钟决定：停止精确D3大public证明投入

150原件/16333291B全hash/size/集合已核，精确d3c550da、manifest ada78534、Main7208074c。独立解析8份原log（各156行、152timed、42ADD），与派生rows及4block汇总逐项相等，同seed checksum全相等，全部慢样本保留。

四block ADD1.505067/1.489358/1.497546/1.483944；whole1.175671/1.176789/1.197037/1.204368。合计ADD多101481270ns，占whole多103319068ns的98.2212%；MUL/SUM/BMM同回调的原波动也保留。168个ADD case-block pair有167慢、1快（1927003 block1 paired6，-78977ns）；42个同名case跨四block合计均慢，最大pooled dense2多4279177ns，top10只占ADD额外33.65%，不是一两个慢样本造成。

实际Main选control闭包11/guarded闭包10，两者arity2/fixed0，boxed wrapper逐指令相同（仅typed call目标不同），共同join的MUL/SUM/BMM闭包1/2/3相同。guarded实际typed wrapper含D3整数GRS逻辑，没有diagnosticEntry或guardedAdd额外helper call。不是旧MUL的arity3 Bool问题。

D3目标的正常非零成功臂确无临时[rsp] spill，无输入ofBits/table/heap；但是带6callee saves+8B局部/对齐，成功臂variable alignment/sticky/排序/符号计算后仍有一个非尾toBits call。control普通R2 numeric臂是2cast/2table mul+add，3callee saves+16B局部，最后tail jump toBits；同普通臂无临时spill。guarded65/79条静态路径与control54条仅作机制定位，不换算周期。失败准入保留原完整ADD，post normal pre-guard拒绝者已付GRS工作再fallback，比例UNKNOWN。

所有case标签均来自实际plan/log；eligible比例没有计数，不能按dense等标签或旧256点代理归因。当前证据支持停放精确D3及昂贵public证明，不证明所有整数ADD机制慢。没有具备实际代码/完整成本依据的新机制能支持约10%whole；不扩框架或阈值网格。
