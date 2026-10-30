# LazyFPOnly producer research

## 结论

**全 finite binary32 输入下，现有 `+720` 半径严格有效；同公式可以改成 `+719`。`+718` 已被一组 512 项、全 normal 输入的原始 bit 反例否定。**

\[
|s_n-S_n|\le 2^{H-303}\frac{n(n-1)}2
<2^{H+2L-304}.
\]

适用条件：`1≤n≤2^30`，实际有限 word 精确 widening，原顺序 RN64 左折，H 和 n 包括 bias。最终全输入 Kernel 不增加假设：非法 fast 输入、窄域排除、consumer miss 均必须真实回退原正确 dot。

证明关键是每个 `k·2^(H−250)` 都可精确表示为 binary64，因此可以证明 `|s_k|≤kM`。增长因子不是被忽略；报告另保留常规增长因子的精确交叉验证。

## 文件

| 文件 | 内容 / 状态 |
|---|---|
| `producer-report.md` | 全量数学推导、边界、真实 helper 映射、guard、固定接口与下一最小实验 |
| `LazyProducerCore.lean` | 原创实数归纳核心，sole `import ContractExact`，**NOT_COMPILED** |
| `NativeBridgeProbe.lean` | 固定源码中查见的真实接口 `#check`，**NOT_COMPILED** |
| `counterexample718.py` | 最小全整数 RN-even 反例，无第三方依赖 |
| `counterexample718.json` | 反例原始 bit / RLE、精确整数和、误差与 radius |
| `verify_producer.py` | 全整数 / Fraction 边界与固定种子有限模型检查 |
| `verification.json` | 已运行的有限检查结果；不是全域证明或 native 计时 |
| `manifest.json` | 输入身份、状态、每个交付文件 SHA256 |

## 复核

```bash
python3 counterexample718.py
python3 verify_producer.py --output verification.json
```

反例的 `2^-46` 整数单位下应得到：精确和 `144115127946316800`，左折 `144115127946318880`，误差 `2080 > r718=2048`，而 `r719=4096`。

完整有限检查应输出 `PASS_FINITE_INTEGER_MODEL`：4080 个 widening words、4321 个 products、525 个 dots / 40264 项、15717 个 `(H,L)` 编码检查。最长实际 dot 512；`n=2^30` 只做整数 / 有理数公式核对。

## 必须保留的证据边界

Lean 核心的 rounding 接口是显式 theorem 参数，**尚未实例化实际 native Float**。没有安装工具链；没有编译、运行 native benchmark / CI，未集成全12正确性证明，也没有整模型性能结论。

normal+±0 guard 能减少 subnormal widening 的正式分支，但不能消除最细抵消格；全 normal 输入同样能精确抵消到 `2^-298`。proposal 限 `E2..253 && fraction!=0` 不降低 producer 的前缀误差义务，且不能排除本次 718 反例。

zip 仅包含原创分析、Lean 数学核心、probe 和验证脚本；不包含上游完整 Kernel 或源码缓存。
