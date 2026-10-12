# 原 head/prev 上的8bit额外tag：待实施计划

这是在A13关闭row之后的一项不同表示假设，尚未改源码/派CI。保持原索引、原候选次序、原normal/lazy预算和record密度，不使用FIFO、游标或多槽扫描。目标仅是跳过已知prefix不可能相等的primary/lazy来源word读取。

## 现有机会与不能声称的数值

A11原641的13个PC chain输入有2792213次实际ahead source-word读取，其中1788933次窗口内masked key相等；全部其余最多1003280次（35.93%）才可能属于前缀tag拒绝域。这个数还混有head=0的热来源、过期位置和8bit碰撞，**不是实际tag miss覆盖，更不是时间收益**。本计划对head完整值0保留原source0行为，故实际可删除机会会更小；必须原生计数。

本次表示仍每次link两次u32 store：head写(tag8,pos24)，prev写旧head的masked pos24。不存在row的独立tag/cursor RMW；但每次key/link/ahead新增位移、mask、OR、tag条件和probe拒绝条件，可能完全抵消负载减少。A13隔离维护差额不能用作这项收益估计。相近负例仍包括R12 wordhead +1.780385%、R13 expired0 +1.194808%以及R4改变预取时机的回归。

目标空间只能由实测判断：同质量641仍需约百分之一量级整轴改善才进入主线程最新5%规划区域；这意味着主要PC parser必须有两位数百分比改善。10%目标需要更多。这里不假定tag删除比例能线性换算成这些速度。

## 固定表示和零来源边界

只改原641的chain调用域（13个公共实际输入）；它们的H均走原15位hash分支，H为32768/32769/32781/32785/131100。输入长度≥2^24，或H不在原15位可编码域时，调用未改的原kernel。所有位置<2^24时，head的高8bit存额外tag，低24bit存原绝对位置；prev仍u32并只记录低24bit位置。

同一次原64bit乘法取原slot和紧随slot之后的8bit tag。真实km3先应用km再hash，不能将len3路径当full4过滤。head值0不视为空/无效：它在父算法中实际指向position0。为稳妥保留head完整值0时的原word读取；即使源0的tag恰为0也如此。其余head只有stored tag不等于query tag时才拒绝候选。tag相同仍走原byte验证，不以tag代替匹配检查。

## 不新增tuple字段的缓存编码候选

可在已有三个ahead字段内编码，避免R12再扩大tuple：

- 原`pre_slot`用低15bit存slot，接着8bit存query tag，再接8bit存缓存head的stored tag，最多31bit，兼容32/64位usize；record/link只读slot和query tag。
- 原`pre_c`用低24bit存position，第24bit作tag-miss标记，最多25bit；probe wrapper遇miss直接返回(0,0)，否则交原probe。进入原deepen之前取低24bit位置。
- `pre_w`仍为原source word；miss时为不消费的占位值。head-fix用cached stored tag和position重建完整head u32并比较，保证未改head时复用既有命中/拒绝缓存，不重演expired0因归零而丢失cache复用。

不使用usize第32bit，避免引入仅64位能表示的隐藏证明前提。没有把旧head=0当空槽，也没有将tag-miss改成position0重试另一个候选。原候选顺序/bytevalidity保持；预期同token，但只有原生核验和必要证明才能提升这个声明。

## 最小判别与证明成本

如获准实现，只做一份冻结候选。先原28token/output与父版严格等价、原encoder、decode；未计时observer记录真实head=0、nonzero tag mismatch、tag false positive、实际primary/lazy消费及head-fix复用/刷新，所有观测必须绑定冻结tokens。直接helper测试0位置、km3、最高24bit边界；输入长度2^24及附近必须实测原kernel fallback，不因公共文件较小省掉边界。若实际非零miss覆盖少或等价失败，先停，不自动进入paired。

新gate需要PosHeadBound（head低24bit≤当前p）、packing/unpacking范围、条件word8身份、tag-miss的FoundAt.none以及更新后的ahead/link/record/main/lazy接口。原f_try、长度比较、Dec/fold/writer仍可复用。大输入fallback使旧pc_run1c仍从parse可达，**不能沿A12的不可达性删除旧链证明**；父Lean仅余37273B，新证明能否容纳尚未知。可考虑减少重复proof写法，但不能删fallback证明或削弱原obligation。

判别：这比row有更小、可独立检验的维护变化，值得先审其机会/成本；未把它当已成立优化。是否实施由主线程结合剩余研究/确认时间决定，不直接追加CI。
