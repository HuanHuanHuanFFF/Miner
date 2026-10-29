# Normal-or-zero binary64 proof domain after runtime freeze

Paper proof decomposition and finite falsifier only. No new runtime fragment,
CI, competition target implementation or performance confirmation. The source
and cost inputs remain frozen. All Lean/native model bridges below are UNPROVED.

For an actual finite binary32 word, write its value as sign*m*2^(idx-149),
where idx=max(E-1,0), m=frac for E=0 and m=2^23+frac otherwise. Then m<2^24,
idx≤253, and every value is an integer multiple of2^-149. Zero is included.
The widened value is normal64 or signed zero, even for input subnormals.
For E=0, frac>0, k=floor(log2 frac)≤22: the recipe's binary64 exponent field is
k+874 and mantissa is (frac-2^k)*2^(52-k), giving value frac*2^-149 exactly.
Normal inputs use exponent E+896 and fraction frac*2^29. A formal theorem needs
the actual fastLog2/raw adapter and signed Float.ofBits bridge, not just this algebra.

Every binary32 product has at most48 significant bits, lies below2^256 and,
if nonzero, has magnitude at least2^-298. It is exactly representable in binary64.
For addition, use a lattice invariant: each exact pre-round sum is z*2^-298.
If its binade exponent e≥-246, binary64 rounding quantum2^(e-52) is a multiple
of2^-298. If e<-246, |z|<2^52 and the pre-round value is already exactly
representable. Thus rounded prefixes stay on this lattice. A nonzero prefix
cannot become a binary64 subnormal; cancellation can still produce signed zero.

Let n≤2^30, H be the SAME two separable cached maxima as the executable, and
M=2^(H-250). Each product magnitude is strictly below M. Let u=2^-53.
Inductively |s_j|≤j*M*(1+u)^j≤j*M/(1-j*u). In particular |s_j|≤2*n*M≤2^287,
so exact addition arguments are below2^288 and cannot overflow binary64.
Together with the lattice lower bound this discharges normal64-or-zero premises
for each native operation, provided the actual rounding/model bridge is available.

A simple absolute error bound avoids a loose gamma_n*sumabs estimate:
local error |delta_j|≤j*u*M/(1-n*u). Summing gives
|s_n-exactSum|≤u*M*n*(n+1)/(2*(1-n*u)). For n≥2, n*u≤2^-23≤1/4 and
n+1≤3*n/2, hence this is ≤u*M*n^2. For n=1, product and first addition are
exact numerically. With L=ceil(log2 n), n≤2^L, the executable radius is
B=2^(H+2*L-303)=u*M*2^(2L), so the desired absolute enclosure follows.
This does not itself establish the endpoint RN64/order-key/midpoint checker;
those remain separate actual-word obligations. Sign of zero also stays separate.

`finite-lattice-model.py` exercises72 new untimed proof-falsifier dots (two seeds,
lengths1..4096, input subnormal/extreme/cancel cases),46050 products/prefixes.
It checks exact products, finite normal-or-zero prefixes, the lattice denominator
and executable B. The report has no raw input fixture and is not a fresh cost
confirmation. Abstract boundary arithmetic is checked up to n=2^30; this is not
an all-n proof. It found no counterexample. Its UNKNOWN fields remain explicit.

`forged-prepared-counterexample.json` refutes the weaker proposed interface
that valid=true plus matching lengths suffices. Two records raw=[+0], values=[1],
maxIndex=0, valid=true produce model accepted1.0 although exact raw dot is+0.
The measured wrappers prepare canonical caches and are unaffected. State the
soundness theorem for `prepare(raw)` or a cache invariant including values/length/
maxIndex. Do not prove an unsound forall-Prepared theorem and then silently use it.
