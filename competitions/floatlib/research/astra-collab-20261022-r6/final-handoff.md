# R6 研究交接

截至2026-10-22 14:48 UTC（北京时间22:48）。共同窗口13:17:45—14:47:45已结束；R研究与原件交接完成，720已启动验证仍由D继续自然完成回收。目标“新冠军”尚未达成。R只修改本轮research与f01-r6-*；D独占Git、CI、整合与最终采用。没有正式参赛上传、注册、签名或资金动作。

## 已验收与否决

| 路线与精确源 | 实际验收 | 性能与决定 |
|---|---|---|
| 两比较normal-add，8a0e40fb |706旧12类25轮完整PASS；719新public-v2/26cells/25轮完整PASS |旧整包归一化新/父本0.999081，新公开计划0.997005；未建立稳定或明显整包收益 |
| 低乘法删重复守卫，75ddbcff |706完整PASS |旧整包1.001941，未见采用优势；保留product界/外层finite证明 |
| normal乘积最高位46/47，96865cba |707完整PASS |乘法归一化1.238717，整包1.136938，明确停放 |
| 偏置舍入与直接打包，998747fa |707statement失败；D组合c18748c6在719同样失败 |常量、模回绕、分派/let展开未通过；无性能结果。756c2332是NOT_RUN修复草稿，按D08停放，不在本窗重开 |
| gap26加法吸收，dcfe0c8e→65cd1338 |707原稿仅最终两条接口rewrite失败；65cd1338只改这两条，已入D720新公开suite |720结果待回收；不能提前写成通过或加速 |

完整SHA/字节见各manifest与handoff-source-identity.json。三份通过稿均核对原obligation、Submission/VerifyFull重放、三允许公理、精确源、实际逐类计时。失败原件、慢样本及网页最初NOT_RUN状态全部保留。证据入口：first-full-results-706.json、full-and-failed-results-707.json、public-suite-719.json。

## 本轮改变下一步投入的证据

官方在窗内发布a0e80de的新suite。旧十二类占比与旧冠军推算链不能跨suite继承。719实际public-v2哈希a16494e9、公开plan哈希7b38aa4c；按真实cell_work加权，8eb当前包计分占比为：add18.3088%、mul21.5198%、sum10.8137%、bmm49.3577%。这是一个公开计划的观测，不是私有paid-suite分布或保证。

主要耗时cell为bmm:specials17.1062%、bmm:ml12.1784%、bmm:extremes7.3192%、sum:specials6.6479%。下一窗口应继续用“实际耗时份额×有证据的可实现降耗”筛选完整成本路线，特别区分NaN/Inf回退与一般矩阵成本；本窗没有因这些读数另开方向。报告cell的ns已按工作量归一化，必须乘实际cell_work才可合计，脚本已与官方headline逐项核对。

## 数学产物与确切缺口

- 已验normal区间守卫把运行时比较与finite证明合并；已验24位尾数乘积界消掉LowScale重复宽度/特殊值守卫。生成C确认改动实际可达，减少检查仍不等于收益。
- gap26路线把公开FloatLib原gap39吸收证明收紧，保留异号二次幂边界；gap25无条件放行有具体反例。最终接口修复实际结果仍由720决定。Finite oracle与全输入Lean验收分列。
- 偏置RN-even的数学公式、两次机器加法无回绕界、23个固定shift证明脚本及真实失败目标均已交付。修复草稿没有被宣传为已证明。
- NaN研究是有条件的证明储备：普通sum后续sNaN可替换当前qNaN的sign/payload；点积右项先经过mul后可能支持qNaN吸收，FMA不能套用。W03给真实Spec条件桥和有序fold归纳，但roundDyadic/nativeOverflow等非signaling分类与实际Packed10.finish接线未闭合，NOT_RUN，不能采用。nan-bridge-remaining.md指出已有公开NaN-decode和zero分类引理，避免下一轮重复查找。

## 网页6 Pro原件

两路并行推进期间，R同步写候选、核对源码与处理实际CI错误；共回收四次网页交付，没有悬挂job。当前E盘文件：

| 包 | ZIP SHA256 | 包内清单核对 |
|---|---|---:|
| E:/Download/R6-W01.zip |3985ff760310a260da99dd387c18865a3c10faaece61b35082cb9a92e62aae1e|23|
| E:/Download/R6-W01b.zip |eca6a3228c975dd55331d314df3e6c7966867c5dce27d2b64cac63d379abc55d|24|
| E:/Download/R6-W02_Absorption26.zip |b988f1119801319dd3a15b50cd81040f6c7cf286d2ee7c3737157a5c1da9e332|43|
| E:/Download/R6-W03.zip |c640ad6f55a299e90636a7d839cf74252adfad86b7258657610ed9509d8979de|13|

对应四份报告也在E:/Download；完整文件名、字节、SHA/CRC、提取成员在download-index-final.json及web各receipt。旧R2-R5十二ZIP已由此前12:20维护展开清理，当前376成员按materials/20261022/manifest.json再次核验；不声称旧ZIP仍在E盘。所有本轮原件未覆盖。

W03第一次发送因自动审批判定项目细节敏感而被拒绝。R去掉全部项目上下文，仅使用匿名核验的公开FloatLib定义，缩小后的请求已成功并完成回收；没有绕过审批或遗留阻塞。

## 验证、权限与剩余

14:39本地根自检PASS，覆盖两赛道、139份FloatLib候选哈希、11个手动工作流及路径；本轮13份候选的精确字节与四ZIP/四报告另行核验。它们不能替代Lean或计时。R没有切分支、暂存、提交、推送、派发/取消CI；其他会话文件和旧dirty内容保留。

720/39796984460是已经启动的父本与absorption26-proof2新公开suite验证，D负责自然完成、完整原件与平台终态回收。截止前14:46:45的GitHub插件返回artifact空列表，job仍在exact-gate步骤；14:47:58本地尚无该run完整原件，未推断其通过/失败。R已交齐自己的四份网页原件及其余回执，不启动新研究，720结果由D在其当前状态入口归并。私有suite及现任冠军直接配对结果仍UNKNOWN，未作正式提交，不能因公开参考提速或局部证明通过声称冲冠成功。
