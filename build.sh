#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"

mkdir -p ${DIR}/artefacts

for dir in ./src/plugin/*; do
  (
    cd ${dir}
    ln -s ${DIR}/lib/JUCE .

    cmake .
    make -j$(sysctl -n hw.logicalcpu)

    artefacts_dir=$(find . -name "*_artefacts")

    mv ${artefacts_dir} ${DIR}/artefacts/$(echo ${artefacts_dir} | sed 's/_artefacts//')
    rm -rf ./CMakeCache.txt ./CMakeFiles JUCE Makefile cmake_install.cmake
  )
done

# Clean up unwanted dirs
rm -rf ${DIR}/artefacts/*_artefacts/{JuceLibraryCode,Debug,lib*_SharedCode.a}
