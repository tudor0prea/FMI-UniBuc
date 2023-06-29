$decision = $Host.UI.PromptForChoice('Uninstall Haskell'
, 'Do you want to uninstall all of the haskell toolchain, including GHC, Cabal, Stack and GHCup itself?'
, [System.Management.Automation.Host.ChoiceDescription[]] @('&Uninstall'
    '&Abort'), 0)

if ($decision -eq 1) {
  Exit 0
}

Write-Host 'Removing ghcup toolchain' -ForegroundColor Green
ghcup nuke

Write-Host 'Unsetting GHCUP_INSTALL_BASE_PREFIX' -ForegroundColor Green
[Environment]::SetEnvironmentVariable('GHCUP_INSTALL_BASE_PREFIX', $null, [System.EnvironmentVariableTarget]::User)

$ghcupMsys2 = [System.Environment]::GetEnvironmentVariable('GHCUP_MSYS2', 'user')
$GhcupBasePrefixEnv = [System.Environment]::GetEnvironmentVariable('GHCUP_INSTALL_BASE_PREFIX', 'user')

if ($ghcupMsys2) {
  $msys2Dir = [IO.Path]::GetFullPath($ghcupMsys2)
  $baseDir = [IO.Path]::GetFullPath('{0}\ghcup' -f $GhcupBasePrefixEnv)

  if ($msys2Dir.StartsWith($baseDir)) {
    Write-Host 'Unsetting GHCUP_MSYS2' -ForegroundColor Green
    [Environment]::SetEnvironmentVariable('GHCUP_MSYS2', $null, [System.EnvironmentVariableTarget]::User)
  } else {
    Write-Host ('GHCUP_MSYS2 env variable is set to a non-standard location {0}. Environment variable not unset. Uninstall manually.' -f $msys2Dir) -ForegroundColor Magenta
  }
} else {
  Write-Host 'Unsetting GHCUP_MSYS2' -ForegroundColor Green
  [Environment]::SetEnvironmentVariable('GHCUP_MSYS2', $null, [System.EnvironmentVariableTarget]::User)
}

Write-Host 'Removing ghcup from PATH env var' -ForegroundColor Green
$path = [System.Environment]::GetEnvironmentVariable(
    'PATH',
    'user'
)
$path = ($path.Split(';') | Where-Object { $_ -ne ('{0}\bin' -f $baseDir) }) -join ';'
[System.Environment]::SetEnvironmentVariable(
    'PATH',
    $path,
    'user'
)

Write-Host 'Removing desktop files' -ForegroundColor Green
$DesktopDir = [Environment]::GetFolderPath("Desktop")
Remove-Item -LiteralPath ('{0}\Install GHC dev dependencies.lnk' -f $DesktopDir) -Force
Remove-Item -LiteralPath ('{0}\Mingw haskell shell.lnk' -f $DesktopDir) -Force
Remove-Item -LiteralPath ('{0}\Mingw package management docs.url' -f $DesktopDir) -Force

Write-Host ('CABAL_DIR env variable is still set to {0} and will be used by cabal regardless of ghcup. You may want to uninstall this manually.' -f [System.Environment]::GetEnvironmentVariable('CABAL_DIR', 'user')) -ForegroundColor Magenta
Write-Host 'You may remove this script now.' -ForegroundColor Magenta

if ($Host.Name -eq "ConsoleHost")
{
    Write-Host "Press any key to continue..."
    $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyUp") > $null
}