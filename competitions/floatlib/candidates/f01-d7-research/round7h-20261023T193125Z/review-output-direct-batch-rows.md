# DirectContinuous：按 batch 再按 row 连续写出

**READY_FOR_STATEMENT**。唯一候选 `f01-d11-bmm-direct-batch-rows/Kernel.lean`，SHA256 `1c544655a8bc6e1d5267dcf98fc1359263cba5da71bc9c72924119b0fa60e6e2`，251809 B，余4191 B。父本严格为原2aaa `2aaa5d9e84c758a23a8c6dc1f77d800950fbaa5769aec7a38d299741c17a5f56`，248566 B；没有组合0655、6c2d、self-classifier或官方add回退。

只替换DirectContinuous原output/output_prefix的742 B，新增batchRow、batchStep和完整Prefix证明桥，净增加3243 B。新output先对batch做Fin.foldl；每batch捕获 `baseA0=b*m*n`、`baseB=b*n*p`，再对m行做Fin.foldl，行i从 `baseA0+i*n` 读取A，按原列顺序将同一个NativeFinal.dot写入原连续Array。没有新增每行tuple或行数组，没有nativeA/packedB准备。这个等差地址方案经Root同意，用来隔离batch遍历和去除每行除法。

新运行调用链为output→batchStep→batchRow→RowStream.emit→原NativeFinal.dot。前三个writer定义中没有除法/取模，也不调用旧row或证明用batchRowIndex。旧row及其r/m仍保留，作为证明目标而非新writer的运行callee；不能据整个文件仍有div就判定新路径未变化。此前实际C每row只执行一次r/m，64/32位分支二择一，本次不把它误计为两次。

证明先构造仅证明使用的flattened row `b*m+i`，由 `Nat.mul_add_div` 和i<m得到除以m等于b，再用 `Nat.add_mul`证明新旧A地址相同，因此batchRow等于旧row。已有row_prefix传递到新行，通用foldl_inv依次证明本批m行和外层batch前缀；继续沿用旧core长度桥、core_eq_reference与全部四份公开spec证明。没有引入fold-product重排引理，也没有展开具体完整输出做类型转换。

新证明的命题覆盖全部Nat维度：m=0时没有Fin m行，除法正性只在有i的证明分支使用；空batch/p、n=0、尾部均接原dot/Prefix语义。运行分派仍严格是原n≤4且p>2，其余形状、巨大Nat表示与回退保持父本原字节。公共add/mul/sum/bmm及四spec（包括证明正文）、原native MAC和原字NaN回放、全部父本作者说明均逐字节不变。

本地固定父本/替换块hash、精确逆变换恢复2aaa、声明库存、八个公开导出及四spec完整字节、新运行源码调用检查、资源选项不变、许可和原版policy检查PASS。**新Lean语句、leanchecker、axiom审核、checksum、完整gate和实际C/汇编均NOT_RUN，性能UNKNOWN。** 源码无div不保证整体提速；额外batch循环和捕获/地址成本必须在Root安排的原版full gate中与同场2aaa比较。只生成这一份完整候选，失败源保持冻结，在下一修订修复实际反馈。
