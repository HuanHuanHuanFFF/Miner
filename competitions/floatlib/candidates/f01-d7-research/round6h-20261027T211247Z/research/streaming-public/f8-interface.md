# F8 四行×双列：最小索引接口，待 D 精确源

`DoubleColumnIndex.lean.inc` 仅给 `G=R15ThinPairs.groups p=(p+1)/2` 的输出列映射与逐字段 step 运输，6 根均 **NOT_RUN**，未定义 F8 运行体或准备布局。

- 对有效列 j : Fin p，读取 cell `j/2`、内部列 `j%2`；`group_lt` 和 `lane_lt` 提供索引证据，`column_recompose` 恢复原列地址。对任意有效cell，其第0列必有效；若第1列无效，`padding_column` 证明它恰为p且p为奇数。p=0没有cell或输出列。
- `selected_field_step` 将 D 的实际8字段更新等式运输为原 `R20WideRowRefinement.storageLoop_lane` 所需的有效输出列 step。此时 a 应为该实际row的A解码；hfield必须来自实际mapIdx/update与prepared B读取，不能把这个条件接口当F8已证。
- 原raw B逻辑地址仍为 `bi*n*p + k*p + 2*g+c`。若物理prepared F2是k-major，则可能使用 `bi*n*G + k*G+g`；若是旧B2 group-major，则读取顺序不同。必须等D精确源固定后再接对应get定理，不能把raw stride p替成G或复用另一布局地址。
- prepared读取证明只需实际循环的 `k<n` 及合法bi/g；现有 `R20WideRowRefinement.storageLoop_lane` 已在hstep提供这个前提。不要为了复制旧raw-quad的无条件advance_view签名，额外证明未被执行的任意k默认值路径；可把hk保留在具体step投影里，再由通用loop消去。
- padding列可以有自己的算术结果，但writer只选有效j；不得让padding列的NaN/符号零改变任何有效lane。原四行逐lane finish与raw NaN replay保持，p奇尾只影响最后cell的第1列是否发出。
- 不额外假定padding字段为+0：已核原 `R15PackedB2.packB` 直接读 `base+1+k*p`，p为奇数时未使用的右列可能读到下一行/下一batch的首值，而不一定越界为posZero。`selected_field_step` 因此只要求 `2*g+c<p` 的字段等式；新producer若显式填0也须按它自己的源证明。未发出的lane不影响有效结果，才是应保留的不变量。
- 一旦B关闭新 `rows4_eq_control`（仍为4次原dot row-major emit），现有A的group/flat尾行/batch运输可迁移。当前 e4bf raw-quad、PreparedQuad及d44d运输都冻结；新源必须重新绑定和核验，不继承77a的38根或任何成本。

下一最小动作：读D的确切Cell字段次序、prepared索引和rows4选择函数；只补缺少的get/field投影或实际writer适配，不再造同类运行体/网格。
