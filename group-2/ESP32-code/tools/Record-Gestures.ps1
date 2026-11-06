param(
    [Parameter(Mandatory=$true)][string]$Port,
    [string]$OutputDirectory = (Join-Path $PSScriptRoot '..\recordings')
)

# Uses Windows/.NET serial support; no additional packages required.
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
$recordingName = 'gestures_' + (Get-Date -Format 'yyyyMMdd_HHmmss_fff')
$csvPath = Join-Path $OutputDirectory ($recordingName + '.csv')
$logPath = Join-Path $OutputDirectory ($recordingName + '.log')
$serialConnection = [System.IO.Ports.SerialPort]::new($Port,115200)
$serialConnection.DtrEnable = $true
$serialConnection.RtsEnable = $false
$csvWriter = $null
$logWriter = $null
$pendingText = ''
$header = 'sample_us,segment,label,ax_m_s2,ay_m_s2,az_m_s2,gx_rad_s,gy_rad_s,gz_rad_s,roll_deg,pitch_deg'
try {
    $serialConnection.Open()
    $csvWriter = [System.IO.StreamWriter]::new($csvPath,$false,[System.Text.UTF8Encoding]::new($false))
    $logWriter = [System.IO.StreamWriter]::new($logPath,$false,[System.Text.UTF8Encoding]::new($false))
    $csvWriter.AutoFlush = $true
    $logWriter.AutoFlush = $true
    $csvWriter.WriteLine($header)
    Write-Host "Saving data to $csvPath"
    Write-Host 'c=calibrate; d=diagnostics; 0=still 1=flick 2=shake 3=tilt; r=record; s=stop; q=quit.'
    Write-Host 'Wait for calibration to complete, then select a label and press r.'
    $quitAt = $null
    while ($true) {
        if ([Console]::KeyAvailable) {
            $key = [Console]::ReadKey($true).KeyChar
            if ($key -eq 'q') {
                $serialConnection.Write('s')
                $quitAt = [DateTime]::UtcNow.AddSeconds(2)
            } elseif ('cd0123rsh'.Contains([string]$key)) {
                $serialConnection.Write([string]$key)
            }
        }
        $pendingText += $serialConnection.ReadExisting()
        while ($pendingText.Contains("`n")) {
            $newline = $pendingText.IndexOf("`n")
            $line = $pendingText.Substring(0,$newline).TrimEnd("`r")
            $pendingText = $pendingText.Substring($newline + 1)
            $logWriter.WriteLine($line)
            if ($line -match '^\d+,\d+,(still|flick|shake|tilt),') {
                if (($line.Split(',')).Count -eq 11) { $csvWriter.WriteLine($line) }
            } elseif ($line -ne $header) {
                Write-Host $line
            }
        }
        if ($null -ne $quitAt -and [DateTime]::UtcNow -ge $quitAt) { break }
        Start-Sleep -Milliseconds 5
    }
} finally {
    if ($null -ne $csvWriter) { $csvWriter.Dispose() }
    if ($null -ne $logWriter) { $logWriter.Dispose() }
    if ($serialConnection.IsOpen) { $serialConnection.Close() }
    $serialConnection.Dispose()
}
