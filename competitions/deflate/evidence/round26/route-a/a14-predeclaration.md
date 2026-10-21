# A14：原链短标签的第一个真实检查

固定源码：`r26-a-641-tagged-head`，Rust SHA-256 `f5350f86643ca65b955b4739165c6f04b27ef673a6e986c1614257687618e04c`；父版公开641 Rust `97254225b7a7a5c67a749b9fed7b58c94a9612b816c233581db6d7401d502181`。旧冻结材料保持原样。

缺口与旧结果：A12固定行少读来源却总时间回退约9%，A13隔离维护回放不支持通过维护改动救回。原链tag计划只有Python布局模型，真实非零tag拒绝及保存缓存身份均未验证。

变化：保留原head数组容量、prev槽位和链顺序、hash槽位、normal/lazy预算、记录、折叠和发射。head原u32改tag8+pos24；ahead原三个字段编码查询tag、旧tag、位置及miss位。非零tag不等时跳过source-word读取，并使该次primary/lazy返回无匹配。head完整0仍读source0。输入至少2^24或不属于15bit hash域的H直接调用原内核。没有固定行、多槽扫描、游标或容量扫描。

最小动作：原444有限token等价；公共28原encoder/双解码与父版token/输出严格身份；169个直接内核case（含实际2^24-1、2^24、2^24+1输入，特殊H回退）；source0、km3与最高24bit插入辅助检查。未计时observer每次真实primary/lazy都与原byte探测结果比较；每次查询前重建完整head身份，记录cache复用、tag miss、false positive和原完整0来源。计数绑定原encoder精确tokens。**计数不换算成时间收益。**

判别：等价或缓存断言失败先修复该具体错误；真实tag拒绝很少则暂停。等价成立且覆盖足够，才做一批原协议配对总时间，继续按真实时间和同源码对照决定。还没有完整Lean、独立确认或正式收益证据。

成本：仅临时Linux runner编译，编译与运行各240秒上限，完整native入口建议20分钟外层上限；预期分钟级得到筛选/诊断，排队时间UNKNOWN。当前4小时窗口最后约90分钟留gate/冻结确认，UTC09:10后不投入新方向。

证明可行性预审：父Lean487015B、剩37273B。旧fallback可达，原chain证明必须保留。新增证明需低24位HeadBound、packed slot范围、低位cast/OR恒等式、条件source word身份、新record/main/lazy循环。原contract只要求合法输出，tag拒绝分支直接返回(0,0)，其FoundAt.none不需要证明tag拒绝与源前缀不等；这个更强性质用于同token原生检查。不能把这种证明简化当成新gate已通过。

证据：`a14-tagged-build.json`、`a14-tagged-entry.json`、`a14-local-preflight.json`、`a14-native-proposed.json`；派发及原始云端回执由主线程绑定。
