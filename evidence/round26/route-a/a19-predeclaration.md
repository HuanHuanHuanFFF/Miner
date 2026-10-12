# A19：U118完整前缀比较的两处安全索引加法

直接证据：A17使用原官方candidate shim及release设置捕获的原row9 IR，在u118_common字循环中，`b+k`和后续be8的`i+8`仍出现溢出panic分支。单纯减少源文字或panic调用总数不能代表性能；B25已提供这类提醒。

本次唯一变化：原公开658 `u118_common`字循环里的`u118_be8(s,a+k) ^ u118_be8(s,b+k)`两处索引改为`a.wrapping_add(k)`／`b.wrapping_add(k)`。保留be8函数、k+8循环界、字节尾循环、比较次序、返回长度、A17末跳、A18窗口、路由和搜索预算。scratch精确反转两处调用后必须等于原函数。不新建生产candidate。

边界推导：common仅由u118_walk调用。原walk不变量`c<=p+2`结合接受的wrapped distance可得c<=p；u118_find固定`p+cap<=input.len()`、cap<=258。字循环分支`k+8<=cap`因此给出`c+k+8<=p+cap<=len<=usize::MAX`。两次加法都不溢出，和wrapping结果相同；保留的be8收到完整8字节可用位置。这里不把“wrapped distance有效”单独当作c<=p的证明，也不外推任意非法直接helper参数。32/64位近MAX算术模型4146例只检查有限边界，不能替代Lean。

最小动作：原源码和这个scratch对照按原shim/完整release设置编译，保存row2、row9及common的IR/汇编、编译命令与哈希；逐热loop判断是否消掉真实比较/分支或使8字节读取/循环发生有效变化。随后同批直接common边界/overlap/短尾测试、28实际parse token严格等价并decode，绑定已收齐658原encoder token；不重复encoder。

决策：无实际热路径变化则停；有明确指令/循环变化且有限等价成立，才形成一份精确candidate、做原协议总压缩时间对照。即使指令减少仍可能因调度/代码布局回退，原11rep与同源码对照才有性能结论。不给增加组合、改be8或扫描源码写法的空间。

成本上限：两次lowering与一次有限验证编译/运行各300秒，建议20分钟外层cap。原pins/shim/release字节对照，不改原官方目录。原Gate、正式结果和配对时间均NOT_RUN；UTC09:18:52研究冻结余量保留。
