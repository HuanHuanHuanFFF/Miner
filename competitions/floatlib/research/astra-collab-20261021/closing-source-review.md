# 冻结包源码与舍入复核

2026-10-21 11:19 UTC。仅源码复核；完整通过状态以window-audit.json及原始gate为准。

核对的精确文件：

| D候选 | SHA-256 |
| --- | --- |
| native-add-proof1 | `7f51b43399c212936038798c763b1fdb0f900fed185c83051b63dbcf08b3d608` |
| native-both-proof1 | `707d22fed8443d883a183983397496492f9a09e071ffcf2715ef818384e44b85` |
| native-sum-acc | `75524a316b846ccfbbba3fabe0f9ac4941c1c126ef6b4fd370573b0e84b09fdd` |

未发现新增源码正确性问题，理由和边界如下。

- 标量native分支只在两个转换值finite且两次raw往返逐位相等时执行。其他情况使用原始x/y进入已有TunedAdd/FastMul，NaN符号／payload、Inf及signed zero不因转换丢失后误用快路径。有限输入产生Inf或次正规输出在证明声明中允许。
- native-both的sum、bmm保留原先fold顺序，bmm每步仍先mul再add，分别返回Binary32；没有FMA或重排调用。乘法的指数前提已显式通过三个格式／乘积引理建立，未把round和roundWithAccuracy直接当作定义相等。
- native-sum的成功不变量按Fin.foldl.loop逐步递推，失败返回none并完整重算referenceSum。最后一次加法即使溢出也可作为成功结果；若还有输入，下一步finite guard失败后回退。所有长度和零长度均在原声明范围，未特判官方尺寸。
- sumTry成功编译C的签名含`float acc`，热循环直接`lean_float32_add`后goto；只有k达到n时box_float32并构造some，失败分支返回none。该机制已由C确认，性能仍需完整计时。
- 三个精确Kernel的静态扫描只有`import ContractTensor`，未见sorry、admit、native_decide、新axiom、unsafe、Unchecked、extern、implemented_by、csimp或初始化代码。此扫描不替代官方policy与完整公理审计。
- native-add已收回完整公理审计，仅Classical.choice、Quot.sound、propext。native-both尚须最终批次的同一审计，不能由“公开定理／代码存在”替代。native-sum也等待其自己的完整回执。

C层可见独立加法、乘法及位转换调用，未取得机器码反汇编；不把C检查写成已独立证明后端从不融合。单文件源码明确两次舍入，官方checksum覆盖运行结果；FMA反例与重排反例保存在counterexamples.json。

MainFull成功C仍将函数闭包交给通用Bench.runFull；当前已回收产物没有候选特有的计时外提证据。冠军源码仍不可得，对其实现机制保持UNKNOWN，native路径的成功不能反推冠军内部代码。

本次移植的FloatLib引理保留公开commit及MIT归属，许可全文在sources/FloatLib-LICENSE.txt。后续若另获正式单文件提交授权，应在最终Kernel中保留相应版权与许可通知，并按新精确文件验收；本窗没有正式提交。
