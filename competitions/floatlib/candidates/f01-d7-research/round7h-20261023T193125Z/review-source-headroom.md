冻结基底是[1b71 Kernel](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d11-bmm-fused-output/Kernel.lean)，SHA `1b71f67ee1cb154399e60a0657618c4b968d8e4b4d642cfc0621fdf416811792`，244998 B，现有余量11002 B。可用一个保留spec重接方案净释放 **9441 B（9.22 KiB）**：投影大小235557 B、余量20443 B。这里只量取和列方案，未生成精简包、未修改候选；Lean依赖闭包及完整gate仍NOT_RUN。

以下行号全部属于精确1b71。每段完整、可唯一匹配的起止原字符串、半开byte偏移、原段SHA和删除条件在[JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-source-headroom.json)；不能用重复的裸namespace/end锚点定位。

|段|原始行|完整范围概述|字节|删除后必须处理的引用|
|---|---:|---|---:|---|
|P1|5670—5785|`namespace Packed10`（紧接`def tileResults`）至配对`end Packed10`；tileResults/tile_finish/inlineDecodeC/outputFromTiles/core及证明|4977|bmmR4、RowOutput.core及RowStream.core_eq均依赖旧Packed10.core，必须与下面段一起处理|
|P2|5787—5805|`def bmmR4`至bmmR4_spec最后`(referenceBmm_spec batch m n p A B)`|824|保留外层5808的end Submission；当前bmmPackedBase_spec仍引用bmmR4及bmmR4_spec|
|P3|5906—5970|完整`namespace Submission.RowOutput`至配对end；row/output/output_eq/core/core_eq|2479|仅旧bmmRows/spec消费该命名空间；新fused RowStream已不调用RowOutput.row|
|P4|5972—5996|含`def bmmRows`的完整Submission重开块至配对end|890|bmmRows/spec在块外没有文本引用；本源没有bmmRowOutput这个名字|
|P5|6203—6208|RowStream内`theorem core_eq`至`(Packed10.core_eq_reference ...).symm`|289|仅存活bmmPackedBase_spec:6232调用；保留更强的core_eq_reference:6185—6201及6210闭合|

推荐B为以上五段一起删，共9459 B；唯一存活spec重接是[bmmPackedBase_spec](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d11-bmm-fused-output/Kernel.lean:6222)。其接口不变，只做四项：6226局部h的右侧bmmR4改referenceBmm；6227只unfold bmmPackedBase；6232调用RowStream.core_eq_reference；6234改referenceBmm_spec。原proof文本547 B，所列新文本565 B（增加18 B），所以净释放9459−18=9441 B。这保留原空输出/n=0两个split，else直接用已经在基底中的reference等式，再对Vector.get作congrArg；不是重新设计规格。实际新proof还没有Lean验收。

只删除P3+P4的A方案无需重接存活spec，但只省3369 B，大小241629 B、余量14371 B，不够8 KiB目标。推荐B按“少改存活证明”取最小结构方案，不主张是所有可能子串删法中的数学最小值。当前旧链既有运行定义又被proof使用，不能因最终运行入口未调用，就整段删掉而不重接。

当前实际运行仍为最终bmm→原DirectRows/DirectSmall或bmmPackedBase→新RowStream.core；推荐B不触及这些定义。当前存活proof绕经bmmPackedBase_spec→bmmR4_spec→旧Packed10.core_eq_reference，以及RowStream.core_eq→旧Packed10.core；推荐方案用已有RowStream.core_eq_reference直接连referenceBmm_spec，外层bmmBeforeDirectRows_spec、DirectRows.core_eq和最终四spec保持原接口/原字节。删除helper规格是bmmR4_spec、bmmRows_spec及旧物化core/output等式，不是删官方义务。

五段删后、重接前，余留相关代码引用精确只有6226/6227的bmmR4、6232的RowStream.core_eq及6234的bmmR4_spec，正好由四处proof替换处理。旧tileResults/outputFromTiles/inlineDecodeC/RowOutput/Packed10.core家族无其余被搜索到的文本引用；这是引用盘点结果，不是Lean解析器或内核证明。818、852、1186的bmmR4属于历史来源说明，必须原字保留，不能当作悬空Lean符号删除。五段中未发现作者/版权/许可证/来源归属cue。

若组合仍缺空间，可在B后另省2837 B：O1旧decode_bounds完整namespace（5515—5542，869 B）；O2 groups_pos_of_col和column_decomposition（5304—5311，192 B）；O3未被消费的lane_zero别名（5293—5294，75 B）；O4 finish_eq_fold与finish_eq_kernel_fold一并删除（5463—5482，1006 B）；O5 finish_dot10_lane_fold（5499—5510，695 B）。这些原引用均局限被删链或同组wrapper，完整独特锚点亦在JSON。B+全部O净省12278 B，投影232720 B、余量23280 B；未需要前不扩大删除范围。

必须保留：F10/lane/packet/update/groups、vector_get_ofFn、packB/packB_lane、nativeA_getD/dot10/dot10_lane/finish/finish_eq_dot/finish_dot10_lane；新group_prefix实际调用后两条lane桥。zero10与lane_zero10不是可随lane_zero别名一起删的无用物：finish_dot10_lane:5495仍用lane_zero10。Packed10Index整体也不能删：新runDot仍活动，而且stepNat/next_decreases还被NativeDecodeSumWord和实际SinglePassSum消费。index_address、NativeFinal.dot_eq及新RowStream的所有前缀/参考等式要保留。

Root后续只在新候选内整合，先按真实跨batch组合重新盘点名字消费；该组合可能引入本清单现在看不到的新依赖。核对精确逆变换、保留的运行/作者说明字节、实际UTF-8大小与现行policy后，先statement，再原版四spec/重放/公理/checksum完整gate。原1b71:6191的GetElem桥接风险不因本清单消失。本清理只解决源码容量，不给运行加速结论；新组合的成本仍需完整同runner对照和冻结后独立确认。未运行Git、CI、builder、新agent或工具链，且未生成任何新Kernel。
