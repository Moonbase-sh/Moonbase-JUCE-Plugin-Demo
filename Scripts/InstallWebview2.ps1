# Define the version and package name
$webview2Version = "1.0.1901.177"
$packageName = "Microsoft.Web.WebView2"

# Determine the relative installation path
$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
$installDirectory = Join-Path -Path $scriptDirectory -ChildPath "..\WebView2"

# Ensure the installation directory exists
if (-not (Test-Path $installDirectory)) {
    Write-Output "Creating directory: $installDirectory"
    New-Item -Path $installDirectory -ItemType Directory | Out-Null
}

# Determine the installed version path
$installedVersionPath = Join-Path -Path $installDirectory -ChildPath $webview2Version

# Check if WebView2 is already installed
if (Test-Path $installedVersionPath) {
    Write-Output "WebView2 is already installed at: $installedVersionPath"
} else {
    Write-Output "WebView2 not found, attempting to install..."

    try {
        # Download the package to a temporary location
        $tempPath = Join-Path -Path $env:TEMP -ChildPath "$packageName.$webview2Version"
        Save-Package -Name $packageName -Source "https://www.nuget.org/api/v2" -Path $tempPath -RequiredVersion $webview2Version -Force -ErrorAction Stop

        # Extract the package contents to the install directory
        $nupkgFile = Get-ChildItem -Path $tempPath -Filter "*.nupkg" | Select-Object -First 1
        $extractPath = Join-Path -Path $installDirectory -ChildPath $webview2Version
        
        if (-not (Test-Path $extractPath)) {
            New-Item -Path $extractPath -ItemType Directory | Out-Null
        }
        
        Add-Type -AssemblyName "System.IO.Compression.FileSystem"
        [System.IO.Compression.ZipFile]::ExtractToDirectory($nupkgFile.FullName, $extractPath)

        Write-Output "WebView2 installation completed."

        # Verify installation
        if (Test-Path $installedVersionPath) {
            Write-Output "WebView2 is successfully installed at: $installedVersionPath"
        } else {
            Write-Error "WebView2 installation failed."
            exit 2
        }
    } catch {
        Write-Error "An error occurred during installation: $_"
        exit 1
    }
}

# Output the raw location of the WebView2 installation
Write-Output "WebView2 is located at: $installedVersionPath"
exit 0
