<#
script to automatically generate .patch files for all file changes between ./stock and ./framework.

usage:
1. copy the root directory of framework-hc32f46x-ddl to a folder ./framework
2. copy the DDL files to a folder ./stock, according to ./docs/FILES_MAPPING.md
3. run this script
    3.1. any files that have changed will have a .patch file generated in ./patches
    3.2. any files added will output a information message to console
#>
function Main() {
    # resolve ./stock and ./framework
    $stock_dir = Resolve-Path ./stock
    $framework_dir = Resolve-Path ./framework

    # get all files in ./framework, including subfolders
    $framework_files = Get-ChildItem -Path $framework_dir -Recurse -File

    # compare all files, if they've got a different hash, call git diff and save the patch file in ./patches/${file_name}.patch
    # ./framework and ./stock have the same file structure, so we can compare them directly
    foreach ($framework_file in $framework_files) {
        $stock_file = $framework_file.FullName.Replace("framework", "stock")
        if (Test-Path $stock_file -PathType Leaf) {
            $framework_hash = Get-FileHash -Path $framework_file.FullName
            $stock_hash = Get-FileHash -Path $stock_file
            if ($framework_hash.Hash -ne $stock_hash.Hash) {
                $patch_file = "./patches/" + $framework_file.Name + ".patch"

                # create path if it doesn't exist
                $patch_file_dir = Split-Path -Path $patch_file
                if (!(Test-Path $patch_file_dir -PathType Container)) {
                    New-Item -Path $patch_file_dir -ItemType Directory | Out-Null
                }

                # run git diff and save the output to the patch file
                $diff = (git --no-pager diff --src-prefix=$stock_dir --dst-prefix=$framework_dir $stock_file $framework_file.FullName)

                # only save if diff is not empty, otherwise print warning
                if ([string]::IsNullOrWhiteSpace($diff)) {
                    Write-Warning "Diff is empty for $framework_file"
                }
                else {
                    # replace $stock_dir and $framework_dir with . in $diff
                    $diff = $diff.Replace($stock_dir.Path, ".").Replace($framework_dir.Path, ".")
                    
                    # do it again, but with \\ instead of \
                    $diff = $diff.Replace($stock_dir.Path.Replace("\", "\\"), ".").Replace($framework_dir.Path.Replace("\", "\\"), ".")

                    # do it again, but with / instead of \
                    $diff = $diff.Replace($stock_dir.Path.Replace("\", "/"), ".").Replace($framework_dir.Path.Replace("\", "/"), ".")

                    #Write-Host "Diff found for $framework_file"
                    $diff | Out-File -FilePath "$patch_file" -Encoding utf8
                }
            }
        }
        else {
            Write-Host "couldn't find stock file for $framework_file @ $stock_file"
        }
    }
}
Main
