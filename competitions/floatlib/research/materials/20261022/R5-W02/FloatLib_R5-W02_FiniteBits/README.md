# FloatLib R5-W02 FiniteBits

全域证明草稿与最小集成。所有 Lean 编译、公理审计、官方 policy/gate、候选 C 生成与计时状态均为 **NOT_RUN**。

先读 `FloatLib_R5-W02_Report_zh.md`。

- `candidate/FiniteBits.lean`：2,693 bytes，7 个完整证明体和一个 inline UInt32 分类器，仅 import ContractTensor。
- `candidate/Kernel.lean`：对指定父本的完整集成候选，136,051 bytes，仅 import ContractTensor。
- `integration/`：局部替换、原段、精确 diff、SHA 锁定的新文件生成脚本。
- `diagnostics/`：独立 #check/#print 命令、本轮机械检查状态、独立静态审阅。
- `sources/` 与 `LICENSES/`：固定公开来源、声明依赖与许可。
- `SHA256SUMS`：除自身外每个有效载荷文件的 SHA256。

父本 SHA256：
`ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630`

新完整候选 SHA256：
`c09eb599cebddb59acd2a5fad1e6d8ce4eba1ca27f8469e03e6592b40d944b7a`

## 原固定环境中的使用

直接编译完整候选，或者把局部变更合并到当前开发分支。无需新增模块依赖、改 lakefile、改编译选项或改 gate。此包未正式提交。

若要由原父本重建：

```bash
python3 integration/apply_to_parent.py /path/to/parent/Kernel.lean /path/to/new/Kernel.lean
```

脚本拒绝父本 SHA 不一致、输入输出同路径、输出已存在。它不联网，不调用 Lean，不覆盖官方文件。

诊断命令不能写入提交候选。可只为诊断构造临时副本：

```bash
cat candidate/Kernel.lean diagnostics/Commands.lean.inc > /tmp/R5W02Diagnostic.lean
```

然后在已经配置好的固定 Lean 项目中，按现有方式编译临时诊断文件并检查输出。不要把独立文本预筛或直接 Lean 编译说成完整官方 gate。

正常路径的源码目标为一次 toBits，随后 UInt32 分类并复用该 word。原 raw fallback 保留在 else 内。预期减少的 finish 层调用数是有限结果数 F；未取得任何实际加速结论。
