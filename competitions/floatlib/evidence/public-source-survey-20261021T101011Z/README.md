# FloatLib 公开强起点调查

2026-10-21，北京时间 18:10 起查询。用户要求优先从公开的历史强版本继续改进。本次为有界源码调查，未启动候选实验、CI、正式上传或资金操作；原 90 分钟研究窗口保持结束。

**结论：在本次检查范围内，未找到可复用的历史冠军精确源码。** 这不表示互联网上一定不存在作者自行发布的副本。当前开发状态仍由 [development-status.json](../../coordination/development-status.json) 维护；完整结构化结果见 [findings.json](findings.json)。

## 已查范围

| 来源 | 实际结果 |
| --- | --- |
| 官方历史冠军 | 26 任详情均取得，含精确 digest 和比较参照 digest |
| 官方公开分支 | 16 个分支的 full/incumbent 均为同一源码：5d0cef3f…7d65868，即现有起始参考 |
| 官方可用示例 | 连同上述分支，共核对 27 份 Kernel.lean；没有与历史冠军 digest 一致的源码 |
| 官方 GitHub 分叉、tag、release | 本次 API 均返回空列表；14 个 PR 为官方维护、接口、政策和许可工作，没有发现参赛者强内核发布 |
| 公开仓库与代码搜索 | 查仓库名、FloatLib/参赛关键词、ContractTensor/mul_spec 及目标 digest，未定位强历史提交源码；原结果见 connector-searches.json |
| FloatLib 下载接口 | 当前官方路由仅有元数据、health、leaderboard、champions、detail、report；已退出获奖前三的 #147 的 source URL 返回 HTTP 404 |

DEFLATE 文档中的“离开 Pareto 前沿后公开源码”不能作为 FloatLib 的源码可用性证据。官方 FloatLib 示例虽公开且附带许可和证明，但其中的历史基准注释不能解释成领先现有起始参考的新成绩。

## 优先争取的起点

统一以本次现任冠军 #174 为 1.00。下列数值标为 INFERRED，由精确源码 digest 连接的历史配对比值换算，不按晋升列表盲乘。

| 源码目标 | 对 #174 耗时 | 可取得源码 | 决定 |
| --- | ---: | --- | --- |
| #165 / #155 | 约 1.05× | UNKNOWN，本次未取得 | 首选；两者 digest 相同，只算一个代码起点 |
| #147 | 约 1.09× | UNKNOWN，本次未取得 | 次选，已退出获奖前三 |
| #93 | 约 1.13× | UNKNOWN，本次未取得 | 备选，已退出获奖前三 |

#165 与 #155 的 digest 均为 42b1070ecf37203ae800489519db7d982e0718988bdc7d3bc1dc6fbbebe52f3c；#165 的参照 digest 也相同，因此不能把其 0.9340 再作为新的代码收益乘入。findings.json 按 digest 合并别名，并保留原始测量。

后续优先使用真正拿到、能核对许可与官方 digest、且已有明显优势的公开版本；先原样验证，再改进。当前没有采用新的外部实现，也未将任何缺源码的目标放入用户的简短看板。

## 可复核来源

- [查询回执](receipts.json)：每份 HTTP 原始响应的 URL、UTC 时间、状态、长度和 SHA-256；所有 .raw 保留原始字节。
- [官方冠军](https://conjectures.io/v1/competitions/floatlib/champions)、[#147 详情](https://conjectures.io/v1/competitions/floatlib/submissions/147)。
- [官方 API 文档](https://github.com/conjectures-io/conjectures-validator/blob/6b0dba7bbdaa732bee9c3c7234e6d2fc608dc263/docs/COMPETITION_API.md)、[实际 FloatLib 路由](https://github.com/conjectures-io/conjectures-validator/blob/6b0dba7bbdaa732bee9c3c7234e6d2fc608dc263/submission_api/routers/floatlib.py)。
- [官方源码树](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/tree/21e42d8f93cd3ecdf5dc4a84c7951ad4c17b185c)、[许可](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/21e42d8f93cd3ecdf5dc4a84c7951ad4c17b185c/LICENSE)。
