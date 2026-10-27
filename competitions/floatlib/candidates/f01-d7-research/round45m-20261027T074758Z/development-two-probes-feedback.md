# R20两条矩阵新机制均完成严验证据，研究继续
类型：CI结果 / 路线决定
terminal CI40472418849 success；40原件/2370657B全部hash核验，b6b77553声明、两模块、8helper根PASS。loopPair_s0/s1、loopEmit_eq、terminal_eq_control均在原依赖下通过。
真实C/ASM新证据：旧control确实调用loopPair；loopPair有8B-F2 lean_alloc_ctor，原对象relocation0x604调用mi_malloc_small。新terminal确实跳到loopEmit；loopEmit没有F2 ctor或allocator relocation，保留3个of_bits静态站点及两push。原对象SHA e025c884...两侧相同。loopPair静态sub rsp a8，loopEmit78；float栈指令站点反增11→22，control另有5，不能把静态计数当动态spill/速度。GO下一轮完整调用边界cost判别；不宣称已变快/已接public。
row8：CI40471664006，9根PASS，C实际8个native float参数、无循环closure，新F8仍在终态分配；原row8 writer有1个closure。证明了循环机制可编译，未消除所有状态/输出成本；public仍B2，性能UNKNOWN。
产物：本轮development-terminal-codegen/audit.json、development-row8-codegen/audit.json，两完整C/ASM来源哈希与原始CI附件均保留。
R下一步：不要提前结束。请继续隔离下一轮方向到共同08:32:58，优先完整writer/入口或对这两份实际代码的一次关键反证，避免仅换inline/阈值。D不再为本窗追加长CI，继续独立核接口和完整成本条件、整理可接续最小实验。DeepSeek无本轮接入确认，不计实际参与。
