# C4冻结证明：gate前静态风险记录

UTC12:23，仅静态核对，未更改冻结proof1及其草稿。精确Rust `ae4602290cc2a0253703ab6e6ac0d2fe098e84429cc4d56314ac9326abbf0f88`，Lean `11426ab441c65b37949eff9de9840310d9192fd797870433d90d5e06463fb105`；原版gate38248430871、screen38248399555已由主线程启动。本记录不是编译或gate通过。

## 已核实的数学接口

`sources/conjectures-optimisation-deflate/validator/lean/Lz77/Search.lean:112`的`emit_match`参数顺序、Matches方向与c4_write_post一致：distance界、len界、终点界、源/目标字节、mkMatch编码及原decode前缀，足以产生新decode前缀。不是复用未经证明的search长度。

`c4_write_post`中的`ntok < out.length`可以由ntok≤pos、full≥3、pos+full≤n及n≤out.length推出；写入index与token算术界没有缺失假设。`Std.Slice.set_length`在原父证明已有使用。

actual helper不限l==8：l≥3、cap≥l、full≥l，所以full≥3；trusted match_len给full≤cap和Matches，cap=min(n-pos-8,258)给full≤258及pos+full≤n。d guard给1≤d≤32768及d≤pos。参数cap/length大于258、无效d、尾部不足8B等域走旧emit；它的规格已经处理拒绝→literal进度。cap≥l但trusted full<l走原emit_lits，符合相同进度和decode后置条件。

`c4_write_post`不声称压缩最优、搜索最大性或与原token相等。实际C4取消lazy，匹配长度及轨迹可变化；full≥l只保证当前长度不小于提案长度，不保证完整输出大小、速度或评分单调。

## 最可能的工程失败点

1. 新Slot.c4_emit_step的实际提取参数/返回形状及内部`full`局部变量名与草稿预期是否一致；目前未收集新Funs。
2. `step*`为match_len建立源/目标cap边界，尤其短路条件、rem=n-pos-8及min分支的scalar事实；出现此处错误时按真实guard假设补局部算术，不改Rust或削弱契约。
3. new writer token cast目标与mkMatch：草稿已显式展开mkMatch/MATCH_BASE，仍可能需要按实际SSA编号补中间post等式。
4. 旧emit/emit_lits回退经step*后可能保留整份后置条件；若日志显示pure conjunction无法匹配，可增加对应已知post的直接assumption/destructure，不重写算法。
5. `o_a_find`改为scan结果投影后const LZT是否仍在实际Slot签名；若提取接口变化，按真实签名更新find_spec及调用者，不按源代码变量名猜测。

这些是未确认的失败候选，不是编译错误事实。下一步只等实际原版gate日志；若需修补，先保留本次失败原字节，在新audit文件准备精确修补，再由主线程按新哈希冻结新proof包。无额外研究或CI。
