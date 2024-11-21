# Define root directory
$RootDir = "." # Insert dir path here

# Show dirs and files tree
cmd /c "tree $RootDir /F"

# Get all files recursively, adding conditions to exclude certain extensions, filenames, and folders
$files = Get-ChildItem -Path $RootDir -Recurse -File | 
         Where-Object {
            $_.Extension -notin '.exe', '.o', '.ps1', '.prefs' -and 
            $_.Name -notin 'tinyxml2.cpp', 'tinyxml2.h', '.cproject', '.gitignore', '.project', 'language.settings.xml' -and
            $_.FullName -notmatch '\\\.pio\\|\\.vscode\\|\\libdeps\\'
         }

foreach ($file in $files) {
    # Calculate relative path
    $relativePath = $file.FullName.Substring($RootDir.Length + 1)
    # Show relative path
    Write-Host "`n--------------------------------------------"
    Write-Host "Ruta: $relativePath"
    Write-Host "--------------------------------------------"
    # Show file content
    Get-Content $file.FullName
}
