# R5-01：逐行输出完整候选已落盘，等待真实编译

10:19Z完成首稿，早于10:35目标。唯一当前入口为本目录research-status.json。D独占Git/推送/CI，R不操作这些资源。

候选：`competitions/floatlib/candidates/f01-r5-row-output/Kernel.lean`，136333 bytes，SHA256 `97cbe074760474c7b04f549a508614c0ba3317ce192e1d9439632b930d77644d`。
父本：f01-d4-final-lowmul，SHA ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630。

机制：在同一份已有tiles上，按batch、row、column构造行Vector；行基址及batch/row两层tiles.get在列构造器之外。两层flatten恢复原行主序长度，避免每个输出做q/(m*p)、q%(m*p)、r/p及r%p。j/10与j%10保持。没有重算任何dot，没有改变浮点执行次序、finite接纳或原始输入回退。

数学桥接：`RowOutput.output_eq`对任意tiles证明新输出等于旧Vector.ofFn；由Vector.ext和固定Lean4.34的getElem_cast/getElem_flatten/getElem_ofFn逐项化简。非空索引推出p与m*p非零；空维无合法索引，最终规格没有额外前提。`core_eq`接旧Packed10.core，实际bmm_spec接原完整规格。原bmm仅改名bmmR4，原四运算实现保留。

本稿完整证明体均已写出；Lean elaboration、公理、完整gate及性能目前全部NOT_RUN，不把静态阅读当通过。请D对精确源码先做statement检查；若通过，对ba93父本做同批完整调用比较。若只是该simp证明留下定义性等式，可查看是否需追加rfl；请保留原稿及修复新SHA。

代价：逐行产生100个输出行Vector、2个batch扁平数组，再最终flatten；复制输出引用及释放成本可能抵消除余和查表减少。不可预报提速，必须由完整调用确认。所有尾列、NaN payload、正负零及巨大Nat仍沿原值层执行。

网页R5-W01已于10:17左右确认GPT-6 Pro并进入responding；它独立寻找更稳妥的输出构造/证明组织，R本稿没有等待网页。原件将在E:/Download回收。
