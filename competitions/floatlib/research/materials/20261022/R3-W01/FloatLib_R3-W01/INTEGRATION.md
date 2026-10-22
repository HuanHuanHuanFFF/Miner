# R3-W01 最小集成

## 1. 已有接口

此包不实现内层循环。它使用用户本轮提供的实际接口，参数顺序为：

```lean
within (n baseA : Nat) (A : Array Float32) (B : Vector Packed4.F4 n)
  (hn : n < USize.size) (ha : baseA < USize.size)
  (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) : Packed4.F4
```

已有 `within_eq` 须将这个实际调用连接到：

```lean
Packed4.dot4 n baseA A B 0
  Packed4.zero32 Packed4.zero32 Packed4.zero32 Packed4.zero32
```

片段中的两处接口全名是 `Submission.Packed4.within` 和 `Submission.Packed4.within_eq`。如果真实声明在另一命名空间，改这两处限定名即可；不要添加新的声明占位或把这个等价当成最终 bmm 的外部 sound 前提。

这两个声明不在指定公开父本中。本轮没有读取私有循环文件，因而不能核实它们的真实声明名、隐式参数或编译状态。矩阵界文件可独立检查；包装必须与这两个真实声明联编。

## 2. 先做并列诊断，保持现有入口

已有开发候选应包含固定父本的定义，以及真实 within / within_eq。把组合片段 `Packed4WholeCallFragment.inc.lean` 放在这些声明之后、文件顶层。此时所有外围命名空间应已关闭；公开父本末尾是 `end Submission`。组合片段自己打开全名命名空间，没有 import。

不要把全名 `namespace Submission.Packed4.WholeCall` 塞进仍打开的 `namespace Submission`，避免形成重复命名空间。

直接拼接后的文件仍只有父本原来的 `import ContractTensor`。诊断检查放在另一个临时文件，不并入最终候选；官方词法策略也扫描注释和诊断命令。

在已有固定官方 Lean workspace 中，使用真实已安装 Lean 4.34.0 和固定依赖：

```bash
cat /absolute/FloatLib_R3-W01/src/MatrixBounds.lean \
  /absolute/FloatLib_R3-W01/diagnostics/BoundsChecks.inc.lean \
  > /tmp/R3W01BoundsCheck.lean
cd /absolute/official-isolated/lean
/absolute/lean-4.34.0/bin/lake env /absolute/lean-4.34.0/bin/lean \
  /tmp/R3W01BoundsCheck.lean
```

随后在同一环境检查实际接口联编：

```bash
cat /absolute/Kernel-with-real-within.lean \
  /absolute/FloatLib_R3-W01/Packed4WholeCallFragment.inc.lean \
  /absolute/FloatLib_R3-W01/diagnostics/IntegrationChecks.inc.lean \
  > /tmp/R3W01IntegratedCheck.lean
/absolute/lean-4.34.0/bin/lake env /absolute/lean-4.34.0/bin/lean \
  /tmp/R3W01IntegratedCheck.lean
```

这里 `Kernel-with-real-within.lean` 是开发侧已有、包含真实机器字实现的完整候选；本包没有伪造这个文件。它应仍提供公开父本的 tileResults、core、bmm 和 bmm_spec，以匹配本包的并列诊断证明。

诊断明确检查：

```lean
example : Competition.BmmObligation Submission.bmmOnce := Submission.bmmOnce_spec
```

公理输出必须是 `{propext, Classical.choice, Quot.sound}` 的子集。缺少任何既有工具就记 NOT_RUN；不安装工具链、不改依赖或编译选项。保存真实首个编译错误及目标，本包没有虚构 Lean 错误记录。

## 3. 生产入口中的最小改动

真正需要接入的是 `WholeCall.selectTiles`。保留原 map、packB、outputFromTiles 和空输出/n=0 分支；在它们已有的非零 n 分支中，把原来的：

```lean
let tiles := tileResults batch m n p nativeA packedB
```

替换为：

```lean
let tiles := WholeCall.selectTiles batch m n p nativeA packedB hn
  (MatrixBounds.nativeA_size batch m n A)
```

其中 `hn : 0 < n` 来自原 n≠0 分支。仅在内部 core 签名传入该 Prop 证据；不能把它或 hAS 加到最终 bmm_spec。辅助声明须位于使用它们的 core 之前，并按顶层命名空间放置。

`selectTiles_eq` 将这个新绑定直接重写回原 tileResults，所以后续 lane、输出与数值证明不变。完整示范是包内 `coreOnce_eq_core` 与 `bmmOnce_spec`。开发侧若直接修改已有 core，复用同一重写即可。

若 `core` 本身不接收 hn，也可以让非零分支调用包内 `coreOnce ... hn`，并用：

```lean
(Packed4.WholeCall.coreOnce_eq_core batch m n p A B hn).trans
  (Packed4.core_eq_reference batch m n p A B)
```

连接到父本 referenceBmm。这里复用的是原数值证明，不另造数学假设。

**注意入口状态：**完整片段的 `bmmOnce` 是新名字，未改写 `Submission.bmm`。若只把片段追加到文件末尾，原官方 VerifyFull 仍验证旧 bmm。要验证采用新包装的正式入口，需先按上述方式完成现有入口接线，再运行既有正确性流程；本轮没有代做这一步，也没有正式提交。

## 4. 两个回退

- `hAS` 为假：`selectTiles` 调用原 tileResults，复用当前 nativeA / packedB，不再调用整个旧 core 重做准备。
- 终点非finite：原 outputFromTiles / finish 读取原始 Binary32 A/B 精确重算。该数值回退不改动。

每个 tile 的新叶子直接调用 within，一次；不调用旧 runDot，不新增前三条件的动态判断，不先把任意 Nat n 截断后再判定是否合法。
