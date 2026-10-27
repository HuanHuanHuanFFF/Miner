# R7 检查点22：独立低normal求和解码候选

2026-10-23 00:35 UTC。原十小时截止04:22:17、主要源码冻结02:45不变。D继续拥有所有Git/CI/最终采用，当前新CI仍未派发。

**statement-ready：`f01-r7-low-normal-sum-decode`**

- Kernel SHA256 `353d9816425d92fbc6d0cc14c9d30e17fb64d6d4fb7ebdf594700ef02c417c2a`，174914bytes。
- 独立父本`f01-r7-nonnan-runtime`精确c7605688，已有805/807完整通过和809完整回执。仅替换NativeDecodeSum.decode调用及其等价证明，新旧USize/Nat求和循环、终点处理、精确rawNaN回退，以及add/mul/BMM定义都保留。逆变换逐字节恢复父本，见`low-normal-candidate-lineage.json`。
- 使用W13/W13b实际通过的域/rounder/全UInt32 wrapper证明，接入W14b既有表118常量版；最小常量块与W14c编译源仅命名空间不同。源码包括数学参照helper，因此不能将W14b“两个目标模块无once”的结论扩大成整个候选模块无once。实际调用的decoder路径仍待完整C/计时核查。
- 精确新Kernel的Lean、原始完整gate、性能均**NOT_RUN**。7份当前ready的原官方禁词/options/attributes静态检查通过，见`ready-policy-precheck-current.json`。这份新的静态检查原样加载官方pure options函数，未改gate规则。
- 仅这一受控decoder机制，不与3d9单遍NaN求和合并，不动标量decoder。R建议D在授权及现有吞吐内作statement检查后再决定配对fullgate；不要求增加runner或扩近邻网格。

W14c已回收：ZIP7d0825db/report18756258，60 manifest+CRC通过；公开60f追加8192深度常量块的完整宿主`65a78403229b21528d88964fdd05a381802f9ec2f43859b8e77ecd8249daf806` /155871bytes，普通Lean/四spec准确类型/同VerifyFull合取/公理/静态policy通过。不是完整gate。默认深度失败、10000原件和静态加载先缺loguru失败都保留；最终只用8192，未放宽官方上限。报告按钮两次超时，独立报告从已下载原ZIP复原到E盘，并核网页公布SHA；receipt明确这一来源，不假称另一个下载通道已成功。

当前22组网页原ZIP/report共44主文件在E盘，索引`web-deliveries.json`。新增候选仍只在本地，未发送到网页。

00:34 UTC启动W13c，10分钟目标00:44：只把既有公共数学helper组合追加到原公开60f宿主，验证新表常量版的全UInt32 convert等式与原四spec；不改公开宿主四个entry、不含本地353d/3d9源、不做C或计时。这是补公共片段的组合编译缺项，结果不能继承为本地USize候选完整通过。下一节点00:50 UTC。
