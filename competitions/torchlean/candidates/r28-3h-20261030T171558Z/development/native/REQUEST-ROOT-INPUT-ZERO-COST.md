# 191300所需linear输入零项：单个NativeOnly完整原型就绪

候选 **29e71174/253816B**，2184B余量。`build_mixer36_input_zero_cost.py`（hash见READY/receipt），只依赖已冻结norm26 builder **fe05b956**；脚本按R28祖先定位，允许冻结到R28下batch子目录，原型字节不变。接口 `transform(raw36,36,"mixer36-input-zero-cost")`；基底raw36 595a90fa，无donor fetch。

保留已证norm26 **79615bd5**及原Ya3M/GEMM、所有原强路径。只对YaVM内一次rawzero probe发现零输入的调用，选择R28MD2InputZero：双零跳两row乘加和共享W读取；单零只更新另一row；无零原MD2完全保留。Bool只在每outputdot分发，dense MAC不加flag检查；不加cache/transpose/offset correction。尾row/异常/shape/sentinel/bias/round全部原样。

**仅NativeOnly，无correct/full_gate=false**：4个不再适用proof ZMVj/ZMVi/ZMV0/correct精确剪枝，runtime bounds所需lemma保留，无sorry/axiom/unsafe。staticpolicyPASS、双重重建相同、431原声明字节未动，只有MVj/MVi/YaVM改+2新runtime。`INPUT-ZERO-COST-STATIC-AUDIT.json`绑定。

已见旧18完整Mixer模型hash全匹配：第一linear0/6186零输入，因此全走原loop；ReLU后第二linear6187/12372零输入；原native paired274108乘法可省137559（双零36522term、单零64515term），probe总6211词，另16000任意UInt64状态恒等式。**计数非walltime**；两随机零分支可能mispredict/ifconvert，完整prepare/scan/branch/fallback/析构必须留计时。

Root若Mobile无跨线信号，可在已计划最后Norm26标准保留批带此**一个**核心成本原型；Mobile正则先全证明/新确认。无本方CI派发，不请求独立新CI。当前36完整profile支持linear43–62%，本源不带已测负pair/centered组件；若整体未达标直接保留负证据，不扩大同族变体。
