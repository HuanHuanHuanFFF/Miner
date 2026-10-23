可再删除旧sum闭链 **5011 B**，不需重接当前sum_spec。按三个独立包的真实净增量估算，P1–P5之后259500 B降至254489 B，余1511 B；若要求最终≥4KB余量，再删此前O1–O5非活动BMM证明段2837 B，预计 **251652 B，余4348 B**。未生成组合，最终改名/空白/证明修复须按实文件重新计量。

精确源：5b7d（245841 B；5b7d926cf628c2d87042386834f7c1581b9a6aa7441af196453984b395534ba2）、4bdd（252609 B；4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0）、d377（244775 B；d37743d3ad6fbc0ee81007a70dc8b1795d3b1aeda4fc58ed379cbab7544feddb）。共同父a066为237142 B，子包净增15467/7633 B；实际增量文件15409/7555 B，差额来自原dispatcher改名及拼接。预算245841+15467+7633=268941，减此前9441=259500，不能把整个子Kernel重复追加。

以下行号均绑定精确5b7d。完整唯一的起止字符串、原段SHA和半开byte区间见[JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-integration-headroom.json)。

|段|5b7d行|完整范围|B|
|---|---:|---|---:|
|S1|5124—5154|NativeFinal.sumLoop及sumLoop_eq至termination_by n-k；保留同namespace的dotLoop|1189|
|S2|5224—5239|originalSum及originalSum_spec|618|
|S3|5810—5838|整个Submission.NativeDecodeSum namespace|898|
|S4|5840—5885|整个Submission.NativeDecodeSumWord namespace|1689|
|S5|5887—5903|含sumBeforeR7SinglePass及spec的完整Submission重开块|617|

五段在三份精确源中逐字相同。全部删去后，旧sumLoop/originalSum/NativeDecodeSum/Word/sumBefore家族无其余被搜到的文本引用；两个新增增量也不引用这些名字。仅S3+S4+S5省3204 B，仍256296 B、超296 B，不能停在半条链。

当前sum:6525及sum_spec:6527直接连R7SinglePassSum.run/run_spec。run:6499在n≥USize.size时走自己natLoop，删除旧NativeDecodeSum.loop没有删除当前巨大Nat后备。必须保留SinglePassSum全段、R7SumRepair.suffixLoop/step及证明、R7W12.ofFloat32_add/classifier、roundtrip，以及repair_quiet仍调用的R7W05.nativeSumStep/repairSumStep_isQNaN。不能因旧命名批量删W05或真正decoder实现。Packed10Index.stepNat/next_decreases还被当前sum和4bdd增量189/203/210行消费；NativeFinal.dotLoop/dot和R7NaNReplay则是实际矩阵/NaN路径，均保留。

referenceSum/spec代码另368 B，但3322前有TorchLean来源doc。只删代码可能留下悬空doc；本方案保留3322—3329整441 B归属与声明，不为微小容量改作者说明。

此前P/O十段已在5b7d逐段重哈希：前四P及全部O位置不变，P5移至6220—6225、仍289 B。原P删除9459 B，bmmPackedBase_spec:6239—6251改接RowStream.core_eq_reference→referenceBmm_spec增加18 B，净9441 B。这仍是唯一须重接的存活BMM规格；旧sum五段直接删除，不产生新sum proof。

若需要≥4KB最终余量，O1旧decode_bounds869 B、O2旧groups_pos_of_col/column_decomposition192 B、O3 Packed10.lane_zero别名75 B、O4 finish_eq_fold/finish_eq_kernel_fold1006 B、O5 finish_dot10_lane_fold695 B，合计2837 B可续删。要按全名区分：4bdd增量66/225行有自己必需的 **R11CrossRows.lane_zero**，不是拟删除的Packed10.lane_zero！CrossRows使用必须保留的finish_eq_dot/vector_get_ofFn；fused使用finish_dot10_lane/packB_lane。zero10/lane_zero10和Packed10Index也不能跟删。总净节省9441+5011+2837=17289 B；268941−17289=251652 B。

旧bmm别名中，bmmR4/bmmRows/RowOutput属于P遗留链；bmmPackedBase整块920 B、bmmBeforeDirectRows整块751 B仍是活动后备，不能直接计为可删容量。DirectRows整块1191 B也仍被4bdd的core_eq_rows证明消费，即使其原运行guard不同。删除这些活动层需改dispatcher并重接spec，本次已有足够方案，不建议新增该风险。

组合只能保留一份四export。若UnderflowZero在最外层，其miss应到已组合的CrossRows，CrossRows miss再到fused base；照搬d377的原a066后备可能绕过其它优化，虽返回值仍正确。空/p=0/n=0/hugeNat、原字NaN及每输出顺序必须保留。所有拟删段未发现版权/许可/作者/来源cue；共同通知、referenceSum的TorchLean doc及d377新增MIT/FiniteProof归属全部保留，不压缩注释或名称。

以上是静态字节、作用域和当前引用盘点，不是形式闭包通过。未改候选/helper或状态，未生成新包，未Git/CI/上传或派agent。Root须在新组合重新核精确引用、逆变换、policy和真实容量，再跑原statement、四spec、内核重放、公理/checksum与完整gate。新组合收益仍UNKNOWN。
