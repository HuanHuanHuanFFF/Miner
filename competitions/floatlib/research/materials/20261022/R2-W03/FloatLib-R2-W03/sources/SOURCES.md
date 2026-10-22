# 固定一手来源

本报告的公式、反例、C诊断和排序结论为本轮推导／测量。源码事实由下列固定链接支持；实际下载文件的完整SHA256见 `sources/source_manifest.json`。

- [S1] [官方 ContractTensor.lean（固定commit）](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean)
- [S2] [官方 BenchTensor.lean（固定commit）](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean)
- [S3] [官方 lakefile.lean（固定commit）](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/lakefile.lean)
- [S4] [Lean v4.34.0 lean.h](https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h)，重点3253..3272及array／unbox／once函数。
- [S5] [Lean v4.34.0 object.cpp](https://github.com/leanprover/lean4/blob/v4.34.0/src/runtime/object.cpp)，重点1987..2004。
- [S6] [Lean v4.34.0 Float/Float32.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean)，重点13、38..44、90..109、132..146、303..316。
- [S7] [Lean v4.34.0 Model/Float32.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean)
- [S8] [FloatLib Native/Integer/Constructors.lean（固定pin）](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/Constructors.lean)，公开round_shiftLeft与private帮助引理。
- [S9] [FloatLib ModelRounding/Proof.lean（固定pin）](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean)
- [S10] [FloatLib Model/Packing/Finite.lean（固定pin）](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Packing/Finite.lean)
- [S11] [Lean v4.34.0 SInt/Float32.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/SInt/Float32.lean)
- [S12] [FloatLib Native/Integer/FromInt.lean（固定pin）](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/FromInt.lean)
- [S13] [Lean v4.34.0 LCNF/EmitC.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Lean/Compiler/LCNF/EmitC.lean)、[Array/Basic.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Basic.lean)、[FloatArray/Basic.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/FloatArray/Basic.lean)。普通命名定义与closed-term cache区分见EmitC对应生成分支。
- [S14] [Oracle Numerical Computation Guide，IEEE Arithmetic](https://docs.oracle.com/cd/E19059-01/stud.10/819-0499/ncg_math.html)，第2.1.1节与表2-2／2-3。
- [S15] [Lean v4.34.0 src/CMakeLists.txt](https://github.com/leanprover/lean4/blob/v4.34.0/src/CMakeLists.txt)，219..221，关闭浮点收缩。
- [S16] [Lean v4.34.0 Lake/Config/LeanConfig.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/lake/Lake/Config/LeanConfig.lean)，117..121，release C优化参数。

