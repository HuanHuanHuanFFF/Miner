# 追加一小时：独立低证明成本路线审查

审查时间：2026-10-12 UTC11:51–11:59。范围仅既有文件、已捕获官方29907和历史原配对重放；只写本audit目录，未改候选、CI、Git、脚本、资金或正式上传。

## 当前决定

没有可直接推荐为“可靠小份额”的旧包。最佳本窗判别路线是 **C2：在658 U118的旧match backward-fold消费者先做末字节必要条件筛选，成功后仍调用原u118_same**。它省掉实际重复扫描，不新增record/head状态；但收益空间尚UNKNOWN，native应先统计取消的真实word/byte工作与新增guard工作，不能把取消调用次数换算总速度。

合法精确起点：`references/round26-public-658/parse.rs`，SHA256 `1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad`；`Parse.lean`，SHA256 `354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494`。两者为原公开阅读副本，修改另在candidates进行。

## 当前快照与历史复用

`official-start/receipt.json`绑定29907，官方计算UTC11:44:41.001875，查询UTC11:50:54.288793–11:51:17.283434，freshness仍unknown，policy `compression-policy-c255effb7d5afeef`。独立原字节、完整公式及API payout审计在`api-audit-29907.json`：664行、101前沿，误差检查通过。使用已有extension4h/rules-start纯scorer，非新网络抓取规则。

`history-29907/`是330份历史原配对文件的当前快照重放，无新增计时；保留全部角色和calibration，去重不增加独立样本：

| 旧包 | 当前主确认最低/中位/最高 | 主零值 | 影子结果 | 复用决定 |
|---|---|---|---|---|
| R24 root-word-price | 0/0/0% | 9/9 | 同为全零 | 无直接小份额起点 |
| R24 fast-adaptive | 0/0/0% | 9/9 | 同为全零 | 无直接小份额起点 |
| R25 end4 | 0/0/0% | 4/4 | 同为全零 | 不因旧gate重推 |
| R25 tiny-pc8 | 0/0/0% | 4/4 | 同为全零 | 单runner微峰不晋升 |
| R22 chain-halfhead | 0/0.972855/2.313741% | 2/4 | 中位0%、3/4零、最高2.099679% | 距正份额近，但不可靠 |

chain-halfhead精确包已有完整原版公共gate，Rust `57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275`、Lean `4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6`，直接复测无需证明迁移；此前373.3s gate不能替代本窗独立性能确认，也不能证明当前份额。其595校准还有正式迁移UNKNOWN。因此它只作为备选对照，优先级低于C2的机制判别。

658坐标为x=0.4715729387405976、y=35.603019029779745%。固定质量时，当前#562 x=0.47116298545451707、y=35.5123546371783%构成直接支配边界：至少跨过约0.086933166%的相对时间改善才可能进入前沿。0.01%时间网格首次≥0.1/0.25/0.5%份额在快0.09%时为0.707331%，≥1%在快0.33%，≥5%在快2.80%；完整非单调网格与项在`geometry-29907.json`。这些是几何场景，不是C2收益预测或私有成功保证。

既有同二进制public658/shadow两块gap为0.017802849%和0.086806838%，后一项几乎等于入前沿门槛。不能据0.1%级发现信号推荐稳定小份额；它需要冻结、跨runner原协议配对及同源码控制。两控制值不是未来误差界。

## C1为何关闭

`u118_common` Rust4169–4190返回最长相等前缀，`u118_find` cap为min(n-p,258)；`u118_PARTIAL=0`在4100。未经截短的旧match若长度<258且后有输入，其结束处与自身距离必失配；fold只改起点、保结束与距离。同距相邻合并若总长≤258因而不可达。直接旧机制论证见`evidence/round26/route-a/forward-fold-domain-closure.md`，其原论证限PC；本次核对U118相同性质后外推为源码推论，未新增Lean形式化最大性定理。

## C2消费者与证明迁移

精确改点：Rust4487的旧match fold条件。保持原`l+w<=258 && w<=p && d<=p-w`的顺序，在原same之前加`input[p-1]==input[p-1-d]`。它是Matches覆盖尾字节的必要条件；失败可跳过same，走原else的part_merge/back终止，成功仍用原same。不能把失败改成继续遍历，也不能改原bounds与分支结果。

活动范围由parse→bulk_parse→p125_row2/row9→u118_run决定，源码9381/9395；row9五个公共文件与row2 catalog已有实际调用证据，合计parser约占原总时间轴7.7%，该占比只作条件投入背景。guard失败比例和原same是否已在首word失败都未知；原same从起点每8B比较，故取消长w的调用不保证省w字节读取。应统计原same实际word/byte比较量，尤其“首word就失败”的负覆盖。

PC直接先例须看完整wrapper：`pc_fold_w` Rust8561–8582在第一次token前已有末min(w,8)word必要筛选；实际pc_run经wrapper。最初只查pc_fold8537得出“PC没有末guard”的说法已撤回。第二/第三fold会看到新token，理论上有新的过滤位置，但缺少真实覆盖计数，不在本窗据此扩实现。U118不经这个wrapper，故C2不是给同一消费路径重复添加已有guard。

安全性证明可沿用Lean3750的`BackInv.match`与3440的`same_spec`，保持same返回1→Matches；不需要证明guard成功即可整段相等，也不需要新增已解码token反向推理。修改集中在Lean3983–4019的`back_loop_inv`，新增两次byte读取与boolean分支后保持原`BackInv.match`/`BackInv.part`。直接guard下标界由p+8≤n、d<p与旧w/d guard给出，p-1-d非负。实际提取可能重编号临时变量或改变短路分支；必须按新提取核对，不按旧iN名字机械复用。

没有新增函数、循环、数组或search状态；证明迁移评为局部，而非新调度级。Lean原505143B，距524288B限额余19145B，局部迁移有空间但最终字节仍需核验。已有父证明只给安全性，不证明token等价；native必须实际检查28文件token/output一致以及有限生成输入。

完整验收仍须绑定新Rust/Lean精确哈希、官方fresh extraction、原LZ77.Obligation、公理白名单和stage1 roundtrip。可参考已执行完整gate秒数373.3s(chain-halfhead)、540.2s(tinyPC)，不含新C2准备/排队/setup，且658 gate时长UNKNOWN；不能把复制父Lean或extract-only写成通过。建议native机会明显薄弱时停在诊断；有足够原协议总时间信号后才迁移并运行完整gate，保留跨runner冻结确认预算。

## 不重开的旧机制

- A14短tag：取消19.05% ahead source word读取仍总轴慢3.12%/3.34%，全record维护成本是真实负例。
- A16近head：省写覆盖0.43%，只少510B，未计时；不以“省写”包装成主线。
- A18窗口filter：取消9.66% common，却新增约145.9万query word读及状态维护，停止该精确版。
- A19局部安全算术：实际只改一个lazy热guard；两主块一零一微峰、同源码副本全零，不是可确定叠加收益。
- B21/B27树prefix、B31 flatten、B36去owner：真实维护、扫描、解包、来源恢复抵消节省，均原协议回退；旧负例只限这些确切实现。
- R24 SF match-cache：1393万已知前缀命中没有总时间收益；高命中缓存不是C2无状态必要条件消费者的直接重复，但提示仍需完整成本。

VERIFIED：上述精确源码位置/哈希、既有回执、当前公式重放及历史原文件审计。INFERRED：C1域排除、C2安全机制与迁移规模、条件几何。UNKNOWN：C2实际覆盖、真实总时间、完整gate、冻结确认、私有迁移和正式可支付结果。
