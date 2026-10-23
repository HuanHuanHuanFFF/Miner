精确候选 `1b71f67ee1cb154399e60a0657618c4b968d8e4b4d642cfc0621fdf416811792`，244998 B；相对256000 B上限余11002 B。本次未发现确定静态阻断，发现一处应由首轮statement裁决的具体GetElem边界桥接风险。新Lean、完整gate、代码生成及性能均NOT_RUN/UNKNOWN。审查者没有编写本次RowStream块或builder，曾审查继承源。

独立按namespace起止锚点逆变换得到精确a066父本（237142 B，SHA `a06608bdc419d4647af301bfdd617d52e4796c404661a28672a022eef4a10b78`）。候选5999—6210行替换父本5999—6038行；前后字节完全相同，辅助块与Kernel实际段完全一致。标量、sum、DirectRows/DirectSmall、最终bmm/spec、原F10 MAC、解码、NaN回放和许可归属文字均保留。固定4b7原policy/options函数及常量的纯文本检查PASS，未运行gate阶段；无新增import/options/export接线。

[运行块](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d11-bmm-fused-output/Kernel.lean:6083)在每个group的lane闭包外绑定一次runDot（6091），read闭包共享result；emit以Fin.foldl按lane递增push（6044），内层按group递增（6140），外层按r递增（6165）。初始Array.mkEmpty容量是batch*m*p，构造Vector只附最终长度证明（6183）。在改变的实际路线n>4、p>2、非空输出上，source层组数仍为batch*m*ceil(p/10)，没有减少点积调用；删除的是旧行号Vector、rowTiles、行输出Vector和flatMap。nativeA映射与整个packedB准备保持。逐group finish移到下一group runDot之前，跨输出调度改变，每个输出内部仍是原k顺序mul再add。

前缀不变式同时约束size=k和每个已写元素=point(j)，不是只证长度。prefix_push分旧索引和新增末位；emit推进k+count。decode_row证明q=r*p+j对应(r/m,r%m,j)，point_row用Nat.div_add_mod'还原A地址r*n。group入口r*p+min(10*g,p)，出口r*p+min(10*(g+1),p)，写入数min(10,p-10*g)；再以row_prefix/output_prefix递推到batch*m*p。实际finish_dot10_lane、packB_lane、runDot_eq及index_address签名均对齐；原finish使用同一Araw/Braw和baseA=r*n、baseB=(r/m)*n*p+j，原NaN精确回放没有被改成原生NaN结果。新helper均在Submission.RowStream闭合，随后原bmmPackedBase_spec仍引用同名core_eq，未见前向引用或新增重名导出。

具体编译风险位于[6191行](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d11-bmm-fused-output/Kernel.lean:6191)：`change (output ...)[q] = _`需要先完成q<output.size的GetElem边界。局部hq仅给q<batch*m*p，output_prefix不是simp定理；显式长度转换在下一条rw的证明中才出现。自动elaboration可能先在change处失败，尚无Lean运行，不能列为确定错误。若实际报该目标，最小修复是先have hqo : q < (output ...).size，由output_prefix.1改写后exact hq，再change或显式给GetElem证明。其余新fold终止/依赖索引目标在静态上自洽，不能据此称已编译。

空输出及n=0的原dispatcher/direct/reference路径逐字未变；独立新core的零rows/groups也有空前缀基例。尾group只finish/push有效lane，原填零无效lane仍可计算，不能混入输出。新循环无USize收窄，原runDot机器界限与Nat后备保持；巨大Nat只核数学地址/计数，未执行巨大分配。±0、次正规、Inf和NaN的种子、更新及原字回放都复用原路径。实现者1548形状/203175位置/12大Nat点的JSON只被读取，不继承为Lean、浮点checksum或性能结果。

运行时仍需区分源级共享与RC实际共享。out只作为当前fold累积器传递；step/read闭包未捕获旧out，没有看到显式保留历史Array的结构。但Lean原件明确push仅在引用唯一时原地修改；Fin.foldl特化、闭包捕获F10、retain/release和容量分配是否如预期，须看精确生成C/IR/机器码。`let result`一次不等于已证明机器码只有一次调用，Array.mkEmpty不等于零复制。最小后续是首statement接受后检查实际RowStream/Fin.foldl特化与lean_array_push所有权，再比较整cell配对完整gate；观察器结果与冻结确认分开，不能把分配数或C大小变成收益。

调度注意：manifest的validation_mode是说明性长字符串。R11 prepare-plan从显式--statement-only生成nested entry，public-suite只验证entry，因此该路径可用；直接run-gates按manifest精确等于statement-only判断，会走完整gate。首轮必须冻结nested entry为statement-only，不能仅依据manifest文字。无需为本报告改候选。

本报告只写两份review工件；未运行builder、layout写脚本、Lean、Git、CI、上传或新agent。完整原件SHA和精确行指针见同名JSON。下一判别点是冻结1b71的statement，随后才是精确代码生成和完整成本验证；不增加通用测试框架。
