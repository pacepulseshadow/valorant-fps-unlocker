using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Vopt.Bridge;

/// <summary>
/// Thin C# tray shim that shells out to vopt-cli. Keeps the C++ core
/// headless so the overlay can stay minimal.
/// </summary>
public sealed class TrayController : IDisposable
{
    private readonly string _cliPath;
    private Process? _cli;

    public TrayController(string cliPath) => _cliPath = cliPath;

    public void Unlock(int targetFps)
    {
        Run($"fps unlock --target {targetFps}");
    }

    public void Restore()
    {
        Run("fps restore");
    }

    public void Diag()
    {
        Run("diag --redact");
    }

    private void Run(string args)
    {
        var psi = new ProcessStartInfo(_cliPath, args)
        {
            UseShellExecute = false,
            CreateNoWindow = true,
            RedirectStandardOutput = true,
        };
        _cli = Process.Start(psi);
        _cli?.WaitForExit(5000);
    }

    public void Dispose()
    {
        _cli?.Dispose();
    }
}