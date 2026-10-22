# FloatLib R2-W01 研究包

先读 **FloatLib_R2-W01_report.md**。结论：固定格点的可组合数学结构成立；当前 scalar CPU 候选未胜 native；Lean 编译与正式目标性能未执行。

## 内容

- `lean/`：两份仅 import ContractTensor 的未编译草稿。不是可提交 Kernel；主 binade 证明仍缺。
- `diagnostics/ordered_sum_diag.py`：标准库整数精确 oracle、候选 guard、反例和生成域覆盖。
- `diagnostics/native_cost_probe.c`：独立 CPU 代理，含所有尝试块域检查、量化、端点检查、失败块重放；不是 Lean benchmark。
- `results/`：主实验 JSON、最终 CPU CSV、初始负结果、汇总与生成汇编。
- `independent/`：第二套数学压力诊断及原始输出。
- `appendices/`：定理桥接与独立审查。附录有同轮中途记录；最终性能和路线决策以主报告、最终 CSV 为准。
- `sources_manifest.json`：固定源码文件级 SHA256、Git blob SHA 与核验状态。
- `SOURCES.md`：主要来源链接。
- `SHA256SUMS.txt`：包内每个交付文件的 SHA256（不包含该清单自身）。

## 复现

只需已有 Python 3 标准库：

```bash
python3 diagnostics/ordered_sum_diag.py --vectors 100 --length 1000 --seed 927401 --output results/diagnostics.json
python3 independent/transition/verify_transition.py
python3 independent/transition/verify_anchor_quantization.py
python3 independent/review/check_examples.py
```

CPU 代理仅在已有 C 编译器时运行：

```bash
cc -O3 -std=c11 -fno-fast-math -ffp-contract=off diagnostics/native_cost_probe.c -o /tmp/r2w01_cost_probe
/tmp/r2w01_cost_probe 400
```

独立脚本的部分结果输出到运行目录/脚本目录，原始本轮结果保留在对应 independent 目录内。重新计时随宿主机器与负载变化，不应期待数值完全相同。

Lean 草稿只能放到用户已配置的固定项目环境下 `lake env lean` 检查；本包不安装工具链、不改依赖、不改官方 bench/gate。所有 payload/全域正确性以未来完整 SumObligation 证明为准。

没有正式提交，没有二进制，没有旧项目/私有输入，没有预存 benchmark 答案。
