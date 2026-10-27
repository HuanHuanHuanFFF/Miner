# 真正public MUL接线副本

**Kernel.lean：255700B，SHA176c70cbd602082c3c4727234487605c1c4945eb808180cac82230d74ebb3831，余300B。** D可直接复制；原365、9be和所有D文件未改。本源NOT_COMPILED，不能继承数学探针的四入口或早期接口通过状态。

原365中98处完整Submission标识符统一改到原源不存在的R18，精确逆向替换还原365全部字节，节省686B；追加825B public导出，无新增证明裁剪。映射和字节偏移在manifest.json。

- 真正Submission.mul调用R18.R17NumericMulInteger.guardedMul **R18.mul**。旧R18.mul仍为原B2 LowScale/native实现，全部旧body中已无Submission标识符，不可能经旧名回调新public。
- 新Submission.mul_spec明确使用R18.R18NumericMulSpec.guardedMul_spec **R18.mul R18.mul_spec**，目标是新mul的原全输入规格；没有以旧spec同名冒充接线。
- add/sum/bmm分别inline转到R18原实现，sum保留原隐式n；未改原计算体。wrapper/namespace变化的实际C和完整四项表现仍需真实gate。

原固定intake/policy/options（含注释）、单import、整体容量及LF预检PASS。HelperAudit.lean.inc已将63个附录根同步改到R18；四个最终Submission规格由原gate核验。旧C/helper选择器若硬编码Submission.R17NumericMulInteger，应按此实际源改用R18.R17NumericMulInteger；最终以MainFull选择的public MUL回调为准。

首个实际编译错误到来后只修本精确源对应目标，另写新版本；不再另开只测数学、却不改public入口的性能任务。无本机Lean、CI、Git或模型重跑。
