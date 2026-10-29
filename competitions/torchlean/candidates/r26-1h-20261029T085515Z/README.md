# R26：overall 大优化，一小时

北京时间2026-10-29 **16:55:15—17:55:15**，一小时窗口完成；到期停止新增研究，已启动CI于17:59:57结束并完整回收。仅初始唤醒直接通知，之后全部文件交流。各角色晚加入的实际时段见[收尾记录](closeout.json)，不把窗口时长当作连续计算时长。

**取得完整模型提速证据，暂不替换保留版。** FP64快速路径、word64/128精确回退与共享卷积准备已接入12算子记录；原型仍缺完整正确性证明，小批量MLP还触发性能门槛。

| 同机配对项目 | 新原型／保留版耗时 | 速度提升 | 逐项性能门槛 |
| --- | ---: | ---: | --- |
| overall | 0.7854× | 1.27× | 未通过 |
| MLP | 1.1902× | 退化19.0% | 未通过 |
| ResNet | 0.4646× | **2.15×** | 通过 |
| MobileNet | 0.5845× | **1.71×** | 通过 |
| 归一化MLP | 1.1500× | 退化15.0% | 未通过 |
| Mixer | 0.8081× | 1.24× | 通过 |

两root seed 26102901/26102903、每seed6workload×30cells×5轮，共1800组配对、3600个耗时值，1800组checksum全部一致。原quick参数inner3/2ms；模型行从完整cohort按原scorer拆出，非另外的分榜作业。原型小批量MLP耗时2.99×保留版、归一化MLP1.98×，大批量MLP则0.474×；后续先区分准备/转置与每dot扫描开销，保留卷积收益。

[公共CI 40852769757](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/40852769757)绑定源提交`12e6d73f5775a753d8a82d4c2f731900a74c0043`，原型SHA `ad9bde3e9e8490df15f3d8d15c08805f85d4451e0a5f2d20977632c0b4b22540`，参照SHA `bcb8172381346b26afc69e2582442510865f74415c657d7ee208045474ca1ea7`。原MainExact字节、编译/链接参数、输入生成器与受保护原文件均核验；完整原gate只在保留参照上重放通过，新原型只作原生诊断，未提供新的Submission.correct。

[结果与重算](native-summary.json) · [完整字节/计时审核](verification/analysis-40852769757-final-root.json) · [原始回执索引](evidence/40852769757/original-artifact-hashes.json) · [冠军乘数看板](../../../../dashboard.md)

前两次CI分别因driver依赖导入和排队启动guard失误，在候选编译前失败；保留原件，不作为算法负结果。最后一轮只修同一已派发实验的环境/排队入口，候选和输入未变，未延长研究窗口。原定09:20首个native里程碑未达成，责任与时间消耗记入[closeout](closeout.json)。

数学侧保留真实producer/checker/dotSpec接口、word-block精确回退草稿，并以精确有理反例否定“RNE端点自动向外包围”的假设；本轮新证明尚无Lean接受。旧key/finite完整失败goal现已收齐：[CI反馈](CI-RESULTS-BATCH3.json)、[研究入口](research/HANDOFF.md)、[开发入口](development/native/HANDOFF.md)。R24 word循环此前已经标量化，本轮创新是完整模型接入与成本判别。

当前[计划](round-plan.json)、[开发状态](development-status.json)。正式提交、资金及重置均未执行。
