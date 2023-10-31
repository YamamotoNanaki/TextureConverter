$files = Get-Item *.jpg
$files2 = Get-Item *.png

foreach($f in $files)
{
    Start-Process -FilePath TextureConverter.exe -ArgumentList $f -Wait
}
foreach($f in $files2)
{
    Start-Process -FilePath TextureConverter.exe -ArgumentList $f -Wait
}

Pause