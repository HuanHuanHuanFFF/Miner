/- R22: existing fastOK/native arithmetic, separate cold B2 boundary. NOT_RUN. -/
namespace Submission.R22NativeColdAdd
open FloatLib.Floats Competition

@[noinline] def coldAdd (x y : Binary32) : Binary32 := Submission.add x y

@[inline] def diagnosticEntry (x y : Binary32) : Binary32 :=
  if R2W01b.fastOK x.raw.1 && R2W01b.fastOK y.raw.1 then
    ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 + R2W01b.tableProduct y.raw.1)
  else coldAdd x y

end Submission.R22NativeColdAdd
