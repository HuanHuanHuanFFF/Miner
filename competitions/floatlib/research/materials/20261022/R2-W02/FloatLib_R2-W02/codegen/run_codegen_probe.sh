#!/usr/bin/env bash
set -euo pipefail
# Existing, prebuilt v4.34.0 workspace only; no installation or dependency update.
# Usage: bash run_codegen_probe.sh /absolute/competition/lean /absolute/output /absolute/lean-4.34.0/bin
workspace=${1:?provide an already prepared competition lean workspace}
output=${2:?provide an output directory outside that workspace}
toolchain_bin=${3:?provide the real existing Lean 4.34.0 bin directory, not an elan shim directory}
script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
package_dir=$(cd -- "$script_dir/.." && pwd)
mkdir -p -- "$output"
output=$(cd -- "$output" && pwd)
workspace=$(cd -- "$workspace" && pwd)
toolchain_bin=$(cd -- "$toolchain_bin" && pwd)
case "$output/" in
  "$workspace/"*) echo 'STOP: diagnostic output must be outside the competition workspace' >&2; exit 2 ;;
esac
if ! test -x "$toolchain_bin/lean" || ! test -x "$toolchain_bin/lake" ||
   ! test -x "$toolchain_bin/leanc" ||
   ! test -f "$toolchain_bin/../lib/lean/Init.olean" ||
   ! test -f "$toolchain_bin/../include/lean/lean.h"; then
  echo 'NOT_RUN: provide a real preinstalled toolchain directory; shims are not accepted' | tee "$output/status.txt"
  exit 2
fi
if test "$(cat "$workspace/lean-toolchain")" != 'leanprover/lean4:v4.34.0'; then
  echo 'STOP: workspace toolchain pin does not match 4.34.0' >&2
  exit 2
fi
if test -n "${ELAN_TOOLCHAIN:-}" && test "$ELAN_TOOLCHAIN" != 'leanprover/lean4:v4.34.0'; then
  echo 'STOP: conflicting ELAN_TOOLCHAIN override' >&2
  exit 2
fi
if test -n "${LEAN_SYSROOT:-}"; then
  actual_sysroot=$(cd -- "$LEAN_SYSROOT" && pwd)
  expected_sysroot=$(cd -- "$toolchain_bin/.." && pwd)
  if test "$actual_sysroot" != "$expected_sysroot"; then
    echo 'STOP: conflicting LEAN_SYSROOT override' >&2
    exit 2
  fi
fi
if ! test -f "$workspace/.lake/build/lib/lean/ContractTensor.olean"; then
  echo 'NOT_RUN: ContractTensor is not already built; no dependency build attempted' | tee "$output/status.txt"
  exit 2
fi
cd -- "$workspace"
"$toolchain_bin/lean" --version > "$output/lean-version.txt"
if ! rg -q 'version 4\.34\.0([ ,)]|$)' "$output/lean-version.txt"; then
  echo 'STOP: expected Lean 4.34.0' >&2
  exit 2
fi
"$toolchain_bin/lake" env "$toolchain_bin/leanc" --print-cflags > "$output/leanc-cflags.txt"
python3 "$package_dir/diagnostics/check_kernel.py" \
  "$workspace/.." "$package_dir/candidate/Kernel.lean" \
  > "$output/static-preflight.json"

"$toolchain_bin/lake" env "$toolchain_bin/lean" -c "$output/Packed4CodegenProbe.c" \
  -o "$output/Packed4CodegenProbe.olean" "$script_dir/Packed4CodegenProbe.lean" \
  > "$output/probe.stdout.txt" 2> "$output/probe.stderr.txt"
"$toolchain_bin/lake" env "$toolchain_bin/lean" -c "$output/Kernel.c" -o "$output/Kernel.olean" \
  "$package_dir/candidate/Kernel.lean" \
  > "$output/kernel.stdout.txt" 2> "$output/kernel.stderr.txt"
# Proof source stays outside the performance candidate until it elaborates.
cat "$package_dir/candidate/Kernel.lean" "$package_dir/proof/ProofAppend.lean" \
  > "$output/ProofProbe.lean"
"$toolchain_bin/lake" env "$toolchain_bin/lean" -o "$output/ProofProbe.olean" "$output/ProofProbe.lean" \
  > "$output/proof.stdout.txt" 2> "$output/proof.stderr.txt"

rg -n 'packed4Loop|state4Loop|plain4Loop|dot4|packB|lean_float32_(of_bits|to_bits|add|mul)|lean_(box|unbox)_float32|lean_ctor_(get|set)_float32|lean_array_.*get|lean_alloc_ctor|lean_inc|lean_dec|goto _start' \
  "$output/Packed4CodegenProbe.c" "$output/Kernel.c" \
  > "$output/codegen-review.txt" || true
echo 'ELABORATED_AND_C_EMITTED_ONLY: no full BmmObligation, gate or timing claim' > "$output/status.txt"
# C emission uses normal lean defaults. Official acceptance and native timing
# must use the unchanged Lake build, which also enforces package leanOptions.
# No extra C flags, source patches, FMA flags, LTO or target flags are added here.
