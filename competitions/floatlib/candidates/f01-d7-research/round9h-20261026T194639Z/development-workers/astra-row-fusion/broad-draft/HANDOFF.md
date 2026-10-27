# 广域 B16 入口草稿：只可进入下一次 typed/C 判别

**源** `Kernel-column4-broad.draft.lean`，255600B，SHA `a87f560a5944a778ca93dfb9a9d2dcd59895edc56b0ae7e498dbcf873fce8f19`，余400B。新核心等同repair1运行体/证明；通用6155B入口只将guard改为 `m>0,n>1,p≥3,4*ceil(p/4)=2*ceil(p/2)`，无新算法或混合tile。`receipt.json`、正逆patch及19根审计入口已存。**编译/C/全gate均NOT_RUN，速度UNKNOWN。**

**真实接线** 新namespace先于public bmm；两处dispatch/spec替换显式传维度。旧父本前缀逐字保留，外层UnderflowZero guard/zero分支与剩余public证明字节不变。选中新支时只建一次flat A4和一次flat outer B16缓存，再按行/列组连续emit；无result cache、补零写、随机set或跨行输出。非目标域回c36。

**成本边界** 对原Dual子域才是已有A4和两B8→一B16；新覆盖的DirectContinuous/其它route会新增A4准备/驻留/析构和B16准备，不能照搬窄域节省公式。所有有效及旧奇列虚MAC、finish/NaN原字回放、输出UInt32装箱保留；实际ASM/新闭包/总生命周期仍待检查。旧R12早有4-lane无spill，不重复计功。

**范围与决定** 窄域已停止（whole3%要求目标调用降约70%/95%）。父方新的旧CI12广域估计7.2887%/5.9742%whole，整包3%需目标全调用降41.16%/50.22%；本worker未读取原scope输入，未把它当收益。广域草稿按父方新增授权组装，仅在repair1核心typed、两模块/公理及实际C支持后才考虑完整D。D17输入/结果及后续性能确认数据未读。

**接手** 先收CI19核心修复，再决定是否编译本精确草稿；按完整真实caller检查旧route到新缓存的成本改变，不从helper孤立ASM或指令数推速度。该稿的15个新根和原4spec都必须重新验收；尤其finish_select、group_prefix及implicit维度接线仅有证明尝试。worker没有Git/CI/本机Lean；03:10截止后不新开任务。
