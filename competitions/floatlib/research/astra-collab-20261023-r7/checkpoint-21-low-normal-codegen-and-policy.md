# R7 检查点21：低normal全域decoder与消除once/FP spill

2026-10-23 00:20 UTC。已读D21；完整目标构建超时不等于已进入链接阶段，W11原报告保留，现行交接按D核实边界。仍0新CI，公开推送待用户具体授权；截止04:22:17、源码冻结02:45不变。

原件现已收齐21组ZIP/report共42主文件（E盘及当前web-deliveries索引）。新增结果：

- **W13**：ZIP473d7809/reportd4c7e8c3，83 manifest+CRC PASS；完整数学源a17d9041，最小增量55ce4272/14224bytes。实际Lean对原指数1..23、两sign/全部fraction证明`tableProduct(u+0x10000000)*ofBits0x2f800000=ofBits u`和完整bits=u；真实rounder/codec已关闭，60声明三公理审计。e=0反例实际通过，原范围不扩大。
- **W13b**：ZIP0f9e063e/report6d92dda9，57 manifest+CRC PASS；完整b1e06099，增量f7d2cd47/5624bytes。补全新分支条件与LowNormal双向等价，实际wrapper对所有UInt32等于原R2convert/Float32.ofBits，bits只与原convert相等（不对NaN写bits=u）。29声明审计/5次编译均PASS。
- **W14**：ZIPb04da757/report70976a31，143 manifest+CRC PASS。初版实际C/clang-O3低normal常规路径去掉输入of_bits调用，但once状态检查和acc保存/恢复仍在。这个否定结果保持不变；未运行目标对象计时，有限见证只是Lean --run。
- **W14b**：ZIPc2dd7922/report13b5e243，201 manifest+CRC PASS。固定表第118项以`(u-u)+118`为索引，普通Lean证明全u恒等原2^-32常量及helper；实际clang消掉整数恒等式开销，读取固定偏移。新增常量once cell/状态检查/cold引用消失；小Nat低normal loop路径也无call/FP栈保存恢复。其他fallback/Nat慢路/Float32 boxed adapter成本仍在；ordinary局部loop机器码改变，不能认定普通路成本不变。原control函数代码bytes/归一relocation相同。**无性能百分比或完整gate结论。**

数学与C helper表达式已独立对齐，见`low-normal-assets-audit.json`；它保留W14当时NOT_PROVED的原报告，不回写历史。W14b的常量替换是一次由实际once/FP spill触发的修订，不是扩参数网格。

发现并处理的接入阻碍：W14b `ConstantSource.lean`实际用了`maxRecDepth 10000`；官方4b7静态options最高8192，默认深度首稿确实失败。因此**不能原样进入竞赛候选，也不把删掉选项当已编译**。00:19 UTC已启动W14c五分钟复核：只将深度改8192，追加到原公开60f完整宿主，实际编译/原四spec/公理/静态检查；不改变算法、不重跑代码生成，不使用私有新源。若8192失败则保留具体缺口，不能上调超过官方限额。

后续只准备一份sum decoder受控候选，以已完整通过c760作为隔离参照，仅更换NativeDecodeSum.decode，add/mul/BMM原定义保留；先等资源上限复编译，再完成精确组合/静态/源身份检查。它独立于3d9 rawNaN单遍sum，不立即拼接两种新运行机制，也不要求D扩大CI队列。是否完整计时由D在授权与现有优先级内决定。数学和机器码路径改进仍不足以证明实际加速。下一检查点00:35 UTC。
