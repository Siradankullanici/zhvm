$exePath = $args[0]
if (-not $exePath) { $exePath = "C:\Users\semae\OneDrive\Belgeler\GitHub\ObfuPufluFuscator\test_app.packed.exe" }
$outputPath = "C:\Users\semae\OneDrive\Belgeler\GitHub\zhvm\test_app_obf.zsf"

$bytes = [System.IO.File]::ReadAllBytes($exePath)
$stream = [System.IO.StreamWriter]::new($outputPath)
$stream.WriteLine("!main")
$stream.WriteLine("`$0 = add[,0] # index 0 in data is exesize")
$stream.WriteLine("`$1 = ldl[`$0]")
$stream.WriteLine("`$0 = add[,4] # index 4 in data is exedata")
$stream.WriteLine("rx[`$0, `$1]")
$stream.WriteLine("hlt[]")
$stream.WriteLine("!data")
$stream.WriteLine("!{0}l" -f $bytes.Length)

for ($i = 0; $i -lt $bytes.Length; $i += 4) {
    if ($i + 4 -le $bytes.Length) {
        $val = [System.BitConverter]::ToUInt32($bytes, $i)
        $stream.WriteLine("!{0}l" -f $val)
    }
    else {
        $remaining = $bytes.Length - $i
        $paddedBytes = New-Object byte[] 4
        [System.Array]::Copy($bytes, $i, $paddedBytes, 0, $remaining)
        $val = [System.BitConverter]::ToUInt32($paddedBytes, 0)
        $stream.WriteLine("!{0}l" -f $val)
    }
}

$stream.WriteLine()
$stream.Close()
