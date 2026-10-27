# R7 检查点26：W13d严格设置补验原件已回收

2026-10-23 02:00 UTC。D请求的精确公共源设置补验已经完成；当前没有运行网页作业。原7份ready候选Kernel字节未改，未新增算法或变体。

- E盘`R7-W13d.zip` SHA256 `14da14cd5cca845dda3023c2fe4887bd37f9a506f87a751ef3a6849ad2cdd536`，578963bytes；report SHA `ae573f542bc36ca697d016abfc9a78fb69a5810c03944bf39e570b516e631d76`。97 manifest项/CRC通过，当前25组/50主文件索引已刷新。
- 精确主源仍是e8fb1bb6671db553162a4e5fcd44d5bc47c7923df68b32cd7cbb9bd8bf65bf54；诊断源仍4db627a9824f7737aa6c44a0d3ae7cf7ba60c15a31f31314f3690b91ab527453。R独立比较两者与W13c及严格成功快照逐字节一致，源码没有覆盖两个严格选项。
- 主调用01:46:48.902862—01:47:04.715934 UTC、诊断调用01:47:04.729337—01:47:13.815150 UTC，均真实exit0；完整argv均显式含`-DautoImplicit=false -DrelaxedAutoImplicit=false`。新输出路径在运行前均不存在。诊断包含整个同字节主源，不导入旧Kernel.olean；独立核本次stdout/stderr哈希和80声明三允许公理审计。
- **接受范围**：确切公共e8fb宿主的严格普通Lean及诊断通过。不是原版完整gate、kernel重放、C/计时，也不继承到私有353d/3d9新接线。
- 环境如实限定：原路径已被远端工作区维护清理，复用另一处现存缓存；Lean可执行/共享库SHA、FloatLib与共有依赖pin、ContractTensor、官方配置字节匹配。没有重建/安装；不能逐字节核整套已清理的旧olean缓存。另有一次Lean启动前的Python路径预检失败，移除了“未使用Cli目录必须存在”的启动器断言，Lean源和严格参数未动；原失败单列保存。
- 时间：网页核对/执行/打包约8.5分钟；R从01:42派发到01:53:11完成原件回收约11分钟，再到01:57:50完成独立审计约16分钟。准备、等待、回收及审计均计入原十小时，不按网页完成时间缩短消耗，也不延长窗口。

复核入口：`w13d-strict-independent-audit.json`及`web/R7-W13d/original-extracted/R7-W13d/R7-W13d-receipt.json`，原始两个strict JSON/stdout/stderr、environment-identity/source-byte-binding与旧成功/四失败皆可定位。`official-lean-settings-receipt.json`另绑定官方lakefile及已捕获Lake选项，避免只凭口头称“官方设置”。

公开push仍等原问题具体人类授权，0新CI。继续现有交接/冻结准备；02:45源码冻结、04:22:17截止不变。下一节点02:20 UTC或新审阅/验证结果到达时。
