# Initial-leading-bit carry fusion: independent paper argument

Scope: D's fixed question in message004224, original biased branches unchanged, normal inputs and S128..380. This is a mathematical review, not a compiled Lean/public correctness or speed result. The original source is `R19DirectBias.normalCore` in fa652/88cdf. D owns new runtime and CI; R creates no replacement Kernel.

Let P=M₁M₂ with 2²³≤Mᵢ≤2²⁴−1. Therefore 2⁴⁶≤P≤(2²⁴−1)². Put h=⌊P/2⁴⁷⌋∈{0,1}, t=23+h, and B=P+(2^(t−1)−1)+(⌊P/2^t⌋ mod2). This is exactly the old two-branch ties-to-even bias, including parity. Let Q=⌊B/2^t⌋. Proposed magnitude is ((S−128+h)·2²³)+Q, using addition. Old code takes h′=⌊B/2⁴⁷⌋, q=⌊B/2^(23+h′)⌋ and packs ((S−127+h′)·2²³) OR (q−2²³).

For h=0, B<2⁴⁷+2²² and B≥2⁴⁶, so 2²³≤Q≤2²⁴. If B<2⁴⁷, h′=0 and Q=q<2²⁴. Subtracting the hidden bit from Q and adding one to the exponent is the same integer value as the proposed sum. The fraction is less than2²³, so old OR equals addition. If B≥2⁴⁷, then Q=2²⁴ exactly and q=2²³; proposed magnitude is (S−126)·2²³, exactly the old carried exponent and zero fraction. No bit of B beyond the carry can survive Q in this interval.

For h=1, B≤(2²⁴−1)²+2²³=2⁴⁸−3·2²³+1<2⁴⁸ and B≥2⁴⁷. Hence h′=1 and 2²³≤Q=q<2²⁴. The proposed sum again equals old exponent plus q−2²³, with disjoint old fraction/exponent fields. This upper bound is necessary: permitting arbitrary P<2⁴⁸ would incorrectly admit a second rounded leading bit.

The encoded exponent in the non-carry cases is S−127+h, in1..254; the h=0 carry case gives S−126, in2..254. Thus the unsigned magnitude is below0x7f800000, its sign bit is clear, and the proposed UInt32 addition/left shift has no wrap in the stated domain. Adding the sign with OR is safe. These arguments use natural/integer S−128 (S≥128); an unproved wrapping subtraction outside the guard is not allowed.

A real normal-mantissa carry witness is M₁=0x800001, M₂=0xfffffe: P=2⁴⁷−2 and h=0, while B crosses2⁴⁷. At S130, Q=2²⁴ must **add** into the exponent. Replacing the proposed addition by OR gives0x01000000 instead of0x02000000. At S129, even the no-carry P=2⁴⁶ witness rejects OR: correct0x01000000 versus0x00800000.

Conclusion: the proposed arithmetic identity is sound over the stated exact interval. The new source still needs actual UInt32/UInt64 bridge elaboration and the original public MUL proof. The compiler may or may not turn initial h into a shorter dependent chain; selected actual callback C/ASM and complete guarded timings decide that separate premise. No percentage saving follows from this proof.
