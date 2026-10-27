# GRS jam-to-RNE progress saved at DirectBias preemption

Status: PAPER / NOT_RUN. No runtime, no new candidate, no CI. Work paused by R after direct-bias runtime code generation closed positively.

Target: roundShiftRightEven (jam p d) k = roundShiftRightEven p (d+k), k in {2,3,4}, arbitrary drop d.

Let D=2^d, C=2^k, p=D*(C*q+v)+r, v<C and r<D. Arithmetic jam is p/D + (if p%D=0 then 0 else 1-(p/D)%2). After extracting the even C*q, its low remainder is j=v+(if r=0 then 0 else 1-v%2), with j<C because C is even. Use a separate quotient-block lemma for roundQuotientEven (r+C*q) C that exposes only q, r, C; prove div/mod with Nat.add_mul_div_left, Nat.add_mul_mod_self_left and exact div/mod equations, not omega over original p.

Reduce to the local decision equality at low residues: decision(q,j,C) = decision(q,D*v+r,D*C). Original remainder bound follows D*v+r < D*(v+1) <= D*C. Split only C=4/8/16 and v=0..C-1 (28 tiny residue states total), plus r=0/nonzero; then all comparisons are linear in D/r with fixed coefficients. No enumeration of d, no generic multiplication-heavy omega. Reconstruct p with Nat.div_add_mod twice, Nat.div_div_eq_div_mul, pow_add.

Known fixed Lean APIs: Nat.div_add_mod; Nat.div_div_eq_div_mul; Nat.add_mul_div_left (x z) (H:0<y); Nat.add_mul_mod_self_left (x y z). Bitwise jam bridge can reuse Nat.or_div_two and Nat.or_mod_two_eq_one to show n OR 1 = n+1-n%2. The former Jam17 rne_jam has already been verified, but this generalization is not yet Lean code or accepted proof.

Remaining obligations: arithmetic-jam quotient preservation; fixed-low-bit local decision lemma; exact bridge from runtime add/sub GRS T to jam of the original dyadic magnitude; Model.add fields/carrier proof. Existing uint32_model_eq_roundDyadic covers arbitrary UInt32 T, including legal cancellation T=4.
