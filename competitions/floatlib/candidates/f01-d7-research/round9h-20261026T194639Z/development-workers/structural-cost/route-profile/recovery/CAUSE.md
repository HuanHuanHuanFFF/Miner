# CI10首因：第二份metadata耗尽剩余采集预算

00:33:10接手，00:36已确认。真实日志不是“35行之后非零”：1927003 metadata在30.0s后**g.own exit0**，35行完整，两个原binary随后分别exit0（2.5/4.6s），result-1927003.json已完成保存。失败的是**1927005 metadata**：原replay.log明确`lake timed out after22s`；partial-progress记录seed1927005、exit124、总module elapsed60.178s，第二份stdout为0字节。

首因是60秒采集deadline剩余不足；泛化`metadata failed`掩盖了seed/exit。没有记录到type/main-return错误或OOM/137；metadata RSS没有保留，不能编造内存因果。prefix ImportOnly/QuotientOnly成功与本原因不冲突。

`audit_failure.py --assert-complete`已对原始trace运行并按真实症状返回非零；普通模式认证原件并给出cause.json。它不会跑Lean。v1完整partial保留，35行本身没有被当作成功条件。

最小v2只修改metadata：不再先materialize全部A/B，而按相同count/role/row调用原Bench.Suite.element/float与原UnderflowZero.small，第一次false即停止；两个all标志仍分别计算，逻辑值不变。保留原plan/raw/timer binary/flags、60秒cap及120/180外层约束，仍要求exit0和完整35标签。是否节省到足够预算须新CI验证；不抬资源、不忽略exit124、不减少seed或case。
