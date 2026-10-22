# FloatLib R2-W03 研究包

先读 `R2-W03-report.md`。本包是一个可复核的转换机制研究，不是通过 gate 的 Kernel 提交。

## 结论

原 normal 数值重构公式数学成立。固定 Lean 4.34 的 unsigned integer casts 有透明逻辑模型；有符号常量表是本轮最值得进行固定 Lean 验证的实现。独立 C 多向量对照反驳了“无表 wide 一定更快”。

## 状态

- Python 精确 dyadic 有限诊断：PASS。
- C 转换、原序 sum、64向量 pool 有限诊断：PASS；性能只代表自写 C surrogate。
- Lean 编译：**NOT_RUN**，没有安装工具链。
- 全域转换等价定理：**未完成**。
- 官方 gate／sum 或 bmm 合同／官方 bench：**NOT_RUN**。

## 内容

| 路径 | 内容 |
|---|---|
| `R2-W03-report.md` | 完整中文综合报告、证据边界、下一步与来源 |
| `ConversionCandidates.lean` | 纯表、UInt32 dense、UInt64 wide 转换候选；不含等价证明 |
| `ProofBridges.lean` | 模型连接与舍入组件、十个闭项诊断，全部 NOT_RUN |
| `diagnostics/exact_dyadic_checks.py` | 纯整数 RN-even 诊断与反例 |
| `diagnostics/variants.c` | 本轮自写 C 转换／有序 sum 对照 |
| `diagnostics/runtime_stub.c` | native canonical-NaN 外部调用 surrogate，非 Lean FFI |
| `diagnostics/diagnostic.c` | 浮点环境、有限正确性与两种输入布局的性能诊断 |
| `diagnostics/run_diagnostic.sh` | 本地编译运行；无依赖安装、网络、正式提交 |
| `evidence/` | 已运行日志、编译器版本及汇编 |
| `analysis/` | 本轮三路独立审计与最终交叉检查 |
| `sources/source_manifest.json` | 实际读取的固定公开源 URL、字节数与 SHA256 |
| `LICENSES/FloatLib_LICENSE` | candidate-local 证明帮助引理的上游 MIT 许可 |
| `SHA256SUMS.txt` | 所有包内其他文件的 SHA256 |

## 复现

在已有固定项目环境，不改变任何配置：

```bash
lake env lean /absolute/path/to/ProofBridges.lean
lake env lean /absolute/path/to/ConversionCandidates.lean
```

这两条本轮没有执行。`With` 候选接受表／常量参数，正确性目标只针对使用本包精确常量的包装函数，不能对任意参数断言正确。

普通本地诊断：

```bash
python3 diagnostics/exact_dyadic_checks.py
bash diagnostics/run_diagnostic.sh
```

C 数据默认由运行时钟产生种子，候选不读取该种子、不缓存结果。需要重现已有输入时可向脚本传入日志中的种子；这只控制诊断数据，不改变被研究的转换函数。`exact_dyadic_checks.py` 会重写其旁边的结果 JSON；C 脚本会创建诊断本地对象文件与可执行文件。初次校验请先核对 `SHA256SUMS.txt`。

完整报告优先于独立子稿中的中间建议。所有运行证据均为本轮新造诊断；没有旧私有附件、账户操作、官方脚本执行或正式提交。
