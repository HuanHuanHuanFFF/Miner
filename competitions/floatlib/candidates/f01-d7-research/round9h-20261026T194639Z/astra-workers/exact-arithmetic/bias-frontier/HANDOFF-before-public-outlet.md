# DirectBias：重复SIGTERM后仅一份proof资源判别稿

root接续授权至主窗04:46:39，原30min阶段已按22:25:27关闭；真实反馈优先。无本机Lean/Git/CI，无第二runtime。

- **本次真实失败**：40410895344/d6b76/1180，VerifyFull exit−15/31.3s；完整输出仅1byte LF（01ba4719…），无Lean错误。原input/log/verdict已对原manifest核哈希。与R14历史同症状，但原因仍UNKNOWN，不是数学反例，也没有确认OOM。
- **当前单一判别稿（HOLD，先等隔离反馈）**：Probe-direct-bias-resource1.lean，235350B，SHA7b0371161a56940568a15a1af3c8db8d11dec4a429ea83c84bc7a31f4ef3d558。仅换private quotient proof：half限2^22/2^23，余数lemma隔离原p；实际两调用bydecide给条件。所有非private头和全部runtime逐字不变、14根清单不变，精确逆patch恢复1180。原静态gatePASS；编译/重放/ASM/性能NOT_RUN，未称已修复。
- **判别理由**：先减旧通用商余数证明的资源成本；新PostBias成本和外部scope终止仍是替代解释。固定gate以systemd-run施加MemoryMax等，timeout返回124，−15不被killed()识别。下一必要诊断保留原gate/上限/flags，抓失败层trace、目标scope的RSS/memory.events及终止证据；若再空输出，不继续无反馈同义改稿。
- **冻结与储备**：原1180、4307B seed、1359B runtime及所有失败原件保留。WordBias.lean.inc6根/cb6f3c2e未入此probe，NOT_RUN；public-outlet.md记录可接B2 FastMul.roundP的纯word出口，未实现public新spec。公开四入口仍B2，诊断caller是Submission.R19DirectBias.diagnosticEntry，不能报新MUL速度。

当前精确回执resource1-manifest.json、proof-resource1.patch；历史history-and-manifest.json、decision.md。D已启动40415182202/e23e49/1927007：原B2先编译，helper逐字seed+PostBias的11个边界flush标记，采RSS/cgroup events，不改gate/flags/上限。先读最后完成声明和资源回执，再决定是否编译7b03；helper成功不等于完整1180修复。不改B2、不复活已失败b271，不读未见确认。token/cacheUNKNOWN，直接CI0。

