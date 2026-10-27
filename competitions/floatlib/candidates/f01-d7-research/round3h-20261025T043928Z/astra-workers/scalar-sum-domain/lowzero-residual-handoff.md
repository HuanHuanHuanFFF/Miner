# LowScale residual zero：有旧完整证明及负结果，保留后置片段，不加D队列

冻结cutoff84原件837341a5不变。本次只写研究证据与可选片段，未生成新完整候选、未编译/CI。

## 先纠正历史状态

`f01-d7-low-zero/manifest.json`仍写NOT_RUN，但后续完整回执已经存在：run39904491256、seed816，原始verdict为passed=true、stage=score、25轮，精确源SHA `e139093ac7f8fc6133bba266d1f2dee25e282d185996e72f2cd91dd073630d24`。

同组相对60f父源，whole归一化比值 **1.0243151645**，mul归一化 **1.0709083051**；原始mul比值1.0761033849。这个原实现没有足够收益，不得改名或换seed重新挑结果。原LowScale低分支与df5c相同，较高native分支后来变化；因此旧负结果是必须考虑的强证据，但不代表所有新guard安排不可能。

已有完整数学接口全部可复用：`LowZero.outer_finite`、`outer_special_false`、`mantissa_zero`、`product_zero`、`core_zero`、`zero_eq_low`。不需新RNE/underflow证明。

## 本次精确目标域与观察

目标为 `84 < ex+ey < 128 ∧ (raw x=±0 ∨ raw y=±0)`。任一zero指数为0，所以命中时另一侧的原指数就是85…127；不会命中双方zero，也不会命中NaN/Inf。整个特殊值排除仍由原<128守卫保证。

`lowzero-residual-screen.json`对三组当前已见DF计划与旧816失败计划，每个mul case取256个确定性分层样本，共43,008对，0.293秒；内部4.4秒/44,000对上限，外部5秒超时实际执行。样本是固定官方生成器的Python转录，不是运行时计时或新holdout。

| 已见run | sparse残余命中/1536 | sparse整个cell占whole | specials残余命中/1536 | specials整个cell占whole |
|---|---:|---:|---:|---:|
| 40129155932 | 158（10.29%） | 6.05% | 125（8.14%） | 2.95% |
| 40152158687 | 294（19.14%） | 6.80% | 130（8.46%） | 2.76% |
| 40155753018 | 366（23.83%） | 5.89% | 75（4.88%） | 2.76% |

其他五个mul cell在这些样本中残余命中为0。special/sparse整cell成本合计8.64%–9.55%只能作为极宽上界，不能把上述命中频率乘这个上界写成可移除耗时。实际目标路径成本与能省的份额均UNKNOWN。旧816计划同样有555个残余样本（sparse337、specials218），当前三组分别283/424/441，没有出现比旧负结果更高的总体样本机会。

新guard若在cutoff84之后，确有不同动态范围：当前样本中新增zero判定只处理85…127；这部分zero命中比例约55.6%/66.0%/73.6%，不用对已被84接受的tiny／zero再判断。该变化与旧全<128零守卫不同，但没有目标机器成本证据，仍不足以由我要求新增完整D。

## 精确成本边界

原 `FastMul.roundP` 与 `LowScale.roundLow` 都先处理product==0，零输入本来就不走fastLog2或RNE。因此本项**不能**宣称省去zero的最高位搜索／舍入。源码层候选仅可能省去special、field、mantissa、finiteScale、整数product、roundSelect等前置工作；实际机器代码可能已共享或消掉部分操作，其动态成本UNKNOWN。高分支不新增判断。

## 可选片段与接入限制

`ResidualLowZero-reserve-fragment.lean`：4,378 B，SHA256 `ea888b468b690510c70bb6f5f75fe71c081ced1b4396a5a708fd37ab5bd02c7d`。

- 数学部分从e139完整通过源精确复制，只将namespace重命名为R15ResidualZero，已逆向核对。
- 导出的mul/spec是精确替换片段：先<128，再≤84，拒绝后才做原已证magnitude==0判断。没有为未经计时的`word<<1`写新证明；mask与shift的机器收益不能凭源码认定。
- 新组合的mul_spec仍NOT_RUN；片段并非完整Kernel，不能单独交gate，也不能直接追加重复导出声明。
- 直接加到未压缩8373原件会达到257,035 B，**超256,000 B上限**。按当前D精确组合214,897 B计算相同替换投影为218,370 B，但接入者仍须核对实际源、声明范围和最终SHA；本子agent没有改D源。

优先级：**停放，不增加D队列。** 如果已有cutoff组合完整反馈接近门槛，并且根/开发认为该小范围前置成本值得一次独立检验，可复用片段；届时按新精确组合自己的首次D验收，不叠加分项收益，不复测旧e139挑seed。
