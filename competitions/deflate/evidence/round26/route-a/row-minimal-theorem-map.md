# A12 精确提取前的最小定理表

仍绑定冻结Rust `9c42e665cfdb8831e2c7f4dbe0a2de6012e59bc8ae9bd6918d540ea71704e2ac`；这里不假定Aeneas提取的参数顺序/返回tuple，也没有新增Lean源码。

| 新接口 | 最小语义要求 | 已有证据或可复用规格 |
|---|---|---|
| `ar_key` | p+4≤usize.max；返回row<4096 | `PC.be4_spec` 1810只给安全性已足够。`h>>52`用U64上界和右移整除得<2^12，再证明cast不截断。tag值无需匹配语义。 |
| `ar_mask` / `ar_rotate` | 安全终止；返回任意U64即可 | wrapping算术总性；cursor%8≤7，shift≤56，非零分支64−shift<64。合法token证明不需要精确lane等价。 |
| `ar_ahead` | row<4096、cursor<8；first>0时decoded c<p且cw=word8(s,c) | `PC.be8_spec` 1485；由c<p和p+8≤n供读取前提。fuel8递减，表索引row*8+slot<32768。空first不要求cw=word8(0)。 |
| `ar_ahead_if` | 在给定B下保留AheadOk；新查询时利用i≤B+1 | 必须保存ahead的**严格**c<i，才能在lazy拒绝后的预取i=p+2时得到c≤p+1。仅用c≤i会丢失这个边界。 |
| `ar_link` | 三个数组操作安全并返回一个u32；无需内容历史性质 | row%4096和cursor%8限界，p转u32及wrapping+1总性，标签更新移位≤56。 |
| `ar_offer` | FoundAt(s,p,l,d)且l≤258、d≤32768 | `PC.probe_m_spec` 2505，`probe_lazy_spec` 2434，`f_try_spec` 2776；后者传c=p。cached-first使用AheadOk的word等式，rest-slot每次重新读取。 |
| `ar_record` | 在end≤n、lim+8=n、ins0≤lim+1下总性；数组类型不变 | 没有HeadBound/FIFO不变量。每个hash调用ins<lim；两个record loop分别用stop−ins、end−ins作measure。dirty无需真假规格以证明token合法。 |
| 新lazy loop | MatchAt、p<lim、ins≤p+2、下个来源≤p+1、P0≤p | 仿`PC.lazy1c_loop_inv` 2841，去HeadBound并换成AheadOk；measure仍lim−p+go。 |
| 新main loop | Dec、输出长度、ls≤p、miss≤p、当前来源≤p | 仿`PC.main1c_loop_spec` 2903，去HeadBound；fuel递减。3数组和ahead tuple捕获以实际Funs为准。 |
| 新tail/run | Dec推进到n，给原LZ77.Valid obligation | `PC.put_lit_spec`与原tail模式；`Dec.init` 1908。进入主loop n>16，lim=n−8。 |

offer loop的best不变量可用 `FoundAt ∧ l≤258 ∧ d≤32768`，初始(0,0)用`FoundAt.none'` 2363；当best≥3时用`FoundAt.real`取MatchAt，再交f_try。`next`与`cached`还需保持：next非零只能指向初始缓存first；迭代后next=0且cached=false。冻结生产源码已令use_cache同时要求old>0，因此空first后再弹出rest slot不会误用零word。

原发射链可直接沿用：`flush4_spec` 2560；`fold_w_spec` 2172保留端点；`put_match_h_spec` 2065给写入后end=p+l与Dec；`gain_spec` 1765只给总性，不是价格最优；`skip_len_spec` 2451需skip<32，`skip_to_spec` 2457保单调。

父入口证明有6处局部启用`PC.run1c_spec`（8611、8660、8681、8723、8737、8744，部分同一行混合其他规格）；新`AR.run1c_spec`要在对应路由证明作用域启用，旧PC规格仍保留给旧定义。不能只证明新helper就跳过parse主obligation。

待精确提取后先核：Rust tuple别名展开、ar_link/record多可变借用返回形状、while嵌套捕获顺序、全部新函数是否提取成功。若接口通过而计时否决，则停止完整证明；若计时有足够信号，再把上述规格落实为Lean并检查37273字节余量。
