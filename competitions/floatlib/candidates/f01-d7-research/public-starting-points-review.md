# R7 公开有效起点刷新

本次只读调查开始于 **2026-10-22T21:49:01Z**，20 分钟预算上限为 **22:09:01Z**。先读前次 `evidence/public-source-survey-20261021T101011Z/README.md`、findings、原始源码树与搜索记录，再检查增量。调查范围为公开 GitHub、官方公开文档及已退榜版本的公开 source URL；没有读取被保留冠军的源码、使用私有仓库、改候选、Git/CI 或上传代码。

**结果：本次检查范围内，新增“有实际源码、适用于当前四内核规格、且有既有优势证据”的起点为 0。** 找到了前次未覆盖的官方 `feat/alternative-kernels` 实验源码，但其算术规格不同，不能列为当前 FloatLib 强起点。这个零结果只覆盖下列已查表面，不表示互联网上不存在作者另行公开但未检索到的副本。

结构化结果见 [public-starting-points-review.json](public-starting-points-review.json)。57 份匿名 HTTP 原始响应及完整 URL、UTC、状态码、字节数、SHA-256 收据仅保存在忽略目录 `.local-maintenance/r7-20261023/public-source-refresh/`，其中 54 份 200、3 份 404。连接器检索原件另存同目录，明确不当作原始 HTTP 字节。没有把未知许可证代码写入待提交候选目录。

## 实际新增源码：有实现，不能替代当前 R7

官方公开仓库 `private=false`，本次匿名读取成功。新增分支 `feat/alternative-kernels` 的固定提交为 **`1c53341a2ab8da66ab3e5a3d7b708d29370bca85`**，作者由 Git commit 及 GitHub 账号关联为 **sagitarim**，提交时间 **2026-10-21T12:08:22Z**，晚于前次调查。以下文件均实际取得 HTTP 200 并核正文：

| 实现 | 真实机制 | 字节 / SHA-256 |
|---|---|---|
| [cached-conv/Kernel.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/1c53341a2ab8da66ab3e5a3d7b708d29370bca85/kernels/exact/cached-conv/Kernel.lean) | 795–807 行把每个输入 patch 物化一次，在输出通道间复用；公共算术仍是 exact dot | 39717 / `63a20ffd61b7cc91a54dc0ee9e7120f2f51e85208e2ee45debcf2931aacfc51f` |
| [hybrid-conv/Kernel.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/1c53341a2ab8da66ab3e5a3d7b708d29370bca85/kernels/exact/hybrid-conv/Kernel.lean) | 832–843 行对 1×1、stride=1、pad=0 的卷积直接索引，其余用 cached patch | 40728 / `6895e073d67122fc65ec2055a748d5fc94c54fa076c5ad8c25b6f674aa940829` |

两份文件首行都是 `import ContractExact`；入口是 12 项 tensor `Kernels` 与 `Obligation kernels`，不是本赛道的 `ContractTensor` 四函数。其 dot 将乘积累计到整数 limbs，最后一次舍入，见文件开头、`Acc`、`dotFn_eq`、`sumX`；当前 R7 的 sum/BMM 必须保留每步 binary32 舍入。二者不能靠更换 import 或重用证明接入。

最小证伪输入已经足够明确：sum 输入 `[16777216, 1, -16777216]`，或同一向量与全 1 向量的单输出 BMM。标准 binary32 逐步舍入输出 `+0`（word `0x00000000`），精确总和最后舍入输出 `1`（word `0x3f800000`）。本次用轻量 binary32 round-trip 计算核对该 witness；没有编译或执行外部 Lean 候选，故它不是外部实现的 gate 回执。

其 [EXACT-TIMING.md](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/1c53341a2ab8da66ab3e5a3d7b708d29370bca85/docs/EXACT-TIMING.md) 是测量试点说明，明确把更快对照界定为 incumbent 对更弱参考，并非 incumbent 的新优化。源码树没有提交 cached/hybrid 的 raw benchmark、results、summary 或 REPORT；`summarize-kernel-optimizations.py` 读取的实际计时位于被忽略的本地 `data/`。因此它们相对旧 reference、当前冠军及 R7 的实际优势均为 **UNKNOWN**，不能把脚本或注释当成绩。

许可证也须单列：当前 main 的 LICENSE 是 MIT，但上述固定实验分支的 `LICENSE` 本次为 **404**，两份新文件没有独立许可头。没有将 main 的许可自动赋给未确认的分支新代码；这两份特定源码的可复用许可标 **UNKNOWN**，只保留忽略目录原件。

**投入判断：停放，不做迁移实验。** 其缓存机制针对卷积 patch 与输出通道，不直接解决当前 26 cell 中耗时占整包约 18–20% 的 BMM specials/extremes 回退或 8–9% 的 sum specials。当前包已有矩阵数据复用；若只重新实现索引缓存，仍须另外证明原逐步舍入和全部特殊值路径，并计入分配/准备成本。目前没有新增命中机会或优势数据支撑这个投入，收益维持 UNKNOWN。

另一个新检索线索是 **Paul Jiang / pauljiang03 的 [HardwarePrimitives](https://github.com/pauljiang03/HardwarePrimitives/tree/02838bfb3171967b657e0ccdaabe4ec4f8d847bf)**。已匿名核对公开 metadata、MIT LICENSE、源码树，以及实际 `MCFloat/Model.lean`、`MC/Special.lean`、`MC/Contract.lean`；FloatLib port 固定 Lean 4.34。它是 GPU Matrix Core 的可执行形式模型及证明，不是当前四内核的已测优化。`MCFloat/Model.lean` 第 46–48 行把输入 NaN 合并成无 payload 的 `.nan`，84/197–202/218–224 行以 canonical NaN 返回；`Special.lean` 文件说明也明确不建模 NaN payload。其 `add32` 第 220 行还会 FTZ。最小证伪目标是带 payload 的 `0x7fc00001 + +0` 或最小次正规数 `+ +0`：这些定义与本赛道逐位规范不同。没有本赛道 CPU 计时或旧冠军优势证据，收益 UNKNOWN；迁移需重做特殊值与舍入规格，不能使用其模型等价证明代替，故停放。

## 其余增量：没有新的四内核实现

- 官方当前 main 仍为 **`4b7e83841cc0c32c6529f533923c73d33b5ecf97`**。前次调查后可见的 6 个 main 提交只涉及 suite、sandbox 隐藏和重复源码拒绝；逐项源码树比较没有 `kernels/` 下的实现变化。4 个新增／更新 PR（#16–#19）均为官方维护，未见参赛者强内核发布。
- 公开分支从前次的 16 条增到 21 条。对 5 条新增分支（alternative-kernels、benchmark-suite-v2、suite-test-set、reject-identical-kernels、sandbox-hides-suite）及已变化的 exact-runtime，实际下载的 `kernels/full/incumbent/Kernel.lean` 都是 **33043 字节、SHA-256 `5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868`**。它们没有提供领先已有起点的新完整包。
- alternative 分支与当前 main 的 **22 份 legacy `kernels/(add|mul|sum|bmm|full)/**/Kernel.lean` blob 全部相同**。这包括证明失败/错误 fixture，不将 fixture 数量计为有效候选数量。benchmark-suite-v2 的差异也不含 kernel 实现。
- 官方竞赛仓库公开 forks 列表仍为空。FloatLib 本体的 6 个公开 forks 最晚 pushed_at 为 2026-10-03，未出现本次以来的新起点；FloatLib main 仍是已知 **`1f5771b3e36a98f17fcac2c6d76aaa024b36aa37`**，该版升级到 Lean 4.35，不升级本轮固定依赖，其已有可移植引理不重复算新成果。
- 官方 tags、releases 列表均为空；没有遗漏在该发布入口中的强内核附件。
- 匿名 GitHub repository 搜索 `conjectures-optimisation-float-kernels fork:true` 返回 1 个官方仓库；`SN66` 返回 88 项完整结果，均为旧 agent/其他用途或无关项目，没有 FloatLib 参赛内核；`floatlib fork:true` 返回 25 项，相关项为本体、上述 forks 与 JumpProcessesLean。后者是 binary64 随机过程模拟项目，真实 README 与公开 metadata 已核，无当前四内核优势证据。
- 代码／提交检索覆盖 `ContractTensor`、`ExecFloat.Spec.add bmm_spec`、`FloatLib champion`、`floatlib Kernel.lean`、公开旧 champion digest 等；命中主要是官方 API、FloatLib 本体、已知 acorn/lean-fftw 等异题项目。未取得新的当前规格竞争内核。GitHub 代码搜索只覆盖其已索引默认分支，不能据此证明全网不存在。
- 额外检查 README 中的竞赛仓库名、ContractTensor 和 floatlib/mining 组合，返回项也没有当前规格内核。宽泛的 `float-kernels`、`conjectures language:Lean` 搜索各只看了首 100 项，含大量无关结果，不计为穷尽性证据；主要否定结论仍来自真实官方分支、源码、公开 forks 与明确不兼容的新实现。

## 退榜源码与规则边界

本次只重新读取已退榜的 [#147 source](https://conjectures.io/v1/competitions/floatlib/submissions/147/source) 和 [#165 source](https://conjectures.io/v1/competitions/floatlib/submissions/165/source)，二者在 **21:53:30 UTC** 均为 **404、133 字节、SHA-256 `40f90378abf922d2708cd45cc87e270302511de5494797c21f98753615198a30`**。没有请求仍被保留冠军的源码。

新核读的 validator 固定提交为 **`e78afe97f93cbdae1f65f354a8e8d12b355f2020`**。其 [FloatLib router](https://github.com/conjectures-io/conjectures-validator/blob/e78afe97f93cbdae1f65f354a8e8d12b355f2020/submission_api/routers/floatlib.py) 声明的公开读路由仍止于 detail/report，没有 FloatLib source 处理器；[API 文档 FloatLib 专节](https://github.com/conjectures-io/conjectures-validator/blob/e78afe97f93cbdae1f65f354a8e8d12b355f2020/docs/COMPETITION_API.md#floatlib) 同样没有新增 source 下载规范。文档前部 DEFLATE 的退出 Pareto 后公开规则不能迁移到 FloatLib。未继续猜测对象存储、内部路径或鉴权入口。

## 对本轮路线的影响

本次没有找到应取代当前保留 `60f74aa4…` 的外部实现，也没有新增足以改变 R7 次序的已验机制。应保持当前按真实耗时份额与命中机会推进的非有限值桥、quiet-NaN/raw suffix 与 scalar 诊断。后续只有出现新的具体仓库/提交/官方公开 source 路由，才值得恢复该调查；单独刷新排行榜不能填补源码、许可、证明和收益证据。

已有 807/809 完整通过及公开套件 2.84–2.94× 是协调者提供的当前包背景，本次没有重新运行或扩大该结论；也没有当前冠军同环境源码对照。新冠军目标仍未达成。
