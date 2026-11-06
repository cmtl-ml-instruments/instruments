# Capture receiver status and note events. Use -RequireLive for a paired radio test.
param(
  [string]$Port = 'COM7',
  [ValidateRange(5,120)][int]$Seconds = 12,
  [switch]$RequireLive,
  [string]$OutputDirectory = (Join-Path $PSScriptRoot '..\recordings')
)
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
$logPath = Join-Path $OutputDirectory ('display_receiver_' + (Get-Date -Format 'yyyyMMdd_HHmmss') + '.log')
$serialLink = [System.IO.Ports.SerialPort]::new($Port,115200)
# Hardware USB Serial/JTAG: leave control lines inactive to avoid ROM resets.
$serialLink.DtrEnable = $false
$serialLink.RtsEnable = $false
$serialLink.ReadTimeout = 250
$lines = [System.Collections.Generic.List[string]]::new()
try {
  $serialLink.Open()
  # Discard USB data buffered before this measurement, then request fresh status.
  Start-Sleep -Milliseconds 1000
  $serialLink.DiscardInBuffer()
  $timer = [Diagnostics.Stopwatch]::StartNew()
  $queried = $false
  while ($timer.Elapsed.TotalSeconds -lt $Seconds) {
    if (!$queried -and $timer.Elapsed.TotalSeconds -gt 1) { $serialLink.Write('d'); $queried = $true }
    try { $lines.Add($serialLink.ReadLine().TrimEnd("`r")) }
    catch [System.TimeoutException] { }
  }
} finally {
  if ($serialLink.IsOpen) { $serialLink.Close() }
  $serialLink.Dispose()
  $lines | Set-Content -LiteralPath $logPath -Encoding utf8
}
Write-Output "Capture: $logPath"
$statusLines = @($lines | Where-Object { $_ -match '^# RECEIVER' })
if ($statusLines.Count -lt 2) { throw 'FAIL: insufficient receiver diagnostics' }
$statusLines | Write-Output
foreach ($line in $statusLines) {
  if ($line -notmatch 'mode=HEADLESS radio=1 selftest=1') { throw 'FAIL: receiver startup checks failed' }
  if ($line -notmatch 'invalid=0 old=0 queue_drops=0') { throw 'FAIL: rejected packets or queue overflow; inspect log' }
}
if ($RequireLive) {
  $firstLive = @($statusLines | Where-Object { $_ -match 'link=LIVE' })
  if ($firstLive.Count -lt 2 -or $statusLines[-1] -notmatch 'link=LIVE') { throw 'FAIL: sustained live sensor link not observed' }
  $first = [regex]::Match($firstLive[0], 'packets=(\d+)').Groups[1].Value
  $last = [regex]::Match($firstLive[-1], 'packets=(\d+)').Groups[1].Value
  if ([long]$last -le [long]$first) { throw 'FAIL: packet count did not advance' }
  if (@($lines | Where-Object { $_ -match '^# AXES ' }).Count -lt 2) { throw 'FAIL: no sensor axes reported' }
  Write-Output 'PASS: live wireless sensor packets received; review rate and missed counters above.'
} else {
  Write-Output 'PASS: headless radio initialized and packet validation self-test passed.'
  Write-Output 'Wireless sensor delivery requires -RequireLive with the Feather transmitting.'
}
