$zhiPath = "C:\Users\semae\OneDrive\Belgeler\GitHub\zhvm\test_app_protected.zhi"
$outputPath = "C:\Users\semae\OneDrive\Belgeler\GitHub\zhvm\src\stub\zhi_bytes.inc"

$bytes = [System.IO.File]::ReadAllBytes($zhiPath)
$hex = $bytes | ForEach-Object { "0x{0:X2}" -f $_ }
$content = $hex -join ","
[System.IO.File]::WriteAllText($outputPath, $content)
