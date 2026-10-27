# Tight/literal RSE：数学条件闭合草稿，当前输入机会小，低优先级储备

完整源 `Kernel-tight-literal-rse.lean`，250,492 B，SHA256 `bb51244607512ca3fa1f6a4456f44cf4b538885142e2b76f61b690ad9c191676`。精确替换片段 `TightLiteralRSE-fragment.lean`，文件SHA `a488dd21c0464aea9f98b11c60864afe3a1bc8d342a79a8d03bc65270e424940`。当前清单为 `tight-literal-rse-manifest-v2.json`；v1保留，其fragment哈希指去掉末尾LF后的插入块，v2明确区分原件／插入块，完整候选字节未变。

## 原规格上的紧界

对非零product，`product<2^width`蕴含`fastLog2 product<width`。因此给出 `width+scale≤172` 即有 `leading+scale≤171<172`。另保留scale<149，原roundP必走同一个右移subnormal分支；原roundLow里的zero及fraction==0x800000（进位到minNormal）不动。

新引理 `LowScale.roundLow_eq_tight` 明确量化任意UInt64 product/scale和Nat width，假设为上述三个条件。零product单独沿原分支处理；其余复用原 `Nat.log2_lt`／`FastMul.fastLog2_eq` 以及同样的UInt64.toNat_add无回卷证明，没有新RNE公式或公理。

只在原完整guard `p<2^48 ∧ scale≤123` **拒绝后** 加三个分支：

| scale | 必须保留的product界 | 运行调用 | 固定右移 |
|---:|---:|---|---:|
|124|p<2^48|roundLow sign p 124|25|
|125|p<2^47|roundLow sign p 125|24|
|126|p<2^46|roundLow sign p 126|23|

其余回原FastMul.roundP。旧roundLow和旧≤123证明逐字保留；逆向替换完整新块可逐字恢复df5c。源码只改LowScale.roundSelect及其证明；除了scalar低分支，BMM raw replay也会调用Submission.mul，因此不宣称BMM耗时必然不变。

不能只把旧hs123改成125。本子agent模型保留三个域外反例：

- scale124,p=0x1000002000000：原0x00800001，错误无界Low为0x00000001（通用UInt64参数反例）。
- scale125,p=0x800001000000：同上。
- scale126,p=0x400000800000：同上。

根另有真实可分解mantissa的125/126反例和912项独立边界检查，入口为本轮 `astra-tight-rse-boundaries.json`；本稿不把父级汇报当Lean验收。

## 最小真实域调查与成本判断

`tight-rse-screen2.json`为当前证据；初版原件与一次脚本生成失败stderr均保留。三个已见D计划每个mul case取512个确定性分层样本，共64,512对；另3,120个精确整数rounder边界／随机检查通过。第二次实际约0.409秒，外部5秒终止上限实际执行。模型、源码与本源Lean状态严格分开。

| 已见run | 每组mul样本 | 新增非零命中 | 三scale上的零product |
|---|---:|---:|---:|
|40129155932|21,504|9|322|
|40152158687|21,504|31|37|
|40155753018|21,504|23|112|

subnormal主类在三组样本均没有新增命中，大多数非零低尺度调用已落原≤123。新命中主要是少量dense/sparse/specials/extremes边缘，不是一个新的大计分域。各cell真实whole份额已按cell_work×submission_ns保存在JSON，但这些稀少命中的实际耗时份额 **UNKNOWN**，不得由样本比例乘cell成本宣布收益。

零product已有原roundLow／roundP的早退；本项不会省它log2/RNE，而可能给这些旧便宜路径添比较。是否被CSE或编译器布局抵消也UNKNOWN。125/126拒绝product界的输入要支付新增guard后再回原roundP，完整D必须覆盖其成本。

## 历史与采用决定

已查RESULTS、R14/R13记录及候选Kernel的124/125/126紧界接线，未找到同一实现的真实失败D；这只是限定检索结果。`f01-mul-rse-threshold`是另一条RNE阈值公式，39558841465声明失败、无性能，不是本三scale分支，也不重用它。R14全整数mul/bias失败仍独立保留。

建议 **低优先级储备，不凭当前覆盖新增D队列**。已完成一份完整可验源供根选择，是因为证明只增加原roundLow_eq的参数化小扩展；这不代表当前经济性足够。若根决定测试，先精确声明／公理检查，再对该精确组合做自己的原gate和首次D。不得继承cb7或cutoff84的结果，不相加组件收益，不换名/seed重挑。

全源Lean、完整gate、实际C/asm及性能全部 **NOT_RUN/UNKNOWN**。未操作Git、CI、本机编译或正式提交；837341a5和所有旧源保持不变。
