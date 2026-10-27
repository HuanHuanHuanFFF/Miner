# 8134第一次编译修复交接

原因：新row_prefix的fold invariant持有偏应用`group … r`，而新row用行地址外提后的`groupFrom`；旧simpa没有展开该函数值。不是旧DC public规格或namespace顺序错误。121原件hash核对PASS，唯一5993:2完整goal保留。

修复只加local callback等式`hgroup`，以`funext acc g; rfl`证明，重写h后用原长度化简。runtime/domain/四public specs/声明顺序逐字不变；14roots静态精确定位。完整新稿Kernel-dc-rawpair-repair1.draft.lean，235456B，SHA6a0c18c52d736a1b8856877d6056372e13f70b095e36e34bd05203bcb7a5d1c0；逆patch逐字回8134/235299B，净增157B。

新Lean/整模块/14roots/selected-C/计时全部NOT_RUN。父可只导入此新稿并更新新manifest/source hash；旧源码/候选未动。详细证据、原goal、正逆diff和自动回执均在本目录；不需要改变runtime或资源，也不直接计时。
