# 后续边界checker：128位有序差，64位half/quarter guard

仅有限数学模型，**尚未生成原生边界实现或新candidate**；先等power-cell2与broad WordGap128的真实typing。与broad约定本方覆盖power2/minnormal/tie，broad冻结strict interior体，不改其文件。

令M=2^23、P=M*D，N为完整128位分子、D为64位正分母。先比较完整128 N/P并求有序绝对差，不能只比较或减low limb。要求gap.high=0，令g=gap.low。

1. 先验`g<D`，使`D−g`没有unsigned下溢。
2. 再验`g≤D−g`，等价`2g≤D`；D<2^64从而后续g+g不会溢出。
3. 如果N≥P，上侧这个half闭区间已足够。
4. 如果N<P且目标E=1（minnormal），下侧也只需half。
5. 如果N<P且E≥2，构造t=g+g，验`t≤D−t`，等价`4g≤D`。因为步骤2先成立，t和D−t都按真实Nat值解释。

M恒even，所以这些端点tie可接受。若推广到其他mantissa，不能省掉odd/tie处理；broad的strict内部checker故意拒绝所有tie。

`gap-boundary-model.py/json`对153246个有理/word样例将该分层UInt64模型与实际roundRatScaled模型及powerCell逐项比较，均一致；45091是观察到的接受计数，不是成功概率。全部254正规目标指数、全64位分母边界、128位gap/跨limb和下面4个错误guard均保留：

- 省high：N=P+2^64造成low gap0，错误接受。
- 省g<D：D=1,g=2^63，上侧D−g下溢后错误接受。
- 先doubling且省half：D=2^64−1,g=2^63，下侧g+g wrap成0，错误quarter接受。
- 把闭half用于odd mantissa：M=2^23+1、D=2、N=2M+1，上侧tie应选下一个even word，错误接受旧odd word。

D=0也明确拒绝。今后原生桥应复用broad `gap_toNat_cases`的完整有序差结论和本方actual powerCell定理，不另造hcell假设，也不从有限模型声称Lean、ABI或成本通过。数学原型不定义新ContractExact Kernels。
