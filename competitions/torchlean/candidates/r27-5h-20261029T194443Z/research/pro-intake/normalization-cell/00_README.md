# R28｜完整 affine 分子的舍入区间认证

## 一屏结论

**值得做一次完整 native 成本实验；目前不能声称整模型已降耗 10%。**

public23 的 LN 出口 `Ya7G` 每元素仍经历三组主要商余，终端 `rrsG→rqU` 再有一组。新机制保留 `Y8f` 精确行统计和正确舍入的 `dw`，直接形成**含 bias 的完整有符号分子 P**，从 P 给出任意浮点候选，再用整数 midpoint 不等式认证最终 raw32；失败回原出口。它绕过求商余的整个任务，与团队的精确 reciprocal 缓存竞争同一热区，收益不能相加。

- 原快速域有 `|P|<2^98`；两个 UInt64 足够。端点乘积 `<2^62`。
- 交付原型扩大为逐项检查的 128 位域；精确整数链无除法，但 proposal 仍有 **1 次 native double 除法**。
- 零项不参与指数锚点选择；先精确处理 bias 抵消，再生成 proposal。
- 只接受非零正规候选的**严格**舍入区间；中点、零、次正规、非有限、越界全部回退。

| 证据层 | 当前状态 |
|---|---|
| 数学恒等式、位宽、边界推导 | 已完成书面推导 |
| Python 精确有限模型 | `FINITE_MODEL_PASS`，本轮检查 0 错误接受 |
| Lean 小引理与 native 草稿 | **`NOT_COMPILED`** |
| word-level soundness / `Submission.correct` | **OPEN** |
| native / 完整模型计时 | **`NOT_RUN`** |

## 首个可证伪实验

用冻结的同一 official 模型、输入、编译和计时边界，对比 **A=原23** 与 **C=新 attempt + 原 Ya7G 回退**；若团队 reciprocal 版本可用，加 B 对比。先逐位差分，再测完整调用，必须计入 proposal、128 位形成/guard、失败回退、数组准备与回收。不要只计认证成功分支。

令 `f` 为被替换旧出口的整模时间份额，`p` 为按旧成本加权的可跳过份额，`a` 为全部 attempt 成本/旧出口总成本，`h` 为其余新增整模开销。目标条件为 **`f·(p−a)−h≥0.10`**。若热区份额不超过 10%，任何正成本替代都不能靠此处达成 10%；若完整 A/C 实测不足 10%，停止扩大证明投入，先解决明确的成本瓶颈。

官方 `43/23=0.9072362322` 仅可作为条件目标标尺：若能同基比较，比43再降10%需比23降 **18.3487%**；它不是直接同机性能证据。

## 复现与文件

```bash
python3 r28_exact_model.py --json finite_results.json
python3 pressure_extra.py --model r28_exact_model.py --json pressure_extra_results.json
```

均只用 Python 标准库。详细推导、反例、失败边界及下一条路线见 `01_RESEARCH.md`；接线义务见 `02_INTEGRATION.md`；精确源身份见 `03_SOURCES.md`。zip 仅含本轮原创片段，不含上游 Kernel、Contract 或旧 helper。

日期：2026-10-30（Asia/Shanghai）。
