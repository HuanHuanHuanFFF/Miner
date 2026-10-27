#eval do
  let stream ← IO.FS.Handle.mk "/dev/stderr" .write
  stream.putStrLn "[DEBUG-R19-SEED] BEFORE 0:marker_control"
  stream.flush

def r19MarkerControl : Nat := 0

#eval do
  let stream ← IO.FS.Handle.mk "/dev/stderr" .write
  stream.putStrLn "[DEBUG-R19-SEED] AFTER 0:marker_control"
  stream.flush

