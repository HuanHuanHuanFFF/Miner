/- Optional direct interface for four explicit lane finish theorems. NOT_RUN. -/
namespace Submission.R22BlockWriter
open FloatLib.Floats Competition

theorem emit_four_rows_prefix (f : Nat → Binary32) (start p : Nat)
    (read0 read1 read2 read3 : Fin p → Binary32) (out : Array Binary32)
    (hout : RowStream.Prefix f start out)
    (h0 : ∀ j, read0 j = f (start + j.val))
    (h1 : ∀ j, read1 j = f (start + p + j.val))
    (h2 : ∀ j, read2 j = f (start + 2 * p + j.val))
    (h3 : ∀ j, read3 j = f (start + 3 * p + j.val)) :
    RowStream.Prefix f (start + 4 * p)
      (RowStream.emit p read3 (RowStream.emit p read2
        (RowStream.emit p read1 (RowStream.emit p read0 out)))) := by
  have first := RowStream.emit_prefix f start p read0 out hout h0
  have second := RowStream.emit_prefix f (start + p) p read1
    (RowStream.emit p read0 out) first h1
  have second' : RowStream.Prefix f (start + 2 * p)
      (RowStream.emit p read1 (RowStream.emit p read0 out)) := by
    have h : start + p + p = start + 2 * p := by omega
    simpa only [h] using second
  have third := RowStream.emit_prefix f (start + 2 * p) p read2
    (RowStream.emit p read1 (RowStream.emit p read0 out)) second' h2
  have third' : RowStream.Prefix f (start + 3 * p)
      (RowStream.emit p read2 (RowStream.emit p read1 (RowStream.emit p read0 out))) := by
    have h : start + 2 * p + p = start + 3 * p := by omega
    simpa only [h] using third
  have fourth := RowStream.emit_prefix f (start + 3 * p) p read3
    (RowStream.emit p read2 (RowStream.emit p read1 (RowStream.emit p read0 out))) third' h3
  have h : start + 3 * p + p = start + 4 * p := by omega
  simpa only [h] using fourth

end Submission.R22BlockWriter
