# R7检查点06：精确组合与sum数学桥

2026-10-22 19:43 UTC。R继续完整十小时窗口；D06已读。806目前原版完整gate仍在执行，未把网页编译或静态检查算作候选PASS。

## 可复核组合

`f01-r7-nonfinite-combined/Kernel.lean`，SHA256 `b1696ff9a51a112c5e34e1a86ef2634c58548492e452199ee041927c6cb5a18d`，173048字节，状态 **NOT_RUN_NEW_COMBINATION**。

同一8eb父本，组合已完整PASS的c760非NaN终点桥与等待806结果的9a2 quiet-NaN矩阵后缀。NativeFinal.dot与Packed10.finish都在外层非NaN守卫失败后直接调用`replayEarly`，用完整`replayEarly_eq`证明，去掉单独9a2版本中此时冗余的第二次NaN判定。普通finite路径、先乘后加顺序、sum非NaN快路、布局和公开接口保持相应组件语义。D可在806反馈后采用或先修具体错误，完整组合必须重新跑原版gate与25配对轮，不能相加组件收益。R不改D的direct-small/singleton布局；由D作最后组合。

7ac原始字quiet守卫仍为唯一待测守卫变体，没有继续扩展相近参数。下一个实质不同机制已准备源码`native-repair-block.lean`与builder，但尚未生成CI请求：NaN终点的第二遍回放保持native前缀，只在第一次native NaN事件做一个精确原始字步骤；quiet则吸收后缀，否则保留原始完整后缀。已明确包含第一遍native、第二遍分类/访存和精确修复成本，有限模型仅诊断，性能UNKNOWN。

## 已回收网页数学成果

W02原件已实际下载到`E:\Download\R7-W02.zip`（200940字节，SHA256 `368af54ae5a958bd8dae9660bf38bf5c011fc681ed426f11751222cddaf18acd`）及`R7-W02-report.md`（SHA256 `c96194daa6624b6de30069c884c443cb9d6e3b4d4a4f93012db6ed20429971d7`）。CRC与96条manifest全部校验，保留原始失败、成功及生成C；本地没有执行下载脚本或安装Lean。

实质桥：raw sNaN掩码等于实际Model分类，quietRaw保留除bit22外所有位，真实codec与ExecFloat.add，quiet初始状态下轻量step与有序后缀扫描全位等价。供集成Append SHA256 `7f2ebdf61b60cc51bbb0a9d27eff5447dedc304cc43c2fd4f64f8511aaa710f4`，18791字节；独立完整文件3651723f在网页固定Lean实际编译与52条公理检查，仍不等于本地集成fullgate。

W02的初始quiet前提必须保留；只知NaN不够，且普通sum不能像dot一样停止。后缀仍会被新的sNaN替换成该输入的sign/payload。R将基于原始Vector/Fin循环接入，避免为定理方便新增List构造。D的标量派发可直接参考raw分类与codec桥；不需等待sum候选。

19:42 UTC左右启动W03公开数学任务：证明从+0的完整sum只要含sNaN，最终字等于最后sNaN的quieted字，闭合add全输入不产生sNaN的实际桥；给出反向扫描命中时的充分条件定理。仅携带公开库/原有公开网页证明，没有私人候选或计时。目标20分钟回收，R同时继续本地集成，不阻塞等待。

下一检查点约20:05 UTC，优先处理806实际错误/完整逐项计时，再选择精确组合及下一机制。冠军直接对照、私有suite收益仍UNKNOWN；正式提交未执行。
