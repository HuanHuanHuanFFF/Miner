# B2 缓存布局调查：不存在可直接删除的第二次全量 B 复制

2026-10-28，R22 A 只读历史短调查；被新的 word-carry 数学判别优先收束。恢复后首次可读时钟00:47:32 UTC；上一阶段精确切换时间UNKNOWN。没有新运行体、候选、Lean或CI。

**关闭“删一次全量 B transpose/copy”的当前前提。** 精确622d的`R15PackedB2.packB`直接从原始B的`b*n*p+2*g+k*p`位置解码并写F2；`output`只调用一次packB。不存在先整份nativeB map再转置到B2的第二层实际运行物化。证明中的`B.toArray.map`只是旧语义等式的右端，不能计入运行成本。401680实际C也确认public分派→output→一次packB→行折叠。原B必须保留给原NaN回放。

G=ceil(p/2)。实际一次调用准备batch*G*n个F2、2*batch*G*n次转换（包含奇列无效右字段），行循环每组每k原A转换一次，借读一个F2，最终每有效输出一次原finish。B2只在p2..8,n>1,m>=4分派；不能把它外推到所有BMM。删除B缓存会恢复每行B转换和跨列stride，无法把准备删除量直接当收益。平坦k-major B2若保持旧固定g的k循环，则增加地址步长G和可能缓存行浪费；R22 Pair8已经通过改为外k映射整个state测试另一种访问顺序，其完整whole未过门槛。

**逐batch准备/计算/释放也不是未实现的历史机制。** R11 `f01-d11-bmm-batch-local-output-proof2`，28af18b4ba270203a44e2cda950967a51475fc592d92b5f026f5bca43498a8e1，run40030638967/seed914的真实C：batchStep一次packBatch，本批m行完成后立刻dec；外batch累加器只保留输出和原输入，没有持有旧packed。原始C SHA1807cee367ddaabe255d6654ef392125847491a0b245287d7498c8f25ec7b9f3；详见`round7h-20261023T193125Z/review-batch-local-914.md`。full whole/a066=.982730039，BMM=.934766171；未有同seed精确fused-only对照，不能隔离batch寿命的边际效果。这个旧负/未过门槛范围保留，不能称所有batch局部方案已普遍否定。

R12–R20邻近路线的当前证据：R16 A4B2仍B2全量一次、每四行A-panel一次，完整whole1.00785021/BMM1.04343738；R19 temporal B8降低包对象/读次数而保持有效B解码数，Dual追加A缓存后whole.99818401/BMM.98576836；R20 rowbroadcast8仅证明探针，不能当完整成本。精确版本与证据见本目录`raw-a4-register-premise.md`及R19 `matrix-structure/cost-ledger.md`。R22 resident8仍一次全局Pair8缓存；resident16仍一次全局B4缓存和每四行A4面板，full探索whole>1，不能把已测寄存器表示重新包装成缓存删除。

**第一个未关闭前提仅是当前B2上batch局部寿命的实际收益，而非重复复制。** 本次有界搜索未定位这个精确B2迁移的同源完整对照；历史28af使用F10且有全局nativeA，不能充当该精确结果。迁移至B2不会减少总packet数、有效B decode或总写入；条件性请求量模型只把同时存活的packet+slot从约24*batch*G*n减为24*G*n（排除header/closure/allocator），并可能增加batch-1个外数组header及准备/释放边界。m行输出、全局原B、输出数组均保留。

若以后重开，最小判别先取已曝光的当前B2发现计划，核实际batch>1且本分支耗时足以影响整包；再确认actual caller的准备/释放、hot-loop指令不变，才比较同源全局/逐batch完整调用。必须包含prep、finish、NaN、尾列、RC，不能只测numeric loop。现无prep/cache-miss耗时占比，写UNKNOWN；不为这个未经成本支持的迁移造候选或新CI。当前优先转word-carry数学判别。
