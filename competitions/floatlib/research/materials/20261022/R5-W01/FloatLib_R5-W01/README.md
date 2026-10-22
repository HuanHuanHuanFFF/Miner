# FloatLib R5-W01 OutputRows

只包含一条实现：每 batch 先展平行，再展平 batch。热循环和数值处理复用精确公开父本。

**NOT_RUN：**尚未执行 Lean elaboration、内核、公理检查、完整 gate、候选或计时。本机没有 lean/lake/elan，未安装工具链。完整证明脚本已提供，不代表已编译通过。

## 文件

- `OutputRows.inc.lean`：134 行主追加片段，已合并通用与 Packed10 接线，不含 import。
- `Rectangular.lean`：通用矩形构造器的独立检查文件，仅 import ContractTensor；不要和主片段重复追加。
- `components/Packed10OutputRows.inc.lean`：具体接线原件，已包含在主片段中，供逐项审阅。
- `compose_attempt.py`：只接受给定父本 SHA，生成追加验证版或真正启用版，不覆盖既有输出文件。
- `FloatLib_R5-W01_Report_zh.md`：完整说明、费用、反例和完整源码。
- `diagnostics/`：分离的公理打印请求、环境、计数、解析反例和实际静态检查记录。
- `review/`：通用证明、接线和独立反方审查原件。
- `sources/`：固定源码清单和许可。

## 固定父本

URL：https://github.com/HuanHuanHuanFFF/Miner/blob/e5b144bf77d477919f4787e36311cf65d2a23c15/competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean

132965 字节；SHA256 `ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630`。

## 最小使用

在已经配置好的固定官方 Lean 工作区运行。无需安装、更改依赖或参数。

```bash
python3 /absolute/path/FloatLib_R5-W01/compose_attempt.py --parent /absolute/path/fixed/Kernel.lean --output /tmp/R5W01_Append.lean --mode append
lake env lean /tmp/R5W01_Append.lean
python3 /absolute/path/FloatLib_R5-W01/compose_attempt.py --parent /absolute/path/fixed/Kernel.lean --output /tmp/R5W01_Active.lean --mode activate
lake env lean /tmp/R5W01_Active.lean
```

append 模式只增加定义，不切换原 Submission.bmm。activate 模式才切换原入口的非空核心与对应证明调用；字节恢复检查确保其他父本内容原样保留。

公理请求仅用于临时文件：

```bash
cat /tmp/R5W01_Active.lean /absolute/path/FloatLib_R5-W01/diagnostics/AxiomChecks.inc.lean > /tmp/R5W01_Axioms.lean
lake env lean /tmp/R5W01_Axioms.lean
```

不要把诊断文件放进正式候选。包内不复制完整父本或完整组合源码；脚本在精确父本上生成报告记录的字节与 SHA。没有正式提交。
