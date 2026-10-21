# 原生累加状态求和

冻结 SHA-256 `75524a316b846ccfbbba3fabe0f9ac4941c1c126ef6b4fd370573b0e84b09fdd`，35312字节。

只改变sum：直接Option Float32尾递归；有限输入和raw往返guard，失败完整回退referenceSum。每元素逐次舍入、原顺序、初始+0；最后一步可溢出，后续还有元素时再决定回退。

四义务证明草稿NOT_COMPILED，性能NOT_RUN。D要求准备并保留，待native-add可行性后择序验证；本包不派CI、不正式提交。
