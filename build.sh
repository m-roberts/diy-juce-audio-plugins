#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"

mkdir -p ${DIR}/artefacts
rm -rf ${DIR}/artefacts/*

for dir in ${DIR}/src/plugin/*; do
  (
    # Clean JUCE submodule
    cd ${DIR}/lib/JUCE
    git clean -fdx

    # Symlink JUCE to project
    [[ -e JUCE ]] || ln -s ${DIR}/lib/JUCE ${dir}

    # Build
    cd "${dir}"
    cmake .
    make -j$(sysctl -n hw.logicalcpu)

    # Store
    suffix_to_remove="*_artefacts"
    artefacts_dir="$(find . -name "${suffix_to_remove}")"

    new_artefacts_dir="${DIR}/artefacts/$(echo ${artefacts_dir} | sed 's/_artefacts//')"
    mv "${artefacts_dir}" "${new_artefacts_dir}"
    rm -rf \
      ${dir}/{CMakeCache.txt,CMakeFiles,JUCE,Makefile,cmake_install.cmake} \
      ${new_artefacts_dir}/{JuceLibraryCode,Debug,lib*_SharedCode.a}
  )
done

# Clean up undesirable artefact files
rm -rf ${DIR}/artefacts/*/{JuceLibraryCode,Debug,lib*_SharedCode.a}

# Final JUCE cleanup
cd ${DIR}/lib/JUCE
git clean -fdx

# Patch installer config
pkgproj="${DIR}/custom-juce-audio-plugins.pkgproj"
cp "${pkgproj}" "${pkgproj}.bak"
sed -i '' "s|CURRENT_DIR_PLACEHOLDER|${DIR}|g" "${pkgproj}"

# Build installer
packagesbuild -v "${pkgproj}"

# sudo pkgbuild \
#   --component /path_to_installed_app/macapp.app \
#   --install-location /Applications \
#   --sign "Developer ID Installer: *******" \
#   /path_to_saved_package/packagename.pkg

# sudo productbuild \
#   --package /path_to_saved_package/packagename.pkg \
#   --content /path_to_app/ \
#   --sign "Developer ID Installer: *******" \
#   /path_to_signed_pkg/signed.pkg

# TODO: sign package
# https://apple.stackexchange.com/a/377236
# (req's Apple Developer acct)
#
# /usr/sbin/spctl --assess --ignore-cache --verbose --type install ${DIR}/build/*.pkg

# Unpatch installer config
mv "${pkgproj}.bak" "${pkgproj}"
