# AROS Git Repository

> This is the main repository for active development of the AROS Operating System.
> The repository contains the main Operating System components, SDK and Build System.


## Nightly Test Builds


* All builds are scheduled to run at 00:00 UTC.
* The builds are made using the scripts/azure-pipelines.yml file. Further details can be found in that file.
* Currently all builds are configured using default toolchain settings, except the pc-x86_64-smp target which uses the experimental gcc 9.1.0 patch.
* The main AROS target and distfiles are built for each arch.
* The builds are downloadable via http://www.aros.org/nightly1.php [![Download AROS Research Operating System](https://img.shields.io/sourceforge/dt/aros.svg)](https://sourceforge.net/projects/aros/files/nightly2/).

| | | |
| --- | --- | --- |
| BUILD Arch <td colspan=2> Status |
| --- | GNU toolchain | LLVM toolchain |
| amiga-m68k | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-amiga-m68k?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=14&branchName=master) | --- |
| pc-i386 | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-pc-i386?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=16&branchName=master) | --- |
| pc-x86_64 | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-pc-x86_64?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=17&branchName=master) | --- |
| pc-x86_64-smp | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-pc-x86_64-smp?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=15&branchName=master) | --- |
| raspi-armhf | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-raspi-armhf?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=19&branchName=master) | --- |
| sam440-ppc | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-sam440-ppc?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=20&branchName=master) | --- |
| linux-i386 | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-linux-i386?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=21&branchName=master) | --- |
| linux-x86_64 | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-linux-x86_64-gnu?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=18&branchName=master) | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-linux-x86_64-llvm?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=26&branchName=master) |
| darwin-i386 | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-darwin-i386?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=24&branchName=master) | --- |
| darwin-x86_64 | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-darwin-x86_64?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=22&branchName=master) | --- |
| darwin-ppc | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-darwin-ppc?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=25&branchName=master) | --- |
| mingw32-i386 | [![Build Status](https://dev.azure.com/aros-development-team/AROS/_apis/build/status/aros-development-team.AROS-mingw32-i386?branchName=master)](https://dev.azure.com/aros-development-team/AROS/_build/latest?definitionId=23&branchName=master) | --- |

## Building the Docker container

The Dockerfile in this repo will compile AROS in order to have a toolchain working for building AROS applications.

This image is built from the [amigadev/docker-base:latest](https://github.com/AmigaPorts/docker-base) base image.

### Build the Docker container

docker build --rm -t "amigadev/arosv1-cross-toolchain:x86_64" -f Dockerfile.x86_64 .

Compiling AROS requires some external packages. If you already have them in `./bin/Sources/` you can use them and save some time on compilation (and allow an offline image build):

docker build --rm -t "amigadev/arosv1-cross-toolchain:x86_64" --build-arg HAVE_LOCAL_PACKAGES=1 -f Dockerfile.x86_64 .

It also needs the [contribs packages](https://github.com/AmigaPorts/AROS-contrib) (third-party libraries). If you already have a "contrib" directory, it will be used instead of checking out the repo.

To run the image for tests/debugging:

docker run --rm -it "amigadev/arosv1-cross-toolchain:x86_64" /bin/bash

## Contributing

Please see the [CONTRIBUTING.md](CONTRIBUTING.md) file for details on joining the GitHub organization, and guidelines on contributing to the AROS project.

## License

This project is licensed under the APL License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

AROS contains parts built upon external components - see the [ACKNOWLEDGEMENTS](ACKNOWLEDGEMENTS) file for details
