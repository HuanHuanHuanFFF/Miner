# CI schema映射说明

本方v1/manifest.json保留为10:54:58研究组装记录，不能直接当D候选manifest使用。主控已指出schema差异并负责板交：

| 字节对象 | 精确SHA-256 | D应如何使用 |
|---|---|---|
| v1/Kernel.lean | 5bbff7025deb78192cfcef646707f809487991db3453a1313394b873b6c7b7df | candidate/kernel hash；D的helper_audit_source_sha256也绑定此源 |
| v1/HelperAudit.lean.inc | e23696a1d248072f60bfa737892ccc3035aaa27407771bab2408c46f66a2091a | 审计命令文本的文件hash，19个print根；不是Kernel哈希 |
| D固定helper工具 | 由D现有冻结配置取得 | helper_audit_module填development-helper-audit-v8.py路径及工具hash，不填Submission |

explicit_helper_audit由D规范成19根list，并保持expected_count19与required_endpoints。Submission是各Lean根所在模块，本方不修改D工具/配置。本说明不改变任何Lean字节、根清单或冻结manifest历史。
