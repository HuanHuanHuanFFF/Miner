# R10：n=1原生乘积专化

SHA-256：`ff34b1b7e2166b7b22f53d5f3e656b6567fd7487d457343e3599885757ab25ad`；247919字节，余8081字节。父本是已验41组合。

只在n=1时直接计算一项原生乘积：非NaN结果直接封装，NaN使用原始参数调用精确Submission.mul；最后仅将原字0x80000000转为0，模拟原+0种子加法。每个乘积仍先舍入，保留NaN sign/payload/优先级。n≠1通过可逆重命名调用原41矩阵分派。scalar、sum、原BMM内部实现及许可原字节保留。

运行体逐字节复用未完整验收的47d singleton-native-normalize；不能继承其证明或性能成功。只将旧seed块的两个重复classifier证明体委托给41已验Submission.R7W05引理，其他数学和地址证明保持。该调整不改变运行代码。

`build.py`默认只读复现，首次`--write`拒绝覆盖已有Kernel/manifest。原gate静态policy、namespace、四导出/四原spec及完整父本逆变换通过；**本新精确源Lean、完整gate、C/asm和性能均NOT_RUN**。

测试应保留完整准备/输出、NaN回退和非n1分支开销，由D按冻结源与41对照完成三个不同输入组。旧输出数或cell份额不是预计收益。

[研究交接](../f01-d7-research/round2h-20261023T170031Z/astra-bmm.md) · [精确身份与映射](../f01-d7-research/round2h-20261023T170031Z/astra-bmm.json)
