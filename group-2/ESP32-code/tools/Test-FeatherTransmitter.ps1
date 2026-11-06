# Capture six-axis USB data and check acquisition rate, continuity, and errors.
param(
    [string]$Port = 'COM5',
    [ValidateRange(5,120)][int]$Seconds = 12,
    [string]$OutputDirectory = (Join-Path $PSScriptRoot '..\recordings')
)
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
$capturePath = Join-Path $OutputDirectory ('feather_imu_' + (Get-Date -Format 'yyyyMMdd_HHmmss') + '.log')
$connection = [System.IO.Ports.SerialPort]::new($Port, 115200)
$connection.DtrEnable = $true
# TinyUSB's Serial boolean requires DTR and RTS asserted on this ESP32 core.
$connection.RtsEnable = $true
$connection.ReadTimeout = 250
$lines = [System.Collections.Generic.List[string]]::new()
try {
    $connection.Open()
    $timer = [System.Diagnostics.Stopwatch]::StartNew()
    $askedForHelp = $false
    $askedForStats = $false
    while ($timer.Elapsed.TotalSeconds -lt $Seconds) {
        if (!$askedForHelp -and $timer.Elapsed.TotalSeconds -gt 2) {
            $connection.Write('h')
            $askedForHelp = $true
        }
        if (!$askedForStats -and $timer.Elapsed.TotalSeconds -gt ($Seconds - 1)) {
            $connection.Write('d')
            $askedForStats = $true
        }
        try { $lines.Add($connection.ReadLine().TrimEnd("`r")) }
        catch [System.TimeoutException] { }
    }
} finally {
    if ($connection.IsOpen) { $connection.Close() }
    $connection.Dispose()
    $lines | Set-Content -LiteralPath $capturePath -Encoding utf8
}

$rows = @($lines | Where-Object { $_ -match '^\d+,' })
$faults = @($lines | Where-Object { $_ -match '^# ERROR' })
$diagnostics = @($lines | Where-Object { $_ -match '^# ready=' })
Write-Output "Capture: $capturePath"
$diagnostics | Write-Output
if ($rows.Count -lt 100) {
    $faults | Select-Object -First 4 | Write-Output
    throw "FAIL: Only $($rows.Count) samples received. Check sensor wiring and close other serial monitors."
}
$culture = [Globalization.CultureInfo]::InvariantCulture
$parsed = @($rows | ForEach-Object {
    $fields = $_.Split(',')
    if ($fields.Count -ne 8) { throw "FAIL: malformed CSV row: $_" }
    ,@($fields | ForEach-Object { [double]::Parse($_, $culture) })
})
$skipped = 0
$gravityTotal = 0.0
$gyroMax = 0.0
for ($i = 0; $i -lt $parsed.Count; $i++) {
    $row = $parsed[$i]
    foreach ($value in $row) {
        if ([double]::IsNaN($value) -or [double]::IsInfinity($value)) { throw 'FAIL: non-finite reading' }
    }
    for ($axis = 2; $axis -lt 8; $axis++) {
        $limit = if ($axis -lt 5) { 39.3 } else { 10.02 }
        if ([Math]::Abs($row[$axis]) -gt $limit) { throw 'FAIL: reading exceeds configured sensor range' }
    }
    if ($i -gt 0) {
        $gap = $row[0] - $parsed[$i-1][0]
        if ($gap -lt 1) { throw 'FAIL: sequence repeated or board reset during capture' }
        $skipped += $gap - 1
    }
    $gravityTotal += [Math]::Sqrt($row[2]*$row[2] + $row[3]*$row[3] + $row[4]*$row[4])
    $gyroMax = [Math]::Max($gyroMax, [Math]::Sqrt($row[5]*$row[5] + $row[6]*$row[6] + $row[7]*$row[7]))
}
$elapsedUs = $parsed[-1][1] - $parsed[0][1]
if ($elapsedUs -lt 0) { $elapsedUs += 4294967296.0 }
if ($elapsedUs -le 0) { throw 'FAIL: invalid sample timestamps' }
$rate = ($parsed.Count - 1) * 1000000.0 / $elapsedUs
Write-Output ('Samples={0}; rate={1:F2} Hz; missing_rows={2}; mean_accel_norm={3:F3} m/s^2; max_gyro_norm={4:F3} rad/s' -f $parsed.Count,$rate,$skipped,($gravityTotal/$parsed.Count),$gyroMax)
if ($faults.Count -gt 0 -or $skipped -gt 0 -or $rate -lt 95 -or $rate -gt 110) {
    throw 'FAIL: sensor errors, missing rows, or rate outside 95-110 Hz; inspect capture.'
}
if ($diagnostics.Count -eq 0 -or $diagnostics[-1] -notmatch 'ready=1 .*read_errors=0 serial_drops=0 ') {
    throw 'FAIL: missing diagnostics or firmware reported a fault/drop since boot.'
}
Write-Output 'PASS: live acquisition, CSV format, numeric ranges, sample rate and continuity.'
Write-Output 'Manual checks still needed: stationary gravity near 9.81 m/s^2, gyro near zero, and deliberate movement on each axis.'
