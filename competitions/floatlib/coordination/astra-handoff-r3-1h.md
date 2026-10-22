# R3：一小时协作续跑

用户新要求“开始新一轮 协作推进1h”。共同窗口2026-10-22 04:36:27—05:36:27 UTC（北京时间12:36:27—13:36:27），准备/等待/修复/验证均计入；已启动实验和CI完整跑完并回收，不取消。原十小时提前收尾是D串用历史半小时消息的错误，不能继承该误判。

沿用现有R会话01a15e06-b75c-7811-b0a0-194d8877365d，Astra/xhigh；R只写research/astra-collab-20261022-r3/及candidates/f01-r3-*，D只写f01-d3-*、总状态、看板，独占Git/CI。旧R2原稿及原始回执保持不动。普通交接走文件，自然检查点读取，不派新Codex会话/子agent。已授权网页研究可用，先回收已有W03b，不以网页任务等待阻塞直接研究。

当前主问题：Packed4 bb1f783f完整gate通过，但bmm约1.45ns/MAC，仍远落后冠军。真实生成C有4个unboxed float累加器、循环无ofBits或每步构造，但仍有Nat k/baseA运算和A bounds。请优先从这个精确版本建立新的USize/证明uget循环，保持4lane各自原k顺序，异常与尾列回退不变。参考full-passed f01-d2-preconverted-usize e87603f9 的独立机器字循环与等价桥；可证明新循环等于旧dot4后接旧lane证明，避免重写整个数学证明。不同版本分目录，先交付完整source+SHA+manifest，D立即做statement反馈，只有实际通过者进完整gate。

D正准备word标量prefix与Packed4 suffix组合及Packed4冻结确认，请不要重复组合。D另将已有W01c完整重构证明和W04单遍FloatArray准备做最小statement摸底；R可在实际错误反馈后承接一个关键证明修复，优先不扩大待测积压。请在约05:00 UTC前给出首份可检验稿，05:15前给最终拟确认版本；预算包含返工与完整验收。若USize路线成本不合算，基于具体新证据给出另一条有实质差别的矩阵优化，而非重复旧fold或无新条件的微调。

固定Lean4.34/FloatLib/pins、官方contract/gate/bench不变；只有ContractTensor导入，四函数全输入逐位，三允许公理；保持原归属与许可。重型工具链仅临时Linux免费公共标准runner；R不Git/CI/注册/签名/钱包/正式上传。研究状态唯一入口research/astra-collab-20261022-r3/research-status.json，完整候选/阶段错误/生成C/计时分别标明，不能继承父版通过。
