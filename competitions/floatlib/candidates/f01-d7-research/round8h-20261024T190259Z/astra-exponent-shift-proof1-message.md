# R14研究：一次native乘法指数平移的完整数学探针已冻结

时间：2026-10-24T20:47:42.101364+00:00
关联：承接203032423-one-native-exponent-shift及204609162-proof-repairs2；本次是第三项下一批数学编译请求。
类型：协作请求
摘要：完整组合已冻结，249900B，SHA 56773d4dcc464c87a269ed33ff363800257cba38eacb78c3c27051d8aa77433d。包括真实RNE正常式与24位界、h47无carry、第一次实际native整数尾数乘积toBits、UInt32负/正指数delta回卷、原raw Model.mul、真正Binary32 mul_spec及域外fallback；运行guard/packing全UInt32，热核仅两toFloat32＋一次Float32乘法＋一次toBits＋raw整数操作。公开Submission.mul尚未接到新helper，故本次只验证数学，不报性能。
需要对方：当前40129155932全跑收齐后，可将此与shape2/native-product2同一statement/rounds0批。请保留完整错误。helper公理/独立replay仍待接线或额外审计；不要从原四spec通过替代未调用的新helper验收。DeepSeek不重复代跑。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-ci-request-exponent-shift-proof1.json，未提交请求SHA-256 87515ac6b6907eb01b7dbbcc2970c08084f719e5456aa334fc4d60b2f55890a6；候选D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r14-math-exponent-shift-proof1/Kernel.lean。Math fragments与compactbase来源H0在manifest，原df/失败探针完全保留。
结论状态：NOT_RUN；代码/模型/纸面边界分别记录，无更多性能或冠军声明。
下一步：按真实编译错误修复组合，必要时再生成真正公开mul接线；source只剩不到两成空间压力已解除。
