# R19 reviewed323 anchor：本地兼容性已验证

UTC 2026-10-26 19:53:26接手，20:03完成核心验证；预算30分钟。只写本目录，无Git/index/CI/网络/Lean重编译，主D的freeze/adopt和全局模型未改。资源token/计费UNKNOWN，新增CI占用0。

- [anchor](reviewed323-anchor.json) SHA `da251287655b84f502434fb6da4f2d3ffaa53fb08ae01e0124bc9a4765afa965`；payload `758dfe0452dd57590e0085d7ff386e81d3221080e5dfeeadd9b7b954c317abe4`。原`validate_anchor`原样PASS。
- [构造/验证脚本](build-reviewed-anchor.py)保留control41六份记录；完整71759字节frozen_records及六份candidate_total_ns/cell_work共13处JSON节点逐字节相等。只对旧309校准cell的submission_ns乘同suite官方323/309配对比值，再重算冠军投影/统计/身份。
- [验证回执](validation-receipt.json)：三组原B2配对回执、cell delta、六份samples、四项和whole均与原字节SHA `ab3be355546023e1e8c88a98830018cf3a72f5b238de6b86dd7c0603b296bfda` 精确相等；独立公式复算也相等。

| INFERRED时间比：B2/323 | add | mul | sum | bmm | whole |
|---|---:|---:|---:|---:|---:|
| 冻结三组重建 | 1.032570829 | 1.160098738 | 1.174665010 | 3.003226637 | 1.248723969 |

**wrapper可行，但不能直接用main刷新保留B2。** [草案](estimator-reviewed323-draft.py)的`load_estimator()`返回实际原模块并只覆写DEFAULT_ANCHOR，保留adopt对`save`的事务拦截语义；[实测](wrapper-validation.json)三个save都只进入内存、四个全局文件哈希不变。CLI强制`--dry-run`。原main读取当前十组B2会得whole `1.268407030330682`，属于重新拟合；不能替换冻结三组模型。R19现有adopt已认证冻结保留模型，新源仍走原select_pairs/estimate_from_anchor及完整原门槛。

**D的下一决定：** 若接入，在R19 freeze/adopt入口加载草案的`load_estimator()`，并将wrapper、新anchor和原estimator同时纳入新cohort的冻结/检查清单；不要替换已冻结cohort。此子任务没有改接入点，不能宣称R19端到端采用已通过。根project check及赛道集成自检由D集成后执行。

原始数据：[ab3b逐字节副本](retained-b2-model-ab3b.json)；109份原件路径/字节数/哈希及309→323 digest/suite/verifier链在anchor.provenance。`retained-b2-pair-records.json`是原公共索引中六行的冻结导出；其底层gate原件另外绑定哈希。[B2导出模型](b2-reconstructed.json)是计算结果。全局可变model/public-results只留观测来源，不放入frozen_files，避免未来新源因索引更新被误拒。

义务与范围：原始cross-suite/cross-hardware校准假设未消除；只采用官方323/309无量纲配对比值，没有用323绝对ns替换校准成本，也未重拟合B2。champion_classes其余incumbent_ns/ratio/spread字段保留旧309元数据，不能解释为323实测。官方323源码仍404；新同机测试NOT_RUN，直接对冠军比较及正式admission均UNKNOWN，以上只为INFERRED开发投影。样本范围不是置信区间。[保持性负测](preservation-rejections.json)确认绝对ns替换与control成本重拟合即使满足原schema内部一致性，仍会被本任务额外保持性检查拒绝。

复验（仓库根运行）：

```powershell
$p = 'competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-workers/anchor-323'
python -B "$p/build-reviewed-anchor.py" --verify-only --probe-original-main
python -B "$p/verify-wrapper.py"
python -B "$p/verify-preservation-rejections.py"
```

全部本目录产物哈希见[MANIFEST.json](MANIFEST.json)。`--verify-only`不会覆盖anchor/冻结副本；验证回执会更新本目录验证时间。
