# R14 网页研究资料

四份原件由 Codex 内置浏览器下载到 E 盘，已逐字整理到当前工作区。原件不覆盖冻结候选；由开发协调者纳入下一本地提交，新公开推送权限另行处理。

**全部 Lean 编译、kernel replay、传递公理审计、新候选完整 gate 与性能仍为 NOT_RUN。** 本目录的已核验结果是文件身份、源码声明/定义比对，以及一处定理名接线修复；不能把网页审阅当作验收。

| 原件 | 字节 | SHA-256 前缀 |
|---|---:|---|
| [共享舍入修订片段](common-rounding/originals/R14_common_rounding_repaired.lean) | 20004 | 9d841b404f705d60 |
| [共享舍入报告](common-rounding/originals/R14_common_rounding_review.md) | 25772 | 255156758f97d7d9 |
| [整数乘法最小修复](integer-mul/originals/R14_integer_mul_fixes.lean) | 1428 | 80db9437246cc5b5 |
| [整数乘法报告](integer-mul/originals/R14_integer_mul_review.md) | 22579 | 4b85a268fd3abe2f |

完整哈希、来源和路径见两份 [common intake](common-rounding/intake.json)、[integer intake](integer-mul/intake.json)。E 盘原件保留在 `E:/Download/FloatLib/20261025-R14/`，两端字节一致。本轮是四个直接文件，没有 ZIP，也没有扩大清理范围。

## 已独立核对的内容

整数候选 `6f8808d0` 第3649行引用 `FastMul.mkW_eq`，实际父本声明为第2206行的 `FastMul.mkW_ofNat`，类型与所需 calc 步骤一致。唯一替换这个引用后，内存预览为253523B，SHA-256 `b8a11a6a1c647df5031505b7effa5c3d21e653631db0638815a3062c7d20b6c2`。没有改开发侧原件，也没有生成或编译新候选；改完不代表其余证明一定通过。见[名称确认回执](integer-mul/review-confirmation.json)。

共享片段的13个原有引理声明文本全部保留，`roundedMantissa`、`carry`、`normalized`定义逐字不变；未扫描到新增占位、公理、unsafe、extern、native_decide等禁用代码，也没有section variable附加假设。这只是文本检查，不能代替Lean类型和公理检查。

修订片段包含闭合的私有log2_shift依赖、小h与正常舍入分支、带存储符号的模运算，以及Int精确和的postguard/零/乘法下界桥。它没有证明具体机器Int64对齐无回卷，也没有绑定某个新公开add的真实运行体。正常输入以外的NaN/Inf/subnormal/±0仍须保持原完整fallback；不要把精确Int零结果的+0结论直接推广到未经限制的IEEE输入。

去掉修订片段首行22字节的重复import后，与227657B的精确compact父本拼接：加一个额外LF为247640B，加两个LF为247641B。后者对应网页报告大小；最终应绑定开发构造的实际字节与SHA，而非只引用这个数字。两个内存预览哈希见[核对回执](intake-verification.json)。没有创建新的CI请求或运行候选。

复核入口为 [verify-intake.py](verify-intake.py)：仅轻量文件/声明检查，实际约0.061秒，2秒上限，不调用Lean或编译器。

## 来源与使用边界

两个会话提交前UI选择Pro，第一份选择菜单显示power5/5。完成后输入栏显示5.6 Medium，第二份页面提示能力降级至10月29日；已完成响应的实际后端模型UNKNOWN。两份资料按普通外部未验证建议接收，不宣称已经以完整6 Pro能力或固定编译器验证。

网页Library持久保存未成功；直接下载并不依赖Library。研究侧没有授予新的Library权限、执行升级/资金动作或使用额度重置。截图仅保存在本地visualizations，不进入Git。会话、输入哈希与此前持续研究/上传授权锚点见 [dispatch](../astra-web-pro-dispatch.json)。

精确compact `3c6af73f`目前只有statement证据；原DF运行/证明有先前full gate。两者不能按不同哈希相互继承验收。当前全部新运行候选和本目录修订片段仍待开发固定runner验证。

源码参照为固定FloatLib `0d918257…`与Lean `293d5d0c…`；原参照及许可证在本轮 `astra-upstream/`、`astra-upstream-lean/`，由各source index记录。四份网页原件保持原字节，不回写其原始NOT_RUN、缺项或保存失败说明。
