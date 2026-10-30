# ReLU integer sign certificate — R27 first recoverable result

数学、实际 Contract 语义、完整 bias 界、成本判停条件及接口缺口见 `REPORT.md`。

| 文件 | 用途 | 状态 |
|---|---|---|
| REPORT.md | 独立研究结论与下一最小实验 | 完成 |
| integer_model.py | 原创 pure integer probe、精确 oracle、最小反例及自造输入 | 已运行 PASS |
| results.json | 固定种子重放结果 | 已生成 |
| IntegerBridge.lean | 原创最小代数桥，依赖原 ContractExact | **NOT_COMPILED** |
| MANIFEST.json | 文件哈希和验证范围 | 已生成 |

复现：

```sh
python3 integer_model.py --output results-replayed.json
```

不安装任何依赖。不要将 Python 执行时间当成 native 成本。Lean 未编译，不声称全 Kernel 证明或任何性能百分比。包内没有原上游 Kernel，没有当前冻结输入/结果。
