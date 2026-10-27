# R7 检查点17：canonical image 与单遍 sum

时间：2026-10-22 23:12 UTC；原截止04:22:17 UTC及02:45源码冻结不变。已读D16/D17。

- W12网页已完成：报告无条件ofFloat32 add/mul闭包、CanonicalImage实际运算闭包、真实sum/dot/BMM及rawNotNaN布尔桥，固定Lean编译、公理检查通过。正在回收并复核原件；不将网页报告等同官方gate。
- W11网页已完成：精确公开60f的Submission/MainFull/Bench/BenchFull/BenchSuite真实C及clang-O3对象文本；MainFull scalar closures仍通过lean_apply_2/boxed ABI。完整链接两次超时，fullgate和计时NOT_RUN。网页用时30分钟，超过要求25分钟，保留偏差。下载首次45秒超时，E盘未出现文件，检查状态后重试。
- W10/W10b已完整回收：当前13组ZIP/report共26文件。W10证明正文仍有attribute命令，尚不是policy-ready候选；W10b实际C把normalizer负零分支的常量初始化调用消掉，但没有性能结论。
- R接手D17单遍raw-NaN感知sum，D拥有BMM冷扫描和scalar路线。R不另做BMM候选。先准备一份受控sum，不扩参数网格。
- 可降低普通路径额外比较的具体实现判断：现有R2 decoder本就判断`0x0bffffff ≤ magnitude-1`及`magnitude < 0x7f800000`；尝试复用这两个分支，只有高端非有限冷路再区分Inf/NaN。low-gate false蕴含finite需要UInt32模减法证明。普通路径最终实际比较/调用成本仍须C/完整gate检查。
- canonical-image-oracle.json：100000 canonical-image操作、3500 sum+3500 dot有限trace未见反例；原始任意NaN/seed不满足像闭包的反例保留。有限模型不是全域证明。
- cold-scan-cost-807.json：计分BMM671个all-input-nonNaN NaN输出；旧完整回放7551步，但quiet-stop后仅2412算术prefix步。冷扫描需15102原word读取，另外2189个拒绝输出先扫9533words。不得把7551全部当新扫描相对quiet路径的可省成本。事件当前两个raw operands均非NaN可覆盖728输出，但尚非独立候选或收益。
- 810仍本地准备、未推送/未派发；无CI在运行。D已向用户请求具体公开目的地和载荷授权，不重复询问，不上传私有新源码到网页。现有5份proof2 ready列表保持不变，供授权后的D统一验证。

下一节点23:30 UTC：核对W11/W12原件、公开依赖及增量定理接口；开始单遍sum数学/本地构造。当前新冠军目标未达成。

23:18 UTC交付追加：

- W12已下载到E:\Download，ZIP `47576c2e...` / report `5049e749...`，182 manifest逐字节与CRC通过。`web/R7-W12/original-extracted/R7-W12/R7W12.lean` 精确 `6baa0a80...`；新增完整增量 `R7W12Increment.lean` 精确 `d907d96b...`。实际成功日志及269声明三公理审计已读取；有保留linter warnings，无编译错误。
- **D可直接取 `canonical-image-minimal-block.lean`，12744bytes，SHA256 `61d49494b764bc433312202f3928a3dc6986eb91f4f64d2fb309ccf7370e0aed`**。插入Submission命名空间、已有R7Native/NativeBridge之后；若文件尾追加需自行包namespace Submission。仅W05实际分类/nativeNaN必要桥及W12首namespace，提供无条件`R7W12.ofFloat32_add/mul`和反方向。无W01/W02/W03依赖，无fold/运行新候选；不要与同名W05/W12重复定义。来源、映射、精确依赖见同名JSON。网页原完整源PASS，这份最小映射尚未实际编译。
- **替换810的a4探针**：W12实际复现数值8/23位宽rewrite不匹配。新`f01-r7-canonical-bridge-probe-policy2` SHA256 `ec36b4dab8134847885a0f7666e834a8c7dba55dc3ed2c7dac06fd88ed26cad7` /193359bytes，仅改成真实格式字段位宽，静态policy PASS；精确映射候选Lean NOT_RUN。旧a4保留，不再作为当前ready。
- W12b约23:15 UTC已启动公开decoder分支/单步闭包增量证明，15分钟目标；未发送私有候选。W11 report成功下载，但ZIP及首分片按钮都未产生下载事件，原件仍在网页、回收继续；不虚报完整回收。
