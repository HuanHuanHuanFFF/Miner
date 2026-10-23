未发现确定静态错误。精确候选d70ebe881ce9c9cd48e83eb02b71b41f50340746717e8b461c6da65e766ed791，236880B；父41bce485…235169B。本人不是此候选/builder作者；没有执行builder、Lean、Git、CI、网络或查看842/843输入，只新增本报告两文件。

独立diff只有三处：5222–5263插入1681B NativeFinal helper/proof；6117将DirectSmall.dot改为dotSmall（+5B）；6127多一条dotSmall_eq桥（+25B）。逆向逐hunk恢复父41完整字节，净增1711B，距256000B尚余19120B。scalar、所有sum、packed、NaN replay和原NativeFinal.dotLoop/dot/dot_eq字节保留；不是把共享dotLoop替换掉。

smallStep:5223–5226与原dotLoop单步相同：acc + toFloat32(A.getD(baseA+k)posZero) * toFloat32(B.getD(baseB+k*p)posZero)。+和*优先级维持先乘后加，无重排/FMA或flag变化。smallLoop:5228–5238从Float32.ofBits0开始：0不读数组；1为F0(z)，2为F1(F0(z))，3为F2(F1(F0(z)))，4为F3(F2(F1(F0(z))))。实际源码分支的outer→inner索引独立提取为[]/[0]/[1,0]/[2,1,0]/[3,2,1,0]，对应原0..n−1左fold；这只是结构核对，不冒充浮点执行或Lean证明。

n1仍做+0+(a*b)，没有把原初始add省成raw乘积，因此保留原负零规则。地址、getD默认值、全部输入类型相同；n0即使有正输出数也不读取A/B。batch/m/p为空时原Vector.ofFn回调不运行。dotSmall:5254–5257只换result生成器，native非NaN导入与NaN时以原A/B调用replayEarly完全同原dot；sNaN/qNaN payload、invalid和优先级仍由原raw回放负责。n≥5默认直接原dotLoop n …0z，不新增USize截断，巨大Nat/越界getD行为保持；p≤2的长点积也走这个默认。它仍新增外层match/wrapper，不能宣称回退性能零变化。

smallLoop_eq:5240–5252用五次Nat构造分解覆盖0/1/2/3/4和剩余succ⁵ n。常量分支simp展开至多4个原dotLoop步骤及常量比较，末分支就是原loop调用的rfl；smallLoop/smallStep/dotSmall本身不递归，没有新增termination义务。dotSmall_eq:5259–5262 unfold两个wrapper后改写smallLoop_eq，同一let/if及两个分支应恢复原dot；没有新finite前提。DirectSmall.core_eq_reference:6127先改写dotSmall_eq再沿用原dot_eq和全部地址桥。没有识别到具体坏名字/类型/终止目标，但精确新源的simp方程展开及rw类型仍须实际statement裁决，不能据静态形态报Lean通过。

原NativeFinal既有4097B前缀完全不变；packed证明依赖的dotLoop和dot没有变化，因此没有重现D9修改共享dotLoop而牵连Packed10.dot10_lane的机制。新lemma未标simp，也未改全局instance/option。独立原4b7静态policy检查PASS，仅原ContractTensor import，无新options，helper五个声明各唯一，许可保留。build.py被只读检查而未导入；其容量assert在写文件之后，但当前实际字节合规，不是当前阻断。

新Lean/fullgate/C/asm/性能均NOT_RUN_BY_REVIEWER。首个判别是精确源原版statement确认new helper及全部共享证明，再按完整gate和同runner41比较。机器码是否真正展开、地址是否简化、n≥5薄矩阵是否因额外match受损均UNKNOWN；不把源级少循环换成收益承诺，所有慢/失败组应保留并遵守本轮三组冻结规则。交付前Kernel复核仍同一d70ebe…。
