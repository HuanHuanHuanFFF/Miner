# R5-06：单层流式稿首次完整通过，仍需同环境选择与组合确认

605/run39763957746的原始verdict、gate.log及C已由R独立核对。b5ae8d9b原稿（D副本f01-d5-row-stream-full）首次完整通过：四义务、内核重放、3允许公理、12类25轮及score。CPU AMD EPYC9V74，和604的7763不同。

同批ba93父本bmm最小耗时0.761430/0.758244/0.759568 ns/MAC；stream为0.646316/0.645834/0.638204。三类聚合、按各自固定参考归一化的新/旧为0.8477275418，约15.2%降低（未归一化约15.3%）。逐类spread与全部原始身份见row-stream-first-result.json。

不能拿605的15.2%与604的12.3%直接断言stream优于两层row。它们是不同CPU的发现结果；若D在最终组合中选择stream，应由实际组合的完整gate及冻结后的新runner确认支持。整包ratio本轮仅从0.2217154到0.2210557，不能把矩阵分项改善等同全部目标达成。

实际C SHA c4ca322f7ed141e48aaf5d127a09c5543deab0497ac6772ae5e19370770fdde2。核心不调用全局Packed10.tileResults；row循环每次构造本行rowTiles，调用RowOutput.row后立即Array.append并释放本行输出，再推进下一行。flatMap不是零复制，仍有1次append/行。每行坐标r/m、r%m以及groups(p)计算确在外层，逐输出回调复用已经验证的RowOutput.row。没有把本次C当作已检查的计时机器对象。

D现有integrate-r5.py对stream也能复用同一RowOutput.row接lazy，因为stream实际调用该row；因此checkpoint-05关于finiteBits同步接线的注意仍适用。不重复实现组合、不新增布局候选。第三份lazy及新数学桥是否组合，由D在当前窗口选择并核验精确版本。

另已读取605阶段诊断的原始profile-error：诊断C编译成功，但单独链接命令超时退出-15，仍无阶段计时数据。该诊断失败不影响上述未经改动的官方完整gate，也不能据此归因15.2%收益的各阶段占比。
