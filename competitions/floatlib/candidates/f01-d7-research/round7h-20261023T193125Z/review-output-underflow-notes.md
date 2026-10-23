# 整次 BMM 下溢到正零：首份候选说明

候选 `f01-d11-bmm-underflow-zero`，SHA256 `d37743d3ad6fbc0ee81007a70dc8b1795d3b1aeda4fc58ed379cbab7544feddb`，244775 B。以精确 a066 为父本，冻结 writer5b7d 不变。新 Lean、内核、公理、checksum 和性能均 NOT_RUN；以下是证明草稿的机制解释。

## 充分条件与证明缩短

每个原始字去符号后严格小于 `0x16000000`，所以原始指数≤43。次正规指数0的 finiteScale=0，其余 finiteScale=e−1，因此两个 scale 之和≤84，且 UInt64 相加不回绕。

无需再证明尾数乘积<2^48：对任意 UInt64 product，既有 `FastMul.log2_lt_64` 已给 leading<64。因此 leading+scale≤147<172，实际 roundP 进入低指数分支；scale<149，而 `149−scale≥65`，实际 `rseAny` 的 shift>64 分支直接返回0。product=0分支本来也返回带原异或符号的零。

通过已有 `FastMul.mul_spec` 和 `ExecFloat.Proof.mul_eq_spec`，这不是一个抽象舍入模型：新定理目标就是实际 `ExecFloat.mul` 得到相应带符号零。`ExecFloat.add posZero` 加任一带符号零的确切定理，再由原 Fin.foldl 从 posZero 的固定点归纳，得到每个参考点积为正零。没有跳过负零语义的前提，也没有改求和顺序。

Array.all结果连接到任意 getD读数；越界默认值posZero同样满足small，所以参考BMM地址无需额外形状前提。原始任意NaN/Inf都会拒绝guard。全维度及任意巨大Nat的形式结论依赖完整Lean验收，而非有限诊断。

## 运行变化及成本

输入A的Array.all先短路，命中后才扫描B；两者全部命中才 `Vector.replicate total posZero`。未命中调用只改名的原a066入口。所有扫描与填充在计时调用内。一般输入可能在首个非小值上拒绝，也可能扫描较长前缀再拒绝；不能把miss成本写成零。

低指数命中时，计算由输入扫描和输出填充替代所有点积。多小值但不满足强阈值的矩阵仍走原路径；阈值是方便完整证明的充分条件，没有声称是可用域的极限。

## 历史与本次差异

`round1h-20261023T125752Z/astra-subnormal-next.md` 已建议 maxExp(A)+maxExp(B)≤102 的整矩阵零结果。其JSON明确没有新Lean定理或Kernel；`direct-low-input-scope-831.json` 当时已暴露输入的whole_matrix_zero_cases为空。这条数学想法不是本轮首次提出。

本次新增的是具体whole-array scan/fill实现、实际word roundP的全链条证明草稿，以及更强的每输入指数≤43条件。旧每MAC低指数word guard、仅零输入的分支会保留点积循环，不能替代本次完整调用实验。当前904已执行计划的subnormal:2和:3分别为center17/spread13、center22/spread20；它们没有specRate/scaleBlock/raw-magnitude模式。捕获的BenchSuite普通数生成器mag1实际使用 `center−min(ctz,spread)`，因此按该源推断这两case均全命中，不能把center+spread当作几何模式的实际最大指数。此推断尚未用新候选运行确认，也未刷新任何未用确认输入。

`model-precheck.json` 检查352个边界字及123904个有符号乘积的精确整数次正规量化，含所有已接受指数的四个尾数和正负号；另核对NaN/Inf及阈值边界拒绝。它不执行ExecFloat或Lean，不替代完整证明/checksum。

下一步只需要Root对精确d377语句验证；若接受，再跑原完整gate并保留逐case数据与guard命中证据。不能由subnormal cell曝光或逻辑零域直接宣称实际收益。
