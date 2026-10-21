# R26 延长4小时：B路线最终结论

结论：B19–B40没有取得可复核的稳定正增益，也没有达到稳定5%/10%份额目标。B37最后受控修复相对原552仍回退；停止树前缀、full-owner flatten和no-owner这几份精确候选的晋升，不投入完整Lean gate，不再启动研究方向。原始正反回执、源码、作者归属与脚本全部保留。主线程负责Git、全局报告、最终看板和之后的官方快照刷新；本报告只收束已授权的B路线。

## 最后一次真实消费：B36/B37

精确候选 `candidates/r26-b-552-a-no-owner` 的Rust SHA-256为`8012a8320f07228f01f383d0946d52f1000d3256d71ea6f1a121a2501ea276eb`。父552 Rust为`5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9`；同场full-owner为`e609a1aee215165a8df155ab124dbaa538fbd5111d956098cce4154431cd72f9`。三者保留的Lean文件均为父552 `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592`；两份新候选尚未适配该证明，不是通过完整gate的Rust/Lean对。

VERIFIED B36 run38226501675：28文件原encoder tokens/output同552和full-owner；1376次真实DP调用的完整cost/ch逐元素相同。no-owner确实删去564136512次owner-slot写入及4KiB owner初始化，仍保留564136512次base写入、379797088次rounded扫描（valid305270500）、odd/tail/fixed回退；实际新增owner helper调用14668774次、cached record读取36058448次、直接继承owner92143次。这里比较的是完整消费及维护，操作计数不是收益或纳秒成本。

VERIFIED B37 run38227360774、commit85d778f09a104b527faac4bbcf93a9be6cbc3758、原始目录`evidence/round26/38227360774/screen-b37/gate`：两块反序，各进程原11次计时；父和no-owner均有同源码/同二进制副本，同场保留full-owner辅助。原提取先于计时，444个有限equivalence案例无差异，540个decode案例无失败、token_changes为空。原语料28输出4868050B、公共均值压缩比例33.85029686801294%，这些质量检查不证明所有输入等价。

以下seconds是28文件各自按total_s排序所选真实中位rep的总和；parse/encode取同一rep，故精确相加。它与官方公共时间轴（逐文件total/incumbent比值的均值）是不同统计量。

| B37进程 | 块1 total / parse / encode秒 | 块2 total / parse / encode秒 | 块1 / 块2 公共时间轴 |
| --- | --- | --- | --- |
| 原552 | 1.595673879 / 1.414883661 / 0.180790218 | 1.595202331 / 1.414585439 / 0.180616892 | 2.4149443843 / 2.4307897502 |
| 原552同源码副本 | 1.597014892 / 1.415445384 / 0.181569508 | 1.596436740 / 1.414871654 / 0.181565086 | 2.4361739990 / 2.4197909345 |
| full-owner | 1.617539733 / 1.436457437 / 0.181082296 | 1.624479119 / 1.443410799 / 0.181068320 | 2.4439390964 / 2.4481140165 |
| no-owner | 1.626913314 / 1.445934895 / 0.180978419 | 1.623899304 / 1.442926107 / 0.180973197 | 2.4489641838 / 2.4345531708 |
| no-owner同源码副本 | 1.626626586 / 1.445111585 / 0.181515001 | 1.624425922 / 1.443035007 / 0.181390915 | 2.4325332268 / 2.4465610299 |

no-owner主相对原552公共轴回退`+1.408719793% / +0.154822959%`，副本回退`+0.728333236% / +0.648812994%`。实际total中位rep之和主回退`+1.957758124% / +1.798955057%`；parse分别增加31.051234ms/28.340668ms，encode只增加0.188201ms/0.356305ms。与full-owner比较，no-owner主total之和第一块慢0.579496182%、第二块快0.035692364%；副本对应慢0.561770003%/快0.003274711%，没有同块/跨块一致的有效修复收益。

同源码副本的公共轴差异为：父`+0.879093319% / -0.452479105%`，no-owner`-0.670934964% / +0.493226407%`；其total之和差异只分别为父`+0.084040543% / +0.077382598%`、no-owner`-0.017624049% / +0.032429228%`。不能把公共轴的小幅反向观察直接解释为候选解析更快。

精确分解对每个文件使用`Ctotal/Cinc-Ptotal/Pinc = (Cparse-Pparse)/Pinc + (Cencode-Pencode)/Pinc + Ctotal*(1/Cinc-1/Pinc)`，再平均28项。主no-owner相对主父的轴差如下：

| 分解项（轴单位） | 块1 | 块2 |
| --- | ---: | ---: |
| parser分子 | +0.01867355693 | +0.01627063625 |
| encoder分子 | +0.00019852871 | -0.00019023561 |
| incumbent分母 | +0.01514771389 | -0.01231698003 |
| 总轴差 | +0.03401979953 | +0.00376342061 |

7个真实A-DP文件的parser项为`+0.01662170665 / +0.01577071892`；其余21文件为`+0.00205185028 / +0.00049991733`。第二块较小的总轴退化受负分母项抵消，不能据此宣称解析有效改进。交叉副本比较中，块1 no-owner-shadow相对父-shadow出现轴`-0.149446311%`，但对应total之和仍慢1.854190224%，parser轴项+0.01077523671被分母-0.01498139852抵消。此反例保留，不构成稳定正增益。所有分解只是代数诊断，没有独立DP/finder计时，也没有替换官方评分。

完整逐文件、选中rep、源码/二进制/原始JSONL哈希、全部父/副本/full-owner交叉比较见[b39-no-owner-paired-cost.json](b39-no-owner-paired-cost.json)，生成脚本`scripts/r26-b-no-owner-pair-cost.py`。

## 提取与证明边界

VERIFIED B37原工具重新提取接受，绑定8012a832精确Rust。Types503B SHA`276d4089d337e0d7da19d73f67b92ed57aa61ce5b0b548420962498a78bf5966`；Constants12170B SHA`fff23524d0d08f7c51fd849ba45c7804a9412cb5b005c2ad576a38c9fa29865d`；Funs1165776B SHA`e85f941ded472f7829d1e5e9ec6dc5b40fc85673f7d11c9720461677925dd466`。extract-only使用空Lean占位，实际候选证明没有被编译，receipt明确`proof_status=NOT_RUN`；目录名gate不表示完整证明gate通过。

真实Funs中16个保留定义与B33逐字同，包括recs/min及其loops、store_choice、slot_of、初始化和继承回退loop。只相对full-owner修改Rust三函数`a_fill/a_dp_fill/a_dp_pass`，增加`a_dp_owner`。真实fill状态只有bl与k/a；dp_fill返回`((prev,pd,odd),bl)`；DP外loop捕获`(cost,ch,bl,i,e,xl,xd)`。新owner因ext分支被提取为loop0/loop1，两份body除定义名外相同，二者都需totality或显式body等式归约。guard保证j索引；mask255后checked U32 `+3`需<=258界；`top-j`终止度量仍需证明guard下wrapping_add没有溢出。源码预审的单loop猜测已由实际接口纠正。

源码证明块迁移的估算471472B与剩余52816B见[b38-no-owner-proof-preaudit.md](b38-no-owner-proof-preaudit.md)；实际接口/保留定义哈希见[b40-no-owner-extract-audit.json](b40-no-owner-extract-audit.json)，脚本`scripts/r26-b-no-owner-extract-audit.py`。无需现在投入证明：没有稳定正性能证据，未适配证明、未运行原始obligation/公理白名单/完整round-trip gate，未冻结后跨runner独立确认，未正式上传或取得admission/reward。

## 其他B机制的已执行结论

| 机制与真实实验 | 观测及结论 |
| --- | --- |
| 精确U16树边prefix，B19/B20 observer、B21消费、B23配对 | shortcut+seed总省8084092/42798913 wordpairs（18.89%），但增加25285324次edge读、38387592次edge写及新表维护。B23主公共轴慢1.779525%/1.078100%，副本也慢；停止此精确表示gate。 |
| 固定31上界packed树边，B27消费/B29配对 | n<2^26可达域保原timestamp，kid高6bits放31-cap prefix/精确flag，没有新增表。省7486105wordpairs（17.49%），但pack/unpack各25285324次，少省597987次。B29主慢2.840276%/2.429873%，副本慢3.009535%/2.803411%；停止，不扫cap。 |
| checked increment向量化，B22/B25 | 官方cdylib shim与overflow=true/fatLTO/cgu1下原/改均2个umin reduction、0个uadd-overflow，stride8归约及汇编主体相同（只常量符号名差异）。原循环已vector；未制造生产wrapping/unroll候选。 |
| 652 per-position base/owner flatten，B31/B33 | 与R18AW future-cost RMQ机制不同，已隔离真实迁移、所有维护包含在消费。1376次完整DP状态/28原输出同父；564M slot-pair填充和379.8M rounded扫描实测。B33主慢0.733903%/0.716664%、副本慢0.946510%/1.554703%；B37辅助仍慢1.200637%/0.712701%。 |
| 相同当前price无scratch分组，B30有限模型/B34真实observer | 总setup合并29.85%中的77.31%是旧同distance域，新增不同distance只有3008334/44430845（6.77%）；额外宽8覆盖只多3.01%terms，另有peek/map成本。NO_GO生产，未假称29.85%全新机会，也未称已实现更快。 |

root在收齐B37后按同一新官方快照29883重放全部历史行：本延长段4份消费候选tree-prefix、tree-packed、a-flatten、a-no-owner，主/影子校准的每条预测均0。合并辅助观测时prefix/flatten各6个实际过程结果、packed/no-owner各4个；全是discovery和同场辅助，不是冻结后的独立确认。每份最低/中位/范围均0，零次数等于观测数，5%/10%达标次数均0。该记录绑定`extension4h/all-analysis-29883.json` SHA`850d1de4cc3d37225ff5cc97d2096fd40207f624ac022b3817bdc4b015c5d7a9`与`all-roles-29883.json` SHA`f3b166e54588a44a4928b9c3223ded38ee85b64c3a2740204c9207483d99cacd`；它不是后续新榜单保证、私有集保证、正式排名或奖励。

## 可复用材料与具体再启条件

可复用的是语义条件、源码迁移、原生observer和反例，并无当前正收益组件可晋升。

- 树边prefix保留exact/下界join、NICE双重重接、过期timestamp消费与258方向不消费的条件和逐probe原生检查。未来只有能实质取消已测25M级读写/pack负担或由新真实consumer复用已有边信息的不同维护方式，才值得重访；重复U16表、31-cap或tag宽度扫描没有新依据。
- flatten保留4helper隔离迁移、完整cost/ch对照及owner first-cover语义论证（不依赖record全局单调）；这些可以用于未来机制证明。再启需设计实际减少仍保留的564M base写入或74.5M rounded无效扫描，并给出winner/tie/wrap/odd/fixed/继承域保持条件；单独删owner已测，不能把它当成功修复再组合。
- price-group保留不同distance新机会拆分。只有不同的一遍延迟消费能避免全域单独peek并复用既有winner owner状态，或新工作负载显著扩大新增覆盖，才进入下一最小计数/消费；旧same-distance负例仍有效。
- B25保留真实官方lowering证据。只有新官方工具链/源码改变且原循环实际不再vector，才重新检查具体阻碍；既有证据不支持盲unroll或off-flags收益外推。
- R24AE skip>=258删状态是已有历史小正向组件，当前552实域中skip260可覆盖部分A调用，skip256回退仍需原路径。未在此延长段迁移/计时；若未来另一机制有真实稳定正收益且组合迁移很低，才同场测完整成本，不因其单独不足5%永久排除，也不把旧1%级观察当本轮结果。
- 652 word4只做了源码区别预审，尚无本轮observer/消费/编译归约证据。未来必须先证明实际caller需要的高位被保留、原读没有已被编译器消去，并区别R24Y已有q复用；它不是本轮已验证候选。

所有再启条件都是未来建议，不是已执行的下一批。当前新研究已按09:18:52UTC截止，最终动作限于回执与报告核查。无需为一项未观察到的收益消耗预留gate/独立确认时间。

本段新增最终交付：b38证明预审、b39成本分解、b40实际extract审计、本报告；两份新审计脚本只读取原始证据并生成route-b派生文件。原始B37 artifact digest为`sha256:d8702977873da7a2b5fa19e199df0f863f2e31630335b558aab6d93ecd0478df`，原始文件不改写。
