# 广域后继：状态载体投影接口，不增加manylane网格

冻结ec40仅是完整八列调用的机制探针。R19已见原完整pass归因记录中，p8的DC成本仅占whole0.594%；即使错误地把全部B2都算进p8，其合计上界也只有6.244%，所以此精确p8域不可能独自支持10%整包收益。任意列数、覆盖B2/DC/Packed10的三个路由总成本上界为14.920%；即便全部2倍加速也仅7.460%整包。出处和原字节hash见coverage-bound.json，都是已见输入/原始完整调用的上界，不是新速度或冠军比值。

**宽域必要变化**：k在外层，每次只解码一次A，再更新本行全部列。固定8/16/32标量网格会让更多累加器跨codec活跃，并增加多个版本的代码/证明；此窗不扩网格。新条件由representation角色提出：safe Array.modify先取出槽值、把槽写box0，再调用更新函数，可能使独占F2记录满足CtorReuse。这里不重复其实现或抢其源码归属。

`WideRowRefinement.lean.inc`给任意列数columns、任意步长p、任意状态类型S的条件接口：只需view(step k s)逐列等于原`view(s)+fa(k)*fb(k,j)`，且只要求有效k<n；generic storageLoop每列就等于NativeFinal.dotLoop。初值为+0，再用原Packed10.finish，原NaN回放/原字路径保持。没有实数交换律、精度放宽或跨输出总NaN标记。此片段**NOT_RUN**，hstep必须由实际状态更新实现证明，不能被当作已经证明该实现。

对Array<F2>可取`S={a : Array F2 // a.size=ceil(p/2)}`，view读取j/2记录的j%2字段，真实j取Fin p；长度证明是erased，不是额外运行字段。step只对每个pair修改一次，最后奇数列的幽灵lane不影响有效view，但其额外load/MAC必须计费。representation需要提供modify读回/其他槽不变、长度不变以及实际独占路径证据；本接口随后只做原序循环运输。对Packed10，可保留原10列分组的记录宽度作为同一接口实例，避免把每两MAC的槽更新成本机械推广到旧10列核心；这不是新增宽度实验队列。

**完整成本条件**：每行G个状态记录/一次数组初始化与清理；每k每group两次槽写、引用计数/独占检查、原生字段load/store、可能的闭包/apply。只有actual C/ASM证明无backedge新record分配且无Array复制，才能把它计为复用。相比旧Packed10，A解码次数本来已经是N，只能删全局A.map生命周期/重复A缓存读取；不能再报p倍decoder节省。相比DC，A解码最多从pN降N，B缓存准备/释放/填充另计。相比B2，A读取从ceil(p/2)N降N；B8准备的节省来自已有c70，不重复记为本次创新。

**明确spill判别**：ec40实际row/loop须看到每完整4k恰好4个A codec、八个scalar累加参数、无A缓存或逐k结果对象；把codec前后八累加器保存/加载、B组指针保存、terminal F8分配/释放计全。D已有terminal后继，本方不改ec40或再造terminal版本。广域state-array则应让acc字段在codec后才从记录加载、内层改完即写回，使跨codec活跃对象主要为数组/指针而非p个标量；若modify未内联或捕获A出现额外box/closure/copy，仍可吞掉收益。

另核已存在FloatArray出路：固定Lean4.34 FloatArray存Float64，Float32.toFloat与Float.toFloat32仍opaque；R17/M15已证明能靠逐值raw-word检查走checked storage。把它用于动态acc状态会把检查移到每MAC，不能当免费广域Float32状态容器，本窗不重开。真实来源为R17 structural-frontier/direction.md及其已固定原件；此项只是重访排除，没有新性能结论。
