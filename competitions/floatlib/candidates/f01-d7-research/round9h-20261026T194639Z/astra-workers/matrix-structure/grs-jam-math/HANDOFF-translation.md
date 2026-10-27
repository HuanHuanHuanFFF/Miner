# GRS jam桥：新增偶平移与缩放，均NOT_RUN

`JamTranslate.lean.inc` **3400 B**，SHA **c9e0cfb3b59f7eb45f8c5cdc281eb54b4598b080c2c43aae100e04df12237542**。依赖冻结a78变量jam源（3477 B，未改）；8个新自然数定理，无运行定义/占位证明。D>0且X偶时关闭加法平移；减法另取m≤X*D，用商借位与余数D−r，再按q奇偶闭合。唯一omega仅见X/q，完整D*q块用div/mod/分配律消去。

关键尺度：d≥4取δ=d−3、D=2^δ；`jam(8b,2^d)=jam(b,D)`。原共同尾数整数`P=a·2^d±b=(8a)·D±b`，故运行纸面的`T=8a±J=jam(P,D)`。接变量RNE时右移量是 **(d−3)+k**；不能误用d+k。详`TRANSLATION-NOTE.md`，有确切API与8根名单。

纸面加减/尺度分解成立；有限公式检查无差异，保存X为奇数时的必要反例；**Lean、typed运行桥、公共ADD、C/性能均NOT_RUN**。接下来仍缺leading/k、UInt32大移位分支、小T与原Model.add字段/符号桥；不扩公共源码、不抢槽。`translation-check.json`记录范围与精确哈希。

阶段00:39:41—01:04:41 UTC有界，提前完成可复用片段。00:50读D状态：40428306094/a92abea/1927011正在跑，含c598对应dual-equation诊断；尚未据此宣称任何proof结果。c598真实目标优先抢占回Dual。R总截止02:28:21 UTC不改；本方没有Git/CI/本地Lean/跨域写入。
