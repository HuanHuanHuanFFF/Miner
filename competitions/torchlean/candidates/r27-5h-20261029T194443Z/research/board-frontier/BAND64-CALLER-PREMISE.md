# C bounded follow-on Band64 review

Read-only/source-and-integer review after00:00, no newcandidateorCI. Frozenhelper32d82657… has correctvisiblebias andzero-shift branches. D'sBand11 outcome iscompilefailurefromtwoNat/UInt64typegoals; runtimecostUNKNOWN, notan algorithmnegative.

- RealYc usesmin(absword-1), notsimplyminidx. Arowof1.0 hasbase125/high126; anallzero row hasbase510 andwrappedlargeQYF, hencewholecallfallback. Do notusea fictitiousallzero cachecaseasreachablefastinput.
- LocalX factor<2^27, cachedWfactor<2^30; each64productblock hasabsolute mass<2^63. Foractualn<=2^20 andbiasedrawrange<=58, originalproductmetadata givesbodymass<2^126 andbias<2^105, hencefinalsigned128 fits. Intermediatebandprefixes needthesameabsolute-massbound; multiplyingindependentloosebandbounds canlose9bits.
- True bias exponent isidxBias+149-base, whiletheguardrawBias isidxBias+126. Legalrows4,n16,onesX/alternating±1W,bias1 gives1.0; using126inthevalue yields2^-23.
- Atzero shift, legalonesdotn16 hasbase250,groupLo=2^52,groupHi=0. Correct16.0; treatingUInt64rightshift64asno-op polluteshighandproduces2^68. Actualshhi hasexplicitdelta0 branch. ExactvaluesinBAND64-ENDPOINT-PREMISE.json.
- Cacheindices,stablecountingpartition, metadata/getter agreement andfinalzero fallback remainessentialformalbridges. A generic64-term integer theorem alone doesnotproveactualdensecaller.
- PotentialduplicateBX/BV scans onwholecallmiss arevisibleinwrapper, butactualfixedsuitewideinputs stilluse normal-scaledweights; do notinferweightspanfailurefromthelabelwide. Fullcostmustincludecacheprep/gather/lost4rowreuse/fallback/output.

No actualcounterexample tothissourcefoundhere; thisisnotall12proof, completevalidation orspeed evidence. No9or10confirmationinputsused.
