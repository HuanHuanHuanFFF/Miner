# Winograd follow-on：一屏结论

**范围修正版：沿用既有冻结原生判别，不扩展队列、不进入大证明。Lean：NOT_COMPILED；性能：UNKNOWN；宽 gap Int 终端：UNKNOWN。**

- **接线范围已纠正：** “未接线”只适用于先前孤立 Runtime 片段。既有 **600eaaa1／71667B nativefinish-v2 已由 builders 接入 `totalWords→finishWords`**；父控逐字节重构报告旧调用0、新调用1。本包不再把接线列为新增效果。
- **fallback 范围：** v2 已在所有输入 cache 无效时，先于 W 准备返回原整入口。仍进入逐输出分支时，mixed-validity scalar miss 丢失四行／稀疏融合的风险保留。public23 的 `QY6G→YL/YD` 成本审计是独立源码对照，不等于 source12 实测。
- **保留public23成本反例：** 若其sparse路径每行 `nnz≤ceil(K/2)`，配对主体乘法无节省。`8×20×40`、X每行一个1、W与bias全1：320→3680次主体乘法，**11.5×**；连共同bias为6.25×。这是源码计数，不是source12计时。
- **新边界：** 全零 `Yc.low=510`，可令 native bodyShift=383。补丁用确证零 body 直接返回非零有限 bias；完整 exact-zero 在 ReLU 下免回放，非 ReLU 保留零符号。

**实际冻结实验范围：** source12 内部对照 vs 已有600e；完整 `normalized_mlp`、batch8全部三个linear（含输出宽10），batch1及norm不变。早期Mixer两入口建议已撤回其作为600e实验描述。本包的 signed63／零出口片段仅为未编译研究草案，不加进冻结候选。见 `SCOPE_CORRECTION.md`、`NATIVE_EXPERIMENT.md`。

**沿用上轮实跑：** Python 精确整数模型通过625组配对、70组字更新、703个准入有限输出（387个 native finish）、450个抽象终端边界、625次零 body 快捷检查；重现旧 signed63 反例。316个宽 finish 路由只记录，未验证缺失的 helper。这些不是600e性能或模型覆盖率；此次未重跑研究。

```bash
python3 verify_winograd.py
```

`REVIEW.md` 的数学推导、反例与条件成本界保留。600e的71667B身份由冻结请求与父控重构报告给出；本环境仅静态核查所补builders，未重构／编译整候选，未执行原生实验。全12证明及宽gap helper仍未验证。未用在途确认材料、Git／CI、工具链安装或新增子代理；包内无上游Kernel或补充builders全文。
