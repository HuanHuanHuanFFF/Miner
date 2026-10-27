# CI16真实ADD成本交接

建议停止精确D3大public ADD证明；没有实际代码/成本证据支持约10%whole的后继，本次不提新机制/阈值网格。

150原件/16333291B、精确d3c550da/ada78534、16冻结组件全核；8原log独立解析，156行/152timed、同seed checksum、四项/whole守恒及原汇总相等。四块ADD1.505067/1.489358/1.497546/1.483944，whole1.175671/1.176789/1.197037/1.204368；pooled ADD1.493992/whole1.188062。ADD多101481270ns，占whole净多103319068ns的98.2212%，只作时间归属；其他三项波动未删。

42同名ADD case跨四块汇总全慢；168pair仅1快（3/block1 paired6 -78977ns）完整保留。最大pooled dense2多4279177ns，top10占ADD净增加33.65%，非单慢样本驱动。全部42×4成本、贡献在ADD-42-cases.md/ADD-168-case-pairs.csv及raw-recomputed.json；所有eligible比例UNKNOWN，未生成500k输入/借旧采样代理归因。

实际Main闭包11(control)/10(guarded)均arity2/fixed0，boxed ASM除call目标逐指令相同，MUL/SUM/BMM共同闭包1/2/3。guarded体内真inline D3，无diagnosticEntry或额外guardedAdd call。正常非零接纳臂无临时[rsp] spill/输入ofBits/table/heap；仍6callee saves+8B与一次非尾toBits，整数排序/shift/sticky；control普通R2臂3callee saves+16B，最后tail codec。正常路径65/79对54条仅静态，不给cycle比例。完整fallback/cold物理分配未知，未丢；动态eligible和慢原因分解UNKNOWN。

完整README/codegen.json/decision.json含边界及停投依据。这里是已见两plan、同runner、同binary Suite pass诊断；不称原D/score/确认或新public等价，当前D3回放七根仍NOT_RUN。未改冻结组件/manifest/Harness，无Git/CI/Lean/新agent。
