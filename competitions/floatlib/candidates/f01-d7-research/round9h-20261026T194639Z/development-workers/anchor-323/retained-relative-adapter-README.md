# R19 retained-relative adapter：接口与内存集成复验

UTC 2026-10-26 20:54:08接手，预算20分钟。只新增本目录文件；core `916bf5b18b6c1a799ded2b1420e7bea49ac34ecbca18e99a45207ccc204d5524`、早前anchor/build及两个旧MANIFEST不变。无Git、CI、Lean或全局写入，没有读取40398675395结果。

[adapter](retained-relative-adapter.py)的`load_estimator()`返回**实际原estimator模块对象**。原`checked_record`、`validate_anchor`、`save`函数不变；新main中的每次写入均动态调用返回模块的`save`，因此旧adopt的Tx拦截仍生效。DEFAULT_ANCHOR继续是reviewed323；数学内核使用冻结ab3b＋旧41校准，不把derived B2成本伪装成原始gate。

## D的最小接入

1. 复制adapter为R19的`development-estimator.py`（字节不改时哈希相同，依赖路径从仓库根定位）；freeze阶段载入后，将`estimator.EXTRA_FROZEN_FILES`全部加入cohort `files`。
2. 原verifier完成且`accepted/group_count=3/no failures`检查通过后，调用`estimator.bind_frozen_cohort(freeze,runs)`。随后保留现有`select_pairs`、`estimate_from_anchor`、`main`和Tx/rollback调用顺序。不可提前bind后跳过原选择guard。
3. 在原`frozen()`检查中同时重新核对EXTRA_FROZEN_FILES。adapter在bind/select/estimate/main时也会按freeze哈希再次检查；缺项直接拒绝。

```python
estimator = adapter_module.load_estimator()
# freeze构造阶段，仅枚举依赖，不需bind：
files += list(estimator.EXTRA_FROZEN_FILES)
# adopt阶段，原verifier判定成功之后、首次select_pairs之前：
estimator.bind_frozen_cohort(freeze, runs)
```

EXTRA_FROZEN_FILES共7项：实际adapter入口、原estimator、core、冻结ab3b副本、旧41 anchor、reviewed323 anchor、R19 selection-policy。复制为D入口后，列表中的adapter路径自动指向该实际入口，其余依赖仍从worker目录读取。原D额外41要求和所有选择条件保持原样；本任务不修改任何D入口。

## 适配行为

- bind锁定真实D/A/B的run、seed、精确候选及保留模型；同一绑定可重复调用，不能换cohort。bind假定调用方已经通过原verifier，不能自行证明首D、未见holdout、.97或正p05。
- select严格认证完整声明source的恰好3行，不允许遗漏、重复或额外full source gate；逐行调用原checked_record，匹配同artifact目录B2，重新读取真实requested-plan并拒绝profile/codegen observer，再按已绑定run附role。estimate还会重新认证pair，拒绝调用方篡改内存classes。
- 新源method与预先声明政策一致：`FROZEN_RETAINED_B2_NORMALIZED_PAIRED_DELTAS`；另记录core原method。formula沿已审核的C/B2方法，model记录新时间、实际adapter/core/原estimator哈希、候选/retained/anchor身份、当前索引/官方回执、cohort canonical哈希。当前reviewed anchor payload与旧control payload分开，当前索引与冻结control索引分开。
- main沿当前official snapshot的原字节回执认证fresh323身份、suite和successor/verifier链；没有网络请求，也不自动更换冠军分母。新模型/视图/状态三次写入全部经`estimator.save`。
- 同源B2的模块main和独立CLI均严格返回ab3b原字典/原序列化字节，零save调用，不读十组later controls重拟合。独立CLI必须`--dry-run`；新源main若尚未bind直接拒绝。

## 复验及范围

运行`python -B competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-workers/anchor-323/verify-retained-relative-adapter.py`。

[integration回执](retained-relative-adapter-integration.json)认证历史三组C=df5c/B2原件，借其run/seed构造**接口fixture**，模拟调用方已经成功验证的阶段；不声称这份历史候选满足R19选择条件。fixture只需C+B2展示估算接口，生产D的额外41 verifier约束仍保留。新数值与已审核纯core精确一致，whole `1.3202500263319141`。

已实测：原模块/原认证函数身份、B2逐字节identity、15个拒绝路径（缺绑定、缺extra freeze、缺组/坏gate、额外源gate、缺B2、raw哈希/classes篡改、真实计划observer、24轮/未pass、换cohort及save失败）。新源三次save仅进入内存，model/view/state的method/source及model证据哈希完全对应；原全局文件字节不变。

save失败测试只模拟外层Tx回滚并确认异常传出；没有在真实D adopt上写入后回滚。D仍需对复制后的入口执行原集成/根自检，并保持原verifier/Tx。原adopt在main之后会恢复旧dashboard_policy：请确保其预先冻结的display policy已指向当前R19入口，避免UI解释器路径陈旧；模型和summary的新method不受这一步影响。

数学输出仍是INFERRED，六份B2成本为derived，直接对冠军比较及正式admission UNKNOWN。当前完整D的结果、第一D资格及A/B确认均不在此fixture验收范围。本次产物和冻结旧文件哈希见`retained-relative-adapter-MANIFEST.json`。
