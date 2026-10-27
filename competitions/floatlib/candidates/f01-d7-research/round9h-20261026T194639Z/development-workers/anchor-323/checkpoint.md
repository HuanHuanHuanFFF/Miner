# 323 anchor checkpoint

UTC 2026-10-26 20:02；预算30分钟（19:53:26—20:23:26），已在前10分钟落盘并更新。仅本目录写入；无Git/index/CI/网络/重编译，不动主D freeze/adopt。

- 已读根AGENTS、FloatLib入口/技术规则/pins/HANDOFF及R19 README。按execute-from-goal实现，verification-before-completion验收，prompt-entropy写交接。
- 原estimator的 `validate_anchor` 是纯构造重放：保留control41六份frozen_records，更新champion_classes各cell的submission_ns、original_model的冠军投影/统计/身份，再重新算payload哈希，即可进入原校验器。当前旧anchor SHA `4a833683649369da031ebdbc8b3c2d37a8bee9d50b6fb5aaf734982faef064d7`。
- 冠军323的官方report SHA `e3725cc1f36e3e9a95cc845271bbd65bfb363744d73fb0b0fe9add882936faac` 与现模型原链一致；新鲜快照原字节已在本地，不需网络。只采用其323/309 paired cell ratios，绝不采用跨机323绝对ns。
- 已定位关键接口风险：`main()` 会读取当前view列出的10组B2 full gates，当前ab3b模型冻结的B2 delta却只有三组（40168687803/40169957447/40171180249）。仅换DEFAULT_ANCHOR可运行，但直接main会重新拟合B2，不能当作无漂移refresh。下一步独立按原三组重建、验证数值一致，并把薄wrapper限制/草案写明。

当前结果：`reviewed323-anchor.json` SHA `da251287655b84f502434fb6da4f2d3ffaa53fb08ae01e0124bc9a4765afa965`，payload `758dfe0452dd57590e0085d7ff386e81d3221080e5dfeeadd9b7b954c317abe4`。原校验器PASS；13处保护节点（含71759字节完整frozen_records）逐字节相等。按原三组重建的四项/whole/six samples/cell delta/paired_updates均与ab3b精确相等；整包1.2487239692464538。

`estimator-reviewed323-draft.py`已能返回实际原estimator模块并覆写DEFAULT_ANCHOR，事务save拦截实测PASS；CLI强制dry-run。十组重算整包1.268407030330682，不能替换当前冻结模型。为了让未来新候选可用，anchor的frozen_files只绑定历史原件和本目录冻结副本，不绑定会变化的全局model/public-results路径。

20:04最终交付：`README.md`为一屏主交接，`MANIFEST.json`列全目录产物哈希。`validation-receipt.json`、`wrapper-validation.json`、`preservation-rejections.json`在20:03:46重新实跑均PASS；两种内部一致但违规的绝对ns替换/源成本重拟合均被额外保持性检查拒绝。保留INFERRED/UNKNOWN边界，不冒充新同机测量。下一决定由D接入R19入口并冻结新cohort；本子任务不改全局或采用。
