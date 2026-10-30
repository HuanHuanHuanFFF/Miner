# 已交成本原型的证明恢复接口

`29e71174/253816B` 是 **NativeOnly**，没有新 `Submission.correct`。保留norm26与原GEMM，未使用已测负的pairlinear/centered组件。先完整成本，再投入全证明；零项数学恒等式不能保证分支优化省时。

源36的 `MD2` 原函数保持逐字不动。新 `R28MD2InputZero` 只把解码后值为0的row更新省略，原bias、末端舍入和zero-sentinel回退不动。对任意UInt64乘数、shift、起始h/l，该单步变换等于原两路更新；不是只在浮点数据域内成立。

`InputZeroStep.lean` 给非递归、泛型continuation的单步等价草稿，用固定word-zero规则，未编译。用K捕获下一次 `R28MD2InputZero` 调用，即可隔离四个零分支；不对整个递归type做大simp。随后证明新loop=原MD2：按原n-k归纳，单步展开后只用一次IH，controlled word rw，无额外浮点/统计前提。

恢复调用层时，MVj/MVi已增加一个 `r28Z:Bool` 参数。先在MVj元数据快分支把新loop重写为原MD2，`if r28Z then MD2…else MD2…`归一后复用旧ZMVs和旧ZMVj骨架；ZMVi同样只线程Bool。YaVM一次rawzero probe传入该Bool，旧ZMV0只需实例化它，不需要证明probe和真实零密度的关系，因为两loop应全输入等价。原型删除的4个proof是ZMVj/ZMVi/ZMV0/correct，runtime bounds所需lemma未删。

完整恢复证明后的源码体积 **OPEN**：当前NativeOnly余2184B不代表全证明能放回。若真有正成本信号，才用现有合法别名/证明压缩买体积；保持每个原定义/回退与新source hash绑定，原all12/AX、完整计时及新确认均重验。

实际成本风险：两随机零分支可能mispredict或被if-convert；per-call rawscan、per-output dispatch、原prepare、oddrow未优化及析构均计时。旧18cells中第一linear无零、第二linear约半零只说明可达；Mobile另一消费者零项已测负不构成本源反例，也不能按相同恒等式转移成功信心。Root统一是否带入已有最终Norm保留批，不能挤占真正达标源proof/确认。
