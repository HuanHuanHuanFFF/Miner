# Released-source final12 binding survey

Only pre9 sourcecache5/12/13/19/23/27; current champion sources were not read. `operator-binding-matrix.json` records exactsourcehashes, all12 actualresolvedfields, localcallee bodyhashes and directfunction=Spec theoremanchors. ExtendsD public-crossboard-structure; no newCI orcandidate.

| Source | Dense | Conv/element deviations fromkernels0 | Norm |
|---|---|---|---|
|5|YaV,Ya3|Ybp/dwQ;Ybk/Ybl/Ybf/Ybe|Ybb,Ybc|
|12|preparedYaV;gemmWithYn|none|Ybb2,MYbc|
|13|prepared+4columnYaV;gemmWithYn|none|bothlegacywithYn|
|19|simpleYaV,Ya3|nativeaddReluYbf|legacyRMS,MYbc|
|23|sameYaVbytesas12;gemmWithYn|none|Ybb2,MYbc withnative128stats/sqrt|
|27|sameYaVbytesas19;Ya3Q|nativeaddReluYbf|legacyRMS,MYbc|

Core fields areYaN/YaM inall6. Theirnamesalone are notperformanceequivalence; exactbodyhashesareinJSON.

Amongdirectfunction=Spec equalities, theonlyrootnotlexicallyruntimereachableis12Ybb/T4. It usesgenericYaE denominator, whileactual12Ybb2usesYaEf; 23furtherusesnative128. Thus it is anoldsupersededRMSwrapper, notanewunwiredhigh-ceilingoperator. Thissearch isbounded: pointwisestatements andimplicitcallsare notexhaustivelyelaborated.

A distinct transferablemechanism exists in13, alreadywiredtherebutabsentin23: **prepared/sparse four-output reuse**. 23row<2 quadpath usesQPac4 onlywhenPempty; sparsepreparedrows alsofall throughscalarswhen4rowreusefails. 13QPq4 dispatchesunpreparedQPac4 / densepreparedQPad4 / sparsepreparedQPas4, andYT4lreceivesF4/D4 forscalarrowfallback. Thisisnotjustswitchingrow/columnorder; it addsactualfour-outputpreparedaccumulators. ZcCstillprovesYaV=linearSpec.

Staticportdelta isabout22912B:12missingdeclarations plusreplacementsYT4l,YaV,ZB4,ZB6,ZcC. Thetwo mainproofsQDd4/QDs4 total10645B; runtimeQPad4/QPas4 total5027B. Frozen9free3281B isinsufficientforstraightport; droppingunusedoptimizedRMS aloneadds4499B andstilldoesnotfit. Actualspeed/benefitUNKNOWN. Do not callfour-outputreusea4xspeedup.

This supports a futurewholeMixercostdiscriminatorifproofspacecanbesolved, but **doesnotopenanotherqueue now**. CurrentNativeAddstructuralcompletion remainsconcrete andsmaller.5conv/elementgraft stillneedsa largerproofclosureasrecordedunderfollow-on/crossboard/.
