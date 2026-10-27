# DC第一判别：停止重做双侧R2数值转换

01:06 UTC检查点，距01:01接手约5分钟。**直接把NativeFinal.dotLoop两侧toFloat32改成R2W01b.convert是已完整负测机制，不建议再排D。** 精确d5e3512f/235524B、run39961709177全gate通过，但BMM归一化1.173127、whole1.040345。脚本逆替两处directDecode后，旧dotLoop与当前622d逐字相同；R2W01b全部runtime声明也逐字相同（删过的旧proof不作runtime差异）。这比旧f65 B1-only及f84 B2-only更直接。

边界没有偷换：旧R9仅n≤4或p≤2的DirectSmall writer；当前DC12例中5例落旧形状域、7例为后来扩展域。旧R9并非新622d/DC的同源同输入对照，不能宣称已测当前12例全部失败；但新m1..3/p3..8本身没有改变每k双numeric转换的成本前提，不为新分派重开同机制。

已核run39961709177全部43原件和CI10全部138原件的SHA/大小/集合。实际622d MainFull闭包→public bmm→B2 miss→B1 miss→bmmBeforeR11Cross→DC output→两个专化fold→NativeFinal.dot→dotLoop已逐边确认，摘录在本目录。每k C有2个ofBits、两边getD bounds/default、3个Nat add/1 mul/3 lt；无显式alloc/apply站点，Nat大数helper内部仍可能分配。现有ASM未采NativeFinal.dotLoop，spill/机器call成本UNKNOWN，不从B2或独立converter借用。

**唯一不同且可证伪的备选**是无A.map/无B.map/无pack的raw双列loop：每完整双列/k共享A读取/转换与循环，保留两次原B ofBits，奇数尾列直接旧dot。它删去真实重复A call，而非用table/cast/mul替换call；旧R15 pairs必须B整次map、m≥4，f84只B2，所查未发现这一无准备DC实现已测。先只给精确设计，不为凑时长拼宽度网格。

原逐case ns直接重算：DC为BMM44.337%/whole7.1908%；p≥2备选10例为whole5.97846%，p1两例保持原样。此样本中即便全删DC也不能支持whole10%。要由备选独自达whole3%，需该完整边界降低50.18%；转换在DC中份额仍UNKNOWN，不能从MAC数或call减少比例推耗时。建议优先级低于真正能影响whole10%的工作；下一步只值得一次selected-C判别，尚不值得直接完整D。

新Lean/C/ASM/D均NOT_RUN；其他public3项、outer underflow、B2及所有原文件未改。
