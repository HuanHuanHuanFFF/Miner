# 原生四字段 scale table：本窗 NO-GO

2026-10-27 03:04 UTC。**不建议 D 为此排 Lean／CI：Array F4 没有删掉所假设的依赖读取。** 这是投入决策，不是所有字段布局都不可能提速的结论。精确父本仍为 B2 `622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58`／226829 B。

- **实际旧路径**：`scaleTable : Array Float32`，共512项；不是 UInt64 表，也未被展开为立即数选择。已复核 CI16 `40436948264` 原 C `7e1a7c77…`、ASM `91376197…`。普通 ADD 两次读取分别为 `0x56/0xb6: mov rax,[array+index*8+24]` → `0x5b/0xbb: mulss xmm,[rax+8]`。`lean_unbox_float32` 本来就是原生字段读取，没有再套一层字段盒；普通臂仍为54条静态指令，不能换算成耗时。
- **本提案与负源的真实差异**：F4 省去 Float64 往返和 global valid，证明可用纯投影；但 `Array F4` 仍是“数组槽指针 → 记录字段”两级依赖，未取得 FloatArray 连续存储真正删除槽指针加载的收益。旧 compact `9c4e9505…` 的完整发现运行 `40417039536` 为 whole `1.0296713646`、gain p05 `−0.0456265`。这只否定旧精确实现，不能直接当作 F4 负测；本次 NO-GO 来自新方案的实际成本前提。
- **完整增减**：可减的是被访问表的对象数量／工作集，省时 UNKNOWN；每次热读仍留全局表访问、槽指针、Float32字段、mantissa cast、scale mul及原守卫。新增分组索引和动态选四字段，最终是分支、选择或索引 load 未编译。若从旧表初始化，旧表仍按已审编译模式持久化，另建128记录／512字段；不能宣称总内存下降。ELF64逻辑申请模型为旧10264 B、新4120 B、同时保留14384 B，未计分配器取整，不是实际驻留量。
- **覆盖与上限缺口**：CI16 四块 control 的 ADD／MUL 各占 whole 37.3927%／39.3687%；即使所有收益都来自两者，whole减10%也需两者平均减约13.03%。真正命中scale读的耗时权重、cache miss／stall份额均 UNKNOWN；没有依据把较小静态表推成这种幅度。SUM/BMM调用覆盖也未新增测量。
- **历史查重与证明边界**：已查 R19 compact、quantized-certificate及R18 structural-frontier。前者是宽浮点表，后者分别是整数精确前缀证书、动态 BMM temporal 字段块；未在这一受限范围发现同一静态 F4 scale 表负源。纯数据证明纸面接口为 `j = 4*(j/4)+j%4`、余数四分支、`Array.ofFn`投影，直接保留原 Float32／NaN／±0；typed draft、root audit、replay、新C和计时均 **NOT_RUN**，未生成新 Kernel。
- **最小证伪已完成／重访条件**：新记录必须先能删除真实依赖读取，或先取得足以支付字段选择的旧表cache成本证据，才值得重开。固定运行时和真实 C 已证伪本次“打包即少一次指针读取”的前提；不以阈值、seed或新框架续投。

证据与精确原件路径／哈希见 [evidence.json](evidence.json)，可用 [audit.py](audit.py) 重核；本地该审计通过。开始02:58:44 UTC，03:04 UTC完成主判别，最晚03:30任务窗口未用满，原因是成本前提不成立。新增Lean运行0、CI0、候选0；token／缓存用量 UNKNOWN。未读 D17/D18及以后确认输入或结果；无Git、安装或后台作业。D继续独占Git／CI／采用决定。
