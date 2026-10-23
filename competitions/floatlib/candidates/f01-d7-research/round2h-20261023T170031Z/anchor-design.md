# R10 冻结冠军粗估锚

本实现将原有六组粗估冻结为开发显示基准，修复同一源码因新增不同 runner 的绝对耗时而漂移的问题。现任冠军自身耗时继续为 1.00；我方数值表示候选耗时／冠军估计耗时，数值越低越快。这里没有新增冠军实测，也没有改变原始 gate、公开测量、直接冠军比较或正式准入状态。

## 冻结对象与来源

- 父协调者指定的源码状态：`c6da14f7`；子任务未执行 Git。
- 候选：`41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7`。
- 冠军：#285，digest `a1e99008577119824464154be5ec52dd390fc1e429b8f85b6ea73315e7103082`。
- 冠军 suite：`scoring-v2-2026-10`，SHA-256 `2e32904d42216dc6995bcd5124da9a9f74d6bce472abe86c5c075ad52e2c6697`。
- 公开 suite：`a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a`。
- 完整保留 run：39944891642、39946600549、39958723767、39959840945、39961709177、39962018518；没有回挑早期较快两组。

`freeze-anchor-original-model.json`、`freeze-anchor-original-estimator.py` 保留原模型与估算代码的原始字节。`freeze-anchor-public-results.json` 是接手时索引的原始字节副本。`freeze-anchor.json` 自带原模型、六组核验记录、冠军逐 cell 成本、来源、原文件 SHA-256 与 canonical payload SHA-256；同时链接并绑定六组原始源码、verdict、summary、执行 provenance、请求计划、实际计划、cell 工作量、公开 suite 和原冠军报告／回执。刷新流程只读取锚，不创建或重置锚。

原模型声明的索引 SHA-256 为 `4c3095d659ccc2778238dee380b4d8edc398feaa021c31a87aa68e650cbee2c4`，但该中间版本未单独保存。父协调者确认 R9 后续增加了 seed835 失败行并更新索引时间，最终索引为 `1506e463caf62d21529cc51f40eb0c61dbb129eff911982accdc6514c8f7746a`。冻结文件明确将前者标为 `UNKNOWN_NOT_PRESERVED`；当前索引只作定位来源。六组模型独立从原始 gate、源码、工作量与原冠军报告逐项重建，额外失败行不进入六组模型。没有声称恢复缺失历史字节，也没有改写旧模型原件。

## 预先固定的更新规则

同一候选 SHA-256、冠军 digest 和冠军 suite 时，直接复用冻结模型的 `operations`、`whole` 和六组 `samples`。新增慢控制、索引时间改变或新增原始记录都不能改变显示值。

新候选必须提供所有已声明的、同原始 artifact 目录的 candidate／anchor 完整 gate 配对。逐对核对 run、seed、公开 suite、官方源码版本、实际输入计划 hash、provenance hash、参照源码 digest、verifier fingerprint、25轮和完整 cell 工作量。每个候选的实际 `Kernel.lean` 字节与请求计划／summary／verdict 精确绑定；原始完整 gate 必须成功且参照完整。CPU 名称相同或 run 号码相同，单独均不足以构成配对。

每个 cell 的相对变化为：

`delta = (candidate_submission_ns / candidate_incumbent_ns) / (anchor_submission_ns / anchor_incumbent_ns)`

先对所有有效配对的每个 cell 取中位数，保留退步值并给予相同权重。再分别将该 delta 乘到六组冻结候选 cell 成本，乘各组自身冻结工作量，重新求出四运算总量与完整包总量；每组使用该组冻结冠军投影作分母。最后对六组运算比值和完整包比值分别取中位数，范围只表示六组投影的最小／最大值，不是置信区间。完整包先求和再相除，不取四运算比值的平均数。

所有候选完整 gate 都必须出现在声明 runs 中，且每个声明 gate 均须有唯一基线配对。缺配对直接拒绝，不能跳过慢样本。候选源码错误、公开 suite 错误、不同输入／runner／参照／gate、缺失 cell、无效耗时和重复配对均拒绝。仅提供绝对 ns 不能更新。

冠军 digest 或冠军 suite（包括版本和 hash）变化时，当前实现明确拒绝，退出码为2，拒绝发生在保存之前。没有同 suite 的可验证官方 digest 链就不能继承旧锚；父协调者负责在当前官方证据下显式审阅和重新建锚。本实现没有静默重锚或填零路径。

## 接口与验证

纯函数入口为 `build_frozen_anchor`、`validate_anchor`、`normalized_pair_delta`、`estimate_from_anchor`。`checked_record` 做原始文件验证，`select_pairs` 做完整样本选择。`main()` 保持既有刷新调用接口，默认使用本轮 `freeze-anchor.json`；可显式传 `--anchor PATH`。`--dry-run` 完整核对并打印，不写模型、view、state。

本地验证：`python -B competitions/floatlib/scripts/test_champion_estimate_anchor.py`，14项通过；`python -B competitions/floatlib/scripts/estimate_champion_time.py --dry-run` 通过。测试包含同源慢控制不漂移、参照有不同耗时尺度时按归一化改善更新、保留负样本、按工作量复算整包、各项错配拒绝、实际历史负候选同 runner 配对，以及原冠军报告重建。三份真实模型／view／state 的前后 SHA-256 相同。原始输出和精确哈希见 `freeze-anchor-validation.txt` 与 `anchor-design.json`。

| 指标 | 冻结候选／冠军耗时比 |
|---|---:|
| add | 1.1396346568806557 |
| mul | 1.2438994878896614 |
| sum | 1.1257978126187094 |
| bmm | 3.5504062334204853 |
| 完整包 | 1.5003094996185882 |

上述显示值仍为 **INFERRED**。原锚的跨 CPU、跨公开／私有 suite 校准不确定性被固定保留，没有被验证或消除。原始索引中间字节仍缺失；直接同 suite 冠军实测、正式准入与排名保持 **UNKNOWN**。本子任务未运行真实写入模式，未操作 Git、CI、网络、钱包或 Kernel；父协调者接管集成与真实看板刷新。
