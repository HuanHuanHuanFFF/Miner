
/--
The special floating-point value `NaN`, short for “not a number”. This value comes up as the result
of erroneous computation like `0 / 0`.

Comparing any value with `NaN` using `==`, `<`, `≤` results in `false`, including `nan == nan`
and `nan ≤ nan`. However, comparing with `NaN` using propositional equality will result in `true`
if and only if the other value is also `NaN`, which means that `nan = nan` is true.

Note: While there are many bit patterns that represent a “not a number” value, they are all equal
in the logical model of `Float`, that is, all floating-point values `f : Float` with `f.isNaN`
are propositionally equal to `nan`.
-/
def Float.nan : Float := .ofModel .nan

/--
The special floating-point value `+Inf`, short for positive infinity, used as a result for
overflowing computations like `1 / 0`.
-/
def Float.inf : Float := .ofModel .inf

/--
Adds two 64-bit floating-point numbers according to IEEE 754. Typically used via the `+` operator.

This function has a logical model in terms of `Float.Model`. It is compiled to the C addition operator.
-/
@[extern "lean_float_add"] def Float.add : Float → Float → Float :=
  fun a b => .ofModel (a.toModel + b.toModel)

/--
Subtracts 64-bit floating-point numbers according to IEEE 754. Typically used via the `-` operator.

This function has a logical model in terms of `Float.Model`. It is compiled to the C subtraction operator.
-/
@[extern "lean_float_sub"] def Float.sub : Float → Float → Float :=
  fun a b => .ofModel (a.toModel - b.toModel)
/--
Multiplies 64-bit floating-point numbers according to IEEE 754. Typically used via the `*` operator.

This function has a logical model in terms of `Float.Model`. It is compiled to the C multiplication operator.
-/
@[extern "lean_float_mul"] def Float.mul : Float → Float → Float :=
  fun a b => .ofModel (a.toModel * b.toModel)
/--
Divides 64-bit floating-point numbers according to IEEE 754. Typically used via the `/` operator.

In Lean, division by zero typically yields zero. For `Float`, it instead yields either `Inf`,
`-Inf`, or `NaN`.

This function has a logical model in terms of `Float.Model`. It is compiled to the C division operator.
-/
@[extern "lean_float_div"] def Float.div : Float → Float → Float :=
  fun a b => .ofModel (a.toModel / b.toModel)

/--
Negates 64-bit floating-point numbers according to IEEE 754. Typically used via the `-` prefix
operator.

This function has a logical model in terms of `Float.Model`. It is compiled to the C negation operator.
-/
@[extern "lean_float_negate"] def Float.neg : Float → Float :=
  fun a => .ofModel (-a.toModel)

/--
Strict inequality of floating-point numbers. Typically used via the `<` operator.
-/
@[extern "lean_float_decLt"] def Float.lt : Float → Float → Bool :=
  fun a b => a.toModel < b.toModel

/--
Non-strict inequality of floating-point numbers. Typically used via the `≤` operator.
-/
@[extern "lean_float_decLe"] def Float.le : Float → Float → Bool :=
  fun a b => a.toModel ≤ b.toModel

/--
Bit-for-bit conversion from `UInt64`. Interprets a `UInt64` as a `Float`, ignoring the numeric value
and treating the `UInt64`'s bit pattern as a `Float`.

`Float`s and `UInt64`s have the same endianness on all supported platforms. IEEE 754 very precisely
specifies the bit layout of floats.

This function has a logical model in terms of `Float.Model`.
-/
@[extern "lean_float_of_bits"] def Float.ofBits : UInt64 → Float :=
  fun a => .ofModel <| .ofBits a

/--
Bit-for-bit conversion to `UInt64`. Interprets a `Float` as a `UInt64`, ignoring the numeric value
and treating the `Float`'s bit pattern as a `UInt64`.

`Float`s and `UInt64`s have the same endianness on all supported platforms. IEEE 754 very precisely
specifies the bit layout of floats.

This function is distinct from `Float.toUInt64`, which attempts to preserve the numeric value rather
than reinterpreting the bit pattern.
-/
@[extern "lean_float_to_bits"] def Float.toBits : Float → UInt64 :=
  fun a => a.toModel.toBits

instance : Add Float := ⟨Float.add⟩
instance : Sub Float := ⟨Float.sub⟩
instance : Mul Float := ⟨Float.mul⟩
instance : Div Float := ⟨Float.div⟩
instance : Neg Float := ⟨Float.neg⟩
instance : LT Float  := ⟨fun a b => a.lt b⟩
instance : LE Float  := ⟨fun a b => a.le b⟩

/--
Checks whether two floating-point numbers are equal according to IEEE 754.

Floating-point equality does not correspond with propositional equality. In particular, it is not
reflexive since `NaN != NaN`, and it is not a congruence because `0.0 == -0.0`, but
`1.0 / 0.0 != 1.0 / -0.0`.

This function does not reduce in the kernel. It is compiled to the C equality operator.
-/
@[extern "lean_float_beq"] def Float.beq (a b : Float) : Bool :=
  a.toModel == b.toModel

instance : BEq Float := ⟨Float.beq⟩

/--
Compares two floating point numbers for strict inequality.

This function does not reduce in the kernel. It is compiled to the C inequality operator.
