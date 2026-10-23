# R10：精确41的独立阶段诊断

本端口只支持 `41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7`，复用旧D7 profiler的临时statement重放、原编译／链接命令和证据保存结构，补齐当前DirectSmall／RowStream分派。**本地静态验证通过；Linux编译／链接／运行均NOT_RUN。** 原gate、bench、public-suite、旧profile文件、原始证据与状态均未修改。

`profile-retained-entry.py` 的参数为：

```text
--upstream <原4b7 checkout>
--kernel <精确41 Kernel.lean>
--out <新的诊断目录>
--plan <实际public-drawn-plan.json>
--original-verdict <此前原完整gate回执>
--original-summary <诊断前复制的原summary>
```

entry首先核对原summary中唯一候选行、41源码hash、verdict hash、原完整gate成功、原public-v2 suite、seed、25轮、pairs500000及完整参照。随后在单独临时层只运行intake／policy／statement；`profile.run` 明确拒绝含score阶段的调用。输出为 `profile-retained-result.json` 以及独立 `diagnostic-only-verdict.json`，后者显式 `diagnostic_only=true, full_gate=false`。原完整gate回执与summary复制保存，并在最后逐字节再核对。诊断失败只能表示诊断失败，不能覆盖原gate成绩。

## 精确生成C与返回覆盖

审阅fixture来自run39945391484的原41 statement codegen：Submission C SHA-256为 `fb421a595ceced1cf8994f19ccb32704ac20a02a0430eda6c4134bf042d075db`，`candidate-c-index.json` 绑定该hash与41源码。新模块只接受这份精确C；新C字节不同会拒绝，不猜测符号或漏插桩。gate／generator／suite也各有精确hash约束。

函数提取器同时支持 `lean_object*`、`uint32_t`、`float` 返回，检查完整平衡函数体及所有真实return。BMM的3个return全部emit；RowStream.core的4个return全部结算准备计时；DirectSmall的1个return结算完整direct时间；replayEarly的1个return结算replay时间。RowStream每行tile／output，以及NativeFinal.dotLoop的完整调用在唯一实际调用点计时，其函数所有return也在库存中检查。NativeFinal.dot原生阶段位于两种return分支之前，fallback时间由replayEarly覆盖。

当前fixture实际旧seed825计划每process有137次BMM调用：77次direct、60次packed；102次timed、34次checksum、1次raw。映射从实际原计划生成，按 `n≤4 ∨ p≤2` 识别direct。逐事件检查序号、路由、累计core／direct计数、packed行数、direct输出dot调用数、fallback调用上限及最终总计。缺失最后return事件、重复END、错误计数和负残差均拒绝。checksum、timed、raw分别输出，不能互相填补。

## 计时边界与控制

互不重叠的主阶段为：

- `nativeA_ns`：packed入口至nativeA.map完成，包含初始行索引数组准备；不是孤立map调用耗时。
- `packB_ns`：map完成至packB完成。
- `tile_ns`：每行rowTiles的完整Array.ofFn调用之和。
- `output_ns`：每行RowOutput.row调用之和。
- `direct_ns`：完整DirectSmall.core调用。

`native_dot_ns` 是direct内部的原生dotLoop小计；`replay_ns` 是两种路由的精确fallback小计。两者与父阶段**重叠**，不能再加入主阶段总和。`residual_ns` 只用BMM总时间减上面五个互斥阶段，保留dispatch、索引／closure准备、append、部分观测开销等。各process还按direct／packed和三种phase分别保存原始小计。

控制按同一源码／输入／编译命令运行：先测原未插桩binary；再编译同构计数／输出harness控制，仅将内部clock宏关为0；最后编译详细计时C并运行3个process。两种harness除detail标记与内部clock宏外逐字相同，保留相同计数与printf。详细结果的checksum须与原控制、同构控制都一致。既保存对原binary的逐case best_ns开销，也保存同构控制对每次timed／checksum／raw调用的开销。控制各一个早期process、详细三个后续process，顺序与process噪声仍存在；负开销样本原样保留，不据此宣称正式阶段份额。

runtime保存原Kernel、三种C、原gate／suite／generator hash、suite与generator字节、精确drawn plan及seed／pairs／inner／绑核、原编译／链接argv和rsp、compiler executable hash／version、重建前后object／binary身份、所有命令原日志、所有process与逐调用记录。只改可丢弃层的生成C，不改变候选或原官方代码。

## 本地验证与接管

`python -B test_profile_retained.py` 共12项通过，覆盖真实fixture绑定、真实return覆盖、同构控制、两种路由／三种phase、零计时、计数／残差错误、C漂移、完整gate前置绑定，以及整个compile／control／detailed流程的**模拟I/O测试**。模拟测试没有执行Git、clang或binary，不能代替Linux运行。`profile-retained.py --selftest` 与entry `--help` 也通过；精确命令输出、hash与保护文件前后hash见 `profile-retained-design.json`。

主协调者已约定只在 `profile_current=true` 且 `profile_candidate=f01-r8-combined-result-guard`、原完整gate成功后接入本entry，并先保存原summary。普通确认计划保持所有observer关闭。新增诊断的Linux运行、当前CPU计时结果与开销仍待根CI验证；这组材料不属于正式采纳gate、冠军比较或排名证据。
