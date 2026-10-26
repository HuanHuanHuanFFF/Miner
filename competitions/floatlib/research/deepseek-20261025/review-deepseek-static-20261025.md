# 静态审阅：开发侧 R14 新候选（ef5dcd96 / 6f8808d0 / d94060b2）

时间：2026-10-24T22:59Z。只读审阅 Codex 工作区文件，不编译、不计时、不改对方文件。
目的：检查与 DeepSeek 6990 的 p≤8 路由重叠、复用前提与明显的成本风险。

## 对象

| 候选 | SHA-256 | 字节 | 机制 |
|---|---|---:|---|
| `f01-r14-dev-thin-bcache1` | ef5dcd96 | 236528 | m≥4,n>1,p≤2 时把 B 原生值 map 一次复用 |
| `f01-r14-dev-integer-exponent1` | 6f8808d0 | 253520 | 正常域整数 24×24 乘 + 直接打包，无 Float32 乘/转换 |
| `f01-r14-dev-combined-slim1` | d94060b2 | 243421 | 上述两者 + DeepSeek p≤8 路由；删除 R11CrossRows 腾空间 |

## 已验证的结构事实（静态）

1. `combined-slim1` 的 `bmmBeforeR11Cross` 条件确为 `(n ≤ 4 ∧ 2 < p) ∨ p ≤ 8`，
   与 6990 的 p≤8 路由一致；`source_attribution` 也标注了 DeepSeek 证据。
2. 全文件已无 `R11CrossRows` 引用（grep 0 次），删除后 dispatch 只剩
   `R14ThinBCache.dispatch` 与 `bmmBeforeR11Cross` 两条。
3. `R14ThinBCache.dispatch` 条件为 `4 ≤ m ∧ 1 < n ∧ 0 < p ∧ p ≤ 2`；
   其余 p≤2 形状落回 `bmmBeforeR11Cross` 的 DirectContinuous。
4. `dot_eq` 的证明骨架是 `Packed10.finish_eq_dot` + `loop_eq`，`output` 传入的正是
   `B.toArray.map ExecFloat.Binary.toFloat32`，与 `row_eq` 的前提一致；`core_eq_reference`
   经 `DirectContinuous.output` 过渡，结构上自洽。

## 风险与建议的最小证伪

### R1 `preparedB` 的分配与提升

- `output` 内 `let preparedB := B.toArray.map ...` 是每次调用一次；但 `row` 被内联后，
  需确认编译产物确实只 map 一次，而不是每行重建。
- 建议：statement/benchmark 构建后直接看生成的 C，确认 `B.map` 在热循环外，且只分配一次。
- 若 m=4 附近的收益被分配吃掉，可把条件提高到 m≥8 或 n≥4 做一次对照（同一 run）。

### R2 条件用 `m` 而非 `batch*m`

- 旧 Cross 用 `4 ≤ batch*m`；B-cache 用 `4 ≤ m`。batch 大、m=1..3 的 p≤2 case 不会进缓存，
  仍走 DirectContinuous。
- 这不是错误，但意味着公开套件里大量“大 batch、小 m”的 p2 形状拿不到缓存收益；
  建议用 1—2 个 seed 的 shape 覆盖统计确认目标命中率，而不是只报 MAC 覆盖率。

### R3 整数正常域乘的核心成本

- 新路径去掉 Float32 乘与 toBits，但引入 64 位乘、最高位/移位、ties-to-even 分支和
  carry 处理；在现代 x86 上 `mulss` 仅 1 周期，整数乘 + 分支的收益主要取决于原路径的
  cast/toBits 成本。
- 建议先只测 `6f8808d0` 的 benchmark-only（public-v2，2—3 seed），确认标量 mul 类
  （尤其 mul:dense/ml）确有下降，再投入完整 gate；不要从“去掉了转换”推出提速。

### R4 字节余量

- `6f8808d0` 253520 B，仅余 2480 B；`combined-slim1` 243421 B，余 12579 B。
  任何组合再加减都会触顶。删除 R11CrossRows 换来的是真实余量，但它也改变了 p=2 小形状行为，
  需要在组合版本上重新做完整 gate，而不是沿用组件回执。

## 与 6990 的关系

- 若 combined-slim1 的 p≤8 路由与 B-cache 叠加，两者都作用于 p≤2 大 batch 小 m 路径的重叠区
  需单独统计：B-cache 只覆盖 m≥4，6990 覆盖全部 p≤2；组合收益不应与 6990 的 0.945 直接相乘。
- 建议组合版本用独立 seed，并与 df5c、6990、combined-slim1 同 run 四方对照。

## 边界

以上均为静态观察，不代表编译、证明或性能结论；开发侧候选仍为 NOT_COMPILED / NOT_RUN。
