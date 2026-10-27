# 最新CI12：精确2177单模块也触及4GiB OOM

40430974047/f4211856：math helper−15/24.132s、stdout0；唯一观测scope run-r340d5e556df84c2b85ac17a0e863f347，Result=oom-kill、MemoryPeak=MemoryMax=4294967296、OOMPolicy=stop、SubState=stop-sigterm，92采样/oom_kill1。9份原件（含B2 input）绑定math-review-40430974047.json。仅此run物理OOM已证；CI11等历史cause仍UNKNOWN。新48根/replay未执行，绝无public接受。

准备但未排队：shared-block-isolation/NatPostClosure.lean 4877 B/cbdb2fb8…（Nat seed+PostBias）与NoWrapOnly.lean1821 B/8d49e866…（原biased_sum_nat）。这两块分别覆盖已失败源共有Nat层与旧word_grouped复制来的1338 B无回卷层；按原字节切出，无证明/runtime/域修改。R/D决定是否两独立process原限额诊断；首段失败不能逻辑推定另一段失败。见该目录manifest/HANDOFF。原quotient-only不重跑，7b03/70d4继续HOLD。

# DirectBias当前：fa652全源再次-15，转现成单模块判别

R截止2026-10-27 02:28:21Z，D窗口不改。仅本方目录；无Git/CI/本机Lean/新runtime。

- **实际CI11**：40428306094/a92abea1，fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5 /255311 B精确匹配。VerifyFull exit−15/30.0s；完整输出1 LF，SHA01ba4719…；verdictSHA117ccd4ded444fa15a0d74b2f2decdb1466ed0f7ba2bc308a9f94689e394a388。该run没有scope采样/Lean goal，cause UNKNOWN。相关6原件核验在public-feedback-40428306094.json；48根/两模块重放/新public C/timing均未到达。
- **最小后继**：既有public-proof-review1/MathOutlet-interface-v1.lean，32332 B，SHA2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266。精确B2 carrier后，原g.own/build=read/caps独立运行单模块，同v2抓live cgroup/observed scope；完整请求math-isolation-request.json，短交接MATH-ISOLATION-HANDOFF.md。无新增proof/source版本、无前缀梯队。exit0也不替代fa652全源接受；仅B2四根audit不等于新48根。
- **排除误修**：CI10原ImportOnly/QuotientOnly均exit0，5.284/5.905s，运行中memory.max4GiB、无oom_kill。原quotient不改；7b03及conditional70d4继续HOLD。CI7曾有scopeOOM只覆盖CI7，历史1180及本CI11原因不回填。旧#eval标记不能定位声明。
- **源码边界**：完整候选已接真实guardedMul→FastMul.mul_spec；独立审查确认48根静态存在、136原B2非证明声明逆命名恒等（155是全包总数）。删9旧普通证明叶4814 B，逆patch准确；runtime f3e86842/1359 B不改。当前余689 B，另有5个可复核旧证明叶1756 B储备（只读未应用）。
- **成本与负例**：CI9 7489诊断完整接受路一imul，无FP/table/call，仍共享frame，公开仍B2，不是性能。Jam b271 full whole=.9988850281、p05=−.0108148042，精确负运行体停放；B2仍保留。

下一：真实单模块错误才作版本化proof-only修复；若新scopeOOM按实际范围定位，无证据保持UNKNOWN。GRS a78a1534独立关键审查无反例/签名问题，报告../grs-jam-independent-review.md；源码未改，公共ADD/Lean仍NOT_RUN。token/cache UNKNOWN，直接CI0。
