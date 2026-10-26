# 40410895344原始反馈：一通过，两条待修

d6b76ba0／1927006已failure终态，88原件全部回收并逐字节核验，三行收齐；批failure不代表三路都失败。完整gate/25轮在本statement批次均NOT_RUN。精确goal见本目录`development-proof-*-40410895344.json`、`development-compiler-error-map-40410895344.{json,md}`，原件根在`f01-mul-log2-proof1/ci-runs/40410895344`。

| 路线 | 真实反馈 | 下一判别 |
|---|---|---|
| DirectBias1180 | VerifyFull在31.3s后exit=-15；完整输出仍仅1B空行，没有编译错误位置，14根未执行 | 原4307B seed旧26.6s的UNKNOWN仍未关闭；不是数学反例或普通可定位typing错误。优先隔离/采资源判别，不能按有利seed复跑同样大探针 |
| DualTemporal9a5f | 五处6750/6759/6763/6767/6771对`R19Temporal.loop`递归定义的rw失败；6810最后goal两边打印相同emit/loop | R matrix按实际完整goal做最小证明修复，保持runtime/guard/布局不改；最后defeq目标可先检查rfl，不能凭打印相同就称已通过 |
| CompactScales9c4e | 原声明成功、Submission及VerifyFull两模块回放成功、10实际根仅3允许公理 | helper原始stdout最后真实`true`、`512`；D下一步核真正MainFull表读取和初始化成本，成立再给首完整D |

补充DirectBias资源边界：刚核当前官方4b7e的gate.py原过程helper（Git blob88894a8f…）；通常communicate timeout会SIGKILL并返回124，不是此处-15。这只排除“普通30s gate超时”的猜测，不能据此断言OOM或具体定理错误。新鲜primary摘录在D本地维护`current-gate-process-helpers.json`，不改官方gate或限额。若下次必要诊断，宜先编译/复用B2再在独立受限helper模块用逐根flush标记，记录进程/MemoryPeak及scope结果；诊断模块不作为正式candidate gate，原1180失败原样保留。不要提升限额/改gate来换通过。

新字节/当前状态由D协调，R请优先把这两条明确界面交回对应Astra。旧Jam cold-boundary1d15仅少一个未用save的上界证据弱，当前不抢纯整数/双侧缓存/静态表槽；若保留就明确NOT_RUN。peer postguard另已通过留言板请求独立认领，D不重复。主窗口仍至04:46:39 UTC。
