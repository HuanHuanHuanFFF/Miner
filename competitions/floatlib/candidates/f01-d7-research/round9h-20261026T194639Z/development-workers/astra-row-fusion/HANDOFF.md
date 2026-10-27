# 单行四列 B16：窄域停；广域草稿交D作typed判别

**03:19追加修复窗当前入口：** `repair2/HANDOFF.md`。CI19实际类型错误已定位；两proof显式规范化blocks及两pack producer。core3=`036372fd…` /249691B；保留D的B2回退广域副本=`386b5fec…` /255721B，余279B。二者NOT_RUN，D母本7f1d4ec3原件未动，运行体及其余证明全字节相同。03:31追加截止；新DC奇列phantom MAC不是免费工作。

**03:05最新交付：** 根据父方新增广域范围证据与授权，组装 `broad-draft/Kernel-column4-broad.draft.lean`，255600B，SHA `a87f560a5944a778ca93dfb9a9d2dcd59895edc56b0ae7e498dbcf873fce8f19`，余400B；NOT_RUN。guard为m>0,n>1,p≥3及同ceil MAC等式，fallback c36；UnderflowZero外层逐字保留。一次A4+B16准备/连续writer/19根/正逆patch已具备，但新增DC域的A4/B16成本不能当作父本已有工作。当前决定与接手入口见 `broad-draft/HANDOFF.md`。

**03:00当前源码：** D18原8ad以pack_low/high两个目标失败，已读原日志。最小另名修复为 `repair1/Kernel-core-repair1.lean`，249625B，SHA `118d8efc9e8c3d92189913c0aae3d66bca1394a677ec09957174c9d9e97eb1fc`；只变两proof体，运行体/旧原件不动，修复版仍NOT_RUN。详见 `repair1/HANDOFF.md`；以下保留初稿及停止依据。

**02:55决定更新：** 父方独立旧CI12范围核算仅4.2873%/3.1457%whole；子域整体2倍的整包上限为2.14365%/1.57285%，核心2倍更低。因此停完整接线；不扩域。已写入口草稿6155B另存，未组装/编译。见 `ENTRY-STOP.md`。已派发D18仅typed/codegen，冻结核心不改。

**交付源** `Kernel-core-probe.lean`，249605B，SHA `8adff3a04e9f30b6416b4c192276d704b88ea20b34d2bbafcbaa6987d20df9ef`。c36bc250父本241509B整段字节不变；公开入口未换路。新增8095B、余6395B；八根见 `HelperAudit.lean.inc`，原样逆patch与manifest俱全。Lean/C/全gate/计时全部 **NOT_RUN**。

**取舍** 四行融合停放，未造候选。只做A4沿k缓存上的B16：两个B8、两次A4读、两个F2合为一个B16、一次A4读、一个F4；四条链保持原k序。仅结构域p=3,4,7,8，不新增奇列虚MAC；p5/6继续父本。无新A面板或结果cache，k尾不做padding MAC。

**旧负结果不能重置** R16 2a937bb0 whole1.007850/BMM1.043437；R12 da09窄F4 whole0.99651且p05负。实看R12 C/ASM已是4-lane SSE、2k展开、热体无call/栈访问；本次新条件只有4k A4/B16的指针与对象布局。旧全局width4 9613 的BMM1.457也保留。

**静态新证据** `check_core.py`已核父本/源SHA、无新增禁用项、739组源码运算序/尾边界；这不是Float32数值验证或Lean证明。`COST.md`完整计A/B生命周期、finish/replay、输出及F4峰值；`static-check.json`绑定历史源码与原C/ASM，两个旧R12实际loop摘录可复核。

**剩余动作** 收D18 typed反馈，只做另名最小proof repair；真实loop/pack caller检查普通full4借读、hot codec/分配/动态调用、四lane及spill。冻结探针缺完整packB/writer/public接线，新增入口草稿也未验证；不能拿父本计时当B16结果。D17及后续确认资料未读，worker Git/CI/本机Lean占用0；token/cache UNKNOWN。窗口02:33:56开始，03:10截止。
