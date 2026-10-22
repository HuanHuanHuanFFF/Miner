# 开发者最小对照请求

本包是 R2-W02 的**待编译候选**。本轮环境没有 Lean/lake；下面的 Lean elaboration、生成 C、原生计时和完整 gate 均 **NOT_RUN**。Python 诊断、脚本语法检查和静态策略扫描不能替代完整 gate。

## 1. 先看生成 C

前提是已有用户指定 commit 的比赛 workspace、真实安装的 Lean 4.34.0、固定 FloatLib 和已构建的 ContractTensor。本包不安装任何工具链，不更新依赖。第三个参数必须是真实 toolchain 的 bin 目录，不是通常的 elan shim 目录。

```bash
bash codegen/run_codegen_probe.sh \
  /absolute/competition/lean /absolute/r2w02-codegen \
  /absolute/lean-4.34.0/bin
```

脚本核对 pin、实际版本、已有 .olean、toolchain 布局和冲突环境覆盖，然后用绝对路径调用已有工具。它发射三组结果：单独的 codegen 小探针、完整 `candidate/Kernel.lean` 的 C、拼接结构证明附录的 ProofProbe。结果写入第二个参数目录，不覆盖 gate、bench、lakefile、依赖或原 Submission。

`lean -c` 只是源码发射诊断；真正受测 native 二进制必须走原 Lake build。第一轮只回答：

1. `dot4` 是否有四个 C `float` 参数/局部累加器，直接尾递归是否为回边？
2. k 循环中是否没有 `lean_float32_of_bits` / `to_bits`、没有四个 accumulator 的箱子、没有每步 F4 构造？
3. B 的四个字段是否由 `lean_ctor_get_float32` 直接读取，布局是否为同对象偏移 0/4/8/12？
4. 每步是否还残留 RC、默认值构造、Nat helper 或闭包调用？A.map/packB 是否有额外临时 Float32 boxes？
5. 实际安装的 `leanc --print-cflags` 是否包含原有 `-ffp-contract=off`？最终受测机器码的有效输出链是否保持独立 mul/add？

生成的 C 不是汇编，也不证明寄存器常驻或 SLP。保留完整 C 与日志，不只截取四行算术代码。若某个证明草稿未能 elaboration，记录完整错误，先修该连接；不要插入占位证明。

## 2. 小型逐位边界诊断

在上述已准备环境里，把实现和诊断拼成**外部临时文件**：

```bash
cat candidate/Kernel.lean diagnostics/NumericCheckAppend.lean \
  > /absolute/r2w02-codegen/NumericProbe.lean
cd /absolute/competition/lean
/absolute/lean-4.34.0/bin/lake env /absolute/lean-4.34.0/bin/lean \
  --run /absolute/r2w02-codegen/NumericProbe.lean
```

追加文件含 IO 主程序，**只能用于外部诊断，不得并入提交 Kernel**。17 个用例逐元素比较原始 uint32 字，覆盖初始 +0、FMA/重结合见证、次正规、NaN payload、Inf、尾块/跨行、零维度。

`lean --run` 不是受测优化 native 二进制。即使小诊断通过，也必须继续做原 benchmark 的 native raw checksum 与最终证明/gate。本轮这份 Lean 诊断自身的 elaboration 和执行也都是 NOT_RUN。

## 3. 原 benchmark 的完整调用对照

### 为什么当前不能使用 `gate --bench`

固定 `gate.py` 的 `BENCH_STAGES` 包含 statement；statement 仍执行 `lake build VerifyBmm`。所以缺少 `Submission.bmm_spec` 的当前 Kernel **连这个模式也不能通过**。不要增加占位证明、改 VerifyBmm 或改 gate。直接构建原 `benchBmm` target 可以诊断：原 `MainBmm.lean` 只调用 `Submission.bmm`，不要求 `bmm_spec`。

### 准备两份已有的隔离工作目录

基线使用开发者现有“单输出 native + 相同 final-finite 精确回退”实现；候选使用 Packed4。两边必须使用相同的原始软件回退、输入分布与环境。不要只与慢的软件 incumbent 比，再把数值适配层的收益都计入本轮布局。

两个目录都应已固定为指定公开版本，拥有同一套已准备好的依赖和真正已安装的 4.34.0。用 `sources/required_workspace_hashes.json` 核对保护文件。只在明确的**隔离开发目录**里写入要比较的 Submission，禁止覆盖活动项目或任何 gate/bench/lakefile/依赖。候选侧示例：

```bash
cp /absolute/FloatLib_R2-W02/candidate/Kernel.lean \
  /absolute/packed4/lean/work/Submission.lean
cd /absolute/packed4/lean
/absolute/lean-4.34.0/bin/lake -v build benchBmm
```

基线侧同样正常构建原 `benchBmm`。保存完整构建日志。不要增加编译选项，不运行依赖 update，不触发安装。构建产物应位于各自 `.lake/build/bin/benchBmm`。原始 benchmark 源码与计时窗口保持不变；kernel 内的输入转换、打包、输出缓冲、回退及释放都留在完整调用内。

### 执行一次明确标记的原生诊断

从本包目录运行：

```bash
python3 diagnostics/compare_bench.py \
  /absolute/native1/lean/.lake/build/bin/benchBmm \
  /absolute/packed4/lean/.lake/build/bin/benchBmm \
  /absolute/r2w02-native-comparison --cpu 3
```

输出目录必须尚不存在。CPU 选与原对照环境一致的可用核心；脚本要求现有 taskset，不安装它。保持默认 `BENCH_PAIRS=500000` 和 `BENCH_INNER=3`，25 个 paired rounds 交替先后顺序，一组比较只选择一次 seed 并复用；新 evaluation 可以选新 seed，或用 `--seed` 重放。Kernel 不得读取 seed 或缓存答案。

脚本逐次比较 dense/relu/wide/raw 四类 checksum，保存每次 stdout/stderr、部分与最终 JSON、二进制 hash、每类最小时间和 paired totals。其状态为 **`UNPROVED_DIRECT_NATIVE_BENCH_DIAGNOSTIC`**：它运行原 BenchBmm 的完整 native 调用，**不复现 gate 的资源隔离、证明检查或统计晋升判定**。checksum 碰巧相同也不等于逐位全域合同证明。

需要的回收件：原始输出、各类两边时间与 raw checksum、paired rounds 和 seed；两个 Kernel SHA256；固定源 SHA256；Lean/C 编译器版本、真实构建命令、CPU/OS 信息；完整生成 C 与最终二进制只读反汇编。若另行插桩研究 fallback/构造次数，单独保存，不把插桩计时当正式结果。

先完成一次默认对照；只有噪声或类间冲突未解决才重复。没有证据时不扩到 8 路或 USize。

## 4. 接入证明以后才做完整本地 gate

补齐布局读取、输出前缀不变量以及已有 final-finite 定理的接入，得到无额外假设的：

```lean
Submission.bmm_spec : Competition.BmmObligation Submission.bmm
```

然后在同一固定环境使用未修改的完整本地 gate：

```bash
python gate.py --slot bmm /absolute/packed4-proved
```

这是本地验证，不是正式参赛提交。保留原 VerifyBmm statement、leanchecker replay、公理检查和全调用 native timing；只能允许合同规定的 propext、Classical.choice、Quot.sound。`#print axioms` 不能替代正确的 BmmObligation 类型。完整 gate 的默认 incumbent 与步骤 3 的数值适配层基线可能不同，报告两种比较时必须注明。

## 5. 停止条件

- 任一原始字不一致、有效链出现 FMA/重结合、零维度或尾块错误：停止晋升。
- 结构证明不能编译：先修具体 proof 连接，不更换合同。
- 热循环仍含转换/四路状态装箱：先定位 C，不扩大路数。
- codegen 合理但完整调用没有重复可见收益：停放此候选，不以孤立热循环速度替代结论。
- 若差异来自 Nat/RC 或准备成本，仅围绕观测到的主因做一次窄修复；不同时添加线程、八路、第二种尾部或另一守卫。
- p 很小时，padding 会使 MAC 接近四倍；本轮没有声明所有形状都加速。后续若按维度选择路线，条件必须对任意数据都正确，所有分支保持同一全域合同。
