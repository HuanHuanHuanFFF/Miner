# FloatLib 研究原件

[数学结论总览](../../RESULTS.md) · [完整成员映射](manifest.json)

12 个 E 盘原始包按原路径结构展开，报告、证明草稿、诊断、反例、公开来源与许可证均保留原始字节。所有 376 个成员、364 条包内校验及 13 份报告／清单映射已核对。原稿的 NOT_RUN 等历史状态保持原文，后续验证看数学结论总览。

| 包 | 内容 | 文件数 | 原始报告 |
|---|---|---:|---|
| [R2-W01](R2-W01/) | 固定 ULP 的双奇偶转移、前缀证书与成本否决 | 28 | [报告](R2-W01/FloatLib_R2-W01_report.md) |
| [R2-W01b](R2-W01b/) | 有符号零、回卷守卫与表驱动转换 | 39 | [报告](R2-W01b/FloatLib_R2-W01b_report.md) |
| [R2-W01c](R2-W01c/) | normal 精确解码的 Model 见证证明 | 92 | [报告](R2-W01c/FloatLib_R2-W01c/FloatLib_R2-W01c_report.md) |
| [R2-W02](R2-W02/) | Packed4 布局、四路原序点积 | 25 | [报告](R2-W02/FloatLib_R2-W02/REPORT_zh.md) |
| [R2-W02b](R2-W02b/) | Packed4 四函数整包与完整证明尝试 | 32 | [报告](R2-W02b/FloatLib_R2-W02b/REPORT_zh.md) |
| [R2-W03](R2-W03/) | 数值重构、尾数移位和 C 代理反例 | 24 | [报告](R2-W03/FloatLib-R2-W03/R2-W03-report.md) |
| [R2-W03b](R2-W03b/) | unpacked-rounding 替代证明草稿 | 17 | [报告](R2-W03b/FloatLib-R2-W03b/R2-W03b-report.md) |
| [R2-W04](R2-W04/) | 单遍 checked FloatArray 准备不变量 | 45 | [报告](R2-W04/R2-W04/R2-W04.md) |
| [R3-W01](R3-W01/) | 整次矩阵准入及机器字地址界 | 19 | [报告](R3-W01/FloatLib_R3-W01/REPORT_zh.md) |
| [R4-W01](R4-W01/) | 两行微块、奇数尾行及独立回退审查 | 18 | [报告](R4-W01/FloatLib_R4-W01/FloatLib_R4-W01_Report_zh.md) |
| [R5-W01](R5-W01/) | 行序展平及输出等价 | 20 | [报告](R5-W01/FloatLib_R5-W01/FloatLib_R5-W01_Report_zh.md) |
| [R5-W02](R5-W02/) | 一次 toBits 的 finite 判定桥 | 17 | [报告](R5-W02/FloatLib_R5-W02_FiniteBits/FloatLib_R5-W02_Report_zh.md) |

原包合计 1,137,545 字节；展开成员合计 3,958,122 字节。12 份 E 盘独立 Markdown 已映射到包内同字节报告；附加的 169 字节校验清单另存于 companions，共保留 377 个普通文件。包内工具仅作为材料保存，本次未执行。

压缩包清理记录：[cleanup-receipt.json](cleanup-receipt.json)。历史轮次中的 E 盘路径可用 manifest 的 source_path 查到当前普通文件目录。
