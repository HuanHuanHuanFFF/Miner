# 异号吸收：必须按真实binade分两支

数学推导，未接Lean原add义务；只为保存下一轮可证接口，不恢复已停放的SUM运行体。

设normal有限累加器的无符号有效尾数为M，2^23≤M<2^24，raw指数e∈[26,254]。小项有效指数d=max(1,rawExp(x))，尾数m（subnormal无隐含位），g=e−d。保守raw条件`absBits(x)<((e−25)<<23)`等价rawExp(x)<e−25，故非零小项满足g≥25及m<2^(g−2)：subnormal时g=e−1≥25、m<2^23；normal时g≥26、m<2^24。符号相反时，对齐整数为N=M·2^g−m>0，指数为d−150。

零小项须独立处理；此处m>0。不要只证明以drop=g舍入，因为当M=2^23时真实rounder少丢一位。

**M>2^23：** 2^(23+g)≤N<2^(24+g)，所以h=log2N=23+g、drop=g。欧式商为M−1，余数r=2^g−m。由m<2^(g−2)<2^(g−1)，r严格大于half，不依赖tie parity便上舍到M。M<2^24，无carry；h+(d−150)=e−127∈[−101,127]，属于原rounder正常且有限分支，位型恢复原acc。

**M=2^23：** 2^(22+g)≤N<2^(23+g)，所以h=22+g、实际drop=g−1。商为2M−1，余r=2^(g−1)−m；严格m<2^(g−2)给r>half。RNE得2M=2^24，真实carry=1、归一化尾数M。舍入前h+(d−150)=e−128≥−102（仍满足原normal下界），加carry后归一化无偏指数e−127，且≤127；mkBits存储指数再加127为e，恢复原acc。

负acc由精确dyadic的符号字段镜像得到相同幅值计算；仍须证明实际add对较大幅值选择原acc符号，不能仅写“对称”。最大有限e254含carry上界安全。该推导保留累加器为非零normal、小项允许subnormal、全部量词、原normal分支前提及carry；没有使用浮点结合律或先合块后舍入。

后续Lean最小模块：先给Nat的subtract-multiple RNE商余数引理与上述两组log2界，再连接实际`roundDyadic`，最后证明raw字段→有效dyadic/add分支桥。块fold接口已有显式scalar_sound参数，不能将它计为该标量桥已经关闭。
