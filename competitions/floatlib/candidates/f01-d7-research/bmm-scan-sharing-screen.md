# BMM 重复 rawNaN 扫描共享：机会筛查

开始 2026-10-23 01:08:41 UTC，最多 30 分钟；主窗截止仍为 04:22:17 UTC。只写本报告与同名 JSON；未写 candidate/helper、未改 R/Git/CI、未上传或安装依赖，未创建外部研究会话，未重跑浮点枚举或读取 future confirmation。 最终核对：2026-10-23T01:33:19Z。

**决定：PARK 共享摘要实现。** 全量预计算把工作前移到大量原本无冷扫描的普通路径；“全部槽位先建 Thunk、冷分支才 force”仍可能产生大量永不使用的对象。Lean 有真实的同对象缓存机制，但当前 RowStream/RowOutput 没有现成缓存所有者或已验接线，不能把 lazy 当零开销。保留一个确实存在的局部复用信号及最小重开判别，不生成变体网格。所有收益 **UNKNOWN**。

## 原始807分层：计数不是时间

本次读取固定 plan SHA `9cc5d7368749c369172b019d66bc4cd8455ae4323d0b9a175bd031f936e78622`、[cold-scan-cost 原记录](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/cold-scan-cost-807.json)（SHA `aa251334465a3d52ef9b2ad01bcd771b39ae7f06bf19b928ca75c1caecad002f`）及 [frontier记录](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/frontier-scalar-counts-807.json)。35 个 BMM 案例逐项 checksum 与 quiet-prefix 字段相符；只重聚合维度/路由，不再执行浮点模型。

路由按真实 `n≤4 ∨ p≤2` 分成 DirectSmall，其余 packed；空形状/零长度不计无用制备。

| 计分域一遍输入 | packed：25例 | direct：9例 |
|---|---:|---:|
| 输出数 / NaN终点 | 133574 / **493** | 434470 / **2367** |
| 全原输入非NaN的 eligible 输出 | **466** | **205** |
| 相比已有 quiet-stop 可省 mul+add 步数 | **1805** | **607** |
| eligible / rejected 扫描 word | 13364 / 685 | 1738 / 8848 |
| 当前扫描 word 合计 | **14049** | **10586** |
| 全部 A+B 输入 word 覆盖 | **1400104** | **1014213** |
| 行+列摘要槽位 | **60856** | **364893** |

direct 的正确 quiet-prefix 字段是原 JSON 中的 **607**，不是 617。以上每“步”是一组原序乘法后加法；它与读取/分类一个 word 不是同一成本单位，不能直接相减成时间。

raw 的 `bmm:check` 单独为 111 个 NaN/76 eligible、1100 步、4509 个扫描 word；不加入计分域。全部精确 per-case/分层数字和原件摘要保存在同名 JSON。

## 全量摘要先证伪，融合也不免费

独立 eager pass 的全覆盖规模，packed 是当前冷扫描 word 数的约 **99.7 倍**，direct 约 **95.8 倍**。这是覆盖量比较，不是减速比；每个行/列摘要可能在 rawNaN 处短路，不能声称每次必读全部 1400104 个 word。

即便考虑短路，packed 的 **21 个没有 NaN 终点的案例**本身就覆盖 1289869 个输入 word、54039 个槽位。非空矩阵的每个原 word 都参与输出；固定 NaN 传播模型下，这些案例没有 rawNaN，独立 eager 摘要会扫完整个范围，而现有代码在这些案例完全不扫描。direct 对应 6 例、987226 个 word、356030 个槽位。这已经是对独立全量预扫描的不利信号。

若把分类融合进已有 nativeA.map / packB，可省去第二次原始内存读取，但仍需给普通路径增加分类/归约、摘要存储及所有者传递。现有准备没有返回可复用的行/列 nonNaN flag；没有实际 C 证据证明新增工作可被免费消掉。

DirectSmall 没有 packed 的 nativeA-map/packB 制备。不能把 direct 新摘要成本塞进 packed 既有准备；其 n=1 部分还与另一个 singleton 组件重叠，未组合前不相加收益。

## 实际 row 结构与 Thunk 的能力边界

当前 [最终packed分流](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:4574) 是：

`bmm → bmmPackedBase → RowStream.core → RowOutput.row → Packed10.finish`

[RowStream](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:4529) 按行 flatMap：每行生成 rowTiles，再调用 [RowOutput.row](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-canonical-dot-scan/Kernel.lean:4440)；row 中的 `Vector.ofFn` 按 j 调用 finish。较早的 RowOutput.output/core 不是最后的 RowStream 运行入口，不能只在那里增加共享便宣称实际路线受益。当前精确 4792 全源没有 Thunk。

| 所有者位置 | 能共享什么 | 必须计入的成本 |
|---|---|---|
| row 的 per-j 函数外 | 同一 A 行可供该行多个 cold j 使用 | 若直接建 Thunk，普通行也先构造对象 |
| RowStream 行循环外、按 batch/column 保留 | B 列可跨不同行使用 | 需要表/捕获、生命周期和跨行实参传递 |
| 每个 dot 的 NaN 分支内部临时建 | 普通输出可不创建 | 若每次新建对象，就没有跨 dot 缓存 |

固定 Lean 4.34 commit `293d5d0c...` 的 [Thunk定义](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Core.lean#L118) 和 [真实runtime](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp#L540) 确认：**同一个对象**首次 get 会取走 closure、调用一次并写入 m_value，后续返回缓存。逻辑上的 get 是 fn()，方便证明结果等价，却不能证明不同回调实际拿到同一个堆对象。重新构造 Thunk.mk 不会自动得到跨 dot 的缓存。

W11 原头文件 SHA `982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13` 的 [1374—1403行](D:/CodingProject/Bitget/competitions/floatlib/research/astra-collab-20261023-r7/web/R7-W11/original-extracted/R7-W11/source/toolchain/include/lean/lean.h:1374) 显示 mk 与 pure 都调用 allocator；pure 只是已经有值，并不使对象免费。首次 force 还有 apply_1/原子交换，缓存 get 还有读取和引用处理。Bool 缓存值可用立即数，**不是每次 get 另分配一个 Bool**。

按 W11 ELF64 布局，Thunk struct 为 24B。若 packed 的 60856 个槽位都物化，该结构体请求量合计 **1460544B**，尚不含 closure/captures/引用表及分配器开销；这是跨案例一遍输入域的总请求量，非峰值 RSS、非已测新候选。493 个 cold 输出至多 force 986 个不同的行列槽，因此至少 **59870 个槽不会 force**。若编译器能下沉/消掉构造，需要真实调用上下文的 C/O3 来证明，当前没有这份证据。

正确性也不只是一条 `(Thunk.mk f).get = f ()` 的定义等价：需要 row flag true 推出实际 A 行所有读取非NaN、column flag true 推出实际 B 列所有读取非NaN，并精确绑定 batch/row/column/n/stride/default。还需把缓存所有者接入现有 row/tile/native-result 证明。canonical 算术闭包可复用，不必重新证明；这些结构接口和新全文件 gate 仍是新工作。

## 保留真实复用信号，限定重开条件

`bmm:extremes:2` 的 378 个输出全部为 NaN且eligible，形状为 1×14×15 乘 1×15×27。这里精确触及 14 行、27 列；理想一次性行列摘要只分类：

`14×15 + 27×15 = 615 words`

当前重复扫描为 11340 words，差 **10725**。所以共享在局部确有空间，不能声称机制完全无益；但这不是整套输入的时间收益，更不能据此添加按案例硬编码的 dispatch。其他案例的原记录只有 case 聚合，没有完整 cold 的 (batch,i,j) 集合，无法从聚合数编造全局 lazy 命中率。

**最小重开判别**是同真实 RowStream/RowOutput 上下文的代码生成检查：明确 Thunk 构造位置、B列所有者是否跨行、重复 cold get 是否持有同一个对象，以及普通行新增构造次数。若普通路径仍物化稠密缓存对象，继续 PARK，先不投入整套证明。后续已有独立诊断若能保留 cold 位置/scan stop，再据此计独立行列复用；无需再跑浮点搜索。

只有普通路径成本被实际界定、缓存复用存活，才值得考虑一份结构正确的整合；仍须精确源原版 fullgate、完整配对计时及冻结确认。本轮不生成 helper/candidate，也不声称已有 4792 的新 Lean/C/性能通过。

角色边界已另行回复协调者：本会话曾编写被 4792 复用的 scanner 组件；本报告是机会筛查，不冒充整个候选的作者独立审查。旧报告保持原样。

