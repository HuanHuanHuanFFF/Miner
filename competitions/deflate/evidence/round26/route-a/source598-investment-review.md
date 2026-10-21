# #598 静态对照：没有新增结构消费点，不跑整包原生

绑定公开读取快照29808，原作者 `5C5jh8db6s5cFMog7H2bnEeYkp28qTRs6xJ46GrdCchXgWC6`。Rust `c859a7f6ee69f38e3e0f54f8389c2f5886f8997beb38bc51208b9933f6b0d9df`，Lean `e1cedbfcdba092b6840b45ebc38f4b6757e1333d164031d1a1adf31782e48d83`；523481B，仅807B余量。来源文件未修改。

与641同名函数171个，其中155个去空白/注释body相同，共同常量没有值差异。变动中12项为路由wrapper，核心只剩三处近距离拒绝差异（A7已经测过）和BFRAW最低距离1对257。绝大部分PC入口只是无lazy/较小有效hash对641的lazy/不同配置。`pim_f_record3`和`pim_run1c`前缀替换后与同份PC函数body逐字规范化相同，不是新匹配器。

更近先例是已取得的public584：186个同名函数中181个相同。只有三条PC wrapper从17位hash/lazy258换为15位/lazy0，DX1一处参数6→4，tiny入口换为已知ET tiny。新增17个ET helper在641已存在同body；不是新的分词/查找机制。因此598的整份正式坐标较快不能归因于发现了免费删除的模块，更不能按文件挑拼595/641输出。

与595的差别确实更大：OA/DX1、重路由和旧/新tiny等。但这些核心在641/584及之前各轮已有，对595的单独新增能力并不是本轮新发现。静态对照结果及逐函数diff见 `source598-static-comparison.json`、`source598-prior584-comparison.json`、三个source598-vs*.diff。

决定：不为598整包跑新native/配对，也不迁移它的一串路由参数。公共28实际输出与本轮paired时间仍UNKNOWN，没有将静态文本相同当全输入语义等价。若有新消费域证据，可以再讨论具体独立机制；这次读取已足以排除“另一个明显不同的快速主内核”的假设。

同时排重：PC正常链按gain过滤更长match的设想已在R14/R15/R20直接实施；不能再次把`pc_gain(m,d2)>pc_gain(l,d)`当新方向。相邻forward-fold则由当前PC最大匹配域排除，另文保存。下一项只评估主线程提出的同head/prev、同候选次序的packed-head额外tag，尚未生成候选或启动CI。

VERIFIED：源码身份、函数/常量静态对照、直接旧机制定义。INFERRED：无足够新结构差异支持整包重跑。UNKNOWN：598本轮真实路由/质量/时间与任何目标份额。
