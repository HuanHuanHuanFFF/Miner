# FP成本判别（R主控自有实验）

旧R26实际生成C确认sumRemaining为double scalar尾循环，函数内无直接Float boxing/ctor；prepare无条件同时建FP与word两缓存。不是热loop装箱假说，真实占比UNKNOWN。

`certificate_census.py`复刻exact旧widen/proposal/strict checker，仅读R26已见normal/sparse首层160夹具。78/80、76/80接受，所有accepted经原act true后与fixture一致；不代表部署概率、后层/wide/scale/boundary或Lean执行。最初误把夹具看作未ReLU输出，失败与修正保留failure1。

`LazyFPOnly.lean`6656B/7cc98e2b为自写直接getter→FP-only cache，去掉临时raw slice与eager word cache；checker/sum来自项目自有R26，FastMul.log2换直接Nat.log2，不能继承旧source全部证明。miss才调用原12 YaU/Yc精确word单dot，metadata扫描也算miss成本。

`patch_fp_only.py`0ed4ccc9重建原12+本helper，candidate afea5f33/225382B；只覆盖dense.linear，其他11项保留。原correct已重命名retainedCorrect且只绑定retainedKernels，新kernels无correct，明确UNPROVED_NATIVE_ONLY、不准入。原AST intake/policy通过，Lean/native/速度均NOTRUN。整源只在private/，公开ownpatch/receipt。

P1一次成本请求见CI-REQUEST.json。优先正在进行的完整norm gate与确认，不修改其冻结源；同board12控制可方便复用，但现任23/source private且配置未归约，冠军倍数UNKNOWN。先成本再新prep/矩阵证明；初始helper需要实际compile，不做同实现重复测试。

22:25追加无现场网站源码依赖版本：owned-only/Kernel.lean49182B/ade9cf63，仅公开项目bcb817+ownThinFP，actual全12record，ownedControlCorrect只证旧control，新correct明确无。ASTpolicyPASS，未elaborate/native。fallback换已证明dotFn，以MLP目标避开norm证明体积，但MLP冠军33更快、尤其batch1guard不能假定可过。只有correctness-only/standalone时current倍数UNKNOWN，绝不重启originalshipped性能pair；若有缓存12，可用正确33→13→12报告链。精确最小请求OWNED-SOURCE-REQUEST.json。

22:47接续3.5h至02:12:53。A静态log2word缺绑定已由父最小复现并修：helper1762a473/6739B，base12 carrierf3e55a34/225465B，source-independent owned863ad0b2/49265B，AST intake/policy均PASS。旧源/请求/recipe完整保存history/pre-log2-binding，旧privatecarrier另留v1。无Lean/native结果，仍无新correct；不要把静态修复当编译通过。只选一条成本探针，不挤强public23主路线。

22:57当前唯一P1请求升级003：公开退任23强norm底座+C的proof-only alias（冻结hash4c3dd）+同语义minimalFP5052B/92cebe2d；最终253720B/6a134c5f，余2280B，b1走原23linear、b8走FP。静态policyPASS，未Lean/native，无新correct。原001/002 hold，owned863ad仅网站不可用时的编译fallback；不把三种源都排队。两网页Pro已responding，分别归一化新机制和FP producer误差，不阻塞A/B/C。
