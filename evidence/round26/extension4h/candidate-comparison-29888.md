# R26 候选对比：快照 29888

生成UTC 2026-10-12T10:45:55.413177+00:00；官方计算 2026-10-12T10:43:57.085857+00:00，freshness=unknown。

以下份额均为条件公共估算，未获得本轮正式准入或支付结果。主候选与同源码副本、主参照与影子参照分列；每个已计时主候选仅一runner两发现块，没有冻结后独立确认或完整公共gate。

追加阶段新增8份不同Rust，6份已做原协议总时间，2份未计时。全R26共28份Rust，13份已计时。

## 原协议主候选

负时间变化表示比实际父版更快；两块顺序保留，不按峰值挑选。份额的最低／中位／最高均按块计算，不能解释为正式成功概率。

| 候选 | 追加 | 两块时间变化 | 主参照最低／中位／最高 | 零／总块 | ≥5%／≥10%块 | 影子参照最低／中位／最高 |
|---|---|---|---|---|---|---|
| [r26-a-641-trimhead](../../../candidates/r26-a-641-trimhead) | 原窗 | +0.188286%／+0.228491% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |
| [r26-b-628-shared-cache-fix1](../../../candidates/r26-b-628-shared-cache-fix1) | 原窗 | -0.130864%／-0.204237% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |
| [r26-a-641-boundary-log](../../../candidates/r26-a-641-boundary-log) | 原窗 | +6.844958%／+7.077428% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |
| [r26-a-641-hash17](../../../candidates/r26-a-641-hash17) | 原窗 | +0.573073%／+0.281967% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.764884%／1.529768% |
| [r26-a-641-allow-near](../../../candidates/r26-a-641-allow-near) | 原窗 | +1.040900%／-0.004535% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.146525%／0.293051% |
| [r26-a-641-lazy-chain](../../../candidates/r26-a-641-lazy-chain) | 原窗 | +2.324381%／+2.531675% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |
| [r26-a-641-row8](../../../candidates/r26-a-641-row8) | 原窗 | +9.176233%／+9.610965% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |
| [r26-a-641-tagged-head](../../../candidates/r26-a-641-tagged-head) | 是 | +3.121938%／+3.336959% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |
| [r26-b-552-tree-prefix](../../../candidates/r26-b-552-tree-prefix) | 是 | +1.779525%／+1.078100% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |
| [r26-b-552-tree-packed](../../../candidates/r26-b-552-tree-packed) | 是 | +2.840276%／+2.429873% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |
| [r26-b-552-a-flatten](../../../candidates/r26-b-552-a-flatten) | 是 | +0.733903%／+0.716664% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |
| [r26-a-658-safe-word-offsets](../../../candidates/r26-a-658-safe-word-offsets) | 是 | +0.277417%／-0.148876% | 0.000000%／0.388151%／0.776302% | 1/2 | 0／0 | 0.000000%／0.442449%／0.884898% |
| [r26-b-552-a-no-owner](../../../candidates/r26-b-552-a-no-owner) | 是 | +1.408720%／+0.154823% | 0.000000%／0.000000%／0.000000% | 2/2 | 0／0 | 0.000000%／0.000000%／0.000000% |

## 未计时版本

| 候选 | 追加 | 原编码证据 | 份额 |
|---|---|---|---|
| [r26-a-641-near-retain](../../../candidates/r26-a-641-near-retain) | 是 | 5222319B，质量轴35.67136677% | UNKNOWN |
| [r26-a-641-second-look](../../../candidates/r26-a-641-second-look) | 原窗 | 5216359B，质量轴35.64462957% | UNKNOWN |
| [r26-a-658-window-filter](../../../candidates/r26-a-658-window-filter) | 是 | 5159012B，质量轴35.30821098% | UNKNOWN |
| [r26-a-tiny-distance12](../../../candidates/r26-a-tiny-distance12) | 原窗 | 5332426B，质量轴36.10187355% | UNKNOWN |
| [r26-b-552-dense-forward](../../../candidates/r26-b-552-dense-forward) | 原窗 | 4868130B，质量轴33.85097084% | UNKNOWN |
| [r26-b-552-discarded](../../../candidates/r26-b-552-discarded) | 原窗 | 4868029B，质量轴33.85009357% | UNKNOWN |
| [r26-b-552-endpoint-fit](../../../candidates/r26-b-552-endpoint-fit) | 原窗 | 4872605B，质量轴33.86690220% | UNKNOWN |
| [r26-b-552-greedy-fit](../../../candidates/r26-b-552-greedy-fit) | 原窗 | 4880263B，质量轴33.88981488% | UNKNOWN |
| [r26-b-552-overlap-select](../../../candidates/r26-b-552-overlap-select) | 原窗 | 4868059B，质量轴33.85030681% | UNKNOWN |
| [r26-b-628-cache-hint](../../../candidates/r26-b-628-cache-hint) | 原窗 | 该台账无原编码汇总；见原始阶段回执 | UNKNOWN |
| [r26-b-628-no-e](../../../candidates/r26-b-628-no-e) | 原窗 | 4864265B，质量轴33.82961417% | UNKNOWN |
| [r26-b-628-no-rf](../../../candidates/r26-b-628-no-rf) | 原窗 | 4864435B，质量轴33.83081938% | UNKNOWN |
| [r26-b-628-rf-backward](../../../candidates/r26-b-628-rf-backward) | 原窗 | 该台账无原编码汇总；见原始阶段回执 | UNKNOWN |
| [r26-b-628-seed](../../../candidates/r26-b-628-seed) | 原窗 | 4864369B，质量轴33.83014591% | UNKNOWN |
| [r26-b-628-shared-cache](../../../candidates/r26-b-628-shared-cache) | 原窗 | 该台账无原编码汇总；见原始阶段回执 | UNKNOWN |

## 联合加入

仅下表组合有匹配run／块／校准记录，每次加入两点后重新计算前沿和归一化；其中带控制角色的点只是同场辅助观测。其他组合缺少共同测量，未把独立份额相加。

| 组合／run／块／参照 | 实际角色 | 分别加入 | 同时加入 |
|---|---|---|---|
| r26-a-641-hash17 + r26-a-641-allow-near；38179533008；1；primary | candidate／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-a-641-hash17 + r26-a-641-allow-near；38179533008；1；shadow | candidate／candidate | 1.529768%／0.293051% | 1.528745%／0.292533% |
| r26-a-641-hash17 + r26-a-641-allow-near；38179533008；2；primary | candidate／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-a-641-hash17 + r26-a-641-allow-near；38179533008；2；shadow | candidate／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-b-552-tree-prefix + r26-b-552-tree-packed；38220986889；1；primary | control／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-b-552-tree-prefix + r26-b-552-tree-packed；38220986889；1；shadow | control／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-b-552-tree-prefix + r26-b-552-tree-packed；38220986889；2；primary | control／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-b-552-tree-prefix + r26-b-552-tree-packed；38220986889；2；shadow | control／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-b-552-a-flatten + r26-b-552-a-no-owner；38227360774；1；primary | control／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-b-552-a-flatten + r26-b-552-a-no-owner；38227360774；1；shadow | control／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-b-552-a-flatten + r26-b-552-a-no-owner；38227360774；2；primary | control／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |
| r26-b-552-a-flatten + r26-b-552-a-no-owner；38227360774；2；shadow | control／candidate | 0.000000%／0.000000% | 0.000000%／0.000000% |

## 精确文件身份

下面Lean只是实际保留文件，不表示已适配或通过gate。详细声明、原始数据路径、逐文件总时间与对照见同目录机器台账、角色统计及原始分析。

| 候选 | Rust SHA-256 | Lean SHA-256 |
|---|---|---|
| r26-a-641-allow-near | `585f7b5d27c1f7570140eaa128bf413b2b81a393b7858272d099b877b8d75e88` | `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` |
| r26-a-641-boundary-log | `8c7e791cc2d3acb483f2f7504538becb76dee5ab3f9fddba18a72fa50cb920d7` | `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` |
| r26-a-641-hash17 | `ba11fad1ce628c36f5d96a9bb02af16ecd29dbc3ac9fe47737efe67d3c2a8bea` | `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` |
| r26-a-641-lazy-chain | `29eeab8a83b7c22d56d5c28986198b735ced2ee3199aebf71164b5198eb71ec4` | `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` |
| r26-a-641-near-retain | `83ae95175233346aebacbadadb0440d78b19e97676104626ce1fa76422d4fe72` | `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` |
| r26-a-641-row8 | `9c42e665cfdb8831e2c7f4dbe0a2de6012e59bc8ae9bd6918d540ea71704e2ac` | `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` |
| r26-a-641-second-look | `6ea536c7d7869f6fc7b6dbfb88e217c99530910f242f0a69ffd19200a7583cef` | `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` |
| r26-a-641-tagged-head | `f5350f86643ca65b955b4739165c6f04b27ef673a6e986c1614257687618e04c` | `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` |
| r26-a-641-trimhead | `392c698b6cc2d2ca836f3831d49a41490648c15a9c450583f00b3630fa879862` | `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e` |
| r26-a-658-safe-word-offsets | `10b2e02e230df8a2225e94db15a50eadf2d5d2abaabfa193936e885dd97a8e64` | `354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494` |
| r26-a-658-window-filter | `aa07317a57e1089ca8a9fc88acb11c4a61f3fe94f4c379831474db15e4ae9d8b` | `354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494` |
| r26-a-tiny-distance12 | `a20208d62cdb8c487a2041bc0d41445081caeaa0aefb1d8ddab620c6e4dd8ab3` | `3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8` |
| r26-b-552-a-flatten | `e609a1aee215165a8df155ab124dbaa538fbd5111d956098cce4154431cd72f9` | `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592` |
| r26-b-552-a-no-owner | `8012a8320f07228f01f383d0946d52f1000d3256d71ea6f1a121a2501ea276eb` | `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592` |
| r26-b-552-dense-forward | `01bc288459303be392ed19f026443835a8c69aec5fa525eec40316aa4bd7beca` | `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592` |
| r26-b-552-discarded | `8974acb8e1c1087d1b4560fd2dc451d8d19c6e3e6f81905b81e9df9a3be4ecdf` | `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592` |
| r26-b-552-endpoint-fit | `11771d2e13a782303d1de974eb8e8b23c5869f1a65d9034c9247809045987e0e` | `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592` |
| r26-b-552-greedy-fit | `d483514a06a7a614aa1e8ffe15120eddb3b03e2b6ef56c4763bb8a2b26ef08b5` | `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592` |
| r26-b-552-overlap-select | `9e0aa3b25acb32bd440b016dd1aa7f72a71faf11d795f50b37b0bd341e7df029` | `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592` |
| r26-b-552-tree-packed | `8d048a0797943c307501c7fb14eb92822668875d39c0e531e0c0f7396c99d682` | `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592` |
| r26-b-552-tree-prefix | `4924b7919c73d39ebd14397da566b47cf3bc6c2f66b80a9547ad803a3d336c2c` | `51b5ea83cbad026c044b5c7812c9189231f5273cc0902342c850af02a1c0b592` |
| r26-b-628-cache-hint | `1d55b3acf2db9c737b4af84a234b96d33748089dc0bb80300314192fde0581cd` | `7c909191f2801e76ac5080966d6df5339191ce48a97a16a3e66ee2a0ca4c636e` |
| r26-b-628-no-e | `d11d1ab3701bbad9dc3bca3cd6384db4a3c9c7309ca25f8c8af2c91ceafa9587` | `d44309fbdebe01cc9cc22965d8351d60837e3c7bd83a613bbe904c6f48f28c24` |
| r26-b-628-no-rf | `61e78803e576a92f3f5b110cca49f63299b5e1f4bd89fa70bd5e486dcf26ff53` | `4702b9f8909e76764598b9d807cd57b887f29c9774a4dade055a4fa6c116317c` |
| r26-b-628-rf-backward | `9ae98b2c71b3bea0a3a386fcb3d1e9a0bb4bd3335d5ed0e808955b742e0b304c` | `7c909191f2801e76ac5080966d6df5339191ce48a97a16a3e66ee2a0ca4c636e` |
| r26-b-628-seed | `17c1ee20d678fe06a97f5e048879c48dfa06311ce10f41520cc7b1ea824d7a8b` | `a1c967d692c042d3c9c7912213da0c67d98b258c4f70710eeebbd9cccfd23ab7` |
| r26-b-628-shared-cache | `bb6bbbf7048bf86a489ed6796208c0c46e929a15b30cf512cc8a49719e98239a` | `7c909191f2801e76ac5080966d6df5339191ce48a97a16a3e66ee2a0ca4c636e` |
| r26-b-628-shared-cache-fix1 | `582c3ea7236dfaa93a801a265713e3c96175d6978d895e62a9bea024fbdd39ac` | `7c909191f2801e76ac5080966d6df5339191ce48a97a16a3e66ee2a0ca4c636e` |

依据：[all-analysis-29888.json](all-analysis-29888.json)、[all-roles-29888.json](all-roles-29888.json)、[candidate-ledger-29888.json](candidate-ledger-29888.json)、[audit-close.json](audit-close.json)。
