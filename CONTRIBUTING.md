# Contributing to valorant-fps-unlocker

Thanks for wanting to help push Valorant-Optimizer forward. This is a hobbyist
project focused on FPS unlocking, frame-pacing tuning, and lightweight overlay
telemetry for Valorant. It is **not** affiliated with Riot Games.

## Ground rules

- Keep PRs scoped. One module per PR where possible (e.g. `fps_unlock/` or
  `overlay_core/`).
- All C++ must build with MSVC 19.40+ and clang-cl. C++20 is the floor.
- C# bridge code must target `net8.0-windows` and stay AOT-compatible.
- No telemetry leaves the machine. Ever.
- Do not commit `config/local.json`, HWID dumps, or captured frame traces.

## Branch naming

- `feat/fps-unlock-<short>` — new features
- `fix/overlay-<short>` — bug fixes
- `tune/frame-pacing-<short>` — perf tuning experiments

## Build

```powershell
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

## Style

- 4-space indent, Allman braces, `snake_case` for functions, `PascalCase` for
  types, `kConstantStyle` for constants.
- Prefer `std::expected` over exceptions in hot paths.
- Log with `vopt::log::*` — never `printf`.

## Reporting issues

Include: Windows build, GPU driver version, Valorant patch, and the output of
`vopt-cli diag --redact`. Redact your Riot ID before pasting.