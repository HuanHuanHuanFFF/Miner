# tinyPC 编码器成本诊断

记录时间：2026-10-11 18:24 北京时间。冻结proof1不变；这次只准备无计时的编码器观察，不更改官方encoder、长度mask或候选参数。

## 已由现有证据排除/定位

I的tiny-config从3094个token降到2276个，输出2487→2155B。两者都远低于官方 `BLOCK_TOKENS=16384`，所以均为一个编码块，不存在“更多token跨出第二块”的解释。tiny-app两者均865个token、原输出相同，作为控制。

原协议四个主/副本观测中，tiny-config的父encoder约249.8–251.7µs，tinyPC约322.0–330.5µs；父parser约12.6µs，新parser约21.3–22.6µs。根线程同场配对分解已把全局新增主要定位在这个文件的encoder，不能继续只优化parser来解释大头。

官方源码 `validator/measure/src/deflate.rs` 已核对固定Linux SHA `172c240014f65d5e2762c1287e4982dd1cd426f2999f74e17011e05f2dc5fdec`：

- `write_block` 在决定stored/fixed/dynamic之前，无条件构建lit/len、distance和code-length三棵package-merge树。
- `package_merge` 的工作不只取决于token总数：每个live symbol构造leaf，随后反复打包和clone符号向量，分布会影响包内容及复制量。
- match还执行由最高码向低码扫描的 `len_code` / `dist_code`；更少token不保证更少match或更少查表步数。
- 原ETINY只使用mask302256384对应的5个长度码，且对未用distance码有额外接受条件。新PC允许更广的长度/距离分布。因此两类字母表都须检查，不能预定“只有长度码”是原因。

这些是源码与原计时的观察。尚不能把约70–80µs差值归因到某一个tree、allocator或符号集合。

## 获授权的最小一次native观察

入口 `scripts/research-round25-tiny-encoder.py`，独立 `main()`；提供纯 `preflight(spec)` 供根线程调用。

配置：`r25_tiny_encoder_counts=true`、`native_encoder=false`；combo与r25-root-tiny-pc8均control=true、无新性能候选、extract/gate为空。保留工作流要求的其他control，但本harness只执行这两个parser各两个tiny输入。

同一个冻结token向量依次送入原encoder及runner临时instrumented-copy。必须满足：

1. 原codec/token实际字节匹配固定hash，诊断后再次核对未修改。
2. 两encoder输出向量逐字节相同，Python对原输出独立zlib解码。
3. 与I真实native的输入、token及输出hash完全一致。
4. 两parser的tiny-app控制在token、输出、频率、树工作量和块决策上逐项一致。

只记录：每块长度/距离/字面量频率、三棵树的live数/打包轮次/实际包数/逻辑syms-vector clone及复制元素数、dynamic/fixed/stored候选bit数、实际块类型，以及由原表重放的len/dist while迭代数。没有Instant、总时间采样或成绩输出。

“逻辑clone调用/元素数”不是机器指令数、实际分配器耗时或可回收速度。次数不能直接换算成收益；观察器代码不能进入正式计时。

## 当前准备与边界

生成器AST、四个trace插入点、官方表解析、一个合法token序列、stdout数组解析及精确spec预检通过。观察器SHA `75f05a6d0201d62f7ea1910e34077cfbe23b4b4a46d0984a094d2d87e1ba5bee`，17,001B。本机只读source副本为CRLF，内存中转LF才与官方pin一致；原文件未写。runner对真正编码器原字节严格核验，不做规范化来掩盖变更。

编译180秒、执行180秒，根线程作业上限12公共runner分钟。超时、非零、计数缺失、输出变化等均保存FAILED回执和日志。当前尚无Rust/native运行结果。

输出：`$RUNNER_TEMP/round4-receipts/r25-tiny-encoder/receipt.json`，以及原始run/compile日志、观察器与harness、固定tokens和两份编码输出。

## 数据怎样改变下一步

- 若token/查表工作减少而树live数及复制量明显增加，优先检验数据驱动的符号集合收敛或单次输出重写；先明确实际稀有码和代价，再实现一份机制，不扫mask/频率阈值。
- 若树工作相近而match查表工作增加，改查短match数量和长度/距离分布，不把问题归因于树。
- 若块类型改变，分别看无条件的树构造与不同emit分支；类型改变本身并不免除前面的三树工作。
- 若主要计数均相近，保留此反证，再考虑一次严格的阶段计时诊断；不由代码印象强行给成本归因。

proof1完整gate若失败，先修复精确Lean；这项观察不覆盖其正确性验收。
