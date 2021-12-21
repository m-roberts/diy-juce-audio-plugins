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

# Symlink to ~/Library/Audio/Plug-Ins
mkdir -p ~/Library/Audio/Plug-Ins/{Components,VST3}
find $(pwd) -name "*.component" -print0 | xargs -0 -I {} ln -s {} ~/Library/Audio/Plug-Ins/Components
find $(pwd) -name "*.vst3" -print0 | xargs -0 -I {} ln -s {} ~/Library/Audio/Plug-Ins/VST3

# Clean up undesirable artefact files
rm -rf ${DIR}/artefacts/*/{JuceLibraryCode,Debug,lib*_SharedCode.a}

# Final JUCE cleanup
cd ${DIR}/lib/JUCE
git clean -fdx
