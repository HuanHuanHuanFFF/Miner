# 后继准备融合：直接构造第一步状态，保留首个+0

与冻结v1/v2独立；没有新Kernel或CI请求。`SeedFirst.lean.inc`3283B/SHAae1bdea0837ecc43b167d72479b802ad82148928f54b63a17ae8dd3efc0b94ba给普通Vector.ofFn seeder、逐列等式、首步loop等式及完整seededRows→streamedRows证明尝试，全部NOT_RUN。v2仅修emit_size，不改变本片段依赖的运行定义；仍需实际组合验收，不能继承v2状态。

当前v2先构造replicate p的共享zero Cell状态，再做第一遍mapIdx；固定后端逐槽清洞/写回，首次往往需新Cell。新条件是把初态填充与第0项算术合并：若n>0，先解码A0/A1，再逐列构造`⟨+0+a0*b,+0+a1*b⟩`，从k=1继续同一个专用loop。p0仍直接返回out，n0走原controlRows；其余finish/rawNaN回放和row-major输出不变。

**不是删除初始p个Cell分配。** 两种方案正常都要一个p槽状态Array，随后p个独立结果Cell。融合只提出删除共享零状态的一遍填槽及第一map的清洞/读旧Cell等工作；Vector.ofFn自身的Array构造、Cell分配、循环/closure和RC也必须计入。实际机器store、CtorReuse、是否共享或新造的数量均待C；没有“少一个Array分配”的证据。

首加法不可偷删：`a=-0,b=+1`时，原`+0+(a*b)`为+0，而仅存乘积为-0。model-check.json保存这一个精确signed-zero主机见证，未用它充当任意Float32 oracle。35组符号运算树检查覆盖n0/1/2/3/5及p0/1/2/3/5/9/17，原独立dot、map状态及seed状态的每输出mul/add树和row0后row1的finish标签完全一致；非Lean证明/非性能。

最小后续判别：只在冻结state实际C已验后，核原first sweep究竟是否有额外zero填槽/清洞工作，再检查seeder是否换来了额外closure或更差寄存器活跃度。若原first成本已消掉，不开此候选；若仍存在且占比可观，才对包含n0、首k、steady、finalize的完整路径验证。没有设置新域阈值，不以源操作数推速度，不修改冻结4e36或5bbf。
