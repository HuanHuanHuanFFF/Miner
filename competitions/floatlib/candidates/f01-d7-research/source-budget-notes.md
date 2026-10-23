# 单文件大小预检

用于官方 `Kernel.lean` 的 256000 字节上限。它准备本地副本和精确报告，保留全部含代码的物理行、缩进及行内注释；新字节仍须另跑 Lean 和完整 gate。它没有性能收益声明，也没有组装新的运行候选。

仅删除占整行的注释。识别到 copyright、license、attribution、author、Sources、MIT/Apache、©、(c) 等明确来源/许可标记时，保留相邻整段注释直到下一段代码，包含授权和免责声明正文。标记表在脚本内公开；这是有界的保留规则，不能代替任意自然语言声明的人工判断。遇到活跃字符串、反引号、quoted identifier 或未闭合注释则拒绝处理。输入、输出和报告必须互异，输出及报告只能新建。

```powershell
python competitions/floatlib/candidates/f01-d7-research/source-budget.py --input <Kernel.lean> --prepared-output <新的本地副本> --report <新的报告.json>
```

[8组文件边界回归](test-source-budget.py)通过，原始输出及脚本/测试 SHA 见[回执](source-budget-test-evidence/receipt.json)。[另次审查](source-budget-review.json)复现并核对了三类保留漏项的修复。测试只使用轻量 Python 子进程，没有运行 Lean、Linux 编译器或 CI。

| 精确原候选 | 原字节 | 修正后预备字节 | 少占字节 |
|---|---:|---:|---:|
| 60f direct-nonnan | 155103 | 147066 | 8037 |
| 3d9 singlepass-sum | 230650 | 210754 | 19896 |
| 939 scalar-exceptional | 175363 | 166529 | 8834 |
| 4792 canonical-dot-scan | 195683 | 182671 | 13012 |
| 47d singleton-native | 188335 | 176512 | 11823 |
| 353d low-normal-sum | 174914 | 163233 | 11681 |
| 97f direct-nonfinite | 174925 | 163749 | 11176 |

[完整大小、代码行和声明哈希](source-budget-summary.json)绑定7份未变输入。预备副本只存在忽略目录；未替换保留版本。不能将各文件的节省直接相加，推成尚未接线的完整组合。

旧 be0a57f8 版本会遗漏 attribution/source 说明、截断连续行注释许可证；47d 的旧预备副本实际漏掉 c44c 来源块。随后 53aa85af 又暴露 © 简写漏项。失败脚本、输入、错误输出和回执分别冻结在 [licence0](negative-sources/source-budget-licence0/receipt.json)、[copyright1](negative-sources/source-budget-copyright1/receipt.json)，旧预备源按原哈希留在本地。当前 e1ee62f4 已通过反例和8组回归，并在实际47d副本重新确认完整来源块 SHA `184a2688…66df`。原始候选从未改写。
