# 直接点积与单遍求和组合草稿

精确源码 `cc06a47f`，232363 字节；原256000字节上限内，未删来源或注释。以3d9求和稿为父本，只将其中仍等于共同0e8父本的BMM尾段，替换为97f已经准备的直接点积尾段。逆变换逐字恢复3d9；求和新增声明与add/mul均不改。

此稿同时包含已备的非NaN终点、quiet-NaN点积后缀、直接布局和单遍求和。60f、9a的独立完整结果仅支持组件起点；97f、3d9和本组合的精确Lean、完整gate、生成代码及性能仍未运行。

先通过本稿原四项规格的精确statement，再对当前保留60f跑原版public-v2完整成本。只有实际收益成立后，才冻结并用全批关闭观察器的新seed、新runner独立确认。

[生成与逆变换检查](../f01-d7-research/build-direct-singlepass.py) · [静态规则预检](../f01-d7-research/direct-singlepass-static-policy.json) · [元数据](manifest.json)

[另次源码审查](../f01-d7-research/direct-singlepass-review.md)已核独立逆变换、四个导出及作用域。DirectSmall正文与60f相同，调用的NaN冷路继承0e8而与60f不同，完整路径的计时仍须重验。
