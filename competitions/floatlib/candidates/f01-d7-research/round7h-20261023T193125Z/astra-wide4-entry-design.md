# 4×F10 接线的最小设计（非新Kernel）

当前唯一冻结探针eb9e保持a066整个前缀不变；机器码尚未返回。投影资产astra-wide4-projection.lean只准备从实际40参数USize循环到既有Packed10Index.loop的逐行等式，未编译。四个projectRow各10lane覆盖40条原有序MAC，循环内没有假定B读取等于某抽象预言机；uget索引与现有机器循环一致。

## 精确证明链

1. wordLoop_row：实际wordLoop投影等于已有单行机器loop；四个真实A基址界、nativeA.size<USize和count=n都是明确类型前提，给出索引加法不回绕与uget合法性。
2. 以40个Packed10.zero32启动，投影为10个原zero32；用已接受Packed10Index.loop_eq连接原Packed10.dot10。不得将证明用projectRow拿来为每个输出新建F10对象；运行输出用直接F40字段选择。
3. 使用实际nativeA=A.rawArray.map toFloat32和实际((Packed10.packB batch n p B).get b).get g。原dot10_lane/finish_dot10_lane中的hb必须由原packB逐lane读取定理闭合，原始列为10*g+j且须jGlobal<p；不能把hb留作最终算法假设。
4. NativeFinal.dot_eq/finish等既有桥负责所有NaN payload、Inf、subnormal、±0以及规定k顺序。输入原始A/B一直保留，只有合法输出调用finish；最后列组的无效lane不做无用raw replay。
5. 输出数组点态等于原referenceBmm，接原bmm_spec及其余三spec。编译探针或投影片段通过不代替这条完整链。

## 真正入口的结构

仍只准备一次global nativeA和现有Packed10.packB；不重排/重复准备B。按batch走m/4个完整四行块，每块的i0=4*t，baseAr=(b*m+i0+r)*n，四行都属于同一batch。每个列组g只执行一次wide40，缓存Vector F40 (groups p)，随后依次输出r=0,1,2,3各行的有效列；下一块开始前释放本块F40缓存。不要缓存整个矩阵的全部F40，也不要为逐行输出重算同一wide40。

尾部m%4行保持既有单行F10路径及一次每列组计算，不能逐输出重算整个F10 tile。不能沿用p2的跨batch四行组：此探针只有同一个F10 B packet，不同batch的B不能共享。m0、batch0、p0、n0按原空路径；巨大Nat或无法建立machine界时保留既有Nat fallback。实际入口的机器界从原Vector尺寸、b<batch、i0+3<m推导，不从有限样本或指针大小猜测。

输出/容量方案由Sol的review-output-wide-layout.md/.lean独立准备；整合前读取该精确资产并核对允许写范围。R负责循环投影、具体packB接线和最终候选。现有窗口截止02:31:25UTC、运行源码目标00:46:25冻结均不延长。

## 首次机器证伪与投入门槛

探针只选column-major一种布局，预期每列四行可组合为一个SSE向量，理论10acc+1A+1B，实际编译可能不同。必须查看同一对象里真实wordLoop：热循环有无重复B加载、foreign call、构造/分配、spill或不完整SLP。入口40参数经ABI栈传递和末尾构造F40的spill单列。代码不好先PARK，重访较少live chains需新增理由，不做宽度网格。

代码良好才整合上述完整入口并跑新原gate和完整配对成本。即使算术内核良好，nativeA装箱、B布局、每块F40缓存、最后列组多余MAC、四行输出顺序、tail和回放都仍有成本。旧R4的SIMD/无hotspill负结果约束完整成本判断；不能用MAC覆盖份额推算耗时或把正组件收益相加。
