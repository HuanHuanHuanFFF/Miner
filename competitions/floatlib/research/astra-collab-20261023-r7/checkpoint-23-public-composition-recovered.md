# R7 检查点23：公共组合、primitive原件回收与队列收敛

2026-10-23 01:05 UTC。已读D23协调消息及D22反馈。所有既定网页作业已结束并回收，当前没有运行网页任务；不再新开相近网页作业或近邻运行候选。W16最小证明依赖提示仅在本地写了草稿，**未发送/未启动**。后续继续已有证据核查与源码预算分析。

- **W13c完成时间**：网页作业约9分钟，在原10分钟目标内；主会话到01:01才下载回收，回收滞后计入本轮总窗，不隐瞒也不误写成网页仍在运行。ZIP19a5985a/report8805f536，65manifest/CRC PASS。完整公共宿主`e8fb1bb6671db553162a4e5fcd44d5bc47c7923df68b32cd7cbb9bd8bf65bf54`实际普通Lean编译/原四spec完整类型/80声明三公理审计通过；最小R7LowTableDecode块42abb4cb/3019bytes。4次失败源/log保留，分别涉及默认深度、局部选项摆放和表项等式的化简类型匹配。R353d的常量证明采用另一个已在W14c精确宿主通过的正文，未见与这些失败稿相同的未修策略；本地完整候选仍NOT_RUN。
- **W15**：ZIPabdb1015/report32d986e7，152manifest/CRC PASS。固定随附libleanshared.so和libleanrt.a/object.cpp.o内，of_bits/to_bits/isnan分别31/16/7bytes；三函数本体无内部call/allocator/FP栈操作。实际二进制canonical值7fc00000另核常量字节；of_bits源码用quiet_NaN，不能仅靠源码跨实现断言位型。不能把短callee当作caller/PLT/GOT/spill/表读取/乘法成本为零，不推周期或速度。未证明与某次CI最终计时对象同一；W11完整构建仍在依赖阶段超时，未确认到链接阶段。
- 当前24组网页ZIP/report共48主文件已在E盘，`web-deliveries.json`为入口。R14c报告的ZIP复原来源仍明确保留。
- R两份新运行接线仍为3d9单遍sum和353d隔离low-normal decoder，各自完整Lean/fullgate/性能NOT_RUN；其他ready精确源不变。353d只相对c760更换sum decoder；不与3d9拼接、不扩数值变体。

官方口径按D最新01:03协调更新：validator e78afe97已按suite隔离speedup_basis，scoring-v2有#265的2.209 anchor，#279官方乘数6.80117；不再将这个现行值统称为跨suite历史链，也不能除以我们的public-v2结果推算冠军差距。当前无source端点，冠军源码仍未取得。该调查原件由D管理，R不覆盖公共看板。

原截止04:22:17 UTC与02:45运行源码冻结不变。公开push仍等既有具体授权问题，0新CI；R不重复提问、不绕过。下一节点01:25 UTC，优先核已有编译/source身份缺口和组合单文件上限预算，不为填时增加方案。
