# Postguard frontier 当前交接

21:27 UTC当前决定：**暂缓aeaae排CI，ADD仍停放。** 新外部发现组th0已改变竞争基线：根对run40397668271独立核49份原件和精确差分，14a6ae2f…仅改主MUL阈值128→0，4原完整gate/25轮通过，whole/B2=0.9690534785132748，p05=0.02115601166435621。仅发现D，未读取A/B、未采用；当前保留B2仍622d，原因归属UNKNOWN。

Kernel-postguard-mul-only.lean /230900B/ aeaae0d9b9d8557f2acc868c6dfbf5bb4779b0560e6e55ceb01461fc22742377；新Lean/codegen/fullgate/timing均NOT_RUN，13root。完整域外B2fallback、四spec语义、NaN payload/Inf/±0/subnormal保留。候选未包含旧classifier或compact table。

若以后继续，首次真实成本须同时比较B2、th0和冻结aeaae；不能仅对B2，更不能把已有exsum分派删除的收益归给fused domain。检查相对th0剩余decoder/post-result节省与joint guard/miss/布局代价；aeaae域外仍走B2，未继承th0的全域native路由。无自动CI、无改源、无组合/范围变体。具体更新在FIRST-DECISION.md；根证据文件由peer-discovery-update.json绑定。本次小阶段只更新边界，主D/R九小时窗继续；CI0、本机编译0、token/cache UNKNOWN。
