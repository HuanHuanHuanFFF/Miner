# 927 Panel4 原始编译证据审查

**UNKNOWN：实际Panel热机器码未被捕获。C表示检查为GO，当前没有机制负面结果。** 不能把921旧WideRows4机器码、较小的函数字节数或本轮fullPASS补作Panel机器码/性能证据。完整hash、命令、选中符号及逐项边界见[JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-panel-codegen-927.json)。

run40042916169，HEAD `794e4e8444649052b80bb1048465b54206dd8555`，floatlib job120717899237，均success。100/100原件重算长度/SHA一致。官方4b7/public-v2，seed927、25round、500000pairs；Panel9a、batchrow ad323和41控制三个原verdict均full/score/passed=true。这里未审查batchrow机器码，也没有同run2aaa，不能作因果速度比较。

Panel Kernel与原statement保存的compiled source均为229218 B / `9a40118eae28c92c1abeca7f6a141fb0fbfe963cbf40321681b8013782f9f7ac`。其前223584 B与749b wide-backbone父本逐字节相同，只追加5634 B；四个实际入口和spec保持不变。原C、trace、nm和asm来自同一原gate statement输出对象的旁路捕获，未额外重编译。

| 原件 | B | SHA-256 |
| --- | ---: | --- |
| Submission.c | 1215385 | `2c196b4f00a97930a41c33fd09d88caac9c159640b39ede9d8c7cf1e510a62dc` |
| C object trace | 1303 | `fdc9b3d1775abe90a36a40e4aa27586a4067a3538fd7043f634d8cacbc6aebaf` |
| Submission.trace | 19961 | `e5bcbe866dd35485072aa0a12ff031c4ac7180b278cb0502ed33621988f7ae4b` |
| 原对象（仅收据，私有副本已删除） | 547160 | `4380cf302c94965f44a622f9bba1c11fdc9a6baefea1ebe0897e7af083458613` |

原件目录为 [capture-2f02…](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40042916169/download-ed8deed8e3b24ba9ad8148884350f78f/diagnostics/f01-d7-public-suite/public-suite/codegen/f01-d11-panel4-codegen-probe/capture-2f02cef6044b48bfa9184fc265f5fe5d)。helper SHA `eab84afe2dc9d6890576a9fc088e54df0397b5817ba1e249d944a01c4ce53ce1`。trace为Lean4.34.0 commit293d5d0c…自带clang，x86_64 Linux，`-O3 -ffp-contract=off -fdata-sections -ffunction-sections -fPIC -fvisibility=hidden -DNDEBUG -DLEAN_EXPORTING`，完整命令保存在JSON。

## C确认的表示与准备

实际 `Submission_Panel4_wordLoop___redArg` C35579–35775：k分支35633仅一次A borrowed uget，35634–35637取四个Float32标量字段；35638一次F10 borrowed uget。后面四十组逐次mul/add及35772的goto，分支内没有ofBits、Float32 box或constructor。F40仅在终止分支35587构造，160 B标量payload。C路径证明了表示和分配位置，未证明LLVM用了movups、十个SIMD accumulator或无热spill。

`Panel4_packA___lam__0` C36104–36220恰四处 `lean_float32_of_bits`（36130、36141、36170、36197），最终一处 `lean_alloc_ctor(0,0,16)`（36131），四个直接Float32字段，没有临时Float32 box。结合固定header，对应F4逻辑/对齐请求预计24 B；由于缺allocation asm，不把allocator实参当已直接观察。

准备仍包含四次getD原字读取/边界判定和Nat地址运算、default-zero once读取、四次ofBits、panel数组与ofFn closure/callback。packA C36239构造五捕获字段的闭包；不是无准备开销，也没有测得该阶段耗时。

`Panel4_block___redArg` C36275先调用packA一次，36276–36279才创建g闭包并捕获panel，36285遍历全部列组；因此**prepare在g外一次**已由实际C确认。列callback C36249–36255借用panel调用runDot；boxed callback在36264 `lean_dec_ref(panel)`。返回F40只有标量payload，不保存panel指针。

panel所有权被传给Array.ofFn的闭包，可推断正常遍历完成后应释放。但本次没有该库函数实现/汇编或实际连续块调用者，不能证明最终panel释放发生在下一块之前。真实局部生命周期仍为INFERRED/UNKNOWN，不把每次callback的dec误当最终销毁。block尚未接入实际BMM。

## 为什么机器码结论缺失

原nm完整列出真实名字：

- `lp_competition_Submission_Panel4_wordLoop___redArg`：0x339/825 B；
- `…Panel4_packA___lam__0`：0x4b2/1202 B；
- `…Panel4_runDot___redArg`：0x194/404 B；
- `…Panel4_block___redArg`：0x17e/382 B。

捕获器查找的却是 `R11Panel4_wordLoop/packA/runDot/block`。metadata的 `stems_without_nm_matches` 明确列出这些错误前缀；真实namespace是 `Submission.Panel4`。20份asm的函数体全部为旧DirectContinuous/RowStream/Packed10Index，**Panel函数体为0份**。objdump中出现Panel section标题只是未反汇编section列表，不是指令证据。

`disassembly.state=PARTIAL`、28个已匹配旧符号、20个选中、另8个因cap遗漏；Panel首先是名字未匹配，不能只归因于20符号预算。当前单次四lane加载、十acc SIMD、热call/stackspill/heap的机器级结论全部UNKNOWN。旧921的热循环不能替代新Panel。

最小补证是Root在未来新冻结helper中加入真实 `Panel4_*` 精确前缀，保留20cap、旧927原件和所有gate/编译参数，再做一次有界原statement捕获。目标为wordLoop redArg真实回边、prepare lambda与block生命周期，不能用额外诊断重编译对象冒充。

本轮捕获复制为00:08:02.658438–00:08:02.663778 UTC；原日志时区不可确认，capture-vs-axioms为UNKNOWN，observer扰动UNKNOWN。定义/终止与packA_get在完整源中通过编译，四个旧入口通过fullgate；仍缺实际Panel矩阵接线、四十lane等价、原字NaN finish、尾部/巨大Nat后备。**没有Panel算法性能结论或正式准入结论。**
