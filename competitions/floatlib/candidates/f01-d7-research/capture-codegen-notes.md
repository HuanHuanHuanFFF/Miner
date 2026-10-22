# Opt-in original-statement code generation capture

Prepared locally on 2026-10-22 UTC. Discovery use only; no adapter is changed or enabled here. Real Linux/Lean/GNU-tool integration and full gate acceptance are **NOT_RUN**.

## Interface

    run_gate(argv, cwd, env, log_path, timeout, output, kernel)
        -> (subprocess.CompletedProcess, codegen_record)

The caller supplies the original full gate arguments, checkout, environment, raw log destination, timeout, artifact output and exact candidate. Arguments/cwd/environment pass unchanged to one original process. Stderr joins stdout and all raw bytes go to the requested log. CompletedProcess retains original args and exit code; stdout/stderr are None because bytes are in the log. Nonzero exits return normally. Timeout kills/drains, then raises the original TimeoutExpired with its codegen_record attribute attached. Launch errors retain their original exception. Derive the gate verdict from the original log/exit status, never from capture status.

The wrapper records its POSIX new-session or Windows process-group launch options; Windows hides the child window. It does not edit official source, gate stages, arguments, environment, objects or scores, and never rebuilds anything. Output must be outside the official checkout.

## Identity, artifacts and private objects

The first raw statement-ok marker starts one worker, including when split across reads. Repeated markers never recapture. The worker requires cwd/lean/work/Submission.lean SHA-256 to equal the exact kernel and checks it again at the end.

Only own Submission.c, own trace names and own Submission.o/Submission.c.o with optional export/noexport suffixes are considered under .sandbox/layer/upper/ir and upper/lib/lean. Other modules are excluded. CAPTURED requires C, trace and ELF object. Missing/wiped/changing files, source mismatch, size/time limits, symlinks and read errors become UNKNOWN with a reason.

The unique capture folder contains C/trace, exact compiled Submission.lean, metadata and selected textual nm/objdump output. Hashes bind the original process's statement objects; these are not instrumented or separately rebuilt diagnostic objects.

ELF copies live only in an absolute dedicated floatlib-codegen-private-* directory under existing RUNNER_TEMP, or system temp when absent. Both temporary root and directory must be outside checkout and artifact output. Objects never enter output, including on failed cleanup or late worker completion. Each private object is individually unlinked; only the empty directory is removed with rmdir. Cleanup success/failure is recorded. A late worker can leave private scratch outside artifacts; that is an error and does not claim successful cleanup.

Metadata records original paths; kernel/compiled-source/C/trace/object/module/gate/log hashes; start/finish UTC; process, timeout and launch configuration; tool arguments/exit/output hashes; symbol sizes; and cleanup outcome. Full gate argv is recorded, so do not put credentials in argv. Only explicitly selected benchmark environment fields and original timezone evidence are recorded.

## Bounded postprocessing

Only after original process exit, nm finds actual own defined text symbols. Selection includes add/mul/nativeMul, NativeFinal dot/dotLoop/sumLoop, dotLoop, DirectSmall core, RowStream core, NativeDecodeSumWord loop, Packed10Index loop and LowZero helpers. Boxed wrappers/unrelated functions are excluded; eliminated symbols remain absent. objdump retains actual textual assembly and relocations with command status and hash.

Live limits: 8 MiB/file, 24 MiB combined, 8 own files, two seconds checked between regular-file reads; kernel source limit 256000 bytes. Postprocessing: cooperative 30-second budget, 20 symbols, four seconds/tool, 2 MiB nm and 8 MiB per assembly output. Tool kill/drain grace can exceed nominal deadlines. Regular-file I/O and thread waits are not hard realtime guarantees. Raw logs are never truncated; hash/stage parsing is capped at 16 MiB, above which logs remain intact and final log analysis is UNKNOWN.

## Timing evidence

Observer impact remains **UNKNOWN**, including when capture finishes early: CPU, memory bandwidth and cache can affect later stages. Root should enable only for discovery and disable it for frozen independent confirmation. A captured run is not independent confirmation or a stage-share measurement.

Original statement/kernel/axioms/score ok lines are retained byte-for-byte in base64 with original timestamp text. Explicit timezone offsets are accepted. Offset-free timestamps convert only when unchanged child TZ explicitly equals UTC, Etc/UTC, GMT or UTC0. Otherwise emission time remains UNKNOWN. Reader arrival time never substitutes for emission time.

When available, capture finish UTC is compared conservatively with the original axioms-ok timestamp lower bound. Later/ambiguous finish is UNKNOWN_POSSIBLE_OVERLAP. Being before that timestamp does not establish zero observer effect. No timestamp is injected into the gate.

## Local verification and runner gaps

    python competitions/floatlib/candidates/f01-d7-research/capture-codegen.py --selftest

Local fake-process tests cover exact raw bytes (invalid UTF-8, CRLF, NUL, split marker), original args/environment/nonzero exit 7, one capture despite duplicate markers, capture before wipe, UNKNOWN after wipe, exact-source mismatch, isolated postprocessor failure, prompt TimeoutExpired cleanup, original emission timestamp and unknown timezone handling, symbol selection, and no ELF/private objects in artifact output. Owned validated scratch is cleaned up.

The tests use lightweight Python children and a fake ELF header; only selftest replaces disassembly. They establish wrapper behavior, not Lean/LLVM acceptance. Actual Linux process-group cleanup, Lake layout/event timing, native nm/objdump availability/symbols, generated code and complete gate integration are **NOT_RUN**. The first runner must bind the exact kernel, inspect original verdict plus identity/phase evidence and verify no ELF was included in artifacts. Freeze confirmation runs with capture disabled.
