# R10：singleton double-cache 的窄范围静态审查

未发现新增正确性缺陷。结论只覆盖新增 `SingletonBPredecode.core/core_eq` 与最终dispatcher的静态审查，**没有运行Lean、完整gate或性能测试**。

精确候选为 `ce6832e600a35382cb7d61ed1f30e539fad54d56545a95dcdb9ce0289f870de1`，253674字节，距256000上限剩2326字节；父为 `f44802093e149959a4b64c519464f9d445de040b6bc2f760512a70596e2640b8`。只读解析builder的block字面量、重建父dispatcher重命名与新增block，结果逐字节等于候选；没有执行builder或写任何候选文件。

`core_eq` 中先unfold新core和父 `SingletonRowCache.core`，再 `simp only [Packed10.nativeA_getD]`，预计可以闭合。该已有引理对任意Binary32数组、任意Nat索引均成立，连越界默认值也精确覆盖：mapped数组的 `Packed10.zero32` 等于原数组 `posZero` 转成Float32。simp的常规zeta规约会暴露nativeB的map以及lambda内的let；重写唯一改变的乘法右操作数后，其余项与父实现定义相同。本审查另做了纯文本逆变换：去掉nativeB let并将该读取还原成 `fa * ExecFloat.Binary.toFloat32 y` 后，整个core正文与父core逐字节一致。**预计闭合仍是INFERRED，不能替代Lean执行。**

payload与地址未变。A仍从 `((b*m+i)*n+0)` 取原字，B原字y仍从 `((b*n+0)*p+j)` 读取；新nativeB也在同一 `baseB+j` 索引读取。只有原生乘法右操作数换成预decode缓存。若result为NaN，仍调用原 `Submission.mul x y`，不会用已丢payload的Float32替代原B。其后seed-normalization也与父相同，保留原先+0起始fold对负零的处理。raw y在源中定义于if前、只被fallback使用；**是否真的省去fast-path原字读取，还需生成C检查，不能仅从let位置声称。**

新增分支准确要求 `n=1 ∧ 2<p ∧ 4≤m`，`bmm_spec` 的 `h.1` 正是singleton-reference引理所需的n=1。新core对父core的等式本身无需n=1；只有最后接reference时才使用该限制。其他形状继续精确f448分派。batch=0时输出与B map均为空；m=0、p=0、n=0时新最终guard为假。泛化core等式仍由total getD与空Vector语义覆盖，无需额外索引边界假设。

没有新增sorry／unsafe／axiom等禁用构造。B map、分配与输出仍在完整入口中，m≥4只是固定复用启发式，并非速度证明。父f448的row-cache等式及既有singleton证明仍需要精确源码完整gate；本次审查不认证它们已通过。若修复证明或改源码，必须重新核对仅剩2326字节的空间。

DISCOVERY853即使将41、f448、ce全部跑完，也仍只是一组输入；不能写成三组确认、冠军对比或正式准入。可继续按既定规则执行该组原完整gate，是否采纳须等待全部预声明独立组与原阈值。完整源码／来源hash、核对细节与限制保存在 `double-cache-review.json`。本子任务未运行Git、CI、网络、派发或读取未来842／843输入，仅新增本MD／JSON。
