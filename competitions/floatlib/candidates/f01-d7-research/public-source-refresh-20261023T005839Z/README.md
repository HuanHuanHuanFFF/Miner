# R7 公开强起点与官方倍率复查

2026-10-23 00:58 UTC起，全部只读GET。[完整回执与结论](findings.json)保存19份原始响应的时间、SHA和公开源码精确版本。

| 检查 | 实际结果 |
|---|---|
| 退位冠军源码 | 目前公开FloatLib实现只有6个读取路由，无source端点；#271/source返回404。通用API文档的source路由属于DEFLATE，不能套用。未据此断言作者不可能另行公开。 |
| 新基准冠军 | #265/#267/#268/#269/#271/#272/#274/#279详情均取得；8份digest与189份本地候选无整文件SHA匹配。 |
| 官方公开仓库 | forks/tags/releases均0；18个PR的head均为官方本仓库，未发现新参赛者内核起点。官方kernel源码HEAD仍4b7e838。 |
| 官方倍率 | #279为6.80117×，明确基准scoring-v2-2026-10；官方沿精确参照hash、同benchmark连接。#265在新基准用官方声明的2.209×实测anchor重启，不是把legacy链直接乘进来。 |
| 当前开发 | public-v2为2.84–2.94×；同一私有基准的正式值和我方/279直接比值尚缺。继续本地已准备机制，不伪造差距。 |

本次修正当前说明中的“跨suite历史链”旧标签；原c329a506提交、原始响应和旧阶段结论保持原字节。官方anchor的原始bench日志尚未取得，不能把源码注释升级为本次独立重测。

公开validator源码：[e78afe97](https://github.com/conjectures-io/conjectures-validator/tree/e78afe97f93cbdae1f65f354a8e8d12b355f2020)；[倍率定义及条件](https://github.com/conjectures-io/conjectures-validator/blob/e78afe97f93cbdae1f65f354a8e8d12b355f2020/docs/COMPETITION_API.md#floatlib)；[固定锚点与hash链](https://github.com/conjectures-io/conjectures-validator/blob/e78afe97f93cbdae1f65f354a8e8d12b355f2020/submission_api/floatlib_store.py)。本次没有上传候选、运行新CI、正式提交或资金动作。
