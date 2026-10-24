# R12 opt-in BMM assembly focus

New helper SHA-256: `53525f8e5ac09300d01b57e37ff652eecdaa4ec3b6dc3d09c11f01dc4c924695`. Exact adjacent legacy module remains `fd17f35a4ef1bc1b1df2afe5fcfe39691d88e7e605968acbe3c38df09df9078b`. The immutable005 runHEAD retains its original `d15aa6da…` helper; this change does not reinterpret that run.

The seven-argument `run_gate` interface is unchanged. It reads the frozen public plan once, before starting the original gate, from `env.GITHUB_WORKSPACE/competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json`. For a candidate explicitly listed in `r12_mainfull_capture.candidates`, `r12_mainfull_capture.assembly_focus` accepts only `scalar` or `bmm`. Missing focus keeps scalar behavior. The shared dispatcher still owns round/module/hash/source/observer validation and is untouched by this change.

Focus affects only the post-gate disassembly selector. Snapshot still copies the same original MainFull/Submission/BenchSuite C, trace and ELF with unchanged3-second/32MiB/24-file bounds. It still preserves exact argv/environment/log bytes, original timeout/exit semantics, original30-second postprocessing deadline, private runner-only ELF copies and cleanup. MAX_SYMBOLS remains20. Complete actual C remains available even if assembly is omitted.

- Scalar mode keeps the prior MainFull/BenchSuite-first order exactly.
- BMM mode selects Submission symbols with the original fd17 `_symbol_info` and sorts them with its `_symbol_sort_key`, before any MainFull/BenchSuite assembly. This includes exact actual Panel4 names and its existing output specializations. Existing fd17 near-match/boxed exclusion rules stay intact.
- Invalid focus is recorded as UNKNOWN; the original gate still runs exactly once and its result is returned. Capture failure never becomes a new gate verdict. Omitted symbols remain explicit and the disassembly state stays PARTIAL when the budget is exhausted.

`scalar-test-observer.py` freshly passed all5 original fake-child tests. `scalar-test-bmm-focus.py` freshly passed3 additional cases: a selector fixture using saved40067286343 MainFull/BenchSuite C/nm plus actual927 Panel4 C/nm; invalid-focus original once-only exit7/log/ELF cleanup; and missing/default/explicit focus configuration. The fixture checks the exact first20 fd17-sorted Submission names, captures an actual Panel4 word loop and records MainFull assembly omissions. Mixing saved modules is only parser/selection coverage, never a measured or linked run. Actual new BMM-focus gate/ELF execution remains NOT_RUN.

Root can now add the explicit prepare-plan assembly-focus field, freeze this helper hash and run the next natural original full gate. No extra compile, benchmark or sampling is requested by this helper.
