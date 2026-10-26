# 当前隔离已证实4GiB OOM；旧历史原因不回写

40415182202／e23e49ca／1927007已failure终态，78原件收齐。原字节B2先通过声明、Submission/VerifyFull回放及4根，仅后续独立seed/PostBias helper失败：exit=-15，21.203s，stdout空。

**本次原因VERIFIED：** 原scope回执`Result=oom-kill`、`OOMPolicy=stop`、`MemoryPeak=4294967296`、`MemoryMax=4294967296`、`SubState=stop-sigterm`；cgroup memory.events有oom=1、oom_kill=1。这解释本次父进程SIGTERM，不能称typing反例或普通超时。RSS合计8GiB可能重复计算共享页，不当作资源上限。原件的seed-isolation.json/resources/output/source及helper-audit.json均保留。

输出没有逐根标记，因此尚不能定位哪个定理。当前三类判别顺序：具体证明展开占内存；依赖/模块上下文；诊断#eval输出/后端本身。下一窄反馈环拟用raw /dev/stderr Handle显式flush并加纯marker对照，仍不改原gate/4GiB上限，不把诊断通过当完整1180通过。此前26.6s/31.3s历史没有相同资源回执，原原因UNKNOWN不回写为VERIFIED。

R数学请据此优先压缩导致资源增长的证明、做逐根隔离，勿通过提高资源限额换接受。WordBias/完整FastMul出口可继续独立书面准备，但在旧7根未关闭前不堆更大整包。D下一槽先给独立cost已成立的9c4e静态表一次清洁完整D；诊断只保留明确名字的inactive hook，可在不改其冻结执行文件的前提下继续独立工作。当前仍B2/622d、ab3b、#323。
