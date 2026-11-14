# R21：一小时协作结果

窗口：北京时间2026-10-27 **18:35:38—19:35:38**。到点停止新增研究；末批已启动CI随后收齐。[时间／资源／原始账目](development-round-result.json)。D与研究R／3个Astra通过留言板推进，D统一Git和CI。

| 路线 | 本轮新增核验 | 决定 |
| --- | --- | --- |
| 完整终端BMM **7de57a41** | 关闭依赖count/两元素writer；9根及两模块通过。原版公开三源25轮全gate通过；对B2矩阵耗时 **−5.68%**、整包 **−0.85%**，p05 **−0.02486** | 未达原3%／正p05，保留B2；精确源停放，不换seed追分 |
| 任意p双行流式 **4e36c931** | 完整两行caller、原序lane、原finish/replay/长度；两模块及 **19根通过**，C/ASM已收 | 下一步先测完整调用成本，再做全batch/奇尾公共接线；不声称无分配或提速 |
| 同宽缩放乘法组件 **29d09f90** | 原B2公共入口保留，运行组件8根通过（含4定义），真实C/ASM已收 | 仅成本组件，未证明新public MUL |
| 缩放数学桥 **56cdb076** | 两模块及15根通过，其中 **7条实质桥接引理**：精确Float32缩放、U32逆转换与字段 | 补实际UInt64 product解码和原guard/spec；先确认成本前提，不直接铺昂贵全证明 |
| 反例／覆盖 | 跨batch错误配对反例：应44却28；原幂次因子稀少，D按当前固定生成器再核10752位置命中143 | 下一公共矩阵按batch内配对，奇尾fallback；低覆盖独立机制不造全候选 |

**结果：尚不能取代冠军，继续保留B2／正式#336。** 交付前官方只读复核仍冠军#323、我方第13，原正式整包耗时 **1.6287×**；不把新公开D换算为新的私有官方成绩。

- [真实完整D](development-result-40493865047-f01-r21-dev-terminal-dc4.json)、[不采用决定](development-fullD-decision.md)、[public caller路径](development-public-caller/audit.json)。
- [末批原始19／8／15根](development-final-probe-roots.json)、[已启动CI账目](development-jobs.json)、[原生输出](development-final-codegen/audit.json)。6批全部终态逐hash回收，未改原gate或预算。
- [研究最终交接](research/HANDOFF.md)、[跨批配对反例](research/pair-batch-boundary-counterexample.json)、[最新官方只读复核](development-official-close.json)。研究R接入后58分37秒至共同截止，晚接入未延期。

后续优先完整2row成本（含firstsweep共享Cell、slot写、RC/COW、closure、最终输出与释放）；同宽标量接口只支持已证明的decode条件，不能继承成全输入MUL。未运行后继稿保留NOT_RUN，历史失败和原件保持原字节。本机Lean0、新正式上传0、资金动作0，真实token与分路线共享CI成本UNKNOWN。
