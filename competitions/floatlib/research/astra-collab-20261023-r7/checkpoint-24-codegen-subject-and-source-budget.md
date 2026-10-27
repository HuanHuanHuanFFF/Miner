# R7 检查点24：现有证据对象核对与组合预算

2026-10-23 01:20 UTC。当前没有网页作业、没有新运行候选变化；W16草稿未派发。继续既有证据工作，截止04:22:17、02:45冻结不变。

## 807诊断对象和W11不能直接等同

`codegen-subject-audit-807-w11.json`逐条核对原candidate-c-index/native-assembly-index、原C和asm字节哈希。807中`candidate-generated-0.c`、`candidate-generated-1.c`及`profile-current-original.c`实际绑定**8eb63a2f**父本，且asm原回执明确说是diagnostic statement replay、不是被清理的计时对象。名字中的current不代表60f。它们与W11的60f/现行MainFull C不同是不同对象所致，不能解释成同源编译不稳定，也不能据此指控运行错误。W11继续仅作固定公开60f的独立C/对象证据。精确计时对象身份缺口仍在，等待D已有observer按授权CI收回。

既有profile输出checksum继续是有限语义锚点；后续根据97f/3d9源转录的调用计数不能改称新候选已实际instrumented运行。D22已重新计算前沿，本核查不撤销既有完整gate的源哈希和计时回执。

## 组合需实际接线，不能简单叠加模块

353d只更换`NativeDecodeSum.decode`，当前c760导出的sum确实经过它。3d9导出sum则直接走`R7SinglePassSum.run/loop/natLoop`，分支中显式使用`R2W01b.tableProduct/Float32.ofBits`。因此在3d9之后仅拼上353d旧decode修改，低normal路径不会进入新导出sum。未来组合需要明确修改3d9的低条件失败分支及对应Nat/USize证明，并独立完整gate；不自动相加收益。D负责最终组合，R未改任何现有候选。

## 源码上限预算是规划，不是已构造结果

`source-budget-inventory.json`绑定7份相关源的精确SHA/字节。示例按D4792矩阵包 +3d9相对0e8的57438bytes增量，减去D包内精确61d最小闭包12744bytes（3d9已提供这些接口），再加353d相对c760的21524bytes：约261901bytes，超256000约5901bytes。**这是加法规划推算，未组装或验证组合源码**，还未计入n1/scalar组件与其他可共享证明。

对W13/W13b新增50个声明做保守词法依赖筛查，以全UInt32 `wrapper_eq_ofBits`为根，暂保留25个；其余候选跨度合计约8455bytes。跨度含相邻注释/指令，不是可直接删除的精确收益，也不是Lean证明项依赖闭包；未删源、未生成精简候选。若实际赢家需要组合，可先在已有证明中裁掉未用接口，再复编译，而不是削弱规格或越过文件上限。原完整数学文件及所有失败永久保留本轮原件中。

R353d/3d9精确Kernel、ready状态与旧gate缺项均不变；当前24组网页原件48主文件在E盘。下一节点01:45 UTC，以D验证进展、原始证据缺口和收尾准备为先。
