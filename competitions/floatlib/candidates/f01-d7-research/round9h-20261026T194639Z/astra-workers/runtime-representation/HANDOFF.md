# R19 runtime representation 当前交接

2026-10-27 02:21 UTC最终窄验收更新；只写本worker，D唯一Git/index/CI。R按用户新续窗22:58:21Z—02:28:21Z执行，D原窗不擅改；后续成本细审交D独立预算，无本机Lean、无嵌套。

- **7737实际成本已核，暂停直接做大publicADD桥**：`grs-codegen-40430974047/HANDOFF.md`。CI404309/f421成功statement/两重放/7根；实际diagnostic非零路1cast+非尾toBits，但6保存/24Bframe及两热栈写供postE失败恢复原输入，同期B2 selectedADD3保存/16B及tailcodec。排序/jam/zero/miss共11完整代表路径已绑定，public仍B2，新时间UNKNOWN；audit8f248d8a…。
- **pre-guard d3c定义接受、完整路径诊断负**：`grs-pre-guard-frontier/HANDOFF.md`、`accepted-40435830288.json`。CI15 40435830288/5ad212c8，228686B/d3c550da05a3e91b5b037bed77623545dbe72af385d826ebc73236d2ed7ec2b5 statement+两模块+7根PASS；7根为4旧B2spec+3新defs，非新ADD等价。CI16原件02:20到，4对照块ADD1.483944–1.505067、诊断组合总时1.175671–1.204368，checksum同；caller为独立noinline arity2/0capture选中ADD入口，其他3回调B2。非原25round/fullgate；细C/ASM交D独立预算，不推进采用，不重hash全批。源/硬界/旧7737 6save/2spill均保留。最短CI16结果见该目录ci16-short-result-40436948264.json。

- **GRS类型失败历史保留**：CI404283/3534的HAnd UInt32 Nat已由唯一+11B mask类型标注修订为7737；CI404309已真实接受其statement/两重放/7根，详最新代码审核。`grs-add-type-repair1/`保留当时NOT_RUN回执和精确逆patch，原e483/3534失败源未改；不是算法反例。

- **GRS三已见R15组投入阈值完成**：`grs-add-threegroup-threshold/HANDOFF.md`。保持256点/case：新9754/9389/10258对旧6056/5400/5863。旧cell cost×work加权命中率代理F31.781%–35.039%；零miss新增成本时10%whole需eligible省28.540%–31.465%（约1.40–1.46×）。生成器未独立Lean对齐，非计时/非严格上界，missguard未知；先收3534真实caller，不挤占DirectBias。results SHA f8f73003eb9fe582927e23fa322177463f45b3a75e57d984e3a8ad463bd4bc08。
- **ROI范围更新**：根转述D板003834部分scope，第一计划B2路径约5.65%whole，其他路径不变的Dual/B2-only该样本理想空间≤此值；第二计划超时、collection不完整、析构待审，不是永久上界。本方未读新输入/重测；scalarMUL+广ADD主攻，矩阵只收已有trace/证明，详该目录root-scope-addendum.json。

- **DirectBias完整出口review1静态审查完成**：`direct-bias-proof-interface-review/HANDOFF.md`。当前255311B/fa6529，余689B；原79e8基础+42B证明定位修订，逆恢复/冻结运行/48根一致。44新theorem+4public静态存在，本地guard/product/scale补R14依赖；旧B2非证明136个保留，155为完整包总数。9定理叶4814B逆删精确。全部NOT_RUN/HOLD两prefix，审计SHA80b3205eeaeeb9f4fc581e13b75b5a371e3dd821a33179558f3f26ff2da5b412；组装前预算表留作历史，不能沿用其8–10KiB余量。

- **7489真实成本已核，支持继续既定公共证明**：`direct-bias-7489-cost/HANDOFF.md`。40420540388精确748999…/228187B；完整diagnosticEntry成功路1imul、bt/adc、一次变量shr，无FP/table/call/显式spill，但仍5保存+16Bframe。实际public MainFull ADD/MUL均与B2同体；7根只含旧规格+新定义，无新MUL等式或性能。audit.json SHA bf0522cc34baeec23d8441ad5429058b1b2246a9a7239bc9549a0f9d7b511256。未改任何候选，下一需公共证明后的真实选中caller与原D。
- **GRS20min阶段完成并冻结**：`grs-add-cost-frontier/HANDOFF.md`，1867B/e4833e4e8b41c7fe50cb8dfa91dbd639fc4cc6aa926fb7b5498e4dda1a2be45a；只运行片段，无Kernel/Lean。新法比R16扩大normal异号覆盖，但一cast+toBits原已存在；toBits非尾调用使原输入/指数/符号跨call live，不能由有限28452模型一致或频数声称收益。Root已独立追加B2成本源，后续只收真实诊断。

- **Classifier停放完整计时**：cc9268820d3c9b3c4e664d6a659a12ef259c7c8443db61980a686cad974ea5a5，228099B。40395429076真实statement与两次kernel replay通过；helper-audit因D清单三个错误Submission.R2W01b前缀失败。`HelperAudit-eager-corrected.lean.inc` / `classifier-corrected-audit.json`给正确3helper+4public根，正文不改。四public公理日志仅三允许项；完整gate/性能仍未通过。
- **成本判别已变为负**：选中MainFull C有变化；同批保留标量control（index1）的MainFull C逐字同B2，standalone scalar C逐体同B2。实际standalone ADD/nativeMul仅两处OR→XOR、MUL仅一处；旧Clang早已把短路AND压成两setcc+OR+一个branch，未减少branch/load/call/spill。详`CLASSIFIER-40395429076.md`、`classifier-standalone-40395429076/review.json`及diff。MainFull ASM未采，不能冒充选中caller或性能结论；下一必要诊断顺带补即可，不为此加完整D。
- **Compact首完整D性能负，停止晋级**：9c4e源未改。40417039536/1927008的55原件独立重哈希，三原fullgate/25round通过；whole/B21.0296713646、p05−0.0456265084、ADD1.028807/MUL1.044535。保留B2，不建A/B或换seed。此前404108接口/actualMainFull/true512证据仍有效，永久中间表及全部成本保留；不能把回归归因于单一flag。详`compact-cost-40417039536/REVIEW.md`和`audit.json`。
- **已交关键旁证**：`runtime-audit.json`绑定B2实际MainFull ADD lambda0/MUL lambda3，排除逐项boxing/RC前提。`CODEGEN-CAPTURE-NOTE.md`指出D脚本ab39…只抓Submission而漏MainFull，root已转板；`JAM17-COST-REVIEW.md/json`核固定U32/64和signed反向cast成本，不另建算术变体。

表示排序见`static-dispatch-frontier/DECISION.md`：Double跨宽仍缺允许桥；valid函数包装没有无新增ABI工作的根据，两路早停，无新候选。原冷边界/其他源保持冻结，本文不更新其独立编译状态。本阶段结束，下一只按根授权收公共证明/实际caller原件，不占槽造微变体。CI占用0，本机编译0；tokens/cache UNKNOWN。
