# R7 检查点18：单遍sum初稿与可复用闭包

时间2026-10-22 23:30 UTC。原10小时截止04:22:17 UTC、02:45源码冻结不变；仍无CI在运行，810未推送/派发。

`f01-r7-sum-singlepass-fused/Kernel.lean` 初稿230429bytes / SHA256 `8ec342ec4bb9f7f72629ee219931fd0f8212c998de92876a2ab413a5466f5ef6`。**尚未ready、尚未编译**，不请D立即派发。父本为精确0e8 combined-proof2；仅新sum导出改成单遍USize循环，保留全部原有定义（旧sum改名），add/mul/BMM仍父本。Nat超大逻辑尺寸后备、首rawNaN一次精确add及W02原序sNaN尾扫已写出全域证明草稿。静态哈希/体积/import/BANNED检查通过，不能替代原版完整policy或Lean。

普通路径复用现有decoder的低/高两条件；只有高端冷分支额外比较Inf与NaN，不逐项检查native accumulator。这个成本意图仍需实际C验证。`singlepass-sum-oracle.json`：9200有限trace、100020原word分支检查通过；35个公开sum案例的完整输出word SHA及D锚定actual checksum相符。计分807共5,046,844原word：5,035,572 native加、320精确repair加、10,952后缀rawword读取；源分支中363 Inf+320首rawNaN=683冷分类点。**不是计时收益**，并与旧sum native-prefix路线替代/重叠。

供D的 `canonical-image-minimal-block.lean` SHA61d49494/12744bytes已静态检查；精确依赖还有`Submission.NotNaNProbe.add_inputs`，原有60f/0e8均具备。完整W12源实际通过，映射块未实际编译。D拥有BMM接入，R不重复构造BMM。

W12b已进入最终整体编译/公理审计和打包：公开decoder分支及任意nativeacc+非NaNraw输入、首rawNaN quietness接口。交付前只按网页进度，不当已核验产物。

W11独立report已在E盘；大ZIP、多MB附件持续下载无事件。800000字节小文本附件实际成功，解码后与原ZIP前600000字节SHA相等；已让网页仅切片余下原件，回收工作继续。只记观察，平台确切体积门槛UNKNOWN。原报告30分钟超25分钟偏差保留。W11原ZIP尚不能标完整已收。

下一节点23:45 UTC：回收W12b、复核草稿证明；完成W11小附件拼接与原ZIP总SHA/CRC/manifest检查。根据实际数学/C证据决定是否将唯一单遍sum转为statement-ready。

23:35 UTC追加：

- 已读D19：官方冠军279/HEAD与suite未变由D管理；R不重复BMM。D的70386323最小闭包矩阵集成仍未Lean/gate验收。
- **唯一单遍sum的proof1现在可供statement检查**：`f01-r7-sum-singlepass-fused-proof1` / SHA256 `3d9b1ea94ec105073334b793adcb5a9fecc4eda37dd2a5809e715b5584a54576` /230650bytes。全新集成Lean **NOT_RUN**。采用W12b实际通过的low UInt32回绕证明、显式UInt32序关系与已编译convert改写方式；相对8ec只改证明，三个运行定义逐字节相同，见`singlepass-proof1-lineage.json`。旧8ec草稿保留，不声称它实际编译失败。D可在授权后优先statement查这一条，旧0fe二次prefix与它是重叠替代，不要求扩大并发或同时计时。
- W12b原件已在E盘并完成CRC/115 manifest核验：ZIP8436066d/reportbecf766b，增量415bc6b9，完整主文件bf334ffa。实际证明允许acc已NaN，并保留qNaN右操作数被左canonicalNaN优先级覆盖的反例；本地草稿始终用精确add处理该步，未采用错误的无条件保留右payload假设。
- W12c约23:32 UTC启动、15分钟目标，仅在原已公开60f上独立提取最小W05/W12闭包并编译原四spec，不包含私有新sum或BMM源，用于降低命名空间/依赖接入风险。
- W11目前已回收到第9/15片；剩余6片继续下载，尚不标完整。源ZIP按总SHA精确复原后再清点解压体积和manifest，不执行其脚本或二进制。
