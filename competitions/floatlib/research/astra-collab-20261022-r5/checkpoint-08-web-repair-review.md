# R5-08：网页桥实际失败已定位，D修复版已独立审阅

607/run39766391628原c09e网页完整候选的statement确实失败，不能继续标成仅未运行。原ZIP、完整源码和full-build-output.txt均保留；其余指数toNat与allOnes桥没有报告错误。

两个具体失败点：

1. unpack展开后仍有嵌套let；原split_ifs只分解了右侧的if，左侧没有先进行let规约，rfl不能按上下文假设归约这些条件。
2. 原isFinite_eq_finiteBits的宽simp把BitVec全一常量及Bool比较改写后，留下decide/取反等式；he与h没有匹配到改写后的目标。它不是浮点反例，也没有表明全域命题不可证。

R在核对错误时，D已创建`f01-d5-finitebits-proof1`，SHA `c3aa5d16e32cf8a05cab9677c4ac297cc72019cf21037ae43069c87b8b7b1b86`，136123bytes。R逐项审阅了新证明：unpack后加dsimp only消去let；分类器显式写成UInt32等于255的if；证明按he/hw分别用if_pos/if_neg，避免宽simp改变目标。该修复正对实际错误，仍保持一次toBits、指数分类和原raw fallback。R不另建重复修复候选或改D文件。

修复版当前仍须自己的真实statement结果，随后组合版须完整gate/公理审计/计时，不能继承原c09的未编译推测。标准UInt32相等的实际生成代码也需核对，不能仅凭源码形式声称变快。

607的流式+打包组合8eb63a2f已完整PASS，但bmm候选spread约1.81—1.85，本批不能靠三个最小值宣称稳定提升。D已启动608对ba93、stream-pack和rows-pack同批比较，后续独立确认由D继续。

阶段诊断607虽checksum_matches_control=true，但三个measurement的calls均为0，阶段纳秒也全部0。这是探针未覆盖实际调用的无效观测，不能解释为准备/输出免费，不能据此算占比。R已按原件保留UNKNOWN，不把诊断脚本执行成功当作有效测量。
