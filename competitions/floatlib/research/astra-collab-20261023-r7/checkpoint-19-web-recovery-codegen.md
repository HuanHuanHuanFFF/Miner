# R7 检查点19：W11完整回收与标量ABI边界

2026-10-22 23:42 UTC。截止04:22:17 UTC不变；W12c正在公开旧60f上验证最小闭包接入，目标约23:47。D已接收61d最小块及ec36替换；R唯一单遍sum当前3d9b1ea9、statement-ready但Lean NOT_RUN。

W11完整原ZIP已恢复并保存`E:\Download\R7-W11.zip`：8798280bytes/SHA256 `18cec34b9ac33146e9144fb7dd7e31d49891b5355a0c7bc7501204464eb7b7f7`。独立report `0db1d42f...`。15片base64严格解码、范围连续、每片原字/文本哈希、总ZIP哈希、CRC、590个payload SHA及JSON manifest字节数全部核验。首轮接收器未识别无扩展名SHA256SUMS，生成CRC-only回执（manifest0）已保留为`receipt-crc-only.json`；补识别后当前`receipt.json`明确590，不将早期0当完整验收。原件没有修改。

全部原始592成员110350503解压字节留在`web/R7-W11/original-extracted/`，无ELF/对象/olean/工具链二进制。为避免将110MB文本证据无意纳入轻量交接，这一完整解压树和本地复原ZIP已在R的web/.gitignore中忽略；E盘原ZIP完整保留，D在同一机器仍可全部读取。729246bytes精选原件在`web/R7-W11/reviewed-evidence/`，复制逐字节相同，完整来源/哈希见`w11-codegen-audit.json`。未删除任何原件或分片。

R独立核对的代码生成事实：

- 实际MainFull closure指向本地lambda的boxed wrapper。add裸符号238bytes，mul两个入口各884bytes，wrapper各116bytes；原始nm与JSON一致。计分suite逐元素循环`BenchSuite.c:8443`仍`lean_apply_2`，没有把算术整体并入遍历循环。
- **boxed ABI不等于每结果堆分配**。实际ELF64、同哈希lean.h的UInt32 boxing为立即数tag；MainFull add wrapper真实反汇编用两次右移解码、`lea 1(rax*2)`编码结果，无heap allocation call。通用引用计数冷分支存在，但有效UInt32输入是tagged immediate。不能据boxed函数名声称此处逐元素分配对象或估算可省堆成本。
- 实际native add/mul转换调用及跨decoder调用的FP栈保存仍存在，见原报告、MainFull asm/relocations。只给结构事实；不把静态callsite/函数尺寸当动态次数或耗时。
- W11是固定源独立远端对象，实际CI timed object身份NOT_VERIFIED；完整VerifyFull/benchFull链接两次超时，fullgate和性能NOT_RUN。网页30分钟超25分钟交付上限偏差原样保留。

当前E盘共16组原ZIP/report、32主文件，索引`web-deliveries.json`。W12b数学quiet结果仍遵守真实NaN优先级；R继续检查单遍sum证明与普通路径成本，不因有限模型或网页证明声明性能获益。
