import ContractExact

/- Original minimal interfaces for the exact proposed runtime. UNCOMPILED.
   Word arithmetic matches source11; loop/array integration is not asserted. -/
namespace R28PackedFold

abbrev State := UInt64 × UInt64 × UInt64 × UInt64
abbrev Item := Nat × UInt64
def zero : State := (0,0,0,0)
def Z : UInt64 := 0x200000000000000
def low (x w : UInt64) : UInt64 := (x &&& 0x1ffffff)*(w-0x80000000)
def high (x w : UInt64) : UInt64 := ((x>>>25)-0x100000000)*(w-0x80000000)

def step (w u : Nat → UInt64) (a : State) (t : Item) : State :=
  (a.1+low t.2 (w t.1),a.2.1+high t.2 (w t.1),
   a.2.2.1+low t.2 (u t.1),a.2.2.2+high t.2 (u t.1))

theorem step_zero (w u : Nat → UInt64) (a : State) (i : Nat) :
    step w u a (i,Z)=a := by
  rcases a with ⟨a,b,c,d⟩
  simp [step, low, high, Z]

def live (t : Item) : Bool := t.2 != Z

theorem filter_fold_identity {α β : Type} (xs : List α) (f : β → α → β)
    (p : α → Bool) (h : ∀ b x, p x=false → f b x=b) (b : β) :
    (xs.filter p).foldl f b = xs.foldl f b := by
  induction xs generalizing b with
  | nil => rfl
  | cons x xs ih =>
    cases hp : p x
    · simp [List.filter_cons, hp, List.foldl_cons, ih, h b x hp]
    · simp [List.filter_cons, hp, List.foldl_cons, ih]

theorem compressed_fold (w u : Nat → UInt64) (xs : List Item) (a : State) :
    (xs.filter live).foldl (step w u) a = xs.foldl (step w u) a := by
  apply filter_fold_identity
  intro b t h
  rcases t with ⟨i,x⟩
  by_cases hx : x=Z
  · subst x; exact step_zero w u b i
  · simp [live, hx] at h

def scan (decode : Nat → Item) (w u : Nat → UInt64) : List Nat → Nat → State → List (Nat × State)
  | [], _, _ => []
  | q::qs, p, a =>
    if q=0 then (p,a)::scan decode w u qs (p+1) zero
    else scan decode w u qs p (step w u a (decode q))

theorem scan_one_window (encode : Item → Nat) (decode : Nat → Item)
    (w u : Nat → UInt64) (xs : List Item)
    (hzero : ∀ t∈xs, encode t≠0) (hdecode : ∀ t∈xs, decode (encode t)=t)
    (tail : List Nat) (p : Nat) (a : State) :
    scan decode w u (xs.map encode ++ 0::tail) p a =
      (p,xs.foldl (step w u) a)::scan decode w u tail (p+1) zero := by
  induction xs generalizing a with
  | nil => simp [scan]
  | cons x xs ih =>
    have hz : encode x≠0 := hzero x (by simp)
    have hd : decode (encode x)=x := hdecode x (by simp)
    simp only [List.map_cons, List.cons_append, scan, if_neg hz, hd, List.foldl_cons]
    exact ih (fun t ht=>hzero t (by simp [ht])) (fun t ht=>hdecode t (by simp [ht])) (step w u a x)

def encodeWindows (encode : Item → Nat) : List (List Item) → List Nat
  | [] => []
  | xs::rest => (xs.filter live).map encode ++ 0::encodeWindows encode rest

def expected (w u : Nat → UInt64) : List (List Item) → Nat → List (Nat × State)
  | [], _ => []
  | xs::rest, p => (p,xs.foldl (step w u) zero)::expected w u rest (p+1)

theorem all_windows (encode : Item → Nat) (decode : Nat → Item)
    (w u : Nat → UInt64) (windows : List (List Item))
    (hzero : ∀ xs∈windows, ∀ t∈xs, live t=true → encode t≠0)
    (hdecode : ∀ xs∈windows, ∀ t∈xs, live t=true → decode (encode t)=t)
    (p : Nat) :
    scan decode w u (encodeWindows encode windows) p zero = expected w u windows p := by
  induction windows generalizing p with
  | nil => rfl
  | cons xs rest ih =>
    rw [encodeWindows, scan_one_window encode decode w u (xs.filter live)
      (fun t ht=>by
        have h:=List.mem_filter.mp ht
        exact hzero xs (by simp) t h.1 h.2)
      (fun t ht=>by
        have h:=List.mem_filter.mp ht
        exact hdecode xs (by simp) t h.1 h.2)]
    rw [compressed_fold]
    simp only [expected]
    congr 1
    exact ih (fun ys hy t ht hl=>hzero ys (by simp [hy]) t ht hl)
      (fun ys hy t ht hl=>hdecode ys (by simp [hy]) t ht hl) (p+1)

/-- Any original finalizer, including the bias and signed-zero replay, receives
exactly the same (position,state) pairs once the producer/array bridge is supplied. -/
theorem finalizer_unchanged {α : Type} (finish : Nat → State → α)
    (a b : List (Nat × State)) (h : a=b) :
    a.map (fun x=>finish x.1 x.2)=b.map (fun x=>finish x.1 x.2) := by rw [h]

end R28PackedFold
