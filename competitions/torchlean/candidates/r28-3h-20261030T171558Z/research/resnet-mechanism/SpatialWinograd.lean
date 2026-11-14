import ContractExact

/- Original spatial F(2x2,3x3) integer algebra bridge. UNCOMPILED.
   This is not the R27 dot-product Winograd route and is not a submitted kernel.
   The UInt64 refinement, array indexing and complete candidate obligation remain open. -/
namespace R28SpatialWinograd

def bt (x : Nat → Int) : Nat → Int
  | 0 => x 0 - x 2
  | 1 => x 1 + x 2
  | 2 => x 2 - x 1
  | _ => x 1 - x 3

def g2 (w : Nat → Int) : Nat → Int
  | 0 => 2 * w 0
  | 1 => w 0 + w 1 + w 2
  | 2 => w 0 - w 1 + w 2
  | _ => 2 * w 2

def at (m : Nat → Int) : Nat → Int
  | 0 => m 0 + m 1 + m 2
  | _ => m 1 - m 2 - m 3

theorem oneD0 (x w : Nat → Int) :
    at (fun i => bt x i * g2 w i) 0 =
      2 * (x 0*w 0 + x 1*w 1 + x 2*w 2) := by
  simp only [at, bt, g2]
  ring

theorem oneD1 (x w : Nat → Int) :
    at (fun i => bt x i * g2 w i) 1 =
      2 * (x 1*w 0 + x 2*w 1 + x 3*w 2) := by
  simp only [at, bt, g2]
  ring

def inputTransform (d : Nat → Nat → Int) (i j : Nat) : Int :=
  bt (fun r => bt (d r) j) i

def weightTransform (w : Nat → Nat → Int) (i j : Nat) : Int :=
  g2 (fun r => g2 (w r) j) i

def outputTimesFour (d w : Nat → Nat → Int) (i j : Nat) : Int :=
  at (fun r => at (fun c => inputTransform d r c * weightTransform w r c) j) i

def direct (d w : Nat → Nat → Int) (i j : Nat) : Int :=
  d i j*w 0 0 + d i (j+1)*w 0 1 + d i (j+2)*w 0 2 +
  d (i+1) j*w 1 0 + d (i+1) (j+1)*w 1 1 + d (i+1) (j+2)*w 1 2 +
  d (i+2) j*w 2 0 + d (i+2) (j+1)*w 2 1 + d (i+2) (j+2)*w 2 2

theorem tile00 (d w : Nat → Nat → Int) :
    outputTimesFour d w 0 0 = 4 * direct d w 0 0 := by
  simp only [outputTimesFour, inputTransform, weightTransform, at, bt, g2, direct]
  norm_num
  ring

theorem tile01 (d w : Nat → Nat → Int) :
    outputTimesFour d w 0 1 = 4 * direct d w 0 1 := by
  simp only [outputTimesFour, inputTransform, weightTransform, at, bt, g2, direct]
  norm_num
  ring

theorem tile10 (d w : Nat → Nat → Int) :
    outputTimesFour d w 1 0 = 4 * direct d w 1 0 := by
  simp only [outputTimesFour, inputTransform, weightTransform, at, bt, g2, direct]
  norm_num
  ring

theorem tile11 (d w : Nat → Nat → Int) :
    outputTimesFour d w 1 1 = 4 * direct d w 1 1 := by
  simp only [outputTimesFour, inputTransform, weightTransform, at, bt, g2, direct]
  norm_num
  ring

theorem tile_exact (d w : Nat → Nat → Int) (i j : Nat) (hi : i<2) (hj : j<2) :
    outputTimesFour d w i j = 4 * direct d w i j := by
  interval_cases i <;> interval_cases j
  · exact tile00 d w
  · exact tile01 d w
  · exact tile10 d w
  · exact tile11 d w

theorem divided_exact (d w : Nat → Nat → Int) (i j : Nat) (hi : i<2) (hj : j<2) :
    outputTimesFour d w i j / 4 = direct d w i j := by
  rw [tile_exact d w i j hi hj]
  omega

end R28SpatialWinograd
