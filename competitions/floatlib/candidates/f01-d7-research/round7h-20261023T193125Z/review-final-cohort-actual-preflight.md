# R11 实际freeze与派发预检快照

**实际选择、冻结文件和派发绑定均匹配；最终三组接受尚未发生。** 本报告新增快照，不修改旧“尚未生成”预检，不编辑任何cohort-bound文件。完整原件hash、31份本地冻结文件、33项HEAD树回执及时间链见[JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-final-cohort-actual-preflight.json)。本快照完成后锁定，A/B回收后的完整接受交原verifier。

## 选择已正确回落原D930

实际cohort SHA为 **`ebcbe8101049eac8f758533b9bb3791f3199934b62af246371cbfcf21ed57ee7`**，与外部给定digest及cohort-freeze.sha256均一致，冻结于 **2026-10-24 01:14:09.767723 UTC**。

冻结candidate为6c `6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d`；baseline为41；D固定seed930/run40044727137/job120723717708。没有用933中更好的backup样本替换D。

重新读取D930的43份、D933的46份原始成员，全部长度/hash一致；原copied Kernel分别匹配6c/41和E5/6c/41。三个933原fullgate均通过，但用冻结helper的纯compare/choose函数在原25round上重算得到：

| 比较 | whole normalized ratio | gain p05 |
| --- | ---: | ---: |
| 933 E5/41 | 0.8781800988697818 | 0.09680277381410553 |
| 933 E5/6c | **1.0003470194540243** | **−0.009184010770667328** |
| 原930 6c/41 | 0.9162235597601194 | 0.06467445202258348 |

结果与01:13:53.596576写入的真实final-selection-receipt逐位相同，严格按predeclared回落first clean D930。只有内存纯函数计算；没有重新运行gate或Git读取。

## 两个holdout的留存时间链

| 角色 | seed / run | plan冻结UTC | dispatch回执checked_at UTC | CI API createdAt UTC |
| --- | --- | --- | --- | --- |
| A | 103391 / 40048911739 | 01:14:28.712313 | 01:14:55.952924 | 01:14:57 |
| B | 103392 / 40048972520 | 01:15:17.548082 | 01:15:40.852365 | 01:15:42 |

每一条留存时间链均严格晚于01:14:09.767723 cohort freeze。checked_at是dispatch回执中的检查时间，不冒充独立观测的网络发送时刻。API返回实际HEAD分别为A `68599c02e8a0ab5c322183ff25b8c0ea1c3bce7d`、B `152bdd78649b463e3c5904290ba881c41762726a`，均与各自source_commit一致。

两个plan均为FROZEN_INDEPENDENT_CONFIRMATION，绑定相同cohort SHA及正确A/B角色，prior discovery均为原40044727137；source hash固定6c/41，capture/profile均关闭。各seed在已留存dispatch记录中只有对应这一次派发。旧预检于01:08:48观察到没有FROZEN确认plan，现有plan记录也在freeze后；未生成或查看任何未来drawn输入。

A和B的实际候选顺序均为[41,6c]，分别满足对D的reverse和rotateleft。两个source下两者相同是预声明算法的结果，不能称三种不同顺序。

## 31文件与33项HEAD树绑定

**31/31 cohort文件当前SHA均匹配**，包括两个Kernel/manifest、choice/predeclared/receipt、选择与验收helper、renderer/estimator及11份执行链。关键helper为：final-choice `1014685a…47402c0f`、freeze `24ccacd0…d59e30e`、verify `84b7c319…85af41a`、adopt `698c9836…d56ebc`、binding `8783d5a8…85b212`；所有完整hash列于JSON。

Root于01:20:41生成的 [cohort-commit-tree-preflight.json](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/cohort-commit-tree-preflight.json)记录D/A/B各11份、**33/33**本地immutable Git blob与common execution freeze匹配。本审查没有自行执行Git；逐项核对该回执的source HEAD、run和source_receipt与原dispatch API回执一致，并核对33个digest等于cohort.execution_files。

该回执范围严格为“原dispatch API实际返回HEAD的本地Git对象”，不等同A/B最终运行环境或artifact输入已通过。11份执行链保持原workflow/CI/outer/public wrapper/D7 adapter；原D7 adapter仍为86084d93…eafca24，outer为519a1898…b165904。选择helper/两份JSON只属LOCAL_REVIEW，未改变旧D930必须匹配的执行链。

## 新鲜测试与剩余验收

只读确认以下Root原日志，没有重跑tests：

- 27项verify：`final-cohort-verifier-tests.txt`，131 B / `ba2630c087ccc979f8a3fd5785d09d85cd84081cd62b6a32fbb0290f97abf47b`，OK。
- 19项adopt：`final-adoption-tests.txt`，123 B / `01b660c2a9e3e8948d702e5b79ca7dd67cdd69923bbee1306d2e23eeda6c113a`，OK。
- 2项choice：`final-choice-2-tests.txt`，105 B / `4cd49ad0c73a8aa832fab522c6a78b7c7920d0020aa82b81b4234fa118a1a5f0`，OK。

`final-choice-regressions.txt`仍是freeze前缺真实receipt导致27errors的历史负面日志；未改写，未误计为新鲜PASS。旧预检MD/JSON仍分别为af07907e…bc392b9、b4d487f9…8bffaa8b。

本次检查时A/B原artifact目录尚未回收到本地；dispatch中in_progress只是当次API状态，不据此判断此刻线上终态。A/B actual job、copied inputs、drawn-plan实际shape/生成多样性、原suite/generator/verdict/25rounds及最终.97/p05门槛均为待回收项，不填零或预报通过。

收齐后仍须按同一external cohort SHA，由原guard重新完成artifact-bound HEAD/plan/Kernel与11文件执行绑定，并让三组verifier逐组验收；之后才可运行adoption。当前仅actual freeze/dispatch preflight匹配，**不是最终接受、adoption或正式冠军准入回执**。
