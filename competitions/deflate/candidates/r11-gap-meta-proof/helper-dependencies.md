# R11 metadata helpers：提取前依赖表

状态：SOURCE_INTERFACE_PREPARATION / UNCOMPILED。Rust候选25bd4ee52560288f36c73f813a769345044cab2c4924705e6c4c92a64c017de6保持冻结；本目录尚无新Parse.lean。最终函数参数顺序、loopstate/return投影必须用gap-b真实Funs核对。

| 新lemma | 必要post和度量 | 现有依赖 | 不可混淆的缺口 |
|---|---|---|---|
| d_gap_positive_max_loop_spec | forall初始i/maximum/positive总性，post True；循环measure 256-i | d2_lt 或 d1_ite给i<256；d2_idx固定256数组；d2_itev处理max/positive两个纯分支；d2_inck 256与d2_msub给i+1后的下降 | 这是总性，不是max对全部literal的语义上界或positive fold证明 |
| d_gap_positive_max_spec | 绑定新loop，最后positive分支返回maximum或0；post True | loop_spec、d2_tot/d2_itev；不用新公理 | 来源语义需要另说明精确fold；不能把其假设加到原obligation |
| d_load_meta_spec | 完整三数组返回总性，post True，类型固定256/512/32 | 原d_load_spec、positive_max_spec、d2_upd恒定index511<512 | 修改仅511；保留0..510是源码/额外语义命题，旧True post不证明它 |
| d_block_meta_spec | 与原block相同返回litc/lc/dcc/bs四项，post True | 逐字复制原d_block_spec的d2_idx/by decide、d2_lt、d2_dec、get0_spec、d2_upd；只换loader lemma | 比较与bs-1算术仍需要原guard，不能省略或用wrapped decrement改变原义 |
| d_gap_meta_loop0_spec / loop1_spec | 与原相应loop的out.length post相同，measure q | 原d_gap_loop0_spec/loop1_spec的证明模式；真实提取后核对有没有多捕获参数 | 前两段源码格式变化但语义未优化；不得把metadata来源当length证明前提 |
| d_gap_meta nested-fill_spec | out.length保持且q_out<=q_in；measure当前q；inv out.length和q<=entry_q | 四个原guard、d2_dec、d2_sub、d2_rem/d2_remR、d2_idx、d2_upd/d2_supd、d2_lift、d2_pred | break分支不继续迭代，无需强求break也降低q；guard rem>258/价格不同只影响是否break，不用于弱化输入域 |
| d_gap_meta_loop2_spec | out.length保持；measure q | 每轮先scalar d2_dec形成q_seed<q_entry；nested-fill post给q_after<=q_seed；Nat.lt_of_le_of_lt闭合 | 此下降不证明完整cell/价格语义等价 |
| d_gap_meta_spec | 与原d_gap相同out.length post | entry禁用分支直接原d_gap_spec，启用分支拼接新三loop；原cached-kc/clip/shift/索引lemma | 任意假metadata独立输入已有反例；all-input totality仍无数据来源前提 |

外层仅四处绑定迁移，预计tuple均不变：d_dp_spec初始化d_load_spec换d_load_meta_spec；d_dp_loop0_loop0_spec的d_block/gap换新lemma；d_dp_loop0_spec node处d_block换新lemma。实际Funs若九项state或返回顺序变了，按真实接口处理，不预先宣称复用已通过。

固定数组index511更新的总性无额外长度假设；U32 max比较和Bool positive折叠均为纯分支。新循环256上界沿用原loader证明对32/64位Usize的界，不假定runner64位即可替代Lean可移植总性。

声明边界：实际loader把当前litc的正价max写入511；实际d_dp调用链rem<=510且candidate/push<=258，确保原价消费不读511。新fast helper的source语义只在该来源不变量下成立。原helper保留，原LZ77.Obligation、公理白名单、checked emitter和全输入totality不增加这个前提；有限token检查或来源说明不能代替实际gate。
