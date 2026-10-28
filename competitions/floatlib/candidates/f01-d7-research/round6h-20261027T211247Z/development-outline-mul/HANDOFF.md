# R22 cold MUL：轻量Nat typing PASS，完整Math待三处修复验证

首工具23:29:51Z；共同截止03:12:47Z。仅本目录写入，D唯一Git/CI；本机Lean/native/独立CI均0，token/cache UNKNOWN。

- **最新406219**：02ecd四根前缀typing PASS6.207s；14d轻量Nat PASS6.422s。父集成fbd94整Math exit1/22.86s，存在四处HAdd（root d8独立修）及3个目标；失败恢复sorryAx不是接受。该轮原件数量/字节为主控回执，子agent已核详细目标，未独立全批rehash。
- **最新只交接**：`math-repair/final-three-fix-v2.patch`精确3 hunks：显式¬425<word后rw、split/simp_all之后rfl关闭UInt64字面量、normalCore_eq_roundP局部1M heartbeat。`MathOutletFinalThreeFixV2.lean` **4583f5f7…／37742B**；见v2-manifest。**NOT_RUN**。V2替代4b492稿，后者rfl错误放在split之前。只移植3 hunks到root d8；不可拿fbd完整源覆盖其HAdd修复。03:02:33首稿已超03:02短批门槛，不要求新CI；不延共同截止。
- **来源**：完整Math始于旧CI404309 raw2177／32332B，非fae383工作拷贝；nat_bias显式rw已b9b typingPASS，normalized轻量版已14d typingPASS。NoWrap原8d49未改。数学域/runtime/官方4GiB/gate未改。旧88cdf整公共源未接受，后续cap/完整gate/AX重放/MainFull与新源成绩均欠。
- **已验成本**：406073 fd4e5b诊断typed45条无frame/save/call/FP/spill，三miss条件尾跳。四块MUL .9392/.9622/.9410/.9674；whole .9803/.9868/.9676/1.0021，200原件全hash，非原gate/采用。`actual406073-review.md/json`。公共boxing成本仍在，不能把全部收益归因frame。
- **储备**：`rse-interface/REVIEW.md`及manifest；2273B runtime908ae8d0无可达log2，旧9038 math23596B可复用，但旧MUL/df5c1.2908；新caller未测，不追加独立CI。复用C闭包审计static_runner_audit.py及19例已通过。

所有失败/负结果/条件跳过保留；helper typing不代替新public验收。冻结源SHA以对应manifest为准。

容量复核：旧88cdf255520B直接拼显式bias＋轻量normalized再加3fix，预计258446B，超256000上限2446B（尚不含root d8 HAdd字节差）。仅内存投影，未造新publicKernel；见`math-repair/public-capacity-projection.json`。后续须先解决cap，不能把当前helper当可提交整包。
