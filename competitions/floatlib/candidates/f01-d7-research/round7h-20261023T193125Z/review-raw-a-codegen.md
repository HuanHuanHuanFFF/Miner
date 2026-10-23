902的精确c477新guard路径，**在machine-bound检查成功时确实不再做全局nativeA map**。新热循环C没有每MAC Float32装箱，仍有每k一次raw→native转换；旧输出物化、闭包与div/mod还在。关键缺口是新RawA/RawIndex函数虽在nm中，14份汇编没有它们的实际指令，不能据capture状态声称新循环SIMD、spill或foreign-call成本已确认。

原件绑定：run40014284237，HEAD `6eb257b2e079c5778558af5151d852d70f9f3301`，floatlib job120622239018；902请求/public-v2/4b7一致。候选、artifact input和compiled-Submission.lean逐字一致，SHA `c477e8078eef66255f1c750b46575fc987144717eb1bffc943cf58a514755a6a`，244077 B；parent本地及902 input均为a066/237142 B。已逐字重哈希27个相关归档成员并匹配original-artifact-hashes.json；capture metadata与nested summary互相绑定。原fullgate verdict确为passed、score、exit0、seed902；这是带observer的discovery，不是独立确认或采用。

实际C为[file-0-Submission.c](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40014284237/download-c940aee00b7a4cba8cc126b8221c5140/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-raw-a-one-group/capture-f7033b9431be4eebb7fd3a8be8002b30/file-0-Submission.c)，1394349 B，SHA `e4596dd8d44e7dcda0971d28ca022a420681e27ac585ece0155664e4bdf14850`。原statement object记录SHA `04746ef716b7c7a9db23047eb81f97bd64f1b9c72405af194e4f2a9543b7d1bc`、560344 B，现已按设计清理，不能再对payload重哈希或补反汇编。trace记录Lean4.34.0、clang -O3与ffp-contract=off。本报告使用nested原gate捕获，不用外层8eb诊断C替代；也不把statement对象冒充另行核过的最终计时binary/链接产物。

[最终bmm C](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40014284237/download-c940aee00b7a4cba8cc126b8221c5140/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-raw-a-one-group/capture-f7033b9431be4eebb7fd3a8be8002b30/file-0-Submission.c:42363)先判断4<n、2<p、p≤10，再直接调用R11RawA.core。Core:42276—42340只建行号Array、packB并进fold，没有nativeA map。runDot已在C的group callback:42117—42193中内联边界检查；成功在42172直接调用R11RawIndex_loop___redArg，不经装箱loop wrapper。但42184的机器界限失败后备明确仍对完整A作map再走Packed10.dot10；其他形状还可走原RowStream。因此只能说新成功路径去掉map，不能无条件说外层形状guard内所有路径都没有map，也没有此次各case实际分支计数。

[新raw loop](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40014284237/download-c940aee00b7a4cba8cc126b8221c5140/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-raw-a-one-group/capture-f7033b9431be4eebb7fd3a8be8002b30/file-0-Submission.c:41812)使用size_t索引与十个float累加器，41849/41850每k借用读取一个raw A字、unbox UInt32、调用一次lean_float32_of_bits，再共享给十对mul/add。循环体没有lean_box_float32、Nat div/mod或closure allocation；41820的40 scalar-byte F10构造只在终止返回分支。nm存在的___boxed wrapper不等于热调用走它。原输入仍是Array中的UInt32，输出Array也仍需UInt32包装；不能把这些称作每MAC新float装箱。primitive内部与新机器码层的分配/寄存器情况没有被本次asm覆盖。

注意收益机制边界：3≤p≤10使groups=1，普通非空且machine-bound成功时，新路径与旧全局map都对每个A字转换一次。省的是nativeA中间物化和独立map遍历，转换被移进MAC循环，没有“少十次转换”。旧map C:39695—39722每字调用of_bits和box_float32；旧RowStream C:40865仍实际调用它，且[旧路径asm](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40014284237/download-c940aee00b7a4cba8cc126b8221c5140/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-raw-a-one-group/capture-f7033b9431be4eebb7fd3a8be8002b30/asm-0-12.txt:648)保留map调用。该旧路径是c477对象内保留的a066源码机制，未捕获902独立a066 binary的汇编。

|仍存结构|精确C证据|能否确认新路径机器码成本|
|---|---|---|
|行号Array、packB|42282、42302附近|C确认；新core asm缺失|
|每行r/m、r%m和groups除法|42217、42218、42235|C确认；是否机器码提取/化简UNKNOWN|
|group closure、rowTiles Array|42225、42237|C确认；实际分配消除UNKNOWN|
|原RowOutput.row闭包/行Array、append|40349—40359、42240、42243|C确认；完整调用成本UNKNOWN|
|每输出j/10、j%10、lane分派、finish|40173、40174及后续分支|C确认；新输出helper未反汇编|
|原isNaN/原字NaN回放|Packed10.finish:38803—38813|源/C保留；未新增NaN策略|

[nm](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40014284237/download-c940aee00b7a4cba8cc126b8221c5140/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-raw-a-one-group/capture-f7033b9431be4eebb7fd3a8be8002b30/nm-0.txt:240)确有RawA_core（0x318）、RawIndex_loop___redArg（0x122）、runDot及私有rowfold。capture选14符号、上限20，STEMS未包含R11RawA/RawIndex；私有fold名字还不满足Submission_前缀。逐份解析真正的`地址 <symbol>:`指令体后，新RawA/RawIndex覆盖数为0。objdump文件里出现的`Disassembly of section .text....RawIndex...`是空标题，不是新函数机器码；这正是不能只grep名字或采信COMPLETE_SELECTED_SYMBOLS的原因。

现有asm能确认两点。[旧Packed10Index内层](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40014284237/download-c940aee00b7a4cba8cc126b8221c5140/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-raw-a-one-group/capture-f7033b9431be4eebb7fd3a8be8002b30/asm-0-11.txt:469)将十处C unbox_float32合并为一次A float load+broadcast，并用3组mulps/addps处理4+4+2lane；backedge无调用，退出后才分配F10。因此不能拿C的十个unbox语法点宣称新路径省十次机器解码。[同对象NativeFinal.dotLoop](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40014284237/download-c940aee00b7a4cba8cc126b8221c5140/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-bmm-raw-a-one-group/capture-f7033b9431be4eebb7fd3a8be8002b30/asm-0-8.txt:475)中of_bits确实为PLT调用（另见515），并有栈暂存；这给新raw loop每k of_bits调用/累加器spill提供了具体疑点，但它不是新loop机器码，结论仍为INFERRED/UNKNOWN。nm大小0x122对旧0xcc也不能换算时间或证明失去SIMD。

最有判别力的下一项是：在Root下一次opt-in原statement discovery里优先捕获确实存在的`lp_competition_Submission_R11RawIndex_loop___redArg`实际反汇编，保持源码和gate不变，直接看of_bits是否每k调用、累加器是否围绕调用spill、十路是否仍有mulps/addps。当前对象已清理，现有artifact不能补出这些指令。若未补齐，不应先根据C大小/包装函数数量再造算术变体。捕获结束早于reader观察到score不证明无观察者扰动；capture_vs_axioms_emission原记录UNKNOWN，正式性能确认应关闭捕获。

本次只写review-raw-a-codegen.md/json；未改候选、helper、adapter，未Git/CI/上传、未读取904/905输入。完整原件SHA、函数段SHA、nm/asm覆盖及证据分类见同名JSON。
