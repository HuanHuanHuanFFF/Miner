# R25 integer C — 最终源码交接

首次tool **06:53:12 UTC**，共同截止 **08:19:16 UTC**；本角色最终时段见 `delivery-receipt.json`。只写本目录，Git/CI由Droot负责；本角色CI、本机Lean/native、正式提交、资金动作均0，token/cache/连续模型CPU UNKNOWN。当前 **paper＋有限重放** 有证据，所有Lean草稿及C成本均无验收回执。

- **新主攻入口：** `BLOCK-REDUCTION.md` 的block16→128采用静态项界，不依赖观察到的抵消。typical seed42首层608→80，normal/sparse **160/160** 点积逐字一致，每点积128合并 **608→38**；wide80项因term93bit拒绝。旧legacy1020dots的pair63仅27，不能冒充正式profile。原始数据分别在`typical-first-layer-probe.json`、`model-span-probe.json`。
- **已备成本源码：** `integer_cost_probe_relu.c` **cc1c1bfb…** 比较双链128/block16/checked桶，分别测prepared与含prepare的完整首层，包含bias、round、ReLU、输出分配释放；header可重生成。旧`integer_cost_probe.c`/1ea72c36…保留，其边界未含ReLU。`cost-source-preflight.json`按冻结源码字运算重放480个输出，但 **C proxy不等于Lean成本，也未实际跑C**。
- **关键迁移判别：** 固定Lean4.34.0 `lean.h`证实UInt64 boxing分配constructor、UInt32在64bit主机为immediate；Int small严格按原header的`sizeof(void*)==8 ? INT_MAX/INT_MIN : shifted`条件，不泛化成63bit。`IMMEDIATE-FACTOR-INTERFACE.md`给出Array UInt32缓存＋`(w.toUInt64 ^^^ 0x80000000)-0x80000000`。`signextend32-probe.json` **06bb2538…**：160/160两operand signed31guard通过，194560访问恢复相同word与输出；每MAC新增2xor+2sub+2unbox，非指令/耗时。普通wide拒绝不变。
- **证明边界：** `SignExtend32Explicit.lean` **3a595ced…** 用Nat xor商/余数两分支及UInt.toNat，不用bv_decide/native_decide；另有实际block fold、checked bucket和ReLU零号端点草稿。全部 **NOT_COMPILED/AX/replay未验**。保留的`SignExtend32.lean`虽非policy token拒绝，仍须排除默认tactic引入native相关额外公理，不能列为已采用根。
- **下一轮独立方向：** `band-pair-probe.json`的typical wide80dots按四指数分段得到10段、14块合并＋10段shift，代价608次index读取；仅有限归约。`WIDE-BAND-REDUCTION.md`列出partition/getter/全局128界；六个失败边界在`route-falsifiers.json`。

`final-audit.json` **3cc35a20…**：23项身份核对通过，原19件冻结源字节不变；storage旧纸面快照保存为`IMMEDIATE-FACTOR-INTERFACE.v1.md`，历史映射已记录。完整最终文件哈希见`delivery-receipt.json`。官方accb82b6、依赖/pins/新track-rules均已读；current champion UNKNOWN，明确拒绝API未重试，无unknown-license前冠军代码复制。下一笔投入先测同源native完整调用并查生成C的缓存/装箱，再决定完整Lean整合；不先扩整Kernel证明。研究目标/冠军/收益均未达成或未验证。
