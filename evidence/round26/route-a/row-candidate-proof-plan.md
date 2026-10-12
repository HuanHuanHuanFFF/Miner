# A12 生产接口：待提取前的最小证明形状

绑定 Rust `9c42e665cfdb8831e2c7f4dbe0a2de6012e59bc8ae9bd6918d540ea71704e2ac`。只做源码接口分析，没有新Lean，也没有宣称提取/证明成功。详细前提仍由官方提取结果决定。

相比影子阶段，生产版的一个有利点是可以不维护 head/row 历史不变量。row的位置是u32提示；`ar_ahead` 和 `ar_offer` 都在使用之前检查非零、c<p、p−c≤32768。只要query满足p+8≤input.length，读取来源word与原 `probe_m` / `probe_lazy` 的前提即可建立。`ar_link` 可以返回任意u32 victim，后续guard与字节验证确保合法性。

候选的ahead tuple为(row,tag,cursor,remaining_mask,first_encoded,cw)。拟用最小 `AheadOk input P a`：row<4096，cursor<8；若first_encoded>0，其解码c≤P并且cw=word8(input,c)。对正常调用还可带first非零时严格c<P，但保留c≤P即可交原probe距离guard。first=0时cw不需要等于word8(0)：`ar_offer` 的use_cache明确要求old>0，扫描后续槽会重新加载word。这避免对空ahead强加错误word等式。

正确性证明无需证明mask枚举了真标签、FIFO最近顺序或dirty与表相等。mask扫描显式fuel8保证终止，索引按%8/%4096限界；所有候选重新验证。`ar_record` 即使改变row，缓存第一来源的cw仍对应不变的input字节；正常复用分支检查p=e，位置上界仍正确。dirty的精确性关系到压缩轨迹与缓存策略，实际逐查询oracle负责有限验证，不能当成全输入等价定理。

新循环仍需完整合法性证明。可复用PC的FoundAt/MatchAt/Dec、flush、fold、writer、skip规格；新增：key/rotate/mask的总性与边界，ahead扫描及word关系，offer预算/fuel与有效best，link/record数组长度，lazy/main两个循环与尾输出。主不变量可只含Dec、输出长度、ls≤p、miss≤p、AheadOk，不需要旧HeadBound；lazy需MatchAt、p<lim、ins≤p+2和下一位置AheadOk。

这有望减少证明篇幅，但不是Lean自动完成的证据。尤其Aeneas对6元tuple传参与3个可变数组返回的实际shape、位移/leading_zeros算术、`step`的前提匹配和文件总大小都未知。父Lean487015B只余37273B；只有实际encoder/成本有潜力才调精确提取，随后按原obligation与公理白名单闭合，而不是删旧假设或接受有限oracle代替gate。
