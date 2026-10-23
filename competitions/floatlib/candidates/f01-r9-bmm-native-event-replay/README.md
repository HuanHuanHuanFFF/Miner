# R9 BMM native event replay

候选SHA：`0d9c2c96a4cb6c92609d8fbd1efac71852d7b75fafac5d3723935f17d5c15ee0`，239412字节，余16588字节。父本是已验41组合，SHA `41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7`。

仅在原NaN endpoint的BMM回退中使用native accumulator重放前缀；首个NaN事件执行一个原序精确add(mul)修复，并由父本W05的实际quiet证明允许直接返回。原native完整首遍仍在，准备、packed/direct布局、乘加顺序、getD边界、全部scalar和单遍sum未变。

相对旧未测a9草稿，本稿使用已验41的W05数学资产移除运行时quiet检查及精确后缀分支，采用显式fold等式运输。不是宽度/shape阈值变体，也不把旧未测草稿当作失败或成功结果。

`build.py`默认只读复现；首次`--write`拒绝覆盖已存在Kernel/manifest。increment.lean只是构建输入，不被Kernel导入。提交包仍仅需Kernel.lean。

新源静态policy、namespace/四导出四规格唯一性、父本逆向字节检查通过。**精确新Lean、完整gate、代码生成和性能均NOT_RUN**。事件前native判据和事件重复计算可能抵消收益，不根据模型步数宣称加速。D负责原完整gate及冻结独立确认。

[交接说明](../f01-d7-research/round1h-20261023T125752Z/astra-bmm.md) · [精确状态](../f01-d7-research/round1h-20261023T125752Z/astra-bmm.json)
