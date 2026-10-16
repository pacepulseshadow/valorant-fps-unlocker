# Security Policy

## Scope

This repository ships a local Windows desktop tool. It does not phone home, it
does not ship a remote loader, and it does not modify Valorant's game files on
disk. If you find behavior that contradicts any of the above, treat it as a
security issue.

## Supported versions

| Version | Supported |
|---------|-----------|
| 0.6.x   | yes       |
| 0.5.x   | critical fixes only |
| < 0.5   | no        |

## Reporting

Open a private security advisory on GitHub or email `security@valorant-fps-unlocker.dev`.
Please include:

- A minimal repro (config + steps).
- Whether the issue requires admin rights.
- Any memory dumps you captured (redact Riot ID / HWID).

We aim to acknowledge within 72 hours.

## Out of scope

- Anti-cheat detection reports. Using this tool may violate Riot's ToS and
  result in a ban. That is a **you** problem, not a CVE.
- "My account got banned" — not a security issue.
- Feature requests for aimbot / wallhack / ESP. This project is an FPS
  optimizer, not a cheat loader. PRs adding combat assistance will be closed.