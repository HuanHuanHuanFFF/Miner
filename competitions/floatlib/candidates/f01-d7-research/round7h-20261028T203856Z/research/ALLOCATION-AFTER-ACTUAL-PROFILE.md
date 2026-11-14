# R24投入调整：使用优化参照的真实层成本

证据入口：D的`development-reference-first-result.json`，run40786223288，源c839fd40，upstream accb82b6，former2 SHA cea4422f。22原件135697B；原始summary SHA4a25e183。R重核结果文件SHA8be91f6f。只是一台AMD EPYC7763、CPU0、五个normal/batch1、model42/input7、原profile best5观察；层时间包含hash/touch/ownership。没有新candidate、独立回放／公理审计、打印checksum、新#5源码、其他profile/hardware或正式成绩。

| 优化参照former2 | dot关联整层占比 | normalization整层占比 |
|---|---:|---:|
| nmlp | 93.39% | 6.20% |
| mixer | 70.26% | 26.08% |
| mlp | 99.79% | 0%（此原profile无norm层） |
| mnet | 65.92% | 0%（此原profile无norm层） |
| cnn | 77.25% | 0%（此原profile无norm层） |

零表示该观察确无对应层，不表示所有形状／协议无归一化成本。shipped中nmlp约38%、mixer约70%的norm占比不能移到已优化参照。整层含观察器，不能直接把它叫纯内核成本。

这一新证据把主要投入移向跨linear／gemm／conv的dot核心。B的商/RNE/normal-word组件保留，RMS/LN独立候选和den-guard扩大降为副线；D原有scaled-word工作保留。B下一项改接主线的strict midpoint→实际binary32 rounder语义，不假定规范化den可放入64bit。原始LN P95/D30可能需72bit规范化den，不能以num<128推D64证书覆盖。

主线保留两种实质不同机制：

1. native64精确产品＋近似累加＋可验证RNE32 cell。widen/MUL/fold及实际dot组合已成源，完整成本、fallback、raw32 cell／读取循环和真实编译仍须闭合；List.map proof probe不作高性能实现。廉价midpoint证书仅删除两个软件端点rounder，不自动胜过exact128。
2. exact fixed-word路径减少串行依赖、carry或wide状态成本。已有pair/partition整数界、S−c延迟修正和tiny-bias基准限制保留。conv已有双链不能重标为创新，2／4链的寄存器压力、实际caller和代码生成均UNKNOWN；后续只在具体新helper或判别证据上投入，避免重写旧数学审查。

接下来计划从初配60/20/15/5调整为：**50%两条高上限路线探索、30%实际实现／证明、15%关键反证／审核、5%协调**。理由是已买到优化参照的热点证据，前置源可组合，真实Lean／checker接口成为下一关键未知。两路线中的第二条至少保留一个独立检查点，不因第一条较易写证明就排空替代方案。实际token、缓存、reasoning/output拆分UNKNOWN，不把计划百分比写成实测消耗。

当前验证吞吐由D一个在途CI控制。D已将六parent片段／193个唯一声明合进95,124B的portable-island2、36 roots，run40788628582在途。**只有精确island2可获得此次验收**，六个原parent Kernel仍NOT_RUN；不继承不同完整源码的PASS。R当前停止增加同类候选，优先处理真实typing，再按实际结果组合。不能为了缩短研究时间改官方contract/gate/pins或省略最终回放／axiom checks。

Pro新版给当前半径的必要条件H+2L−E≤278，故H+2L≥406时所有normal proposal必拒。R独立核过cell-width推导。A正在按公开fixture源核可达性：初步所有公开有限激活/权重界与fanin给H+2L≤401，故这个硬条件没有淘汰公开shape；不等于实际命中、hidden范围或速度。只限制当前误差界，不排除更紧半径／bias分离的native64路线。

共同截止03:38:56不变，03:15后不新增长作业。迁移目标选择仍待用户已有问题的答复；当前研究为旧ContractTensor可复用数学及只读源／成本观察，不擅自当作新12kernel开发或正式参赛。
