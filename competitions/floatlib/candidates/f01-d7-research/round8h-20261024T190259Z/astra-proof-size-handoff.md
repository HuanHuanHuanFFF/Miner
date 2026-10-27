# R14：证明字节余量调查，未改开发源码

时间：2026-10-25T00:35Z。针对新 add 数学片段可能超过 combined-slim1 剩余12579B，做了独立只读调查。

`astra-proof-size-audit.py/.json` 对精确 6f8808d0 和 d94060b2，各定位 **42 个无属性、叶名称只出现一次的 theorem/lemma 区段，共12870B**。两源清单相同；未发现 exact?/apply?/aesop/grind/simp? 环境搜索 tactic。跳过所有有属性的声明及其附近20行、公开 add/mul/sum/bmm 义务名称；没有删除定义、证明或运行体。

较大项包括 round_normal_decode 1256B区段、finiteRoundtrip815、add_finite_inputs636、mul_finite_inputs555、repairDotStep_isQNaN551、modelDotEarly_eq501。JSON保留精确源SHA、起止、区段SHA，**区段可含邻近注释，实际删除应保留版权/作者及必要注释**。这是词法机会清单，尚未Lean解析/编译，不能宣称安全完成或机器码相同。若采用，由开发在新版本中先集成实际 add 证明、再按新源重算引用，避免删掉新桥正要引用的旧 helper；原候选不改。

首版审计重复逐声明扫描耗时越过3秒上限，已保留 failed-v1 原件/失败记录；改为单次token计数与边界索引后约0.038秒完成。没有本机Lean或重任务。

数学补充仍保持优先：00:08/00:12/00:17的对齐、小移位、log2、完整E、carry/fraction、公开Model.add桥全部NOT_COMPILED。另在astra文件中保留通用正位移RNE推导及远指数吸收的备选数学草稿；这些**不加入当前候选/CI队列，不替代你当前add集成方向**。我继续核对纸面边界，Git/index/CI仍由开发协调。

目录：`D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/`。
